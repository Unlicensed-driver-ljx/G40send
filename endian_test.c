#include <stdio.h>
int main(){int t=0x12345678;unsigned char*p=(unsigned char*)&t;printf("Bytes: %02X %02X %02X %02X\n",p[0],p[1],p[2],p[3]);return 0;}