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

uint16_t b;
int e ,c;
uint8_t a, n;
kb_key_t key;


void main(void)
{
	/*
	Important Colors:
	Black = 231
	Green = 7
	Red = 8
	Grey = 12
	*/
    uint16_t x, s, f, y, z, g;
	uint8_t colors[37] = {231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,231,8,12};
	uint8_t numbers[37] = {26,3,35,12,28,7,29,18,22,9,31,14,20,1,33,16,24,5,10,23,8,30,11,36,13,27,6,34,17,25,2,21,4,19,15,32,0};
	
    gfx_Begin(); //Start the graphics 
    gfx_SetPalette(palette_gfx, sizeof_palette_gfx, 0); //Load Palette
	s = 0;
	gfx_SetDrawBuffer();
	gfx_RotateSprite(ro, rotate_sprite, a + s);//Rotate the sprite
	gfx_FillScreen(7);//Green background
	gfx_SetTextFGColor(231);//Black text color
	gfx_SetTextBGColor(255);//Transparent text background
	gfx_SetTextScale(1,1);//Text size for title
	gfx_SetTextXY(110,10);//Title position
	gfx_PrintString("Roulette v0.2.0");//Print title
	gfx_SetTextXY(49,228);//Text position
	gfx_PrintString("Press 2nd to spin or Clear to exit");//Print text
	gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
	gfx_TransparentSprite_NoClip(pfeil, 59, 36);//Show arrow
	
	/*Create table*/ 
	gfx_SetColor(231);
	for(y = 0; y<15; ++y)
	{
		gfx_Line(215, (y + 1) * 14, 310, (y + 1) * 14);
	}
	for(z = 0; z<6; ++z)
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
	gfx_FillRectangle_NoClip(215,84,41,15);
	gfx_FillRectangle_NoClip(215,126,41,15);
	gfx_SetColor(8);
	gfx_FillTriangle(235,75,225,90,245,90);
	gfx_FillTriangle(235,105,225,90,245,90);
	gfx_SetColor(231);
	gfx_FillTriangle(235,117,225,132,245,132);
	gfx_FillTriangle(235,147,225,132,245,132);
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
	for(y = 0; y < 12; ++y)
	{
		for(z = 0; z<3; ++z)
		{
			gfx_SetTextXY(258 + z * 18, 31 + y * 14);
			gfx_PrintInt(g, 2);
			g++;
		}
	}
	/*Print numbers in table*/
	
	gfx_SwapDraw();
	
	do //Loop everything
	{
		while (kb_Data[1] != kb_Clear && kb_Data[1] != kb_2nd); //Wait for key press
		if (kb_Data[1] == kb_Clear) {break;}//Exit
		srand(rtc_Time());//Set random seed
    
		/*Generate random amount to rotate*/
		b = 50000;
		s = rand() % 256;
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
		
			/*Generate random amount to rotate*/
	
			gfx_SetDrawBuffer();
			gfx_RotateSprite(ro, rotate_sprite, a + s);//Rotate the sprite
			gfx_FillScreen(7);//Green background
			gfx_SetTextFGColor(231);//Black text color
			gfx_SetTextBGColor(255);//Transparent text background
			gfx_SetTextScale(1,1);//Text size for Title
			gfx_SetTextXY(110,10);//Title position
			gfx_PrintString("Roulette v0.2.0");//Print title
	
			gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
			gfx_TransparentSprite_NoClip(pfeil, 59, 36);//Show arrow
			gfx_SwapDraw();
		}
		if (f == 1) {break;}//Exit
		/*Determine number*/
		c = colors[n / 7];
		e = numbers[n / 7];
		/*Determine number*/
	
		gfx_SetDrawBuffer();
		gfx_FillScreen(7);//Green background
		gfx_SetTextFGColor(231);//Black text color
		gfx_SetTextBGColor(255);//Transparent text background
		gfx_SetTextScale(1,1);//Text size for Title
		gfx_SetTextXY(110,10);//Title position
		gfx_PrintString("Roulette v0.2.0");//Print title
		gfx_SetTextXY(49,228);//Text position
		gfx_PrintString("Press 2nd to spin or Clear to exit");//Print text
		gfx_SetTextScale(3,3);//Text size for number
		gfx_SetTextXY(56,200);//number position
		gfx_SetTextFGColor(c);//Text color of number
		gfx_PrintInt(e,2);//Print number
	
		gfx_RotateSprite(ro, rotate_sprite, n);//Rotate the sprite
		gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
		gfx_TransparentSprite_NoClip(pfeil, 59, 36);//Show arrow
	
		/*Create table*/ 
		gfx_SetColor(231);
		for(y = 0; y<15; ++y)
		{
			gfx_Line(215, (y + 1) * 14, 310, (y + 1) * 14);
		}
		for(z = 0; z<6; ++z)
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
		gfx_FillRectangle_NoClip(215,84,41,15);
		gfx_FillRectangle_NoClip(215,126,41,15);
		gfx_SetColor(8);
		gfx_FillTriangle(235,75,225,90,245,90);
		gfx_FillTriangle(235,105,225,90,245,90);
		gfx_SetColor(231);
		gfx_FillTriangle(235,117,225,132,245,132);
		gfx_FillTriangle(235,147,225,132,245,132);
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
		for(y = 0; y < 12; ++y)
		{
			for(z = 0; z<3; ++z)
			{
				gfx_SetTextXY(258 + z * 18, 31 + y * 14);
				gfx_PrintInt(g, 2);
				g++;
			}
		}
		/*Print numbers in table*/
		
		gfx_SwapDraw();
	} while(1);
		
    gfx_End();// Close the graphics
}
