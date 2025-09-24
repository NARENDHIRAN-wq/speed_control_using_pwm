#include <reg51.h>
#include <stdio.h>

sbit s0 = P1^0;
sbit s1 = P1^1;
sbit s2 = P1^2;
sbit s3 = P1^3;
sbit s4 = P1^4;
sbit s5 = P1^5;

sbit fan = P2^6;

void delay(unsigned int time);

void main() {
    while (1) {
        if (s0 == 0) {
            fan = 1;
            delay(8);
            fan = 0;
            delay(2);
        }

        if (s2 == 0) {
            fan = 1;
            delay(6);
            fan = 0;
            delay(4);
        }

        if (s3 == 0) {
            fan = 1;
            delay(4);
            fan = 0;
            delay(6);
        }

        if (s4 == 0) {
            fan = 1;
            delay(2);
            fan = 0;
            delay(8);
        }

        if (s5 == 0) {
            fan = 1;
        } else {
            fan = 0;
        }
    }
}

void delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++) {
        for (j = 0; j < 113; j++);
    }
}
