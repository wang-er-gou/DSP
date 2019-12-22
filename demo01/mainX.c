#include<reg51.h>
#include<intrins.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

sbit switch1 = P3^0;
sbit switch2 = P3^1;
sbit switch3 = P3^2;
sbit switch4 = P3^3;

unsigned char *strCode="                I Love You!";

/*
  �����ⲿ����
*/
extern void delay_ms(int ms);
extern void init();
extern void write_cmd(unsigned char cmd8);
extern void write_str(int r, int c, char *str);
extern void write_data(unsigned char data8);

/**
* ˮƽ��������
*
* @return
*/
void h_scroll_words()
{
	int i;
	init();
	write_str(0,0, "    Example-1   ");
	while(1)
	{
		/*
		  fun1
		*/
		for(i = 0; i<strlen(strCode); i++)
		{
			write_str(1, 0, strCode + i);
			delay_ms(100);
		}
		
		if(switch1 != 0) break;
	}

}

/**
* ��������
*
* @return
*/
void random_words()
{
	int a,b,i;
	unsigned char tempStr[17];

	init();
	write_cmd(0x0F);
	write_str(0,0, "    Example-2   ");

	while(1)
	{
		//srand(TH0);
		a = rand()%10;
		b = rand()%10;
		sprintf(tempStr, "%d+%d=%d", a, b, a+b);
		write_cmd(0xC0|0x05);
		for(i = 0; i < 11; i++)
		{
			if(tempStr[i]) write_data(tempStr[i]); 
			else write_data(' ');
			delay_ms(150);
		}
		write_str(1, 0, "           ");
		delay_ms(150);
		if(switch2 != 0) break;
	}

}

/**
* ȫ����ʾ
*
* @return
*/
void all_str_code()
{
 	int i,j;
	init();
	write_cmd(0x0F);//0000_1111:��ʾ��/�ؿ��� 
	write_str(0,0, "    Example-3   "); 	
	while(1)
	{
		write_cmd(0xC0);
		for(i = 0x20; i <= 0xFF; i++)
		{
			if(switch3) return;
			if(i >= 0x80 && i < 0xa0) continue;

			if((++j) == 16)
			{
				write_str(1, 0, "           ");
				j = 0;
				//������������ӵڶ���д�������õ��ڶ��е�һ����ַ
				write_cmd(0xC0);
			}
			//if(i == 0xFF) i = 0x20;
			write_data(i);
			delay_ms(50);
		}
	
	}

}

/**
* �Զ����ַ���ʾ
*
* @return
*/
void character_str_code()
{
  	int i = 0;
  	unsigned char CC[] = {0x1F,0x11,0x1F,0x11,0x1F,0x11,0x1F,0x00};
  	init();
	write_cmd(0x0F); // 0000_1111:��ʾ���ؿ���
	write_str(0, 0, "    Example-4   ");
	write_cmd(0x40); //0100_0000:���ַ�������������ַ
	for(i = 0; i < 8; i++)
	{
		// ͨ������write_LCD_CMD(0x40); ������д��CGRAM
		write_data(CC[i]);	
	}
	while(1)
	{
		write_cmd(0xC0);
		for(i = 0; i < 16; i++)
		{
			if(switch4) return;
			write_data(0);
			delay_ms(50);
		}
		//��������ʾ������
		write_str(1, 0, "                ");
		delay_ms(150);
	}
	

}

/**
* ������ 
*/
void main()
{
	while(1)
	{
		if(switch1 == 0)
		{
			h_scroll_words();
		}
		else if(switch2 == 0)
		{
			random_words();
		}
		else if(switch3 == 0)
		{
			all_str_code();
		}
		else if(switch4 == 0)
		{
			character_str_code();
		}
	}
}