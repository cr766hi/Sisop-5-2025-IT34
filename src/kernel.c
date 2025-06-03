#include "shell.h"
#include "kernel.h"

int main() {
  clearScreen();
  shell();
}

void printString(char *str) {
  while (*str != '\0') {
    interrupt(0x10, 0x0E00 | *str, 0, 0, 0);
    str++;
  }
}

void readString(char *buf) {
  int i = 0;
  while (true) {
    char c = interrupt(0x16, 0, 0, 0, 0);
    if (c == '\r') {  // Enter key
      buf[i] = '\0';
      printString("\n");
      return;
    } else if (c == '\b' && i > 0) {  // Backspace
      i--;
      printString("\b \b");
    } else if (c >= 32 && c <= 126) {  // Printable characters
      buf[i] = c;
      i++;
      interrupt(0x10, 0x0E00 | c, 0, 0, 0);
    }
  }
}

void clearScreen() {
  // Clear screen by filling with spaces
  for (int i = 0; i < 80 * 25; i++) {
    putInMemory(0xB000, 0x8000 + i * 2, ' ');
    putInMemory(0xB000, 0x8000 + i * 2 + 1, 0x07);  // White on black
  }
  // Reset cursor position
  interrupt(0x10, 0x0200, 0, 0, 0);  // Set cursor position
}
