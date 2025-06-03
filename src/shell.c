#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char username[64] = "user";
char company[64] = "";
int textColor = 0x07;  // Default white

void shell() {
  char buf[128];
  printString("Welcome to EorzeOS!\n");
  while (true) {
    // Print prompt with username and company
    printPrompt();
    
    readString(buf);
    
    // Handle echo if command not recognized
    if (!handleCommand(buf)) {
      printString(buf);
      printString("\n");
    }
  }
}

void printPrompt() {
  printString(username);
  if (strcmp(company, "") != 0) {
    printString("@");
    printString(company);
  }
  printString("> ");
}

bool handleCommand(char *buf) {
  char cmd[64];
  char args[2][64];
  parseCommand(buf, cmd, args);
  
  // Question 1: The Echo is already handled by default in shell()
  
  // Question 2: gurt: yo
  if (strcmp(cmd, "yo") == 0) {
    printString("gurt\n");
    return true;
  }
  if (strcmp(cmd, "gurt") == 0) {
    printString("yo\n");
    return true;
  }
  
  // Question 3: Change username
  if (strcmp(cmd, "user") == 0) {
    if (strcmp(args[0], "") == 0) {
      strcpy(username, "user");
    } else {
      strcpy(username, args[0]);
    }
    printString("Username changed to ");
    printString(username);
    printString("\n");
    return true;
  }
  
  // Question 4: Grand Company colors
  if (strcmp(cmd, "grandcompany") == 0) {
    if (strcmp(args[0], "maelstrom") == 0) {
      clearScreen();
      textColor = 0x04;  // Red
      strcpy(company, "Storm");
    } else if (strcmp(args[0], "twinadder") == 0) {
      clearScreen();
      textColor = 0x0E;  // Yellow
      strcpy(company, "Serpent");
    } else if (strcmp(args[0], "immortalflames") == 0) {
      clearScreen();
      textColor = 0x01;  // Blue
      strcpy(company, "Flame");
    } else {
      printString("Error: Invalid Grand Company\n");
    }
    return true;
  }
  
  if (strcmp(cmd, "clear") == 0) {
    clearScreen();
    textColor = 0x07;  // White
    strcpy(company, "");
    return true;
  }
  
  // Question 5: Calculator
  if (strcmp(cmd, "add") == 0 || strcmp(cmd, "sub") == 0 || 
      strcmp(cmd, "mul") == 0 || strcmp(cmd, "div") == 0) {
    int x, y;
    atoi(args[0], &x);
    atoi(args[1], &y);
    int result;
    
    if (strcmp(cmd, "add") == 0) result = x + y;
    else if (strcmp(cmd, "sub") == 0) result = x - y;
    else if (strcmp(cmd, "mul") == 0) result = x * y;
    else if (strcmp(cmd, "div") == 0) result = x / y;
    
    char numStr[16];
    itoa(result, numStr);
    printString(numStr);
    printString("\n");
    return true;
  }
  
  // Question 6: Yogurt responses
  if (strcmp(cmd, "yogurt") == 0) {
    int response = mod(getBiosTick(), 3);
    if (response == 0) printString("yo\n");
    else if (response == 1) printString("ts unami gng </3\n");
    else printString("sygau\n");
    return true;
  }
  
  return false;
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, argNum = 0;
  
  // Skip leading spaces
  while (buf[i] == ' ') i++;
  
  // Parse command
  while (buf[i] != ' ' && buf[i] != '\0') {
    cmd[j++] = buf[i++];
  }
  cmd[j] = '\0';
  
  // Parse arguments
  for (int a = 0; a < 2; a++) {
    j = 0;
    // Skip spaces
    while (buf[i] == ' ') i++;
    // Parse argument
    while (buf[i] != ' ' && buf[i] != '\0') {
      arg[a][j++] = buf[i++];
    }
    arg[a][j] = '\0';
  }
}
