
/*
####################################################################
## Simple Mqtt Client Code for connecting to Eugenio.io IoT platform
####################################################################
##
##################################################
## Código feito por Artur Sarlo(artur.sarlo@la.logicalis.com) codigo 
## modificado por Luiz Henrique (luizhfmonteiro@gmail.com) para 
## Eugenio Challenge Hub
##################################################
*/

#ifndef SECRETS
#define SECRETS

/*
 #########################################################################################
 # CHANGE HERE
 #########################################################################################
*/
#define WIFI_SSID "Luiz-2.4G-"
#define WIFI_PASSWORD "ruanicolaucoelho"

#define DEVICE_ID "3ebc74ed-60a0-4873-8d09-920975fabfcf"

// Copy contents from CA certificate here ▼
static const char cacert[] PROGMEM = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDdzCCAl+gAwIBAgIEAgAAuTANBgkqhkiG9w0BAQUFADBaMQswCQYDVQQGEwJJ\n" \
"RTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJlclRydXN0MSIwIAYD\n" \
"VQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTAwMDUxMjE4NDYwMFoX\n" \
"DTI1MDUxMjIzNTkwMFowWjELMAkGA1UEBhMCSUUxEjAQBgNVBAoTCUJhbHRpbW9y\n" \
"ZTETMBEGA1UECxMKQ3liZXJUcnVzdDEiMCAGA1UEAxMZQmFsdGltb3JlIEN5YmVy\n" \
"VHJ1c3QgUm9vdDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKMEuyKr\n" \
"mD1X6CZymrV51Cni4eiVgLGw41uOKymaZN+hXe2wCQVt2yguzmKiYv60iNoS6zjr\n" \
"IZ3AQSsBUnuId9Mcj8e6uYi1agnnc+gRQKfRzMpijS3ljwumUNKoUMMo6vWrJYeK\n" \
"mpYcqWe4PwzV9/lSEy/CG9VwcPCPwBLKBsua4dnKM3p31vjsufFoREJIE9LAwqSu\n" \
"XmD+tqYF/LTdB1kC1FkYmGP1pWPgkAx9XbIGevOF6uvUA65ehD5f/xXtabz5OTZy\n" \
"dc93Uk3zyZAsuT3lySNTPx8kmCFcB5kpvcY67Oduhjprl3RjM71oGDHweI12v/ye\n" \
"jl0qhqdNkNwnGjkCAwEAAaNFMEMwHQYDVR0OBBYEFOWdWTCCR1jMrPoIVDaGezq1\n" \
"BE3wMBIGA1UdEwEB/wQIMAYBAf8CAQMwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3\n" \
"DQEBBQUAA4IBAQCFDF2O5G9RaEIFoN27TyclhAO992T9Ldcw46QQF+vaKSm2eT92\n" \
"9hkTI7gQCvlYpNRhcL0EYWoSihfVCr3FvDB81ukMJY2GQE/szKN+OMY3EU/t3Wgx\n" \
"jkzSswF07r51XgdIGn9w/xZchMB5hbgF/X++ZRGjD8ACtPhSNzkE1akxehi/oCr0\n" \
"Epn3o0WC4zxe9Z2etciefC7IpJ5OCBRLbf1wbWsaY71k5h+3zvDyny67G7fyUIhz\n" \
"ksLi4xaNmjICq44Y3ekQEe5+NauQrz4wlHrQMz2nZQ/1/I6eYs9HRCwBXbsdtTLS\n" \
"R9I4LtD+gdwyah617jzV/OeBHRnDJELqYzmp\n" \
"-----END CERTIFICATE-----\n";

