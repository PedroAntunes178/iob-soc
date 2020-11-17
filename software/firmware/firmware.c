#include "stdlib.h"
#include "system.h"
#include "periphs.h"
#include "iob-uart.h"
#include <stdint.h>

void num2s(uint64_t, char*);
int main()
{
  //init uart
  uart_init(UART_BASE,FREQ/BAUD);
  uart_printf("\n\nFibonacci Series: \n\n");
  uint8_t n = 100;
  uint8_t i = 1;
  uint16_t present = 0;
  uint16_t past = 0;
  uint16_t future = 0;
  uint8_t expoente = 0;
  unsigned char c[100];
  uart_printf("%d Term \t %u\n", i, present);
  present = 1;
  for (i = 2; i <= n; ++i) {
    future = past + present;
    if(future<present || future<past){
      uart_printf("%d Term\tOverflow\n", i);
      past = past/100;
      present = present/100;
      future = past + present;
      expoente = expoente + 2;
    }
    //num2s(present, c);
    uart_printf("%d Term\t%ux10^%d\n", i, present, expoente);
    past = present;
    present = future;
  }
}

void num2s(uint64_t i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    uint64_t shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
}
