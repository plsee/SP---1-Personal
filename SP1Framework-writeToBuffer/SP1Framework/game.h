#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <stdio.h>
extern StopWatch g_timer;
extern bool g_quitGame;

enum Keys
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_ESCAPE,
	K_SPACE,
	K_W,
	K_A,
	K_S,
	K_D,
    K_E,
    K_COUNT
};

void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void collision();
#define MAP_WIDTH 53
#define MAP_HEIGHT 27
void randomSeed();
void minimap();
void HUD();
void switchPath();
void moveMonster();
void moveMonster1();
void projectile();
void monsterDeath();
void monster1Death();
void collision1();
void projKill1();
void projKill();
void refill();
void mapChange();


#endif // _GAME_H