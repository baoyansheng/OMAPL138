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


#define  RDSR  0x05
#define  WRSR  0x01
#define  WREN  0x06
#define  RDRTC  0x13
#define  WRRTC   0x12


void main()
{
    unsigned long ulDataTx[4];
    unsigned long ulDataRx[4];
    unsigned long ulTime[8];
    unsigned long dummyRx;
    unsigned long dummyTx = 0xFF;
    int index = 0;
    // Disable Protection
    HWREG(SYSCTL_MWRALLOW) =  0xA5A5A5A5;
    // Setup main clock tree for 75MHz - M3 and 150MHz - C28x
    SysCtlClockConfigSet(SYSCTL_SYSDIV_1 | SYSCTL_M3SSDIV_2 | SYSCTL_USE_PLL |
                         (SYSCTL_SPLLIMULT_M & 0x0F));


    // The SSI0 peripheral must be enabled for use.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);

    // For this example SSI0 is used with PortA[5:2].  The actual port and pins
    // used may be different on your part, consult the data sheet for more
    // information.  GPIO port A needs to be enabled so these pins can be used.
    // TODO: change this to whichever GPIO port you are using.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Configure the pin muxing for SSI0 functions on port A2, A3, A4, and A5.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    GPIOPinConfigure(GPIO_PB4_SSI1TX);
    GPIOPinConfigure(GPIO_PB5_SSI1RX);
    GPIOPinConfigure(GPIO_PB6_SSI1CLK);
    //GPIOPinConfigure(GPIO_PB7_SSI1FSS);

    GPIOPinUnlock(GPIO_PORTB_BASE, GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_7);
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_7,0);

    // Configure the GPIO settings for the SSI pins.  This function also gives
    // control of these pins to the SSI hardware.  Consult the data sheet to
    // see which functions are allocated per pin.
    // The pins are assigned as follows:
    //      PA5 - SSI0Tx
    //      PA4 - SSI0Rx
    //      PA3 - SSI0Fss
    //      PA2 - SSI0CLK
    // TODO: change this to select the port/pin you are using.
    GPIOPinTypeSSI(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6
                   /*| GPIO_PIN_7*/);

    // Configure and enable the SSI port for SPI master mode.  Use SSI0,
    // system clock supply, idle clock level low and active low clock in
    // freescale SPI mode, master mode, 1MHz SSI frequency, and 8-bit data.
    // For SPI mode, you can set the polarity of the SSI clock when the SSI
    // unit is idle.  You can also configure what clock edge you want to
    // capture data on.  Please reference the datasheet for more information on
    // the different SPI modes.
    SSIConfigSetExpClk(SSI1_BASE, SysCtlClockGet(SYSTEM_CLOCK_SPEED),
                       SSI_FRF_MOTO_MODE_0,
                       SSI_MODE_MASTER, 10000000, 8);

    //HWREG(SSI1_BASE + SSI_O_CR1) |= SSI_CR1_LBM;

    // Enable the SSI0 module.
    SSIEnable(SSI1_BASE);

    while(1){
    	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_7,0);
    	    	SSIDataPut(SSI1_BASE, RDRTC);
    	        while(SSIBusy(SSI1_BASE))
    	        {
    	        }
    	        SSIDataGet(SSI1_BASE,&dummyRx);

    	    	SSIDataPut(SSI1_BASE, 0x09);
    	        while(SSIBusy(SSI1_BASE))
    	        {
    	        }
    	        SSIDataGet(SSI1_BASE,&dummyRx);


    	        for(index=0;index<7;index++){
    	        	SSIDataPut(SSI1_BASE, dummyTx);
    	            while(SSIBusy(SSI1_BASE))
    	            {
    	            }
    	        	SSIDataGet(SSI1_BASE, &ulTime[index]);
    	        }

    	        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_7,0xFF);
    }
}
