#include "24l01.h"

const unsigned char TX_ADDRESS[TX_ADR_WIDTH] = { 0x34, 0x43, 0x10, 0x10, 0x01 }; //发送地址
const unsigned char RX_ADDRESS[RX_ADR_WIDTH] = { 0x34, 0x43, 0x10, 0x10, 0x01 };

	 	 
//SPI写寄存器
//uc_reg:指定寄存器地址
//uc_value:写入的值
unsigned char NRF24L01_Write_Reg( unsigned char uc_reg, unsigned char uc_value )
{
	unsigned char uc_status;
	
   	digitalWrite( CSN_PIN, LOW );      	//使能SPI传输
  	uc_status = SPI_ReadWriteByte( uc_reg );	//发送寄存器号 
  	SPI_ReadWriteByte( uc_value );      		//写入寄存器的值
  	digitalWrite( CSN_PIN, HIGH );            	//禁止SPI传输	
	
  	return uc_status;       			//返回状态值
}


//读取SPI寄存器值
//uc_reg:要读的寄存器
unsigned char NRF24L01_Read_Reg( unsigned char uc_reg )
{
	unsigned char uc_reg_val;	
    
 	digitalWrite( CSN_PIN, LOW );      	//使能SPI传输		
  	SPI_ReadWriteByte( uc_reg );   		//发送寄存器号
  	uc_reg_val = SPI_ReadWriteByte( 0XFF );	//读取寄存器内容
  	digitalWrite( CSN_PIN, HIGH );     	//禁止SPI传输
	
  	return uc_reg_val;           //返回状态值
}	


//在指定位置读出指定长度的数据
//uc_reg:寄存器(位置)
//*ucp_Buf:数据指针
//uc_len:数据长度
//返回值,此次读到的状态寄存器值 
unsigned char NRF24L01_Read_Buf( unsigned char uc_reg, unsigned char *ucp_Buf, unsigned char uc_len )
{
	unsigned char uc_status, uc_ctr;
	
  	digitalWrite( CSN_PIN, LOW );           //使能SPI传输
	
  	uc_status = SPI_ReadWriteByte( uc_reg );	//发送寄存器值(位置),并读取状态值   	   
 	for( uc_ctr = 0; uc_ctr < uc_len; uc_ctr++ )
	{
		ucp_Buf[uc_ctr] = SPI_ReadWriteByte( 0XFF );//读出数据
	}
	
  	digitalWrite( CSN_PIN, HIGH );       //关闭SPI传输
	
  	return uc_status;        //返回读到的状态值
}


//在指定位置写指定长度的数据
//uc_reg:寄存器(位置)
//*ucp_Buf:数据指针
//uc_len:数据长度
//返回值,此次读到的状态寄存器值
unsigned char NRF24L01_Write_Buf( unsigned char uc_reg, unsigned char *ucp_Buf, unsigned char uc_len )
{
	unsigned char uc_status,uc_ctr;	
    
 	digitalWrite( CSN_PIN, LOW );          //使能SPI传输
	
  	uc_status = SPI_ReadWriteByte( uc_reg );//发送寄存器值(位置),并读取状态值
  	for( uc_ctr = 0; uc_ctr < uc_len; uc_ctr++ )
	{
		SPI_ReadWriteByte( *ucp_Buf++ ); //写入数据	 
	}
	
  	digitalWrite( CSN_PIN, HIGH );       //关闭SPI传输
	
  	return uc_status;          //返回读到的状态值
}

				   
//启动NRF24L01发送一次数据
//uc_txbuf:待发送数据首地址
//返回值:发送完成状况
unsigned char NRF24L01_TxPacket( unsigned char *uc_txbuf )
{
	unsigned char uc_sta;
	
	digitalWrite( CE_PIN, LOW );
  	NRF24L01_Write_Buf( WR_TX_PLOAD, uc_txbuf, TX_PLOAD_WIDTH );	//写数据到TX BUF  32个字节
	
 	digitalWrite( CE_PIN, HIGH );	//启动发送	   
	while(( digitalRead( IRQ_PIN )) != 0);			//等待发送完成
	
	uc_sta = NRF24L01_Read_Reg( STATUS );  	//读取状态寄存器的值	   
	NRF24L01_Write_Reg( NRF_WRITE_REG + STATUS, uc_sta ); 	//清除TX_DS或MAX_RT中断标志
	if( uc_sta & MAX_TX )		//达到最大重发次数
	{
		NRF24L01_Write_Reg( FLUSH_TX, 0xff );	//清除TX FIFO寄存器 
		return MAX_TX; 
	}
	
	if( uc_sta & TX_OK )	//发送完成
	{
		return TX_OK;
	}
	
	return 0xff;	//其他原因发送失败
}


