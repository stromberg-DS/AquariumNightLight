# 1 "D:\\Users\\Daniel_Data\\CodeProjects\\AquariumNightLight\\AquariumNightLight.ino"
# 2 "D:\\Users\\Daniel_Data\\CodeProjects\\AquariumNightLight\\AquariumNightLight.ino" 2
# 3 "D:\\Users\\Daniel_Data\\CodeProjects\\AquariumNightLight\\AquariumNightLight.ino" 2





Adafruit_DotStar strip(20, 4, 5);
RTC_DS3231 rtc;

int brightness = 0;
int increment = 5;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
unsigned long currentMillis = 0;
unsigned long lastMillis = 0;
int switchOnHour = 20;
int switchOnMinute = 45;
int switchOffHour = 21;
int switchOffMinute = 1;
const int MAX_BRIGHTNESS = 50;


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
    rtc.adjust(DateTime((reinterpret_cast<const __FlashStringHelper *>(
# 40 "D:\\Users\\Daniel_Data\\CodeProjects\\AquariumNightLight\\AquariumNightLight.ino" 3
                       (__extension__({static const char __c[] __attribute__((__progmem__)) = ("Aug  3 2024"); &__c[0];}))
# 40 "D:\\Users\\Daniel_Data\\CodeProjects\\AquariumNightLight\\AquariumNightLight.ino"
                       )), (reinterpret_cast<const __FlashStringHelper *>(
# 40 "D:\\Users\\Daniel_Data\\CodeProjects\\AquariumNightLight\\AquariumNightLight.ino" 3
                                    (__extension__({static const char __c[] __attribute__((__progmem__)) = ("20:34:50"); &__c[0];}))
# 40 "D:\\Users\\Daniel_Data\\CodeProjects\\AquariumNightLight\\AquariumNightLight.ino"
                                    ))));
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
  int increment = MAX_BRIGHTNESS/60;

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

    Serial.print(now.hour(), 10);
    Serial.print(':');
    Serial.print(now.minute(), 10);
    Serial.print(':');
    Serial.print(now.second(), 10);
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
