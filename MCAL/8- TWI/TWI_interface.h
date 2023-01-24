/*********************************************************************/
/*********************************************************************/
/******** Author:    Amgad Samir   ***********************************/
/******** Component: TWI           ***********************************/
/******** Layer:     MCAL          ***********************************/
/******** Version:   1.0           ***********************************/
/*********************************************************************/
/*********************************************************************/

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum
{
	NoError,
	NullPtrErr,
	StartCondErr,
	RepStartErr,
	SlaveAddressWithWriteErr,
	SlaveAddressWithReadErr,
	MstrWriteByteWithAckErr,
	MstrReadByteWithAck


}TWI_ErrorStatus_t;

void TWI_voidMasterInit(uint8 Copy_u8Address);

void TWI_voidSlaveInit(uint8 Copy_u8Address);

TWI_ErrorStatus_t TWI_SendStartCondition(void);

TWI_ErrorStatus_t TWI_SendRepeatedStart(void);

TWI_ErrorStatus_t TWI_SendSlaveAdressWithWrite(uint8 Copy_u8SlaveAddress);

TWI_ErrorStatus_t TWI_SendSlaveAdressWithRead(uint8 Copy_u8SlaveAddress);

TWI_ErrorStatus_t TWI_MstrWriteDataByte(uint8 Copy_u8DataByte);

TWI_ErrorStatus_t TWI_MstrReadDataByte(uint8* Copy_u8DataByte);

void TWI_SendStopCondition(void);

#endif
