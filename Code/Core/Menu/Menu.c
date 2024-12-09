	//#################################################################//
	
/**
* @brief MENU Selection & Display Library (Source File)
* @details Designed for PM Drive Panel Based on TM1637 Library		
* @note  Use Only For PM motor Drive Panel

	Version:1402/12/1 -> Ragan Parto Pars 
	By M.Baradaran 
	Editor:... 
	Version of Edit:
*/

	//#################################################################//

#include "stm32G0xx_hal.h"
#include "Menu.h"
#include "math.h"
//#include "tm1637.h"
#include "Store_Flash.h"
#include <stdbool.h>
#include "Display.h"
//#include "LED.h"

#define Default_Password 1234
#define Length_Frame 11

#define Number_Submenu_LEVEL1 10
#define Number_Submenu_LEVEL2 14
#define Number_Submenu_LEVEL3 22
#define Number_Segments 4
uint8_t Number_OF_Settings=107;


#define Max_Value_1 100 // It's Max for majority of variables
#define Max_Value_2 255 // It's Max for "KP_detection_time"
#define Max_Value_3 50  // It's Max for "Motor_Pole_Number"
#define Max_Value_4 2000// It's Max for "Motor_Nominal_Current"
#define Max_Value_5 500 // It's Max for "Motor_Nominal_Voltage" and "Motor_Nominal_Speed"


#define Min_Value_1 16  // It's Min for "Motor_Pole_Number"
#define Min_Value_2 400 // It's Max for "Motor_Nominal_Current"
#define Min_Value_3 50  // It's Max for "Motor_Nominal_Voltage"
#define Min_Value_4 100 // It's Max for "Motor_Nominal_Speed"


//-----------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------Display Level 1
//-----------------------------------------------------------------------------------------------------
char Res_1[Number_Segments]="OBP ";//Address in memory = 0x01
char Res_2[Number_Segments]="OPS ";//Address in memory = 0x02
char Res_3[Number_Segments]="CLS ";//Address in memory = 0x03
char Res_4[Number_Segments]="LSP ";//Address in memory = 0x04  ----------> New : Low Speed
char Res_5[Number_Segments]="LRN ";//Address in memory = 0x05
char Res_6[Number_Segments]="DOD ";//Address in memory = 0x06
char Res_7[Number_Segments]="CSR ";//Address in memory = 0x07
char Res_8[Number_Segments]="AD1 ";
char Res_9[Number_Segments]="AD2 ";
char Res_10[Number_Segments]="SED ";//Address in memory = 0xFE
char Res_11[Number_Segments]="    ";      //Reserve
char Res_12[Number_Segments]="    ";      //Reserve
char Res_13[Number_Segments]="    ";      //Reserve
char Res_14[Number_Segments]="    ";      //Reserve
char Res_15[Number_Segments]="    ";      //Reserve
char Res_16[Number_Segments]="    ";      //Reserve
//-----------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------Display Level 2 : ADV1
//-----------------------------------------------------------------------------------------------------
char Res_17[Number_Segments]="OPA4";//Address in memory = 0x07
char Res_18[Number_Segments]="OPA5";//Address in memory = 0x08
char Res_19[Number_Segments]="OPS ";//Address in memory = 0x09
char Res_20[Number_Segments]="OPS2";//Address in memory = 0x0A
char Res_21[Number_Segments]="OPS4";//Address in memory = 0x0B
char Res_22[Number_Segments]="OPS5";//Address in memory = 0x0C
char Res_23[Number_Segments]="CLA1";//Address in memory = 0x0E
char Res_24[Number_Segments]="CLA2";//Address in memory = 0x0F
char Res_25[Number_Segments]="CLS ";//Address in memory = 0x10
char Res_26[Number_Segments]="CLS2";//Address in memory = 0x11
char Res_27[Number_Segments]="CLS4";//Address in memory = 0x13
char Res_28[Number_Segments]="CLS5";//Address in memory = 0x14
char Res_29[Number_Segments]="LDI ";//Address in memory = 0x15 ----------> New
char Res_30[Number_Segments]="BUA ";//Address in memory = 0x18
char Res_31[Number_Segments]="    ";      //Reserve
char Res_32[Number_Segments]="    ";      //Reserve
char Res_33[Number_Segments]="    ";      //Reserve
char Res_34[Number_Segments]="    ";      //Reserve
char Res_35[Number_Segments]="    ";      //Reserve
//-----------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------Display Level 3 : ADV2
//-----------------------------------------------------------------------------------------------------
char Res_37[Number_Segments]="OPA ";//Address in memory = 0x19
char Res_38[Number_Segments]="OPA3";//Address in memory = 0x1A
char Res_39[Number_Segments]="OPC ";//Address in memory = 0x1D
char Res_40[Number_Segments]="OPC1";//Address in memory = 0x1E
char Res_41[Number_Segments]="OPC2";//Address in memory = 0x1F
char Res_42[Number_Segments]="OPC3";//Address in memory = 0x20
char Res_43[Number_Segments]="OPC4";//Address in memory = 0x21
char Res_44[Number_Segments]="OPC5";//Address in memory = 0x22
char Res_45[Number_Segments]="CLA ";//Address in memory = 0x28
char Res_46[Number_Segments]="OBD ";//Address in memory = 0x27
char Res_47[Number_Segments]="NOJ1";//Address in memory = 0x28
char Res_48[Number_Segments]="RDJ ";//Address in memory = 0x32
char Res_49[Number_Segments]="OLL ";//Address in memory = 0x33
char Res_50[Number_Segments]="OLD ";//Address in memory = 0x34
char Res_51[Number_Segments]="ACL ";//Address in memory = 0x23 , 0x24 ,0x2D , 0x2E , 0x2F
char Res_52[Number_Segments]="POC ";//Address in memory = 0x35
char Res_53[Number_Segments]="CUR ";//Address in memory = 0x36
char Res_54[Number_Segments]="VOL ";//Address in memory = 0x37
char Res_55[Number_Segments]="NSP ";//Address in memory = 0x38 ----------> New
char Res_56[Number_Segments]="DLO ";//Address in memory = 0x39
char Res_57[Number_Segments]="DLC ";//Address in memory = 0x3A
char Res_58[Number_Segments]="DNO ";      //Reserve
char Res_59[Number_Segments]="    ";      //Reserve
char Res_60[Number_Segments]="    ";      //Reserve
char Res_61[Number_Segments]="    ";      //Reserve


