#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int   
uchar code mum[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; //??
//???????????,138??
sbit s1=P2^2;
sbit s2=P2^3;
sbit s3=P2^4;
/*k1 ????, k2 ?? , k3 ?????, k4 ??? */
sbit k1=P3^0;          
sbit k2=P3^1;
sbit k3=P3^2;
sbit k4=P3^3;
sbit l1=P2^1;//?????
sbit buzzer=P1^5;
sbit led=P2^0;
uint hour=0;
uint min=0;
uint sec=0;
uint s=0;
uint m=0;
uint h=0;
uint ss=0;
uint ih=23;
uint im=23;
uint is=59;
uint n=0;//????
void delayms(uint k)           // ????
{
        uint i,j;
        for(i=k;i>0;i--)
                for(j=110;j>0;j--);
}

void display(uchar zs,uchar zm, uchar zh)            //???????
{         
  s1=1;	//P2? S ????????,138??
  s2=1;
  s3=1;
  P0=mum[zh/10];  //P0?????? ,??????? 
  delayms(5);
  s1=0;
  s2=1;
  s3=1;
  P0=mum[zh%10]+0x80;           // ???????????
  delayms(5);
  s1=1;
  s2=0;
  s3=1;
  P0=0x40;         
  delayms(5);
  s1=0;
  s2=0;
  s3=1;
  P0=mum[zm/10];         //??????
  delayms(5);
  s1=1;
  s2=1;
  s3=0;
  P0=mum[zm%10]+0x80;           //?????????
  delayms(5);
  s1=0;
  s2=1;
  s3=0;     
  P0=0x40;   
  delayms(5);
  s1=1;
  s2=0;
  s3=0;
  P0=mum[zs/10];  //????
  delayms(5);
  s1=0;
  s2=0;
  s3=0;     
  P0=mum[zs%10];   //????
  delayms(5);
 
  
  
}
void keyscan_settime()                  // ??????
{
        uchar st,mt,ht;
        if(k1==0)
        {
                delayms(10);  // ????????????????????
                if(k1==0)
                {
                st=sec,mt=min,ht=hour;
                TR0=0;                 // ?????
                while(k1==0)         // ??????
                {       
                        display(st,mt,ht);                       
                        if(k3==0)
                        {
                                delayms(10);
                                if(k3==0)          
                                {
                                while(!k3);
                                ss++;
                                if(ss==3)        
									ss=0;
                                }
                        }
                        /* ?? ss ??????? */
                        if(k4==0)                // ??
                                {
                                         delayms(10);//??
                                        if(k4==0)
                                        {
                                        while(!k4);
                                        switch(ss)
                                        {
                                        case 0:st++;if(st==60)st=0;break;
                                        case 1:mt++;if(mt==60)mt=0;break;
                                        case 2:ht++;if(ht==24)ht=0;break;       
                                        default :;                                               
                                        }
                                        }       
                                }
                        
							
                                }
                        TR0=1;  // ????,?????
                        sec=st,min=mt,hour=ht;                                                       
                        }                                               
                }               
                display(sec,min,hour);
}
//?????????
void keyscan_time()// ??????
{
        if(k2==0)
        {
                delayms(10);               
                if(k2==0)
                {
				delayms(10);
                s=sec;m=min;h=hour;
                while(k2==0)         // ??????
                {
                        display(s,m,h);
                        if(k3==0)
                        {
                                delayms(10);
                                if(k3==0)          
                                {
                                while(!k3);
                                ss++;
                                if(ss==3)        ss=0;
                                }
                        }
                        /* ?? ss ??????? */
                        if(k4==0)                // ? ?
                                {
                                         delayms(10);
                                        if(k4==0)
                                        {
                                        while(!k4);
                                        switch(ss)
                                        {
                                        case 0:s++;if(s==60)s=0;break;
                                        case 1:m++;if(m==60)m=0;break;
                                        case 2:h++;if(h==24)h=0;break;       
                                        default :;                                               
                                        }
										is=s;
										im=m;
										ih=h;
                                        }       
                                }
                       
                                }                                               
                        }
        }

}
void timecontrol()       
{
        sec++;
        if(sec==60)  // ? sec ? 60 ??,? min ??
  {
                sec=0;
                min++;
                if(min==60)  // ? min ? 60 ??,? hour ??
                {
                        min=0;
                        hour++;
                        if(hour==24)  // ?? hour ?? 24 ???
                        hour=0;
                }
        }
}
void T0_ms()  interrupt 1         // ??????
{       uint count;
        TH0=(65536-45872)/256;                // ?????
        TL0=(65536-45872)%256;
        count++;
        if(count==20)                 // ?? 1s ??????
        {  
                count=0;
                timecontrol();
        }
		if( k4==0 )
	{
		is=s;
		im=m;
		ih=h;
        l1=1;
}
	}
void reply()//????
{
if( k4==0 )
	{
		is=s;
		im=m;
		ih=h;
        l1=1;
		
        }
	else 
		{
		im=im+1;
		l1=0;
		if(im==60)  // ? min ? 60 ??,? hour ??
                {
                        im=0;
                        ih++;
                        if(ih==24)  // ?? hour ?? 24 ???
                        ih=0;
                }
		}
}
 void buz() 
{
if((hour==ih)&&(min==im)&&(sec==is))
        {
		n=125;
		while(n--)
		{buzzer=1;
		led=0;//led???
        delayms(20);
        buzzer=0;
		led=1;//??
		}
		reply();
        }
}


	


void main()
{       
        TMOD=0x01;                                // ??? 0 ????? 1
        TH0=(65536-45872)/256;           // ???, 50ms
        TL0=(65536-45872)%256;
        EA=1;                  // ?????
        ET0=1;                 //T0 ????
        TR0=1; 	// ???? 0    
	    while(1)
        {
                keyscan_settime();
                keyscan_time();  
                if((hour==ih)&&(min==im)&&(sec==is))
                {
					buz();
					
					
				}	
					
        }
}

