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
extern COORD   Bprojectile1;
extern COORD   Bprojectile2;
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
    TpointerLoc.Y = 15;
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
    invincibility();
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
	case SPLASH: splash(); // splash screen
		break;
	case TITLE: titlescreen(); //title screen
		break;
    case PAUSE: pausemenu();  //pause screen
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

//seeding
void randomSeed(){
    int seed = 6;
    srand(seed);
}
//move the 1st monster
void moveMonster(){
    // CHASER MOVEMENT
    if (Monster == STARTGAME){
        monsterdelay++; //change gamestate so that the monster can move, and with a delay
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
            monsterdelay = 0; // resets delay after making a move
        }
    }
}
//move the 2nd monster
void moveMonster1(){
	// CHASER MOVEMENT
    if (Monster == STARTGAME){
        monster1delay++; //change gamestate so that the monster can move, and with a delay
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
            monster1delay = 0; // resets delay after making a move
        }
    }
}
// check if 1st monster gets shot
void projKill(){
	if (g_cChaserLoc.X == g_cProjectile.X && g_cChaserLoc.Y == g_cProjectile.Y){
		monsterDeath(); // monster dies after getting hit by projectile
	}
}
// check if second monster gets shot
void projKill1(){
	if (g_cChaser1Loc.X == g_cProjectile.X && g_cChaser1Loc.Y == g_cProjectile.Y){
		monster1Death(); // monster dies after getting hit by projectile
	}
}
//1st monster death
void monsterDeath(){
	int spawnLocation = rand() % 3; // Spawns the monster randomly between 3 different spawn locations
	g_cChaserLoc.X = 26;
	if (spawnLocation == 0){
		g_cChaserLoc.Y = 2; // location 1
	}
	else if (spawnLocation == 1){
		g_cChaserLoc.Y = 14; // location 2
	}
	else{
		g_cChaserLoc.Y = 24; // location 3
	}
}
// 2nd monster death
void monster1Death(){
	int spawnLocation = rand() % 3; // Spawns the monster randomly between 3 different spawn locations
	g_cChaser1Loc.X = 26;
	if (spawnLocation == 0){
		g_cChaser1Loc.Y = 14; // location 1
	}
	else if (spawnLocation == 1){
		g_cChaser1Loc.Y = 24; // location 2
	}
	else{
		g_cChaser1Loc.Y = 2; // location 3
	}
}

//collision check/damage calculation
//1st monster collision check
void collision(){
    if (charLocation.X == g_cChaserLoc.X && charLocation.Y == g_cChaserLoc.Y){
        monsterDeath(); // Monster dies after damaging player
        if (iToken == 0){
            player.health -= 1; // reduces player health by 1
            iToken += 1;
            t_invincibility = elapsedTime + 0.5; // allows player to have invicibility for 0.5 sec after being damaged
        }
    }
}
//2nd monster collision check
void collision1(){
     if (charLocation.X == g_cChaser1Loc.X && charLocation.Y  == g_cChaser1Loc.Y){
		monster1Death(); // Monster dies after damaging player
        if (iToken == 0){
            player.health -= 1; // reduces player health by 1
            iToken += 1;
            t_invincibility = elapsedTime + 0.5; // allows player to have invicibility for 0.5 sec after being damaged
        }
	}
}
//Refill Ammo & Health
void refill(){
    if (printMap[charLocation.Y][charLocation.X] == 7){
        printMap[charLocation.Y][charLocation.X] = 0;
        if (player.ammo + 10 >= 20){
            player.ammo = 20; // Does not allow player ammo to be above 20 
        }
        else if (classes == WARRIOR) {
            player.ammo = 1; // doesnt change for warrior as he has infinite ammo
        }
        else{
            player.ammo += 5; // Ammo pack refills ammo by 5
        }
	}
    if ((printMap[charLocation.Y][charLocation.X] == 8)){
        if (player.health < MaxHP){
            player.health += 1; // Refills player health by 1
            printMap[charLocation.Y][charLocation.X] = 0;
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
		console.writeToBuffer(c, gamesplash, 0x0E); // Prints the characters line by line after reading the text file
		c.Y += 1;
	}
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
    Bhealth = 50;
} // Boss projectile for all the 8 different directions 

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
	} // Basic instructions shown at start of game, hard coded into array
}

// title screen
void titlescreen(){
	clearScreen();
	std::string title;
	COORD c;
	c.Y = 3;
	c.X = 10;
	std::ifstream myfile;
	myfile.open("screen/title.txt");
	for (int i = 0; myfile.good(); i++){
		std::getline(myfile, title);
		console.writeToBuffer(c, title, 0x0E);
		c.Y += 1;
	} // prints out the characters line by line

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
            if (fight == BATTLE) {
                Bhealth -= 5;
            } // Kills off enemy and reduces boss health by 5 if fighting boss
		}
    }
}
//TITLE POINTER
void Tpointer(){
    if (keyPressed[K_UP]){
        TpointerLoc.Y = 15;
    } // Move pointer upwards
    else if (keyPressed[K_DOWN]){
        TpointerLoc.Y = 19;
    } // Move pointer downwards
    console.writeToBuffer(TpointerLoc, ">");
    if (keyPressed[K_RETURN]){
        if (TpointerLoc.Y == 15){
            g_eGameState = CLASSSELECT;
        }
        else if (TpointerLoc.Y == 19){
            g_quitGame = true;
        } //confirm selection
    }
}
// pause screen
void Ppointer(){
    //Up button pressed
    if (keyPressed[K_UP]){
        if (PpointerLoc.Y == 15){
            PpointerLoc.Y = 17;
        } // changes the pointer location by changing the coordinates
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
        } // changes the pointer location by changing the coordinates
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
        } // move to the game screen
        else if (PpointerLoc.Y == 17){
            tutorial();
            g_eGameState = GAMEOVER;
        } // move to game over screen
        else if (PpointerLoc.Y == 19){
            tutorial();
            g_eGameState = SPLASH;
            elapsedTime = 2;
        } // move to splash screen
    }
}
//Pause menu
void pausemenu(){
		clearScreen();
		std::string pause;
		COORD c;
		c.Y = 3;
		c.X = 10;
		std::ifstream myfile;
		myfile.open("screen/pause.txt"); // prints the characters from text files to screen
		for (int i = 0; myfile.good(); i++){
			std::getline(myfile, pause);
			console.writeToBuffer(c, pause, 0x0E);
			c.Y += 1;
		} // print line by line 

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
