#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <keypadc.h>
#include <fileioc.h>
#include <graphx.h>
#include <debug.h>

#include "gfx/palette_gfx.h"
#include "gfx/gfx.h"

gfx_UninitedSprite(rotate_sprite, ro_width, ro_height);//sprite buffer

/*Declaring Variables*/
uint16_t b, x, s, f, y, z, g, posx, posy, h, i, j, k, l, color, chip, chipa, chipb, m, p , o, v, s, t , u, e, c, credits, menu, keycount;
uint8_t a, n;
kb_key_t keyA, keyB, keyC, prevkeyA, prevkeyB, prevkeyC;
uint16_t bets[50] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//bets array
/*Declaring Variables*/

void DrawTitle() //This function shows the title
{
	gfx_SetTextFGColor(254);//Black text color
	gfx_SetTextScale(1,1);//Text size for Title
	gfx_SetTextXY(110,10);//Title position
	gfx_PrintString("Roulette v0.4.1");//Print title
}

void DrawMenu()//This function draws the menu at the bottom
{
	gfx_SetColor(253);
	gfx_FillRectangle(10,230,300,8);
	gfx_SetTextFGColor(254);
	gfx_SetTextScale(1,1);
	gfx_SetTextXY(10,230);
	gfx_PrintString("Add Credits");
	if(menu == 1)
	{
		gfx_FillRectangle(10,230,300,8);
		gfx_SetTextXY(18,230);
		gfx_PrintString("+10");
		gfx_SetTextXY(82,230);
		gfx_PrintString("+20");
		gfx_SetTextXY(146,230);
		gfx_PrintString("+50");
		gfx_SetTextXY(210,230);
		gfx_PrintString("+100");
		gfx_SetTextXY(274,230);
		gfx_PrintString("+200");
	}
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

void PrintNumber()//This function shows the number
{
	gfx_SetColor(253);
	gfx_FillRectangle(56,200,50,30);//Clear old number
	gfx_SetTextScale(3,3);//Text size for number
	gfx_SetTextXY(56,200);//number position
	gfx_SetTextFGColor(c);//Text color of number
	gfx_PrintInt(e,2);//Print number
}

void DrawChip(type,cx,cy)//This function draws a chip at a specific location
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
	gfx_SetColor(245);
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

void correctchip()//This function selects the chip to be shown when stacking chips
{
	if(chipa > 0){chipb = 1;} 
	if(chipa > 1){chipb = 2;} 
	if(chipa > 4){chipb = 5;} 
	if(chipa > 9){chipb = 10;} 
	if(chipa > 19){chipb = 20;} 
	if(chipa > 49){chipb = 50;} 
}

void placechip(v, x, y)//This function draws placed chips
{
	chipa = 0;
	chipb = 0;
	chipa = bets[v];
	correctchip();
	if(chipa > 0)
	{
		DrawChip(chipb, x, y);
		if(chipa != chipb)
		{
			gfx_SetTextScale(1,1);
			gfx_SetTextFGColor(0);
			gfx_SetTextXY(x - 4, y);
			gfx_PrintInt(bets[v], 1);
		}
	}
}

void createTableau()//this functions shows the tableau
{
	gfx_RLETSprite_NoClip(tableau,215,15);
	for(m=0; m < 39; m++)
	{
		chipa = 0;
		chipb = 0;
		chipa = bets[m];
		correctchip();
		p = m % 3;//column
		o = m / 3;//row
		p = p * 18;
		o = o * 14;
		if(chipa > 0)
		{
			DrawChip(chipb, p + 268, o + 36);
			if(chipa != chipb)
			{
				gfx_SetTextScale(1,1);
				gfx_SetTextFGColor(0);
				gfx_SetTextXY(p + 264, o + 36);
				gfx_PrintInt(bets[m], 1);
			}
		}
	}
	
	placechip(39, 286, 22);
	placechip(40, 250, 36);
	placechip(41, 250, 50);
	placechip(42, 250, 64);
	placechip(43, 250, 78);
	placechip(44, 250, 120);
	placechip(45, 250, 162);
	placechip(46, 250, 176);
	placechip(47, 250, 190);
	placechip(48, 250, 204);
	placechip(49, 250, 218);	
}

void bet(s, t, u)//This functions makes chips stack
{
	if(posx == t && posy == u)
	{
		if(bets[s] + chip < 51 && credits >= chip)
		{
			bets[s] = bets[s] + chip;
			credits = credits - chip;
		}
	}
}

void PrintCredits()//This function prints the amount of chips the player has
{
	gfx_SetColor(253);
	gfx_FillRectangle(10,15,100,10);
	gfx_SetTextFGColor(0);
	gfx_SetTextXY(10,15);
	gfx_PrintString("Credits: ");
	gfx_PrintInt(credits, 1);
}

void main(void)
{
	/*
	List of important colors:
	White = 0
	Black =	254
	Green = 253
	Red = 252
	Grey = 251
	Light Green = 250
	Yellow = 249
	Light Blue = 248
	Dark Blue = 247
	Purple = 246
	Light Grey = 245
	*/
	posx = 4;
	posy = 1;
	credits = 0;
	uint8_t colors[37] = {254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,254,252,251};//color array
	uint8_t numbers[37] = {26,3,35,12,28,7,29,18,22,9,31,14,20,1,33,16,24,5,10,23,8,30,11,36,13,27,6,34,17,25,2,21,4,19,15,32,0};//number array
	chip = 1;
	
	ti_CloseAll();
	ti_var_t sv = ti_Open("ROULSV","r");
	uint16_t* creditsv = &credits;
	ti_Read(creditsv,2,1,sv);
	ti_Close(sv);
	credits = *creditsv;
	
	
    gfx_Begin(); //Start the graphics 
    gfx_SetPalette(palette_gfx, sizeof_palette_gfx, 0); //Load Palette
	s = 0;
	gfx_SetDrawBuffer();
	gfx_RotateSprite(ro, rotate_sprite, a + s);//Rotate the sprite
	gfx_FillScreen(253);//Green background
	DrawTitle();
	DrawMenu();
	gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
	gfx_RLETSprite_NoClip(pfeil, 59, 36);//Show arrow
	
	createTableau();
	DrawButtons();
	
	gfx_SwapDraw();
	gfx_FillScreen(253);
	do //Loop everything
	{
		for(x=0; x < 50; x++)//Payout prize and clear bets array
		{
			if(x < 36 && x + 1 == e){credits = credits + bets[x] * 36;}
			if(x == 39 && e == 0){credits = credits + bets[x] * 36;}
			if(x == 36 && e % 3 == 1){credits = credits + bets[x] * 3;}
			if(x == 37 && e % 3 == 2){credits = credits + bets[x] * 3;}
			if(x == 38 && e % 3 == 0 && e != 0){credits = credits + bets[x] * 3;}
			if(x == 40 && e > 0 && e < 13){credits = credits + bets[x] * 3;}
			if(x == 41 && e < 25 && e > 12){credits = credits + bets[x] * 3;}
			if(x == 42 && e > 24){credits = credits + bets[x] * 3;}
			if(x == 43 && c == 252){credits = credits + bets[x] * 2;}
			if(x == 44 && c == 254){credits = credits + bets[x] * 2;}
			if(x == 45 && e < 19 && e > 0){credits = credits + bets[x] * 2;}
			if(x == 46 && e > 18){credits = credits + bets[x] * 2;}
			if(x == 47 && e % 2 == 1){credits = credits + bets[x] * 2;}
			if(x == 48 && e % 2 == 0 && e != 0){credits = credits + bets[x] * 2;}
			bets[x] = 0;
		}
		
		
		while (kb_Data[6] != kb_Clear)//Controls
		{
			kb_Scan();
			gfx_SetColor(253);
			gfx_FillRectangle(160,10,155,220);//Green background
			DrawTitle();
			DrawMenu();
			gfx_SetTextXY(163,167);
			gfx_PrintInt(chip,2);//Print Text
			DrawChip(chip,187,170);
			PrintCredits();
			PrintNumber();
			DrawCursor();
			createTableau();
			DrawButtons();
			gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
			gfx_RLETSprite_NoClip(pfeil, 59, 36);//Show arrow
			
			/*Tableau navigation*/
			if(kb_Data[7] == kb_Up && keyC != prevkeyC)//Up
			{
				if(posy > 1){if(!(posx == 1 && posy == 4)){posy = posy - 1;}}
			}
			if(kb_Data[7] == kb_Down && keyC != prevkeyC)//Down
			{
				if(posx == 2 && posy == 4){posy = 5;}
				else if(posx == 2 && posy == 5){posy = 8;}
				else if(posx == 2 && posy == 8){posy = 11;}
				else if(posy < 14){if(!(posx == 1 && posy == 10)){posy = posy + 1;}}	
			}
			if(kb_Data[7] == kb_Left && keyC != prevkeyC)//Left
			{
				if((posx == 2 && posy == 4) || (posx == 2 && posy == 5) || (posx == 2 && posy == 8)){posx = 1;}
				else if(posx > 2){posx = posx - 1;}
				
			}
			if(kb_Data[7] == kb_Right && keyC != prevkeyC)//Right
			{
				if(posx < 5){posx = posx + 1;}
			}
			if(kb_Data[1] == kb_2nd && keyA != prevkeyA)//2nd
			{
				if(posx == 1 && posy == 4){break;}//spin
				
				if(posx == 1 && posy == 5){chip = 1;}
				if(posx == 1 && posy == 6){chip = 2;}
				if(posx == 1 && posy == 7){chip = 5;}
				if(posx == 1 && posy == 8){chip = 10;}
				if(posx == 1 && posy == 9){chip = 20;}
				if(posx == 1 && posy == 10){chip = 50;}
				
				if(((posx == 3 && posy < 15) || (posx == 4 && posy < 15 && posy > 1) || (posx == 5 && posy < 15)) && credits >= chip)//Bet on single number except 0
				{
					if(bets[(posy - 2) * 3 + posx - 3] + chip < 51)
					{
						bets[(posy - 2) * 3 + posx - 3] = bets[(posy - 2) * 3 + posx - 3] + chip;
						credits = credits - chip;
					}
				}
				bet(39,4,1);
				bet(40,2,2);
				bet(41,2,3);
				bet(42,2,4);
				bet(43,2,5);
				bet(44,2,8);
				bet(45,2,11);
				bet(46,2,12);
				bet(47,2,13);
				bet(48,2,14);
			}
			
			if(kb_Data[1] == kb_Window && menu == 1 && keyA != prevkeyA){credits = credits + 20; menu = 0;}
			if(kb_Data[1] == kb_Zoom && menu == 1 && keyA != prevkeyA){credits = credits + 50; menu = 0;}
			if(kb_Data[1] == kb_Trace && menu == 1 && keyA != prevkeyA){credits = credits + 100; menu = 0;}
			if(kb_Data[1] == kb_Graph && menu == 1 && keyA != prevkeyA){credits = credits + 200; menu = 0;}
			if(kb_Data[1] == kb_Yequ && menu == 1 && keyA != prevkeyA){credits = credits + 10; menu = 0;}
			else if(kb_Data[1] == kb_Yequ && menu == 0 && keyA != prevkeyA)
			{
				menu = 1;
			}
			
			if((posx == 1 && posy == 1) || (posx == 2 && posy == 1) || (posx == 3 && posy == 1) || (posx == 5 && posy == 1)){posx = 4;}
			if((posx == 2 && posy == 6) || (posx == 2 && posy == 7)){posy = 5;}
			if((posx == 2 && posy == 9) || (posx == 2 && posy == 10)){posy = 8;}
			/*Tableau navigation*/
			
			gfx_SwapDraw();
			kb_Scan();
			prevkeyA = keyA;
			prevkeyB = keyB;
			prevkeyC = keyC;
			keyA = kb_Data[1];
			keyB = kb_Data[6];
			keyC = kb_Data[7];
			if(keyC == prevkeyC)
			{
				keycount = keycount + 1;
				if(keycount > 3)//Long press
				{
					if(keycount % 2 == 1)
					{
						prevkeyC = 0;
					}
				}
			}
			else
			{
				keycount = 0;
			}
		}			
		if (kb_Data[6] == kb_Clear) {break;}//Exit
		srand(rtc_Time());//Set random seed
		
		/*Draw everything*/
		gfx_SetColor(253);
		gfx_FillRectangle(160,10,155,220);//Green background
		DrawTitle();
		DrawMenu();		
		gfx_SetTextXY(163,167);
		gfx_PrintInt(chip,2);//Print Text
		DrawChip(chip,187,170);
		PrintCredits();
		PrintNumber();
		DrawCursor();
		createTableau();
		DrawButtons();
		gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
		gfx_RLETSprite_NoClip(pfeil, 59, 36);//Show arrow
		gfx_SwapDraw();
		gfx_SetColor(253);
		gfx_FillRectangle(160,10,155,220);//Green background
		DrawTitle();	
		DrawMenu();		
		gfx_SetTextXY(163,167);
		gfx_PrintInt(chip,2);//Print Text
		DrawChip(chip,187,170);
		PrintCredits();
		PrintNumber();
		DrawCursor();
		createTableau();
		DrawButtons();
		gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
		gfx_RLETSprite_NoClip(pfeil, 59, 36);//Show arrow
		gfx_SwapDraw();
		/*Draw everything*/
		
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
			DrawMenu();
			
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
	*creditsv = credits;
	sv = ti_Open("ROULSV","w");
    ti_Write(creditsv,2,1,sv);
    ti_Close(sv);
    pgrm_CleanUp();
    gfx_End();// Close the graphics
}
