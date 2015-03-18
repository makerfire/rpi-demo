#include <stdio.h>
#include <wiringPi.h>
#include <sr595.h>
 
int main(int argc, char *argv[])
{
    int j;
    wiringPiSetup();
    sr595Setup(100, 32, 12, 14, 10);
    for(j = 0; j < 32; j++)
    {
        pinMode(100 + j, OUTPUT);
    }
    for(j = 0; j < 24; j++)
    {
        digitalWrite(100 + j, 0);
    }
	for(j = 0; j < 8; j++)
    {
        digitalWrite(116 + j, 1);
    }
}