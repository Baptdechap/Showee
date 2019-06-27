#include <SPI.h>
#include <WiFi101.h>
#include "arduino_secrets.h"
#include "myEPD.h"
#define DEBUT_TRAME '<'
#define FIN_TRAME '>'
char toto[128];
extern String Subs[];
const byte rxPin = 6;
const byte txPin = 7;
String ReceivedString = "";
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
IPAddress server(10, 96, 16, 7); // numeric IP for Google (no DNS)
//char server[] = " 10.96.16.7 ";    // name address for Google (using DNS)
WiFiClient client;

//Subs[0].toCharArray(toto, 128)
void Infos(void)
{
  Subs[0].toCharArray(toto, 128);
  epd_set_color (BLACK , WHITE);
  epd_set_en_font(ASCII64);
  epd_disp_string(toto, 400, 100);
  epd_set_color (BLACK , WHITE);
  epd_set_en_font(ASCII32);
  epd_disp_string("Nom", 380, 70);

  Subs[1].toCharArray(toto, 128);
  epd_set_color (BLACK , WHITE);
  epd_set_en_font(ASCII64);
  epd_disp_string(toto, 400, 250);
  epd_set_color (BLACK , WHITE);
  epd_set_en_font(ASCII32);
  epd_disp_string("Prenom", 380, 225);

  Subs[2].toCharArray(toto, 128);
  epd_set_color (BLACK , WHITE);
  epd_set_en_font(ASCII64);
  epd_disp_string(toto, 400, 405);
  epd_set_color (BLACK , WHITE);
  epd_set_en_font(ASCII32);
  epd_disp_string("Entreprise",380,380);
  
  Subs[4].toCharArray(toto, 128);
  epd_set_color (BLACK , WHITE);
  epd_set_en_font(ASCII64);
  epd_disp_string(toto, 70, 360);
  epd_set_color (BLACK , WHITE);
  epd_set_en_font(ASCII32);
  epd_disp_string("De", 30, 340);

  Subs[5].toCharArray(toto, 128);
  epd_set_color (BLACK , WHITE);
  epd_set_en_font(ASCII64);
  epd_disp_string(toto, 70, 490);
  epd_set_color (BLACK , WHITE);
  epd_set_en_font(ASCII32);
  epd_disp_string("Jusqu'a", 30, 460);
  
  Subs[3].toCharArray(toto, 128);
  epd_disp_bitmap(toto, 30, 40);
  Serial.println(toto);
  //epd_disp_bitmap("SHOWEE.BMP", 30, 60); 

}

void DotLine()
{
  for (int i = 0; i < 600; i += 8)
  {
    epd_draw_pixel(i, 40);
    epd_draw_pixel(i + 1, 40);
    epd_draw_pixel(i + 2, 40);
    epd_draw_pixel(i + 4, 40);
  }
}


void setup() {
  WiFi.setPins(8, 7, 4, 2);
  Serial.begin(9600);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(1000);
  }
  if (client.connect(server, 80)) {
    client.println("GET /showee/test.php");
    client.println("Host: 10.96.16.7");
    client.println("Connection: close");
    client.println();
  }
  Serial.begin( 115200 );
  //mySerial.begin(115200);
  Serial1.begin( 115200 );
  epd_reset();
  epd_init();
  epd_set_memory(MEM_NAND);
  epd_set_memory(MEM_TF);
  epd_screen_rotation (0);
  epd_clear();
  epd_set_en_font(ASCII32);
  epd_set_color (BLACK , WHITE);
  epd_disp_string("Poste n", 650, 15);
  epd_set_en_font(ASCII64);
  epd_set_color (BLACK , WHITE);
  epd_disp_string("3", 750, 0);
  //DotLine();
  epd_udpate();
}

void loop() {

  while (client.available()) {

    char c = client.read();
    Serial.write(c);
    char Chr = c;
    if (Chr == DEBUT_TRAME) ReceivedString = "";
    else
    {
      if (Chr == FIN_TRAME)
      {
        Serial.println();
        Serial.print("Trame reÃ§ue: ");
        Serial.println(ReceivedString);
        String_Split(',', ReceivedString);
        Infos();
        epd_udpate();
      }
      else ReceivedString += Chr;
    }
    
  }
  

}








