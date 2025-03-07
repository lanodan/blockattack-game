/*
===========================================================================
blockattack - Block Attack - Rise of the Blocks
Copyright (C) 2005-2012 Poul Sander

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/

Source information and contacts persons can be found at
http://blockattack.net
===========================================================================
*/

//Make sure it is only included once
#ifndef _MAINVARS_HPP
#define	_MAINVARS_HPP

#include "sago/SagoSprite.hpp"
#include "BlockGame.hpp"
#include "sago/SagoTextField.hpp"
#include "sago/SagoTextBox.hpp"


//main variables and constants


//Animation lengths:
#define READYTIME 500
#define BOMBTIME 200
#define CURSORTIME 200

const char sharedir[] = SHAREDIR;

//All graphic in the game:
sago::SagoSprite backgroundImage; //Stores the background image
sago::SagoSprite backgroundSixteenNineImage; // For 16:9 format
sago::SagoSprite bExit;
static sago::SagoSprite backBoard;     //Stores the background to the board
static sago::SagoSprite bForward;      //The "forward" button
#if NETWORK
//static sago::SagoSprite bNetwork;
//static sago::SagoSprite bConnect;
//static sago::SagoSprite bHost;
#endif
static sago::SagoSprite blackLine;		//The seperator in stage clear
static sago::SagoSprite stageBobble;	//The bobble instage clear
SDL_Renderer *screen;        //The whole screen;
static sago::SagoTextBox tbGameOver;
static sago::SagoTextBox tbWinner;
static sago::SagoTextBox tbDraw;
static sago::SagoSprite iChainFrame;
//Animations:
static sago::SagoSprite cursor;    //The animated cursor
static sago::SagoSprite bomb;
static sago::SagoSprite ready;      //Before the blocks fall
static sago::SagoSprite explosion[4];   //Then a block explodes
//Animations end
static sago::SagoSprite counter[3];    //Counts down from 3
sago::SagoSprite bricks[7];     //The bricks, saved in an array of pointers
static sago::SagoSprite crossover;     //Cross the bricks that will be cleared soon
static sago::SagoSprite balls[7];      //The balls (the small ones that jump around)

static sago::SagoSprite boardBackBack;
static sago::SagoSprite garbageTL;			//the Garbage Blocks
static sago::SagoSprite garbageT;
static sago::SagoSprite garbageTR;
static sago::SagoSprite garbageR;
static sago::SagoSprite garbageBR;
static sago::SagoSprite garbageB;
static sago::SagoSprite garbageBL;
static sago::SagoSprite garbageL;
static sago::SagoSprite garbageFill;
static sago::SagoSprite garbageM;
static sago::SagoSprite garbageML;
static sago::SagoSprite garbageMR;
static sago::SagoSprite smiley[4];
static sago::SagoSprite garbageGM;
static sago::SagoSprite garbageGML;
static sago::SagoSprite garbageGMR;
static sago::SagoSprite transCover;        //The transperant block, covers the upcomming
static sago::SagoSprite bSkip;
static sago::SagoSprite bRetry;
const int bExitSize = 100;  //height and width of the exit button
const int bExitOffset = 140; //pixels from the buttom right corner to the top left of the exit button

static sago::MusicHandler bgMusic;         //backgroundMusic
static sago::MusicHandler highbeatMusic;   //Background music with higher beat
static sago::SoundHandler boing;           //boing sound when clearing
static sago::SoundHandler applause;        //Applause, then the player is good
static sago::SoundHandler photoClick;      //clickSound
static sago::SoundHandler counterChunk;         //When counting down
static sago::SoundHandler counterFinalChunk;

static bool bMouseUp;              //true if the mouse(1) is unpressed
static bool bMouseUp2;             //true if the mouse(2) is unpressed
#if NETWORK
static bool bNetworkOpen;			//Show the network menu
#endif
static bool bNearDeathPrev;                    //Near death status last time checked.
static bool puzzleLoaded;          //true if the puzzle levels have been loaded
static bool drawBalls;             //if true balls are drawed to the screen, this might lower framerate too much



//global settings (reset everytime the game starts)
static Uint8 player1Speed=0;
static Uint8 player2Speed=0;
static bool player1AI=false;		//Is AI enabled?
static bool player2AI=false;		//Is AI enabled for player 2 (opponent in single player)
static Uint8 player1AIlevel=3;		//What level is AI? 0 min, 6 max
static Uint8 player2AIlevel=3;
static const Uint8 AIlevels=7;		//7 possible levels: 0..6
static Uint8 player1handicap=0;
static Uint8 player2handicap=0;

unsigned long int currentTime;      //contains the current time, so we don't call SDL_GetTickets() too often...

bool twoPlayers;    //True if two players are playing

//Old Stage Clear Buble
static int oldBubleX, oldBubleY;

//Allows starting the game with just a single puzzle. Mainly to be able to open a puzzle directly from the level editor
static bool singlePuzzle = false; 
static int singlePuzzleNr = 0;
static std::string singlePuzzleFile;

#if DEBUG
//frame counter (fps)
unsigned long int Frames, Ticks;
char FPS[10];
#endif


//keySetup
const int player1keys = 0;
const int player2keys = 2;

//Stores the controls
struct control
{
	SDL_Keycode up;
	SDL_Keycode down;
	SDL_Keycode left;
	SDL_Keycode right;
	SDL_Keycode change;
	SDL_Keycode push;
};

control keySettings[3];	//array to hold the controls (default and two custom)

#define KEYMENU_MAXWITH 4
#define KEYMENU_MAXDEPTH 7


static const int buttonXsize = 120;
static const int buttonYsize = 40;

struct ButtonCords
{
	int x;
	int y;
	int xsize;
	int ysize;
};

ButtonCords cordNextButton =
{
	cordNextButton.x = 3*bsize+(3*bsize-buttonXsize)/2,
	cordNextButton.y = 10*bsize,
	cordNextButton.xsize = buttonXsize,
	cordNextButton.ysize = buttonYsize
};

ButtonCords cordRetryButton =
{
	cordRetryButton.x = (3*bsize-buttonXsize)/2,
	cordRetryButton.y = 10*bsize,
	cordRetryButton.xsize = buttonXsize,
	cordRetryButton.ysize = buttonYsize
};

static sago::SagoTextField player1name;
static sago::SagoTextField player2name;
static sago::SagoTextField player1time;
static sago::SagoTextField player2time;
static sago::SagoTextField player1score;
static sago::SagoTextField player2score;
static sago::SagoTextField player1chain;
static sago::SagoTextField player2chain;
static sago::SagoTextField player1speed;
static sago::SagoTextField player2speed;


#endif
