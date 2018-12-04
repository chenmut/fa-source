#include "24l01.h"

const unsigned char TX_ADDRESS[TX_ADR_WIDTH] = { 0x34, 0x43, 0x10, 0x10, 0x01 }; //发送地址
const unsigned char RX_ADDRESS[RX_ADR_WIDTH] = { 0x34, 0x43, 0x10, 0x10, 0x01 };


//设置引脚, 包括：CS, SCL, MOSI, MISO
void NRF24L01_Init( void )
{
	wiringPiSetupPhys();
	
	pinMode( IRQ_PIN, INPUT );
	pinMode( CE_PIN, OUTPUT );
	pinMode( CSN_PIN, OUTPUT );
	pinMode( SCL_PIN, OUTPUT );
	pinMode( MOSI_PIN, OUTPUT );
	pinMode( MISO_PIN, INPUT );
	
	digitalWrite( SCL_PIN, LOW );
	digitalWrite( CSN_PIN, HIGH );
	digitalWrite( CE_PIN, LOW );
	
	#if SPIEMULATE
		pinMode( SCL_PIN, OUTPUT );
		pinMode( MOSI_PIN, OUTPUT );
		pinMode( MISO_PIN, INPUT );
		
		digitalWrite( SCL_PIN, LOW );
	#else 	
		wiringPiSPISetup( 0, 1000000);
	#endif
	
	//digitalWrite( MOSI_PIN, LOW );
}



//检测24L01是否存在
//返回值:0，成功;1，失败	
unsigned char NRF24L01_Check(void)
{
	unsigned char u8Buf[5] = { 0XA5, 0XA5, 0XA5, 0XA5, 0XA5 };
	unsigned char i;
	
	NRF24L01_WriteBuf( NRF_WRITE_REG + TX_ADDR, u8Buf, 5 );	//写入5个字节的地址.
	
	memset( u8Buf, 0, sizeof( u8Buf ));
	NRF24L01_ReadBuf( TX_ADDR, u8Buf, 5 ); 	//读出写入的地址
	//printf("the buff is %0x\n",u8Buf[0]);
	for ( i = 0; i < 5; i++ )
	{
		if ( u8Buf[i] != 0XA5 )
		{
			break;
		}
	}
	
	if( i != 5 )
	{
		return 1;	//检测24L01错误	
	}
	
	return 0;		//检测到24L01
}


//SPI写寄存器
//u8Reg:指定寄存器地址
//u8Value:写入的值
unsigned char NRF24L01_WriteReg( unsigned char u8Reg, unsigned char u8Value )
{
	unsigned char u8Status;
	
   	digitalWrite( CSN_PIN, LOW );      	//使能SPI传输
	
  	u8Status = SPI_ReadWriteByte( u8Reg );	//发送寄存器号 
  	u8Status = SPI_ReadWriteByte( u8Value ); //写入寄存器的值
	
  	digitalWrite( CSN_PIN, HIGH );          //禁止SPI传输	
	
  	return u8Status;       			//返回状态值
}


//读取SPI寄存器值
//u8Reg:要读的寄存器
unsigned char NRF24L01_ReadReg( unsigned char u8Reg )
{
	unsigned char u8RegVal;	
    
 	digitalWrite( CSN_PIN, LOW );      	//使能SPI传输
	
  	u8RegVal = SPI_ReadWriteByte( u8Reg );   		//发送寄存器号
  	u8RegVal = SPI_ReadWriteByte( 0XFF );	//读取寄存器内容
	
  	digitalWrite( CSN_PIN, HIGH );     	//禁止SPI传输
	
  	return u8RegVal;           //返回状态值
}	


