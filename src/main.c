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
uint16_t b, x, s, f, y, z, g, posx, posy, h, i, j;
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
	gfx_SetTextBGColor(255);//Transparent text background
	gfx_SetTextScale(1,1);//Text size for Title
	gfx_SetTextXY(110,10);//Title position
	gfx_PrintString("Roulette v0.2.2");//Print title
}

void DrawCursor() //This function shows the cursor
{
	gfx_SetColor(250);//Light green
	h = 0;
	i = 0;
	if(posx == 2){h = 23;}//Larger cursor in the left column
	if(posx == 2 && (posy == 5 || posy == 8)){i = 28;}//Larger cursor for the black and red symbols
	gfx_FillRectangle(posx * 18 + 203 - h, posy * 14 + 1, 17 + h, 13 + i);//cursor
}

void PrintNumber()
{
	gfx_FillRectangle(56,200,50,30);//Clear old number
	gfx_SetTextScale(3,3);//Text size for number
	gfx_SetTextXY(56,200);//number position
	gfx_SetTextFGColor(c);//Text color of number
	gfx_PrintInt(e,2);//Print number
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
	*/
	posx = 1;
	posy = 1;
	uint8_t colors[37] = {254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,251};//color array
	uint8_t numbers[37] = {26,3,35,12,28,7,29,18,22,9,31,14,20,1,33,16,24,5,10,23,8,30,11,36,13,27,6,34,17,25,2,21,4,19,15,32,0};//number array
	
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
	
	gfx_SwapDraw();
	gfx_FillScreen(253);
	do //Loop everything
	{
		while (kb_Data[1] != kb_Clear && kb_Data[1] != kb_2nd)//Controls
		{
			gfx_SetColor(253);
			gfx_FillRectangle(210,10,105,220);//Green background
			DrawTitle();		
			if (kb_Data[1] == kb_Clear || kb_Data[1] == kb_2nd) {break;}//Exit
			
			PrintNumber();
			DrawCursor();
			createTableau();
			gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
			gfx_RLETSprite_NoClip(pfeil, 59, 36);//Show arrow
			
			if (kb_Data[1] == kb_Clear || kb_Data[1] == kb_2nd) {break;}//Exit
			
			/*Tableau navigation*/
			if(kb_Data[1] == kb_Up)//Up
			{
				if(posy > 1){posy = posy - 1;}
			}
			if(kb_Data[1] == kb_Down)//Down
			{
				if(posx == 2 && posy == 4){posy = 5;}
				else if(posx == 2 && posy == 5){posy = 8;}
				else if(posx == 2 && posy == 8){posy = 11;}
				else if(posy < 14){posy = posy + 1;}	
			}
			if(kb_Data[1] == kb_Left)//Left
			{
				if(posx > 2){posx = posx - 1;}
			}
			if(kb_Data[1] == kb_Right)//Right
			{
				if(posx < 5){posx = posx + 1;}
			}
			if((posx == 1 && posy == 1) || (posx == 2 && posy == 1) || (posx == 3 && posy == 1) || (posx == 5 && posy == 1)){posx = 4;}
			if((posx == 2 && posy == 6) || (posx == 2 && posy == 7)){posy = 5;}
			if((posx == 2 && posy == 9) || (posx == 2 && posy == 10)){posy = 8;}
			/*Tableau navigation*/
			
			gfx_SwapDraw();
			for(x = 0; x < 121; x++){gfx_SetColor(253); gfx_FillRectangle(150,100,20,100);if(kb_Data[1] == kb_2nd || kb_Data[1] == kb_Clear){break;}}
		}			
		if (kb_Data[1] == kb_Clear) {break;}//Exit
		srand(rtc_Time());//Set random seed
		
		DrawCursor();
		createTableau();

		/*Generate random amount to rotate*/
		b = 50000;
		s = rand() % 256;
		/*Generate random amount to rotate*/
		
		f = 0;
		for (x = 0; ++x;)
		{
			if (kb_Data[1] == kb_Clear) {f = 1; break;}//Exit
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
		if (f == 1) {break;}//Exit
		
		DrawTitle();
		gfx_RotateSprite(ro, rotate_sprite, n);//Rotate the sprite
		gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
		gfx_RLETSprite_NoClip(pfeil, 59, 36);//Show arrow
		
		DrawCursor();
		createTableau();
		
		
		gfx_SwapDraw();
	} while(1);
		
    gfx_End();// Close the graphics
}
