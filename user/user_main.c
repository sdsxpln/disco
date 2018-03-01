#include "ets_sys.h"
#include "driver/uart.h"
#include "osapi.h"
#include "mqtt.h"
#include "wifi.h"
#include "debug.h"
#include "gpio.h"
#include "user_interface.h"
#include "mem.h"
#include "json.h"
#include "jsonparse.h"
#ifdef DISCO_BALL
#include "io_pwm.h"
#endif
#ifdef DISCO_LIGHT
#include "io_relay.h"
#endif

MQTT_Client mqttClient;

static void ICACHE_FLASH_ATTR wifiConnectCb(uint8_t status) {
  if (status == STATION_GOT_IP) {
    MQTT_Connect(&mqttClient);
  } else {
    MQTT_Disconnect(&mqttClient);
  }
}

static void ICACHE_FLASH_ATTR mqttConnectedCb(uint32_t *args) {
  MQTT_Client* client = (MQTT_Client*)args;
  INFO("MQTT: Connected\r\n");
  MQTT_Subscribe(client, "/ciot/cercle/1/0/event/disco/intensity", 0);
}

static void ICACHE_FLASH_ATTR mqttDisconnectedCb(uint32_t *args) {
  MQTT_Client* client = (MQTT_Client*)args;
  INFO("MQTT: Disconnected\r\n");
}

static int ICACHE_FLASH_ATTR get_value_from_json(char* raw_json, int length) {
  struct jsonparse_state state;
  jsonparse_setup(&state, raw_json, length);

  int json_type;
  while (json_type = jsonparse_next(&state)) {
    switch (json_type) {
      case JSON_TYPE_INT:
        INFO("Int\n");
        int state_value = jsonparse_get_value_as_int(&state);
        return state_value;
      // case JSON_TYPE_NUMBER:
      //   printf("Number: %ld\n", jsonparse_get_value_as_long(&state));
      //   break;
      case JSON_TYPE_ERROR:
      default:
        INFO("Unknown file format: %d\n", json_type);
        return 0;
    }
  }
}

static void ICACHE_FLASH_ATTR mqttDataCb(uint32_t* args, const char* topic, uint32_t topic_len, const char* data, uint32_t data_len) {
  char *dataBuf = (char*) os_zalloc(data_len + 1);
  MQTT_Client* client = (MQTT_Client*)args;
  os_memcpy(dataBuf, data, data_len);
  dataBuf[data_len] = 0;
  INFO("Receive data: %s \r\n", dataBuf);

  int percentage = get_value_from_json(dataBuf, data_len);

  os_free(dataBuf);

  if (percentage == 0) {
#ifdef DISCO_BALL
    io_pwm_off();
#endif
#ifdef DISCO_LIGHT
    io_relay_off();
#endif
  } else {
#ifdef DISCO_BALL
    io_pwm_on_with_percentage(percentage);
#endif
#ifdef DISCO_LIGHT
    io_relay_on();
#endif
  }
}

void ICACHE_FLASH_ATTR print_info() {
  INFO("\r\n\r\n[INFO] BOOTUP...\r\n");
  INFO("[INFO] SDK: %s\r\n", system_get_sdk_version());
  INFO("[INFO] Chip ID: %08X\r\n", system_get_chip_id());
  INFO("[INFO] Memory info:\r\n");
  system_print_meminfo();

  INFO("[INFO] -------------------------------------------\n");
  INFO("[INFO] Build time: %s\n", BUID_TIME);
  INFO("[INFO] -------------------------------------------\n");
}

static void ICACHE_FLASH_ATTR app_init(void) {
  uart_init(BIT_RATE_115200, BIT_RATE_115200);
#ifdef DISCO_BALL
  io_pwm_initialize();
#endif
#ifdef DISCO_LIGHT
  io_relay_init();
#endif
  print_info();
  MQTT_InitConnection(&mqttClient, MQTT_HOST, MQTT_PORT, DEFAULT_SECURITY);
  //MQTT_InitConnection(&mqttClient, "192.168.11.122", 1880, 0);

  if (!MQTT_InitClient(&mqttClient, MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS, MQTT_KEEPALIVE, MQTT_CLEAN_SESSION)) {
    INFO("Failed to initialize properly. Check MQTT version.\r\n");
    return;
  }

  MQTT_InitLWT(&mqttClient, "/lwt", "offline", 0, 0);
  MQTT_OnConnected(&mqttClient, mqttConnectedCb);
  MQTT_OnDisconnected(&mqttClient, mqttDisconnectedCb);
  MQTT_OnData(&mqttClient, mqttDataCb);

  WIFI_Connect(STA_SSID, STA_PASS, wifiConnectCb);
}

void user_init(void) {
  system_init_done_cb(app_init);
}
