#include <Arduino.h>
#line 1 "D:\\Users\\Daniel_Data\\CodeProjects\\AquariumNightLight\\AquariumNightLight.ino"
#include <RTClib.h>
#include <Adafruit_DotStar.h>

#define NUMPIXELS   20

#define DATAPIN     4
#define CLOCKPIN    5
Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN);
RTC_DS3231 rtc;

int brightness = 0;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
unsigned long currentMillis = 0;
unsigned long lastMillis = 0;
int switchOnHour = 18;
int switchOnMinute = 1;
int switchOffHour = 23;
int switchOffMinute = 59;
const int MAX_BRIGHTNESS = 150; //50 was way too dim


#line 22 "D:\\Users\\Daniel_Data\\CodeProjects\\AquariumNightLight\\AquariumNightLight.ino"
void setup();
#line 48 "D:\\Users\\Daniel_Data\\CodeProjects\\AquariumNightLight\\AquariumNightLight.ino"
void loop();
#line 22 "D:\\Users\\Daniel_Data\\CodeProjects\\AquariumNightLight\\AquariumNightLight.ino"
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
  
    // Serial.print(now.year(), DEC);
    // Serial.print('/');
    // Serial.print(now.month(), DEC);
    // Serial.print('/');
    // Serial.print(now.day(), DEC);
    // Serial.print(" (");
    // Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    // Serial.print(") ");
    // Serial.print(now.hour(), DEC);
    // Serial.print(':');
    // Serial.print(now.minute(), DEC);
    // Serial.print(':');
    // Serial.print(now.second(), DEC);
    // Serial.println();

    // Serial.print(" since midnight 1/1/1970 = ");
    // Serial.print(now.unixtime());
    // Serial.print("s = ");
    // Serial.print(now.unixtime() / 86400L);
    // Serial.println("d");

    // // calculate a date which is 7 days, 12 hours, 30 minutes, 6 seconds into the future
    // DateTime future (now + TimeSpan(7,12,30,6));

    // Serial.print(" now + 7d + 12h + 30m + 6s: ");
    // Serial.print(future.year(), DEC);
    // Serial.print('/');
    // Serial.print(future.month(), DEC);
    // Serial.print('/');
    // Serial.print(future.day(), DEC);
    // Serial.print(' ');
    // Serial.print(future.hour(), DEC);
    // Serial.print(':');
    // Serial.print(future.minute(), DEC);
    // Serial.print(':');
    // Serial.print(future.second(), DEC);
    // Serial.println();

    // Serial.print("Temperature: ");
    // Serial.print(rtc.getTemperature());
    // Serial.println(" C");

    // Serial.println();
    // delay(3000);


  
}

