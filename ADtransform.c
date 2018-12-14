#include <reg52.h>
#include <intrins.h>  //?
#define unchar unsigned char
#define unint unsigned int

sbit dula = P2^6;   // u1锁存器的锁存端
sbit wela =P2^7;	// u2锁存器的锁存端
sbit adwr =P3^6;	// 定义 A/D 的WR端
sbit asrd =P3^7;	// 定义 A/D 的RD端

unchar code table[]={
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};
void delayms (unint xms)
{
	unint i, j;
	for (i=xms ; i>0; i--)
		for (j=110; j>0; j--);
}


void display(unchar bai , unchar shi ,unchar ge )
{
	dula=1;
	P0=table[bai];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0x7e;
	wela=0;
	delayms(5);

	dula=1;
	P0=table[shi];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0x7d;
	wela=0;
	delayms(5);

	dula=1;
	P0=table[ge];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0x7b;
	delayms(5);

}

void main ()
{
	unchar a,A1,A2,A3,adval;

	wela=1;
	P0=0x7f;   //置CSAD为0， 置通   0111 1111
	wela=0;

	while(1)
	{
		adwr=1;   //启动A/D转换器
		_nop_();
		adwr=0;
		_nop_();
		adwr=1;

		for (a=10; a>0; a--)    //显示放在这里就是为了为A/D转换留时间
		{
			display(A1,A2,A3);
		}

		P1=0xff;  //读取P1端口的值
		asrd=1;   //选通ADCS、
		_nop_();
		asrd=0;   // A/D读取使能
		_nop_();
		adval=P1;	//将P1口的数据读取出来
		asrd=1;

		A1=adval/100;  //提取个十百位的数字
		A2=adval%100/10;
		A3=adval%10;


	}



}

