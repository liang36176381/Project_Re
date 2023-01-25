#include <LiquidCrystal.h>
#include <Wire.h>
#include <Servo.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include "dePin.h"
int humid = 0, temperature = 0, light = 0;
uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0};
uint8_t uidLength;
void setLed(String color)
{
    if (color == "all")
    {
        digitalWrite(led_r, HIGH);
        digitalWrite(led_g, HIGH);
        digitalWrite(led_b, HIGH);
    }
    else
    {
        digitalWrite(led_r, color == "red" ? HIGH : LOW);
        digitalWrite(led_g, color == "green" ? HIGH : LOW);
        digitalWrite(led_b, color == "blue" ? HIGH : LOW);
    }
}

void setFan(String state)
{
    digitalWrite(fanpin, state == "on" ? HIGH : LOW);
}

void setDoor(String state)
{
    myservo.attach(servopin);
    myDelay(300);
    myservo.write(state == "on" ? OPEN_DEGREE : CLOSE_DEGREE);
    if (state == "on")
    {
        myDelay(1000 * 2);
        myservo.write(CLOSE_DEGREE);
    }
    myDelay(300);
    myservo.detach();
}

void setRfid(String state)
{
    lcd_rfid.setCursor(0, 0);
    lcd_rfid.print(state == "on" ? "Success" : "Error");
    digitalWrite(led_rfid_g, state == "on" ? HIGH : LOW);
    digitalWrite(led_rfid_r, state == "off" ? HIGH : LOW);
    setDoor(state);
    myDelay(500);
    digitalWrite(led_rfid_r, LOW);
    digitalWrite(led_rfid_g, LOW);
}
void serialRead()
{
    if (mySerial.available() > 0)
    {
        String s = mySerial.readStringUntil('/');
        String value = mySerial.readStringUntil('/');
        if (s == "LED")
            setLed(value);
        else if (s == "Fan")
            setFan(value);
        else if (s == "Door")
            setDoor(value);
        else if (s == "RFID")
            setRfid(value);
    }
}
void sendJson(String func)
{
    doc["func"] = func;
    serializeJson(doc, mySerial);
    mySerial.print('#');
    doc.clear();
}
void senserRead()
{
    humid = dht.readHumidity();
    temperature = dht.readTemperature();
    light = map((0.3 * light + 0.7 * analogRead(lightpin)), 0, 1023, 0, 255);
    doc["humid"] = humid;
    doc["temp"] = temperature;
    doc["light"] = light;
    sendJson("SaveData");
}
void rfidRead()
{
    bool rfid_success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength, 1000);
    lcd_rfid.clear();
    if (rfid_success)
    {
        lcd_rfid.setCursor(16, 0);
        String uidStr = "";
        String uiS[4];
        for (int i = 0; i < 4; i++)
        {
            String temp;
            temp = String(uid[i], HEX);
            if (temp.length() < 2)
            {
                temp = "0" + temp;
            }
            temp.toUpperCase();
            uiS[i] = temp;
            uidStr += temp + " ";
        }
        lcd_rfid.print(uidStr);
        doc["uid0"] = uiS[0];
        doc["uid1"] = uiS[1];
        doc["uid2"] = uiS[2];
        doc["uid3"] = uiS[3];
        sendJson("RFID");
    }
}
void lcdUpdate()
{
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    String first = "h:" + String(humid) + " t:" + String(temperature) + " l:" + String(light);
    lcd_1.print(first);
    // lcd_1.setCursor(16, 0);
    // time_t sec = now();
    // lcd_1.print(String(sec));
}
void myDelay(int time)
{
    unsigned long startTime = millis();
    while (true)
        if (millis() - startTime >= time)
            break;
}
void setup()
{
    lcd_1.begin(16, 2);
    lcd_rfid.begin(16, 2);
    pinMode(led_r, OUTPUT);
    pinMode(led_g, OUTPUT);
    pinMode(led_b, OUTPUT);
    pinMode(led_rfid_r, OUTPUT);
    pinMode(led_rfid_g, OUTPUT);
    pinMode(led_rfid_b, OUTPUT);
    pinMode(fanpin, OUTPUT);
    pinMode(dhtpin, INPUT);
    pinMode(lightpin, INPUT);
    pinMode(servopin, OUTPUT);
    nfc.begin();
    nfc.setPassiveActivationRetries(0xFF);
    nfc.SAMConfig();
    dht.begin();
    mySerial.begin(9600);
}

void loop()
{
    rfidRead();
    myDelay(500);
    serialRead();
    senserRead();
    lcdUpdate();
    myDelay(1000);
}
