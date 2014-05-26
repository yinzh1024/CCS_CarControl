#include <msp430g2553.h>

/*DCOCTL 寄存器*/
/********************************************************************************
* bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0
* DCO.2 CCO.1 DCO.0 MOD.4 MOD.3 MOD.2 MOD.1 MOD.0
* DCO.0--DCO.2定义8种频率之一，可分段调节DCOCLK频率，相邻两种频率相差10%。
* 而频率由注入直流发生器的电流定义。
* MOD.O--MOD.4定义在32个DCO周期中插入的fdco+l周期个数，而在余下的DCO周期
* 中为fDco周期，控制切换DCO和DCO+1选择的两种频率。如果DCO常数为7，表示已
* 经选择最高颂率，此时不能利用MOD.O-MOD.4进行频率调整。
* ********************************************************************************/
/*BCSCTL1 寄存器*/
/**********************************************************************************
* bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0
* XT2OFF XTS DIVA.1 DIVA.0 XT5V Rse1.2 Rse1.1 Rse1.0
*XT2OFF控制 XT2 振荡器的开启与关闭。
*XT2OFF=0，XT2振荡器开启；
*XT2OFF=1，XT2振疡器关闭(默认XT2关闭)。
*XTS控制 LFXTl 工作模武，选择需结合实际晶体振荡器连接情况。
*XTS=0，LFXTl工作在低频模式 (默认低频模式)；
*XTS=1，LFXTl工作在高频模式(必须连接有相应高频时钟源)。
*DIVA.0，DIVA.l控制ACLK分频。
*0 不分频（默认不分频）；
*1 2分频；
*2 4分频；
*3 8分频。
*XT5V此位设置为0。
*Rse1.0，Rsel.l，Rse1.2三位控制某个内部电阻以决定标称频率。
*Rse1=0，选择最低的频率；
*Rse1=7，选择最低的标称频率；
***********************************************************************************/
/*BCSCTL2 寄存器*/
/***********************************************************************************
* bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0
*SELM.1 SELM.0 DIVM.1 DIVM.0 SELS DIVS.1 DIVS.0 DCOR
*SELM.1，SELM.0选择 MCLK 时钟源。
*0 时钟源为 DCOLCK（默认时钟源）；
*1 时钟源为DCOCLK ;
*2 时钟源为LFXTlCLK；
*3 时钟源为 LFXT1CLK 。
*DIVM.1，DlVM.0选择 MCLK 分频。
*0 1分频（默认MCLK=DCOCLK）；
*1 2分频；
*2 4分频；
*3 8分频。
*DIVS.1，DIVS.0选择 SMCLK 分频。
*0 1分频（默认 SMCLK=MCLK)；
*1 2分频；
*2 4分频；
*3 8分频。
************************************************************************************/
/*BCSCTL3 寄存器*/
/************************************************************************************
* bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0
* XT2S1 XT2S0 LFXT1S1 LFXT1S0 XCAP1 XCAP0 XT2OF LFXT1OF
* XT2S1和XT2S0（2553不支持）
* LFXT1S1和LFXT1S0选择LFXT1的范围。
* XCAP1和XCAP0选择LFXT1的匹配电容
* 00 1pf
* 01 6pf
* 10 10pf
* 11 12.5pf
************************************************************************************/


