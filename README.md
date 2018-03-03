# Disco :dancer: :dancer:

## Wait what ?

A MQTT enabled disco ball. Start the CI disco ball with wifi by adding value to the MQTT broker.

The MQTT library used in this project is [esp_mqtt](https://github.com/tuanpmt/esp_mqtt) from tuanpmt.

## Compile

Be sure to change the settings in the files in `include/user_config.h`.

The NON OS SDK and GCC toolchain for xtensa should be installed on your computer before compiling.

```bash
cd esp_mqtt
#clean
make clean
# Compile the disco ball code
make SDK_BASE=<your sdk path>/ESP8266_NONOS_SDK ESPTOOL=<your esptool path>/esptool/esptool.py DISCO_BALL=yes all
# Compile the disco light code
make SDK_BASE=<your sdk path>/ESP8266_NONOS_SDK ESPTOOL=<your esptool path>/esptool/esptool.py DISCO_LIGHT=yes all
# Flash (works for wemos other ESP-12 based devboard)
make ESPPORT=/dev/ttyUSB0 flash
# Flash on an ESP-01
make ESPPORT=/dev/ttyUSB0 ESP_SIZE=16m flash
```

## LICENSE

[MIT License](https://github.com/Cerkinfo/disco/blob/master/LICENSE)
