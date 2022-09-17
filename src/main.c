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

#include "gfx/palette_gfx.h"
#include "gfx/gfx.h"
#include "const.h"

gfx_UninitedSprite(rotate_sprite, ro_width, ro_height);//sprite buffer

/*Declaring Variables*/
uint16_t posx, posy, chip, chipa, chipb, credits;
char bets[50] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//bets array
/*Declaring Variables*/

void DrawTitle()
{
	gfx_SetTextFGColor(254);//Black text color
	gfx_SetTextScale(1,1);//Text size for Title
	gfx_SetTextXY(118,10);//Title position
	gfx_PrintString("RoulCE v1.0.0");//Print title
}

void DrawMenu(int currentMenu)//This function draws the menu at the bottom
{
	gfx_SetColor(253);
	gfx_FillRectangle(10,230,300,8);
	gfx_SetTextFGColor(254);
	gfx_SetTextScale(1,1);
	gfx_SetTextXY(10,230);
	gfx_PrintString("Add Credits");
	if(currentMenu == 1)
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
	int width = 17;
	int leftOffset = 0;
	int height = 14;
	if(posx == 2){width = 40; leftOffset = 23;}//Larger cursor in the left column
	if(posx == 1){width = 40; leftOffset = 61;}//Larger cursor for the buttons
	if(posx == 2 && (posy == 5 || posy == 8)){height = 42;}//Larger cursor for the black and red symbols
	gfx_FillRectangle(posx * 18 + 203 - leftOffset, posy * 14 + 1, width, height);//cursor
}

void PrintNumber(int number, int color)//This function shows the number
{
	gfx_SetColor(253);
	gfx_FillRectangle(56, 200, 50, 30);//Clear old number
	gfx_SetTextScale(3, 3);//Text size for number
	gfx_SetTextXY(56, 200);//number position
	gfx_SetTextFGColor(color);//Text color of number
	gfx_PrintInt(number, 2);//Print number
}

void DrawChip(int type, int cx, int cy)//This function draws a chip at a specific location
{
	gfx_SetTextFGColor(254);
	if(type == 1){gfx_SetColor(252);}//Red
	if(type == 2){gfx_SetColor(248);}//Light Blue
	if(type == 5){gfx_SetColor(249);}//Yellow
	if(type == 10){gfx_SetColor(247);}//Dark Blue
	if(type == 20){gfx_SetColor(251);}//Grey
	if(type == 50){gfx_SetColor(246);}//Purple
	
	gfx_FillCircle(cx,cy,5);
	gfx_SetColor(245);
	gfx_FillCircle(cx,cy,3);

}

