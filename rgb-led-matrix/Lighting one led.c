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
        digitalWrite(100 + j, 1);
    }
	for(j = 0; j < 8; j++)
    {
        digitalWrite(116 + j, 0);
    }
 
    if(argc < 3)
    {
        printf("Summary:lunch -[rgb] x_point y_point \n");
        printf("Example:lunch -r 0 5 \nDraw Red Point At X=0 Y=5 \n");
    }
 
    if(argc > 1 && strcmp(argv[1], "-b") == 0)
    {
        digitalWrite(atoll(argv[2]) + 100, 0);
    }
    if(argc > 1 && strcmp(argv[1], "-g") == 0)
    {
        digitalWrite(atoll(argv[2]) + 108, 0);
    }
    if(argc > 1 && strcmp(argv[1], "-r") == 0)
    {
        digitalWrite(atoll(argv[2]) + 116, 0);
    }
 
    digitalWrite(124 + atoll(argv[3]), 1);
}