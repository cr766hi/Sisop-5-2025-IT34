#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char username[64] = "user";
char grandcompany[64] = "";
int textColor = 0x07; // Default white

void shell(){
  char buf[128];
  char cmd[64];
  char args[2][64];
  
  printString("Welcome to EorzeOS!\n");
  while (true) {
    // Print prompt with username and grandcompany
    printString(username);
    if (strcmp(grandcompany, "")) {
      printString("@");
      printString(grandcompany);
    }
    printString("> ");
    
    readString(buf);
    
  
    parseCommand(buf, cmd, args);
    
    if (strcmp(cmd, "user")) {
      if (strcmp(args[0], "")) {
        strcpy(username, args[0]);
        printString("Username changed to ");
        printString(username);
        printString("\n");
      } else {
        strcpy(username, "user");
        printString("Username changed to user\n");
      }
    }
    else if (strcmp(cmd, "grandcompany")) {
      if (strcmp(args[0], "maelstrom")) {
        clearScreen();
        textColor = 0x04; // Red
        strcpy(grandcompany, "Storm");
      }
      else if (strcmp(args[0], "twinadder")) {
        clearScreen();
        textColor = 0x0E; // Yellow
        strcpy(grandcompany, "Serpent");
      }
      else if (strcmp(args[0], "immortalflames")) {
        clearScreen();
        textColor = 0x01; // Blue
        strcpy(grandcompany, "Flame");
      }
      else if (strcmp(args[0], "clear")) {
        clearScreen();
        textColor = 0x07; // White
        strcpy(grandcompany, "");
      }
      else {
        printString("Error: Invalid grand company\n");
      }
    }
    else if (strcmp(cmd, "add") || strcmp(cmd, "sub") || 
             strcmp(cmd, "mul") || strcmp(cmd, "div")) {
        int x, y, result;
        char numStr[16];
        
        atoi(args[0], &x);
        atoi(args[1], &y);
        
        if (strcmp(cmd, "add")) result = x + y;
        else if (strcmp(cmd, "sub")) result = x - y;
        else if (strcmp(cmd, "mul")) result = x * y;
        else if (strcmp(cmd, "div")) result = div(x, y);
        
        itoa(result, numStr);
        printString(numStr);
        printString("\n");
    }
    else if (strcmp(cmd, "yogurt")) {
      // Random responses
      int tick = getBiosTick();
      switch (mod(tick, 3)) {
        case 0: printString("yo\n"); break;
        case 1: printString("ts unami gng </3\n"); break;
        case 2: printString("sygau\n"); break;
      }
    }
    else if (strcmp(cmd, "clear")) {
      clearScreen();
      textColor = 0x07;
      strcpy(grandcompany, "");
    }
    else {
      printString(buf);
      printString("\n");
    }
  }
}

void parseCommand(char *buf, char *cmd, char args[2][64]) {
  int i = 0, argNum = 0, pos = 0;
  
  strcpy(cmd, "");
  strcpy(args[0], "");
  strcpy(args[1], "");
  
  while (buf[i] == ' ') i++;
  
  while (buf[i] != ' ' && buf[i] != '\0') {
    cmd[pos++] = buf[i++];
  }
  cmd[pos] = '\0';
  
  while (buf[i] != '\0') {
    while (buf[i] == ' ') i++;
    if (buf[i] == '\0') break;
    
    pos = 0;
    while (buf[i] != ' ' && buf[i] != '\0') {
      args[argNum][pos++] = buf[i++];
    }
    args[argNum][pos] = '\0';
    argNum++;
    if (argNum >= 2) break;
  }
}
