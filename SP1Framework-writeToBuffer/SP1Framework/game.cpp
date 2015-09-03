// This is the main file for the game logic and function
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "game.h"
#include "Map.h"
#include "Framework\console.h"
extern char BossMap[MAP_HEIGHT][MAP_WIDTH];
extern char printMap[MAP_HEIGHT][MAP_WIDTH];
extern BOSS fight;
extern int iToken; 
extern int monsterToken;
extern int monster1Token;
extern int timesRetry;
extern int healthDMG;
extern int ammoUsed;
extern int bombUsed;
extern double t_monsterDied;
extern double t_monster1Died;
extern COORD    Bprojectile1;
extern COORD    Bprojectile2;
extern COORD	Bprojectile3;
extern COORD	Bprojectile4;
extern COORD	Bprojectile5;
extern COORD	Bprojectile6;
extern COORD	Bprojectile7;
extern COORD	Bprojectile8;
COORD	guarda;
COORD	guardb;
COORD	guardc;
COORD	guardd;
COORD	guarde;
bool keyPressed[K_COUNT];
int Phealth = 0;
int cobwebToken = 0;
int monsterdelay = 0; 
int monster1delay = 0;
int Bhealth = 50;
int showCD = 0;
int gamesoundToken = 0;
int MaxHP = 0;
int bossSoundToken = 0;
double uCooldown = 0;
double elapsedTime;
double deltaTime;
double bossFightTime = elapsedTime;
double t_invincibility = elapsedTime;
double t_dDamage = elapsedTime;
double t_maxRange = elapsedTime;
double cobweb = elapsedTime;
double cobwebInvul = elapsedTime;
GAMESTATES g_eGameState = SPLASH;
CLASSES classes;
DEATHSTATE die = SAD;
MONSTERSTATE Monster = TUTORIAL;
MAPSTATE level = TUTORIALROOM;

// Console object

Console console(75, 27, "Spooky Spooky Ghosts");

// Game specific variables here
COORD	charLocation;
COORD	g_cConsoleSize;
COORD	g_cChaserLoc;
COORD	g_cChaser1Loc;
COORD	g_cProjectile;
// Pointer coordinates
COORD   TpointerLoc;
COORD   PpointerLoc;
// Class selection coordinates
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
	// Pointer for Title screen
    TpointerLoc.X = 32;
    TpointerLoc.Y = 18;
	// Pointer for Pause screen
    PpointerLoc.X = 32;
    PpointerLoc.Y = 15;
	// Pointer for class selection screen
    pointerCSLoc.X = 65;
    pointerCSLoc.Y = 24;
	// Pointer for start/back button on class selection screen
    pointerCLoc.X = 7;
    pointerCLoc.Y = 2;
	// Bordering for the class screen
    border1CLoc.X = 6;
    border1CLoc.Y = 2;
    border2CLoc.X = 26;
    border2CLoc.Y = 2;
    CSdescLoc.X = 0;
    CSdescLoc.Y = 0;
    //Guards
    guarda.X = 18;
    guarda.Y = 13;
    guardb.X = 13;
    guardb.Y = 13;
    guardc.X = 22;
    guardc.Y = 13;
    guardd.X = 30;
    guardd.Y = 13;
    guarde.X = 39;
    guarde.Y = 13;
	
    // sets the width, height and the font name to use in the console
    console.setConsoleFont(0, 24, L"Consolas");
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
    keyPressed[K_Q] = isKeyPressed('Q');
}

struct Stats {
    short health;
    short ammo;
    short bomb;
}player;

//---------//
// Classes //
//---------//

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
// Adventure class
void balanced() {
    player.health = 4;
    player.ammo = 5000;
    player.bomb = 1;
    MaxHP = 4;
}
// Warrior class
void warrior() {
    player.health = 4;
    player.ammo = 1;
    player.bomb = 1;
    MaxHP = 4;
}
// Archer class
void archer() {
    player.health = 2;
    player.ammo = 8;
    player.bomb = 1;
    MaxHP = 2;
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
		case SPLASH: splashwait();
	}
}