//------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------Variables for Saving data on Flash
//------------------------------------------------------------------------------------------------------------------------
bool ID_RES1_SAVE_PERMISSION=0;//Level: 1
bool ID_RES2_SAVE_PERMISSION=0;//Level: 1
bool ID_RES3_SAVE_PERMISSION=0;//Level: 1
bool ID_RES4_SAVE_PERMISSION=0;//Level: 1
bool ID_RES5_SAVE_PERMISSION=0;//Level: 1
bool ID_RES6_SAVE_PERMISSION=0;//Level: 1
bool ID_RES7_SAVE_PERMISSION=0;//Level: 1
bool ID_RES8_SAVE_PERMISSION=0;//Level: 1
bool ID_RES9_SAVE_PERMISSION=0;//Level: ADV 1
bool ID_RES10_SAVE_PERMISSION=0;//Level: ADV 2
bool ID_RES11_SAVE_PERMISSION=0;//Level: 1
//------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------Device's modes
//------------------------------------------------------------------------------------------------------------------------ 
char Res_Mod_1[Number_Segments]="CO  ";
char Res_Mod_2[Number_Segments]="HH  ";
char Res_Mod_3[Number_Segments]="OF  ";
extern char Commercial_Flash_Array[255];
extern char Household_Flash_Array[255];
extern char Office_Flash_Array[255];
//------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------Constant sentences
//------------------------------------------------------------------------------------------------------------------------
char Save_Notic[Number_Segments]="SAVE";
char Empty_Seg[Number_Segments]="    ";
char OP[Number_Segments]=             "OP  ";
char Auto[Number_Segments]=           "AU  ";
char CL[Number_Segments]=             "CL  ";
//----------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------Variables depended on Menu
//----------------------------------------------------------------------------------------------------------------------------
extern uint8_t Byte_1_CD_Mode;
extern uint8_t Byte_1_OD_Mode;
extern uint8_t Byte_1_Normal_Mode;
extern uint8_t Byte_1_Manual_Mode;
extern uint8_t Counter_Back_to_Norm;
extern bool Manual_mode;
Menu_HandleTypeDef Menu;
uint8_t Sub_Page=0;
int Value=0;
uint8_t setting;
bool Change_Mode_Flag=0;
bool End_Page=0;
extern bool Toggle_Sevensegment;
extern char Read_Array_Flash[255];
extern char Display_storage[Number_Segments];
bool Flag_Tune_Mode_Menu=0;
bool Flag_Door_Direction_Menu=0;
bool Flag_Command_Source_Menu=0;
bool Flag_Buzzer_Menu=0;
bool Flag_KP_Detection_Time_Menu=0;
bool Flag_Motor_Pole_Number_Menu=0;
bool Flag_Motor_Nominal_Current_Menu=0;
bool Flag_Motor_Nominal_Voltage_Menu=0;
bool Flag_Motor_Nominal_Speed_Menu=0;
bool Flag_Demo=0;
bool Change_State_Manual=0;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------Variables depended on trasmision (UART)
//--------------------------------------------------------------------------------------------------------------------------------
extern uint8_t arr_frame[Length_Frame];
extern uint8_t Byte_1_Start_Frame; 
extern uint8_t Byte_2_Start_Frame;
extern uint8_t Byte_1_END_Frame;
extern uint8_t Byte_2_END_Frame;
extern uint8_t Byte_1_Write_Frame;
extern UART_HandleTypeDef huart1;
extern uint8_t Byte_1_Device_Mode;
extern bool Serial_Repeat;
extern char Seial_Repeat_arr_frame[Length_Frame];	
extern bool Flag_Repeat_Off;
extern bool Transmision_Flag;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------Variables depended on the Flash Storage
//--------------------------------------------------------------------------------------------------------------------------------
char Read_Array_Flash_Res[Number_Segments];
bool Reset_Flash=0;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------Advance mode variables 
//--------------------------------------------------------------------------------------------------------------------------------
uint8_t Address_Value;
bool Read_ADV1=0;
bool Flag_ADV1=0;
uint8_t ADV1_NUM_Param=0;
bool Read_ADV2=0;
bool Flag_ADV2=0;
uint8_t ADV2_NUM_Param=0;
//--------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------- Password's Variables 
//--------------------------------------------------------------------------------------------------------------------------------
bool Password_Mode_Flag=0;
char Pass_Field[Number_Segments]="    ";
uint8_t Step_Pass=0;
bool check_Pass=0;
bool Reset_Menu=0;
//--------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------- Manual Mode Variables 
//--------------------------------------------------------------------------------------------------------------------------------
extern bool Tune_Mode;
extern bool Flag_Show_Auto;
extern bool Flag_Show_OD;
extern bool Flag_Show_CD;
//-------------------------------------------------------
//----------------------------- CRC Variable
//-------------------------------------------------------
extern uint8_t CRC_Value;

