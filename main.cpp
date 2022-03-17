#include "mbed.h"
#include "wifi.h"
/*------------------------------------------------------------------------------
Hyperterminal settings: 115200 bauds, 8-bit data, no parity

This example 
  - connects to a wifi network (SSID & PWD to set in mbed_app.json)
  - Connects to a TCP server (set the address in RemoteIP)
  - Sends "Hello" to the server when data is received

This example uses SPI3 ( PE_0 PC_10 PC_12 PC_11), wifi_wakeup pin (PB_13), 
wifi_dataready pin (PE_1), wifi reset pin (PE_8)
------------------------------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/
#define WIFI_WRITE_TIMEOUT 10000
#define WIFI_READ_TIMEOUT  10000
#define CONNECTION_TRIAL_MAX          10

/* Private typedef------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Serial pc(SERIAL_TX, SERIAL_RX);
uint8_t RemoteIP[] = {MBED_CONF_APP_SERVER_IP_1,MBED_CONF_APP_SERVER_IP_2,MBED_CONF_APP_SERVER_IP_3, MBED_CONF_APP_SERVER_IP_4};
uint8_t RxData [500];
char* modulename;
uint8_t TxData[] = "STM32 : Hello!\n";
uint16_t RxLen;
uint8_t  MAC_Addr[6]; 
uint8_t  IP_Addr[4]; 

int main()
{
   
    int BaudRate = 115200;
    pc.baud(BaudRate);

    printf("\n");
    printf("************************************************************\n");
    printf("***   STM32 IoT Discovery kit for STM32L475 MCU          ***\n");
    printf("***                     Start AP                         ***\n");
    printf("************************************************************\n");

    /*Initialize  WIFI module */
    if(WIFI_Init() ==  WIFI_STATUS_OK) {
        printf("> WIFI Module Initialized.\n");  
        if(WIFI_GetMAC_Address(MAC_Addr) == WIFI_STATUS_OK) {
            printf("> es-wifi module MAC Address : %X:%X:%X:%X:%X:%X\n",     
                   MAC_Addr[0],
                   MAC_Addr[1],
                   MAC_Addr[2],
                   MAC_Addr[3],
                   MAC_Addr[4],
                   MAC_Addr[5]);   
        } else {
            printf("> ERROR : CANNOT get MAC address\n");
        }
        
        // Init WiFi AP Parameters
        uint8_t WiFi_SSID[10] = "ESWIFI";
        uint8_t WiFi_PASSWORD[10] = "12345678";
        uint8_t WiFi_CHANNEL = 0;
        uint8_t WiFi_MAX_CONNECTIONS = 2;
        WIFI_Ecn_t WiFi_ecn = WIFI_ECN_WPA2_PSK;
        // End Init WiFi AP Parameters
    
        if( WIFI_ConfigureAP(WiFi_SSID, WiFi_PASSWORD, WiFi_ecn, WiFi_CHANNEL, WiFi_MAX_CONNECTIONS) == WIFI_STATUS_OK) {
            printf("> es-wifi module AP ready to connect\n");
         }
         else{
             printf("> Failed to start AP \n");
        }
    }
}
