// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Map.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

bool keyPressed[K_COUNT];
int iToken = 0;
int Phealth = 0;
int cobwebToken = 0;
int monsterdelay = 0; 
int monster1delay = 0;
int Bhealth = 50;
int BAdelay1 = 0; // for btm right
int RandAtk1 = rand() % 4 + 1; // random atk 
int BAdelay2 = 0; // for btm left
int RandAtk2 = rand() % 4 + 1;
int BAdelay3 = 0; //for top right
int RandAtk3 = rand() % 4 + 1;
int BAdelay4 = 0; // for top left
int RandAtk4 = rand() % 4 + 1;
int BAdelay5 = 0; // for top
int RandAtk5 = rand() % 4 + 1;
int BAdelay6 = 0; // for right
int RandAtk6 = rand() % 4 + 1;
int BAdelay7 = 0; //for down
int RandAtk7 = rand() % 4 + 1;
int BAdelay8 = 0; //for left
int RandAtk8 = rand() % 4 + 1;
double elapsedTime;
double deltaTime;
double bossFightTime = elapsedTime;
double t_invincibility = elapsedTime;
double cobweb = elapsedTime;
double cobwebInvul = elapsedTime;
FILE *map;
GAMESTATES g_eGameState = SPLASH;
CLASSES classes;
DEATHSTATE die = SAD;
MONSTERSTATE Monster = TUTORIAL;
BOSS fight = NORMAL;

// Console object

Console console(75, 27, "Spooky Spooky Ghosts");



// Initial print map
char printMap[MAP_HEIGHT][MAP_WIDTH] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'Q', 'P', 'P', 'P', 'P', 'R', 'P', 'P', 'P', 'P', 'S', 'P', 'P', 'P', 'P', 'T', 'P', 'P', 'P', 'P', 'U', 'P', 'P', 'P', 'P', 'V', 'P', 'P', 'P', 'P', 'W', 'P', 'P', 'P', 'P', 'X', 'P', 'P', 'P', 'P', 'Y', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'K', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};
// Game specific variables here
COORD	charLocation;
COORD	g_cConsoleSize;
COORD	g_cChaserLoc;
COORD	g_cChaser1Loc;
COORD	g_cProjectile;
COORD   TpointerLoc;
COORD   PpointerLoc;
COORD   Bprojectile1;
COORD   Bprojectile2;
COORD	Bprojectile3;
COORD	Bprojectile4;
COORD	Bprojectile5;
COORD	Bprojectile6;
COORD	Bprojectile7;
COORD	Bprojectile8;
COORD   pointerCSLoc;
COORD   pointerCLoc;
COORD   border1CLoc;
COORD   border2CLoc;
COORD   CSdescLoc;

// Initialize variables, allocate memory, load data from file, etc. 
// This is called once before entering into your main loop
void init()
{
    // Set precision for floating point output
    elapsedTime = 0.0;
    charLocation.X = 3;
    charLocation.Y = 13;
	g_cChaserLoc.X = 26;
    g_cChaserLoc.Y = 2;
	g_cChaser1Loc.X = 26;
	g_cChaser1Loc.Y = 24;
	//initial state
	g_eGameState = SPLASH;
    //Pointer location
    TpointerLoc.X = 32;
    TpointerLoc.Y = 15;
    PpointerLoc.X = 32;
    PpointerLoc.Y = 15;
    pointerCSLoc.X = 65;
    pointerCSLoc.Y = 24;
    pointerCLoc.X = 7;
    pointerCLoc.Y = 2;
    border1CLoc.X = 6;
    border1CLoc.Y = 2;
    border2CLoc.X = 26;
    border2CLoc.Y = 2;
    CSdescLoc.X = 0;
    CSdescLoc.Y = 0;
	
    // sets the width, height and the font name to use in the console
    console.setConsoleFont(0, 16, L"Consolas");
}

// Do your clean up of memory here
// This is called once just before the game exits
void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    console.clearBuffer();
}
/*
	This function checks if any key had been pressed since the last time we checked
	If a key is pressed, the value for that particular key will be true
	
	Add more keys to the enum in game.h if you need to detect more keys
	To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
	For Alphanumeric keys, the values are their ascii values (uppercase).
*/
void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
    keyPressed[K_RETURN] = isKeyPressed(VK_RETURN);
	keyPressed[K_W] = isKeyPressed('W');
	keyPressed[K_A] = isKeyPressed('A');
	keyPressed[K_S] = isKeyPressed('S');
	keyPressed[K_D] = isKeyPressed('D');
	keyPressed[K_E] = isKeyPressed('E');
	keyPressed[K_R] = isKeyPressed('R');

}

struct Stats {
    short health;
    short ammo;
    short bomb;
}player;

void status() {
    switch (classes) {
    case BALANCED: balanced();
        break;
    case WARRIOR: warrior();
        break;
    case ARCHER: archer();
        break;
    }
}

void balanced() {
    player.health = 3;
    player.ammo = 5;
    player.bomb = 1;
}

void warrior() {
    player.health = 4;
    player.ammo = 1;
    player.bomb = 1;
}

void archer() {
    player.health = 2;
    player.ammo = 5;
    player.bomb = 1;
}

/*
	This is the update function
	double dt - This is the amount of time in seconds since the previous call was made

	Game logic should be done here.
	Such as collision checks, determining the position of your game characters, status updates, etc
	If there are any calls to write to the console here, then you are doing it wrong.

    If your game has multiple states, you should determine the current state, and call the relevant function here.
*/
void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;
	switch (g_eGameState){
        case CLASSSELECT: classSelect();
            break;
		case GAME: gameplay();
			break;
        case PAUSE: pausemenu();
            break;
		case GAMEOVER: gameend();
			break;
		default: SPLASH : splashwait();
	}
}
// waiting time before Splash Screen switches
void splashwait(){
	if (elapsedTime > 3.0){
		g_eGameState = TITLE;
	}
}
void gameplay(){
    processUserInput();// checks if you should change states or do something else with the game, e.g. pause, exit
    // Cobwebbed
    if (cobwebToken == 0){
        moveCharacter();// moves the character, collision detection, physics, etc
    }
	moveMonster();//moves the monsters
	moveMonster1();
    if (Monster == STARTGAME){
        monsterDamage();
    }// check monster dmg
    trapLava();// check traps
    // sound can be played here too.
    // When the player dies and the gamestate switches to the game over screen
	if (player.health <= 0){
		g_eGameState = GAMEOVER;
	}
}

