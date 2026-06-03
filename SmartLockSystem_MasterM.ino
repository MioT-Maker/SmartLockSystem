#include "arduino_secrets.h"

#include <SPI.h>
#include <MFRC522.h>
#include <DHT.h>
#include <Servo.h>
#include <IskakINO_LiquidCrystal_I2C.h>
#include "thingProperties.h"

// DHT11
#define DHT_PIN 2
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// Servo
#define SERVO_PIN 6
Servo myServo;

// RC522
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

// LCD
LiquidCrystal_I2C lcd(16, 2);

// Timer
unsigned long previousMillis = 0;
const unsigned long interval = 5000;

// Door open timer
unsigned long doorOpenMillis = 0;
const unsigned long doorOpenTime = 5000;

// íì©ë ì¹´ë UUID
String VALID_CARD_UUID = "B9 E1 E2 B9";

// Door ìí
bool doorOpen = false;

// LCD íìì© ìí
bool doorDisplayState = false;

void setup() {
  Serial.begin(9600);
  delay(1500);

  // Arduino IoT Cloud
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // DHT11 begin
  dht.begin();

  // Servo begin
  myServo.attach(SERVO_PIN);
  myServo.write(0);

  DoorOpen = false;

  // RC522 begin
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("ì¹´ë ìë ¥ ëê¸°");

  // LCD begin
  lcd.begin();
  lcd.backlight();

  printDefaultLCD();
}

void loop() {
  ArduinoCloud.update();

  unsigned long currentMillis = millis();

  // ë¬¸ì´ ì´ë¦° ìíë¼ë©´ 5ì´ í ë«ê¸°
  if (doorOpen == true) {
    if (currentMillis - doorOpenMillis >= doorOpenTime) {
      closeDoor();
    }
    return;
  }

  // 5ì´ë§ë¤ ì¤í
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    readDHT11();
    readRFIDOnce();
  }
}

void readDHT11() {
  float humidity = dht.readHumidity();
  float temperatureC = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  DeviceTemperature = temperatureC;
}

void readRFIDOnce() {
  Serial.println("RFID Check");

  if (!rfid.PICC_IsNewCardPresent()) {
    Serial.println("No RFID card");
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    Serial.println("RFID read failed");
    return;
  }

  String readUuid = "";

  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) {
      readUuid += "0";
    }

    readUuid += String(rfid.uid.uidByte[i], HEX);

    if (i < rfid.uid.size - 1) {
      readUuid += " ";
    }
  }

  readUuid.toUpperCase();

  Serial.print("Card UID: ");
  Serial.println(readUuid);

  CardUUID = readUuid;

  if (readUuid == VALID_CARD_UUID) {
    openDoor();
  } 
  else {
    Serial.println("Invalid Card");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

void openDoor() {
  doorOpen = true;
  doorOpenMillis = millis();

  doorDisplayState = true;
  DoorOpen = true;
  myServo.write(180);

  Serial.println("Door Open");

  printDefaultLCD();
}

void closeDoor() {
  doorOpen = false;

  doorDisplayState = false;
  DoorOpen = false;
  myServo.write(0);

  Serial.println("Door Close");

  printDefaultLCD();

  previousMillis = millis();
}

void printDefaultLCD() {
  lcd.clear();
  delay(10);

  lcd.setCursor(0, 0);
  lcd.print("Smart Lock Sys.");

  lcd.setCursor(0, 1);

  if (doorDisplayState == true) {
    lcd.print("Door Open");
  } 
  else {
    lcd.print("Door Close");
  }

  Serial.print("LCD Door State: ");
  Serial.println(doorDisplayState ? "Open" : "Close");
}

/*
  Cloudìì CardUUID ë³ê²½ ì
*/
void onCardUUIDChange() {
  Serial.print("CardUUID changed from Cloud: ");
  Serial.println(CardUUID);

  VALID_CARD_UUID = CardUUID;
}

/*
  Cloudìì DoorOpen ë³ê²½ ì
*/
void onDoorOpenChange() {
  if (DoorOpen == true) {
    doorOpen = true;
    doorDisplayState = true;
    doorOpenMillis = millis();
    myServo.write(180);
  } 
  else {
    doorOpen = false;
    doorDisplayState = false;
    myServo.write(0);
  }

  Serial.print("Door State changed from Cloud: ");
  Serial.println(DoorOpen ? "Open" : "Close");
}
