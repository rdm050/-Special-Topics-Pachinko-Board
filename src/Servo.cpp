#include "mbed.h"   //Compliled using Keil Studio

PwmOut servo1(p22);
PwmOut servo5(p23);
PwmOut servo2(p24);
PwmOut servo3(p25);
PwmOut servo4(p26);
PwmOut servo6(p21);

void spinblock(int pulsewidth) {

    servo1.pulsewidth_us(pulsewidth);
    servo2.pulsewidth_us(pulsewidth);
    servo3.pulsewidth_us(pulsewidth);
    servo4.pulsewidth_us(pulsewidth);
    servo5.pulsewidth_us(pulsewidth);
    servo6.pulsewidth_us(pulsewidth);

}

int main() {
 
    servo1.period_ms(20);
    servo2.period_ms(20);
    servo3.period_ms(20);
    servo4.period_ms(20);
    servo5.period_ms(20);
    servo6.period_ms(20);
 
    int pulsewidth = 500;
    Ticker spinBlockTicker;
 
    spinBlockTicker.attach([&pulsewidth]() {
    if (pulsewidth >= 2500) {
    pulsewidth = 500;
    } 
    spinblock(pulsewidth); 
    pulsewidth += 180;
    }, 1.0);
    while (1) {
 
 }
}