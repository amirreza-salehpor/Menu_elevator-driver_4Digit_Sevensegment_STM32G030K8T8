/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32G0xx_hal_gpio.h"
#include "Display.h"
#include "Store_Flash.h"
#include "Menu.h"

#define Lock_ADV 200                  				// Lock time is according to Timer 100ms : Ex: 150*100ms= 15000ms = 15s
#define Enter_Manual_Time 30          				// Entering manual mode or tuning mode is deppended on the Timer 100ms : Ex: 30*100ms= 3000ms = 3s
#define Back_To_First_After_Time 100  				// Entering manual mode or tuning mode is deppended on the Timer 100ms : Ex: 100*100ms= 10000ms = 3s
#define RST_Time 30
extern uint8_t Number_OF_Settings;
//---------------------------------- Reserve in Flash
extern uint8_t Byte_1_Device_Mode;
//----------------------------------
extern char Default_Flash_Array[255];					 // Coefficients for Defualt : when you program your device for the first, we would have 'Default_Flash_Array' coefficients on RAM and FLASH
char Commercial_Flash_Array[255];    				   // Coefficients for Commercial
char Household_Flash_Array[255];     					 // Coefficients for Household
char Office_Flash_Array[255]={0x01};  				 // Coefficients for Office
//bool Reset_To_Default_Value=0;     

bool Reset_To_Default_Value=0;
//-------------------------------------------------------
//----------------------------- Reserve in Flash
//-------------------------------------------------------
#define Byte_1_Setup 0xFF                       // It’s an address in RAM, and it is used to set up the device.
uint8_t Byte_1_Manual_Mode=0xFE;						    // It's a setting address for Manual mode
#define Byte_1_OK_Received 0xFD							    // It's a setting receving aknowledge
#define Byte_1_Receive_Data_Main_Board 0xFC     // It's a setting address for receving Data through mainboard
#define Byte_1_Reset_LCD 0xFB                   // It's a setting address for Reset LCD
//-------------------------------------------------------
//----------------------------- Read/Write Flash Variable
//-------------------------------------------------------
uint32_t addr = FLASH_USER_START_ADDR;          // Start address in flash memory :It's for storagind coefficients
char Read_Array_Flash[255];											// It's coefficients array 
uint8_t Array_Flash_Counter=0;									// It's for counting coefficient's index
//-------------------------------------------------------
//----------------------------- UART Variables
//-------------------------------------------------------
uint8_t byte;
#define  Length_Frame 11
char buffer[Length_Frame];                 			//It's for printf Function in UART.
uint8_t  arr_frame[Length_Frame];							  //This array use for Storge valid bytes that sent from master device.
int  frame_counter=0;						           			//It's for counting bytes received from UART that they are valid for making Frame. 
bool block_Counter_frame=0;			           		  //It's for checking start of frame "0xAA";
int  clear_counter_Frame=0;                     //It's for clearing "arr_frame";
uint8_t Value_Res1;                             //This variable is used for sending data on UART
uint8_t Byte_1_Start_Frame=0xAA;                //Setting Byte: Start Frame 1
uint8_t Byte_2_Start_Frame=0xBB;                //Setting Byte: Start Frame 2
uint8_t Byte_1_END_Frame=0xEE;               	  //Setting Byte: End Frame 1
uint8_t Byte_2_END_Frame=0xFF;                	//Setting Byte: End Frame 2
uint8_t Byte_1_Read_Frame=0xCC;                 //Setting Byte: Read Frame
uint8_t Byte_1_Write_Frame=0xDD;                //Setting Byte: Write Frame
bool Serial_Available=0;									      //show UART is available or not
bool Serial_Repeat=0;											      //It's a Flag for Enabling repeat_serial
uint8_t  Seial_Repeat_arr_frame[Length_Frame];	//repeat's fream
bool Repeat_Time=0;															//It's for controling time of blinking
uint8_t Number_Repeat_Serial=0;                 //Number of repeat for sending frame
bool Lock_System=0;															//Arrow keys would be out of reach when this variable set 1
bool Transmision_Flag=0;												//This variable use for blocking sending Data

uint8_t Counter_Reset_system=9;									//Reset system after 9 second
uint8_t Counter_Devide_10=0;                     // It is used to divide time in the timer loop.

