// This is the main file for the game logic and function
#include "game.h"
#include "Map.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

extern char BossMap[MAP_HEIGHT][MAP_WIDTH];
extern char printMap[MAP_HEIGHT][MAP_WIDTH];
extern BOSS fight;
extern int iToken; 
extern int monsterToken;
extern int monster1Token;
extern COORD    Bprojectile1;
extern COORD    Bprojectile2;
extern COORD	Bprojectile3;
extern COORD	Bprojectile4;
extern COORD	Bprojectile5;
extern COORD	Bprojectile6;
extern COORD	Bprojectile7;
extern COORD	Bprojectile8;
bool keyPressed[K_COUNT];
int Phealth = 0;
int cobwebToken = 0;
int monsterdelay = 0; 
int monster1delay = 0;
int Bhealth = 50;
int showCD = 0;
int MaxHP = 0;
double uCooldown = 0;
double elapsedTime;
double deltaTime;
double bossFightTime = elapsedTime;
double t_invincibility = elapsedTime;
double t_tDamage = elapsedTime;
double t_maxRange = elapsedTime;
double cobweb = elapsedTime;
double cobwebInvul = elapsedTime;
FILE *map;
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
    keyPressed[K_Q] = isKeyPressed('Q');
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
// Balanced/Adventure class
void balanced() {
    player.health = 4;
    player.ammo = 5;
    player.bomb = 1;
    MaxHP = 4;
}
// Warrior class
void warrior() {
    player.health = 6;
    player.ammo = 1;
    player.bomb = 1;
    MaxHP = 6;
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
		case SPLASH : splashwait();
	}
}

void gameplay(){
    processUserInput();// checks if you should change states or do something else with the game, e.g. pause, exit
    // Cobwebbed
    if (cobwebToken == 0){
        moveCharacter();// moves the character, collision detection, physics, etc
    }
    invincibility();
    if (monsterToken == 1) {
        moveMonster();//moves the monsters
    }
    if (monster1Token == 1){
        moveMonster1();
    }
    if (Monster == STARTGAME){
        monsterDamage();
    }// check monster dmg
    trapLava();// check traps
    spawnMonster();//check if enemy will spawn
    spawnMonster1();
    // sound can be played here too.
    // When the player dies and the gamestate switches to the game over screen
	if (player.health <= 0){
		g_eGameState = GAMEOVER;
	}
    // When the boss dies and the gamestate switches to the victory screen
    if (Bhealth <= 0){
        g_eGameState = VICTORY;
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
	case SPLASH: splash(); // splash screen
		break;
	case TITLE: titlescreen(); // title screen
		break;
    case VICTORY: victory(); // victory screen
        break;
    case PAUSE: pausemenu();  // pause screen
        break;
    case CLASSSELECT: classSelect();  // class selection screen
        break;
	case GAME: renderGame();  // Game screen
		break;
	case GAMEOVER: gameend(); // Retry screen
		break;
	}
	renderToScreen();// dump the contents of the buffer to the screen, one frame worth of game
}