//-------------------------------------------------------
//----------------------------- Wating
//-------------------------------------------------------
extern bool Flag_System_Waitng;
//--------------------------------------------------------------
void Menu_Data_Display(Menu_HandleTypeDef *Menu)
{
	if(Menu->Override_Vector==0)
	{
		if(Reset_Menu==1){
			//Menu->Current_Menu_Page=0;
			//Menu->Menu_Page=1;
			//Menu->Menu_Sub_Page=1;
			Menu->Current_Menu_Page=0;
			Menu->Current_Menu_SubPage=1;
			Password_Mode_Flag=0;
			Step_Pass=0;
			Sub_Page=0;
			Flag_ADV1=0;
			Reset_Menu=0;
			
		}
			//--------------------------------------- Page 0: Setup
					if(Menu->Current_Menu_Page==0)
					{
					//String2segment("      ");		
					Menu->machine_state_selection=0;
					Menu->Current_Menu_Page=1;
					}
			//----------------------------------------------------
			//--------------------------------------- Page 1: RES1 : Obstacle
			//----------------------------------------------------
			if(Menu->Current_Menu_Page==1)
			{
				End_Page=0;
					switch (Menu->Current_Menu_SubPage)
						{	
						case 1://Current_Menu_SubPage 1 ---> Show Menu
							Value=0;
							Sub_Page=0;
							Change_Mode_Flag=0;
							ID_RES1_SAVE_PERMISSION=0;
							for(int i=0;i<4;i++){
								Display_storage[i]=Res_1[i];
							}
							Display(Display_storage,"12345","00000");
							
						break;
						
						case 2://Current_Menu_SubPage 2 ---> Change Menu
							ID_RES1_SAVE_PERMISSION=0;
							Change_Mode_Flag=0;
							Change_Value_In_Sub_Page2(Read_Array_Flash[1]);//Covert Hex to 4 digit for display.
						break;
							
						case 3://Current_Menu_SubPage 3 ---> Save Changes
							Sub_Page=2;
							End_Page=1;
							ID_RES1_SAVE_PERMISSION=1;
							Toggle_Show_Save();
						break;
						}
			}
			//----------------------------------------------------
			//--------------------------------------- Page 1: RES2 : High SP Open
			//----------------------------------------------------
			if(Menu->Current_Menu_Page==2)
			{
				End_Page=0;
					switch (Menu->Current_Menu_SubPage)
						{	
						case 1://Current_Menu_SubPage 1 ---> Show Menu
							Value=0;
							Sub_Page=0;
							Change_Mode_Flag=0;
							ID_RES2_SAVE_PERMISSION=0;
							for(int i=0;i<4;i++){
								Display_storage[i]=Res_2[i];
							}
							Display(Display_storage,"12345","00000");
						break;
						
						case 2://Current_Menu_SubPage 2 ---> Change Menu
							ID_RES2_SAVE_PERMISSION=0;
							Change_Mode_Flag=0;
							Change_Value_In_Sub_Page2(Read_Array_Flash[2]);//Covert Hex to 4 digit for display.
						break;
							
						case 3://Current_Menu_SubPage 3 ---> Save Changes
							Sub_Page=2;
							End_Page=1;
							ID_RES2_SAVE_PERMISSION=1;
							Toggle_Show_Save();
						break;
						}
			}
			//----------------------------------------------------
			//--------------------------------------- Page 1: RES3 : High SP Close
			//----------------------------------------------------
			if(Menu->Current_Menu_Page==3)
			{
				
				End_Page=0;	
					switch (Menu->Current_Menu_SubPage)
						{	
						case 1://Current_Menu_SubPage 1 ---> Show Menu
							Value=0;
							Sub_Page=0;
							Change_Mode_Flag=0;
							ID_RES3_SAVE_PERMISSION=0;
							for(int i=0;i<4;i++){
								Display_storage[i]=Res_3[i];
							}
							Display(Display_storage,"12345","00000");
						break;
						
						case 2://Current_Menu_SubPage 2 ---> Change Menu
						ID_RES3_SAVE_PERMISSION=0;
						Change_Mode_Flag=0;
						Change_Value_In_Sub_Page2(Read_Array_Flash[3]);//Covert Hex to 4 digit for display.
						break;
							
						case 3://Current_Menu_SubPage 3 ---> Save Changes
							Sub_Page=2;
							End_Page=1;
							ID_RES3_SAVE_PERMISSION=1;
							Toggle_Show_Save();
						break;	
						}	
			}
			//----------------------------------------------------
			//--------------------------------------- Page 1: RES4 : Low Speed
			//----------------------------------------------------
			if(Menu->Current_Menu_Page==4)
			{
				
				End_Page=0;
					switch (Menu->Current_Menu_SubPage)
						{	
						case 1://Current_Menu_SubPage 1 ---> Show Menu
							Value=0;
							Sub_Page=0;
							Change_Mode_Flag=0;
							ID_RES4_SAVE_PERMISSION=0;
							for(int i=0;i<4;i++){
								Display_storage[i]=Res_4[i];
							}
							Display(Display_storage,"12345","00000");
						break;
									
						case 2://Current_Menu_SubPage 2 ---> Change Menu
						ID_RES4_SAVE_PERMISSION=0;
						Change_Mode_Flag=0;
						Change_Value_In_Sub_Page2(Read_Array_Flash[4]);//Covert Hex to 4 digit for display.
						break;
							
						case 3://Current_Menu_SubPage 3 ---> Save Changes
							Sub_Page=2;
							End_Page=1;
							ID_RES4_SAVE_PERMISSION=1;
							Toggle_Show_Save();
						break;	
						}
			}
			//----------------------------------------------------
			//--------------------------------------- Page 1: RES5 : Tune Mode
			//----------------------------------------------------
			if(Menu->Current_Menu_Page==5)
			{
				
				End_Page=0;
					switch (Menu->Current_Menu_SubPage)
						{
						case 1://Current_Menu_SubPage 1 ---> Show Menu
							Flag_Tune_Mode_Menu=0;
							Value=0;
							Sub_Page=0;
							Change_Mode_Flag=0;
							ID_RES5_SAVE_PERMISSION=0;
							for(int i=0;i<4;i++){
								Display_storage[i]=Res_5[i];
							}
							Display(Display_storage,"12345","00000");
						break;
									
						case 2://Current_Menu_SubPage 2 ---> Change Menu
						Flag_Tune_Mode_Menu=1;
						ID_RES5_SAVE_PERMISSION=0;
						Change_Mode_Flag=0;
						Change_Value_In_Sub_Page2(Read_Array_Flash[6]);//Covert Hex to 4 digit for display.
						break;
							
						case 3://Current_Menu_SubPage 3 ---> Save Changes
							Flag_Tune_Mode_Menu=0;
							Sub_Page=2;
							End_Page=1;
							ID_RES5_SAVE_PERMISSION=1;
							Toggle_Show_Save();
						break;	
						}	
			}
			//----------------------------------------------------
			//--------------------------------------- Page 1: RES6 : Door Direction
			//----------------------------------------------------
			if(Menu->Current_Menu_Page==6)
			{
				End_Page=0;
					switch (Menu->Current_Menu_SubPage)
						{
						case 1://Current_Menu_SubPage 1 ---> Show Menu
						Flag_Door_Direction_Menu=0;
						Value=0;
						Sub_Page=0;
						Change_Mode_Flag=0;
						ID_RES6_SAVE_PERMISSION=0;
						for(int i=0;i<4;i++){
								Display_storage[i]=Res_6[i];
							}
							Display(Display_storage,"12345","00000");
						break;
						
						case 2://Current_Menu_SubPage 2 ---> Change Menu
						Flag_Door_Direction_Menu=1;
						ID_RES6_SAVE_PERMISSION=0;
						Change_Mode_Flag=0;
						Change_Value_In_Sub_Page2(Read_Array_Flash[7]);//Covert Hex to 4 digit for display.
						break;
							
						case 3://Current_Menu_SubPage 3 ---> Save Changes
							Flag_Door_Direction_Menu=0;
							Sub_Page=2;
							End_Page=1;
							ID_RES6_SAVE_PERMISSION=1;
							Toggle_Show_Save();
						break;	
						}		
			}
			//----------------------------------------------------
			//--------------------------------------- Page 1: RES7 : Command Source
			//----------------------------------------------------
			if(Menu->Current_Menu_Page==7)
			{
				
				End_Page=0;
					switch (Menu->Current_Menu_SubPage)
						{
						case 1://Current_Menu_SubPage 1 ---> Show Menu
							Flag_Command_Source_Menu=0;
							Value=0;
							Sub_Page=0;
							Change_Mode_Flag=0;
							ID_RES7_SAVE_PERMISSION=0;
							for(int i=0;i<4;i++){
								Display_storage[i]=Res_7[i];
							}
							Display(Display_storage,"12345","00000");
						break;
						
						case 2://Current_Menu_SubPage 2 ---> Change Menu
							Flag_Command_Source_Menu=1;
							ID_RES7_SAVE_PERMISSION=0;
							Change_Mode_Flag=0;
							Change_Value_In_Sub_Page2(Read_Array_Flash[8]);//Covert Hex to 4 digit for display.
						break;
							
						case 3://Current_Menu_SubPage 3 ---> Save Changes
							Flag_Command_Source_Menu=0;
							Sub_Page=2;
							End_Page=1;
							ID_RES7_SAVE_PERMISSION=1;
							Toggle_Show_Save();
						break;	
						}		
			}
			
			//----------------------------------------------------
			//--------------------------------------- Page 1: RES8 : Advance 1
			//----------------------------------------------------
			if(Menu->Current_Menu_Page==8)
			{
	
				End_Page=0;
					switch (Menu->Current_Menu_SubPage)
						{
						case 1://Current_Menu_SubPage 1 ---> Show Menu
							//----------------------
							Flag_Buzzer_Menu=0;
							//----------------------
							Step_Pass=0;
							memset(Pass_Field,32,sizeof(Pass_Field));
							Value=0;
							Sub_Page=0;
							ADV1_NUM_Param=0;
						  Flag_ADV1=0;
							Change_Mode_Flag=0;
							ID_RES8_SAVE_PERMISSION=0;
							for(int i=0;i<4;i++){
									Display_storage[i]=Res_8[i];
								}
								Display(Display_storage,"12345","00000");
						break;
						
						case 2://Current_Menu_SubPage 2 ---> Change Menu
							Sub_Page=1;
							ID_RES8_SAVE_PERMISSION=0;
							Change_Mode_Flag=0;
							if(check_Pass==0){
								Check_Password();
							}
							else if(check_Pass==1){
								//Sub_Page=2;
								change_Param_ADV1();
							}
							//change_Param_ADV1();
						
						break;
						
						case 3://Current_Menu_SubPage 3 ---> change Value in advance mode 1
							Sub_Page=2;
							change_Param_ADV1();
							Change_Value_In_Sub_Page2(Address_Value);
						break;
							
						case 4://Current_Menu_SubPage 4 ---> Save Changes
							//----------------------
							Flag_Buzzer_Menu=0;
							//----------------------
							Sub_Page=3;
							End_Page=1;
							ID_RES8_SAVE_PERMISSION=1;
							Toggle_Show_Save();
						break;	
						}		
			}
			//----------------------------------------------------
			//--------------------------------------- Page 1: RES10: Advance 2
			//----------------------------------------------------
			if(Menu->Current_Menu_Page==9)
			{

				End_Page=0;
					switch (Menu->Current_Menu_SubPage)
						{
						case 1://Current_Menu_SubPage 1 ---> Show Menu
							//----------------------
							Flag_KP_Detection_Time_Menu=0;
							Flag_Motor_Pole_Number_Menu=0;
							Flag_Motor_Nominal_Current_Menu=0;
							Flag_Motor_Nominal_Voltage_Menu=0;
						  Flag_Motor_Nominal_Speed_Menu=0;
							Flag_Demo=0;
							//----------------------
							Step_Pass=0;
						  memset(Pass_Field,32,sizeof(Pass_Field));
							Value=0;
							Sub_Page=0;
							ADV2_NUM_Param=0;
						  Flag_ADV2=0;
							Change_Mode_Flag=0;
							ID_RES9_SAVE_PERMISSION=0;
							for(int i=0;i<4;i++){
									Display_storage[i]=Res_9[i];
								}
								Display(Display_storage,"12345","00000");
						break;
						
						case 2://Current_Menu_SubPage 2 ---> Change Menu
							
							Sub_Page=1;
							ID_RES9_SAVE_PERMISSION=0;
							Change_Mode_Flag=0;						
							if(check_Pass==0){
								Check_Password();
							}
							else if(check_Pass==1){
								change_Param_ADV2();
							}
							//change_Param_ADV2();
							break;
						
						case 3://Current_Menu_SubPage 3 ---> change Value in advance mode 1
							Sub_Page=2;
						  change_Param_ADV2();
							Change_Value_In_Sub_Page2(Address_Value);
						break;
							
						case 4://Current_Menu_SubPage 4 ---> Save Changes
							//----------------------
							Flag_KP_Detection_Time_Menu=0;
							Flag_Motor_Pole_Number_Menu=0;
						  Flag_Demo=0;
							//Flag_Motor_Nominal_Current_Menu=0;
							//Flag_Motor_Nominal_Voltage_Menu=0;
							//----------------------
							Sub_Page=3;
							End_Page=1;
							ID_RES9_SAVE_PERMISSION=1;
							Toggle_Show_Save();
						break;	
						}		
			}
			//----------------------------------------------------
			//--------------------------------------- Page 1: RES11 : Device Mode
			//----------------------------------------------------
			if(Menu->Current_Menu_Page==10)
			{

				End_Page=0;
					switch (Menu->Current_Menu_SubPage)
					{
						case 1://Current_Menu_SubPage 1 ---> Show Menu
							Value=0;
							Sub_Page=0;
							Change_Mode_Flag=0;
							ID_RES10_SAVE_PERMISSION=0;
							for(int i=0;i<4;i++){
									Display_storage[i]=Res_10[i];
								}
								Display(Display_storage,"12345","00000");
						break;
									
						case 2://Current_Menu_SubPage 2 ---> Change Menu
							ID_RES10_SAVE_PERMISSION=0;	
							Change_Mode_Flag=1;
							change_Mode_Value_In_Sub_Page2(Read_Array_Flash[Byte_1_Device_Mode]);
						break;
				
						case 3://Current_Menu_SubPage 3 ---> Save Changes
							Sub_Page=2;
							End_Page=1;
							ID_RES10_SAVE_PERMISSION=1;
							Toggle_Show_Save();
						break;	
					}
			}
			//--------------------------------------- 
	}
}




