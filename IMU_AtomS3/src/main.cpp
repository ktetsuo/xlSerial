
#include <Arduino.h>
#include <M5Unified.h>

void setup()
{
  auto cfg = M5.config();
  M5.begin(cfg);
  Serial.begin(115200);
  if (!M5.Imu.begin())
  {
    while (1)
    {
      Serial.println("IMU Init Failed!");
      delay(1000);
    }
  }
  M5.Lcd.fillScreen(TFT_BLUE);
}

void loop()
{
  static bool _output = false;
  M5.update();
  if (M5.BtnA.wasPressed())
  {
    _output = !_output;
    M5.Lcd.fillScreen(_output ? TFT_GREEN : TFT_BLUE);
  }
  if (_output)
  {
    float accX, accY, accZ;
    if (M5.Imu.getAccel(&accX, &accY, &accZ))
    {
      Serial.print(accX, 3);
      Serial.print(",");
      Serial.print(accY, 3);
      Serial.print(",");
      Serial.println(accZ, 3);
    }
    delay(10); // 10msごと
  }
  // Serial echo back
  const int c = Serial.read();
  if (c != -1)
  {
    Serial.write(c);
  }
}
