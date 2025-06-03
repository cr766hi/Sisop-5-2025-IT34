#ifndef __SHELL_H__
#define __SHELL_H__

#include "std_type.h"
#include "kernel.h"

// Shell core functions
void shell();
void printPrompt();
bool handleCommand(char *buf);
void parseCommand(char *buf, char *cmd, char arg[2][64]);

// Command handlers
void changeUsername(char *newName);
void setGrandCompany(char *company);
void handleCalculator(char *operation, char *arg1, char *arg2);
void handleYogurt();

// Utility functions
void setTextColor(byte color);

// Global variables (extern declarations)
extern char username[64];
extern char company[64];
extern byte textColor;

#endif // __SHELL_H__
