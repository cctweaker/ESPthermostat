///////////////////////////////////////////////////////////////////////
// configuration file
///////////////////////////////////////////////////////////////////////
const char wifi_cfg_file[] = "wifi.json";
const char dev_cfg_file[] = "device.json";
const char mqtt_cfg_file[] = "mqtt.json";
const char thermo_cfg_file[] = "thermost.json";
///////////////////////////////////////////////////////////////////////

//

///////////////////////////////////////////////////////////////////////
// flags
///////////////////////////////////////////////////////////////////////
bool cfg_wifi = false;
bool cfg_dev = false;
bool cfg_mqtt = false;
bool cfg_thermostat = false;

bool use_wifi = false;
bool use_ssl = false;
bool use_softap = false;
bool use_dns = false;
bool use_mqtt = false;
bool use_webserver = false;
bool use_thermostat = false;

bool start_wifi = false;
bool start_mqtt = false;
bool start_webserver = true;

bool do_ota_update = false;
///////////////////////////////////////////////////////////////////////

//

///////////////////////////////////////////////////////////////////////
// DEVICE
///////////////////////////////////////////////////////////////////////
const char FW_NAME[] = "ESPthermostat";
#ifdef LNG
#if LNG == 1
const char LANG[] = "_RO";
#else
const char LANG[] = "";
#endif
#endif

char update_url[128] = "esp.3dstar.ro/";

char LOC[32] = "home/";
char TIP[32] = "hvac/";
char NAME[32] = "ESPthermostat";
char XTRA[32] = "";

bool heartbeat = false;
uint8_t heartbeat_minutes = 60;
unsigned long last_heartbeat = 0;
///////////////////////////////////////////////////////////////////////

//

///////////////////////////////////////////////////////////////////////
// WIFI
///////////////////////////////////////////////////////////////////////
char SSIDa[32] = "";
char PASSa[65] = "";

char SSIDb[32] = "";
char PASSb[65] = "";

const char STA_PASS[] = "abcd1234";
IPAddress STA_IP(192, 168, 10, 1);
IPAddress STA_MASK(255, 255, 255, 0);
const byte DNS_PORT = 53;
///////////////////////////////////////////////////////////////////////

//

///////////////////////////////////////////////////////////////////////
// MQTT
///////////////////////////////////////////////////////////////////////
char MQTT_HOST[128] = "mqtt.3dstar.ro";
int MQTT_PORT = 1883;
char MQTT_USER[32] = "test";
char MQTT_PASS[64] = "12345678";

char WILL[32] = "will";
char PUB[32] = "";
char SUB[32] = "cmnd";
char STAT[32] = "stat";
char TELE[32] = "tele";
///////////////////////////////////////////////////////////////////////

//

///////////////////////////////////////////////////////////////////////
// THERMOSTAT
///////////////////////////////////////////////////////////////////////
bool use_1wire = false;
uint8_t onewire_device_count = 0;
unsigned int last_temp_read = 0;
float onewire_temp[8];
uint8_t addresses[64];

bool use_expander = false;
uint8_t io_expander_address = 0;
uint8_t max_channels = 0;
uint8_t channel_to_pin[4] = {2, 0};
unsigned int channel_timeout[4];
bool channel_timeout_check[4];
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// Let's Encrypt CA certificate for SSL
// it will authenticate any valid Let's Encrypt issued cert
///////////////////////////////////////////////////////////////////////
#ifdef USE_SSL
static const char digicert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIEkjCCA3qgAwIBAgIQCgFBQgAAAVOFc2oLheynCDANBgkqhkiG9w0BAQsFADA/
MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT
DkRTVCBSb290IENBIFgzMB4XDTE2MDMxNzE2NDA0NloXDTIxMDMxNzE2NDA0Nlow
SjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxIzAhBgNVBAMT
GkxldCdzIEVuY3J5cHQgQXV0aG9yaXR5IFgzMIIBIjANBgkqhkiG9w0BAQEFAAOC
AQ8AMIIBCgKCAQEAnNMM8FrlLke3cl03g7NoYzDq1zUmGSXhvb418XCSL7e4S0EF
q6meNQhY7LEqxGiHC6PjdeTm86dicbp5gWAf15Gan/PQeGdxyGkOlZHP/uaZ6WA8
SMx+yk13EiSdRxta67nsHjcAHJyse6cF6s5K671B5TaYucv9bTyWaN8jKkKQDIZ0
Z8h/pZq4UmEUEz9l6YKHy9v6Dlb2honzhT+Xhq+w3Brvaw2VFn3EK6BlspkENnWA
a6xK8xuQSXgvopZPKiAlKQTGdMDQMc2PMTiVFrqoM7hD8bEfwzB/onkxEz0tNvjj
/PIzark5McWvxI0NHWQWM6r6hCm21AvA2H3DkwIDAQABo4IBfTCCAXkwEgYDVR0T
AQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAYYwfwYIKwYBBQUHAQEEczBxMDIG
CCsGAQUFBzABhiZodHRwOi8vaXNyZy50cnVzdGlkLm9jc3AuaWRlbnRydXN0LmNv
bTA7BggrBgEFBQcwAoYvaHR0cDovL2FwcHMuaWRlbnRydXN0LmNvbS9yb290cy9k
c3Ryb290Y2F4My5wN2MwHwYDVR0jBBgwFoAUxKexpHsscfrb4UuQdf/EFWCFiRAw
VAYDVR0gBE0wSzAIBgZngQwBAgEwPwYLKwYBBAGC3xMBAQEwMDAuBggrBgEFBQcC
ARYiaHR0cDovL2Nwcy5yb290LXgxLmxldHNlbmNyeXB0Lm9yZzA8BgNVHR8ENTAz
MDGgL6AthitodHRwOi8vY3JsLmlkZW50cnVzdC5jb20vRFNUUk9PVENBWDNDUkwu
Y3JsMB0GA1UdDgQWBBSoSmpjBH3duubRObemRWXv86jsoTANBgkqhkiG9w0BAQsF
AAOCAQEA3TPXEfNjWDjdGBX7CVW+dla5cEilaUcne8IkCJLxWh9KEik3JHRRHGJo
uM2VcGfl96S8TihRzZvoroed6ti6WqEBmtzw3Wodatg+VyOeph4EYpr/1wXKtx8/
wApIvJSwtmVi4MFU5aMqrSDE6ea73Mj2tcMyo5jMd6jmeWUHK8so/joWUoHOUgwu
X4Po1QYz+3dszkDqMp4fklxBwXRsW10KXzPMTZ+sOPAveyxindmjkW8lGy+QsRlG
PfZ+G6Z6h7mjem0Y+iWlkYcV4PIWL1iwBi8saCbGS5jN2p8M+X+Q7UNKEkROb3N6
KOqkqm57TH2H3eDJAkSnh6/DNFu0Qg==
-----END CERTIFICATE-----
)EOF";
#endif
///////////////////////////////////////////////////////////////////////