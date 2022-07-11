//conecxÃƒÂµes GPS
//GPS RX-ESP TX; 
//GPS TX-ESP RX;


//conecxÃƒÂµes RTC
//RTC SCL-ESP 22
//RTC SDA-ESP 21

//LOX SCL-ESP 22
//LOX SDA-ESP 21

//SD CS-ESP 5
//SD SCK-ESP 18
//SD MOSI-ESP 23
//SD MISO-ESP 19


//wifi e protoclo HTTP
#include <HTTPClient.h>
#include <WiFi.h>      //biblioteca do Mode MCU wifi
const char* SSID = "Laboratorio"; // rede wifi
const char* PASSWORD = "12345678"; // senha da rede wifi
String BASE_URL = "http://200.129.69.20/mccontrol/datasms/add.php?data="; //tag da URL de envio dos dados
WiFiClient client; //DleclaraÃƒÂ§ÃƒÂ£o de objeto do cliente
HTTPClient http;   //declaraÃƒÂ§ÃƒÂ£o de objto de protocolo de troca de dados

String nome1 = "Ecosolo";
String nome2 = "LAPTOP";
String nome3 = "SERVITEC_SIVP";
String nome4 = "AndroidAP";
String nome5 = "RamboDetona";

int i =0;
String wifiname;

//GPS
#include <Arduino.h>
#include <HardwareSerial.h>
#include<TinyGPS.h>   
TinyGPS GPS;   
HardwareSerial SerialGPS(2);
float latitude;
float longitude;
String latitudeS;
String longitudeS;
float vel;
float alt;
String velS;
String altS;
String dados;
String LeituraSD;
String arquivoSemanal;
const char*  arquivoSemanal2;
const char*  arquivoUp1;
String arquivoUp;
int contadorDesalvamento;
int StringSalvamento=1;
int contUP=1; 

//RTC
#include <Wire.h> 
#include <RTClib.h> 
RTC_DS3231 rtc; 
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String data;
String hora;
String dia;

//Sensor de nivel laser VL53L0X
#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
float Tank;

//SD card
#include "FS.h"
#include "SD.h"
#include "SPI.h"
String dadosPrint;
char dadosPrint1;

//declaraÃƒÂ§ÃƒÂ£o dos voids de processamento
void initSerial();
void initWiFi();
void httpRequest(String path);

//variaveis de buffer e contagem
int cont;                                                                          
float bufferTank;
String systemID="DEVICE_02";

void setup() {
  pinMode(16,OUTPUT);
  pinMode(17,OUTPUT);
  Serial.begin(9600);          // RX  TX
  SerialGPS.begin(9600, SERIAL_8N1, 15, 2);
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  lox.begin();
  SD.begin(5);

}

void loop() {
  initWiFi();
  satelite();
  relogio();
  TankLevel();
  cont=cont+1;
  bufferTank=bufferTank+Tank;
  if(cont==2){
      bufferTank=bufferTank/2;
      concatenador();
//---------------------------------     
      gerador_de_arquivo();
      appendFile(SD, arquivoSemanal2, dados.c_str());
      cont=0;
      bufferTank=0;
      }
  delay(10000);
if (WiFi.status() == WL_CONNECTED){
upLoad();
}
}

//________________HTTP REQUEST

void httpRequest(String path){
  String payload = makeRequest(path);

  if (!payload) {
    return;
  }
}

String makeRequest(String path){
  http.begin(BASE_URL + LeituraSD);
  int httpCode = http.GET();

  if (httpCode < 0) {
    return "";
  }
  if (httpCode != HTTP_CODE_OK) {
    return "";
  }
  String response =  http.getString();
  http.end();

  return response;
}

