#include "mbed.h"   //Compliled using Keil Studio

AnalogIn ir1(p15);  // IR Sensors
AnalogIn ir2(p16);
AnalogIn ir3(p17);
AnalogIn ir4(p18);
AnalogIn ir5(p19);

PwmOut buzzer(p21);

DigitalOut B(p22),A(p23),F(p24),G(p25),E(p26),C(p6),D(p5);  //Segmentes for Single digit display

DigitalOut Digit1(p14); //Digits for 4 digit display
DigitalOut Digit2(p13);
DigitalOut Digit3(p12);
DigitalOut Digit4(p11);

DigitalOut led[8] = {p27, p28, p29, p30, p9, p8, p7, p10};  //Segments for 4 digit display 

int matrix[11][8] = {
    {1, 1, 1, 1, 1, 1, 0, 0}, // Zero
    {0, 1, 1, 0, 0, 0, 0, 0}, // One
    {1, 1, 0, 1, 1, 0, 1, 0}, // Two
    {1, 1, 1, 1, 0, 0, 1, 0}, // Three
    {0, 1, 1, 0, 0, 1, 1, 0}, // Four
    {1, 0, 1, 1, 0, 1, 1, 0}, // Five
    {1, 0, 1, 1, 1, 1, 1, 0}, // Six
    {1, 1, 1, 0, 0, 0, 0, 0}, // Seven
    {1, 1, 1, 1, 1, 1, 1, 0}, // Eight
    {1, 1, 1, 0, 0, 1, 1, 0}, // Nine
    {0, 0, 0, 0, 0, 0, 0, 1} // Dot
    };

void displayDigit(int digit, int number) {
     // Turn off all digits initially
    Digit1 = 1;
    Digit2 = 1;
    Digit3 = 1;
    Digit4 = 1;

    // Activate the selected digit
    switch (digit) {

 case 1:
 Digit1 = 0;
 break;

 case 2:
 Digit2 = 0;
 break;

 case 3:
 Digit3 = 0;
 break;

 case 4:
 Digit4 = 0;
 break;

 }

 // Display the number on the selected digit
 for (int i = 0; i < 8; i++) {
 led[i] = matrix[number][i];
 }
 wait_us(1000); // Adjust this delay based on your display's specifications
}

enum BuzzerState {
 BUZZER_OFF,
 PLAY_NOTE_1,
 PLAY_NOTE_2,
 PLAY_NOTE_3,
 PLAY_NOTE_4
};

BuzzerState buzzerState = BUZZER_OFF;

void playBuzzerTune () {
 switch (buzzerState) {
 case BUZZER_OFF:
 buzzer.write(0);
 wait_us(10000); // Small delay
 buzzerState = PLAY_NOTE_1;
 break;

 case PLAY_NOTE_1:
 buzzer.period(1.0 / 261.63);
 buzzer.write(0.5);
 wait_us(100000); // Adjust this duration
 buzzer.write(0);
 buzzerState = PLAY_NOTE_2;
 break;

 case PLAY_NOTE_2:
 buzzer.period(1.0 / 293.66);
 buzzer.write(0.5);
 wait_us(100000); // Adjust this duration
 buzzer.write(0);
 buzzerState = PLAY_NOTE_3;
 break;

 case PLAY_NOTE_3:
 buzzer.period(1.0 / 329.63);
 buzzer.write(0.5);
 wait_us(100000); // Adjust this duration
 buzzer.write(0);
 buzzerState = PLAY_NOTE_4;
 break;

 case PLAY_NOTE_4:
 buzzer.period(1.0 / 329.0);
 buzzer.write(0.5);
 wait_us(100000); // Adjust this duration
 buzzer.write(0);
 buzzerState = BUZZER_OFF;
 break;

 }
}

int main() { 

 int totalScore = 0;
 int totalmoves = 0;

while(1){

 if (totalmoves >= 6) {
 totalmoves = 0;
 totalScore = 0;
 }
 switch (totalmoves) {
 case 0: 
 G=1, F=0, A=0, B=0, E=0, D=0, C=0; // display 0
 break;

 case 1: 
 G=1, F=1, A=1, B=0, E=1, D=1, C=0; // display 1 
 break;

 case 2:
 G=0, F=1, A=0, B=0, E=0, D=0, C=1; // display 2
 break;

 case 3:
 G=0, F=1, A=0, B=0, E=1, D=0, C=0; // display 3
 break;

 case 4:
 G=0, F=0, A=1, B=0, E=1, D=1, C=0; // display 4
 break;

 case 5:
 G=0, F=0, A=0, B=1, E=1, D=0, C=0; // display 5
 break; 

 }
 displayDigit(3, totalScore % 10); // Display the last digit
 displayDigit(2, (totalScore / 10) % 10); // Display the tens digit
 displayDigit(1, (totalScore / 100) % 10); // Display the hundreds digit
 
 if (ir1.read() < 0.1) {
 playBuzzerTune();
 totalScore += 50;
 totalmoves++;
 }
 else if (ir2.read() < 0.1) {
 playBuzzerTune();
 totalScore += 15;
 totalmoves++;
 }
 else if (ir3.read() < 0.1) {
 playBuzzerTune();
 totalScore += 10;
 totalmoves++;
 }
 else if (ir4.read() < 0.1) {
 playBuzzerTune();
 totalScore += 15;
 totalmoves++;
 }


 else if (ir5.read() < 0.2) {
 playBuzzerTune();
 totalScore += 25;
 totalmoves++;
 } 
 wait_us(1000);
 }
 
}
