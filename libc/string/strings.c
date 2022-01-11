#include <string.h>

/*
    base determines what number we are going to % by
    returns length;
*/
int itoa(unsigned long int n, char *buf, int base) {
    unsigned long int temp = n;
    int curr;
    int i = 0;
    do {
        curr = temp % base;
        char ch = (char)(curr + 48); // add 48 because ASCII of 0 is 48
        if (58 <= ch && ch <= 63) {
            ch += 39;
        }
        buf[i] = ch;
        temp /= base;
        i++;
    } while(temp > 0);

    strrev(buf);
    return i;
} 
//97, 98, 99, 100, 101, 102
//58, 59, 60, 61,  62,  63

int strrev(char *buf) {
    int length = strlen(buf);
    int j = length - 1;
    for (int i = 0; i < j; i++, j--) {
        char temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
    }

    return length;
}