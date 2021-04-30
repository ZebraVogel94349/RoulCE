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


gfx_UninitedSprite(rotate_sprite, ro_width, ro_height);//sprite buffer

uint16_t a, b;
int n, keypressed,e ,c;
uint8_t stop;
bool prevkey;
kb_key_t key;


void main(void)
{
    uint16_t k, x, s, i;
	
    gfx_Begin(); //Start the graphics 
    gfx_SetPalette(palette_gfx_pal, sizeof_palette_gfx_pal, 0); //Load Palette
	s = 0;
	gfx_SetDrawBuffer();
	gfx_RotateSprite(ro, rotate_sprite, a + s);//Rotate the sprite
	gfx_FillScreen(9);//Green background
	gfx_SetTextFGColor(249);//Black text color
	gfx_SetTextBGColor(255);//Transparent text background
	gfx_SetTextScale(1,1);//Text size for Title
	gfx_SetTextXY(110,10);//Title position
	gfx_PrintString("Roulette v0.1.1");//Print title
	gfx_SetTextXY(49,228);//Text position
			gfx_PrintString("Press 2nd to spin or Clear to exit");//Print text
	gfx_TransparentSprite_NoClip(rotate_sprite, 12, 64);//Show rotated sprite
	gfx_TransparentSprite_NoClip(pfeil, 59, 36);//Show arrow
	gfx_SwapDraw();
	
	for (i = 0; ++i;) //Loop everything
	{
		while (kb_Data[1] != kb_Clear && kb_Data[1] != kb_2nd); //Wait for key press
		if (kb_Data[1] == kb_Clear) {break;}//Exit
	
		srand(rtc_Time());//Set random seed
    
		/*Generate random amount to rotate*/
		b = 50000;
		s = rand() % 256;
		for (x = 0; ++x;)
		{
			int r = rand() % 1000;
			b = b - r;
			a = a + b / 5000;
			if (b / 2000 < 1)
			{
				break;
			}
			n = a + s;
			
			/*Keep rotation value below 256*/
			if (a > 255)
			{
				a = a - 256;
			}
			/*Keep rotation value below 256*/
		
			/*Generate random amount to rotate*/
	
			gfx_SetDrawBuffer();
			gfx_RotateSprite(ro, rotate_sprite, a + s);//Rotate the sprite
			gfx_FillScreen(9);//Green background
			gfx_SetTextFGColor(249);//Black text color
			gfx_SetTextBGColor(255);//Transparent text background
			gfx_SetTextScale(1,1);//Text size for Title
			gfx_SetTextXY(110,10);//Title position
			gfx_PrintString("Roulette v0.1.1");//Print title
	
			gfx_TransparentSprite_NoClip(rotate_sprite, 12, 64);//Show rotated sprite
			gfx_TransparentSprite_NoClip(pfeil, 59, 36);//Show arrow
			gfx_SwapDraw();
		}
	
		/*Keep rotation value below 256*/
		if (n > 255)
		{
			n = n - 256;
		}
		/*Keep rotation value below 256*/
	
		/*Determine number*/
		if(n >= 0 && n < 7){e = 26; c = 249;}
		if(n >= 7 && n < 14){e = 3;  c = 1;}
		if(n >= 14 && n < 20){e = 35; c = 249;}
		if(n >= 20 && n < 28){e = 12; c = 1;}
		if(n >= 28 && n < 35){e = 28; c = 249;}
		if(n >= 35 && n < 42){e = 7; c = 1;}
		if(n >= 42 && n < 48){e = 29; c = 249;}
		if(n >= 48 && n < 55){e = 18; c = 1;}
		if(n >= 55 && n < 62){e = 22; c = 249;}
		if(n >= 62 && n < 69){e = 9; c = 1;}
		if(n >= 69 && n < 76){e = 31; c = 249;}
		if(n >= 76 && n < 83){e = 14; c = 1;}
		if(n >= 83 && n < 90){e = 20; c = 249;}
		if(n >= 90 && n < 97){e = 1; c = 1;}
		if(n >= 97 && n < 104){e = 33; c = 249;}
		if(n >= 104 && n < 111){e = 16; c = 1;}
		if(n >= 111 && n < 118){e = 24; c = 249;}
		if(n >= 118 && n < 125){e = 5; c = 1;}
		if(n >= 125 && n < 131){e = 10; c = 249;}
		if(n >= 131 && n < 138){e = 23; c = 1;}
		if(n >= 138 && n < 145){e = 8; c = 249;}
		if(n >= 145 && n < 152){e = 30; c = 1;}
		if(n >= 152 && n < 159){e = 11; c = 249;}
		if(n >= 159 && n < 166){e = 36; c = 1;}
		if(n >= 166 && n < 173){e = 13; c = 249;}
		if(n >= 173 && n < 180){e = 27; c = 1;}
		if(n >= 180 && n < 187){e = 6; c = 249;}
		if(n >= 187 && n < 194){e = 34; c = 1;}
		if(n >= 194 && n < 201){e = 17; c = 249;}
		if(n >= 201 && n < 208){e = 25; c = 1;}
		if(n >= 208 && n < 214){e = 2; c = 249;}
		if(n >= 214 && n < 221){e = 21; c = 1;}
		if(n >= 221 && n < 228){e = 4; c = 249;}
		if(n >= 228 && n < 235){e = 19; c = 1;}
		if(n >= 235 && n < 242){e = 15; c = 249;}
		if(n >= 242 && n < 249){e = 32; c = 1;}
		if(n >= 249 && n <= 256){e = 0; c = 12;}
		/*Determine number*/
	
		gfx_SetDrawBuffer();
		gfx_FillScreen(9);//Green background
		gfx_SetTextFGColor(249);//Black text color
		gfx_SetTextBGColor(255);//Transparent text background
		gfx_SetTextScale(1,1);//Text size for Title
		gfx_SetTextXY(110,10);//Title position
		gfx_PrintString("Roulette v0.1.1");//Print title
		gfx_SetTextXY(49,228);//Text position
		gfx_PrintString("Press 2nd to spin or Clear to exit");//Print text
		gfx_SetTextScale(3,3);//Text size for number
		gfx_SetTextXY(56,200);//number position
		gfx_SetTextFGColor(c);//Text color of number
		gfx_PrintInt(e,2);//Print number
	
		gfx_RotateSprite(ro, rotate_sprite, n);//Rotate the sprite
		gfx_TransparentSprite_NoClip(rotate_sprite, 12, 64);//Show rotated sprite
		gfx_TransparentSprite_NoClip(pfeil, 59, 36);//Show arrow
		gfx_SwapDraw();
	}
		
    gfx_End();// Close the graphics
}
