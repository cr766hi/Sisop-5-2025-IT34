#include "std_lib.h"

int div(int a, int b) {
    int sign = 1;
    int result = 0;
    
    if (a < 0) {
        sign = -sign;
        a = -a;
    }
    if (b < 0) {
        sign = -sign;
        b = -b;
    }
    
    while (a >= b) {
        a -= b;
        result++;
    }
    
    return sign * result;
}

int mod(int a, int b) {
    int divResult = div(a, b);
    return a - (divResult * b);
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
    unsigned int i;
    for (i = 0; i < size; i++) {
        buf[i] = 0;
    }
}

void atoi(char *str, int *num) {
    int sign = 1;
    *num = 0;
    
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
    int i = 0;
    int sign = num < 0;
    int len, j;
    char temp;
    
    if (num == 0) {
        strcpy(str, "0");
        return;
    }
    
    if (sign) num = -num;
    
    while (num > 0) {
        str[i++] = '0' + mod(num, 10);
        num = div(num, 10);
    }
    
    if (sign) str[i++] = '-';
    
    str[i] = '\0';
    

    len = i;
    for (j = 0; j < len/2; j++) {
        temp = str[j];
        str[j] = str[len-j-1];
        str[len-j-1] = temp;
    }
}
