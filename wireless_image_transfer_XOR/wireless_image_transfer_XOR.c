/*Program to display Image on Graphics LCD using AT89C52*/

#include<reg51.h>
#include<intrins.h>
#define dport P2
#include "glcd.h"
#include "key.h"



unsigned char c;



unsigned char rx();




void main()
{
	char v;
	int i,j,value,a,b,d;
	
	
	
	TMOD=0x20;			// selecting Timer 1, with mode 8bit auto reload.
	TH1=0xFD;			// setting baud rate = 9600
	SCON=0x50;			// setting the 8bit Control reg which control the SBUF with RC5
	TR1=1;				// starting the timer


	displayon();
	setstartline(0);
	clrlcd();
	
	while(1)
	{
		setcolumn(0);
		setpage(0);
		for(j=0;j<8;j++)
		{
			setpage(j);
			setcolumn(0);
			for(i=0;i<128;i++)
			{
				v=rx();
				a=v;
				b=key[j][i];
				d=b^a;
				value=d;
			
				if(c<64)
				{
					dport=value;
					cs1=1;cs2=0;
					rs=1;
					rw=0;
					en=1;
					_nop_(); 
					en=0	;
					c++;
				}
				else
				{ 
					setcolumn(c);
					dport=value;
					cs2=1;cs1=0;
					rs=1;
					rw=0;
					en=1;
					_nop_();  
					en=0	;
					c++;
				}
			}
		}
	
	}
	
} 



unsigned char rx()			
{
	unsigned char val; 			
	while(RI==0);
	val=SBUF;
	RI=0;
	return(val);    	
}