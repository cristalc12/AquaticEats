#include <Wire.h> //library for I2C communication
#include <RTClib.h> //RTC library
#include <Servo.h> //servo libary

//instance of the RTC_DS1307 class
RTC_DS1307 rtc;

//instance of the Servo class
Servo myServo;

//pin number Servo is connected to
int servoPin = 8;

int firstFeedingHour = 10;
int firstFeedingMinute = 30;

int secondFeedingHour = 17;
int secondFeedingMinute = 49;

void setup() { 
  
  myServo.attach(servoPin);
  myServo.write(0);

  // initializing serial communication
  Serial.begin(9600);

 // check if RTC is present
  if (!rtc.begin()) {
    Serial.println("DS1307 RTC Module not Present");
    while (1);
  }


 
}

void loop() {
 
  DateTime time = rtc.now();

  //continuously printing time and date with a delay of 1 second

  Serial.print("Time: ");
  Serial.print(time.hour(), DEC);
  Serial.print(":");
  Serial.print(time.minute(), DEC);
  Serial.print(":");
  Serial.print(time.second(), DEC);

  Serial.print("  ");

  Serial.print("Date: ");
  Serial.print(time.day());
  Serial.print("/");
  Serial.print(time.month());
  Serial.print("/");
  Serial.println(time.year());

  delay(1000);

  //calls the feedingTime function to check if current time is equal to the set feeding values
 if (feedingTime(time)) {
    if (feed()) {
      Serial.println("Feeding completed.");
    } else {
      Serial.println("Error during feeding.");
    }
  }
}

//feeding time function takes a DateTime object to represent the current time
boolean feedingTime(DateTime time) {
   return ((time.hour() == firstFeedingHour && time.minute() == firstFeedingMinute) || (time.hour() == secondFeedingHour && time.minute() == secondFeedingMinute));
  
}


boolean feed() {

  myServo.write(45);
  delay(2000); 
  myServo.write(90);
  delay(2000); 
  myServo.write(145);
  delay(2000); 
  myServo.write(180);
  delay(2000); 
  myServo.write(90);
  delay(2000); 
  myServo.write(0);


  return true;
}
