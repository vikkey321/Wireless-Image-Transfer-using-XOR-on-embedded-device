/*Program to display Image on Graphics LCD using AT89C52*/


#define dport P2

#include "font.h"
#include "font2.h"

						
sbit rs=P3^4;
sbit rw=P3^3;
sbit en=P3^2;
sbit cs1=P3^5;
sbit cs2=P3^6;

unsigned char c,z=0;


void ctrloff()
{
	rs=0;
	rw=0;
	en=0;
	cs1=0;
	cs2=0;
}

//DELAY FUNCTION
void delay(unsigned int j)
{
	unsigned int i;
	for(i=0;i<j;i++);
}
			 
void displayon()
{ 
	ctrloff();
	dport=0x3f;  
	cs1=1;cs2=1;
	rw=0;rs=0;
	en=1;
	_nop_();  
	en=0;
}

void displayoff()
{
	ctrloff();
	dport=0x3e;
	cs1=1;cs2=1;
	rs=0;rw=0;
	en=1;
	_nop_(); 
	en=0;
}
 
void setcolumn(unsigned char y)
{
	if(y<64)
	{
		ctrloff();
		c=y;
		dport=0x40|(y&63);	  //0x40 represents Column 0
		cs1=1;cs2=0;
		rs=0;
		rw=0;
		en=1;
		_nop_();  
		en=0;
	}
	else
	{ 
		c=y;
		dport=0x40|((y-64)&63);	  //0x40 represents Column 0
		cs2=1;cs1=0;
		rs=0;
		rw=0;
		en=1;
		_nop_(); 
		en=0;
  
	}
}

void setpage(unsigned char x)
{
	ctrloff();
	dport= 0xb8|x;	   //0xb8 represents Page 0
	cs1=1;
	cs2=1;
	rs=0;
	rw=0;
	en=1;
	_nop_();
	en=0; 
}

//Function to Scroll Strings
void setstartline(unsigned char z)			 
{
	ctrloff();
	dport=0xc0|z;	   //0xc0 represents Line 0
	cs1=1;
	cs2=1;
	rs=0;
	rw=0;
	en=1;
	_nop_();  
	en=0;		  
} 

void lcddata(unsigned char *value,unsigned int limit)
{
	unsigned int i;
	for(i=0;i<limit;i++)
	{
		if(c<64)
		{
			dport=value[i];
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
			dport=value[i];
			cs2=1;cs1=0;
			rs=1;
			rw=0;
			en=1;
			_nop_();  
			en=0	;
			c++;
		}
		if(c>127)
	           return;
	}
}

void lcdputs1(unsigned char y,unsigned char x,unsigned char *str)
{
	unsigned char i;
	unsigned int a;
	setcolumn(y);
	setpage(x);
	for(i=0;str[i]!=0;i++)
	{
		a=(*(str+i));
		a*=8;
		lcddata(&Character8x8[a],8);
	}
}

void lcdputs2(unsigned char y,unsigned char x,unsigned char *str)
{
	unsigned char i;
	unsigned int a;
	setcolumn(y);
	setpage(x);
	for(i=0;str[i]!=0;i++)
	{
		a=(*(str+i)-32);
		a*=5;
		lcddata(&font5x7[a],5);
	}
}

//Function to display Image
void picture(unsigned char * val)
{
	unsigned char j;
	setcolumn(0);
	setpage(0);
	for (j=0;j<8;j++)
	{
		setpage(j);
		setcolumn(0);
		lcddata(&val[(j*128)],128);				 
	}
}

void clrlcd()
{
    unsigned char i,j;
    for (i=0;i < 8;i++)
    {
	setpage(i);
	setcolumn(0);
        for (j= 0 ;j < 128; j++)
        lcddata(&z,1);
    }
}


