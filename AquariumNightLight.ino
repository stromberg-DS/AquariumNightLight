#include <RTClib.h>
#include <Adafruit_DotStar.h>

#define NUMPIXELS   20

#define DATAPIN     4
#define CLOCKPIN    5
Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN);
RTC_DS3231 rtc;

int brightness = 0;
unsigned long currentMillis = 0;
unsigned long lastMillis = 0;
int switchOnHour = 17;
int switchOnMinute = 30;
int switchOffHour = 20;
int switchOffMinute = 30;
const int MAX_BRIGHTNESS = 150; //150 seems good


void setup()
{
    Serial.begin(57600);
	  strip.begin();
    strip.clear();
    strip.show();

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}



void loop() {
  currentMillis = millis();
  DateTime now = rtc.now();
  DateTime onTime = DateTime(now.year(), now.month(), now.day(), switchOnHour, switchOnMinute, 0);

  int currentSecond = now.second();
  int currentMinute = now.minute();
  int currentHour = now.hour();
  bool isHourRight = ((now.hour()>=switchOnHour)&&(now.hour()<=switchOffHour));
  bool isMinRight = ((now.minute()>=switchOnMinute)&&(now.minute()<switchOffMinute));
  int increment = 3;

  if(currentMillis - lastMillis > 1000){
    if(isHourRight && isMinRight){
      if(brightness<MAX_BRIGHTNESS){
        brightness += increment;
      }
      // brightness = 50;
    }else{
      if(brightness>0){
        brightness -= increment;
      }
      // brightness = 0;
    }

    Serial.print("brightness: ");
    Serial.println(brightness);

    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    Serial.print("currentSecond: ");
    Serial.println(now.second());
    Serial.println();

    lastMillis = currentMillis;
  }

  // for(int i=0; i<NUMPIXELS; i++){
  //   strip.setPixelColor(i, brightness);
  // }

  strip.setPixelColor(0, brightness);
  strip.show();                    
  
}