uint8_t Repeat_time_Serial=0;
//-------------------------------------------------------
//----------------------------- Keys&Menu Variable
//-------------------------------------------------------
Menu_HandleTypeDef PM_Menu;
uint8_t Menu_ESC=0;															// It would be 1 if we press ESC
uint8_t Menu_ENT=0;															// It would be 1 if we press ENT
uint8_t Menu_Down=0;														// It would be 1 if we press Down
uint8_t Menu_Up=0;															// It would be 1 if we press Up
uint8_t Menu_Reset=0;														// It would be 1 if we press Reset
extern int Value;																// It's for showing value on LCD or deciding about settings 
int Fault_Vector=0;															// Reserve
bool Menu_CD=0;																	// It would be 1 if we press CD Key
bool Menu_OD=0;																	// It would be 1 if we press OD Key
int Counter_CD_Key=0;														// It whould be increase when you press and hold "CD Key" 
int Counter_OD_Key=0;														// It whould be increase when you press and hold "CD Key" 
int Counter_ENT_Key=0;													// It whould be increase when you press and hold "ENT Key"  
int Counter_RST_Key=0;													// It whould be increase when you press and hold "RST Key" 
bool Manual_mode=0;															// It whould be one when you enter manual mode
uint8_t Counter_UP_Key=0;												// It whould be increase when you press and hold "UP Key" 
uint8_t Counter_Down_Key=0;											// It whould be increase when you press "Down Key"  
uint8_t Counter_ESC_Key=0;											// It whould be increase when you press and hold "ESC Key" 
uint8_t Step_Speed=0;														// It whould be increase when you press and hold on a key : we have 3 steps for increasing count's speed
uint8_t Counter_Change_Value=0;                 // It is used for changing Steps when we press up or down keys and hold on 
uint8_t Counter_Key_Hold=0;											// It is used for calculating time when we press Up or down key and hold on 
bool Lock_Counter_Key=1;												// Changing the count's speed and changing steps would be locked if this flag set to 1
extern bool Reset_Menu;													// We can reset everything in the menu if this flag set to 1
bool Lock_LCD=0;																// Nothing shows on the LCD if this flag is set to 1
bool Flag_OK_Setup=0;														// It would be 1 if the flash is set up 
//-------------------------------------------------------
//----------------------------- Save Process Variables
//-------------------------------------------------------
bool Toggle_Sevensegment=0;										  // This variable is used for toggle LED segments when we are in save mode.
uint8_t Counter_Toggle_Sevensegment=0; 				  // We can control blinking time with this counter
extern uint8_t setting; 						  					// Coefficient array's Index 
//-------------------------------------------------------
//----------------------------- Check Manual mode Variables
//-------------------------------------------------------
uint8_t Counter_Back_to_Norm=0;                 // When we are in advanced mode and we don't press any key, the menu would back to first menu after "Back_To_First_After_Time" time
bool Tune_Mode=0;                               // It would be 1 if tune mode is enabled
uint8_t Byte_1_OD_Mode=0x01;										// It's a special value when we are in manual mode if you want to have more information, please refer to the protocols document
uint8_t Byte_1_CD_Mode=0x02;										// It's a special value when we are in manual mode if you want to have more information, please refer to the protocols document
uint8_t Byte_1_Tune_Mode=0x03;									// It's a special value when we are in manual mode if you want to have more information, please refer to the protocols document
uint8_t Byte_1_Normal_Mode=0x04;								// It's a special value when we are in manual mode if you want to have more information, please refer to the protocols document
bool Flag_Show_Auto=0;													// When you press the ESC key when you are in manual mode, the device exit manual mode and show "Auto" on seven-segment.
bool Flag_Show_OD=0;                            // When you press the OD key, 'OD' shows on the seven-segment display, and we enter manual mode.
bool Flag_Show_CD=0;														// When you press the CD key, 'OD' shows on the seven-segment display, and we enter manual mode.
uint8_t Counter_Auto_Show=0;										// It's a counter for showing "Auto" on seven-segment when we press ESC key
//-------------------------------------------------------
//----------------------------- Password Variable
//-------------------------------------------------------
extern bool check_Pass;													// It's a flag for validating the password
uint8_t Counter_Lock_Pass=0;										// Advance would be lock after a special time
bool Flag_Lock_Pass_Show=0;                     // It's a flag for locking the advanced mode
//-------------------------------------------------------
//----------------------------- Screen saver Variable
//-------------------------------------------------------
#define Travel_Byte_1_main 0x55                 // Setting Byte: For illustrating the Travel state on LCD, the main board has to send this value as a setting
#define Fault_Byte_1_main 0x77									// Setting Byte: For illustrating the Fault state on LCD, the main board has to send this value as a setting
char Show_Variable[4];													// Illustrating values on screen saver when value are sended through mainborad
bool Flag_Screen_Saver=0;												// It's a flag for enabeling sacreen saver
uint8_t Screen_Number=0;												// It's a value for selecting travel state or fault state that recieved through mainboard
uint8_t Counter_Time_Screen_Saver=0;						// It's a time counter for sceern saver: It would be 0 if we push keys
bool Flag_Repeat_Off=0;													// Sending repeat data would be off if this flag set to 1
//-------------------------------------------------------
//----------------------------- Wating
//-------------------------------------------------------
bool Flag_System_Waitng=0;                      // when system  has a special duty at the moment like sending frame or receiving frame, this flag would be 1
bool Flag_Load_Data=0;
uint8_t Counter_Wating=0;                       // It’s used to calculate the time needed to return to normal mode.
uint8_t Counter_Wating_Show=0;                  /* When the device connects to the mainboard, the mainboard starts sending data to provide coefficients. 
																									 At this time, the device enters waiting mode to respond to each request. The waiting time is calculated
																									 through 'Counter_Waiting_Show'. Additionally, we have five LEDs to indicate the loading of all data on 
																									 the mainboard. These LEDs will turn on after a specific time, which is determined by 'Counter_Waiting_Show'. */