void gameplay(){
    processUserInput();     // checks if you should change states or do something else with the game, e.g. pause, exit
    // Cobwebbed
    if (cobwebToken == 0){
        moveCharacter();    // moves the character, collision detection, physics, etc
    }
    invincibility();
    
    if (Monster == STARTGAME){
        monsterDamage();    // check ghost damage
    }

    traps();                // check traps
    monsterSpawn();         // check for monster spawn
    guardMovement(); 
    monstersMoveChecker();  // Moving trap function

    // sound can be played here too.
    // When the player dies and the gamestate switches to the game over screen
	if (player.health <= 0){
		g_eGameState = GAMEOVER;
		PlaySound(L"sounds/dietheme.wav", NULL, SND_ASYNC | SND_LOOP);
	}
    // When the boss dies and the gamestate switches to the victory screen
    if (Bhealth <= 0){
        g_eGameState = VICTORY;
        PlaySound(L"sounds/victorytheme.wav", NULL, SND_ASYNC | SND_LOOP);
    }
    // When player not in boss room
	if (gamesoundToken == 0){
		if (level != BOSSROOM){
			PlaySound(L"sounds/gametheme.wav", NULL, SND_ASYNC | SND_LOOP);
			gamesoundToken++;
		}
	}
    // When player in boss room
	if (level == BOSSROOM){
		if (bossSoundToken == 0){
			PlaySound(L"sounds/bosstheme.wav", NULL, SND_ASYNC | SND_LOOP);
			bossSoundToken++;
		}
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
    clearScreen();                      // clears the current screen and draw from scratch 
	switch (g_eGameState) {
	case SPLASH: splash();              // splash screen
		break;
	case TITLE: titlescreen();          // title screen
		break;
    case VICTORY: victory();            // victory screen
        break;
    case CREDITS: credits();            // credits & statistics screen
        break;
    case PAUSE: pausemenu();            // pause screen
        break;
    case CLASSSELECT: classSelect();    // class selection screen
        break;
	case GAME: renderGame();            // Game screen
		break;
	case GAMEOVER: gameend();           // Retry screen
		break;
	}
	renderToScreen();// dump the contents of the buffer to the screen, one frame worth of game
}

void renderGame() {
	renderMap();                // renders the character into the buffer
	renderCharacter();          // renders the character into the buffer
    renderMonster();            // renders Ghost
    renderGuards();             // renders guards
	projectile();               // projectile function
    bomb();                     // bomb function
    Ultimate();                 // ultimate skills function
	if (fight == BATTLE){
        BossAttack();
        if (elapsedTime > bossFightTime){
            bossSpeed();                        // Seeding
            bossFightTime = elapsedTime + 30;   // map and boss pattern refreshes every 30 seconds
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
    COORD c;
    std::cout << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < MAP_HEIGHT; i++){
        c.Y = i;
        for (int j = 0; j < MAP_WIDTH; j++){
            c.X = j;
            // Wall
            if (printMap[i][j] == 1){
                console.writeToBuffer(c, '|', 0x03);
            }
			// Lava
            else if (printMap[i][j] == 2){
                console.writeToBuffer(c, (char)247, 0x0C);
            }
			// Cobweb
            else if (printMap[i][j] == 3){
                console.writeToBuffer(c, 'X');
            }
			// Ammo for warrior
            else if (printMap[i][j] == 4){
                console.writeToBuffer(c, (char)236, 0x0B);
            }
			// Door
            else if (printMap[i][j] == 5){
                console.writeToBuffer(c, (char)239, 0x0B);
            }
            // Bomb
            else if (printMap[i][j] == 6){
                console.writeToBuffer(c, (char)235, 0x0B);
            }
            // Ammo
            else if (printMap[i][j] == 7){
                console.writeToBuffer(c, (char)240, 0x0B);
            }
            // Health
            else if (printMap[i][j] == 8){
                console.writeToBuffer(c, (char)3, 0x0C);
            }
            // Spawn points
            else if (printMap[i][j] == 9){
                console.writeToBuffer(c, (char)241);
            }
            // From A - E & K, Map doors
            // Door A
            else if (printMap[i][j] == 'A'){
                console.writeToBuffer(c, (char)239, 0x0B);
            }
            // Door B
            else if (printMap[i][j] == 'B'){
                console.writeToBuffer(c, (char)239, 0x0B);
            }
            // Door C
            else if (printMap[i][j] == 'C'){
                console.writeToBuffer(c, (char)239, 0x0B);
            }
            // Door D
            else if (printMap[i][j] == 'D'){
                console.writeToBuffer(c, (char)239, 0x0B);
            }
            // Door E
            else if (printMap[i][j] == 'E'){
                console.writeToBuffer(c, (char)239, 0x0B);
            }
            // Door K
            else if (printMap[i][j] == 'K'){
                console.writeToBuffer(c, (char)239, 0x0B);
            }
            // From Y - P, tutorial
            // Moving traps
            else if (printMap[i][j] == 'Z') {
                console.writeToBuffer(c, '*', 0x0E);
            }
            // Monster spawner
			else if (printMap[i][j] == 'Y') {
				console.writeToBuffer(c, (char)241);
			}
            // Health pack
			else if (printMap[i][j] == 'X') {
				console.writeToBuffer(c, (char)3, 0x0C);
			}
            // Ammo pack
			else if (printMap[i][j] == 'W') {
                console.writeToBuffer(c, (char)240, 0x0B);
			}
            // Bomb
			else if (printMap[i][j] == 'V') {
                console.writeToBuffer(c, (char)235, 0x0B);
			}
            // Super ghost
			else if (printMap[i][j] == 'U') {
				console.writeToBuffer(c, (char)69, 0x0A);
			}
            // Ghost
			else if (printMap[i][j] == 'T') {
				console.writeToBuffer(c, (char)69, 0x0E);
			}
            // Cobweb
			else if (printMap[i][j] == 'S') {
				console.writeToBuffer(c, 'X');
			}
            // Lava
			else if (printMap[i][j] == 'R') {
				console.writeToBuffer(c, (char)247, 0x0C);
			}
            // Wall
			else if (printMap[i][j] == 'Q') {
				console.writeToBuffer(c, '|', 0x03);
			}
            // Path for tutorial
			else if (printMap[i][j] == 'P') {
				console.writeToBuffer(c, ' ' , 0x03);
			}
            // Boss
            else if (printMap[i][j] == 'I') {
                console.writeToBuffer(c, (char)154, 0x0C);
            }
            else{
                console.writeToBuffer(c, " ");
            }
        }
        std::cout << std::endl;
    }
	textbox();      // Description for tutorial
	minimap();      // Minimap for gameplay
	HUD();          // HUD for gameplay
	
}

//-----------------//
// Player movement //
//-----------------//

void moveCharacter()
{
        //PLAYER MOVEMENT
        // JUMP UP
        if (keyPressed[K_UP] && keyPressed[K_SPACE] && charLocation.Y > 0)
        {        
            if (printMap[charLocation.Y - 2][charLocation.X] == 1){

            }    
            else{
                
                charLocation.Y -= 2; 
            }
        }
        // JUMP LEFT
        else if (keyPressed[K_LEFT] && keyPressed[K_SPACE] && charLocation.X > 0)
        {
            if (printMap[charLocation.Y][charLocation.X - 2] == 1){

            }
            else{
       
                charLocation.X -= 2;
            }
        }
        // JUMP DOWN
        else if (keyPressed[K_DOWN] && keyPressed[K_SPACE] && charLocation.Y < console.getConsoleSize().Y - 1)
        {
            if (printMap[charLocation.Y + 2][charLocation.X] == 1){
            }
            else{
             
                charLocation.Y += 2;
            }
        }
        // JUMP RIGHT
        else if (keyPressed[K_RIGHT] && keyPressed[K_SPACE] && charLocation.X < console.getConsoleSize().X - 1)
        {
            if (printMap[charLocation.Y][charLocation.X + 2] == 1){

            }
            else{
                
                charLocation.X += 2;
            }
        }
        //MOVE UP
        else if (keyPressed[K_UP] && charLocation.Y > 0)
        {
            if (printMap[charLocation.Y - 1][charLocation.X] == 1){
                
            }
            else{
                
                charLocation.Y -= 1;
            }
        }
        //MOVE LEFT
        else if (keyPressed[K_LEFT] && charLocation.X > 0)
        {
            if (printMap[charLocation.Y][charLocation.X -1] == 1){

            }
            else{
                
                charLocation.X -= 1;
            }
        }
        //MOVE DOWN
        else if (keyPressed[K_DOWN] && charLocation.Y < console.getConsoleSize().Y - 1)
        {
            if (printMap[charLocation.Y + 1][charLocation.X] == 1){

            }
            else{
          
                charLocation.Y += 1;
            }
        }
        //MOVE RIGHT
        else if (keyPressed[K_RIGHT] && charLocation.X < console.getConsoleSize().X - 1)
        {
            if (printMap[charLocation.Y][charLocation.X + 1] == 1){

            }
            else{
            
                charLocation.X += 1;
            }
        }
        mapChange();            // Change from one map to another
        refill();               // Refill items
}

void processUserInput()
{
    // pauses the game when player presses escape
    if (keyPressed[K_ESCAPE]){
        g_eGameState = PAUSE;
		PlaySound(NULL, NULL, 0);
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
    if (cobwebToken != 1){
        console.writeToBuffer(charLocation, (char)1, 0x0A);
    }
    else{
        console.writeToBuffer(charLocation, (char)1);
    }
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    console.flushBufferToConsole();
}

//-----------------//
// Gameover, Retry //
//-----------------//

void gameend(){
	clearScreen();
	std::string gameover;
	COORD c;
	c.Y = 6;
	c.X = 15;
	
	std::ifstream myfile;
	myfile.open("screen/gameover.txt");
	for (int i = 0; myfile.good(); i++){
		std::getline(myfile, gameover);
		console.writeToBuffer(c, gameover, 0x0E); // Prints the characters line by line after reading the text file
		c.Y += 1;
	}
	// Text for retry
	c.X = 28;
	c.Y = 13;
	console.writeToBuffer(c, "Press R to retry", 0x0E);
	if (keyPressed[K_R]) {
        levelReset();
	} // Change gamestate from gameover to game and allows player to retry the stage they are at
    if (classes == BALANCED) {
        player.health = 4;
        player.ammo = 5;
    } // Adventurer/Balanced class, health 4, 4 ammo at start, 2 range 
    else if (classes == WARRIOR) {
        player.health = 4;
        player.ammo = 1;
    } // Warrior class, health 6, infinite ammo, 1 range
    else if (classes == ARCHER) {
        player.health = 2;
        player.ammo = 8;
    } // Archer class, health 2 , 8 ammo at start, 3 range
	soundreset();
	//Boss Projectile
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
} // Boss projectile for all the 8 different directions 

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
        Monster = TUTORIAL;
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

//---------------------//
// Initial Ghost spawn //
//---------------------//

void setmonsterlocation(){
    g_cChaserLoc.X = 26;
    g_cChaserLoc.Y = 2;
    g_cChaser1Loc.X = 26;
    g_cChaser1Loc.Y = 24;
    charLocation.X = 3;
    charLocation.Y = 13;
    t_monsterDied = 0;
    t_monster1Died = 0;
} // Code the coordinates for each entity

//--------------------------//
// Description for tutorial //
//--------------------------//

void textbox() {
	COORD c;	
	// Wall
	if (printMap[charLocation.Y][charLocation.X] == 'Q'){
		c.X = 6;
		c.Y = 7;
		console.writeToBuffer(c, "This is a Wall");
        c.X = 6;
        c.Y = 8;
        console.writeToBuffer(c, "Able to jump over single layer wall");
		c.X = 6;
		c.Y = 9;
		console.writeToBuffer(c, "WOOOO time to parkour", 0x0A);
	}

    // Moving traps
    if (printMap[charLocation.Y][charLocation.X] == 'Z'){
        c.X = 6;
        c.Y = 7;
        console.writeToBuffer(c, "This is a moving trap");
        c.X = 6;
        c.Y = 8;
        console.writeToBuffer(c, "Deals a damage when you step into it");
        c.X = 6;
        c.Y = 9;
        console.writeToBuffer(c, "Won't get in your way... most of the time", 0x0A);
    }
	
	// Lava
    if (printMap[charLocation.Y][charLocation.X] == 'R'){
        c.X = 6;
		c.Y = 7;
		console.writeToBuffer(c, "This is lava");
        c.X = 6;
        c.Y = 8;
        console.writeToBuffer(c, "Deals 2 damage when you step into it");
        c.X = 6;
        c.Y = 9;
        console.writeToBuffer(c, "It's almost as hot as me", 0x0A);
	}

    // Door
    if (printMap[charLocation.Y][charLocation.X] == 5){
        c.X = 6;
        c.Y = 7;
        console.writeToBuffer(c, "This is a door");
        c.X = 6;
        c.Y = 8;
        console.writeToBuffer(c, "It transports you to another level");
        c.X = 6;
        c.Y = 9;
        console.writeToBuffer(c, "Onward!", 0x0A);
    }

	// Cobwebs
	if (printMap[charLocation.Y][charLocation.X] == 'S'){
        c.X = 6;
		c.Y = 7;
		console.writeToBuffer(c, "This is Cobwebs");
        c.X = 6;
        c.Y = 8;
        console.writeToBuffer(c, "You get stuck for a second");
        c.X = 6;
        c.Y = 9;
        console.writeToBuffer(c, "White sticky stuff", 0x0A);
	}

    // Ghost
	if (printMap[charLocation.Y][charLocation.X] == 'T'){
        c.X = 6;
        c.Y = 7;
		console.writeToBuffer(c, "This is a ghost");
        c.X = 6;
        c.Y = 8;
        console.writeToBuffer(c, "It deals 1 damage to you if it touches you");
        c.X = 6;
        c.Y = 9;
        console.writeToBuffer(c, "BOOOOO spookyyyyy", 0x0A);
	}

    // Super ghost
	if (printMap[charLocation.Y][charLocation.X] == 'U'){
        c.X = 6;
        c.Y = 7;
		console.writeToBuffer(c, "This is a super ghost");
        c.X = 6;
        c.Y = 8;
        console.writeToBuffer(c, "It appears when 2 ghost combines");
        c.X = 6;
        c.Y = 9;
        console.writeToBuffer(c, "It deals 2 damage to you if it touches you");
        c.X = 6;
        c.Y = 10;
        console.writeToBuffer(c, "Twice as creepy", 0x0A);
	}
	
    // Bomb
	if (printMap[charLocation.Y][charLocation.X] == 'V'){
		c.X = 6;
		c.Y = 7;
		console.writeToBuffer(c, "This is a bomb");
		c.X = 6;
		c.Y = 8;
		console.writeToBuffer(c, "It kills all the ghosts on the map");
        c.X = 6;
        c.Y = 9;
        console.writeToBuffer(c, "Jet fuels can't melt steel beams", 0x0A);
	}
	// Ammo pack
	if (printMap[charLocation.Y][charLocation.X] == 'W'){
		c.X = 6;
		c.Y = 7;
		console.writeToBuffer(c, "This is an ammo pack");
		c.X = 6;
		c.Y = 8;
		console.writeToBuffer(c, "Refills ammo by 5");
        c.X = 6;
        c.Y = 9;
        console.writeToBuffer(c, "Where's the guns?", 0x0A);
	}
	// Health pack
	if (printMap[charLocation.Y][charLocation.X] == 'X'){
		c.X = 6;
		c.Y = 7;
		console.writeToBuffer(c, "This is a Health Pack");
		c.X = 6;
		c.Y = 8;
		console.writeToBuffer(c, "Refills health by 1");
        c.X = 6;
        c.Y = 9;
        console.writeToBuffer(c, "They are literally human hearts...", 0x0A);
	}
	// Monster Spawner
	if (printMap[charLocation.Y][charLocation.X] == 'Y'){
		c.X = 6;
		c.Y = 7;
		console.writeToBuffer(c, "This is a ghost spawner");
		c.X = 6;
		c.Y = 8;
        console.writeToBuffer(c, "Monster spawns here when killed");
        c.X = 6;
        c.Y = 9;
        console.writeToBuffer(c, "Able to walk through it");
        c.X = 6;
        c.Y = 10;
        console.writeToBuffer(c, "At least you don't spawn there", 0x0A);
	}
    // Path for tutorial
	if (printMap[charLocation.Y][charLocation.X] == 'P')
	{
		c.X = 8;
		c.Y = 7;
		console.writeToBuffer(c, "Step on each item to know what it is!");
		c.X = 8;
		c.Y = 12;
		console.writeToBuffer(c, "Arrow Keys to Move");
		c.X = 8;
		c.Y = 14;
		console.writeToBuffer(c, "WASD to shoot in respective directions");
		c.X = 8;
		c.Y = 16;
		console.writeToBuffer(c, "Press & hold Space + Arrow key to jump");
        c.X = 8;
        c.Y = 18;
        console.writeToBuffer(c, "'Q' to use class ultimate");
        c.X = 8;
        c.Y = 20;
        console.writeToBuffer(c, "'E' to use bomb");
        c.X = 8;
        c.Y = 22;
        console.writeToBuffer(c, "'Esc' to pause game");
	} // Basic instructions shown at start of game, hard coded into array
}

//----------------------------//
// Invincibility when damaged //
//----------------------------//

void invincibility(){
    if (elapsedTime > t_invincibility){
        iToken = 0;
    }
}

//-------------//
// Retry level //
//-------------//

void retry(){
    switch (level){
        case RIVERROOM: mapRiver();
            break;
        case LIBRARYROOM: mapLibrary();
            break;
        case LECTUREHALLROOM: mapLectureHall();
            break;
        case MERRYGRROOM: mapMerryGR();
            break;
        case THEHROOM: mapTheH();
            break;
        case BOSSROOM: BossFight();  
            break;
    }
    minimap();
}

//-------------//
// Sound reset //
//-------------//

void soundreset(){ 
	gamesoundToken = 0;
	bossSoundToken = 0;
}

//---------------//
// Level reset //
//---------------//

void levelReset() { // Resets level when dead
    g_eGameState = GAME;
    player.bomb = 1;
    uCooldown = 0;
    fight = NORMAL;
    retry();
    cobwebToken = 0;
    timesRetry++;
    soundreset();
    gamesoundToken = 0;
    monsterToken = 1;
    monster1Token = 1;
    Bhealth = 50;
}

//------------//
// Game reset //
//------------//

void completeReset(){ // Reset the whole game
    soundreset();
    g_eGameState = SPLASH;
    player.bomb = 1;
    fight = NORMAL;
    level = TUTORIALROOM;
    tutorial();
    Bhealth = 50;
    healthDMG = 0;
    ammoUsed = 0;
    bombUsed = 0;
    t_monsterDied = 0;
    t_monster1Died = 0;
    uCooldown = 0;
    elapsedTime = 0;
    cobwebToken = 0;
}

//----------------------------//
// Render ghost & super ghost //
//----------------------------//

void renderMonster(){
    // render super monster
    if (g_cChaserLoc.X == g_cChaser1Loc.X && g_cChaserLoc.Y == g_cChaser1Loc.Y && monsterToken == 1 && monster1Token == 1){
            console.writeToBuffer(g_cChaserLoc, (char)238, 0x0D);
    }
    // normal monster
    else{
        if (monsterToken == 1) {
            if (level != TUTORIALROOM){
                console.writeToBuffer(g_cChaserLoc, (char)238, 0x0E);
            }
        }
        if (monster1Token == 1){
            if (level != TUTORIALROOM){
                console.writeToBuffer(g_cChaser1Loc, (char)238, 0x0E);
            }
        }
    }
}

//---------------------//
// Render moving traps //
//---------------------//

void renderGuards(){
    if (level == LIBRARYROOM){
        console.writeToBuffer(guarda, '*', 0x0E);
    }
    else if (level == RIVERROOM){
        console.writeToBuffer(guardb, '*', 0x0E);
    }
    else if (level == THEHROOM){
        console.writeToBuffer(guardc, '*', 0x0E);
    }
    if (level == MERRYGRROOM){
        console.writeToBuffer(guardd, '*', 0x0E);
    }
    if (level == LECTUREHALLROOM)
    {
        console.writeToBuffer(guarde, '*', 0x0E);
    }
}
void monstersMoveChecker(){
    if (monsterToken == 1) {
        moveMonster();      // moves ghost1
    }
    if (monster1Token == 1){
        moveMonster1();     // moves ghost2
    }
}