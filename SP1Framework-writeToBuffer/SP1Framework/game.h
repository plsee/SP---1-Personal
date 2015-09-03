#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <stdio.h>
extern StopWatch g_timer;
extern bool g_quitGame;

enum Keys // Keypress
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
	K_R,
    K_Q,
    K_RETURN,
	K_COUNT
};

enum MAPSTATE{ // Maps
    TUTORIALROOM,
    RIVERROOM,
    LIBRARYROOM,
    LECTUREHALLROOM,
    MERRYGRROOM,
    THEHROOM,
    BOSSROOM
};
enum GAMESTATES{ // Gamestates
	SPLASH,
	TITLE,
    CLASSSELECT,
	GAME,
    VICTORY,
    CREDITS,
	PAUSE,
	GAMEOVER
};
enum DEATHSTATE{ // Deathstates
	SAD,
	RESTART,
	QUIT
};
enum MONSTERSTATE{ // Monsterstates
    TUTORIAL,
    STARTGAME,
    ENDGAME
};

enum CLASSES { // Classes
    BALANCED,
    WARRIOR,
    ARCHER
    
};
enum BOSS{ // Boss mode
	NORMAL,
	BATTLE
};

/*Initial*/
void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void renderGame();          // renders play function
void shutdown();            // do clean up, free memory
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void gameplay();            // Process user input, invincibility, runs sound
void renderGuards();        // Renders Guards
void renderMonster();       // Renders Ghosts

/*Screens*/
void splashwait();          // Splash screen time function
void splash();              // Splash screen

void titlescreen();         // Title screen
void Tpointer();            // Pointer for title screen
void ghost1();              // Title screen ghost1
void ghost2();              // Title screen ghost2
void ghost3();              // Title screen ghost3
void ghost4();              // Title screen ghost4

void classSelect();         // Class Select screen
void CSdesc();              // Class Select screen description
void pointerCS();           // pointer for class select screen
void balanced();            // Adventurer Class
void archer();              // Archer Class
void warrior();             // Warrior Class
void Ultimate();            // Ultimate skills for classes
void status();              // Determine class function

void pausemenu();           // Pause screen
void pause();               // Pause function
void Ppointer();            // Pointer for pause screen

void victory();             // Victory screen
void firework();            // Victory screen firework

void credits();             // Credits & Statistics screen

/*On gameplay screen*/
void minimap();             // Shows minimap
void HUD();                 // Shows stats of player and boss

/*Ghost & Boss*/
void collision();           // Detect ghost1 collision for damage calculation
void collision1();          // Detect ghost2 collision for damage calculation
void moveMonster();         // Ghost1 movement
void moveMonster1();        // Ghost2 movement
void projectile();          // Projectile from player
void monsterDeath();        // Ghost1 death
void monster1Death();       // Ghost2 death
void BossAttack();          // Attack pattern for boss
void Getdamagedbyboss();    // Damage function for boss
void BossFight();           // Determine if player is in boss map
void bossSpeed();           // Boss projectile speed function
void randomSeed();          // Random seeding
void projKill1();           // kill ghost when projectile hits
void projKill();            // kill ghost when projectile hits
void monsterDamage();  
void monstersMoveChecker();
// Damage function for super ghost
/* moving traps */
void guardMovement();
/*Spawn monster*/
void setmonsterlocation();  // Set monster spawn
void spawnMonster();        // Spawn ghost 1
void spawnMonster1(); // Spawn ghost 2
void monsterSpawn();

/*Restart*/
void completeReset();       // Game reset
void levelReset();          // Level reset
void retry();               // Retry level when dead
void gameend();             // Resets the game, gameover

/*Traps*/
void traps();               // Traps such as lava and cobweb
void 
Movement();       // Moving traps function

/*Maps*/
void mapLibrary();          // Library map
void mapLectureHall();      // Lecture Hall map
void mapRiver();            // River map
void mapMerryGR();          // Merry-Go-Round Map
void mapTheH();             // The H Map
void tutorial();            // Tutorial map
void textbox();             // Description for tutorial map

/*Remove sound*/
void soundreset();          // Reset sound for different gamestates

/*Bomb*/
void bomb();                // Bomb function

/*Invincibility*/
void invincibility();       // Invincibility when player damaged

/*Change map*/
void mapChange();           // Change from one map to another

/*Refil items*/
void refill();              // Refil health, ammo, bomb

#endif // _GAME_H