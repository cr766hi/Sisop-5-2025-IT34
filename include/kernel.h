#ifndef KERNEL_H
#define KERNEL_H

#include "std_type.h"

extern void putInMemory(int segment, int address, char character);
extern int interrupt(int number, int AX, int BX, int CX, int DX);
extern unsigned int getBiosTick();

void printString(char *str);
void readString(char *buf);
void clearScreen();

#endif