//-------------------------------------------------------
//----------------------------- CRC Variable
//-------------------------------------------------------
uint8_t CRC_Value;                              //CRC= summation(All Coefficient)%97
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim14;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM14_Init(void);
/* USER CODE BEGIN PFP */
//------------------------------------------------------------------------------------------ Welcome
void Welcome_Seg(void){
	uint8_t Delay_welcome=50;
	Select_Segment(1);
	Show_Segment('a');
	HAL_Delay(Delay_welcome);
	Select_Segment(2);
	Show_Segment('a');
	HAL_Delay(Delay_welcome);
	Select_Segment(3);
	Show_Segment('a');
	HAL_Delay(Delay_welcome);
	Select_Segment(4);
	Show_Segment('a');
	HAL_Delay(Delay_welcome);
	Select_Segment(4);
	Show_Segment('b');
	HAL_Delay(Delay_welcome);
	Select_Segment(4);
	Show_Segment('c');
	HAL_Delay(Delay_welcome);
	Select_Segment(4);
	Show_Segment('d');
	HAL_Delay(Delay_welcome);
	Select_Segment(3);
	Show_Segment('d');
	HAL_Delay(Delay_welcome);
	Select_Segment(2);
	Show_Segment('d');
	HAL_Delay(Delay_welcome);
	Select_Segment(1);
	Show_Segment('d');
	HAL_Delay(Delay_welcome);
	Select_Segment(1);
	Show_Segment('e');
	HAL_Delay(Delay_welcome);
	Select_Segment(1);
	Show_Segment('f');
	HAL_Delay(Delay_welcome);
}
//------------------------------------------------------------------------------------------ UART Response
void Response_Input_Data(char byte_0){
	arr_frame[5]=0x00;   //Bit0 Response Value
	Value_Res1=byte_0;
	arr_frame[6]=Value_Res1; //Bit1 Response Value
	HAL_UART_Transmit(&huart1, arr_frame, sizeof(arr_frame), 10);	
}
//------------------------------------------------------------------------------------------ TIMER
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{  
	if (htim==&htim14) //100ms
  {
			if(Counter_Toggle_Sevensegment>1){ //It is for controling speed of blinking : 200 ms
				if(Flag_System_Waitng==1){
					//Counter_Wating_Show=Counter_Wating_Show+1;
				}
				Toggle_Sevensegment=!Toggle_Sevensegment;
				Counter_Toggle_Sevensegment=0;
			}
			Counter_Toggle_Sevensegment=Counter_Toggle_Sevensegment+1;
	}
	if (htim==&htim1) //100ms
  {
		//-------------------------------------------------------- Change Value when we press up key and hold on
		if(HAL_GPIO_ReadPin(Up_Key_GPIO_Port,Up_Key_Pin)==0){
			
			Counter_Change_Value=Counter_Change_Value+1;
			if(Lock_Counter_Key==0){
				Counter_Key_Hold=Counter_Key_Hold+1;
			}
			if(Counter_Key_Hold>=25 && Step_Speed==0){ //It would be faster after 2.5 second
				Counter_Key_Hold=0;
				Step_Speed=Step_Speed+1;
				Counter_Change_Value=0;
			}
			else if(Counter_Key_Hold>=25 && Step_Speed==1){ //It would be faster after +2.5 second
				Step_Speed=Step_Speed+1;
				Lock_Counter_Key=1;
				Counter_Change_Value=0;
			}
			if(Step_Speed==0 && Counter_Change_Value>=4){ //The Value would be change in each 1 second
					Change_Value_Conditions_Up_Key(&PM_Menu);
					Counter_Change_Value=0;
			}
			else if(Step_Speed==1 && Counter_Change_Value>=2){ //The Value would be change in each 0.2 second
					Change_Value_Conditions_Up_Key(&PM_Menu);
					Counter_Change_Value=0;
			}
			else if(Step_Speed==2 && Counter_Change_Value>=1){ //The Value would be change in each 0.1 second
					Change_Value_Conditions_Up_Key(&PM_Menu);
					Counter_Change_Value=0;
			}	
		}
		//-------------------------------------------------------- Change Value when we press up key and hold on
		else if(HAL_GPIO_ReadPin(Down_Key_GPIO_Port,Down_Key_Pin)==0){
			
			Counter_Change_Value=Counter_Change_Value+1;
			if(Lock_Counter_Key==0){
				Counter_Key_Hold=Counter_Key_Hold+1;
			}
			if(Counter_Key_Hold>=25 && Step_Speed==0){ //It would be faster after 2.5 second
				Counter_Key_Hold=0;
				Step_Speed=Step_Speed+1;
				Counter_Change_Value=0;
			}
			else if(Counter_Key_Hold>=25 && Step_Speed==1){ //It would be faster after +2.5 second
				Step_Speed=Step_Speed+1;
				Lock_Counter_Key=1;
				Counter_Change_Value=0;
			}
			if(Step_Speed==0 && Counter_Change_Value>=4 && Value>>0){ //The Value would be change in each 0.4 second
					Change_Value_Conditions_Down_Key(&PM_Menu);
					Counter_Change_Value=0;
			}
			else if(Step_Speed==1 && Counter_Change_Value>=2 && Value>>0){ //The Value would be change in each 0.2 second
					Change_Value_Conditions_Down_Key(&PM_Menu);
					Counter_Change_Value=0;
			}
			else if(Step_Speed==2 && Counter_Change_Value>=1 && Value>>0){ //The Value would be change in each 0.1 second
					Change_Value_Conditions_Down_Key(&PM_Menu);
					Counter_Change_Value=0;
			}	
		}
		else if(HAL_GPIO_ReadPin(Up_Key_GPIO_Port,Up_Key_Pin)==1 && HAL_GPIO_ReadPin(Down_Key_GPIO_Port,Down_Key_Pin)==1){
			Step_Speed=0;
			Counter_Change_Value=0;
			Lock_Counter_Key=0;
			Counter_Key_Hold=0;
		}
		//---------------------------------------------------- Time for Repeating serial's data : Repeat data after 500 milisecound
		if(Serial_Repeat==1){
				Repeat_time_Serial=Repeat_time_Serial+1;
				if(Repeat_time_Serial==5){
					Repeat_Time=1;
					Repeat_time_Serial=0;
				}
			}
		//---------------------------------------------------- Read ESC Key
		if(HAL_GPIO_ReadPin(ESC_Key_GPIO_Port,ESC_Key_Pin)==0){
			Counter_ESC_Key=Counter_ESC_Key+1;
			if(Counter_ESC_Key>=Enter_Manual_Time){
				Counter_ESC_Key=Enter_Manual_Time;
			}
		}
		else{
			Counter_ESC_Key=0;
		}
		//---------------------------------------------------- Read UP Key
		if(HAL_GPIO_ReadPin(Up_Key_GPIO_Port,Up_Key_Pin)==0){
			Flag_Screen_Saver=0;
			Counter_Time_Screen_Saver=0;
			Counter_UP_Key=Counter_UP_Key+1;
				if(Counter_UP_Key>=Enter_Manual_Time){
				Counter_UP_Key=Enter_Manual_Time;
			}
		}
		else{
			Counter_UP_Key=0;
		}
		//---------------------------------------------------- Read Down Key
		if(HAL_GPIO_ReadPin(Down_Key_GPIO_Port,Down_Key_Pin)==0){
			Flag_Screen_Saver=0;
			Counter_Time_Screen_Saver=0;
			Counter_Lock_Pass=0;
			Counter_Down_Key=Counter_Down_Key+1;
			if(Counter_Down_Key>=Enter_Manual_Time){
				Counter_Down_Key=Enter_Manual_Time;
			}
		}
		else{
			Counter_Down_Key=0;
		}
		//---------------------------------------------------- Read CD Key
		if(HAL_GPIO_ReadPin(CD_Key_GPIO_Port,CD_Key_Pin)==0){
			Counter_CD_Key=Counter_CD_Key+1;
			if(Counter_CD_Key>=Enter_Manual_Time){
				Counter_CD_Key=Enter_Manual_Time;
			}
		}
		else{
			Counter_CD_Key=0;
		}
		
		//---------------------------------------------------- Read OD Key
		if(HAL_GPIO_ReadPin(OD_Key_GPIO_Port,OD_Key_Pin)==0){
			Counter_OD_Key=Counter_OD_Key+1;
				if(Counter_OD_Key>=Enter_Manual_Time){
				Counter_OD_Key=Enter_Manual_Time;
			}
		}
		else{
			Counter_OD_Key=0;
		}
		
		//---------------------------------------------------- Read ENT Key
		if(HAL_GPIO_ReadPin(ENT_Key_GPIO_Port,ENT_Key_Pin)==0){
			Counter_ENT_Key=Counter_ENT_Key+1;
				if(Counter_ENT_Key>=Enter_Manual_Time){
				Counter_ENT_Key=Enter_Manual_Time;
			}
		}
		else{
			Counter_ENT_Key=0;
		}
		//---------------------------------------------------- Read Reset Key
		if(HAL_GPIO_ReadPin(RST_Key_GPIO_Port,RST_Key_Pin)==0){
			Counter_RST_Key=Counter_RST_Key+1;
			if(Counter_RST_Key>=RST_Time){
				Counter_RST_Key=RST_Time;
				//Read_Array_Flash[0]=0x00;
				Reset_To_Default_Value=1;
			}
		}
		else{
			Counter_RST_Key=0;
		}
		//--------------------------- If ADV 1 or ADV 2 was unlocked, it would be lock after "Lock_ADV" time
		if(check_Pass==1){
			Counter_Lock_Pass=Counter_Lock_Pass+1;
			if(Counter_Lock_Pass==Lock_ADV){
				Flag_Lock_Pass_Show=1;
				check_Pass=0;
				Counter_Lock_Pass=0;
				Reset_Menu=1;
				//Flag_Screen_Saver=1;
			}
		}
		//---------------------------------------------------- Back to Screen Saver Mode
		if(Flag_Screen_Saver==0){
			if(Manual_mode==0){
				Counter_Time_Screen_Saver=Counter_Time_Screen_Saver+1;
			}
		}
		if(Counter_Time_Screen_Saver>=Back_To_First_After_Time){
			//Reset_Menu=1;
			//Flag_Show_Auto=1;
			Flag_Screen_Saver=1;
			Counter_Time_Screen_Saver=0;
		}
		//---------------------------------------------------- Back to Normal Mode
		if(Manual_mode==0 && Counter_Back_to_Norm>=Back_To_First_After_Time){
			Lock_LCD=0;
			Manual_mode=0;
			Counter_Back_to_Norm=0;
			Reset_Menu=1;
			Flag_Screen_Saver=1;
			Counter_Back_to_Norm=Counter_Back_to_Norm+1;
		}
		/*else if(Manual_mode==1){
			Counter_Back_to_Norm=Counter_Back_to_Norm+1;
		}*/
		//---------------------------------------------------- Reset systeam after a special time
		if(Lock_System==1){
			Counter_Devide_10=Counter_Devide_10+1;
			if(Counter_Devide_10>=10){
				Counter_Devide_10=0;
				Counter_Reset_system=Counter_Reset_system-1;
			}
		}
		//---------------------------------------------------- Wating for filling coefficient
		if(Flag_System_Waitng==1){
			Counter_Wating=Counter_Wating+1;
			if(Counter_Wating>=10){
				LED_Control(1,0);
				LED_Control(2,0);
				LED_Control(3,0);
				LED_Control(4,0);
				LED_Control(5,0);
				Counter_Wating_Show=0;
				Flag_System_Waitng=0;
				Counter_Wating=0;
				Flag_Screen_Saver=1;
			}
		}
		//----------------------------------------------- Repeat data if we dont have reponse from main board when we have a change in the menu
		
	}
}

