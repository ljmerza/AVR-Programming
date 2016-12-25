#include <avr/io.h>                       
#include <util/delay.h>               


int main(void) {

  // -------- Inits --------- //
  DDRB |= 0x07;
  uint16_t delay = 500;
  uint8_t i;


  while (1) {
  	i=0; // reset i

  	while(i<3) {
  		// shift 0x01 over i number of bits
  		PORTB = (1 << i);
  		// delay
  		_delay_ms(delay);
  		//increment i
  		i=i+1;
  	}

  } 
  return 0;
}