//启动NRF24L01发送一次数据
//uc_txbuf:待发送数据首地址
//返回值:0，接收完成；其他，错误代码
unsigned char NRF24L01_RxPacket( unsigned char *ucp_rxbuf )
{
	unsigned char uc_sta;	
	
	uc_sta = NRF24L01_Read_Reg( STATUS );  //读取状态寄存器的值    	 
	NRF24L01_Write_Reg( NRF_WRITE_REG + STATUS, uc_sta ); 	//清除TX_DS或MAX_RT中断标志
	if( uc_sta & RX_OK )	//接收到数据
	{
		NRF24L01_Read_Buf( RD_RX_PLOAD, ucp_rxbuf, RX_PLOAD_WIDTH );	//读取数据
		NRF24L01_Write_Reg( FLUSH_RX, 0xff );	//清除RX FIFO寄存器 
		
		return 0; 
	}	
	
	return 1;	//没收到任何数据
}

					    
//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了		   
int NRF24L01_RX_Mode( void )
{
	digitalWrite( CE_PIN, LOW );	
	
  	NRF24L01_Write_Buf( NRF_WRITE_REG +	RX_ADDR_P0, (unsigned char*)RX_ADDRESS, RX_ADR_WIDTH );	//写RX节点地址 
	
  	NRF24L01_Write_Reg( NRF_WRITE_REG +	EN_AA, 0x01 );    //使能通道0的自动应答    
  	NRF24L01_Write_Reg( NRF_WRITE_REG +	EN_RXADDR, 0x01 );	//使能通道0的接收地址  	 
  	NRF24L01_Write_Reg( NRF_WRITE_REG +	RF_CH, 40 );	     //设置RF通信频率		  
  	NRF24L01_Write_Reg( NRF_WRITE_REG +	RX_PW_P0, RX_PLOAD_WIDTH );	//选择通道0的有效数据宽度 	    
  	NRF24L01_Write_Reg( NRF_WRITE_REG +	RF_SETUP, 0x0f );	//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
  	NRF24L01_Write_Reg( NRF_WRITE_REG +	CONFIG, 0x0f );	//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
	
  	digitalWrite( CE_PIN, HIGH ); 	//CE为高,进入接收模式 
	
	return 0;
}	

					 
//该函数初始化NRF24L01到TX模式
//设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR
//PWR_UP,CRC使能
//当CE变高后,即进入RX模式,并可以接收数据了		   
//CE为高大于10us,则启动发送.	 
int NRF24L01_TX_Mode( void )
{														 
	digitalWrite( CE_PIN, LOW );
	
  	NRF24L01_Write_Buf( NRF_WRITE_REG + TX_ADDR, (unsigned char*)TX_ADDRESS, TX_ADR_WIDTH );	//写TX节点地址 
  	NRF24L01_Write_Buf( NRF_WRITE_REG + RX_ADDR_P0, (unsigned char*)RX_ADDRESS, RX_ADR_WIDTH ); //设置TX节点地址,主要为了使能ACK	  
                                        
  	NRF24L01_Write_Reg( NRF_WRITE_REG + EN_AA, 0x01 );     //使能通道0的自动应答    
  	NRF24L01_Write_Reg( NRF_WRITE_REG + EN_RXADDR, 0x01 ); //使能通道0的接收地址  
  	NRF24L01_Write_Reg( NRF_WRITE_REG + SETUP_RETR, 0x1a );	//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
  	NRF24L01_Write_Reg( NRF_WRITE_REG + RF_CH, 40 );       //设置RF通道为40
  	NRF24L01_Write_Reg( NRF_WRITE_REG + RF_SETUP, 0x0f );  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
  	NRF24L01_Write_Reg( NRF_WRITE_REG + CONFIG, 0x0e );    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	
	digitalWrite( CE_PIN, HIGH );	//CE为高,10us后启动发送
	
	return 0;
}

 
