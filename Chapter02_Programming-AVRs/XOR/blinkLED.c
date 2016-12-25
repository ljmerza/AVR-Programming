#include <avr/io.h>                       
#include <util/delay.h>               


int main(void) {

  // -------- Inits --------- //
  DDRB |= 0x07;
  uint16_t delay = 500;
  uint8_t i;


  while (1) {

    // write opposite of current value to first three leds
    PORTB ^= 0x07;
    _delay_ms(delay);
  } 
  return 0;
}
