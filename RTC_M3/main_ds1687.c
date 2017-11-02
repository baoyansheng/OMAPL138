/*
 * main_ds1687.c
 *
 *  Created on: 2016Äê5ÔÂ11ÈÕ
 *      Author: nbpub01
 */
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "driverlib/ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/flash.h"
#include "utils/uartstdio.h"
#include <string.h>

void setRegsiterBanker(int bank);
void readRegsiterBank0(int addr,int *pValue);
void writeRegsiterBank0(int addr,int value);

#define  ALE_UP()       GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_7,0xFF)
#define  ALE_DOWN()     GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_7,0)

#define  RD_ENABLE()    GPIOPinWrite(GPIO_PORTJ_BASE,GPIO_PIN_4,0);\
		                GPIOPinWrite(GPIO_PORTJ_BASE,GPIO_PIN_5,0xFF)
#define  WR_ENABLE()    GPIOPinWrite(GPIO_PORTJ_BASE,GPIO_PIN_4,0xFF);\
                        GPIOPinWrite(GPIO_PORTJ_BASE,GPIO_PIN_5,0);
#define  RD_WR_DISABLE()    GPIOPinWrite(GPIO_PORTJ_BASE,GPIO_PIN_4,0xFF);\
                            GPIOPinWrite(GPIO_PORTJ_BASE,GPIO_PIN_5,0xFF);

int g_iResult = 0;
int g_iAddress = 0;

void main()
{
    // Disable Protection
    HWREG(SYSCTL_MWRALLOW) =  0xA5A5A5A5;
    // Setup main clock tree for 75MHz - M3 and 150MHz - C28x
    SysCtlClockConfigSet(SYSCTL_SYSDIV_1 | SYSCTL_M3SSDIV_2 | SYSCTL_USE_PLL |
                         (SYSCTL_SPLLIMULT_M & 0x0F));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);

    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_7);  //ALE

    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_3);

    GPIOPinTypeGPIOOutput(GPIO_PORTJ_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTJ_BASE, GPIO_PIN_5);

    RD_WR_DISABLE();
    ALE_DOWN();

/*    writeRegsiterBank0(11,0x86);

    writeRegsiterBank0(2,12);
    writeRegsiterBank0(4,17);
    writeRegsiterBank0(7,11);
    writeRegsiterBank0(8,5);
    writeRegsiterBank0(6,3);
    writeRegsiterBank0(9,16);

    writeRegsiterBank0(11,0x06);*/


    while(1)
    {
    	writeRegsiterBank0(11,0x86);
    	readRegsiterBank0(g_iAddress,&g_iResult);
    	writeRegsiterBank0(11,0x06);
    }
}

void setRegsiterBanker(int bank)
{

}


void readRegsiterBank0(int addr,int *pValue)
{
	int tempValue = 0;
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);

    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_3);
	ALE_UP();
	GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_3,(addr&0x01)<<3);
	GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_2,(addr&0x02)<<1);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,(addr&0x04)<<2);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,(addr&0x08)<<2);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,(addr&0x10)<<2);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,(addr&0x20)<<2);
	GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_0,(addr&0x40)>>6);
	GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_1,(addr&0x80)>>6);
	ALE_DOWN();

    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_6);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_7);

    GPIOPinTypeGPIOInput(GPIO_PORTH_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOInput(GPIO_PORTH_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOInput(GPIO_PORTH_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOInput(GPIO_PORTH_BASE, GPIO_PIN_3);
	RD_ENABLE();
	tempValue = GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_3)>>3;
	tempValue |= GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_2)>>1;
	tempValue |= GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4)>>2;
	tempValue |= GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_5)>>2;
	tempValue |= GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_6)>>2;
	tempValue |= GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_7)>>2;
	tempValue |= GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_0)<<6;
	tempValue |= GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_1)<<6;
	RD_WR_DISABLE();

	*pValue = tempValue;
}


void writeRegsiterBank0(int addr,int value)
{
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);

    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_3);
	ALE_UP();
	GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_3,(addr&0x01)<<3);
	GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_2,(addr&0x02)<<1);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,(addr&0x04)<<2);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,(addr&0x08)<<2);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,(addr&0x10)<<2);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,(addr&0x20)<<2);
	GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_0,(addr&0x40)>>6);
	GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_1,(addr&0x80)>>6);
	ALE_DOWN();

	WR_ENABLE();
	GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_3,(value&0x01)<<3);
	GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_2,(value&0x02)<<1);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,(value&0x04)<<2);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,(value&0x08)<<2);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,(value&0x10)<<2);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,(value&0x20)<<2);
	GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_0,(value&0x40)>>6);
	GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_1,(value&0x80)>>6);
	RD_WR_DISABLE();
}




