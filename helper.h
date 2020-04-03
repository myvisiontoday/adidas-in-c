#ifndef _HELPER_H
#define _HELPER_H

void splitByteIntoNibbles(uint8_t dataByte, uint8_t nibbles[]);
void addParityBit(uint8_t* nibble);
void error_correction(uint8_t* data);
void mergeNibblesToOneByte(uint8_t nibbles[], uint8_t* data);

#endif