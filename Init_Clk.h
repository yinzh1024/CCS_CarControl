#ifndef _INIT_CLK_H
#define _INIT_CLK_H

void Init_Clk();
static void DcoClkSet(unsigned char x,unsigned char y); //msp430g2553datasheet P30
static void MClkSet(unsigned char Div, unsigned char Clk_Source);
static void SMClkSet(unsigned char Div, unsigned char Clk_Source);
static void AClkSet(unsigned char Div);

#endif