/*
    This is the render loop
    At this point, you should know exactly what to draw onto the screen.
    Just draw it!
    To get an idea of the values for colours, look at console.h and the URL listed there
*/
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState) {
	case SPLASH: splash();
		break;
	case TITLE: titlescreen();
		break;
    case PAUSE: pausemenu();
        break;
    case CLASSSELECT: classSelect();
        break;
	case GAME: renderGame();
		break;
	case GAMEOVER: gameend();
		break;
	}
	renderToScreen();// dump the contents of the buffer to the screen, one frame worth of game
}

void renderGame() {
	renderMap(); // renders the character into the buffer
	renderCharacter();  // renders the character into the buffer
	projectile();     // projectile
    bomb(); // bomb
	if (fight == BATTLE){
		BossAttack();
        if (elapsedTime > bossFightTime){
            bossFightTime = elapsedTime + 15;
            for (int i = 0; i < MAP_HEIGHT; i++){
                for (int j = 0; j < MAP_WIDTH; j++){
                    printMap[i][j] = BossMap[i][j];
                }
            }
        }
	}
}
//Renders the map according to data
void renderMap()
{
    //Print Map
    /* 0 = nothing
    1 = wall
    2 = trap
    3 = trap
    4 = bomb
    5 = health
    6 = BOMB
    7 = ammo
    8 = door
    9 = spawn
    */
    COORD c;
    std::cout << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < MAP_HEIGHT; i++){
        c.Y = i;
        for (int j = 0; j < MAP_WIDTH; j++){
            c.X = j;
            //WALLS
            if (printMap[i][j] == 1){
                console.writeToBuffer(c, '|', 0x03);
            }
			// Lava
            else if (printMap[i][j] == 2){
                console.writeToBuffer(c, (char)247, 0x0C);
            }
			// Spikes
            else if (printMap[i][j] == 3){
                console.writeToBuffer(c, 'X');
            }
			//
            else if (printMap[i][j] == 4){
                console.writeToBuffer(c, (char)236, 0x0B);
            }
			//
            else if (printMap[i][j] == 5){
                console.writeToBuffer(c, (char)237, 0x0B);
            }
            //6 Bomb
            else if (printMap[i][j] == 6){
                console.writeToBuffer(c, (char)235, 0x0B);
            }
            //7 ammo
            else if (printMap[i][j] == 7){
                console.writeToBuffer(c, (char)240);
            }
            //8 is health
            else if (printMap[i][j] == 8){
                console.writeToBuffer(c, (char)244);
            }
            //9 spawn points
            else if (printMap[i][j] == 9){
                console.writeToBuffer(c, (char)241);
            }
            // From A - K maps
            else if (printMap[i][j] == 'A'){
                console.writeToBuffer(c, (char)456);
            }
            else if (printMap[i][j] == 'B'){
                console.writeToBuffer(c, (char)456);
            }
            else if (printMap[i][j] == 'C'){
                console.writeToBuffer(c, (char)456);
            }
            else if (printMap[i][j] == 'D'){
                console.writeToBuffer(c, (char)456);
            }
            else if (printMap[i][j] == 'E'){
                console.writeToBuffer(c, (char)456);
            }
            else if (printMap[i][j] == 'K'){
                console.writeToBuffer(c, (char)456);
            }
            // From Z - P tutorial
			else if (printMap[i][j] == 'Z') {

			}
			else if (printMap[i][j] == 'Y') {
				console.writeToBuffer(c, (char)241);
			}
			else if (printMap[i][j] == 'X') {
				console.writeToBuffer(c, (char)244);
			}
			else if (printMap[i][j] == 'W') {
				console.writeToBuffer(c, (char)240);
			}
			else if (printMap[i][j] == 'V') {
				console.writeToBuffer(c, (char)235, 0x0B);
			}
			else if (printMap[i][j] == 'U') {
				console.writeToBuffer(c, (char)237, 0x0B);
			}
			else if (printMap[i][j] == 'T') {
				console.writeToBuffer(c, (char)236, 0x0B);
			}
			else if (printMap[i][j] == 'S') {
				console.writeToBuffer(c, 'X');
			}
			else if (printMap[i][j] == 'R') {
				console.writeToBuffer(c, (char)247, 0x0C);
			}
			else if (printMap[i][j] == 'Q') {
				console.writeToBuffer(c, '|', 0x03);
			}
			else if (printMap[i][j] == 'P') {
				console.writeToBuffer(c, ' ' , 0x03);
			}

            else{
                console.writeToBuffer(c, " ");
            }
        }
        std::cout << std::endl;
    }
	textbox();
	minimap();
	HUD();
	
}

void moveCharacter()
{
        //PLAYER MOVEMENT
        // JUMP UP
        if (keyPressed[K_UP] && keyPressed[K_SPACE] && charLocation.Y > 0)
        {        
            if (printMap[charLocation.Y - 2][charLocation.X] == 1){

            }    
            else{
                Beep(1440, 30);
                charLocation.Y -= 2; 
            }
        }
        // JUMP LEFT
        else if (keyPressed[K_LEFT] && keyPressed[K_SPACE] && charLocation.X > 0)
        {
            if (printMap[charLocation.Y][charLocation.X - 2] == 1){

            }
            else{
                Beep(202, 30);
                charLocation.X -= 2;
            }
        }
        // JUMP DOWN
        else if (keyPressed[K_DOWN] && keyPressed[K_SPACE] && charLocation.Y < console.getConsoleSize().Y - 1)
        {
            if (printMap[charLocation.Y + 2][charLocation.X] == 1){
            }
            else{
                Beep(1440, 30);
                charLocation.Y += 2;
            }
        }
        // JUMP RIGHT
        else if (keyPressed[K_RIGHT] && keyPressed[K_SPACE] && charLocation.X < console.getConsoleSize().X - 1)
        {
            if (printMap[charLocation.Y][charLocation.X + 2] == 1){

            }
            else{
                Beep(1440, 30);
                charLocation.X += 2;
            }
        }
        //MOVE UP
        else if (keyPressed[K_UP] && charLocation.Y > 0)
        {
            if (printMap[charLocation.Y - 1][charLocation.X] == 1){
                
            }
            else{
                Beep(1440, 30);
                charLocation.Y -= 1;
            }
        }
        //MOVE LEFT
        else if (keyPressed[K_LEFT] && charLocation.X > 0)
        {
            if (printMap[charLocation.Y][charLocation.X -1] == 1){

            }
            else{
                Beep(1440, 30);
                charLocation.X -= 1;
            }
        }
        //MOVE DOWN
        else if (keyPressed[K_DOWN] && charLocation.Y < console.getConsoleSize().Y - 1)
        {
            if (printMap[charLocation.Y + 1][charLocation.X] == 1){

            }
            else{
                Beep(1440, 30);
                charLocation.Y += 1;
            }
        }
        //MOVE RIGHT
        else if (keyPressed[K_RIGHT] && charLocation.X < console.getConsoleSize().X - 1)
        {
            if (printMap[charLocation.Y][charLocation.X + 1] == 1){

            }
            else{
                Beep(1440, 30);
                charLocation.X += 1;
            }
        }
        else if (keyPressed[K_E])
        {
            if (printMap[charLocation.Y][charLocation.X] != 6){
            }
        }
        mapChange();
        refill();
		Getdamagedbyboss();
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE]){
        g_eGameState = PAUSE;
    }
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    console.clearBuffer(0x00);
}

