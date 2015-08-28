#include "game.h"
#include "Framework\console.h"
#include <fstream>
#include <sstream>
#include <iostream>

extern bool keyPressed[K_COUNT];
extern Console console;
extern CLASSES classes;
extern GAMESTATES g_eGameState;
extern double elapsedTime;

extern COORD pointerCLoc;
extern COORD pointerCSLoc;
extern COORD border1CLoc;
extern COORD border2CLoc;
extern COORD CSdescLoc;

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