void renderGame() {
	renderMap(); // renders the character into the buffer
	renderCharacter();  // renders the character into the buffer
	projectile();     // projectile
    bomb(); // bomb
    Ultimate(); // ultimate skills
	if (fight == BATTLE){
		BossAttack();
        if (elapsedTime > bossFightTime){
            bossFightTime = elapsedTime + 30;
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
                console.writeToBuffer(c, (char)240, 0x0B);
            }
            //8 is health
            else if (printMap[i][j] == 8){
                console.writeToBuffer(c, (char)3, 0x0C);
            }
            //9 spawn points
            else if (printMap[i][j] == 9){
                console.writeToBuffer(c, (char)241);
            }
            // From A - K maps
            else if (printMap[i][j] == 'A'){
                console.writeToBuffer(c, (char)239, 0x04);
            }
            else if (printMap[i][j] == 'B'){
                console.writeToBuffer(c, (char)239, 0x04);
            }
            else if (printMap[i][j] == 'C'){
                console.writeToBuffer(c, (char)239, 0x04);
            }
            else if (printMap[i][j] == 'D'){
                console.writeToBuffer(c, (char)239, 0x04);
            }
            else if (printMap[i][j] == 'E'){
                console.writeToBuffer(c, (char)239, 0x04);
            }
            else if (printMap[i][j] == 'K'){
                console.writeToBuffer(c, (char)239, 0x04);
            }
            // From Y - P tutorial
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
				console.writeToBuffer(c, (char)69, 0x0D);
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
            // Path
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
        mapChange();
        refill();
		Getdamagedbyboss();
}
void processUserInput()
{
    // pauses the game when player presses escape
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
    if (cobwebToken != 1){
        console.writeToBuffer(charLocation, (char)232, 0x0A);
    }
    else{
        console.writeToBuffer(charLocation, (char)232);
    }
    // render super monster
    if (g_cChaserLoc.X == g_cChaser1Loc.X && g_cChaserLoc.Y == g_cChaser1Loc.Y){
        if (monsterToken == 1){
            console.writeToBuffer(g_cChaserLoc, (char)238, 0x0D);
        }
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

//seeding
void randomSeed(){
    int seed = 6;
    srand(seed);
}

//Gameover,Retry screen
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
		g_eGameState = GAME;
        player.bomb = 1;
        uCooldown = 0;
        fight = NORMAL;
        retry();
		cobwebToken = 0;
	} // Change gamestate from gameover to game and allows player to retry the stage they are at
    if (classes == BALANCED) {
        player.health = 4;
        player.ammo = 5;
    } // Adventurer/Balanced class, health 4, 4 ammo at start, 2 range 
    else if (classes == WARRIOR) {
        player.health = 6;
        player.ammo = 1;
    } // Warrior class, health 6, infinite ammo, 1 range
    else if (classes == ARCHER) {
        player.health = 2;
        player.ammo = 8;
    } // Archer class, health 2 , 8 ammo at start, 3 range

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
// initial monster spawn
void setmonsterlocation(){
    g_cChaserLoc.X = 26;
    g_cChaserLoc.Y = 2;
    g_cChaser1Loc.X = 26;
    g_cChaser1Loc.Y = 24;
    charLocation.X = 3;
    charLocation.Y = 13;
} // Code the coordinates for each entity

// textbox for tutorial screen
void textbox() {
	COORD c;	
	//wall
	if (printMap[charLocation.Y][charLocation.X] == 'Q'){
			c.X = 6;
			c.Y = 7;
			console.writeToBuffer(c, "This is a Wall");
			c.X = 6;
			c.Y = 8;
			console.writeToBuffer(c, "You can jump over 1 layer thick walls");
		}
	
	//Lava
    if (printMap[charLocation.Y][charLocation.X] == 'R'){
        c.X = 6;
		c.Y = 7;
		console.writeToBuffer(c, "This is lava");
        c.X = 6;
		c.Y = 8;
		console.writeToBuffer(c, "It does 2 damage instantly");
	}
	//cobwebs
	if (printMap[charLocation.Y][charLocation.X] == 'S'){
        c.X = 6;
		c.Y = 7;
		console.writeToBuffer(c, "This is Cobwebs");
        c.X = 6;
		c.Y = 8;
		console.writeToBuffer(c, "It makes you stop moving for 1 second");
	}

	if (printMap[charLocation.Y][charLocation.X] == 'T'){
        c.X = 6;
        c.Y = 7;
		console.writeToBuffer(c, "This is a ghost");
        c.X = 6;
        c.Y = 8;
        console.writeToBuffer(c, "It deals 1 damage to you if it touches you");
	}

	if (printMap[charLocation.Y][charLocation.X] == 'U'){
        c.X = 6;
        c.Y = 7;
		console.writeToBuffer(c, "This is a super ghost");
        c.X = 6;
        c.Y = 8;
        console.writeToBuffer(c, "It appears when 2 ghost combines");
        c.X = 6;
        c.Y = 8;
        console.writeToBuffer(c, "It deals 2 damage to you if it touches you");
	}
	
	if (printMap[charLocation.Y][charLocation.X] == 'V'){
		c.X = 6;
		c.Y = 7;
		console.writeToBuffer(c, "This is a bomb");
		c.X = 6;
		c.Y = 8;
		console.writeToBuffer(c, "It kills all the ghosts on the map");
	}
	// Ammo pack
	if (printMap[charLocation.Y][charLocation.X] == 'W'){
		c.X = 6;
		c.Y = 7;
		console.writeToBuffer(c, "This is an ammo pack");
		c.X = 6;
		c.Y = 8;
		console.writeToBuffer(c, "Refills ammo by 5");
	}
	// Health pack
	if (printMap[charLocation.Y][charLocation.X] == 'X'){
		c.X = 6;
		c.Y = 7;
		console.writeToBuffer(c, "This is a Health Pack");
		c.X = 6;
		c.Y = 8;
		console.writeToBuffer(c, "Refills health by 1");
	}
	//Monster Spawner
	if (printMap[charLocation.Y][charLocation.X] == 'Y'){
		c.X = 6;
		c.Y = 7;
		console.writeToBuffer(c, "This is a monster spawner");
		c.X = 6;
		c.Y = 8;
        console.writeToBuffer(c, "Monster spawns here when killed");
        c.X = 6;
        c.Y = 9;
        console.writeToBuffer(c, "Able to walk through it");
	}
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

//BOMB
void bomb() {
    if (keyPressed[K_E]) {
		if (player.bomb > 0){
			monsterDeath();
			monster1Death();
			player.bomb -= 1;
            if (fight == BATTLE) {
                Bhealth -= 5;
            } // Kills off enemy and reduces boss health by 5 if fighting boss
		}
    }
}

void invincibility(){
    if (elapsedTime > t_invincibility){
        iToken = 0;
    }
}

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