void initWiFi() {
  
    if (WiFi.status() != WL_CONNECTED) {
    int network = WiFi.scanNetworks();
    Serial.print("disponivel:");
    Serial.println(network);
    Serial.println("no-WIFI");
    digitalWrite(17,HIGH);
    digitalWrite(16,LOW);

      //Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "   OPEN ":"   Password Required");
          
      if(WiFi.SSID(i)= (nome1 || nome2 || nome3 || nome4|| nome5)){
      Serial.println("-----------i: ");
      Serial.println(i);
      
      if(WiFi.SSID(i)==nome1){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  wifi1
      WiFi.begin("Ecosolo", "ecosolo15");
      Serial.print("uma rede compatÃƒÂ­vel:"); 
      Serial.println(WiFi.SSID(i));
      wifiname="RamboDetona";
      delay(10000);
      }
      
      if(WiFi.SSID(i)==nome2){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  wifi1
      WiFi.begin("LAPTOP", "6765Qi22");
      Serial.print("uma rede compatÃƒÂ­vel:"); 
      Serial.println(WiFi.SSID(i));
      wifiname="LAPTOP";
      delay(10000);
      }

      if(WiFi.SSID(i)==nome3){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  wifi1
      WiFi.begin("SERVITEC_SIVP", "RR79BYSIVP");
      Serial.print("uma rede compatÃƒÂ­vel:"); 
      Serial.println(WiFi.SSID(i));
      wifiname="Laboratorio";
      delay(10000);
      }

      if(WiFi.SSID(i)==nome4){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  wifi1
      WiFi.begin("AndroidAP", "brck7528");
      Serial.print("uma rede compatÃƒÂ­vel:"); 
      Serial.println(WiFi.SSID(i));
      wifiname="AndroidAP";
      delay(10000);
      }

      if(WiFi.SSID(i)==nome5){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  wifi1
      WiFi.begin("RamboDetona", "rambo1992");
      Serial.print("uma rede compatÃƒÂ­vel:"); 
      Serial.println(WiFi.SSID(i));
      wifiname="RamboDetona";
      delay(10000);
      }

      if (WiFi.status() != WL_CONNECTED) {
      Serial.println("somando");
      i=i+1;
      }
      if(i>network){
      i=0;
      }
    }
  }else{
  digitalWrite(17,LOW);
  digitalWrite(16,HIGH);
  }
}


void satelite(){
    while (SerialGPS.available()) {
    if (GPS.encode(SerialGPS.read())) {
        GPS.f_get_position(&latitude, &longitude);
        alt = GPS.f_altitude();
        vel = GPS.f_speed_kmph();
        latitudeS=String(latitude,5);
        longitudeS=String(longitude,5);
    }
 }
}
void concatenador(){
dados=("ID:"+(String)systemID+"|"+(String)dia +"|D:"+(String)data +"|H:"+(String)hora+"|La:"+String(latitudeS)+"|Lo:"+String(longitudeS)+"|V:"+String(vel)+"|A:"+String(alt)+"|T:"+String(bufferTank)+"[_]"); 
}
void relogio(){
  DateTime now = rtc.now(); //chama a funÃƒÆ’Ã‚Â§ÃƒÆ’Ã‚Â£o do relÃƒÆ’Ã‚Â³gio
  data=((String)now.day()+"/"+(String)now.month()+"/"+(String)now.year());
  hora=((String)now.hour()+":"+(String)now.minute()+":"+(String)now.second());
  dia=daysOfTheWeek[now.dayOfTheWeek()];
}
void TankLevel(){
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
  Tank=measure.RangeMilliMeter;
  }    
}

//voids SD card
void readFile(fs::FS &fs, const char * path){
  File file = SD.open(path);
  if(!file){
  Serial.println("erro de upload");
  }
  if( contUP==50){
  contUP=0;
  }
  while(file.available()){
  Serial.println("up33");
  LeituraSD=file.readString();
  Serial.println(LeituraSD);
  httpRequest(file.readString());
  file.close();
  }  
}

void appendFile(fs::FS &fs, const char * path, const char * message){
  File file = SD.open(path, FILE_APPEND);
  if(!file){
  Serial.println("eeo ds");
  return;
  }
  //if(file.print(message)){
  if(file.print(message)){
  Serial.print("contadorDesalvamento:");
  Serial.print(contadorDesalvamento);
  Serial.println();
  Serial.print("StringSalvamento:");
  Serial.print(StringSalvamento);
  Serial.println();
  Serial.print("arquivoSemanal2:");
  Serial.print(arquivoSemanal2);
  Serial.println();
  contadorDesalvamento=contadorDesalvamento+1;
  gerador_de_arquivo();
  DateTime now = rtc.now();
    if(now.hour()==23 && now.minute()==59){
    contadorDesalvamento=0;
    StringSalvamento=0;
    }
      if(contadorDesalvamento==80){
      contadorDesalvamento=0;
      StringSalvamento=StringSalvamento+1;  
      }
    }

  file.close();
}
void gerador_de_arquivo(){
arquivoSemanal="/"+(String)dia+(String)StringSalvamento+".txt";
arquivoSemanal2 =arquivoSemanal.c_str();
}
void upLoad(){
arquivoUp="/"+(String)dia+(String)contUP+".txt";
arquivoUp1=arquivoUp.c_str();
readFile(SD,arquivoUp1);
Serial.println(arquivoUp1);
contUP=contUP+1; 
}

