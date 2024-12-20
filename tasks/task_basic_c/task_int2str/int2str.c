#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "int2str.h"


char* int2str(int number) {
    if (number == -2147483648) {
        char* str = malloc(12 * sizeof(char));
        assert(str != NULL);
        snprintf(str, sizeof("-2147483648"), "%s", "-2147483648");
        return str;
    }

    int isNegative = (number < 0);
    if (isNegative) {
        number = -number;
    }

    int temp = number;
    int length = isNegative ? 1 : 0;
    do {
        length++;
        temp /= 10;
    } while (temp > 0);

    char* str = malloc((length + 1) * sizeof(char));
    assert(str != NULL);
    str[length] = '\0';

    int index = length - 1;
    do {
        str[index--] = '0' + (number % 10);
        number /= 10;
    } while (number > 0);

    if (isNegative) {
        str[0] = '-';
    }

    return str;
}
