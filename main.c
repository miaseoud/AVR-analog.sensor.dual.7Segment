/*************************************************************************************************************************/
/*------------------------------- Analog Sensor to Dual Seven Segment display (0-99) using IC 7448 ----------------------*/
/*************************************************************************************************************************/
/*  - Attiny85 is connected to 7448, 2n2222 transistor and analog sensor.
 *  - Attiny85 writes BCD value to 7448 and switches from one 7segment to another...
 *    periodically by switching on and off the base of 2n2222 with high frequency.
 *  - The transistor acts a switch for the common cathode seven segment. The switching
 *    signal is NOT-ed to switch between the 2 seven segments, driving the base of a second transistor
 *    connected to the cammon cathode of the 2nd 7 segment display.
 */
#include <avr/io.h>
#include <avr/delay.h>
#include "DIO.h" //Custom library for defining pin directions and set/clear.
/*------------------------------- Functions definitions & Declarations ----------------------*/
void write7Segment (int val);
/************************************************************************************************************/
/*------------------------------- Initilize ADC Channel based on function input (0-3) ----------------------*/
/************************************************************************************************************/
void ADCx_Init (char ADC_channel) {
  ADCSRA |=  (ADEN) ; //ADC Enable
  ADMUX  &= ~ ( (1 << REFS0) | (1 << REFS1) | (1 << ADLAR)); //Voltage Reference: VCC
  ADMUX  |= ADC_channel;
  ADCSRB &= ~((1 << ADTS0) | (1 << ADTS1) | (1 << ADTS2)); //ADC Auto Trigger Source: Free Running Mode
  ADCSRA |= ( (ADPS0) | (ADPS1) | (ADPS2)  ); //clk division factor 2
  //ADCSRA |= ( (ADEN) | (ADIE) | (ADATE)  ); //ADC Enable + Interrupt
  //ADMUX  |= (1 << MUX0) | (2 << MUX0);  //ADC3 only
}
/***********************************************************************************************************/
/*----------------------------------------ADC Trigger and get value----------------------------------------*/
int getADC (void) {
  ADCSRA |= 1 << ADSC; //Start a new conversion
  while ( ADCSRA & (1 << ADSC)); // wait untill conversion complete
  return ADCL + ADCH * 256; //XCombine higher and lower bytes
}
/**********************************************************************************************************/
/*---------------------------------------------------- MAIN ----------------------------------------------*/
/***********************************************************************************************************/
int main (void) {
  int mapped_value, old_value = 0;
/*-------------------------------------------- Initilizations----------------------------------------------*/
  DIO_PortDirection(PortB , Pin1, DIO_INPUT);                               //Analog sensor input
  DIO_PortDirection(PortB , Pin0 | Pin1 | Pin2 | Pin3  | Pin4, DIO_OUTPUT); //BCD output and switching signal
  ADCx_Init (0); //Selection and initilization of ADC "0"
/*---------------------------------------------------- SUPER LOOP --------------------------------------------*/
  while (1) {
    /*Only a new value is written to 7 segments if a big change occured
      to prevent continious flickering between 2 consuctive values.*/
    if (abs(old_value - getADC()) > 2) {
      old_value = getADC();
    }
    mapped_value = old_value * 99 / 1023; //Maping 10 bit ADC value from 0-99 for display
    DIO_PortWrite(PortB, Pin4, DIO_LOW); //Switch to first segment
    write7Segment(mapped_value % 10);   //Write first digit
    _delay_ms (5);
    DIO_PortWrite(PortB, Pin4, DIO_HIGH);//Switch to second segment
    write7Segment(mapped_value / 10);    //Write 2nd digit
    _delay_ms (5);
  }
}
/************************************************************************************************************/
/************************************************************************************************************/
/*-------------------------------- Write to common cathode BCD to 7 segment ---------------------------------*/
/************************************************************************************************************/
void write7Segment (int val) {
  switch (val) {
    case 0:
      DIO_PortWrite(PortB, Pin0 | Pin1 | Pin2 | Pin3, DIO_LOW);
      break;
    case 1:
      DIO_PortWrite(PortB, Pin1 | Pin2 | Pin3, DIO_LOW);
      DIO_PortWrite(PortB, Pin0, DIO_HIGH);
      break;
    case 2:
      DIO_PortWrite(PortB, Pin0 | Pin2 | Pin3, DIO_LOW);
      DIO_PortWrite(PortB, Pin1, DIO_HIGH);
      break;
    case 3:

      DIO_PortWrite(PortB, Pin0 | Pin1 , DIO_HIGH);
      DIO_PortWrite(PortB, Pin2 | Pin3, DIO_LOW);
      break;
    case 4:
      DIO_PortWrite(PortB, Pin0 | Pin1 | Pin3, DIO_LOW);
      DIO_PortWrite(PortB, Pin2 , DIO_HIGH);

      break;
    case 5:
      DIO_PortWrite(PortB, Pin1 |  Pin3, DIO_LOW);
      DIO_PortWrite(PortB, Pin0 | Pin2 , DIO_HIGH);
      break;
    case 6:
      DIO_PortWrite(PortB, Pin0 |  Pin3, DIO_LOW);
      DIO_PortWrite(PortB, Pin1 | Pin2 , DIO_HIGH);

      break;
    case 7:
      DIO_PortWrite(PortB, Pin0 | Pin1 | Pin2 , DIO_HIGH);
      DIO_PortWrite(PortB,  Pin3, DIO_LOW);
      break;
    case 8:
      DIO_PortWrite(PortB, Pin0 | Pin1 | Pin2 , DIO_LOW);
      DIO_PortWrite(PortB, Pin3 , DIO_HIGH);
      break;
    case 9:
      DIO_PortWrite(PortB,  Pin1 | Pin2 , DIO_LOW);
      DIO_PortWrite(PortB, Pin0 | Pin3  , DIO_HIGH);
      break;
  }
}
/******************************************************************************************************************************************************************************/

