#include "Display.h"
#include "main.h"


char Segment_Number=4;
char LEDS_Number=5;     //we have 5 sections for illustrating characters or LEDs //LEDs is known as a segments
char Display_storage[4]="    ";




void Show_Segment(char Input){
	
	switch(Input){
		
		case ' ':
			//Show on sevensegment: 
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		
		case '0':
			//Show on sevensegment: 0
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
			
		case '1':
			//Show on sevensegment: 1
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		
		case '2':
			//Show on sevensegment: 2
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		
		case '3':
			//Show on sevensegment: 3
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		
		case '4':
			//Show on sevensegment: 4
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		
		case '5':
			//Show on sevensegment: 5
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		
		case '6':
			//Show on sevensegment: 6
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		
		case '7':
			//Show on sevensegment: 7
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		
		case '8':
			//Show on sevensegment: 8
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		
		case '9':
			//Show on sevensegment: 9
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);	
		break;
		
    //--------------------------------------------------------------------------
		
		case 'A':
			//Show on sevensegment: A
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'B':
			//Show on sevensegment: D
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'C'://small
			//Show on sevensegment: C
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'D':
			//Show on sevensegment: D
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'E':
			//Show on sevensegment: E
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'F':
			//Show on sevensegment: F
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		
		case 'H':
			//Show on sevensegment: H
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'I':
			//Show on sevensegment: I
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);	
		break;
		
		case 'J':
			//Show on sevensegment: J
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		
		/*case 'K':///not
			//Show on sevensegment: k
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;*/
		
		case 'L':
			//Show on sevensegment: L
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'N'://small
			//Show on sevensegment: n
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'O': // small
			//Show on sevensegment: o
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'P':
			//Show on sevensegment: P
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'R'://small
			//Show on sevensegment: r
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'S':
			//Show on sevensegment: S
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'T'://not
			//Show on sevensegment: T
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'U':// conveted to U
			//Show on sevensegment: U
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		case 'V':
			//Show on sevensegment: U
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);
		break;
		
		//----------------------------------------------------------------------------------- 
		case 'a'://not
			//Show on sevensegment: -
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		
		case 'b':
			//Show on sevensegment: |
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		case 'c':
			//Show on sevensegment: |
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		case 'd':
			//Show on sevensegment: -
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		
		
		case 'e'://not
			//Show on sevensegment: |
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		case 'f'://not
			//Show on sevensegment: |
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		case '-'://not
			//Show on sevensegment: -
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);		
		break;
		case '.'://not
			//Show on sevensegment: -
			HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_RESET);		
		break;

		
		
		
		default:
			//Segments are Off
			/*HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_SEG_GPIO_Port, F_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_SEG_GPIO_Port, G_SEG_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DP_SEG_GPIO_Port, DP_SEG_Pin, GPIO_PIN_SET);*/
		break;
	}

}
//--------------------------------------------------------------
void Select_Segment(uint8_t Input){
	

	HAL_Delay(1);

	
	
	switch(Input){
		
		
		
		case 0:
			//Select Segment: All OFF
			HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_Select_GPIO_Port, LED_Select_Pin, GPIO_PIN_SET);

		break;
		case 1:
			//Select Segment: D1
			HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_Select_GPIO_Port, LED_Select_Pin, GPIO_PIN_SET);

		break;
		case 2:
			//Select Segment: D2
			HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_Select_GPIO_Port, LED_Select_Pin, GPIO_PIN_SET);

		break;
		case 3:
			//Select Segment: D3
			HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_Select_GPIO_Port, LED_Select_Pin, GPIO_PIN_SET);

		break;
		
		case 4:
			//Select Segment: D3
			HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_RESET);//EN
			HAL_GPIO_WritePin(LED_Select_GPIO_Port, LED_Select_Pin, GPIO_PIN_SET);
		break;
		
		case 5:
			//Select Segment: LEDS
			HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_SET);//EN
			HAL_GPIO_WritePin(LED_Select_GPIO_Port, LED_Select_Pin, GPIO_PIN_RESET);

		break;
	}
}


//--------------------------------------------------------------
void LED_Control(char LED_Number,char LED_Status){
	switch(LED_Number){
		
		case 0:
					
		break;
		//------------------------------------------------------------------
		case 1:	
			if(LED_Status==1){
				HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_RESET);//EN
			}
			else if(LED_Status==0){
				HAL_GPIO_WritePin(A_SEG_GPIO_Port, A_SEG_Pin, GPIO_PIN_SET);
			}
		break;
		//------------------------------------------------------------------
		case 2:		
			if(LED_Status==1){
				HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_RESET);//EN
			}
			else if(LED_Status==0){
				HAL_GPIO_WritePin(B_SEG_GPIO_Port, B_SEG_Pin, GPIO_PIN_SET);
			}
		break;
		//------------------------------------------------------------------
		case 3:
		
			if(LED_Status==1){
				HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_RESET);//EN
			}
			else if(LED_Status==0){
				HAL_GPIO_WritePin(C_SEG_GPIO_Port, C_SEG_Pin, GPIO_PIN_SET);
			}
		break;
		//------------------------------------------------------------------
		case 4:
		
			if(LED_Status==1){
				HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_RESET);//EN
			}
			else if(LED_Status==0){
				HAL_GPIO_WritePin(D_SEG_GPIO_Port, D_SEG_Pin, GPIO_PIN_SET);
			}
		break;
		//------------------------------------------------------------------
		case 5:
		
			if(LED_Status==1){
				HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_RESET);//EN
			}
			else if(LED_Status==0){
				HAL_GPIO_WritePin(E_SEG_GPIO_Port, E_SEG_Pin, GPIO_PIN_SET);
			}
		break;
		//------------------------------------------------------------------
	}
	
}
//--------------------------------------------------------------
void Display(char Word_Segment[Segment_Number],char LED_Select[LEDS_Number],char LEDS_Status[LEDS_Number]){
	for(uint8_t Segment_Counter=1; Segment_Counter<=Segment_Number ; Segment_Counter++){
		Select_Segment(Segment_Counter);
		Show_Segment(Word_Segment[Segment_Counter-1]);
	}
	
	Select_Segment(5); //Select LED's Segment
	
	for(uint8_t Segment_Counter=0; Segment_Counter<LEDS_Number ; Segment_Counter++){
		LED_Control(LED_Select[Segment_Counter]-48,LEDS_Status[Segment_Counter]-48);
	}
}
//--------------------------------------------------------------