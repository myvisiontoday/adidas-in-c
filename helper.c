#include <stdio.h>
#include <stdint.h>
#include "helper.h"

void splitByteIntoNibbles(uint8_t dataByte, uint8_t nibbles[]){
    uint8_t highNibble = dataByte & 0xF0; // 0xFO -->binary 11110000
    uint8_t lowNibble = dataByte & 0x0F; // 0x0F --> binary 00001111

    nibbles[0]=highNibble;
    lowNibble<<=4;//shift to the front
    nibbles[1]=lowNibble;
}

void addParityBit(uint8_t* nibble){
    /*
    1. Calculate the parity bits. p[0],p[1],p[2]
    2. add parity bit to the nibble
    */
    uint8_t data[4];
    uint8_t parityBits[3];
    printf("received nibble: ");
    for (int i = 0; i < 4; i++)
    {
        uint8_t mask = *nibble;
        mask&=(1 << (7-i));
        data[i]=mask>>(7-i);
        printf("%u",data[i]);
    }
    parityBits[0]=(data[0] + data[1] + data[2])%2 ==0 ? 0 : 1;
    parityBits[1]=(data[0] + data[1] + data[3])%2 ==0 ? 0 : 1;
    parityBits[2]=(data[2] + data[1] + data[3])%2 ==0 ? 0 : 1;

    *nibble >>=1;
    for (int i = 0; i < 3; i++)
    {
        *nibble |= (parityBits[i]<<i);
    }    
    printf("\nparity bits: %u%u%u\n", parityBits[0], parityBits[1], parityBits[2]);

}

void error_correction(uint8_t* input){
    uint8_t data[4];
    uint8_t parityBits[3];

    for (int i = 0; i < 7; i++)
    {
        uint8_t mask = *input;
        mask&=(1 << (i));
        if(i<3){
            parityBits[i] = mask>>i;
        }
        else if (i>=3)
        {
            data[6-i] = mask>>i;
        }
    }

    // for (int i = 0; i < 4; i++)
    // {
    //     printf("Parity:%u",data[i]);
    //     if(i<3){
    //     printf("Data:%u",parityBits[i]);
    //     }
    // }

    /*
     This section is to check which bit is flipped. 
     Also corrects it once detected. 
    */

   // this removes parity bit first and move everything back to the front.
    *input >>=3;
    *input <<=4;

    int circle1 = (parityBits[0] ^ data[0] ^ data[1] ^ data[2]);
    int circle2 = (parityBits[1] ^ data[0] ^ data[1] ^ data[3]);
    int circle3 = (parityBits[2] ^ data[2] ^ data[1] ^ data[3]);
    int circle = circle3  + circle2   + circle1;

    if (circle==0)
    {
        printf("No error during transmission of data.\n");
    }
    else if (circle==1)
    {
        printf("it seems like one of the parity bit is flipped.\n");
    }
    else if(circle==2){

        if((circle1+circle2) ==2){
        //data[0] was flipped.
            *input^=(1<<7);
        }
        else if((circle1+circle3) ==2){
        //data[2] was flipped.
            *input^=(1<<5);
        }
        else{
        //data[3] was flipped.
            *input^=(1<<4);
        }
    }
    //if all cicle has odd value, then common bit of three circle is flipped.
    else if (circle==3){
    //data[1] was flipped.        
        *input^=(1<<6);
    }
}

void mergeNibblesToOneByte(uint8_t nibbles[], uint8_t* data){
    uint8_t tempData = nibbles[0] | (nibbles[1]>>4);
    *data = tempData;
}