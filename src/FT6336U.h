
#ifndef FT6336U_H
#define FT6336U_H

#include <Arduino.h>
#include <Wire.h>

/* สำหรับจอที่ใช้ชิปทัช FT6336U */
class FT6336U
{
public:
    FT6336U(uint8_t sda_pin, uint8_t scl_pin );
    bool begin();
    uint8_t getNumTouches();
    bool getTouchCoordinates(uint16_t &x, uint16_t &y);
    void calibrateScreen();

    // Calibration data
    uint16_t calX[2] = {0, 479};
    uint16_t calY[2] = {0, 319};
    uint16_t rawTouchX[2] = {0, 0};
    uint16_t rawTouchY[2] = {0, 0};

private:
    static const uint8_t FT6336U_I2C_ADDR = 0x38;
    static const uint8_t FT6336U_REG_NUM_TOUCHES = 0x02;
    static const uint8_t FT6336U_REG_TOUCH1_XH = 0x03;
    static const uint8_t FT6336U_REG_TOUCH1_XL = 0x04;
    static const uint8_t FT6336U_REG_TOUCH1_YH = 0x05;
    static const uint8_t FT6336U_REG_TOUCH1_YL = 0x06;
};

#endif
