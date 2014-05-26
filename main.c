#include <msp430G2553.h>
//#include "Init_Clk.h"
//#include "PWM_OUT.h"
//#include "I2C.h"
#include "CarControl.h"
#include <stdio.h>


void forward(int gpio)
{
	P1OUT = gpio;
}
void backward(int gpio)
{
	P1OUT = ~(gpio);
}

struct CarWheelRollDirectory rollDirectory=
{
	forward,
	backward,
};

struct CarWheel wheel[fourWheel] =
{
	{
		"FrontLeftWheel",
		BIT0,
		&rollDirectory,
	},{
		"FrontRightWheel",
		BIT6,
		&rollDirectory,
	},{
		"BackLeftWheel",
		BIT1,
		&rollDirectory,
	},{
		"BackRightWheel",
		BIT2,
		&rollDirectory,
	},
};

struct Car car =
{
	fourWheel,
	fourDrive,
	wheel,
	NULL,
};

int CarInit(void)
{
	int ret = 0;
	P1DIR |= BIT0 + BIT1 + BIT2 + BIT6;
	ret  = CarRegist(&car);
	if (ret == -1)
		return ret;
	else
	{

	}
		return 1;
}

void delayms(unsigned int time)
{
  unsigned int i;
  for(;time>0;time--)
  {
    for(i=300;i>0;i--)
    {
    }
  }
}

void main(void)
{
	// Stop watchdog timer to prevent time out reset
	WDTCTL=WDTPW+WDTHOLD;
	//Init_Clk();
	//P1DIR |= BIT0 + BIT6;
	//P1OUT |= (BIT0 + BIT6);
	CarInit();
	while(1)
	{
		TurnLeft(1, 1);
		delayms(1000);
		TurnRight(1, 1);
		delayms(1000);
	}
	//LPM0;
}