void renderCharacter()
{
    // Draw the location of the character
    console.writeToBuffer(charLocation, (char)232, 0x0A);
    if (g_cChaserLoc.X == g_cChaser1Loc.X && g_cChaserLoc.Y == g_cChaser1Loc.Y){
        console.writeToBuffer(g_cChaserLoc, (char)238, 0x0D);
    }
    else{
        console.writeToBuffer(g_cChaserLoc, (char)238, 0x0E);
        console.writeToBuffer(g_cChaser1Loc, (char)238, 0x0E);
    }
}
void renderFramerate()
{
    //COORD c;
    //// displays the framerate
    //std::ostringstream ss;
    //ss << std::fixed << std::setprecision(3);
    //ss << 1.0 / deltaTime << "fps";
    //c.X = console.getConsoleSize().X - 9;
    //c.Y = 0;
    //console.writeToBuffer(c, ss.str(), 0x59);

    //// displays the elapsed time
    //ss.str("");
    //ss << elapsedTime << "secs";
    //c.X = 0;
    //c.Y = 0;
    //console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    console.flushBufferToConsole();
}

// PROJECTILE
void projectile() {
    if (player.ammo > 0){
        if (keyPressed[K_W]) {
            player.ammo -= 1;
            g_cProjectile.X = charLocation.X;
            g_cProjectile.Y = charLocation.Y - 1;
            if (classes == WARRIOR) {
                player.ammo = 1;
                for (int i = 0; i < 1; ++i) {
                    if (fight == BATTLE){
                        if (printMap[g_cProjectile.Y][g_cProjectile.X] == 9){
                            Bhealth -= 1;
                        }
                    }
                    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                        console.writeToBuffer(g_cProjectile, (char)30, 0x0B);
                        projKill();
                        projKill1();
                        g_cProjectile.Y -= 1;
                    }
                    else{
                        break;
                    }
                }
            }
            else if (classes == ARCHER) {
                for (int i = 0; i < 3; ++i) {
                    if (fight == BATTLE){
                        if (printMap[g_cProjectile.Y][g_cProjectile.X] == 9){
                            Bhealth -= 1;
                        }
                    }
                    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                        console.writeToBuffer(g_cProjectile, (char)30, 0x0B);
                        projKill();
                        projKill1();
                        g_cProjectile.Y -= 1;
                    }
                    else{
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < 2; ++i) {
                    if (fight == BATTLE){
                        if (printMap[g_cProjectile.Y][g_cProjectile.X] == 9){
                            Bhealth -= 1;
                        }
                    }
                    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                        console.writeToBuffer(g_cProjectile, (char)30, 0x0B);
                        projKill();
                        projKill1();
                        g_cProjectile.Y -= 1;
                    }
                    else{
                        break;
                    }
                }
            }
        }
        else if (keyPressed[K_A]) {
            player.ammo -= 1;
            g_cProjectile.X = charLocation.X - 1;
            g_cProjectile.Y = charLocation.Y;
            if (classes == WARRIOR) {
                if (fight == BATTLE){
                    if (printMap[g_cProjectile.Y][g_cProjectile.X] == 9){
                        Bhealth -= 1;
                    }
                }
                player.ammo += 1;
                for (int i = 0; i < 1; ++i) {
                    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                        console.writeToBuffer(g_cProjectile, (char)17, 0x0B);
                        projKill();
                        projKill1();
                        g_cProjectile.X -= 1;
                    }
                    else{
                        break;
                    }
                }
            }
            else if (classes == ARCHER) {
                for (int i = 0; i < 3; ++i) {
                    if (fight == BATTLE){
                        if (printMap[g_cProjectile.Y][g_cProjectile.X] == 9){
                            Bhealth -= 1;
                        }
                    }
                    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                        console.writeToBuffer(g_cProjectile, (char)17, 0x0B);
                        projKill();
                        projKill1();
                        g_cProjectile.X -= 1;
                    }
                    else{
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < 2; ++i) {
                    if (fight == BATTLE){
                        if (printMap[g_cProjectile.Y][g_cProjectile.X] == 9){
                            Bhealth -= 1;
                        }
                    }
                    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                        console.writeToBuffer(g_cProjectile, (char)17, 0x0B);
                        projKill();
                        projKill1();
                        g_cProjectile.X -= 1;
                    }
                    else{
                        break;
                    }
                }
            }
        }
        else if (keyPressed[K_S]) {
            player.ammo -= 1;
            g_cProjectile.X = charLocation.X;
            g_cProjectile.Y = charLocation.Y + 1;
            if (classes == WARRIOR) {
                player.ammo += 1;
                for (int i = 0; i < 1; ++i) {
                    if (fight == BATTLE){
                        if (printMap[g_cProjectile.Y][g_cProjectile.X] == 9){
                            Bhealth -= 1;
                        }
                    }
                    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                        console.writeToBuffer(g_cProjectile, (char)31, 0x0B);
                        projKill();
                        projKill1();
                        g_cProjectile.Y += 1;
                    }
                    else{
                        break;
                    }
                }
            }
            else if (classes == ARCHER) {
                for (int i = 0; i < 3; ++i) {
                    if (fight == BATTLE){
                        if (printMap[g_cProjectile.Y][g_cProjectile.X] == 9){
                            Bhealth -= 1;
                        }
                    }
                    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                        console.writeToBuffer(g_cProjectile, (char)31, 0x0B);
                        projKill();
                        projKill1();
                        g_cProjectile.Y += 1;
                    }
                    else{
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < 2; ++i) {
                    if (fight == BATTLE){
                        if (printMap[g_cProjectile.Y][g_cProjectile.X] == 9){
                            Bhealth -= 1;
                        }
                    }
                    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                        console.writeToBuffer(g_cProjectile, (char)31, 0x0B);
                        projKill();
                        projKill1();
                        g_cProjectile.Y += 1;
                    }
                    else{
                        break;
                    }
                }
            }
        }
        else if (keyPressed[K_D]) {
            player.ammo -= 1;
            g_cProjectile.X = charLocation.X + 1;
            g_cProjectile.Y = charLocation.Y;
            if (classes == WARRIOR) {
                player.ammo += 1;
                for (int i = 0; i < 1; ++i) {
                    if (fight == BATTLE){
                        if (printMap[g_cProjectile.Y][g_cProjectile.X] == 9){
                            Bhealth -= 1;
                        }
                    }
                    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                        console.writeToBuffer(g_cProjectile, (char)16, 0x0B);
                        projKill();
                        projKill1();
                        g_cProjectile.X += 1;
                    }
                    else{
                        break;
                    }
                }
            }
            else if (classes == ARCHER) {
                for (int i = 0; i < 3; ++i) {
                    if (fight == BATTLE){
                        if (printMap[g_cProjectile.Y][g_cProjectile.X] == 9){
                            Bhealth -= 1;
                        }
                    }
                    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                        console.writeToBuffer(g_cProjectile, (char)16, 0x0B);
                        projKill();
                        projKill1();
                        g_cProjectile.X += 1;
                    }
                    else{
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < 2; ++i) {
                    if (fight == BATTLE){
                        if (printMap[g_cProjectile.Y][g_cProjectile.X] == 9){
                            Bhealth -= 1;
                        }
                    }
                    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                        console.writeToBuffer(g_cProjectile, (char)16, 0x0B);
                        projKill();
                        projKill1();
                        g_cProjectile.X += 1;
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
}
//minimap
void minimap() {
	COORD c;
	#define MINIMAP_WIDTH 22
	#define MINIMAP_HEIGHT 10

	for (int i = 0; i < MINIMAP_HEIGHT; i++) {
		c.Y = i;
		console.writeToBuffer(c, '#');
		for (int j = 0; j < MINIMAP_WIDTH; j++) {
			c.X = console.getConsoleSize().X + j - 22;
			console.writeToBuffer(c, ' ');
		}
	}

	for (int k = 0; k < MINIMAP_WIDTH; k++) {
		for (int i = 0; i < 3; i++){
			c.X = console.getConsoleSize().X + k - 22;
			console.writeToBuffer(c, '_');
		}
	}
	mapper();
}

void mapper() {
	COORD c;
	//Tutorial Map
	c.X = (MINIMAP_WIDTH / 2) + 46;
	c.Y = (MINIMAP_HEIGHT / 2) - 1;
	console.writeToBuffer(c, (char)1, 0x0C);

	//Joint
	c.X = (MINIMAP_WIDTH / 2) + 47;
	c.Y = (MINIMAP_HEIGHT / 2) - 1;
	console.writeToBuffer(c, (char)205, 0x0B);

	//MAP 1
	c.X = (MINIMAP_WIDTH / 2) + 48;
	c.Y = (MINIMAP_HEIGHT / 2) - 1;
	console.writeToBuffer(c, (char)1, 0x0C);

	//Joint
	c.X = (MINIMAP_WIDTH / 2) + 49;
	c.Y = (MINIMAP_HEIGHT / 2) - 1;
	console.writeToBuffer(c, (char)185, 0x0B);

    //MAP 2
    c.X = (MINIMAP_WIDTH / 2) + 49;
    c.Y = (MINIMAP_HEIGHT / 2) - 2;
    console.writeToBuffer(c, (char)1, 0x0C);

    c.X = (MINIMAP_WIDTH / 2) + 49;
    c.Y = (MINIMAP_HEIGHT / 2);
    console.writeToBuffer(c, (char)1, 0x0C);

    //Joint
    c.X = (MINIMAP_WIDTH / 2) + 50;
    c.Y = (MINIMAP_HEIGHT / 2) - 2;
    console.writeToBuffer(c, (char)205, 0x0B);

    c.X = (MINIMAP_WIDTH / 2) + 51;
    c.Y = (MINIMAP_HEIGHT / 2) - 1;
    console.writeToBuffer(c, (char)186, 0x0B);

    c.X = (MINIMAP_WIDTH / 2) + 50;
    c.Y = (MINIMAP_HEIGHT / 2);
    console.writeToBuffer(c, (char)205, 0x0B);

    //MAP 3
    c.X = (MINIMAP_WIDTH / 2) + 51;
    c.Y = (MINIMAP_HEIGHT / 2) - 2;
    console.writeToBuffer(c, (char)1, 0x0C);

    c.X = (MINIMAP_WIDTH / 2) + 51;
    c.Y = (MINIMAP_HEIGHT / 2);
    console.writeToBuffer(c, (char)1, 0x0C);

    //Joint
    c.X = (MINIMAP_WIDTH / 2) + 52;
    c.Y = (MINIMAP_HEIGHT / 2) - 2;
    console.writeToBuffer(c, (char)205, 0x0B);

    c.X = (MINIMAP_WIDTH / 2) + 53;
    c.Y = (MINIMAP_HEIGHT / 2) - 1;
    console.writeToBuffer(c, (char)204, 0x0B);

    c.X = (MINIMAP_WIDTH / 2) + 52;
    c.Y = (MINIMAP_HEIGHT / 2);
    console.writeToBuffer(c, (char)205, 0x0B);

    //MAP 4
    c.X = (MINIMAP_WIDTH / 2) + 53;
    c.Y = (MINIMAP_HEIGHT / 2) - 2;
    console.writeToBuffer(c, (char)1, 0x0C);

    c.X = (MINIMAP_WIDTH / 2) + 53;
    c.Y = (MINIMAP_HEIGHT / 2);
    console.writeToBuffer(c, (char)1, 0x0C);

    ////Boss
    c.X = (MINIMAP_WIDTH / 2) + 54;
    c.Y = (MINIMAP_HEIGHT / 2) - 1;
    console.writeToBuffer(c, (char)1, 0x0C);
}
//HUD
void HUD() {
	COORD c;
	#define HUD_WIDTH 22
	#define HUD_HEIGHT 17

	c.X = console.getConsoleSize().X - 21;
	c.Y = console.getConsoleSize().Y - 16;

	//Health
	for (int m = 0; m < 4; m++){
		console.writeToBuffer(c, "HEALTH");
	}
    if (player.health > 2){
        for (int m = 0; m < player.health * 2; m++){
            c.X = console.getConsoleSize().X - 21 + m;
            c.Y = console.getConsoleSize().Y - 15;
            console.writeToBuffer(c, (char)220);
        }
    }
    else if (player.health == 2){
        for (int m = 0; m < player.health * 2; m++){
            c.X = console.getConsoleSize().X - 21 + m;
            c.Y = console.getConsoleSize().Y - 15;
            console.writeToBuffer(c, (char)220, 0x0E);
        }
    }
    else if (player.health == 1){
        for (int m = 0; m < player.health * 2; m++){
            c.X = console.getConsoleSize().X - 21 + m;
            c.Y = console.getConsoleSize().Y - 15;
            console.writeToBuffer(c, (char)220, 0x0C);
        }
    }

    c.X = console.getConsoleSize().X - 21;
    c.Y = console.getConsoleSize().Y - 13;
	//Ammo
    for (int m = 0; m < 4; m++) {
        console.writeToBuffer(c, "AMMO");
    }

    for (int m = 0; m < player.ammo; m++){
        c.X = console.getConsoleSize().X - 21 + m;
        c.Y = console.getConsoleSize().Y - 12;
        console.writeToBuffer(c, (char)248);
    }

    c.X = console.getConsoleSize().X - 21;
    c.Y = console.getConsoleSize().Y - 10;
	//Bomb
    for (int m = 0; m < 4; m++) {
        console.writeToBuffer(c, "BOMB");
    }

	for (int m = 0; m < player.bomb; m++){
		c.X = console.getConsoleSize().X - 21 + m;
		c.Y = console.getConsoleSize().Y - 9;
		console.writeToBuffer(c, (char)235);
	}
	c.X = console.getConsoleSize().X - 21;
	c.Y = console.getConsoleSize().Y - 5;
	
	


}
//seeding
void randomSeed(){
    int seed = 6;
    srand(seed);
}
//move the 1st monster
void moveMonster(){
    // CHASER MOVEMENT
    if (Monster == STARTGAME){
        monsterdelay++;
        if (monsterdelay == 5){
            if (charLocation.Y < g_cChaserLoc.Y){
                g_cChaserLoc.Y -= 1;
                Beep(1440, 30);
            } // up
            if (charLocation.X < g_cChaserLoc.X){
                g_cChaserLoc.X -= 1;
                Beep(1440, 30);
            } // left
            if (charLocation.X > g_cChaserLoc.X){
                g_cChaserLoc.X += 1;
                Beep(1440, 30);
            } // right
            if (charLocation.Y > g_cChaserLoc.Y){
                g_cChaserLoc.Y += 1;
                Beep(1440, 30);
            } // down
            monsterdelay = 0;
        }
    }
}
//move the 2nd monster
void moveMonster1(){
	// CHASER MOVEMENT
    if (Monster == STARTGAME){
        monster1delay++;
        if (monster1delay == 5){
            if (charLocation.Y < g_cChaser1Loc.Y){
                g_cChaser1Loc.Y -= 1;
                Beep(1440, 30);
            } // up
            if (charLocation.X < g_cChaser1Loc.X){
                g_cChaser1Loc.X -= 1;
                Beep(1440, 30);
            } // left
            if (charLocation.X > g_cChaser1Loc.X){
                g_cChaser1Loc.X += 1;
                Beep(1440, 30);
            } // right
            if (charLocation.Y > g_cChaser1Loc.Y){
                g_cChaser1Loc.Y += 1;
                Beep(1440, 30);
            } // down
            monster1delay = 0;
        }
    }
}
// check if 1st monster gets shot
void projKill(){
	if (g_cChaserLoc.X == g_cProjectile.X && g_cChaserLoc.Y == g_cProjectile.Y){
		monsterDeath();
	}
}
// check if second monster gets shot
void projKill1(){
	if (g_cChaser1Loc.X == g_cProjectile.X && g_cChaser1Loc.Y == g_cProjectile.Y){
		monster1Death();
	}
}
//1st monster death
void monsterDeath(){
	int spawnLocation = rand() % 3;
	g_cChaserLoc.X = 26;
	if (spawnLocation == 0){
		g_cChaserLoc.Y = 2;
	}
	else if (spawnLocation == 1){
		g_cChaserLoc.Y = 14;
	}
	else{
		g_cChaserLoc.Y = 24;
	}
}
// 2nd monster death
void monster1Death(){
	int spawnLocation = rand() % 3;
	g_cChaser1Loc.X = 26;
	if (spawnLocation == 0){
		g_cChaser1Loc.Y = 14;
	}
	else if (spawnLocation == 1){
		g_cChaser1Loc.Y = 24;
	}
	else{
		g_cChaser1Loc.Y = 2;
	}
}

//collision check/damage calculation
void collision(){
    if (charLocation.X == g_cChaserLoc.X && charLocation.Y == g_cChaserLoc.Y){
        monsterDeath();
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
    }
}
//2nd monster collision check
void collision1(){
     if (charLocation.X == g_cChaser1Loc.X && charLocation.Y  == g_cChaser1Loc.Y){
		monster1Death();
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
	}
}
//Refill Ammo
void refill(){
    if (printMap[charLocation.Y][charLocation.X] == 7){
        printMap[charLocation.Y][charLocation.X] = 0;
        if (player.ammo + 10 >= 20){
            player.ammo = 20;
        }
        else if (classes == WARRIOR) {
            player.ammo = 1;
        }
        else{
            player.ammo += 10;
        }
	}
}
//Splash Screen
void splash(){
	std::string gamesplash;
	COORD c = console.getConsoleSize();
	c.Y /= 5;
	c.X /= 9;
	std::ifstream myfile;
	myfile.open("screen/Spooky.txt");
	for (int i = 0; myfile.good(); i++){
		std::getline(myfile, gamesplash);
		console.writeToBuffer(c, gamesplash, 0x0E);
		c.Y += 1;
	}
}
//Dies
void gameend(){
	clearScreen();
	std::string gameover;
	COORD c;
	c.Y = 6;
	c.X = 15;
	std::ifstream myfile;
	FILE * pFile;
	myfile.open("screen/gameover.txt");
	for (int i = 0; myfile.good(); i++){
		std::getline(myfile, gameover);
		console.writeToBuffer(c, gameover, 0x0E);
		c.Y += 1;
	}
	c.X = 28;
	c.Y = 13;
	console.writeToBuffer(c, "Press R to retry", 0x0E);
	if (keyPressed[K_R]) {
		g_eGameState = GAME;
        tutorial();
        player.ammo = 5;
        player.bomb = 1;
	}
	fight = NORMAL;
    if (classes == BALANCED) {
        player.health = 3;
    }
    else if (classes == WARRIOR) {
        player.health = 4;
    }
    else if (classes == ARCHER) {
        player.health = 2;
    }//Boss Projectile
    Bprojectile1.X = 0;
    Bprojectile1.Y = 0;
    Bprojectile2.X = 0;
    Bprojectile2.Y = 0;
    Bprojectile3.X = 0;
    Bprojectile3.Y = 0;
    Bprojectile4.X = 0;
    Bprojectile4.Y = 0;
    Bprojectile5.X = 0;
    Bprojectile5.Y = 0;
    Bprojectile6.X = 0;
    Bprojectile6.Y = 0;
    Bprojectile7.X = 0;
    Bprojectile7.Y = 0;
    Bprojectile8.X = 0;
    Bprojectile8.Y = 0;
}

//Refill Bomb
void bombrefill(){
    if (printMap[charLocation.Y][charLocation.X] == 6){
        printMap[charLocation.Y][charLocation.X] = 0;
        player.bomb += 1;
    }
}
// Changes the map
void mapChange(){
    if (printMap[charLocation.Y][charLocation.X] == 'A'){
        mapRiver();
        Monster = STARTGAME;
    }
    else if (printMap[charLocation.Y][charLocation.X] == 'B'){
        mapLectureHall();
        Monster = STARTGAME;
    }
    else if (printMap[charLocation.Y][charLocation.X] == 'C'){
        mapLibrary();
        Monster = STARTGAME;
    }
    else if (printMap[charLocation.Y][charLocation.X] == 'D'){
        mapMerryGR();
        Monster = STARTGAME;
    }
    else if (printMap[charLocation.Y][charLocation.X] == 'E'){
        mapTheH();
        Monster = STARTGAME;
    }
	else if (printMap[charLocation.Y][charLocation.X] == 'K'){
		BossFight();
		Monster = STARTGAME;
	}
}

//Renders Library
void mapLibrary(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            printMap[i][j] = library[i][j];
           }
    }
    setmonsterlocation();
}
//Renders Lecture Hall
void mapLectureHall(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int  j = 0; j < MAP_WIDTH; j++){
            printMap[i][j] = LectureHall[i][j];
        }
    }
    setmonsterlocation();
}
//Renders River
void mapRiver(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            printMap[i][j] = River[i][j];
        }
    }
    setmonsterlocation();
}
//Renders MerryGR
void mapMerryGR(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            printMap[i][j] = MerryGR[i][j];
        }
    }
    setmonsterlocation();
}
void mapTheH(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            printMap[i][j] = TheH[i][j];
        }
    }
    setmonsterlocation();
}
//Restarts the game
void tutorial(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            printMap[i][j] = Tutorial[i][j];
        }
    }
    setmonsterlocation();
    Monster = TUTORIAL;
}
// initial monster spawn
void setmonsterlocation(){
    g_cChaserLoc.X = 26;
    g_cChaserLoc.Y = 2;
    g_cChaser1Loc.X = 26;
    g_cChaser1Loc.Y = 24;
    charLocation.X = 3;
    charLocation.Y = 13;
}
// textbox for tutorial screen
void textbox() {
	COORD c;	
	//wall
	if (printMap[charLocation.Y][charLocation.X] == 'Q'){
			c.X = 10;
			c.Y = 7;
			console.writeToBuffer(c, "This is a Wall");
			c.X = 10;
			c.Y = 8;
			console.writeToBuffer(c, "You can jump over 1 layer thick walls");
		}
	
	//Lava
    if (printMap[charLocation.Y][charLocation.X] == 'R'){
		c.X = 10;
		c.Y = 7;
		console.writeToBuffer(c, "This is lava");
		c.X = 10;
		c.Y = 8;
		console.writeToBuffer(c, "It does 3 damage instantly");
	}
	//cobwebs
	if (printMap[charLocation.Y][charLocation.X] == 'S'){
		c.X = 10;
		c.Y = 7;
		console.writeToBuffer(c, "This is Cobwebs");
		c.X = 10;
		c.Y = 8;
		console.writeToBuffer(c, "It makes you stop moving for 1 second");
	}
	c.X = 14;
	c.Y = 7;
	if (printMap[charLocation.Y][charLocation.X] == 'T'){
		console.writeToBuffer(c, "PlaceHolder");
	}
	c.X = 17;
	c.Y = 7;
	if (printMap[charLocation.Y][charLocation.X] == 'U'){
		console.writeToBuffer(c, "Another Placeholder");
	}
	
	if (printMap[charLocation.Y][charLocation.X] == 'V'){
		c.X = 20;
		c.Y = 7;
		console.writeToBuffer(c, "This is a bomb");
		c.X = 2;
		c.Y = 8;
		console.writeToBuffer(c, "It kills all the monster on the map at the moment");
	}
	// Ammo pack
	if (printMap[charLocation.Y][charLocation.X] == 'W'){
		c.X = 10;
		c.Y = 7;
		console.writeToBuffer(c, "This is an ammo pack");
		c.X = 10;
		c.Y = 8;
		console.writeToBuffer(c, "Refills ammo by 10");
	}
	// Health pack
	if (printMap[charLocation.Y][charLocation.X] == 'X'){
		c.X = 10;
		c.Y = 7;
		console.writeToBuffer(c, "This is a Health Pack");
		c.X = 10;
		c.Y = 8;
		console.writeToBuffer(c, "Refills health by 1");
	}
	//Monster Spawner
	
	if (printMap[charLocation.Y][charLocation.X] == 'Y'){
		c.X = 10;
		c.Y = 7;
		console.writeToBuffer(c, "This is a monster spawner");
		c.X = 10;
		c.Y = 8;
	}
	if (printMap[charLocation.Y][charLocation.X] == 'P')
	{
		c.X = 8;
		c.Y = 7;
		console.writeToBuffer(c, "Step on each item to know what it is!");
		c.X = 8;
		c.Y = 18;
		console.writeToBuffer(c, "Arrow Keys to Move");
		c.X = 8;
		c.Y = 20;
		console.writeToBuffer(c, "WASD to shoot in respective directions");
		c.X = 8;
		c.Y = 22;
		console.writeToBuffer(c, "Press & hold Space + Arrow key to jump");
	}
}

