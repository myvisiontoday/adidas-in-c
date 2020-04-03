#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 
#include <time.h>
#include "helper.h"

/*
1. flip bit
2. 
*/

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
        return 1;
    }

     FILE *fp_read; 
     FILE *fp_write; 
     uint8_t data;

     // Open for reading in binary mode. if the file doesnot exits it returns NULL.
     fp_read = fopen(argv[1], "rb");

     // Open for reading in binary mode. if the file doesnot exits it returns NULL.
     fp_write = fopen(argv[2], "wb");

     if((fp_read==NULL) && (fp_write==NULL)){
        printf("error opening the file.\n");
        return 1;
     }
    int read = fread(&data, 1, 1, fp_read);
    srand(time(NULL));
    int counter=0;
    while(read > 0){
        printf("Read data byte: %u\n", data);
        //start fliping the random bit.
        int random=rand() % 8; // for random no 0-7
        printf("R no: %d\n", random);
        data ^= (1<<random); // exclusive or 
        counter++;
        //writing encoded data in the file
        fwrite(&data, 1, 1, fp_write);

        read = fread(&data, 1, 1, fp_read);
    }
    fclose(fp_read);
    fclose(fp_write);

    printf("%d bits are fliped here.\n", counter);
    return 0;
}