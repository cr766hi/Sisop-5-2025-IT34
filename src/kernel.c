#include "shell.h"
#include "kernel.h"

int main() {
    clearScreen();
    shell();
}

void printString(char *str) {
    while (*str) {
        interrupt(0x10, 0x0E00 | *str, 0, 0, 0);
        str++;
    }
}

void readString(char *buf) {
    int i = 0;
    while (1) {
        char c = interrupt(0x16, 0, 0, 0, 0);
        if (c == '\r' || c == '\n') {
            buf[i] = '\0';
            printString("\r\n");
            return;
        } else if (c == '\b' && i > 0) {
            i--;
            printString("\b \b");
        } else if (c >= 32 && c <= 126) {
            buf[i++] = c;
            interrupt(0x10, 0x0E00 | c, 0, 0, 0);
        }
    }
}

void clearScreen() {
    int i;
    for (i = 0; i < 80*25; i++) {
        putInMemory(0xB800, i*2, ' ');
        putInMemory(0xB800, i*2+1, 0x07);
    }
    interrupt(0x10, 0x0200, 0, 0, 0);
}
