#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <keypadc.h>
#include <graphx.h>
#include <debug.h>

#include "gfx/palette_gfx.h"
#include "gfx/gfx.h"


gfx_UninitedSprite(rotate_sprite, ro_width, ro_height);//sprite buffer

/*Declaring Variables*/
uint16_t b, x, s, f, y, z, g, posx, posy, h, i, j, k, l, color, chip;
int e ,c;
uint8_t a, n;
kb_key_t key;
/*Declaring Variables*/


void createTableau()//this functions shows the tableau
{
	gfx_RLETSprite_NoClip(tableau,215,15);
}

void DrawTitle() //This function shows the title
{
	gfx_SetTextFGColor(254);//Black text color
	gfx_SetTextScale(1,1);//Text size for Title
	gfx_SetTextXY(110,10);//Title position
	gfx_PrintString("Roulette v0.2.4");//Print title
}

void DrawCursor() //This function shows the cursor
{
	gfx_SetColor(250);//Light green
	h = 0;
	i = 0;
	l = 0;
	if(posx == 2){h = 23; l = 23;}//Larger cursor in the left column
	if(posx == 1){h = 23; l = 61;}//Larger cursor for the buttons
	if(posx == 2 && (posy == 5 || posy == 8)){i = 28;}//Larger cursor for the black and red symbols
	gfx_FillRectangle(posx * 18 + 203 - l, posy * 14 + 1, 17 + h, 14 + i);//cursor
}

void PrintNumber()
{
	gfx_SetColor(253);
	gfx_FillRectangle(56,200,50,30);//Clear old number
	gfx_SetTextScale(3,3);//Text size for number
	gfx_SetTextXY(56,200);//number position
	gfx_SetTextFGColor(c);//Text color of number
	gfx_PrintInt(e,2);//Print number
}

void DrawChip(type,cx,cy)
{
	gfx_SetTextFGColor(254);
	if(type == 1){color = 252;}//Red
	if(type == 2){color = 248;}//Light Blue
	if(type == 5){color = 249;}//Yellow
	if(type == 10){color = 247;}//Dark Blue
	if(type == 20){color = 251;}//Grey
	if(type == 50){color = 246;}//Purple
	gfx_SetColor(color);
	gfx_FillCircle(cx,cy,5);
	gfx_SetColor(0);
	gfx_FillCircle(cx,cy,3);
	
}

void DrawButtons()//This function creates the Menu
{
	gfx_SetColor(254);
	for(k = 0; k < 7; k++)
	{
		gfx_Rectangle(160,57 + (14 * k),41,15);
	}
	gfx_SetTextFGColor(254);//Black text color
	gfx_SetTextScale(1,1);
	gfx_SetTextXY(165,61);
	gfx_PrintString("Spin");//Print Text
	gfx_SetTextXY(167,75);
	gfx_PrintString("1");//Print Text
	DrawChip(1,187,78);
	gfx_SetTextXY(167,89);
	gfx_PrintString("2");//Print Text
	DrawChip(2,187,92);
	gfx_SetTextXY(167,103);
	gfx_PrintString("5");//Print Text
	DrawChip(5,187,106);
	gfx_SetTextXY(163,117);
	gfx_PrintString("10");//Print Text
	DrawChip(10,187,120);
	gfx_SetTextXY(163,131);
	gfx_PrintString("20");//Print Text
	DrawChip(20,187,134);
	gfx_SetTextXY(163,145);
	gfx_PrintString("50");//Print Text
	DrawChip(50,187,148);

}