/************************************************************************
* 函数名 : DcoClkSet
* 函数功能 : 对时钟DCOCLK进行配置
* 函数形参 : 传入的形参为x和y，其值参考2553datsheet第28页中DCO频率表
* 函数返回值 : 无
************************************************************************/
void DcoClkSet(unsigned char x,unsigned char y) // msp430g2553datasheet P30
{
  DCOCTL &=~( 0xFF);
  BCSCTL1 &=~( 0xFF);
  unsigned char temp=(x<<4)+y;
  switch(temp){
  case 0x00: {
    DCOCTL &=~( DCO0 + DCO1 + DCO2);
    BCSCTL1 &=~( RSEL0 + RSEL1 + RSEL2 + RSEL3);
    break;
  }
  case 0x03: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 &=~( RSEL0 + RSEL1 + RSEL2 + RSEL3);
    break;
  }
  case 0x13: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0 );
    break;
  }
  case 0x23: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL1 );
    break;
  }
  case 0x33: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0 + RSEL1 );
    break;
  }
  case 0x43: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL2);
    break;
  }
  case 0x53: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0 + RSEL2 );
    break;
  }
  case 0x63: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL1 + RSEL2 );
    break;
  }
  case 0x73: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 );
    break;
  }
  case 0x83: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL3);
    break;
  }
  case 0x93: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0+ RSEL3);
    break;
  }
  case 0xA3: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL1 + RSEL3);
    break;
  }
  case 0xB3: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL3);
    break;
  }
  case 0xC3: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL2 + RSEL3);
    break;
  }
  case 0xD3: {
    DCOCTL |= ( DCO0 + DCO1 );
    DCOCTL |= ( MOD4 + MOD3 + MOD2 + MOD1 + MOD0 );//微调DCOCLK
    BCSCTL1 |= ( RSEL0 + RSEL2 + RSEL3);
    break;
  }
  case 0xE3: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL1 + RSEL2 + RSEL3);
    break;
  }
  case 0xF3: {
    DCOCTL |= ( DCO0 + DCO1 );
    BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 + RSEL3);
    break;
  }
  case 0xF7: {
    DCOCTL |= ( DCO0 + DCO1 + DCO2 );
    BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 + RSEL3);
    break;
  }
  default: {
    DCOCTL |= ( DCO0 + DCO1 + DCO2 );
    BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 + RSEL3);
  }
  }
}
/********************************************************************
* 函数名 : MClkSet
* 函数功能 : 对时钟MCLK进行配置
* 函数形参 : 传入的形参为Div，对时钟源DCOCLK进行Div分频
* 函数返回值 : 无
********************************************************************/
void MClkSet(unsigned char Div, unsigned char Clk_Source)
{
  unsigned char i;
  switch (Clk_Source)
  {
    case 'V':{
      break;
    }
    case 'L':{
      BCSCTL1 &= ~(XT2OFF);  
      do{
        IFG1 &= ~(OFIFG);                                                                                                                                                                                                                                                                                                                      
        for(i=0; i<100; i++){_NOP();}
      }while((IFG1 & OFIFG) != 0);
      BCSCTL1 |= XTS;
      BCSCTL2 |= SELM1 + SELM0;
      BCSCTL3 &= ~(XCAP0 + XCAP1);
      break;
    }
    case 'D':{
      BCSCTL2 &= ~(SELM1+SELM0); //select DCOCLK for SMCLK
      break;
    }
  }
  switch(Div){ //1分频
  case 0x01:{
    BCSCTL2 &=~(DIVM1 + DIVM0);
    break;
  }
  case 0x02:{ //2分频
    BCSCTL2 &=~(DIVM1 + DIVM0);
    BCSCTL2 |=DIVM0;
    break;
  }
  case 0x04:{ //4分频
    BCSCTL2 &=~(DIVM1 + DIVM0);
    BCSCTL2 |=DIVM1;
    break;
  }
  case 0x08:{ //8分频
    BCSCTL2 |=(DIVM1 + DIVM0);
    break;
  }
  default :{ //默认不分频
    BCSCTL2 &=~(DIVM1 + DIVM0);
  } 
  }
}
/********************************************************************
* 函数名 : SMClkSet
* 函数功能 : 对时钟MCLK进行配置
* 函数形参 : 传入的形参为Div，对时钟源DCOCLK进行Div分频
* 函数返回值 : 无
********************************************************************/
void SMClkSet(unsigned char Div, unsigned char Clk_Source)
{
  unsigned char i;
  switch (Clk_Source)
  {
    case 'V':{
      break;
    }
    case 'L':{
      BCSCTL1 &= ~(XT2OFF);  
      do{
        IFG1 &= ~(OFIFG);                                                                                                                                                                                                                                                                                                                      
        for(i=0; i<100; i++){_NOP();}
      }while((IFG1 & OFIFG) != 0);
      BCSCTL1 |= XTS;
      BCSCTL2 |= SELS;
      BCSCTL3 &= ~(XCAP0 + XCAP1);
      break;
    }
    case 'D':{
      BCSCTL2 &= ~SELS; //select DCOCLK for SMCLK
      break;
    }
  }
  switch(Div)
  {
  case 0x01:{ //1分频
    BCSCTL2 &=~(DIVS_3);
    break;
  }
  case 0x02:{ //2分频
    BCSCTL2 &=~(DIVS_3);
    BCSCTL2 |=(DIVS_1);
    break;
  }
  case 0x04:{ //4分频
    BCSCTL2 &=~(DIVS_3);
    BCSCTL2 |=(DIVS_2);
    break;
  }
  case 0x08:{ //8分频
    BCSCTL2 |=(DIVS_3);
    break;
  }
  default :{ //默认不分频
    BCSCTL2 &=~(DIVS_3);
  } 
  }
}
/********************************************************************
* 函数名 : AClkSet
* 函数功能 : 对时钟MCLK进行配置
* 函数形参 : 传入的形参为Div，对时钟源LFXT1CLK进行Div分频
* 函数返回值 : 无
********************************************************************/
void AClkSet(unsigned char Div)
{
  BCSCTL1 &=~(XTS); //low-frequency mode
  switch(Div){
    case 0x01:{ //1分频
      BCSCTL1 &=~(DIVA_3);
      break;
    }
    case 0x02:{ //2分频
      BCSCTL1 &=~(DIVA_3);
      BCSCTL1 |=(DIVA_1);
      break;
    }
    case 0x04:{ //4分频
      BCSCTL1 &=~(DIVA_3);
      BCSCTL1 |=(DIVA_2);
      break;
    }
    case 0x08:{ //8分频
      BCSCTL1 |=(DIVA_3);
      break;
    }
    default :{ //默认不分频
      BCSCTL1 &=~(DIVA_3);
    } 
  }
  BCSCTL3 |= XT2S0 + LFXT1S0 + XCAP_3; //配置ACLK匹配电容
}
/********************************************************************
* 名称 : Init_Clk()
* 功能 : MSP430时钟系统初始化程序
* 输入 : 无
* 返回值 : 无
********************************************************************/
void Init_Clk() //时钟系统设置
{
  DcoClkSet(13,3); //7.84MHz 2553datasheet 第28页
  AClkSet(0x08); //8分频LFXT1CLK
  SMClkSet(0x01, 'D'); //1分频DCOCLK
  MClkSet(0x01, 'D'); //1分频DCOCLK
}
/************************ end of file *************************/
