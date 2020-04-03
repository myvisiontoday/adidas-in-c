#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <time.h>
#include "helper.h"


// argc: argumennt count | argv[]: arguments
int main (int argc, char *argv[]){
    /*
    argc should be 3.
    argv[0] = ./encode
    argv[1] = inputfile
    argv[2] = outputfile
    */
    if(argc == 3){
        printf("This program was called with arguments: %s %s\n",argv[1],argv[2]);
    }
    else
    {
        printf("Error, This program should be called with two additional arguments");
        return -1;
    }

     FILE *fp_read; 
     FILE *fp_write; 
     uint8_t data;
     uint8_t nibbles[2];

     // Open for reading in binary mode. if the file doesnot exits it returns NULL.
     fp_read = fopen(argv[1], "rb");

     // Open for reading in binary mode. if the file doesnot exits it returns NULL.
     fp_write = fopen(argv[2], "wb");

    if(fp_read==NULL && fp_write==NULL){
         printf("error opening the file.\n");
         return 1;
     }

    int read = fread(&data, 1, 1, fp_read);
    bool is_empty = 1;
    while(read > 0){
        printf("Read data byte: %u\n", data);
        //call function to detect the flipped bit and remove parity bit.
        error_correction(&data);

        if(is_empty){
            nibbles[0]=data; // add 1st half-byte to the array after correction.
            is_empty=0;
        }
        else
        {
            nibbles[1]=data; // add  2nd half-byte to the array after correction.
            mergeNibblesToOneByte(nibbles, &data);
            fwrite(&data, 1, 1, fp_write);
            is_empty=1; // set is_empty true.
        }
        read = fread(&data, 1, 1, fp_read);
    }
    fclose(fp_read);
    fclose(fp_write);
    return 0;
}