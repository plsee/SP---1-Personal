#include "game.h"
#include "Framework\console.h"
#include <fstream>
#include <sstream>
#include <iostream>

extern int Bhealth;
extern bool keyPressed[K_COUNT];
extern double elapsedTime;
extern Console console;
extern GAMESTATES g_eGameState;
extern CLASSES classes;
extern BOSS fight;
extern MAPSTATE level;

extern COORD TpointerLoc;
extern COORD PpointerLoc;
extern COORD pointerCLoc;
extern COORD pointerCSLoc;
extern COORD border1CLoc;
extern COORD border2CLoc;
extern COORD CSdescLoc;

struct Stats {
    short health;
    short ammo;
    short bomb;
};

extern Stats player;

//--------------------------------------------//
// Waiting time before Splash Screen switches //
//--------------------------------------------//

void splashwait(){
    if (elapsedTime > 3.0){
        g_eGameState = TITLE;
    }
}

//---------------//
// Splash Screen //
//---------------//

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

//------------//
// Title Menu //
//------------//

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
    c.Y = 18;
    c.X = 34;
    console.writeToBuffer(c, "Start");
    // exit button
    c.Y = 19;
    c.X = 34;
    console.writeToBuffer(c, "Exit");
    Tpointer();
}

//----------------------//
// Title Menu's pointer //
//----------------------//

void Tpointer(){
    if (keyPressed[K_UP]){
        TpointerLoc.Y = 18;
    } // Move pointer upwards
    else if (keyPressed[K_DOWN]){
        TpointerLoc.Y = 19;
    } // Move pointer downwards
    console.writeToBuffer(TpointerLoc, ">");
    if (keyPressed[K_RETURN]){
        if (TpointerLoc.Y == 18){
            g_eGameState = CLASSSELECT;
        }
        else if (TpointerLoc.Y == 19){
            g_quitGame = true;
        } //confirm selection
    }
}

//--------------//
// Pause Screen //
//--------------//

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

//------------------------//
// Pause Screen's pointer //
//------------------------//

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
    if (keyPressed[K_RETURN]){
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
            fight = NORMAL;
        } // move to splash screen
    }
}

//----------------------------------------//
// Open design for Classes from text file //
//----------------------------------------//

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

//------------------------//
// Class Selection border //
//------------------------//

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

//-------------------//
// Class description //
//-------------------//

void CSdesc() {
    if (pointerCLoc.X == 7){
        CSdescLoc.X = 6;
        CSdescLoc.Y = 23;
        console.writeToBuffer(CSdescLoc, "Health: 4");
        CSdescLoc.X = 6;
        CSdescLoc.Y = 24;
        console.writeToBuffer(CSdescLoc, "Ammo: 5");
        CSdescLoc.X = 6;
        CSdescLoc.Y = 25;
        console.writeToBuffer(CSdescLoc, "Bomb: 1");
        CSdescLoc.X = 22;
        CSdescLoc.Y = 23;
        console.writeToBuffer(CSdescLoc, "Projectile Range: 2");
        CSdescLoc.X = 22;
        CSdescLoc.Y = 24;
        console.writeToBuffer(CSdescLoc, "Ultimate: Trusty First-Aid Kit");
        CSdescLoc.X = 32;
        CSdescLoc.Y = 25;
        console.writeToBuffer(CSdescLoc, "Restore health to 4");
    }
    else if (pointerCLoc.X == 27){
        CSdescLoc.X = 6;
        CSdescLoc.Y = 23;
        console.writeToBuffer(CSdescLoc, "Health: 6");
        CSdescLoc.X = 6;
        CSdescLoc.Y = 24;
        console.writeToBuffer(CSdescLoc, "Ammo: Infinite");
        CSdescLoc.X = 6;
        CSdescLoc.Y = 25;
        console.writeToBuffer(CSdescLoc, "Bomb: 1");
        CSdescLoc.X = 22;
        CSdescLoc.Y = 23;
        console.writeToBuffer(CSdescLoc, "Projectile Range: 1");
        CSdescLoc.X = 22;
        CSdescLoc.Y = 24;
        console.writeToBuffer(CSdescLoc, "Ultimate: Warrior's Rage");
        CSdescLoc.X = 32;
        CSdescLoc.Y = 25;
        console.writeToBuffer(CSdescLoc, "Triple damage for 1 second");
    }
    else if (pointerCLoc.X == 47){
        CSdescLoc.X = 6;
        CSdescLoc.Y = 23;
        console.writeToBuffer(CSdescLoc, "Health: 2");
        CSdescLoc.X = 6;
        CSdescLoc.Y = 24;
        console.writeToBuffer(CSdescLoc, "Ammo: 8");
        CSdescLoc.X = 6;
        CSdescLoc.Y = 25;
        console.writeToBuffer(CSdescLoc, "Bomb: 1");
        CSdescLoc.X = 22;
        CSdescLoc.Y = 23;
        console.writeToBuffer(CSdescLoc, "Projectile Range: 4");
        CSdescLoc.X = 22;
        CSdescLoc.Y = 24;
        console.writeToBuffer(CSdescLoc, "Ultimate: True Marksman");
        CSdescLoc.X = 32;
        CSdescLoc.Y = 25;
        console.writeToBuffer(CSdescLoc, "Max range for half a second");
    }
}

//----------------//
// Victory Screen //
//----------------//

void victory() {
    clearScreen();
    std::string victory;
    COORD c;
    c.Y = 6;
    c.X = 15;
    std::ifstream myfile;
    FILE * pFile;
    myfile.open("screen/victory.txt");
    for (int i = 0; myfile.good(); i++){
        std::getline(myfile, victory);
        console.writeToBuffer(c, victory, 0x0E);
        c.Y += 1;
    }
    c.X = 28;
    c.Y = 13;
    console.writeToBuffer(c, "Press R to return to title screen", 0x0E);
    if (keyPressed[K_R]) {
        g_eGameState = GAME;
        player.bomb = 1;
        fight = NORMAL;
        g_eGameState = SPLASH;
        level = TUTORIALROOM;
        tutorial();
        Bhealth = 50;
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
}