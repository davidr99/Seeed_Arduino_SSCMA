#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Seeed_Arduino_SSCMA.h>

SSCMA AI;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    while (!Serial)
        delay(1000);
    SPI.begin(SCK, MOSI, MISO, -1);
    AI.begin(&SPI, D1, D0);

    Serial.println("Proxy start");
}

char buf[32768];
void loop()
{
    int s_len = Serial.available();
    if (s_len)
    {
        int len = Serial.readBytes((char *)buf, s_len);
        AI.write(buf, len);
    }
    memset(buf, 0x00, s_len);
    int t_len = AI.available();
    if (t_len)
    {
        if (t_len > sizeof(buf)) {
            t_len = sizeof(buf);
        }
        AI.read(buf, t_len);
        // Serial.write(buf, t_len);
        Serial.write(buf, 80);
        Serial.flush();
    }
}
