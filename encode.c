#include <stdio.h>
#include <stdint.h>
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

     // Open for reading in binary mode. if the file doesnot exits it returns NULL.
     fp_read = fopen(argv[1], "rb");

     // Open for reading in binary mode. if the file doesnot exits it returns NULL.
     fp_write = fopen(argv[2], "wb");

    if(fp_read==NULL && fp_write==NULL){
         printf("error opening the file.\n");
         return 1;
     }

     int read = fread(&data, 1, 1, fp_read);
     while(read > 0){
         printf("Read data byte: %u\n", data);

         uint8_t nibbles[2];
         splitByteIntoNibbles(data, nibbles); // split into high & low nibbes
         printf("Nibbles: %u %u\n", nibbles[0],nibbles[1]);

         addParityBit(&nibbles[0]);
         addParityBit(&nibbles[1]);

         //writing encoded data in the file
         fwrite(nibbles, 1, 2, fp_write);

         read = fread(&data, 1, 1, fp_read);
     }
    fclose(fp_read);
    fclose(fp_write);
    return 0;
}