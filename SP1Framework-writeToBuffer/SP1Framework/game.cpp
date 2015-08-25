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

int monsterdelay = 0; 
int monster1delay = 0;
int BAdelay = 0;
FILE *map;
GAMESTATES g_eGameState = SPLASH;
CLASSES classes = ARCHER;
DEATHSTATE die = SAD;
MONSTERSTATE Monster = TUTORIAL;
// Console object

Console console(75, 27, "SP1 Framework");


double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];

// Initial print map
char printMap[MAP_HEIGHT][MAP_WIDTH] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
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
    //Boss Projectile
    Bprojectile1.X = 26;
    Bprojectile1.Y = 13;

	

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
    case ARCHER: archer();
        break;
    case WARRIOR: warrior();
        break;
    default:
        break;
    }
}

void balanced() {
    player.health = 3;
    player.ammo = 5;
    player.bomb = 1;
}

void archer() {
    player.health = 2;
    player.ammo = 5;
    player.bomb = 1;
}

void warrior() {
    player.health = 4;
    player.ammo = 1;
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
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
	moveMonster();		//moves the monsters
	moveMonster1();
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
	projectile();     //projectile
    bomb();
    BossAttack();
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
            else if (printMap[i][j] == 'A'){
                console.writeToBuffer(c, (char)456);
            }
            else if (printMap[i][j] == 'B'){
                console.writeToBuffer(c, (char)456);
            }
            else if (printMap[i][j] == 'C'){
                console.writeToBuffer(c, (char)456);
            }
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
		trapLava();
        refill();
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

//collision check/damage calculation
void collision(){
    if (charLocation.X == g_cChaserLoc.X && charLocation.Y == g_cChaserLoc.Y){
		player.health -= 1;
		monsterDeath();
	}
}
// PROJECTILE
void projectile() {
    if (player.ammo > 0){
        if (keyPressed[K_W]) {
            player.ammo -= 1;
            g_cProjectile.X = charLocation.X;
            g_cProjectile.Y = charLocation.Y - 1;
            if (classes == WARRIOR) {
                player.ammo += 1;
                for (int i = 0; i < 1; ++i) {
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
	
	for (int m = 0; m < player.health; m++){
		c.X = console.getConsoleSize().X - 21 + m;
		c.Y = console.getConsoleSize().Y - 15;
		console.writeToBuffer(c, (char)233);
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
}
//seeding
void randomSeed(){
    int seed = 1;
    srand(seed);
}
//move the 1st monster
void moveMonster(){
    // CHASER MOVEMENT
    
    if (Monster == STARTGAME){
        monsterdelay++;
        if (monsterdelay == 10){
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
        collision();
    }
}
//move the 2nd monster
void moveMonster1(){
	// CHASER MOVEMENT
    if (Monster == STARTGAME){
        monster1delay++;
        if (monster1delay == 10){
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
        collision1();
    };
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
//2nd monster collision check
void collision1(){
	if (charLocation.X == g_cChaser1Loc.X && charLocation.Y  == g_cChaser1Loc.Y){
		monster1Death();
		player.health -= 1;
	} // Top left
}
//Refill Ammo
void refill(){
    if (printMap[charLocation.Y][charLocation.X] == 7){
        printMap[charLocation.Y][charLocation.X] = 0;
        if (player.ammo + 10 >= 20){
            player.ammo = 20;
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
	FILE * pFile;
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
	player.health = 3;
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
}
//Dying to traps
void trapLava(){
	if (printMap[charLocation.Y][charLocation.X] == 2){
		player.health = 0;
	}
    if (printMap[charLocation.Y][charLocation.X] == 3){
        player.health = 0;

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
	c.X = 3;
	c.Y = 7;
	if (printMap[charLocation.Y][charLocation.X] == 'Q'){
			console.writeToBuffer(c, "This is a Wall");
		}
	
	c.X = 7;
	c.Y = 7;
    if (printMap[charLocation.Y][charLocation.X] == 'R'){
		console.writeToBuffer(c, "This is lava");
	}
	c.X = 10;
	c.Y = 7;
	if (printMap[charLocation.Y][charLocation.X] == 'S'){
		console.writeToBuffer(c, "This is spikes");
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
	c.X = 20;
	c.Y = 7;
	if (printMap[charLocation.Y][charLocation.X] == 'V'){
		console.writeToBuffer(c, "This is a bomb");
	}
	c.X = 23;
	c.Y = 7;
	if (printMap[charLocation.Y][charLocation.X] == 'W'){
		console.writeToBuffer(c, "This is ammo pack");
	}
	c.X = 27;
	c.Y = 7;
	if (printMap[charLocation.Y][charLocation.X] == 'X'){
		console.writeToBuffer(c, "This is a Health Pack");
	}
	c.X = 30;
	c.Y = 7;
	if (printMap[charLocation.Y][charLocation.X] == 'Y'){
		console.writeToBuffer(c, "This is a monster spawner");
	}
	c.X = 8;
	c.Y = 20;
	if (printMap[charLocation.Y][charLocation.X] == 'P')
	console.writeToBuffer(c, "Step on each item to know what it is!");
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
	c.X = 33;
	console.writeToBuffer(c, "Start");
	// exit button
	c.Y = 19;
	c.X = 33;
	console.writeToBuffer(c, "Exit");
    Tpointer();
}
//BOMB
void bomb() {
    if (keyPressed[K_E]) {
        monsterDeath();
        monster1Death();
        player.bomb -= 1;
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
            g_eGameState = GAME;
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
            g_eGameState = GAME;
        }
        else if (PpointerLoc.Y == 19){
            tutorial();
            g_eGameState = SPLASH;
            elapsedTime = 0;
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
   console.writeToBuffer(Bprojectile1, (char)30, 0x0B);
   if (BAdelay == 1){
       if (printMap[Bprojectile1.Y][Bprojectile1.X] == 1){
           Bprojectile1.X = 26;
           Bprojectile1.Y = 13;
       }
       else{
           Bprojectile1.X += 2;
           Bprojectile1.Y += 1;
       }
       BAdelay = 0;
    }
   BAdelay++;
}