/**
* @brief 		Menu Page , Subpage & Over ride Value Calculator Based on Input Parameter
* @details 	There is 4 Main Key for Exploring Menu and Based on This 4 Key Menu Page & Subpage Are decided
						Fault Vector Will decide Menu Override Parameter Value 
						If Fault Vector !=0 Then Buzzer Will activate in  continous Mode
* @param 		UP/DOWN/LEFT/RIGHT Keys & Fault Vector
* @note  		***
*/


void Menu_Selection(Menu_HandleTypeDef *Menu,uint8_t ESC, uint8_t ENT, uint8_t Down, uint8_t Up,uint8_t Reset,uint8_t FaultVector){
	
	//---------------------------------------------------
	if(FaultVector==0)
	{
			//HAL_GPIO_WritePin(Buzzer_Port,Buzzer_Pin,0);
			Menu->Override_Vector=0;
			//---------------------------------------------------  Down Key
			if(Down==1)
			{
				Change_State_Manual=0;
				memset(Read_Array_Flash_Res,32,sizeof(Read_Array_Flash_Res));
				if(Password_Mode_Flag==0){
					if(Sub_Page==0){
						Menu->Current_Menu_Page--;
						Menu->Current_Menu_SubPage=0;
					}
				}
				Change_Value_Conditions_Down_Key(Menu);
				
			}
			//---------------------------------------------------  UP Key
			if(Up==1)
			{
				Change_State_Manual=0;
				memset(Read_Array_Flash_Res,32,sizeof(Read_Array_Flash_Res));
				
				if(Password_Mode_Flag==0){
					if(Sub_Page==0){
						Menu->Current_Menu_Page++;
						Menu->Current_Menu_SubPage=0;
					}
				}
				
				Change_Value_Conditions_Up_Key(Menu);
				
				

			}
			//---------------------------------------------------  Enter Key
			if(ENT==1)
			{
				memset(Read_Array_Flash_Res,32,sizeof(Read_Array_Flash_Res));
				//memset(Pass_Field,32,sizeof(Pass_Field));
				if(Password_Mode_Flag==0){
					if(End_Page==0){
						Menu->Current_Menu_SubPage++;
					}
					if(End_Page==1){
						//HAL_Delay(1000);
						Save_Changes();
						Sub_Page=0;
						End_Page=0;
						Read_ADV1=0;
						Read_ADV2=0;
						Menu->Current_Menu_Page=1;
						Menu->Current_Menu_SubPage=0;
					}
				}
				else if(Password_Mode_Flag==1){
					Value=0;
					Step_Pass=Step_Pass+1;	
				}
			}
			//---------------------------------------------------  Escape Key
			if(ESC==1)
			{
				
				if(Manual_mode==1){
					Storage_Data_On_Mainboard(Byte_1_Normal_Mode,Byte_1_Manual_Mode);
					Flag_Show_Auto=1;
					Manual_mode=0;
					Flag_Show_OD=0;
					Flag_Show_CD=0;
					
				}
				memset(Read_Array_Flash_Res,32,sizeof(Read_Array_Flash_Res));
				memset(Pass_Field,32,sizeof(Pass_Field));
				Step_Pass=0;
				End_Page=0;
				Menu->Current_Menu_SubPage--;
				
				if(Sub_Page>0){
					Sub_Page=Sub_Page-1;
				}
				
				if(Password_Mode_Flag==1){
					Password_Mode_Flag=0;
					Value=0;
					
				}
			}
			
			/*if(Reset==1)
			{
				Save_Changes();
			}*/
			//---------------------------------------------------
			if(Menu->Current_Menu_Page>Number_Submenu_LEVEL1)
			Menu->Current_Menu_Page=1;
			if(Menu->Current_Menu_Page<1)
			Menu->Current_Menu_Page=Number_Submenu_LEVEL1;

			
			if(Menu->Current_Menu_SubPage>Number_Submenu_LEVEL1-1)
			Menu->Current_Menu_SubPage=Number_Submenu_LEVEL1-1;
			if(Menu->Current_Menu_SubPage<1)
			Menu->Current_Menu_SubPage=1;
	}
	//---------------------------------------------------
	else
	{
			//HAL_GPIO_WritePin(Buzzer_Port,Buzzer_Pin,Buzzer_Active);
			Menu->Override_Vector=Menu->Override_Vector|FaultVector;
	}
}

