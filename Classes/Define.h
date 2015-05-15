#ifndef __DEFINE_H__
#define __DEFINE_H__

#define PI 3.14159265


#define INIT_VECTOR_Y 4000000.0f
#define INIT_VECTOR_X 4000000.0f

#define CONTACT_TEST_BITMASK 0x01

enum COLLISION_BITMASK
{
	NORMAL = 0x00000001,
	NON = 0x00000000
};

#define MARGIN_X 100
#define END_BUTTON_MARGIN_X 100
#define END_BUTTON_MARGIN_Y 100
#define SCORE_MARGIN 50
//number of block in default block game
#define BLOCKS_NUMBER 30
//Sprite TAGS
enum SPRITE_TAG
{
	WALL = 0,
	BALL = 1,
	BASE = 2,
	BLOCK = 3,
	DELETE = 4,
	ADD = 5,
	ARRAW = 6,
	NOR = 100,
	LAYER = 111,
	CUSOR = 1212,
	PANDA = 10,
	MONKEY = 11,
	BIRD = 12,
	SNAKE = 13

};
enum BIA
{
	BASE_BALL = 0,
	PRI_BALL = 1,
	SEC_BALL = 2,
	MULTIPLE = 50000,
	MAX_SCALE = 4,
	MIN_SPEED = 1500,
	MAX_SPEED = 200000,
	PUSH_LIMIT = 200
};
#define LINEAR_DUMPING 0.2
#define  ANGULARDUMPING 0.3
#define BALL_SCALE_RATIO 0.7

#define TAG_INFOLAYER 111
#define DRAG_BODYS_TAG 80

//the KEY set for PopLayer to create gameplay screen or gameover scene
#define REPLAY 1
#define EXIT 0

#define MAX_TEXT_LENGTH 32

//////UserDefault SAVE KEY

//GAME LEVEL
#define LEVEL "GAMELEVEL"
//Game UI mode
#define UIMODE "GAME_UI_MODE"


#endif