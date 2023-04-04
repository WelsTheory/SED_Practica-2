
#include "main.h"
#include "config.h"

const char *TAG = "MAIN";

char BROKER[100];

/*******************************************************************************
 Programa principal
******************************************************************************/
void app_main(void)
{
  char wifi_message[100];
  char pwd_message[200];
  char medicones[32];

  int active_led = 0;

  int rssi;
  char timestamp[64]="";
  int64_t epoch;

  char msg[100];
  char led_msg[50];

  CRONO_sntpInit();
  IO_gpioInit();
  SD_mount();

  FILE * f = SD_open("config.txt", "r");

  SD_gets(f, wifi_message, sizeof(wifi_message));
  SD_gets(f, pwd_message, sizeof(wifi_message));
  SD_gets(f, medicones, sizeof(wifi_message));
  SD_gets(f, BROKER, sizeof(BROKER));
  SD_close(f);
  CRONO_delayMs(500);
  printf("valor de red %s\n",wifi_message); 
  // Inicializaciones
  WIFI_userInit(wifi_message,pwd_message);
  MQTT_userInit(BROKER);
  printf("valor de Broker %s\n",BROKER);  
  
  f = SD_open("lecturas.csv", "w");
  SD_printf(f, "Timestamp, RSSI\n");
  active_led ^= 1;
  sprintf(led_msg,"%d",active_led);
  MQTT_publish("test/led",led_msg);  
  IO_toggleLed();

  for(int i=0;i<medicones[0];i++)
  {
    rssi = WIFI_getRSSI();
    epoch = CRONO_getTime(timestamp, sizeof(timestamp));
    sprintf(msg,"%s,%d \n", timestamp,rssi);
    SD_printf(f, "%s\n", msg);
    MQTT_publish("test/msg",msg);
    CRONO_delayMs(1000);
  }
  SD_close(f);
  active_led ^= 1;
  sprintf(led_msg,"%d",active_led);
  MQTT_publish("test/led",led_msg); 
  IO_toggleLed();

  while(1){


    

  }

  // All done, unmount partition and disable SDMMC or SPI peripheral
  SD_unmount();

}


/** EJEMPLOS DE PRACTICA **/
/*
  PARTE 1
  char timestamp[64]="";
  int64_t epoch;
  */
  

  // Use POSIX and C standard library functions to work with files.
  /** 
   * PARTE 2
  SD_mount();
  FILE * f = SD_open("wels.txt", "r");
  char delay_milis[32];
  char user_message[200];
  SD_gets(f, delay_milis, sizeof(delay_milis));
  SD_gets(f, user_message, sizeof(user_message));
  SD_close(f);

  int d = atoi(delay_milis);
  */

  /*
  PARTE 3
  
  char timestamp[64]="";
  int64_t epoch;
  SD_mount();
  FILE * f = SD_open("welstheory.txt", "w");
  SD_printf(f, "Lecturas de tiempo en distintos formatos:\n");
  for(int i=0; i<50; i++)
  {
    epoch = CRONO_getTime(timestamp, sizeof(timestamp)); 
    SD_printf(f, "Epoch: %lli -- Timestamp: %s\n", epoch, timestamp);
    CRONO_delayMs(500);
  }
  SD_close(f);*/


  /*
    PARTE 2
    CRONO_delayMs(d);
    MQTT_publish("test/msg",user_message);
    printf("MAIN: Mensaje %s\n",user_message);
    printf("MAIN: Mili Segundos %s\n",delay_milis);
    */
    // PArte 1
    // Loop
    //CRONO_delayMs(1000);
    //epoch = CRONO_getTime(timestamp, sizeof(timestamp));
    //printf("MAIN: Timestamp %s: \n", timestamp);
    //printf("MAIN: Epoch %lli: \n'", epoch);