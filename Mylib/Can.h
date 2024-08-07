#ifndef CAN_H
#define CAN_H
#include "main.h"

#define ODRIVE_HEARTBEAT_MESSAGE		0x001
#define SET_AXIS_NODE_ID				0x006
#define SET_AXIS_REQUESTED_STATE 		0x007
#define ENCODER_ESTIMATES				0x009
#define GET_ENCODER_COUNT				0x00A
#define SET_CONTROLLER_MODES			0x00B
#define SET_INPUT_POS					0x00C
#define SET_INPUT_VEL					0x00D
#define SET_INPUT_TORQUE				0x00E
#define SET_LIMITS						0x00F
#define GET_IQ							0x014
#define REBOOT_ODRIVE					0x016
#define GET_BUS_VOLTAGE_CURRENT			0x017
#define CLEAR_ERRORS					0x018
#define SET_POSITION_GAIN				0x01A
#define SET_VEL_GAINS					0x01B

typedef struct{
	CAN_HandleTypeDef *can;
	uint8_t TxData[8];
	uint8_t RxData[8];
	uint32_t TxMailbox;
	CAN_TxHeaderTypeDef TxHeader;
	CAN_RxHeaderTypeDef RxHeader;
}Val;

typedef enum{
	UNDEFINED = 0x0,
	IDLE = 0x1,
	STARTUP_SEQUENCE = 0x2,
	FULL_CALIBRATION_SEQUENCE = 0x3,
	MOTOR_CALIBRATION = 0x4,
	ENCODER_INDEX_SEARCH = 0x6,
	ENCODER_OFFSET_CALIBRATION = 0x7,
	CLOSED_LOOP_CONTROL = 0x8,
	LOCKIN_SPIN = 0x9,
	ENCODER_DIR_FIND = 0xA,
	HOMING = 0xB,
	ENCODER_HALL_POLARITY_CALIBRATION = 0xC,
	ENCODER_HALL_PHASE_CALIBRATION = 0xD
} Axis_State;

void Set_TX_parameter(Val *val,int AXIS_ID,int COMMAND_ID, uint32_t RTR,uint32_t DLC);
void Set_Axis_Requested_State(Val *val,Axis_State state);
void Set_Input_Vel(Val *val, float vel, float torqueff);
void Set_Input_Pos(Val *val,float Input_Pos, int Vel_FF, int Torque_FF);
void CAN_setup(Val *val,CAN_HandleTypeDef *hcan1);
#endif
