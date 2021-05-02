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
	/*Create table*/ 
	gfx_SetColor(231);
	for(y = 0; y<15; ++y)//Horizontal lines
	{
		j = 41;
		if(y != 5 && y != 6 && y != 8 && y != 9)//Shorter vertical lines
		{
			j = 0;	
		}
		gfx_Line(215 + j, (y + 1) * 14, 310, (y + 1) * 14);
	}
	for(z = 0; z<6; ++z)//Vertical lines
	{
		if (z != 1 && z != 0)
		{
			gfx_Line(220 + (z * 18), 14, 220 + (z * 18), 210);
		}
	}
	/*Create table*/ 
	
	/*Print numbers in table*/
	gfx_SetTextScale(1,1);//Text size for numbers
	gfx_SetTextFGColor(231);//Black text color
	gfx_SetTextXY(280, 17);
	gfx_PrintString("0");
	gfx_SetTextXY(262, 199);
	gfx_PrintString("^");
	gfx_SetTextXY(280, 199);
	gfx_PrintString("^");
	gfx_SetTextXY(298, 199);
	gfx_PrintString("^");
	gfx_SetColor(7);
	gfx_FillRectangle_NoClip(215,14,41,14);
	gfx_SetColor(8);//Red symbol
	gfx_FillTriangle(235,75,225,90,245,90);//Red symbol
	gfx_FillTriangle(235,105,225,90,245,90);//Red symbol
	gfx_SetColor(231);//Black symbol
	gfx_FillTriangle(235,117,225,132,245,132);//Black symbol
	gfx_FillTriangle(235,147,225,132,245,132);//Black symbol
	gfx_Line(215,29,215,210);
	gfx_SetTextXY(222, 31);
	gfx_PrintString("1-12");
	gfx_SetTextXY(217, 45);
	gfx_PrintString("13-24");
	gfx_SetTextXY(217, 59);
	gfx_PrintString("25-36");
	gfx_SetTextXY(222, 157);
	gfx_PrintString("1-18");
	gfx_SetTextXY(217, 171);
	gfx_PrintString("19-36");
	gfx_SetTextXY(225, 185);
	gfx_PrintString("ODD");
	gfx_SetTextXY(222, 199);
	gfx_PrintString("EVEN");
	g = 1;
	for(y = 0; y < 12; ++y)//Numbers 1-36
	{
		for(z = 0; z<3; ++z)
		{
			gfx_SetTextXY(258 + z * 18, 31 + y * 14);
			gfx_PrintInt(g, 2);
			g++;
		}
	}
	/*Print numbers in table*/
}

void DrawTitle() //This function shows the title
{
	gfx_SetTextFGColor(231);//Black text color
	gfx_SetTextBGColor(255);//Transparent text background
	gfx_SetTextScale(1,1);//Text size for Title
	gfx_SetTextXY(110,10);//Title position
	gfx_PrintString("Roulette v0.2.0");//Print title
}

void DrawCursor() //This function shows the cursor
{
	gfx_SetColor(226);//Light green
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
	Black = 231
	Green = 7
	Red = 8
	Grey = 11
	Light Green = 226
	*/
	posx = 1;
	posy = 1;
	uint8_t colors[37] = {231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,11};//color array
	uint8_t numbers[37] = {26,3,35,12,28,7,29,18,22,9,31,14,20,1,33,16,24,5,10,23,8,30,11,36,13,27,6,34,17,25,2,21,4,19,15,32,0};//number array
	
    gfx_Begin(); //Start the graphics 
    gfx_SetPalette(palette_gfx, sizeof_palette_gfx, 0); //Load Palette
	s = 0;
	gfx_SetDrawBuffer();
	gfx_RotateSprite(ro, rotate_sprite, a + s);//Rotate the sprite
	gfx_FillScreen(7);//Green background
	DrawTitle();
	gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
	gfx_TransparentSprite_NoClip(pfeil, 59, 36);//Show arrow
	
	createTableau();
	
	gfx_SwapDraw();
	gfx_FillScreen(7);
	do //Loop everything
	{
		while (kb_Data[1] != kb_Clear && kb_Data[1] != kb_2nd)//Controls
		{
			gfx_SetColor(7);
			gfx_FillRectangle(210,10,105,220);//Green background
			DrawTitle();		
			if (kb_Data[1] == kb_Clear || kb_Data[1] == kb_2nd) {break;}//Exit
			
			PrintNumber();
			DrawCursor();
			createTableau();
			gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
			gfx_TransparentSprite_NoClip(pfeil, 59, 36);//Show arrow
			
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
			for(x = 0; x < 121; x++){gfx_SetColor(7); gfx_FillRectangle(150,100,20,100);if(kb_Data[1] == kb_2nd || kb_Data[1] == kb_Clear){break;}}
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
			gfx_SetColor(7);
			DrawTitle();
			
			gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
			gfx_TransparentSprite_NoClip(pfeil, 59, 36);//Show arrow
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
		gfx_TransparentSprite_NoClip(pfeil, 59, 36);//Show arrow
		
		DrawCursor();
		createTableau();
		
		
		gfx_SwapDraw();
	} while(1);
		
    gfx_End();// Close the graphics
}
