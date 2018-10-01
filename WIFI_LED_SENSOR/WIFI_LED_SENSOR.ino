#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <dht11.h>
#include <M5Stack.h>
dht11 DHT11;

#define DHT11PIN 27

const char* ssid     = "coral";
const char* password = "12345678";

Adafruit_ST7735 tft = Adafruit_ST7735(16, 17, 23, 5, 9); // CS,A0,SDA,SCK,RESET
float r, x1, ya, z1, x2, y2, z2, x3, y3, z3;               //
int f[8][2], x, y;                                         // Draw box, x, y center
int c[8][3] = {                                            // Cube
 {-20,-20, 20},{20,-20, 20},{20,20, 20},{-20,20, 20},
 {-20,-20,-20},{20,-20,-20},{20,20,-20},{-20,20,-20} };

WiFiServer server(80);

void setup() {
  
   tft.initR(INITR_18GREENTAB);                             // 1.44 v2.1
  tft.fillScreen(ST7735_BLACK);                            // CLEAR
  tft.setTextColor(0x5FCC);                                // GREEN
  //tft.setRotation(1);                                      // 
  x = tft.width() /2; x = x + 14;                          // x Center Calculate
  y = tft.height()/2;                                      // y Center Calculate
  tft.setCursor(5, 5);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextWrap(true);
  
  Serial.begin(115200);
  while(!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  
  
  Serial.println("scan start");
  tft.print("scan start");

  int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        tft.fillScreen(ST7735_BLACK);
            tft.setCursor(5, 5);
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            
            tft.print(i+1);
            Serial.print(i + 1);
             tft.print(" : ");
            Serial.print(": ");
             tft.print(WiFi.SSID(i));
            Serial.print(WiFi.SSID(i));
            tft.print(" (");
            Serial.print(" (");
            tft.print(WiFi.RSSI(i));
            Serial.print(WiFi.RSSI(i));
            tft.print(")");
            Serial.print(")");
            tft.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");
    
    delay(5000);

  // We start by connecting to a WiFi network
  Serial.println();
  tft.println();
  Serial.println();
  tft.println();
  Serial.print("Connecting to ");
  tft.print("Connecting to ");
  Serial.println(ssid);
  tft.println(ssid);
  
  WiFi.begin(ssid, password);// connect
  
  // attempt to connect to Wifi network:
  while(WiFi.status() != WL_CONNECTED) {
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    delay(500);
    Serial.print(".");
    tft.print(".");
  }
  Serial.println("");
  tft.println("");
  Serial.println("WiFi connected");
  tft.println("WiFi connected");
  Serial.println("IP address: ");
  tft.println("IP address: ");
  Serial.println(WiFi.localIP());
  tft.println(WiFi.localIP());
  
  server.begin();
  

}


void loop() {
   
  int a26 = 0;
  a26 = analogRead(26);
  
  int chk = DHT11.read(DHT11PIN);

  //testdrawtext("fuck", ST7735_WHITE,x,y);
  //delay(1000);

  //tft.initR(INITR_18GREENTAB);                             // 1.44 v2.1
  tft.fillScreen(ST7735_BLACK);                            // CLEAR
  //tft.setTextColor(0x5FCC);                                // GREEN
  //tft.setRotation(1);                                      // 
  tft.setCursor(5, 5);
   tft.setTextColor(ST7735_RED);
   tft.setTextWrap(true);
   tft.println(WiFi.localIP());
   //tft.println(WiFi.status());
  tft.setTextColor(ST7735_WHITE);
  tft.setTextWrap(true);
  tft.print("Temperature : ");
  tft.println((float)DHT11.temperature,2);
  tft.print("Humidity : ");
  tft.println((float)DHT11.humidity,2);
  tft.print("sensor : ");
  tft.print(a26);
  /*testdrawtext("Temperature : ", ST7735_WHITE,(float)DHT11.temperature,5);
  testdrawtext("Humidity : ", ST7735_WHITE,(float)DHT11.humidity,10);*/
  delay(1000);

}