//在指定位置读出指定长度的数据
//u8Reg:寄存器(位置)
//*u8pBuf:数据指针
//u8Len:数据长度
//返回值,此次读到的状态寄存器值 
unsigned char NRF24L01_ReadBuf( unsigned char u8Reg, unsigned char *u8pBuf, unsigned char u8Len )
{
	unsigned char u8Status, u8Ctr;
	
  	digitalWrite( CSN_PIN, LOW );           //使能SPI传输
	
  	u8Status = SPI_ReadWriteByte( u8Reg );	//发送寄存器值(位置),并读取状态值   	   
 	for( u8Ctr = 0; u8Ctr < u8Len; u8Ctr++ )
	{
		u8pBuf[ u8Ctr ] = SPI_ReadWriteByte( 0XFF );	//读出数据
	}
	
  	digitalWrite( CSN_PIN, HIGH );       //关闭SPI传输
	
  	return u8Status;        //返回读到的状态值
}


//在指定位置写指定长度的数据
//u8Reg:寄存器(位置)
//*u8pBuf:数据指针
//u8Len:数据长度
//返回值,此次读到的状态寄存器值
unsigned char NRF24L01_WriteBuf( unsigned char u8Reg, unsigned char *u8pBuf, unsigned char u8Len )
{
	unsigned char u8Status,u8Ctr;	
    
 	digitalWrite( CSN_PIN, LOW );          //使能SPI传输
	
  	u8Status = SPI_ReadWriteByte( u8Reg );//发送寄存器值(位置),并读取状态值
  	for( u8Ctr = 0; u8Ctr < u8Len; u8Ctr++ )
	{
		SPI_ReadWriteByte( *u8pBuf++ ); //写入数据	 
	}
	
  	digitalWrite( CSN_PIN, HIGH );       //关闭SPI传输
	
  	return u8Status;          //返回读到的状态值
}


//该函数配置NRF24L01部分寄存器
void NRF24L01_ModeConfig( void )
{
	/* digitalWrite( CSN_PIN, HIGH );
	delayMicroseconds( 10 ); */
	
	NRF24L01_WriteReg( NRF_WRITE_REG + EN_AA, 0x01 );    	//使能通道0的自动应答    
  	NRF24L01_WriteReg( NRF_WRITE_REG + EN_RXADDR, 0x01 );	//使能通道0的接收地址  	 
  	NRF24L01_WriteReg( NRF_WRITE_REG + RF_CH, 40 );	   		//设置RF通信频率	
	NRF24L01_WriteReg( NRF_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH );   //选择通道0的有效数据宽度 	
  	NRF24L01_WriteReg( NRF_WRITE_REG + RF_SETUP, 0x0f );	//设置TX发射参数,0dBm增益,2Mbps,低噪声增益开启   
}

  
//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了		   
void NRF24L01_RXMode( void )
{
	digitalWrite( CE_PIN, LOW );	
	
	NRF24L01_WriteBuf( NRF_WRITE_REG + RX_ADDR_P0, (unsigned char*)RX_ADDRESS, RX_ADR_WIDTH ); //设置RX节点地址,主要为了使能ACK
	
	NRF24L01_ModeConfig();
  	NRF24L01_WriteReg( NRF_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH );	//选择通道0的有效数据宽度 
	//delayMicroseconds( 150 );
	
  	NRF24L01_WriteReg( NRF_WRITE_REG + CONFIG, 0x0f );		//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
	
  	digitalWrite( CE_PIN, HIGH ); 	//CE为高,进入接收模式 
}	


//该函数初始化NRF24L01到TX模式
//设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR
//PWR_UP,CRC使能
//当CE变高后,即进入RX模式,并可以接收数据了		   
//CE为高大于10us,则启动发送.	 
void NRF24L01_TXMode( void )
{														 
	digitalWrite( CE_PIN, LOW );
	
  	NRF24L01_WriteBuf( NRF_WRITE_REG + TX_ADDR, (unsigned char*)TX_ADDRESS, TX_ADR_WIDTH );	//写TX节点地址  
  	NRF24L01_WriteBuf( NRF_WRITE_REG + RX_ADDR_P0, (unsigned char*)RX_ADDRESS, RX_ADR_WIDTH ); //设置RX节点地址,主要为了使能ACK
	
	NRF24L01_ModeConfig();
	NRF24L01_WriteReg( NRF_WRITE_REG + SETUP_RETR, 0x1a );	//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
  	//NRF24L01_WriteReg( NRF_WRITE_REG + SETUP_RETR, 0x00 );
	//delayMicroseconds( 150 );
	
  	NRF24L01_WriteReg( NRF_WRITE_REG + CONFIG, 0x0e );   	//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	
	digitalWrite( CE_PIN, HIGH );	//CE为高,10us后启动发送
}


