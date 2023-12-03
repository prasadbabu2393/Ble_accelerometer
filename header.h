#include<LPC21XX.H>
int m[]={15,30,60,0,15};
void uart0_init(int baud)
{
	int temp=0.pclk=0;
	pclk=m[VPBDIV]*1000000;
	if(VPBDIV!=3)
		temp=(pclk/(16*baud));
	PINSEL0=0x5;
	U0LCR=0x83;
	U0DLL=temp&0x7FF;
	U0DLM=(temp>>8)&0x7ff;
	U0LCR=0x03;
}
void uart0_tx(char data)
{
	U0THR=data;
	while(((U0LSR>>5)&1)==0);
}
char uart0_rx(void)
{
	while((U0LSR&1)==0)
		return U0RBR;
}

