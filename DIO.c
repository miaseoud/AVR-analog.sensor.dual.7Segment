/*************************************************************************************************************************/
/*------------------------------------------------ Library for driving AVR GPIOs ----------------------------------------*/
/***** -- Modified for ATtiny85 -- ***************************************************************************************/
/* - Library is used for: 
*  - Determining Port/Pin direction.
*  - Setting/Clearing Port/Pin.
*  - Reading Port/Pin
*  Ex: DIO_PortWrite(PortB, Pin0 | Pin2 | Pin3, DIO_LOW);
*/
#include "DIO.h"
#include <avr/io.h>"
/*************************************************************************************************************************/
/*------------------------------------------------------ DIRECTION ------------------------------------------------------*/
/*************************************************************************************************************************/
void DIO_PortDirection(uint8_t port, uint8_t mask, uint8_t value){
  switch (port)
  {
  case PortA:
  //  SET_REG(DDRA,value,mask);
    break;

  case PortB:
    SET_REG(DDRB,value,mask);
    break;

  case PortC:
 //   SET_REG(DDRC,value,mask);
    break;

  case PortD:
 //   SET_REG(DDRD,value,mask);
    break;

  case PortE:
  //  SET_REG(DDRE,value,mask);
    break;

  case PortF:
   // SET_REG(DDRF,value,mask);
    break;
  }
}
/*************************************************************************************************************************/
/*------------------------------------------------------ WRITE ------------------------------------------------------*/
/*************************************************************************************************************************/
void DIO_PortWrite(uint8_t port, uint8_t mask, uint8_t value){
    switch (port)
    {
    case PortA:
//        SET_REG(PORTA,value,mask);
        break;

    case PortB:
        SET_REG(PORTB,value,mask);
        break;

    case PortC:
   //     SET_REG(PORTC,value,mask);
        break;

    case PortD:
     //   SET_REG(PORTD,value,mask);
        break;

    case PortE:
    //    SET_REG(PORTE,value,mask);
        break;

    case PortF:
     //   SET_REG(PORTF,value,mask);
        break;
    }
}
/*************************************************************************************************************************/
/*------------------------------------------------------ READ ------------------------------------------------------*/
/*************************************************************************************************************************/
void DIO_PortRead(uint8_t port , uint8_t mask, puint8_t data){
	switch (port)
		{
		case PortA:
	//		*data = GET_REG(PORTA,mask);
			break;

		case PortB:
			*data =GET_REG(PORTB,mask);
			break;

		case PortC:
		//	*data =GET_REG(PORTC,mask);
			break;

		case PortD:
		//	*data =GET_REG(PORTD,mask);
			break;

		case PortE:
	//		*data =GET_REG(PORTE,mask);
			break;

		case PortF:
		//	*data = GET_REG(PORTF,mask);
			break;
		}
}
/******************************************************************************************************************************************************************************/
