const int
    led_r = A2,
    led_g = A1, led_b = A0,
    led_rfid_r = A15, led_rfid_g = A14, led_rfid_b = A13,
    dhtpin = A7, lightpin = A6,
    fanpin = 37, servopin = 3;
#define OPEN_DEGREE 150
#define CLOSE_DEGREE 0
LiquidCrystal lcd_rfid(23, 25, 27, 29, 31, 33); // gnd vcc x 32 gnd 30 x x x x 28 26 24 22 x x
LiquidCrystal lcd_1(22, 24, 26, 28, 30, 32);

Servo myservo;
DHT dht(dhtpin, DHT11);
DynamicJsonDocument doc(1024);
SoftwareSerial mySerial(10, 11);    // RX, TX
Adafruit_PN532 nfc(39, 41, 43, 45); // SCK MISO MOSI SS
