#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
uchar code table[]={
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};

uchar code keyvalue[]={
	0xee,0xde,0xbe,0x7e,
	0xed,0xdd,0xbd,0x7d,
	0xeb,0xdb,0xbb,0x7b,
	0xe7,0xd7,0xb7,0x77
};
uchar code rowv[]={
	0xfe,0xfd,0xfb,0xf7
};


void matrixkeyscan();
void delayms(uint);
void display(uchar);

void main()
{
	P0=0;
	dula=1;
	dula=0;
	
	P0=0xc0;  // 1100 0000
	wela=1;
	wela=0;

	while(1)
	{
		matrixkeyscan();
	}
}


void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}

void display(uchar num)
{
	P0 = table[num];
	dula = 1;
	dula = 0;
}


void matrixkeyscan()
{
	uchar temp,key;
	uint ii=0;
	uint jj=0;
	
	while(ii<4)
	{
		P3 = rowv[ii]; // 1111 1110   将第一行置于低电平，其余高电平
		temp = P3;  // 读取当前状态值P3，付给临时变量temp
		temp = temp & 0xf0;     // 1111 0000  
		if (temp != 0xf0)   // 主要判别前四位是否全是1  若不是1说明出现了按键动作
		{

			delayms(10);
			temp = P3;    //重新确认有按键按下  高位 不全为1 
			temp = temp & 0xf0;    

			if (temp != 0xf0)   
			{
				delayms(10);  // 延迟，去除震荡

				temp = P3;   // 重新获取最新的P3值
				
				jj=0;
				while (jj<16)
				{
					if (temp == keyvalue[jj])
					{
						key=jj;
						break;
					}
					jj++;

				}

				while (temp != 0xf0)  //  等待按键释放  恢复到全部为1
				{
					temp = P3;          // 检测按键
					temp = temp & 0xf0;   // 求与 下一次循环检测按键是否恢复
				}
			}
		}
		
		ii++;
	}
	display(key);  //显示
}
