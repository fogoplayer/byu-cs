#include <stdio.h>

int main() {
  int x = 0x12345678;
  printf("%x\n", x);
  printf("i: %x\n", (x & (0x0f << 16))>>16);
  printf("i: %x\n", x | (0x0a << 16));

  return 0; 
}