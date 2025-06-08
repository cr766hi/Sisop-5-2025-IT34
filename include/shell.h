#ifndef SHELL_H
#define SHELL_H

#include "kernel.h"

void shell();
void parseCommand(char *buf, char *cmd, char arg[2][64]);

#endif
