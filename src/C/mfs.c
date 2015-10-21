/*---------------------------------------------*/
/*                    mfs.c                    */
/*---------------------------------------------*/
/*            MFS TX/RX IRQHandlers            */
/*---------------------------------------------*/

#include "FM3_type2.h"

void mrbgem_Handler_Trap(uint8_t mfs);

void MFS_TX_IRQHandler_i2cmaster (uint8_t mfs) __attribute__((weak, alias("mrbgem_Handler_Trap")));
void MFS_TX_IRQHandler_uart (uint8_t mfs) __attribute__((weak, alias("mrbgem_Handler_Trap")));
void MFS_RX_IRQHandler_uart (uint8_t mfs) __attribute__((weak, alias("mrbgem_Handler_Trap")));

/*-------------------------*/
/*         MFS 0ch         */
/*-------------------------*/

void MFS0_RX_IRQHandler (void)
{
	uint8_t md = (MFS0_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_RX_IRQHandler_uart(0);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			break;
		default:
			break;
	}
}
 
void MFS0_TX_IRQHandler (void)
{
	uint8_t md = (MFS0_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_TX_IRQHandler_uart(0);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			MFS_TX_IRQHandler_i2cmaster(0);		break;
		default:
			break;
	}
}

/*-------------------------*/
/*         MFS 1ch         */
/*-------------------------*/
 
void MFS1_RX_IRQHandler (void)
{
	uint8_t md = (MFS1_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_RX_IRQHandler_uart(1);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			break;
		default:
			break;
	}
}
 
void MFS1_TX_IRQHandler (void)
{
	uint8_t md = (MFS1_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_TX_IRQHandler_uart(1);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			MFS_TX_IRQHandler_i2cmaster(1);		break;
		default:
			break;
	}
}

/*-------------------------*/
/*         MFS 2ch         */
/*-------------------------*/
 
void MFS2_RX_IRQHandler (void)
{
	uint8_t md = (MFS2_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_RX_IRQHandler_uart(2);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			break;
		default:
			break;
	}
}
 
void MFS2_TX_IRQHandler (void)
{
	uint8_t md = (MFS2_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_TX_IRQHandler_uart(2);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			MFS_TX_IRQHandler_i2cmaster(2);		break;
		default:
			break;
	}
}

/*-------------------------*/
/*         MFS 3ch         */
/*-------------------------*/
 
void MFS3_RX_IRQHandler (void)
{
	uint8_t md = (MFS3_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_RX_IRQHandler_uart(3);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			break;
		default:
			break;
	}
}
 
void MFS3_TX_IRQHandler (void)
{
	uint8_t md = (MFS3_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_TX_IRQHandler_uart(3);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			MFS_TX_IRQHandler_i2cmaster(3);		break;
		default:
			break;
	}
}

/*-------------------------*/
/*         MFS 4ch         */
/*-------------------------*/
 
void MFS4_RX_IRQHandler (void)
{
	uint8_t md = (MFS4_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_RX_IRQHandler_uart(4);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			break;
		default:
			break;
	}
}
 
void MFS4_TX_IRQHandler (void)
{
	uint8_t md = (MFS4_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_TX_IRQHandler_uart(4);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			MFS_TX_IRQHandler_i2cmaster(4);		break;
		default:
			break;
	}
}

/*-------------------------*/
/*         MFS 5ch         */
/*-------------------------*/
 
void MFS5_RX_IRQHandler (void)
{
	uint8_t md = (MFS5_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_RX_IRQHandler_uart(5);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			break;
		default:
			break;
	}
}
 
void MFS5_TX_IRQHandler (void)
{
	uint8_t md = (MFS5_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_TX_IRQHandler_uart(5);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			MFS_TX_IRQHandler_i2cmaster(5);		break;
		default:
			break;
	}
}

/*-------------------------*/
/*         MFS 6ch         */
/*-------------------------*/

void MFS6_RX_IRQHandler (void)
{
	uint8_t md = (MFS6_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_RX_IRQHandler_uart(6);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			break;
		default:
			break;
	}
}
 
void MFS6_TX_IRQHandler (void)
{
	uint8_t md = (MFS6_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_TX_IRQHandler_uart(6);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			MFS_TX_IRQHandler_i2cmaster(6);		break;
		default:
			break;
	}
}

/*-------------------------*/
/*         MFS 7ch         */
/*-------------------------*/

void MFS7_RX_IRQHandler (void)
{
	uint8_t md = (MFS7_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_RX_IRQHandler_uart(7);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			break;
		default:
			break;
	}
}
 
void MFS7_TX_IRQHandler (void)
{
	uint8_t md = (MFS7_SMR & 0xE0) >> 5;
	
	switch(md)
	{
		case 0:		/* asynchronous normal mode */
			MFS_TX_IRQHandler_uart(7);	break;
		case 1:		/* asynchronous multiprocessor mode */
			break;
		case 2:		/* clock synchronization mode */
			break;
		case 3:		/* LIN communication mode */
			break;
		case 4:		/* I2C mode */
			MFS_TX_IRQHandler_i2cmaster(7);		break;
		default:
			break;
	}
}

/*----------------------------------/
/      Unexpected mrbgems Trap      /
/----------------------------------*/

void mrbgem_Handler_Trap(uint8_t mfs)
{
	for(;;);
}