// title screen
void titlescreen(){
	clearScreen();
	std::string title;
	COORD c;
	c.Y = 3;
	c.X = 10;
	std::ifstream myfile;
	FILE * pFile;
	myfile.open("screen/title.txt");
	for (int i = 0; myfile.good(); i++){
		std::getline(myfile, title);
		console.writeToBuffer(c, title, 0x0E);
		c.Y += 1;
	}
	// start button
	c.Y = 15;
	c.X = 34;
	console.writeToBuffer(c, "Start");
	// exit button
	c.Y = 19;
	c.X = 34;
	console.writeToBuffer(c, "Exit");
    Tpointer();
}

//BOMB
void bomb() {
    if (keyPressed[K_E]) {
		if (player.bomb > 0){
			monsterDeath();
			monster1Death();
			player.bomb -= 1;
		}
    }
}
//TITLE POINTER
void Tpointer(){
    if (keyPressed[K_UP]){
        TpointerLoc.Y = 15;
    }
    else if (keyPressed[K_DOWN]){
        TpointerLoc.Y = 19;
    }
    console.writeToBuffer(TpointerLoc, ">");
    if (keyPressed[K_RETURN]){
        if (TpointerLoc.Y == 15){
            g_eGameState = CLASSSELECT;
        }
        else if (TpointerLoc.Y == 19){
            g_quitGame = true;
        }
    }
}
// pause screen
void Ppointer(){
    //Up button pressed
    if (keyPressed[K_UP]){
        if (PpointerLoc.Y == 15){
            PpointerLoc.Y = 17;
        }
        else if (PpointerLoc.Y == 17){
            PpointerLoc.Y = 19;
        }
        else{
            PpointerLoc.Y = 15;
        }
    }
    //Down button pressed
    else if (keyPressed[K_DOWN]){
        if (PpointerLoc.Y == 19){
            PpointerLoc.Y = 17;
        }
        else if (PpointerLoc.Y == 17){
            PpointerLoc.Y = 15;
        }
        else{
            PpointerLoc.Y = 19;
        }
        
    }
    console.writeToBuffer(PpointerLoc, ">");
    //Confirming option
    if(keyPressed[K_RETURN]){
        if (PpointerLoc.Y == 15){
            g_eGameState = GAME;
        }
        else if (PpointerLoc.Y == 17){
            tutorial();
            g_eGameState = GAMEOVER;
        }
        else if (PpointerLoc.Y == 19){
            tutorial();
            g_eGameState = SPLASH;
            elapsedTime = 2;
        }
    }
}
void pausemenu(){
		clearScreen();
		std::string pause;
		COORD c;
		c.Y = 3;
		c.X = 10;
		std::ifstream myfile;
		FILE * pFile;
		myfile.open("screen/pause.txt");
		for (int i = 0; myfile.good(); i++){
			std::getline(myfile, pause);
			console.writeToBuffer(c, pause, 0x0E);
			c.Y += 1;
		}
		//continue button
		c.Y = 15;
		c.X = 33;
		console.writeToBuffer(c, "Continue");
		// Restart button
		c.Y = 17;
		c.X = 33;
		console.writeToBuffer(c, "Restart");
		// Exit to main Menu button
		c.Y = 19;
		c.X = 33;
		console.writeToBuffer(c, "Exit to Main Menu");
        Ppointer();
}
void BossAttack(){
	//btm right
   console.writeToBuffer(Bprojectile1, (char)30, 0x0B); 
   if (BAdelay1 == RandAtk1){
       if (printMap[Bprojectile1.Y][Bprojectile1.X] == 1){
           Bprojectile1.X = 26;
           Bprojectile1.Y = 13;
       }
       else{
           Bprojectile1.X += 2;
           Bprojectile1.Y += 1;
       }
       BAdelay1 = 0;
   }  
  
   //btm left
   console.writeToBuffer(Bprojectile2, (char)30, 0x0B);
   if (BAdelay2 == RandAtk2){
	   if (printMap[Bprojectile2.Y][Bprojectile2.X] == 1){
		   Bprojectile2.X = 26;
		   Bprojectile2.Y = 13;
	   }
	   else{
		   Bprojectile2.X -= 2;
		   Bprojectile2.Y += 1;
	   }
	   BAdelay2 = 0;
   }
   //top right
   console.writeToBuffer(Bprojectile3, (char)30, 0x0B);
   if (BAdelay3 == RandAtk3){
	   if (printMap[Bprojectile3.Y][Bprojectile3.X] == 1){
		   Bprojectile3.X = 26;
		   Bprojectile3.Y = 13;
	   }
	   else{
		   Bprojectile3.X += 2;
		   Bprojectile3.Y -= 1;
	   }
	   BAdelay3 = 0;
   }
   // top left
   console.writeToBuffer(Bprojectile4, (char)30, 0x0B);
   if (BAdelay4 == RandAtk4){
	   if (printMap[Bprojectile4.Y][Bprojectile4.X] == 1){
		   Bprojectile4.X = 26;
		   Bprojectile4.Y = 13;
	   }
	   else{
		   Bprojectile4.X -= 2;
		   Bprojectile4.Y -= 1;
	   }
	   BAdelay4 = 0;
   }
   //top
   console.writeToBuffer(Bprojectile5, (char)30, 0x0B);
   if (BAdelay5 == RandAtk5){
	   if (printMap[Bprojectile5.Y][Bprojectile5.X] == 1){
		   Bprojectile5.X = 26;
		   Bprojectile5.Y = 13;
	   }
	   else{
		   Bprojectile5.Y -= 1;
	   }
	   BAdelay5 = 0;
   }
   // right
   console.writeToBuffer(Bprojectile6, (char)30, 0x0B);
   if (BAdelay6 == RandAtk6){
	   if (printMap[Bprojectile6.Y][Bprojectile6.X] == 1){
		   Bprojectile6.X = 26;
		   Bprojectile6.Y = 13;
	   }
	   else{
		   Bprojectile6.X += 1;
		  
	   }
	   BAdelay6 = 0;
   }
   // down
   console.writeToBuffer(Bprojectile7, (char)30, 0x0B);
   if (BAdelay7 == RandAtk7){
	   if (printMap[Bprojectile7.Y][Bprojectile7.X] == 1){
		   Bprojectile7.X = 26;
		   Bprojectile7.Y = 13;
	   }
	   else{
		   Bprojectile7.Y += 1;
	   }
	   BAdelay7 = 0;
   }
   //left
   console.writeToBuffer(Bprojectile8, (char)30, 0x0B);
   if (BAdelay8 == RandAtk8){
	   if (printMap[Bprojectile8.Y][Bprojectile8.X] == 1){
		   Bprojectile8.X = 26;
		   Bprojectile8.Y = 13;
	   }
	   else{
		   Bprojectile8.X -= 1;
	   }
	   BAdelay8 = 0;
   }
   BAdelay1++;
   BAdelay2++;
   BAdelay3++;
   BAdelay4++;
   BAdelay5++;
   BAdelay6++;
   BAdelay7++;
   BAdelay8++;
}
void Getdamagedbyboss(){
	if (charLocation.X == Bprojectile1.X && charLocation.Y == Bprojectile1.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
	}
	else if (charLocation.X == Bprojectile2.X && charLocation.Y == Bprojectile2.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
	}
	else if (charLocation.X == Bprojectile3.X && charLocation.Y == Bprojectile3.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
	}
	else if (charLocation.X == Bprojectile4.X && charLocation.Y == Bprojectile4.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
	}
	else if (charLocation.X == Bprojectile5.X && charLocation.Y == Bprojectile5.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
	}
	else if (charLocation.X == Bprojectile6.X && charLocation.Y == Bprojectile6.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
	}
	else if (charLocation.X == Bprojectile7.X && charLocation.Y == Bprojectile7.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
	}
	else if (charLocation.X == Bprojectile8.X && charLocation.Y == Bprojectile8.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
	}
	
}
void BossFight(){
	for (int i = 0; i < MAP_HEIGHT; i++){
		for (int j = 0; j < MAP_WIDTH; j++){
			printMap[i][j] = BossMap[i][j];
		}
	}
	setmonsterlocation();
	fight = BATTLE;
    //Boss Projectile
    Bprojectile1.X = 26;
    Bprojectile1.Y = 13;
    Bprojectile2.X = 26;
    Bprojectile2.Y = 13;
    Bprojectile3.X = 26;
    Bprojectile3.Y = 13;
    Bprojectile4.X = 26;
    Bprojectile4.Y = 13;
    Bprojectile5.X = 26;
    Bprojectile5.Y = 13;
    Bprojectile6.X = 26;
    Bprojectile6.Y = 13;
    Bprojectile7.X = 26;
    Bprojectile7.Y = 13;
    Bprojectile8.X = 26;
    Bprojectile8.Y = 13;
}

