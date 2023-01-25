#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Bridge.h>
#include <BridgeClient.h>
#include <BridgeServer.h>
#include <Process.h>
DynamicJsonDocument doc(1024);
SoftwareSerial mySerial(9, 10); // RX TX
BridgeServer server;
void setup()
{
    digitalWrite(13, LOW);
    Bridge.begin();
    // 啟動後點亮13號LED
    digitalWrite(13, HIGH);
    server.listenOnLocalhost();
    server.begin();
    mySerial.begin(9600);
}
void loop()
{
    BridgeClient client = server.accept();
    if (client)
    {
        process(client);
        client.stop();
    }
    while (mySerial.available() > 0)
    {
        readMega(client);
    }
    myDelay(500);
}

void process(BridgeClient client)
{
    String command = client.readStringUntil('/');
    command.trim();
    if (command == "test")
    {
    }
    else
    {
        String receive = client.readStringUntil('/');
        mySerial.print(command + "/" + receive + "/");
    }
    doc.clear();
}

// 讀取 Arduino Mega 傳回的數據
void readMega(BridgeClient client)
{
    String get = mySerial.readStringUntil('#');
    myDelay(1000);
    if (get.length() == 0)
        return;
    deserializeJson(doc, get);
    if (doc.isNull())
        return;
    String func = doc["func"];
    if (func == "SaveData")
    {
        String humid = doc["humid"];
        String temp = doc["temp"];
        String light = doc["light"];
        storeInBridge(humid, temp, light);
    }
    else if (func == "RFID")
    {
        String uid0 = doc["uid0"];
        String uid1 = doc["uid1"];
        String uid2 = doc["uid2"];
        String uid3 = doc["uid3"];
        String uid = uid0 + "," + uid1 + "," + uid2 + "," + uid3;
        Bridge.put("search", uid);
        Process p;
        p.begin("sh");
        p.addParameter("/mnt/sd/arduino/www/Yun/search.sh");
        p.run();
        String re = p.readStringUntil('#').substring(0, 1);
        if (re.length() != 0)
        {
            mySerial.print("RFID/on/");
        }
        else
        {
            mySerial.print("RFID/off/");
        }
    }
    doc.clear();
}

void storeInBridge(String humid, String temp, String light)
{
    if (humid != "")
        Bridge.put("humid", humid);
    if (temp != "")
        Bridge.put("temp", temp);
    if (light != "")
        Bridge.put("light", light);
}

void myDelay(int time)
{
    unsigned long startTime = millis();
    while (true)
        if (millis() - startTime >= time)
            break;
}