// Copy contents from cert.pem here ▼
static const char client_cert[] PROGMEM = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIFCTCCAvGgAwIBAgIUXnrqgzDJGADz+7hb/Eo3DwQfkxswDQYJKoZIhvcNAQEL\n" \
"BQAwFDESMBAGA1UEAwwJbG9jYWxob3N0MB4XDTIwMTAwNjAwMjQwMFoXDTIxMTAw\n" \
"NjAwMjQwMFowFDESMBAGA1UEAwwJbG9jYWxob3N0MIICIjANBgkqhkiG9w0BAQEF\n" \
"AAOCAg8AMIICCgKCAgEArJIYI0NXEZTmRV61lff9c4fxCVuLKH0WiwdoQIqeSvwp\n" \
"eF+vSqRtUxlqruJQUUWEpMpT5csBLmjI3gS9YRPqUaqUIhkZ+eJjKJR1XADXCdNP\n" \
"Hsoq4FFMiNsadcX5ccoy7563b9Bs+vFv0F9qwDDInhN8NeiiFs3ajl8w9f1QJ5+Y\n" \
"+dU/JLxk/Hl+2Y0EXhggzKGSRqZ/hIlYHWmFo96jgad69lST7rZpNxBZY2LWCaZK\n" \
"ORfDlu+KvIwkDB8+gMhD9oZv7gaEC43En0EQijzYH+bdqffPw3SZ4A1xLO8HD+nO\n" \
"fYBgBnheMnvr6ZQThiCRJxvYeev6dxsxPqJGd8RcIanYD+81WAYAWmOj/iWvmIZK\n" \
"uYXWup+n7fRKexjXEyDbFWkwZzYqUtCEtuh7xXEPl7BqafsTrD154qtYMGbatbe0\n" \
"300SrDjtZ0Spnq1JlEKxJj9KeQsHERdtVsFRNfVOWjmjtKh/iIuY0c8R0NJ9X1Pv\n" \
"3fGZI5EVOyVnJP+e2zk55Ra47umllWzaM8xaqUQaTMnR9BuEhFcBgNh75UYQKImF\n" \
"df0OTkoBFxLHv2fvF1JXqHVv+hf/a+FXQ687TgKR6bN+Aq0aQ95D9vXvyvTSFKBz\n" \
"PemR69ettYBmVNn9d6vsUOUlHqXa6d3E1T5sbrQup4FmmcOxFLs5d/O1sybo6VkC\n" \
"AwEAAaNTMFEwHQYDVR0OBBYEFGbn4bqX3Wi3zD+ieJOqm9E3Tl72MB8GA1UdIwQY\n" \
"MBaAFGbn4bqX3Wi3zD+ieJOqm9E3Tl72MA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZI\n" \
"hvcNAQELBQADggIBAJqZQTL+3E8eVxA1lPa3fldNx08f2UNNabEKEP+Fxq7IoBnd\n" \
"RHEofacpo7ERZZ298Pp4WHZe/P7jcsFE51jhvwbxod+8y9//YKwodOeqi2/3Q+5q\n" \
"aUsWq1xOze7ELksYEJtNvr1TlIAgnjDQLYgojIlpkoKtfbDG8BWrrEEmXJMr/zx5\n" \
"NFboeENrlUUCnlfAY69INfxbw+7JrMQCKajQXcObFQysLTE9Z5P7wCrmfGxud2d0\n" \
"LD4DEKO0C/jUmCqMgibiccOBj2QMmuonnR/CmBUJHU/ZID84+ZPmVXzKPO1DfoPr\n" \
"yutG2dIZoQY7j/lGdz1oGU9ulBBuVV3/UBa2oBnekO46ptsP2pcYncCVvgSedCOo\n" \
"mvywlRXbPO7LvdC3SoSGgYaOkRJqip/sAQZd8mogils80p9PmPOgXJK0PD5CGK9I\n" \
"bdY3MMbTCeRaFotScKKk4iaHkJbngFChNIQq9quzchf5+Eto+YYIwxQIkLwAjgih\n" \
"S33Y/a9Ntud2Hf8uBdTHGwRL5Btw3XgsT+5icbnBr9f2pZtqm+ApWEXNBg3ztycY\n" \
"TInJ2u5XTtgfbdQ64PqDnwhqJ/j+sXsJwig1Ss6j064GWBAZPWScJvB1o+pi/0Rf\n" \
"6TrH75+QhaSRrw1nltWMIxCw1OTXyBVky9sdnyYLpBbVAzc5BWGxtri4yZLx\n" \
"-----END CERTIFICATE-----\n";

// Copy contents from  key.pem here ▼
static const char privkey[] PROGMEM = \
"-----BEGIN PRIVATE KEY-----\n" \
"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\n" \
"/IAebRr7FlPTT0HBRZUmWTRClCP+\n" \
"-----END PRIVATE KEY-----\n";

/*
#########################################################################################
#########################################################################################
*/

// NTP related
#define UTC_TIME_ZONE_BRAZIL_HOURS -3
#define UTC_TIME_ZONE_BRAZIL_SECONDS UTC_TIME_ZONE_BRAZIL_HOURS * 3600
//#define USE_SUMMER_TIME_DST  //uncomment to use DST
#define DST_HOURS 0
#define DST_SECONDS DST_HOURS * 3600
#define CURRENT_TIME_APROXIMATION_AS_EPOCH_SECONDS 1510592825
#define NTP_SERVER_0 "pool.ntp.org"
#define NTP_SERVER_1 "time.nist.gov"

// MQTT related
#define MQTT_BROKER "logicalis-eugeniostg-iothub.azure-devices.net"
#define MQTT_PORT 8883
#define MQTT_USER "logicalis-eugeniostg-iothub.azure-devices.net/" DEVICE_ID "/api-version=2019-03-30"

#define MQTT_SUB_CLOUD_TO_DEVICE_TOPIC "devices/529a226c-f80f-4c26-8175-46f8e3c37ff8/messages/devicebound/#"
#define MQTT_SUB_INVOKE_BASE_TOPIC "$iothub/methods/POST/"
#define MQTT_SUB_INVOKE_TOPIC "$iothub/methods/POST/#"

#define MQTT_PUB_INVOKE_REPLY_TOPIC "$iothub/methods/res/{status_code}/?$rid={rid}"
#define MQTT_PUB_DEVICE_TO_CLOUD_TOPIC "devices/529a226c-f80f-4c26-8175-46f8e3c37ff8/messages/events/"

// #define USE_ARDUINO_JSON_LIB

#endif