void classSelect() {
    clearScreen();
    std::string classSel;
    COORD c;
    c.Y = 3;
    c.X = 10;
    std::ifstream myfile;

    myfile.open("screen/classSel.txt");
    for (int i = 0; myfile.good(); i++){
        std::getline(myfile, classSel);
        console.writeToBuffer(c, classSel, 0x0E);
        c.Y += 1;
    }
    // start button
    c.Y = 24;
    c.X = 66;
    console.writeToBuffer(c, "Start");
    // exit button
    c.Y = 25;
    c.X = 66;
    console.writeToBuffer(c, "Back");
    pointerCS();
    CSdesc();
    status();
}

void pointerCS(){
    if (keyPressed[K_UP]){
        pointerCSLoc.Y = 24;
    }
    else if (keyPressed[K_DOWN]){
        pointerCSLoc.Y = 25;
    }

    console.writeToBuffer(pointerCSLoc, ">");
    if (keyPressed[K_RETURN]){
        if (pointerCSLoc.Y == 24){
            if (pointerCLoc.X == 7){
                classes = BALANCED;
                g_eGameState = GAME;
            }
            else if (pointerCLoc.X == 27){
                classes = WARRIOR;
                g_eGameState = GAME;
            }
            else if (pointerCLoc.X == 47){
                classes = ARCHER;
                g_eGameState = GAME;
            }
        }
        else if (pointerCSLoc.Y == 25){
            g_eGameState = SPLASH;
            elapsedTime = 2;
        }
    }

    if (keyPressed[K_LEFT]) {
        if (pointerCLoc.X > 7) {
            pointerCLoc.X -= 10;
        }
    }
    else if (keyPressed[K_RIGHT]) {
        if (pointerCLoc.X <= 37) {
            pointerCLoc.X += 10;
        }
    }

    console.writeToBuffer(pointerCLoc, "||||||||||||||||||||");


    if (keyPressed[K_LEFT]) {
        if (border1CLoc.X > 10) {
            border1CLoc.X -= 10;
        }
    }
    else if (keyPressed[K_RIGHT]) {
        if (border1CLoc.X <= 40) {
            border1CLoc.X += 10;
        }
    }

    console.writeToBuffer(border1CLoc, "||||||||||||||||||||");
    for (int i = 2; i < 22; i++) {
        border1CLoc.Y = i;
        console.writeToBuffer(border1CLoc, "||");
        std::cout << std::endl;
    }

    if (keyPressed[K_LEFT]) {
        if (border2CLoc.X > 26) {
            border2CLoc.X -= 10;
        }
    }
    else if (keyPressed[K_RIGHT]) {
        if (border2CLoc.X <= 56) {
            border2CLoc.X += 10;
        }
    }

    for (int i = 2; i < 22; i++) {
        border2CLoc.Y = i;
        console.writeToBuffer(border2CLoc, "||");
        std::cout << std::endl;
    }
}

