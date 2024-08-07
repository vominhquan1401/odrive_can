#include "Can.h"

void Set_TX_parameter(Val *val,int AXIS_ID,int COMMAND_ID, uint32_t RTR,uint32_t DLC)
{
	val->TxHeader.StdId=(AXIS_ID<<5)|COMMAND_ID;
	val->TxHeader.IDE=CAN_ID_STD;
	val->TxHeader.RTR=RTR;
	val->TxHeader.DLC=DLC;
}

void Set_Axis_Requested_State(Val *val,Axis_State state){
	Set_TX_parameter(val,0x00, SET_AXIS_REQUESTED_STATE, CAN_RTR_DATA, 4);
	unsigned int Requested_State = state;
	uint8_t *ptrToFloat;
	ptrToFloat = (uint8_t *)&Requested_State;
	
	val->TxData[0] = ptrToFloat[0];
	val->TxData[1] = ptrToFloat[1];
	val->TxData[2] = ptrToFloat[2];
	val->TxData[3] = ptrToFloat[3];
	HAL_CAN_AddTxMessage(val->can,&val->TxHeader,val->TxData,&val->TxMailbox);
}

void Set_Input_Vel(Val *val, float vel, float torqueff){
	Set_TX_parameter(val,0x00, SET_INPUT_VEL, CAN_RTR_DATA, 8);
	uint8_t *ptrVel;
	ptrVel = (uint8_t *)&vel;
	uint8_t *ptrTor;
	ptrTor = (uint8_t *)&torqueff;
	
	val->TxData[0] = ptrVel[0];
	val->TxData[1] = ptrVel[1];
	val->TxData[2] = ptrVel[2];
	val->TxData[3] = ptrVel[3];

	val->TxData[4] = ptrTor[0];
	val->TxData[5] = ptrTor[1];
	val->TxData[6] = ptrTor[2];
	val->TxData[7] = ptrTor[3];
	HAL_CAN_AddTxMessage(val->can,&val->TxHeader,val->TxData,&val->TxMailbox);
	//CAN_Send_Packet(&CAN, &TX);
}

void Set_Input_Pos(Val *val,float Input_Pos, int Vel_FF, int Torque_FF){
	Set_TX_parameter(val,0x00, SET_INPUT_POS, CAN_RTR_DATA, 8);
	uint8_t *ptrPos;
	ptrPos = (uint8_t *)&Input_Pos;
	uint8_t *ptrVel;
	ptrVel = (uint8_t *)&Vel_FF;
	uint8_t *ptrTor;
	ptrTor = (uint8_t *)&Torque_FF;
	
	val->TxData[0] = ptrPos[0];
	val->TxData[1] = ptrPos[1];
	val->TxData[2] = ptrPos[2];
	val->TxData[3] = ptrPos[3];

	val->TxData[4] = ptrVel[0];
	val->TxData[5] = ptrVel[1];
	
	val->TxData[6] = ptrTor[0];
	val->TxData[7] = ptrTor[1];
	HAL_CAN_AddTxMessage(val->can,&val->TxHeader,val->TxData,&val->TxMailbox);
}
void CAN_setup(Val *val,CAN_HandleTypeDef *hcan1){
	val->can=hcan1;
}