void DrawButtons()//This function creates the Menu
{
	gfx_SetColor(254);
	for(int i = 0; i < 7; i++)
	{
		gfx_Rectangle(160,57 + (14 * i),41,15);
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

void placechip(int v, int x, int y)//This function draws placed chips
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

void createTableau(char *numberHistory, char *colorHistory)//this function shows the tableau and the history
{
	int columnWidth, rowHeight;
	gfx_RLETSprite_NoClip(tableau,215,15);
	for(int i = 0; i < 39; i++)
	{
		chipa = 0;
		chipb = 0;
		chipa = bets[i];
		correctchip();
		columnWidth = i % 3;
		rowHeight = i / 3;//row
		columnWidth = columnWidth * 18;
		rowHeight = rowHeight * 14;
		if(chipa > 0)
		{
			DrawChip(chipb, columnWidth + 268, rowHeight + 36);
			if(chipa != chipb)
			{
				gfx_SetTextScale(1,1);
				gfx_SetTextFGColor(0);
				gfx_SetTextXY(columnWidth + 264, rowHeight + 36);
				gfx_PrintInt(bets[i], 1);
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


	gfx_SetColor(253);
	gfx_FillRectangle(110,40,60,10);
	gfx_SetTextScale(1,1);
	gfx_SetTextFGColor(254);
	gfx_SetTextXY(110,26);
	gfx_PrintString("History:");
	gfx_SetTextXY(110,40);
	for(int i = 0; i < 5; i++)
	{
		gfx_SetTextFGColor(colorHistory[i]);
		if(colorHistory[i] != 0)
		{
			gfx_PrintInt(numberHistory[i], 1);
		}
		gfx_SetTextXY(110 + (i + 1) * 20,40);
	}


}

void bet(int s, int t, int u)//This functions makes chips stack
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

int main(void)
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
	kb_key_t keyA, keyC, prevkeyA, prevkeyC;
	char keycount = 0;
	int currentMenu = 0;
	int currentRotation = 0;
	int rotationOffset = 0;
	int spinningSpeed = 0;
	int number = 0;
	int color = 251;
	posx = 4;
	posy = 1;
	credits = 0;
	chip = 1;
	char numberHistory[5] = {0,0,0,0,0};//Number history
	char colorHistory[5] = {0,0,0,0,0};//Color history


	ti_var_t sv = ti_Open("ROULSV","r");
	uint16_t* creditsv = &credits;
	ti_Read(creditsv,2,1,sv);
	ti_Close(sv);
	credits = *creditsv;


	srand(rtc_Time());//Set random seed


    gfx_Begin(); //Start the graphics
    gfx_SetPalette(palette_gfx, sizeof_palette_gfx, 0); //Load Palette
	gfx_SetDrawBuffer();
	gfx_RotateSprite(ro, rotate_sprite, 0);//Rotate the sprite for the first time


	gfx_FillScreen(253);
	gfx_SwapDraw();
	gfx_FillScreen(253);


	while(true)
	{
		for(int i = 0; i < 50; i++)//Payout prize and clear bets array
		{
			if(i < 36 && i + 1 == number){credits = credits + bets[i] * 36;}
			if(i == 39 && number == 0){credits = credits + bets[i] * 36;}
			if(i == 36 && number % 3 == 1){credits = credits + bets[i] * 3;}
			if(i == 37 && number % 3 == 2){credits = credits + bets[i] * 3;}
			if(i == 38 && number % 3 == 0 && number != 0){credits = credits + bets[i] * 3;}
			if(i == 40 && number > 0 && number < 13){credits = credits + bets[i] * 3;}
			if(i == 41 && number < 25 && number > 12){credits = credits + bets[i] * 3;}
			if(i == 42 && number > 24){credits = credits + bets[i] * 3;}
			if(i == 43 && color == 252){credits = credits + bets[i] * 2;}
			if(i == 44 && color == 254){credits = credits + bets[i] * 2;}
			if(i == 45 && number < 19 && number > 0){credits = credits + bets[i] * 2;}
			if(i == 46 && number > 18){credits = credits + bets[i] * 2;}
			if(i == 47 && number % 2 == 1){credits = credits + bets[i] * 2;}
			if(i == 48 && number % 2 == 0 && number != 0){credits = credits + bets[i] * 2;}
			bets[i] = 0;
		}


		while (kb_Data[6] != kb_Clear)//Controls
		{
			kb_Scan();
			gfx_SetColor(253);
			gfx_FillRectangle(160,10,155,220);//Green background
			DrawTitle();
			DrawMenu(currentMenu);
			gfx_SetTextXY(163,167);
			gfx_PrintInt(chip,2);
			DrawChip(chip,187,170);
			PrintCredits();
			PrintNumber(number, color);
			DrawCursor();
			createTableau(numberHistory, colorHistory);
			DrawButtons();
			gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
			gfx_RLETSprite_NoClip(pfeil, 59, 36);
			gfx_SwapDraw();


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
			if(kb_Data[1] == kb_Window && currentMenu == 1 && keyA != prevkeyA){credits = credits + 20; currentMenu = 0;}
			if(kb_Data[1] == kb_Zoom && currentMenu == 1 && keyA != prevkeyA){credits = credits + 50; currentMenu = 0;}
			if(kb_Data[1] == kb_Trace && currentMenu == 1 && keyA != prevkeyA){credits = credits + 100; currentMenu = 0;}
			if(kb_Data[1] == kb_Graph && currentMenu == 1 && keyA != prevkeyA){credits = credits + 200; currentMenu = 0;}
			if(kb_Data[1] == kb_Yequ && currentMenu == 1 && keyA != prevkeyA){credits = credits + 10; currentMenu = 0;}
			else if(kb_Data[1] == kb_Yequ && currentMenu == 0 && keyA != prevkeyA)
			{
				currentMenu = 1;
			}

			if((posx == 1 && posy == 1) || (posx == 2 && posy == 1) || (posx == 3 && posy == 1) || (posx == 5 && posy == 1)){posx = 4;}
			if((posx == 2 && posy == 6) || (posx == 2 && posy == 7)){posy = 5;}
			if((posx == 2 && posy == 9) || (posx == 2 && posy == 10)){posy = 8;}
			

			prevkeyA = keyA;
			prevkeyC = keyC;
			keyA = kb_Data[1];
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


		spinningSpeed = 50000;
		currentRotation = rand() % 222;//Generate random amount to rotate
		while(true)//Spin
		{
			kb_Scan();
			if (kb_Data[6] == kb_Clear) {break;}//Exit
			int speedLoss = rand() % 1000;
			spinningSpeed = spinningSpeed - speedLoss;
			currentRotation = currentRotation + spinningSpeed / 5000;
			if(currentRotation >= 222){currentRotation = currentRotation - 222; rotationOffset = 0;}
			if (spinningSpeed / 2000 < 1)
			{
				break;
			}

			if(currentRotation > 38){rotationOffset = 1;}
			if(currentRotation > 128){rotationOffset++;}
			if(currentRotation > 211){rotationOffset++;}
			
			gfx_RotateSprite(ro, rotate_sprite, currentRotation + currentRotation / 7 + rotationOffset);//Rotate the sprite
			gfx_SetColor(253);
			DrawTitle();
			DrawMenu(currentMenu);

			gfx_TransparentSprite_NoClip(rotate_sprite, 17, 69);//Show rotated sprite
			gfx_RLETSprite_NoClip(pfeil, 59, 36);//Show arrow
			gfx_SwapDraw();


			color = colors[currentRotation / 6];
			number = numbers[currentRotation / 6];
			PrintNumber(number, color);
		}

		numberHistory[4] = numberHistory[3];
		numberHistory[3] = numberHistory[2];
		numberHistory[2] = numberHistory[1];
		numberHistory[1] = numberHistory[0];
		numberHistory[0] = number;
		colorHistory[4] = colorHistory[3];
		colorHistory[3] = colorHistory[2];
		colorHistory[2] = colorHistory[1];
		colorHistory[1] = colorHistory[0];
		colorHistory[0] = color;

	}

	*creditsv = credits;
	sv = ti_Open("ROULSV","w");
    ti_Write(creditsv,2,1,sv);
    ti_Close(sv);


    pgrm_CleanUp();
    gfx_End();
}