void CSdesc() {
    if (pointerCLoc.X == 7){
        CSdescLoc.X = 6;
        CSdescLoc.Y = 23;
        console.writeToBuffer(CSdescLoc, "Health: 3");
        CSdescLoc.X = 6;
        CSdescLoc.Y = 24;
        console.writeToBuffer(CSdescLoc, "Ammo: 5");
        CSdescLoc.X = 6;
        CSdescLoc.Y = 25;
        console.writeToBuffer(CSdescLoc, "Bomb: 1");
        CSdescLoc.X = 22;
        CSdescLoc.Y = 23;
        console.writeToBuffer(CSdescLoc, "Projectile Range: 2");
    }
    else if (pointerCLoc.X == 27){
        CSdescLoc.X = 6;
        CSdescLoc.Y = 23;
        console.writeToBuffer(CSdescLoc, "Health: 4");
        CSdescLoc.X = 6;
        CSdescLoc.Y = 24;
        console.writeToBuffer(CSdescLoc, "Ammo: Infinite");
        CSdescLoc.X = 6;
        CSdescLoc.Y = 25;
        console.writeToBuffer(CSdescLoc, "Bomb: 1");
        CSdescLoc.X = 22;
        CSdescLoc.Y = 23;
        console.writeToBuffer(CSdescLoc, "Projectile Range: 1");
    }
    else if (pointerCLoc.X == 47){
        CSdescLoc.X = 6;
        CSdescLoc.Y = 23;
        console.writeToBuffer(CSdescLoc, "Health: 2");
        CSdescLoc.X = 6;
        CSdescLoc.Y = 24;
        console.writeToBuffer(CSdescLoc, "Ammo: 5");
        CSdescLoc.X = 6;
        CSdescLoc.Y = 25;
        console.writeToBuffer(CSdescLoc, "Bomb: 1");
        CSdescLoc.X = 22;
        CSdescLoc.Y = 23;
        console.writeToBuffer(CSdescLoc, "Projectile Range: 3");
    }
}

void invincibility(){
    if (elapsedTime > t_invincibility){
        iToken = 0;
    }
}
// checking monster dmg
void monsterDamage(){
    if(charLocation.X == g_cChaser1Loc.X && charLocation.Y == g_cChaser1Loc.Y && charLocation.X == g_cChaserLoc.X && charLocation.Y == g_cChaserLoc.Y){
        monsterDeath();
        monster1Death();
        if (iToken == 0){
            player.health -= 2;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
    }
    else{
        collision();
        collision1();
    }
    invincibility();
}
//Dying to traps
void trapLava(){
    //LAVA
    if (printMap[charLocation.Y][charLocation.X] == 2){
        if (iToken == 0){
            player.health -= 3;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
    }
    //COBWEBBED
    if (printMap[charLocation.Y][charLocation.X] == 3){
        if (elapsedTime > cobwebInvul){
            if (cobwebToken == 0){
                cobwebToken += 1;
                cobweb = elapsedTime + 1.5;
                cobwebInvul = elapsedTime +2.5;
            }
        }
    }
    if (elapsedTime < cobwebInvul && elapsedTime > cobweb){
        cobwebToken = 0;
    }
}