//启动NRF24L01发送一次数据
//u8TxBuf:待发送数据首地址
//返回值:发送完成状况
unsigned char NRF24L01_TxPacket( unsigned char *u8TxBuf )
{
	unsigned char u8Sta = 0;
	
	digitalWrite( CE_PIN, LOW );
	delayMicroseconds( 10 );
	
  	NRF24L01_WriteBuf( WR_TX_PLOAD, u8TxBuf, TX_PLOAD_WIDTH );	//写数据到TX u8Buf  32个字节
	
 	digitalWrite( CE_PIN, HIGH );	//启动发送	
	delayMicroseconds( 15 );
	
	while(( digitalRead( IRQ_PIN )) != 0 );		//等待发送完成
	
	u8Sta = NRF24L01_ReadReg( STATUS );  	//读取状态寄存器的值	   
	NRF24L01_WriteReg( NRF_WRITE_REG + STATUS, u8Sta ); 	//清除TX_DS或MAX_RT中断标志
	
	if( u8Sta & MAX_TX )		//达到最大重发次数
	{
		NRF24L01_WriteReg( FLUSH_TX, 0xff );	//清除TX FIFO寄存器 
		return MAX_TX; 
	}
	
	if( u8Sta & TX_OK )	//发送完成
	{
		return TX_OK;
	}
		
	return 0xff;	//其他原因发送失败
}


//启动NRF24L01发送一次数据
//u8TxBuf:待发送数据首地址
//返回值:0，接收完成；其他，错误代码
unsigned char NRF24L01_RxPacket( unsigned char *u8pRxBuf )
{
	unsigned char u8Sta;	
	
	u8Sta = NRF24L01_ReadReg( NRF_READ_REG + STATUS );  //读取状态寄存器的值    	 
	NRF24L01_WriteReg( NRF_WRITE_REG + STATUS, u8Sta ); 	//清除TX_DS或MAX_RT中断标志
	
	if( u8Sta & RX_OK )	//接收到数据
	{
		NRF24L01_ReadBuf( RD_RX_PLOAD, u8pRxBuf, RX_PLOAD_WIDTH );	//读取数据
		NRF24L01_WriteReg( FLUSH_RX, 0xff );	//清除RX FIFO寄存器 
		
		return 0; 
	}	
	
	return 1;	//没收到任何数据
}

//-----------------------------------------
void NRF24L01_Command( unsigned char channel, unsigned char command, unsigned char command_data )
{
	unsigned char data[33];
	data[0] = command;
		
	if ( command_data )
	{
		data[1] = command_data;
	}
	printf("TX_DATA : %8d%8d\r\n", data[0], data[1] );
	
	if ( command_data )
	{
		wiringPiSPIDataRW( channel, data, 2 );
	}
	else
	{
		wiringPiSPIDataRW( channel, data, 1 );
	}
	printf("RX_DATA : %8d%8d\r\n", data[0], data[1] );
}

//SPI写寄存器
//command:指定寄存器地址
//command_data:写入的值
void NRF24L01_WriteRegCsChange( unsigned char channel, unsigned char command, unsigned char command_data)
{
	unsigned char data[32];
	data[0] = command;
	
   	digitalWrite( CSCAHNGEPIN, LOW );      	//使能SPI传输
	
  	if ( command_data )
	{
		data[1] = command_data;
	}
	printf("TX_DATA : %8x%8x\r\n", data[0], data[1] );
	
	if ( command_data )
	{
		wiringPiSPIDataRW1( channel, data, 2, 1 );		//cs_change == 1
	}
	else
	{
		wiringPiSPIDataRW1( channel, data, 1, 1 );
	}
	printf("RX_DATA : %8x%8x\r\n", data[0], data[1] );
	
  	digitalWrite( CSCAHNGEPIN, HIGH );          //禁止SPI传输	
}
