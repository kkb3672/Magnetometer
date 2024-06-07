#include <Wire.h>
#define HMC5883L_ADDRESS 0x1E

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(HMC5883L_ADDRESS);
  Wire.write(0x00);//A
  Wire.write(0x18);//for 7.5hz
  
   
  Wire.write(0x01);//B
  Wire.write(0xA0);
 
  Wire.write(0x02);//mode
  Wire.write(0x00);
  Wire.endTransmission();
}

void loop() {
  int16_t x, y, z;
  magm(x, y, z);
  Serial.print("  X: "); Serial.print(x);
  Serial.print("  Y: "); Serial.print(y);
  Serial.print("  Z: "); Serial.println(z);
}

void magm(int16_t &x, int16_t &y, int16_t &z) {
  Wire.beginTransmission(HMC5883L_ADDRESS);
  Wire.write(0x03);
  Wire.endTransmission();
  Wire.requestFrom(HMC5883L_ADDRESS, 6);
  if (Wire.available() == 6) {
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
  }
}
