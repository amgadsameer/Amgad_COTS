/*********************************************************************/
/*********************************************************************/
/******** Author:    Amgad Samir   ***********************************/
/******** Component: TWI           ***********************************/
/******** Layer:     MCAL          ***********************************/
/******** Version:   1.0           ***********************************/
/*********************************************************************/
/*********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"

#include "TWI_interface.h"
#include "TWI_config.h"
#include "TWI_private.h"
#include "TWI_reg.h"

/*In case of the master will not being addressed, pass the address parameter as zero*/
void TWI_voidMasterInit(uint8 Copy_u8Address)
{
	/*Set node address*/
	if(Copy_u8Address != 0u)
	{
		TWAR = Copy_u8Address << 1u;
	}

	/*CPU frequency = 16 MHZ, prescaler =0 , Communication frequency = 400KHz*/
	CLR_BIT(TWSR, TWSR_TWPS0);
	CLR_BIT(TWSR, TWSR_TWPS1);
	TWBR = 12u;

	/*Enable acknowledge*/
	SET_BIT(TWCR, TWCR_TWEA);

	/*TWI enable*/
	SET_BIT(TWCR, TWCR_TWEN);
}

void TWI_voidSlaveInit(uint8 Copy_u8Address)
{
	/*Set node address*/
	TWAR = Copy_u8Address << 1u;

	/*TWI enable*/
	SET_BIT(TWCR, TWCR_TWEN);
}

TWI_ErrorStatus_t TWI_SendStartCondition(void)
{
	TWI_ErrorStatus_t Local_Error = NoError;

	/*Set start condition bit*/
	SET_BIT(TWCR, TWCR_TWSTA);

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the previous action finishes and the interrupt flag is raised again*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != START_ACK)
	{
		Local_Error = StartCondErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}

TWI_ErrorStatus_t TWI_SendRepeatedStart(void)
{
	TWI_ErrorStatus_t Local_Error = NoError;

	/*Set start condition bit*/
	SET_BIT(TWCR, TWCR_TWSTA);

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the previous action finishes and the interrupt flag is raised again*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != REP_START_ACK)
	{
		Local_Error = RepStartErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}

TWI_ErrorStatus_t TWI_SendSlaveAdressWithWrite(uint8 Copy_u8SlaveAddress)
{
	TWI_ErrorStatus_t Local_Error = NoError;

	/*Set the slave address into the data register*/
	TWDR = Copy_u8SlaveAddress << 1u ;

	/*Clear bit 0 for write request*/
	CLR_BIT(TWDR, 0u);

	/*Clear the start condition bit*/
	CLR_BIT(TWCR, TWCR_TWSTA);

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the previous action finishes and the interrupt flag is raised again*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_Error = SlaveAddressWithWriteErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;

}

TWI_ErrorStatus_t TWI_SendSlaveAdressWithRead(uint8 Copy_u8SlaveAddress)
{
	TWI_ErrorStatus_t Local_Error = NoError;

	/*Set the slave address into the data register*/
	TWDR = Copy_u8SlaveAddress << 1u ;

	/*Set bit 0 for read request*/
	SET_BIT(TWDR, 0u);

	/*Clear the start condition bit*/
	CLR_BIT(TWCR, TWCR_TWSTA);

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the previous action finishes and the interrupt flag is raised again*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		Local_Error = SlaveAddressWithReadErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;

}

TWI_ErrorStatus_t TWI_MstrWriteDataByte(uint8 Copy_u8DataByte)
{
	TWI_ErrorStatus_t Local_Error = NoError;

	/*Put the data byte on the bus*/
	TWDR = Copy_u8DataByte;

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the previous action finishes and the interrupt flag is raised again*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != MSTR_WR_BYTE_ACK)
	{
		Local_Error = MstrWriteByteWithAckErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;

}

TWI_ErrorStatus_t TWI_MstrReadDataByte(uint8* Copy_u8DataByte)
{
	TWI_ErrorStatus_t Local_Error = NoError;

	if(Copy_u8DataByte != NULL)
	{
		/*Clear interrupt flag to enable slave to send data*/
		SET_BIT(TWCR, TWCR_TWINT);

		/*wait until the slave writing finishes and the interrupt flag is raised again*/
		while((GET_BIT(TWCR,TWCR_TWINT))==0);

		/*Check the status of the bus*/
		if((TWSR & STATUS_BITS_MASK) != MSTR_RD_BYTE_WITH_ACK)
		{
			Local_Error = MstrReadByteWithAck;
		}
		else
		{
			/*Read the data sent from slave*/
			*Copy_u8DataByte = TWDR;
		}
	}
	else
	{
		Local_Error = NullPtrErr;
	}

	return Local_Error;

}

void TWI_SendStopCondition(void)
{
	/*Set the stop condition bit*/
	SET_BIT(TWCR, TWCR_TWSTO);

	/*Clear interrupt flag to enable previous action to happen*/
	SET_BIT(TWCR, TWCR_TWINT);
}
