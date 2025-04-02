#include "FT6336U.h"

FT6336U::FT6336U(uint8_t sda_pin, uint8_t scl_pin) {
    _sdaPin = sda_pin;
    _sclPin = scl_pin;
}

#define I2C_FREQUENCY 400000UL  

bool FT6336U::begin() {
    Wire1.begin(_sdaPin, _sclPin, static_cast<uint32_t>(I2C_FREQUENCY));
    Wire1.beginTransmission(FT6336U_I2C_ADDR);
    return (Wire1.endTransmission() == 0);
}

uint8_t FT6336U::getNumTouches() {
    Wire1.beginTransmission(FT6336U_I2C_ADDR);
    Wire1.write(FT6336U_REG_NUM_TOUCHES);
    Wire1.endTransmission();
    Wire1.requestFrom(FT6336U_I2C_ADDR, 1);
    return Wire1.read();
}

bool FT6336U::getTouchCoordinates(uint16_t &x, uint16_t &y) {
    Wire1.beginTransmission(FT6336U_I2C_ADDR);
    Wire1.write(FT6336U_REG_TOUCH1_XH);
    Wire1.endTransmission();
    Wire1.requestFrom(FT6336U_I2C_ADDR, 4);
    
    if (Wire1.available() == 4) {
        x = (Wire1.read() & 0x0F) << 8;
        x |= Wire1.read();
        y = (Wire1.read() & 0x0F) << 8;
        y |= Wire1.read();
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
