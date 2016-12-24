#include <avr/io.h>                       
#include <util/delay.h>               


int main(void) {

  // -------- Inits --------- //
  DDRB |= 0x07;
  uint8_t delay = 200;


  // ------ Event loop ------ //
  while (1) {

    PORTB = 0x01;
    _delay_ms(delay);
    PORTB = 0x02;
    _delay_ms(delay);
    PORTB = 0x04;
    _delay_ms(delay);

  } 
  return 0;
}
