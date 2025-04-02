#include "FT6336U.h"

FT6336U::FT6336U(uint8_t sda_pin, uint8_t scl_pin) {
    _sdaPin = sda_pin;
    _sclPin = scl_pin;
}

bool FT6336U::begin() {
    Wire.begin(_sdaPin, _sclPin, (uint32_t) 400E3);
    Wire.beginTransmission(FT6336U_I2C_ADDR);
    return (Wire.endTransmission() == 0);
}

uint8_t FT6336U::getNumTouches() {
    Wire.beginTransmission(FT6336U_I2C_ADDR);
    Wire.write(FT6336U_REG_NUM_TOUCHES);
    Wire.endTransmission();
    Wire.requestFrom(FT6336U_I2C_ADDR, 1);
    return Wire.read();
}

bool FT6336U::getTouchCoordinates(uint16_t &x, uint16_t &y) {
    Wire.beginTransmission(FT6336U_I2C_ADDR);
    Wire.write(FT6336U_REG_TOUCH1_XH);
    Wire.endTransmission();
    Wire.requestFrom(FT6336U_I2C_ADDR, 4);
    
    if (Wire.available() == 4) {
        x = (Wire.read() & 0x0F) << 8;
        x |= Wire.read();
        y = (Wire.read() & 0x0F) << 8;
        y |= Wire.read();
        return true;
    }
    return false;
}

void FT6336U::calibrateScreen() {
    Serial.println("Touch the top-left corner");
    while (getNumTouches() == 0);
    while (getNumTouches() > 0) {
        getTouchCoordinates(rawTouchX[0], rawTouchY[0]);
    }
    delay(500);

    Serial.println("Touch the bottom-right corner");
    while (getNumTouches() == 0);
    while (getNumTouches() > 0) {
        getTouchCoordinates(rawTouchX[1], rawTouchY[1]);
    }
    delay(500);

    Serial.println("Calibration completed!");
}