//--------------------------------------------------------------
void Change_Value_In_Sub_Page2(char Read_Array_Flash_byte_1){
	//This function set your value on diffrent setting;
	if(Sub_Page==0){
		Value=Read_Array_Flash_byte_1;
		Sub_Page=Sub_Page+1;
	}
	
	
	else if(Sub_Page==2 && Read_ADV1==0 && Flag_ADV1==1){
		Value=Read_Array_Flash[Read_Array_Flash_byte_1];
		Read_ADV1=1;
	}
	
	else if(Sub_Page==2 && Read_ADV2==0 && Flag_ADV2==1){
		Value=Read_Array_Flash[Read_Array_Flash_byte_1];
		
		if(Flag_Motor_Nominal_Current_Menu==1){
			Value=Value*10;
		}
		else if(Flag_Motor_Nominal_Voltage_Menu==1 ){
			Value=Value*2;
		}
		else if(Flag_Motor_Nominal_Speed_Menu==1){
			Value=Value*5;
		}

		Read_ADV2=1;
	}
	
	if(Flag_Motor_Nominal_Current_Menu==1){
		//memset(Read_Array_Flash_Res,0,sizeof(Read_Array_Flash_Res));
		Read_Array_Flash_Res[3]=(Value%10)+48;
		Read_Array_Flash_Res[2]=((Value/10)%10)+48;	
		Read_Array_Flash_Res[1]=((Value/100)%10)+48;
		Read_Array_Flash_Res[0]=(Value/1000)+48;
		Display(Read_Array_Flash_Res,"12345","00000");
	}
	else if(Flag_Motor_Nominal_Voltage_Menu==1 || Flag_Motor_Nominal_Speed_Menu==1){
		//memset(Read_Array_Flash_Res,0,sizeof(Read_Array_Flash_Res));
		Read_Array_Flash_Res[3]=' ';
		Read_Array_Flash_Res[2]=(Value%10)+48;
		Read_Array_Flash_Res[1]=((Value/10)%10)+48;	
		Read_Array_Flash_Res[0]=((Value/100)%10)+48;
		Display(Read_Array_Flash_Res,"12345","00000");
	}
	
	
	if(Flag_Motor_Nominal_Current_Menu==0 && Flag_Motor_Nominal_Voltage_Menu==0){
		//memset(Read_Array_Flash_Res,0,sizeof(Read_Array_Flash_Res));
		Read_Array_Flash_Res[3]=' ';
		Read_Array_Flash_Res[2]=(Value%10)+48;	
		Read_Array_Flash_Res[1]=((Value/10)%10)+48;
		Read_Array_Flash_Res[0]=(Value/100)+48;
		//Display(Read_Array_Flash_Res,"12345","00000");
	}
	
	
	
	
	
	//--------------------------------------------
	if(Flag_Tune_Mode_Menu==1){
		if(Value==0){
			Display("D   ","12345","00000");
			//LCD_Puts(0,1,Disable);
		}
		else if(Value==1){
			Display("E   ","12345","00000");
			//LCD_Puts(0,1,Enable);
		}
	}
	//--------------------------------------------
	else if(Flag_Door_Direction_Menu==1){
		if(Value==0){
			//LCD_Puts(0,1,Left);
			Display("L   ","12345","00000");
		}
		else if(Value==1){
			Display("R   ","12345","00000");
			//LCD_Puts(0,1,Right);
		}
	}
	//--------------------------------------------
	else if(Flag_Command_Source_Menu==1){
		if(Value==0){
			Display("CC  ","12345","00000");
			//LCD_Puts(0,1,CCM);
		}
		else if(Value==1){
			Display("OCC ","12345","00000");
			//LCD_Puts(0,1,CCMO);
		}
	}
	//--------------------------------------------
	else if(Flag_Buzzer_Menu==1){
		if(Value==0){
			Display("D   ","12345","00000");
			//LCD_Puts(0,1,Disable);
		}
		else if(Value==1){
			Display("E   ","12345","00000");
			//LCD_Puts(0,1,Enable);
		}
	}
					//--------------------------------------------
	else if(Flag_Demo==1){
		if(Value==0){
			Display("D   ","12345","00000");
		}
		else if(Value==1){
			Display("E   ","12345","00000");
		}
	}
	//--------------------------------------------
	else{
		Display(Read_Array_Flash_Res,"12345","00000");
		//LCD_Puts(0,1,Read_Array_Flash_Res);
	}
	//--------------------------------------------
				
				
}
//--------------------------------------------------------------
void change_Mode_Value_In_Sub_Page2(char Read_Array_Flash_byte_1){
	//This funcation change your mode among commercial, household and office mode
	
	if(Sub_Page==0){
		if(Read_Array_Flash_byte_1==0){      //Abbreviation of Commercial: COMM
			Value=0;
		}
		else if(Read_Array_Flash_byte_1==1){ //Abbreviation of Household: HHLD
			Value=1;
		}
		else if(Read_Array_Flash_byte_1==2){ //Abbreviation of Office: OFFC
			Value=2;
		}
	}
	
	
	Sub_Page=1;
	
	if(Value==0){
		memcpy(Read_Array_Flash_Res,Res_Mod_1,sizeof(Res_Mod_1));
	}
	else if(Value==1){					
		memcpy(Read_Array_Flash_Res,Res_Mod_2,sizeof(Res_Mod_2));
	}
	else if(Value==2){
		memcpy(Read_Array_Flash_Res,Res_Mod_3,sizeof(Res_Mod_3));
	}
	Display(Read_Array_Flash_Res,"12345","00000");					

}
//--------------------------------------------------------------
void change_Param_ADV1(){
	//This funcation change your advance menu in level 2
	if(Sub_Page==1){
		Flag_ADV1=1;
		Read_ADV1=0;
	}
	//----------------------
	Flag_Buzzer_Menu=0;
	//----------------------
	switch (ADV1_NUM_Param){
		case 0:
			memcpy(Read_Array_Flash_Res,Res_17,sizeof(Res_17));// Open Accel 4
			Address_Value=14;
		break;
		case 1:
			memcpy(Read_Array_Flash_Res,Res_18,sizeof(Res_18));// Open Accel 5
			Address_Value=15;
		break;
		case 2:
			memcpy(Read_Array_Flash_Res,Res_19,sizeof(Res_19));// Open Speed
			Address_Value=16;
		break;
		case 3:
			memcpy(Read_Array_Flash_Res,Res_20,sizeof(Res_20));// Open Speed 2
			Address_Value=17;
		break;
		case 4:
			memcpy(Read_Array_Flash_Res,Res_21,sizeof(Res_21));// Open Speed 4
			Address_Value=18;
		break;
		case 5:
			memcpy(Read_Array_Flash_Res,Res_22,sizeof(Res_22));// Open Speed 5
			Address_Value=19;
		break;
		case 6:
			memcpy(Read_Array_Flash_Res,Res_23,sizeof(Res_23));// Close Accel 1
			Address_Value=20;
		break;
		case 7:
			memcpy(Read_Array_Flash_Res,Res_24,sizeof(Res_24));// Close Accel 2
			Address_Value=21;
		break;
		case 8:
			memcpy(Read_Array_Flash_Res,Res_25,sizeof(Res_25));// Close Speed
			Address_Value=22;
		break;
		case 9:
			memcpy(Read_Array_Flash_Res,Res_26,sizeof(Res_26));// Close Speed 2
			Address_Value=23;
		break;
		case 10:
			memcpy(Read_Array_Flash_Res,Res_27,sizeof(Res_27));// Close Speed 4
			Address_Value=24;
		break;
		case 11:
			memcpy(Read_Array_Flash_Res,Res_28,sizeof(Res_28));// Close Speed 5
			Address_Value=25;
		break;
		case 12:
			memcpy(Read_Array_Flash_Res,Res_29,sizeof(Res_29));// Lock Distance
			Address_Value=26;
		break;
		case 13:
			memcpy(Read_Array_Flash_Res,Res_30,sizeof(Res_30));// Buzzer
			Address_Value=28;
			Flag_Buzzer_Menu=1;
		break;

	}
	
	
	if(Sub_Page==1){
		Display(Read_Array_Flash_Res,"12345","00000");
	}

}
//--------------------------------------------------------------
void change_Param_ADV2(){
	//This funcation change your advance menu in level 3 
	if(Sub_Page==1){
		Flag_ADV2=1;
		Read_ADV2=0;
	}
	//----------------------
	Flag_KP_Detection_Time_Menu=0;
	Flag_Motor_Pole_Number_Menu=0;
	Flag_Motor_Nominal_Current_Menu=0;
	Flag_Motor_Nominal_Voltage_Menu=0;
	Flag_Motor_Nominal_Speed_Menu=0;
	Flag_Demo=0;
	//----------------------
	
	switch (ADV2_NUM_Param){
		case 0:
			memcpy(Read_Array_Flash_Res,Res_37,sizeof(Res_37));// Open Accel
			Address_Value=34;
		break;
		case 1:
			memcpy(Read_Array_Flash_Res,Res_38,sizeof(Res_38));// Open Accel 3
			Address_Value=37;
		break;
		case 2:
			memcpy(Read_Array_Flash_Res,Res_39,sizeof(Res_39));// Open Current
			Address_Value=38;
		break;
		case 3:
			memcpy(Read_Array_Flash_Res,Res_40,sizeof(Res_40));// Open Current 1
			Address_Value=39;
		break;
		case 4:
			memcpy(Read_Array_Flash_Res,Res_41,sizeof(Res_41));// Open Current 2
			Address_Value=40;
		break;
		case 5:
			memcpy(Read_Array_Flash_Res,Res_42,sizeof(Res_42));// Open Current 3
			Address_Value=41;
		break;
		case 6:
			memcpy(Read_Array_Flash_Res,Res_43,sizeof(Res_43));// Open Current 4
			Address_Value=42;
		break;
		case 7:
			memcpy(Read_Array_Flash_Res,Res_44,sizeof(Res_44));// Open Current 5
			Address_Value=43;
		break;
		case 8:
			memcpy(Read_Array_Flash_Res,Res_45,sizeof(Res_45));// Close Accel
			Address_Value=44;
		break;
		case 9:
			memcpy(Read_Array_Flash_Res,Res_46,sizeof(Res_46));// KP Time(ms)
			Address_Value=48;
			Flag_KP_Detection_Time_Menu=1;
		break;
		case 10:
			memcpy(Read_Array_Flash_Res,Res_47,sizeof(Res_47));// Normal Jerk
			Address_Value=49;
		break;
		case 11:
			memcpy(Read_Array_Flash_Res,Res_48,sizeof(Res_48));// Stop Jerk
			Address_Value=50;
		break;
		case 12:
			memcpy(Read_Array_Flash_Res,Res_49,sizeof(Res_49));// OverLoad Limit
			Address_Value=51;
		break;
		case 13:
			memcpy(Read_Array_Flash_Res,Res_50,sizeof(Res_50));// OverLoad Time(s)
			Address_Value=52;
		break;
		case 14:
			memcpy(Read_Array_Flash_Res,Res_51,sizeof(Res_51));// Accel Lock 
			Address_Value=35;
		break;
		case 15:
			memcpy(Read_Array_Flash_Res,Res_52,sizeof(Res_52));// Pole Number(NO)
			Address_Value=53;
			Flag_Motor_Pole_Number_Menu=1;
		break;
		case 16:
			memcpy(Read_Array_Flash_Res,Res_53,sizeof(Res_53));// Nominal CUR(mA)
			Address_Value=54;
			Flag_Motor_Nominal_Current_Menu=1;
		break;
		case 17:
			memcpy(Read_Array_Flash_Res,Res_54,sizeof(Res_54));// Nominal VOL(V)
			Address_Value=55;
			Flag_Motor_Nominal_Voltage_Menu=1;
		break;
		case 18:
			memcpy(Read_Array_Flash_Res,Res_55,sizeof(Res_55));// Nominal Speed(RPM)
			Address_Value=56;
			Flag_Motor_Nominal_Speed_Menu=1;
		break;
		case 19:
			memcpy(Read_Array_Flash_Res,Res_56,sizeof(Res_56));// Open Destination
			Address_Value=57;
		break;
		case 20:
			memcpy(Read_Array_Flash_Res,Res_57,sizeof(Res_57));// CloseDestination
			Address_Value=58;
		break;
		case 21:
			memcpy(Read_Array_Flash_Res,Res_58,sizeof(Res_58));// CloseDestination
			Address_Value=59;
			Flag_Demo=1;
		break;

	}
	
	if(Sub_Page==1){
		Display(Read_Array_Flash_Res,"12345","00000");
	}
}
//--------------------------------------------------------------
void Toggle_Show_Save(void){
	//This funcation is sutable for Blinking
	
	if(Toggle_Sevensegment==0){
		memcpy(Display_storage,Save_Notic,sizeof(Save_Notic));
		Display(Display_storage,"12345","11111");
	}
	else if(Toggle_Sevensegment==1){
		memcpy(Display_storage,Empty_Seg,sizeof(Empty_Seg));
		Display(Display_storage,"12345","00000");
	}
}
//--------------------------------------------------------------
void Save_Changes(void){
	//This funcation Save your changes on your Flash 
			memset(Read_Array_Flash_Res,32,sizeof(Read_Array_Flash_Res)); //clear and fill LCD with space
			//LCD_Clear();
			Display(Display_storage,"12345","00000");
			Flag_System_Waitng=1;
			//-----------------------------------------------------------------------------------		SAVE RES1 : Obstacle
			if(ID_RES1_SAVE_PERMISSION==1 && Change_Mode_Flag==0){
				setting=1;
				Read_Array_Flash[1]=Value;
				Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
				incriment_array(1,sizeof(Read_Array_Flash),Read_Array_Flash);
				writeFlash(FLASH_USER_START_ADDR, Read_Array_Flash);
			  incriment_array(-1,sizeof(Read_Array_Flash),Read_Array_Flash);
				Storage_Data_On_Mainboard(Value,setting);
				ID_RES1_SAVE_PERMISSION=0;
			}
			else if(ID_RES1_SAVE_PERMISSION==1 && Change_Mode_Flag==1){
				//----------------------------
				//Place your code when you are in changing mode
				
				//----------------------------
				ID_RES1_SAVE_PERMISSION=0;
			}
			//-----------------------------------------------------------------------------------		SAVE RES2 : High SP Open
			if(ID_RES2_SAVE_PERMISSION==1 && Change_Mode_Flag==0){
				setting=2;
				Read_Array_Flash[2]=Value;
				Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
				incriment_array(1,sizeof(Read_Array_Flash),Read_Array_Flash);
				writeFlash(FLASH_USER_START_ADDR, Read_Array_Flash);
				incriment_array(-1,sizeof(Read_Array_Flash),Read_Array_Flash);
				
				Storage_Data_On_Mainboard(Value,setting);
				ID_RES2_SAVE_PERMISSION=0;
			}
			else if(ID_RES2_SAVE_PERMISSION==1 && Change_Mode_Flag==1){
				//----------------------------
				//Place your code when you are in changing mode
				
				//----------------------------
				ID_RES2_SAVE_PERMISSION=0;
			}
			//-----------------------------------------------------------------------------------		SAVE RES3 : High SP Close
			if(ID_RES3_SAVE_PERMISSION==1 && Change_Mode_Flag==0){
				setting=3;

				Read_Array_Flash[3]=Value;
				Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
				incriment_array(1,sizeof(Read_Array_Flash),Read_Array_Flash);
				writeFlash(FLASH_USER_START_ADDR, Read_Array_Flash);
				incriment_array(-1,sizeof(Read_Array_Flash),Read_Array_Flash);
				Storage_Data_On_Mainboard(Value,setting);
				ID_RES3_SAVE_PERMISSION=0;
			}
			else if(ID_RES3_SAVE_PERMISSION==1 && Change_Mode_Flag==1){
				//----------------------------
				//Place your code when you are in changing mode
				
				//----------------------------
				ID_RES3_SAVE_PERMISSION=0;
			}
			//-----------------------------------------------------------------------------------		SAVE RES4 : Low Speed
			if(ID_RES4_SAVE_PERMISSION==1 && Change_Mode_Flag==0){
				setting=4;

				Read_Array_Flash[4]=Value;
				Read_Array_Flash[5]=Value;
				Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
				incriment_array(1,sizeof(Read_Array_Flash),Read_Array_Flash);
				writeFlash(FLASH_USER_START_ADDR, Read_Array_Flash);
				incriment_array(-1,sizeof(Read_Array_Flash),Read_Array_Flash);
				Storage_Data_On_Mainboard(Value,setting);
				ID_RES4_SAVE_PERMISSION=0;
			}
			else if(ID_RES4_SAVE_PERMISSION==1 && Change_Mode_Flag==1){
				//----------------------------
				//Place your code when you are in changing mode
				
				//----------------------------
				ID_RES4_SAVE_PERMISSION=0;
			}
			//-----------------------------------------------------------------------------------		SAVE RES5 : Tune Mode
			if(ID_RES5_SAVE_PERMISSION==1 && Change_Mode_Flag==0){
				setting=6;
				Read_Array_Flash[6]=Value;
				Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
				incriment_array(1,sizeof(Read_Array_Flash),Read_Array_Flash);
				writeFlash(FLASH_USER_START_ADDR, Read_Array_Flash);
				incriment_array(-1,sizeof(Read_Array_Flash),Read_Array_Flash);
				Storage_Data_On_Mainboard(Value,setting);
				ID_RES5_SAVE_PERMISSION=0;
				if(Value==1){
					Tune_Mode=1;
				}
			}
			else if(ID_RES5_SAVE_PERMISSION==1 && Change_Mode_Flag==1){
				//----------------------------
				//Place your code when you are in changing mode
				
				//----------------------------
				ID_RES5_SAVE_PERMISSION=0;
			}
			//-----------------------------------------------------------------------------------		SAVE RES6 : Door Direction
			if(ID_RES6_SAVE_PERMISSION==1 && Change_Mode_Flag==0){
				setting=7;

				Read_Array_Flash[7]=Value;
				Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
				incriment_array(1,sizeof(Read_Array_Flash),Read_Array_Flash);
				writeFlash(FLASH_USER_START_ADDR, Read_Array_Flash);
				incriment_array(-1,sizeof(Read_Array_Flash),Read_Array_Flash);
				Storage_Data_On_Mainboard(Value,setting);
				ID_RES6_SAVE_PERMISSION=0;
			}
			else if(ID_RES6_SAVE_PERMISSION==1 && Change_Mode_Flag==1){
				//----------------------------
				//Place your code when you are in changing mode
				
				//----------------------------
				ID_RES6_SAVE_PERMISSION=0;
			}
			//-----------------------------------------------------------------------------------		SAVE RES7 : Command Source
			if(ID_RES7_SAVE_PERMISSION==1 && Change_Mode_Flag==0){
				setting=8;

				Read_Array_Flash[8]=Value;
				Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
				incriment_array(1,sizeof(Read_Array_Flash),Read_Array_Flash);
				writeFlash(FLASH_USER_START_ADDR, Read_Array_Flash);
				incriment_array(-1,sizeof(Read_Array_Flash),Read_Array_Flash);
				Storage_Data_On_Mainboard(Value,setting);
				ID_RES7_SAVE_PERMISSION=0;
			}
			else if(ID_RES7_SAVE_PERMISSION==1 && Change_Mode_Flag==1){
				//----------------------------
				//Place your code when you are in changing mode
				
				//----------------------------
				ID_RES7_SAVE_PERMISSION=0;
			}
			//-----------------------------------------------------------------------------------		SAVE RES9 _ADV
			if(ID_RES8_SAVE_PERMISSION==1 && Change_Mode_Flag==0){
				Read_Array_Flash[Address_Value]=Value;
				if(Address_Value==26){
					Read_Array_Flash[Address_Value+1]=Value;
				}
				Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
				incriment_array(1,sizeof(Read_Array_Flash),Read_Array_Flash);
				writeFlash(FLASH_USER_START_ADDR, Read_Array_Flash);
				incriment_array(-1,sizeof(Read_Array_Flash),Read_Array_Flash);
				Storage_Data_On_Mainboard(Value,Address_Value);
				ID_RES8_SAVE_PERMISSION=0;
				Flag_ADV1=0;
			}
			else if(ID_RES8_SAVE_PERMISSION==1 && Change_Mode_Flag==1){
				//----------------------------
				//Place your code when you are in changing mode
				
				//----------------------------
				ID_RES8_SAVE_PERMISSION=0;
			}
			//-----------------------------------------------------------------------------------		SAVE RES10 _ADV
			if(ID_RES9_SAVE_PERMISSION==1 && Change_Mode_Flag==0){
				
				if(Flag_Motor_Nominal_Current_Menu==1){
					Value=Value/10;
					Flag_Motor_Nominal_Current_Menu=0;		
				}
				
				if(Flag_Motor_Nominal_Voltage_Menu==1){
					Value=Value/2;
					Flag_Motor_Nominal_Voltage_Menu=0;
				}
				if(Flag_Motor_Nominal_Speed_Menu==1){
					Value=Value/5;
					Flag_Motor_Nominal_Speed_Menu=0;
				}
				
				
				

				Read_Array_Flash[Address_Value]=Value;
				
				if(Address_Value==35){
					Read_Array_Flash[Address_Value+1]=Value;
					Read_Array_Flash[Address_Value+10]=Value;
					Read_Array_Flash[Address_Value+11]=Value;
					Read_Array_Flash[Address_Value+12]=Value;
				}
				Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
				incriment_array(1,sizeof(Read_Array_Flash),Read_Array_Flash);
				writeFlash(FLASH_USER_START_ADDR, Read_Array_Flash);
				incriment_array(-1,sizeof(Read_Array_Flash),Read_Array_Flash);
				Storage_Data_On_Mainboard(Value,Address_Value);
				ID_RES9_SAVE_PERMISSION=0;
				Flag_ADV2=0;
			}
			else if(ID_RES9_SAVE_PERMISSION==1 && Change_Mode_Flag==1){
				//----------------------------
				//Place your code when you are in changing mode
				
				//----------------------------
				ID_RES9_SAVE_PERMISSION=0;
			}

			//-----------------------------------------------------------------------------------		SAVE RES11 _Mode
			if(ID_RES10_SAVE_PERMISSION==1 && Change_Mode_Flag==0){
				
				//----------------------------
				//Place your code when you are in Number mode
				
				//----------------------------
			}
			else if(ID_RES10_SAVE_PERMISSION==1 && Change_Mode_Flag==1){
				setting=Byte_1_Device_Mode;

				if(Value==0){
					memcpy(Read_Array_Flash,Commercial_Flash_Array,sizeof(Commercial_Flash_Array));
				}
				else if(Value==1){
					memcpy(Read_Array_Flash,Household_Flash_Array,sizeof(Household_Flash_Array));
				}
				else if(Value==2){
					memcpy(Read_Array_Flash,Office_Flash_Array,sizeof(Office_Flash_Array));
				}
				//Read_Array_Flash[27]=(Value)+48;
				Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
				incriment_array(1,sizeof(Read_Array_Flash),Read_Array_Flash);
				writeFlash(FLASH_USER_START_ADDR, Read_Array_Flash);
				incriment_array(-1,sizeof(Read_Array_Flash),Read_Array_Flash);
				Storage_Data_On_Mainboard(Value,setting);
				Change_Mode_Flag=0;
				ID_RES10_SAVE_PERMISSION=0;
			}
			//-------------------------------------	
			
}	
//--------------------------------------------------------------
void Storage_Data_On_Mainboard(uint8_t Value,uint8_t setting){ 
	// This funncation send your Frame changes to main board
	CRC_Value=Calculate_CRC();
	arr_frame[0]=Byte_1_Start_Frame; //Byte0 StartFrame
	arr_frame[1]=Byte_2_Start_Frame; //Byte1 StartFrame
	arr_frame[2]=Byte_1_Write_Frame; //Set to Write main board
	arr_frame[3]=0x00;               //Byte0 Setting
	arr_frame[4]=setting;            //Byte1 Setting
	arr_frame[5]=0x00;               //Byte0 Value
	arr_frame[6]=Value;              //Byte1 Value
	arr_frame[7]=CRC_Value;
	arr_frame[8]=CRC_Value;
	arr_frame[9]=Byte_1_END_Frame;   //Byte0 End Frame
	arr_frame[10]=Byte_2_END_Frame;   //Byte1 End Frame
	
	
	memcpy(Seial_Repeat_arr_frame,arr_frame,sizeof(arr_frame));
	if(Flag_Repeat_Off==0){
		Serial_Repeat=1;
	}
	Flag_Repeat_Off=0;
	HAL_UART_Transmit(&huart1, arr_frame, sizeof(arr_frame), 1000);
	setting=0;
	Transmision_Flag=1;
	
}
//--------------------------------------------------------------
bool Check_Password(void){
	Password_Mode_Flag=1;

	if(Toggle_Sevensegment==0){
		HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);//EN
		HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);//EN
		HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);//EN
		HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);//EN
		HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);//EN
	}
	else if(Toggle_Sevensegment==1){
		HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);//EN
		HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);//EN
		HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);//EN
		HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);//EN
		HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);//EN
	}
	
	
	if(Step_Pass==0){
		Pass_Field[0]=Value+48;		
	}
	else if(Step_Pass==1){
		Pass_Field[1]=Value+48;		
	}
	else if(Step_Pass==2){
		Pass_Field[2]=Value+48;		
	}
	else if(Step_Pass==3){
		Pass_Field[3]=Value+48;		
	}
	
	if(Step_Pass<=3){
		//memcpy(Display_storage,Pass_Field,sizeof(Pass_Field));
		Display(Pass_Field,"","");
	}
	else if(Step_Pass==4){
		Value=((Pass_Field[0]-48)*1000)+((Pass_Field[1]-48)*100)+((Pass_Field[2]-48)*10)+((Pass_Field[3]-48)*1);
		if(Default_Password==Value){
			Step_Pass=0;
			Value=0;
			memset(Pass_Field,32,sizeof(Pass_Field));
			check_Pass=1;
			Password_Mode_Flag=0;
		}
		else{
			Step_Pass=0;
			Value=0;
			memset(Pass_Field,32,sizeof(Pass_Field));
			check_Pass=0;
			Password_Mode_Flag=0;
			Reset_Menu=1;
		}
	}
	return 0;
}
//--------------------------------------------------------------
void Change_Value_Conditions_Up_Key(Menu_HandleTypeDef *Menu){
	
	
	if(Password_Mode_Flag==0){
			if (Sub_Page==1 
				&& Flag_Motor_Nominal_Speed_Menu==0 && Flag_Motor_Nominal_Voltage_Menu==0 && Flag_Motor_Nominal_Current_Menu==0 
				&& Flag_Motor_Pole_Number_Menu==0 && Flag_KP_Detection_Time_Menu==0 && Flag_Buzzer_Menu==0 
			  && Flag_Command_Source_Menu==0 && Flag_Door_Direction_Menu==0 && Flag_Tune_Mode_Menu==0 && Change_Mode_Flag==0 
			  && Flag_ADV1==0 && Flag_ADV2==0)
			  {
				Value=Value+1;
				if(Value>=Max_Value_1){
					Value=Max_Value_1;
				}
			}
			else if (Sub_Page==1 && Change_Mode_Flag==1){
				Value=Value+1;
				if(Value>=2){
					Value=2;
				}
			}
			else if (Sub_Page==1 && Flag_Tune_Mode_Menu==1){
				Value=Value+1;
				if(Value>=1){
					Value=1;
				}
			}
			else if (Sub_Page==1 && Flag_Door_Direction_Menu==1){
				Value=Value+1;
				if(Value>=1){
					Value=1;
				}
			}
			else if (Sub_Page==1 && Flag_Command_Source_Menu==1){
				Value=Value+1;
				if(Value>=1){
					Value=1;
				}
			}
			//-------------------------------------------------------- Subpage 2
			else if (Sub_Page==2 && Flag_Buzzer_Menu==1){
				Value=Value+1;
				if(Value>=1){
					Value=1;
				}
			}
			else if (Sub_Page==2 && Flag_KP_Detection_Time_Menu==1){
				Value=Value+1;
				if(Value>=Max_Value_2){
					Value=Max_Value_2;
				}
			}
			else if (Sub_Page==2 && Flag_Motor_Pole_Number_Menu==1){
				Value=Value+2;
				if(Value>=Max_Value_3){
					Value=Max_Value_3;
				}
			}
			else if (Sub_Page==2 && Flag_Motor_Nominal_Current_Menu==1){
				Value=Value+50;
				if(Value>=Max_Value_4){
					Value=Max_Value_4;
				}
			}
				else if (Sub_Page==2 && Flag_Motor_Nominal_Voltage_Menu==1){
				Value=Value+1;
				if(Value>=Max_Value_5){
					Value=Max_Value_5;
				}
			}
				else if (Sub_Page==2 && Flag_Motor_Nominal_Speed_Menu==1){
				Value=Value+5;
				if(Value>=Max_Value_5){
					Value=Max_Value_5;
				}
			}
			

	
			
			
			else if (Sub_Page==1 && Flag_ADV1==1){
				ADV1_NUM_Param=ADV1_NUM_Param+1;
				if(ADV1_NUM_Param>Number_Submenu_LEVEL2-1){
					ADV1_NUM_Param=0;
				}
			}
			else if (Sub_Page==2 && Flag_ADV1==1){
				Value=Value+1;
				if(Value>=Max_Value_1){
					Value=Max_Value_1;
				}
			}
			
			else if (Sub_Page==1 && Flag_ADV2==1){
				ADV2_NUM_Param=ADV2_NUM_Param+1;
				if(ADV2_NUM_Param>Number_Submenu_LEVEL3-1){
					ADV2_NUM_Param=0;
				}
			}
			else if (Sub_Page==2 && Flag_ADV2==1 && Flag_Motor_Pole_Number_Menu==0){
				Value=Value+1;
				if(Value>=Max_Value_1){
					Value=Max_Value_1;
				}
			}
		}
	
		
		
		
	else if(Password_Mode_Flag==1){
		Value=Value+1;
		if(Value>=9){
			Value=9;
		}
		
	}
				
}
//--------------------------------------------------------------
void Change_Value_Conditions_Down_Key(Menu_HandleTypeDef *Menu){
	if(Password_Mode_Flag==0){

		if (Sub_Page==1 && Value!=0 
			&& Flag_Motor_Nominal_Speed_Menu==0 && Flag_Motor_Nominal_Voltage_Menu==0 && Flag_Motor_Nominal_Current_Menu==0 && Flag_Motor_Pole_Number_Menu==0 
		  && Flag_KP_Detection_Time_Menu==0 && Flag_Buzzer_Menu==0 && Flag_Command_Source_Menu==0 
		  && Flag_Door_Direction_Menu==0 && Flag_Tune_Mode_Menu==0 && Change_Mode_Flag==0 && Flag_ADV1==0 
		  && Flag_ADV2==0)
		  {
			Value=Value-1;
		}
		else if (Sub_Page==1 && Value!=0 && Change_Mode_Flag==1){
			Value=Value-1;
		}
		else if (Sub_Page==1 && Value!=0 && Flag_Tune_Mode_Menu==1){
			Value=Value-1;
		}
		else if (Sub_Page==1 && Value!=0 && Flag_Door_Direction_Menu==1){
			Value=Value-1;
		}
		else if (Sub_Page==1 && Value!=0 && Flag_Command_Source_Menu==1){
			Value=Value-1;
		}
		//--------------------------------------------------------------- Subpage 2
		else if (Sub_Page==2 && Value!=0 && Flag_Buzzer_Menu==1){
			Value=Value-1;
		}
		else if (Sub_Page==2 && Value!=0 && Flag_KP_Detection_Time_Menu==1){
			Value=Value-1;
		}
		else if (Sub_Page==2 && Value>Min_Value_1 && Flag_Motor_Pole_Number_Menu==1){
			Value=Value-2;
		}
		else if (Sub_Page==2 && Value>Min_Value_2 && Flag_Motor_Nominal_Current_Menu==1){
			Value=Value-50;
		}
		else if (Sub_Page==2 && Value>Min_Value_3 && Flag_Motor_Nominal_Voltage_Menu==1){
			Value=Value-1;
		}
		else if (Sub_Page==2 && Value>Min_Value_4 && Flag_Motor_Nominal_Speed_Menu==1){
			Value=Value-5;
		}
		

		else if (Sub_Page==1 && ADV1_NUM_Param!=0 && Flag_ADV1==1){
			ADV1_NUM_Param=ADV1_NUM_Param-1;
		}
		else if (Sub_Page==1 && ADV1_NUM_Param==0 && Flag_ADV1==1){
			ADV1_NUM_Param=Number_Submenu_LEVEL2-1;
		}
		else if (Sub_Page==2 && Value!=0 && Flag_ADV1==1){
			Value=Value-1;
		}
		
		
		else if (Sub_Page==1 && ADV2_NUM_Param!=0 && Flag_ADV2==1){
			ADV2_NUM_Param=ADV2_NUM_Param-1;
		}
		else if (Sub_Page==1 && ADV2_NUM_Param==0 && Flag_ADV2==1){
			ADV2_NUM_Param=Number_Submenu_LEVEL3-1;
		}
		else if (Sub_Page==2 && Value!=0 && Flag_ADV2==1 && Flag_Motor_Pole_Number_Menu==0 && Flag_Motor_Nominal_Current_Menu==0 && Flag_Motor_Nominal_Voltage_Menu==0 && Flag_Motor_Nominal_Speed_Menu==0){
			Value=Value-1;
		}
	}
	
	else if(Password_Mode_Flag==1){
		
		if(Value>0){
			Value=Value-1;
		}
	}
	
}

//--------------------------------------------------------------
int Calculate_CRC(void){
	uint16_t Sum_Coefficient_Array=0;
	uint8_t CRC_Number=0;
	for (int Counter_CRC=1;Counter_CRC<=Number_OF_Settings;Counter_CRC++){
		Sum_Coefficient_Array=Sum_Coefficient_Array+Read_Array_Flash[Counter_CRC];
	}
	CRC_Number=Sum_Coefficient_Array%97;
	return CRC_Number;	
}




