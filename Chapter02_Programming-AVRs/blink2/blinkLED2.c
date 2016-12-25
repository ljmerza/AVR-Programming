#include <avr/io.h>                       
#include <util/delay.h>               


int main(void) {

  // -------- Inits --------- //
  DDRB |= 0x07;
  uint16_t delay = 500;
  uint8_t i;


  while (1) {
    // shift 0x01 over i number of bits
    PORTB = (1 << i);
    // delay
    _delay_ms(delay);

    // turn on LED 2
    PORTB |= (1 << 1);
    _delay_ms(delay);

    // turn on LED 3
    PORTB |= (1 << 2);
    _delay_ms(delay);

    // turn off all
    PORTB = 0x00;
    _delay_ms(delay);


  } 
  return 0;
}
