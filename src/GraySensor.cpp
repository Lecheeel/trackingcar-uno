#include<Arduino.h>
class GraySensor {
public:
    GraySensor(int clkPin, int datPin) : clkPin(clkPin), datPin(datPin) {
        pinMode(clkPin, OUTPUT); //设置时钟为输出
        pinMode(datPin, INPUT_PULLUP); //设置数据为输入
        digitalWrite(clkPin, 0);
    }

    int* getGrayValues() {
        static int grayValues[8];
        unsigned char sensor_status = gw_gray_serial_read_simple();
        for (int i = 0; i < 8; ++i) {
            grayValues[i] = ~((sensor_status >> i) & 0x1) & 0x1;
        }
        return grayValues;
    }

private:
    int clkPin;
    int datPin;

    void gray_gpio_clk_high() {
        digitalWrite(clkPin, 1);
    }

    void gray_gpio_clk_low() {
        digitalWrite(clkPin, 0);
    }

    unsigned char gw_gray_serial_read_simple() {
        unsigned char ret = 0;
        for (int i = 0; i < 8; ++i) {
            ret <<= 1;
            gray_gpio_clk_high();
            ret |= digitalRead(datPin);
            gray_gpio_clk_low();
            delayMicroseconds(1);
        }
        return ret;
    }
};