void main(void)
{
	/*
	List of important colors:
	Black =	254
	Green = 253
	Red = 252
	Grey = 251
	Light Green = 250
	Yellow = 249
	Light Blue = 248
	Dark Blue = 247
	Purple = 246
	*/
	posx = 4;
	posy = 1;
	uint8_t colors[37] = {254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,251};//color array
	uint8_t numbers[37] = {26,3,35,12,28,7,29,18,22,9,31,14,20,1,33,16,24,5,10,23,8,30,11,36,13,27,6,34,17,25,2,21,4,19,15,32,0};//number array
	chip = 1;
	
    gfx_Begin(); //Start the graphics 
    gfx_SetPalette(palette_gfx, sizeof_palette_gfx, 0); //Load Palette
	s = 0;
	gfx_SetDrawBuffer();
	gfx_RotateSprite(ro, rotate_sprite, a + s);//Rotate the sprite
	gfx_FillScreen(253);//Green background
	DrawTitle();
	gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
	gfx_RLETSprite_NoClip(pfeil, 59, 36);//Show arrow
	
	createTableau();
	DrawButtons();
	
	gfx_SwapDraw();
	gfx_FillScreen(253);
	do //Loop everything
	{
		while (kb_Data[6] != kb_Clear)//Controls
		{
			kb_Scan();
			gfx_SetColor(253);
			gfx_FillRectangle(160,10,155,220);//Green background
			DrawTitle();		
			gfx_SetTextXY(163,167);
			gfx_PrintInt(chip,2);//Print Text
			DrawChip(chip,187,170);
			PrintNumber();
			DrawCursor();
			createTableau();
			DrawButtons();
			gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
			gfx_RLETSprite_NoClip(pfeil, 59, 36);//Show arrow
			
			/*Tableau navigation*/
			if(kb_Data[7] == kb_Up)//Up
			{
				if(posy > 1){if(!(posx == 1 && posy == 4)){posy = posy - 1;}}
			}
			if(kb_Data[7] == kb_Down)//Down
			{
				if(posx == 2 && posy == 4){posy = 5;}
				else if(posx == 2 && posy == 5){posy = 8;}
				else if(posx == 2 && posy == 8){posy = 11;}
				else if(posy < 14){if(!(posx == 1 && posy == 10)){posy = posy + 1;}}	
			}
			if(kb_Data[7] == kb_Left)//Left
			{
				if((posx == 2 && posy == 4) || (posx == 2 && posy == 5) || (posx == 2 && posy == 8)){posx = 1;}
				else if(posx > 2){posx = posx - 1;}
				
			}
			if(kb_Data[7] == kb_Right)//Right
			{
				if(posx < 5){posx = posx + 1;}
			}
			if(kb_Data[1] == kb_2nd)//2nd
			{
				if(posx == 1 && posy == 4){break;}//spin
				if(posx == 1 && posy == 5){chip = 1;}
				if(posx == 1 && posy == 6){chip = 2;}
				if(posx == 1 && posy == 7){chip = 5;}
				if(posx == 1 && posy == 8){chip = 10;}
				if(posx == 1 && posy == 9){chip = 20;}
				if(posx == 1 && posy == 10){chip = 50;}
			}
			
			if((posx == 1 && posy == 1) || (posx == 2 && posy == 1) || (posx == 3 && posy == 1) || (posx == 5 && posy == 1)){posx = 4;}
			if((posx == 2 && posy == 6) || (posx == 2 && posy == 7)){posy = 5;}
			if((posx == 2 && posy == 9) || (posx == 2 && posy == 10)){posy = 8;}
			/*Tableau navigation*/
			
			gfx_SwapDraw();
			for(x = 0; x < 16; x++){gfx_SetColor(253); kb_Scan(); DrawTitle();if(kb_Data[1] == kb_2nd || kb_Data[6] == kb_Clear){break;}} //some delay
		}			
		if (kb_Data[6] == kb_Clear) {break;}//Exit
		srand(rtc_Time());//Set random seed
		
		DrawCursor();
		createTableau();
		DrawButtons();
		
		/*Generate random amount to rotate*/
		b = 50000;
		s = rand() % 256;
		/*Generate random amount to rotate*/
		
		f = 0;
		for (x = 0; ++x;)
		{
			kb_Scan();
			if (kb_Data[6] == kb_Clear) {f = 1; break;}//Exit
			int r = rand() % 1000;
			b = b - r;
			a = a + b / 5000;
			if (b / 2000 < 1)
			{
				break;
			}
			n = a + s;
	
			gfx_RotateSprite(ro, rotate_sprite, a + s);//Rotate the sprite
			gfx_SetColor(253);
			DrawTitle();
			
			gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
			gfx_RLETSprite_NoClip(pfeil, 59, 36);//Show arrow
			gfx_SwapDraw();
			
			/*Determine number*/
			c = colors[n / 7];
			e = numbers[n / 7];
			/*Determine number*/
			PrintNumber();
		}
	} while(1);
		
    gfx_End();// Close the graphics
}