//------------------------------------------------------------------------------------------ Receive UART1 and making Frame
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1) {
		Serial_Available=1;
		//------------------------------------------- Make frame
		if(block_Counter_frame==1 && frame_counter<Length_Frame){
			arr_frame[frame_counter]=byte;
			frame_counter=frame_counter+1;
		}
		else if(byte==0xAA){
			memset(arr_frame,0,sizeof(arr_frame));
			block_Counter_frame=1;
			frame_counter=0;
			arr_frame[frame_counter]=byte;
			frame_counter=frame_counter+1;
			//free(arr_frame);
			//arr_dynamic = calloc(elements, sizeof(int)); //Array with 2 integer blocks
		}
		HAL_UART_Receive_IT(&huart1, &byte, 1);
	}
}
//------------------------------------------------------------------------------------------ EXTERNAL INTERUPT KEY
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
		Counter_Lock_Pass=0;
		if(Flag_Show_Auto==0 && Flag_System_Waitng==0 && Tune_Mode==0 ){
			if(Flag_Screen_Saver==0){
				if(GPIO_Pin== ESC_Key_Pin)
						Menu_ESC= !(HAL_GPIO_ReadPin(ESC_Key_GPIO_Port,ESC_Key_Pin));
				if(Flag_Show_CD==0 && Flag_Show_OD==0){
					if(GPIO_Pin== ENT_Key_Pin)
							Menu_ENT= !(HAL_GPIO_ReadPin(ENT_Key_GPIO_Port,ENT_Key_Pin));
					if(GPIO_Pin== Down_Key_Pin)
							Menu_Down= !(HAL_GPIO_ReadPin(Down_Key_GPIO_Port,Down_Key_Pin));
					if(GPIO_Pin== Up_Key_Pin)
							Menu_Up= !(HAL_GPIO_ReadPin(Up_Key_GPIO_Port,Up_Key_Pin));
				}
			}
		}
		if(GPIO_Pin== CD_Key_Pin)
				Menu_CD= !(HAL_GPIO_ReadPin(CD_Key_GPIO_Port,CD_Key_Pin));
		if(GPIO_Pin== OD_Key_Pin)
				Menu_OD= !(HAL_GPIO_ReadPin(OD_Key_GPIO_Port,OD_Key_Pin));
		if(GPIO_Pin==RST_Key_Pin)
				Menu_Reset= !(HAL_GPIO_ReadPin(RST_Key_GPIO_Port,RST_Key_Pin)); 

		Counter_Time_Screen_Saver=0;
		Flag_Screen_Saver=0;
	
		if(Lock_System==0 && Flag_System_Waitng==0 && Menu_CD==1 && Flag_OK_Setup==1){
			Manual_mode=1;
			Storage_Data_On_Mainboard(Byte_1_CD_Mode,Byte_1_Manual_Mode);
			Menu_CD=0;
			Flag_Show_OD=0;
			Flag_Show_CD=1;
			Counter_Auto_Show=0;
			Flag_Show_Auto=0;
		}
		if(Lock_System==0 && Flag_System_Waitng==0 && Menu_OD==1 && Flag_OK_Setup==1){
			Manual_mode=1;
			Storage_Data_On_Mainboard(Byte_1_OD_Mode,Byte_1_Manual_Mode);
			Menu_OD=0;	
			Flag_Show_OD=1;
			Flag_Show_CD=0;
			Counter_Auto_Show=0;
			Flag_Show_Auto=0;
		}	
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim14);

	
	HAL_UART_Receive_IT(&huart1, &byte, 1);
	
	Welcome_Seg();	

	Manage_Memory(Default_Flash_Array,0);
	Manage_Memory(Commercial_Flash_Array,1);
	Manage_Memory(Household_Flash_Array	,2);
	Manage_Memory(Office_Flash_Array,3);



	//------------------------------- Reading Flash and filling coefficient array
	while(1) {
		int32_t data = readFlash(addr);
		if(data == -1) {
			break;
		}
		Read_Array_Flash[Array_Flash_Counter]=data-1;
		Array_Flash_Counter=Array_Flash_Counter+1;
		addr += 8;
	}
	
	if(Read_Array_Flash[0]==0x00){
		Setup_Flash();
		//Read_Flash=1;
		HAL_NVIC_SystemReset();
	}
	
	if(Counter_ESC_Key!=0 && Counter_ENT_Key!=0){
		Tune_Mode=1;
	}
	
	HAL_Delay(100);
	Storage_Data_On_Mainboard(0x00,Byte_1_Setup);
	Array_Flash_Counter=0x00;
	HAL_Delay(100);
	
	if(Read_Array_Flash[6]==1 || Tune_Mode==1){
		setting=6;
		Tune_Mode=1;
		Read_Array_Flash[6]=Tune_Mode;
		Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
		incriment_array(1,sizeof(Read_Array_Flash),Read_Array_Flash);
		writeFlash(FLASH_USER_START_ADDR, Read_Array_Flash);
		incriment_array(-1,sizeof(Read_Array_Flash),Read_Array_Flash);
		Storage_Data_On_Mainboard(Tune_Mode,setting);
		setting=0;
	}
	
	
	

	Flag_Screen_Saver=1;
	Screen_Number=0;
	Flag_OK_Setup=1;
	//CRC_Value=Calculate_CRC();
	
  while (1)
  {
		
		if(Serial_Repeat==1 && Repeat_Time==1 && Lock_System==0){
			HAL_UART_Transmit(&huart1, Seial_Repeat_arr_frame, sizeof(Seial_Repeat_arr_frame), 1000);
			Number_Repeat_Serial=Number_Repeat_Serial+1;
			Repeat_Time=0;
		}
		//------------------------------- It's for illustrating Lock ("....") on the seven segment
		if(Flag_Lock_Pass_Show==1){
			Flag_Screen_Saver=0;
			Display("....","12345","0000");
			Counter_Lock_Pass=Counter_Lock_Pass+1;
			if(Counter_Lock_Pass>=200){
				Counter_Lock_Pass=0;
				Flag_Lock_Pass_Show=0;
				Flag_Screen_Saver=1;
			}
		}
		//------------------------------- It's for illustrating "AUTO" on the seven segment
		else if(Lock_System==0 && Flag_Show_Auto==1 && Flag_System_Waitng==0){
			Display("AUTO","12345","1111");
			Counter_Auto_Show=Counter_Auto_Show+1;
			if(Counter_Auto_Show>=200){
				Counter_Auto_Show=0;
				Flag_Show_Auto=0;
			}
		}
		
		//------------------------------- Check Input Frame and Response
		if(Serial_Available){
			Serial_Available=0;
			//----------------------------------------------- Check Input Frame and Response
			if(arr_frame[0]==Byte_1_Start_Frame && arr_frame[1]==Byte_2_Start_Frame  //Start Frames
				&& arr_frame[2]==Byte_1_Read_Frame 																		 //Type of Inputs
				&& arr_frame[9]==Byte_1_END_Frame && arr_frame[10]==Byte_2_END_Frame   //End Frames
			  && frame_counter==Length_Frame)                                        //Length of Inputs
			  {
				block_Counter_frame=0;
				//--------------------------------------------------------------------------------------------------------------------------------------
				arr_frame[2]=Byte_1_Write_Frame;                                //Set the UART to response mode
				if(arr_frame[4]>=0x01 && arr_frame[4]<=Number_OF_Settings){     //Just answer to Setting values ==> we have 107 settings on our device
					Response_Input_Data(Read_Array_Flash[arr_frame[4]]);
					Flag_System_Waitng=1;
					Counter_Wating=0;
					Flag_Screen_Saver=0;
					Serial_Repeat=0;

					if(Flag_Load_Data==0){
						switch(arr_frame[4]){
							case 2:
								Counter_Wating_Show=1;
							break;
							case 30:
								Counter_Wating_Show=2;
							break;
							case 55:
								Counter_Wating_Show=3;
							break;
							case 75:
								Counter_Wating_Show=4;
							break;
							case 107:
								Counter_Wating_Show=5;
								Flag_Load_Data=1;
								Flag_Screen_Saver=1;
								Flag_System_Waitng=0;
							break;
						}
					}
					//if(Tune_Mode==0){
						
					//}
					Number_Repeat_Serial=0;
				}
				//--------------------------------------------------------------------------------------------------------------------------------------
				if(arr_frame[4]==Byte_1_Receive_Data_Main_Board){             //It's for illustrating status of the main bord
					if(arr_frame[5]==Travel_Byte_1_main){
						switch(arr_frame[6]){
							case 0x00:
								Screen_Number=1; //Idle
							break;
							case 0x01:
								Screen_Number=2; //Stop
							break;
							case 0x02:
								Screen_Number=3; //Slow Close
							break;
							case 0x04:
								Screen_Number=4; //Opening
							break;
							case 0x08:
								Screen_Number=5; //Opened
							break;
							case 0x10:
								Screen_Number=6; //Closing
							break;
							case 0x20:
								Screen_Number=7; //Closed
							break;
							case 0x44:
								Screen_Number=8; //Opening(KP)
							break;
							case 0x48:
								Screen_Number=9; //Opened(KP)
							break;
							default:
									Screen_Number=26;
							break;
						}
					}
					
					else if(arr_frame[5]==Fault_Byte_1_main){
						switch(arr_frame[6]){
							case 0x01:
								Screen_Number=20; //Short Circuit
							break;
							case 0x02:
								Screen_Number=21; //Over Voltage
							break;
							case 0x04:
								Screen_Number=22; //Over Load
							break;
							case 0x08:
								Screen_Number=23; //Over Heat
							break;
							case 0x10:
								Screen_Number=24; //DC Link
							break;
							case 0x20:
								Screen_Number=25; //Encoder
							break;
							default:
								Screen_Number=26; //Value
								memset(Show_Variable,0,sizeof(Show_Variable));
								Show_Variable[0]=arr_frame[6];
							break;
						}
					}
					if(Transmision_Flag==0){
						Flag_Repeat_Off=1;
						Storage_Data_On_Mainboard(0x00,Byte_1_OK_Received);
					}	
				}
				//--------------------------------------------------------------------------------------------------------------------------------------
				else if(arr_frame[4]==Byte_1_OK_Received){                          //It's a Respose from main board
					memset(Seial_Repeat_arr_frame,32,sizeof(Seial_Repeat_arr_frame));
					Serial_Repeat=0;
					Repeat_Time=0;
					Number_Repeat_Serial=0;
					Transmision_Flag=0;
					Flag_System_Waitng=0;
				}
				//--------------------------------------------------------------------------------------------------------------------------------------
				else if(arr_frame[4]==Byte_1_Reset_LCD){                            //Reset LCD through main board
					HAL_UART_Receive_IT(&huart1, &byte, 0);
					HAL_NVIC_SystemReset();
					HAL_Delay(1000);
				}
				//--------------------------------------------------------------------------------------------------------------------------------------
				if(arr_frame[3]==0x00 && arr_frame[4]==Byte_1_Manual_Mode && arr_frame[5]==0x00 && arr_frame[6]==Byte_1_Tune_Mode){ // Turn off tune mode
					Tune_Mode=0;
					Lock_LCD=0;
					Flag_Repeat_Off=1;
					Storage_Data_On_Mainboard(0x00,Byte_1_OK_Received);
					Read_Array_Flash[6]=Tune_Mode;
					Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
					incriment_array(1,sizeof(Read_Array_Flash),Read_Array_Flash);
					writeFlash(FLASH_USER_START_ADDR, Read_Array_Flash);
					incriment_array(-1,sizeof(Read_Array_Flash),Read_Array_Flash);
					Reset_Menu=1;
				}
				//---------------------------
				frame_counter=0;
				memset(arr_frame,0,sizeof(arr_frame));
			}
		} // End of Serial Available
		
		//--------------------------------------------------------------------------------------------------------------------------------------
		else if(Reset_To_Default_Value==1){
			Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
			writeFlash(FLASH_USER_START_ADDR, Default_Flash_Array);
			Storage_Data_On_Mainboard(0,Byte_1_Device_Mode);
			HAL_NVIC_SystemReset();
		}
		//--------------------------------------------------------------------------------------------------------------------------------------
		if(Number_Repeat_Serial>=10){ //After 10 tries, the display will notify us that there is a problem with the connection.
			Lock_System=1;
			Flag_System_Waitng=0;
			Display("ERR ","12345","11111");
			//LCD_Puts(0,1,"Reset system:");
			//LCD_Put(Counter_Reset_system+48);
			memset(arr_frame,0,sizeof(arr_frame));
			if(Counter_Reset_system==0){
				HAL_NVIC_SystemReset();
			}
		}
		//--------------------------------------------------------------------------------------------------------------------------------------
		if(Flag_System_Waitng==1){ // It's for loading Data when we start our device: It shows us loading data.
			Select_Segment(5);
			if(Counter_Wating_Show==1){ //
				LED_Control(1,1);
			}
			else if(Counter_Wating_Show==2){//
				LED_Control(1,1);
				LED_Control(2,1);
			}
			else if(Counter_Wating_Show==3){//
				LED_Control(2,1);
				LED_Control(3,1);
			}
			else if(Counter_Wating_Show==4){//
				LED_Control(1,1);
				LED_Control(2,1);
				LED_Control(3,1);
				LED_Control(4,1);
			}
			else if(Counter_Wating_Show==5){//
				LED_Control(1,1);
				LED_Control(2,1);
				LED_Control(3,1);
				LED_Control(4,1);
				LED_Control(5,1);
				Counter_Wating_Show=0;
				Flag_System_Waitng=0;
			}
		}
		//--------------------------------------------------------------------------------------------------------------------------------------
		if(Lock_System==0 && Flag_Show_Auto==0){
			if((Manual_mode==1 && Toggle_Sevensegment==1)||(Tune_Mode==1 && Toggle_Sevensegment==1 && Flag_Load_Data==1 && Flag_System_Waitng==0)){
				Display("    ","12345","00000");
			}
			else if(Tune_Mode==1 && Toggle_Sevensegment==0 && Flag_Load_Data==0 && Flag_System_Waitng==0){
				Display("ERR ","12345","00000");
			}
			else if(Tune_Mode==1 && Toggle_Sevensegment==0 && Flag_Load_Data==1){
				Display("8888","12345","11111");
			}
			else if(Manual_mode==1 && Toggle_Sevensegment==0 && Flag_Show_OD==1){
				Display("OD  ","12345","11111");
			}
			else if(Manual_mode==1 && Toggle_Sevensegment==0 && Flag_Show_CD==1){
				Display("CD  ","12345","11111");
			}
		}
		//--------------------------------------------------------------------------------------------------------------------------------------
		if(Lock_System==0 && Flag_Lock_Pass_Show==0){
			if(Tune_Mode==0){	                           //Device status
				if(Flag_Screen_Saver==1){
					//LCD_Puts(0,0,"Status:         ");
					switch(Screen_Number){
						case 0:
								Display("-AA-","12345","00000");//Get Data
						break;
						case 1:
								Display("-  -","12345","00000");//
						break;
						case 2:
								Display("-ST-","12345","00000");//Stop
						break;
						case 3:
								Display("-  -","12345","00000");//
						break;
						case 4:
								Display("-OP-","12345","00000");//Opening
						break;
						case 5:
								Display("-OP-","12345","00000");//Opened
						break;
						case 6:
								Display("-CL-","12345","00000");//Closing
						break;
						case 7:
								Display("-CL-","12345","00000");//Closed
						break;
						case 8:
								Display("-OB-","12345","00000");//Opening(KP)
						break;
						case 9:
								Display("-OB-","12345","00000");//Opened(KP)
						break;
						//----------------------------------------------------------
						case 20:
							  Display("-  -","12345","00000");//
						break;
						case 21:
								Display("-  -","12345","00000");//
						break;
						case 22:
								Display("-  -","12345","00000");//
						break;
						case 23:
								Display("-  -","12345","00000");//
						break;
						case 24:
								Display("-  -","12345","00000");//
						break;
						case 25:
								Display("-  -","12345","00000");//
						break;
						case 26:
							switch(Show_Variable[0]){// Illustrate Value of the fault
								case 100:
									Display("-E0-","12345","00000");
								break;
								case 101:
									Display("-E1-","12345","00000");
								break;
								case 102:
									Display("-E2-","12345","00000");
								break;
								case 103:
									Display("-E3-","12345","00000");
								break;
								case 104:
									Display("-E4-","12345","00000");
								break;
								case 105:
									Display("-E5-","12345","00000");
								break;
								case 106:
									Display("-E6-","12345","00000");
								break;
								case 107:
									Display("-E7-","12345","00000");
								break;
								case 108:
									Display("-E8-","12345","00000");
								break;
								case 109:
									Display("-E9-","12345","00000");
								break;
								default:
									Display("----","12345","00000");
								break;
							}		
						break;
					}
				}
				//----------------------------------------------- Chosing "Menu"
				else if(Flag_Screen_Saver==0 && Flag_Lock_Pass_Show==0 && Flag_System_Waitng==0 && Flag_Show_Auto==0 && Tune_Mode==0){
					if(Manual_mode==0 && Flag_Show_Auto==0){
						Menu_Data_Display(&PM_Menu);
					}
					Menu_Selection(&PM_Menu,Menu_ESC,Menu_ENT,Menu_Down,Menu_Up,Menu_Reset,Fault_Vector);
					Menu_ESC=0;Menu_ENT=0;Menu_Up=0;Menu_Down=0;
				}
			}
		}
		//----------------------------------------------- Illustrating Manual mode or Tune mode on LCD
		if(Lock_LCD==0 && Tune_Mode==1){
			Lock_LCD=1;
			//LCD_Clear();
			//LCD_Puts(0,0,"Tune Mode...");
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 6399;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 999;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 6399;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DP_SEG_Pin|G_SEG_Pin|F_SEG_Pin|E_SEG_Pin
                          |D_SEG_Pin|C_SEG_Pin|B_SEG_Pin|A_SEG_Pin
                          |D1_Pin|D4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D2_Pin|LED_Select_Pin|D3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DP_SEG_Pin G_SEG_Pin F_SEG_Pin E_SEG_Pin
                           D_SEG_Pin C_SEG_Pin B_SEG_Pin D1_Pin
                           D4_Pin */
  GPIO_InitStruct.Pin = DP_SEG_Pin|G_SEG_Pin|F_SEG_Pin|E_SEG_Pin
                          |D_SEG_Pin|C_SEG_Pin|B_SEG_Pin|D1_Pin
                          |D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : A_SEG_Pin */
  GPIO_InitStruct.Pin = A_SEG_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(A_SEG_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Down_Key_Pin ENT_Key_Pin RST_Key_Pin */
  GPIO_InitStruct.Pin = Down_Key_Pin|ENT_Key_Pin|RST_Key_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : Up_Key_Pin */
  GPIO_InitStruct.Pin = Up_Key_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Up_Key_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ESC_Key_Pin */
  GPIO_InitStruct.Pin = ESC_Key_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ESC_Key_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CD_Key_Pin */
  GPIO_InitStruct.Pin = CD_Key_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(CD_Key_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : D2_Pin LED_Select_Pin D3_Pin */
  GPIO_InitStruct.Pin = D2_Pin|LED_Select_Pin|D3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : OD_Key_Pin */
  GPIO_InitStruct.Pin = OD_Key_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(OD_Key_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_3_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
