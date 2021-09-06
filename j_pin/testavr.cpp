#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <j_pin.h>
#define F_CPU = 20000000L
int main(){

	DDRA = 0x07;
	DDRB = 0x07;
	DDRF = 0x0f;
	DDRK = 0x0f;
	
	setup_ADC();
	sei();
	while(1){
	
	}
	return 0;
}

void setup_ADC(){
	ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << ADLAR) | (1 << MUX1) | (1 << MUX0);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	DIDR0 = (1 << ADCSO);
	ADCSRB = (1 << MUX5) | (1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0);
}

void adc_conversion(){
	ADCSRA |= (1 << ADSC);
}

void ISR(INT1_vect){
}

void ISR(TIMER0_OVR_vect){

}

void MIDI_conversion(){

}
