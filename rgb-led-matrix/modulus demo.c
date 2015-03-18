#include <stdio.h>
#include <wiringPi.h>
#include <sr595.h>


#define FULL { \
	{1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1}  \
}
#define Smile { \
	{0, 0, 1, 1, 1, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {1, 0, 1, 0, 0, 1, 0, 1}, \
    {1, 0, 0, 0, 0, 0, 0, 1}, \
    {1, 0, 1, 0, 0, 1, 0, 1}, \
    {1, 0, 0, 1, 1, 0, 0, 1}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 0, 1, 1, 1, 1, 0, 0}  \
}
#define Heart { \
    {0, 1, 0, 0, 0, 1, 0, 0},  \
    {1, 0, 1, 0, 1, 0, 1, 0},  \
    {1, 0, 0, 1, 0, 0, 1, 0},  \
    {1, 0, 0, 0, 0, 0, 1, 0},  \
    {0, 1, 0, 0, 0, 1, 0, 0},  \
    {0, 0, 1, 0, 1, 0, 0, 0},  \
    {0, 0, 0, 1, 0, 0, 0, 0},  \
    {0, 0, 0, 0, 0, 0, 0, 0},  \
}
#define Heart_small { \
    {0, 0, 0, 0, 0, 0, 0, 0},  \
    {0, 0, 1, 0, 1, 0, 0, 0},  \
    {0, 1, 0, 1, 0, 1, 0, 0},  \
    {0, 1, 0, 0, 0, 1, 0, 0},  \
    {0, 0, 1, 0, 1, 0, 0, 0},  \
    {0, 0, 0, 1, 0, 0, 0, 0},  \
    {0, 0, 0, 0, 0, 0, 0, 0},  \
    {0, 0, 0, 0, 0, 0, 0, 0},  \
}

int RowRed[8]={116,117,118,119,120,121,122,123};
int RowGreen[8]={108,109,110,111,112,113,114,115};
int RowBlue[8]={100,101,102,103,104,105,106,107};
int Column[8]={124,125,126,127,128,129,130,131};


void MatrixSetup()
{
	int j;
	for(j = 0; j < 32; j++)
    {
        pinMode(100 + j, OUTPUT);
    }
    for(j = 0; j < 8; j++)
    {
        digitalWrite(100 + j, 1);
    }
    for(j = 0; j < 8; j++)
    {
        digitalWrite(116 + j, 1);
    }
    for(j = 0; j < 8; j++)
    {
        digitalWrite(108 + j, 1);
    }
}
void Clear()
{
    int i;
    for(i=0;i<8;i++)
    {
        digitalWrite(RowRed[i],1);
        digitalWrite(RowGreen[i],1);
        digitalWrite(RowBlue[i],1);
        digitalWrite(Column[i],0);
    }


}
void WriteRed(int number)
{
    digitalWrite(RowRed[number],0);
    digitalWrite(RowRed[number],1);
}
void WriteGreen(int number)
{
    digitalWrite(RowGreen[number],0);
    digitalWrite(RowGreen[number],1);
}
void WriteBlue(int number)
{
    digitalWrite(RowBlue[number],0);
    digitalWrite(RowBlue[number],1);
}

void Draw(int matrix[8][8])
{
    int column, row;
    for(int times = 0; times < 30; times++)
    {
        for(column = 0; column < 8; column++)
        {
            digitalWrite(Column[column],1);
            for(row = 0; row < 8; row++)
            {
                    switch(matrix[column][row])
                    {
                        case 1:
                            WriteRed(row);
                            break;
                        case 2:
                            WriteGreen(row);
                            break;
                        case 3:
                            WriteBlue(row);
                            break;
                        default:
                            break;
                    }
            }
            digitalWrite(Column[column],0);
        }
    }
}

int main(int argc, char *argv[])
{
    int column, row, current=0;
    wiringPiSetup();
    sr595Setup(100, 32, 12, 14, 10);
    MatrixSetup();
    int matrix[8][8]= Heart;
    int matrix_small[8][8]= Heart_small;
    while(1)
    {
       if(current == 0)
       {
            Draw(matrix);
            current=1;
       }
       else
       {
            Draw(matrix_small);
            current=0;
       }
    }
}
