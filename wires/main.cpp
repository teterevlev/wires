/*
 * wires.cpp
 *
 * Created: 21.02.2017 17:51:26
 * Author : odama
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
static const uint8_t mask[5] = {
	0b10110111,
	0b11010111,
	0b01110111,
	0b11100111,
	0b11110111
};
void openDoor(){
	PORTC = 0b00010000;
	_delay_ms(500);
	PORTC = 0b00011000;
	_delay_ms(200);
	PORTC = 0b00010000;
	_delay_ms(200);
	PORTC = 0b00000000;
}
bool checkWires(){
	for(uint8_t i=0; i<5; i++){
		DDRB = 1<<i;
		_delay_ms(10);
		if(PIND != mask[i]) return false;
	}
	return true;
}
int main(void)
{
    DDRB = 0;
	DDRD = 0;
	DDRC = 0b00011000;
	PORTD = 0xff;
    while (1) 
    {
		if(checkWires()){
			openDoor();
			while(checkWires());
		}
    }
}

