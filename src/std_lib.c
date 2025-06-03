#include "std_lib.h"

int div(int a, int b) {
  int result = 0;
  while (a >= b) {
    a -= b;
    result++;
  }
  return result;
}

int mod(int a, int b) {
  while (a >= b) {
    a -= b;
  }
  return a;
}

bool strcmp(char *str1, char *str2) {
  while (*str1 && *str2) {
    if (*str1 != *str2) return false;
    str1++;
    str2++;
  }
  return *str1 == *str2;
}

void strcpy(char *dst, char *src) {
  while (*src) {
    *dst++ = *src++;
  }
  *dst = '\0';
}

void clear(byte *buf, unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    buf[i] = 0;
  }
}

void atoi(char *str, int *num) {
  *num = 0;
  int sign = 1;
  if (*str == '-') {
    sign = -1;
    str++;
  }
  while (*str >= '0' && *str <= '9') {
    *num = *num * 10 + (*str - '0');
    str++;
  }
  *num *= sign;
}

void itoa(int num, char *str) {
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }
  
  int i = 0;
  int isNegative = num < 0;
  if (isNegative) num = -num;
  
  while (num != 0) {
    int rem = mod(num, 10);
    str[i++] = rem + '0';
    num = div(num, 10);
  }
  
  if (isNegative) str[i++] = '-';
  
  str[i] = '\0';
  
  // Reverse the string
  int start = 0;
  int end = i - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}
