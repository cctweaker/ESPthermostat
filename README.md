# ESPthermostat
Software for the 4 channel relay controller and 8 channel DS18B20 sensor reader provided by <a href="https://3dstar.ro/proiecte/espthermostat">3DStar.ro</a>

# Features
- simple or secure MQTT connection, Let's Ecrypt CA cetificate already loaded
- topic structure for multiple buildings (locations) control: <code>location/device_espid/+</code>
- main and backup WiFi connections
- secured, no access point is presented in case both WiFi connections are unavailable
- after the initial configuration, web access can be disabled, module uses just pure MQTT
- extra information on device status topic: type, ID, supply voltage, AP SSID, AP RSSI, AP mac



# Hardware
Roll your own or get one from <a href="https://3dstar.ro/proiecte/espthermostat">3DStar shop</a> in PCB, kit (PCB + components), SMD kit (PCB with soldered SMD components + bags of through hole components) or fully assembled form.

The ESP-01 / ESP-01S from AI Thinker is used to control one PCA9536D 4bit IO expander. On each channel there is a relay that can be used to control heating equipment (boilers, pumps, valves, etc.).

8 connectors are provided for directly attaching 1-Wire DS18B20 temperature sensors. Their number is not limited and by using splitter cables more than 8 can be attached.


# Build & upload
- there are 2 methods:
    - download, edit config.h, build & upload
    - download binary and upload
For building the sources PlatformIO is recommended for automatic library management.

# Usage
- mqtt topic: <code>LOC/TIP/NAME_ESPid</code> where LOC, TIP and NAME are user defined and ESPid is the HEX representation of your ESP mac address' last 3 bytes. What follows are possible suffixes and must be appended to the above mqtt topic.
- command topic: <code>/cmnd/...</code>
    - <code>save</code>: save current configuration to LittleFS
    - <code>update</code>: perform OTA update
    - <code>reset</code>: restart ESP device
    - <code>format</code>: format LittleFS space
    - <code>list</code>: list current LittleFS stored config.json to Serial @ 115200bps. Other than this serial is not used at all.
    - <code>config</code>: change device configuration. Due to MQTT message length restrictions do not send json messages longer than 256 bytes. Get examples from config.json in data folder. You can send any part at any time. Remember to send save command after you are satisfied with the configuration.

    - <code>/rX</code>: relay control. X is the relay number. Payload can be 0 = OFF, 1 = ON.

- relay status topic: <code>/relay/X</code> where X is the relay number. Payload will be 0 for OFF and 1 for ON. It is updated by the ESP after processing commands, statuses are sent with retain flag.
- sensorss topic: <code>/temp</code>, a json message is sent continaing the unique codes and temperature of all found DS18B20 sensors.
- status topic: <code>/stat</code> where the ESP sends periodic updates (heartbeat) with type, ID, supply voltage, SSID, RSSI, BSSID (AP mac) Example: <code>{"Type":"thermostat","ID":"abcdef","Vin":3.31,"SSID":"WIFI","RSSI":-29,"BSSID":"D8:50:E6:XX:XX:XX"}</code>
- will topic: <code>/will</code> Payload is 1 when device is ON and 0 when powered OFF


# Libraries
- https://github.com/256dpi/arduino-mqtt
- https://github.com/bblanchon/ArduinoJson

# PCB example
<img src="https://github.com/cctweaker/ESPthermostat/blob/master/Hardware/PCB ESPthermostat v1.1 top.png?raw=true">
<img src="https://github.com/cctweaker/ESPthermostat/blob/master/Hardware/PCB ESPthermostat v1.1 bottom.png?raw=true">