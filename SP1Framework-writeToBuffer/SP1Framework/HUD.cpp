#include <sstream>
#include <iomanip>
#include "game.h"
#include "Framework\console.h"

extern int Bhealth;//Boss health
extern double elapsedTime;
extern double uCooldown;//Cooldown for Ultimate
extern Console console;
extern MAPSTATE level;
extern CLASSES classes;

struct Stats {
    short health;
    short ammo;
    short bomb;
};

extern Stats player;

/* HUD
The display for the player's health/ammo/bomb/boss hp
Done by Cher Yi , 25 Aug 2015
Checks using loops to add/minus respective stats
*/

//-----------------------------//
// Display player & boss stats //
//-----------------------------//

void HUD() {
    COORD c;
    #define HUD_WIDTH 22
    #define HUD_HEIGHT 17
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(1);
    ss.str("");
    ss << elapsedTime << "s";
    c.X = 24;
    c.Y = 0;
    console.writeToBuffer(c, ss.str());

    //defining HUD position
    c.X = console.getConsoleSize().X - 21;
    c.Y = console.getConsoleSize().Y - 16;

    //Health
    console.writeToBuffer(c, "HEALTH");
    if (player.health > 2){							 // Player health > 2, Health bar will be white
        for (int m = 0; m < player.health * 2; m++){
            c.X = console.getConsoleSize().X - 21 + m;
            c.Y = console.getConsoleSize().Y - 15;
            console.writeToBuffer(c, (char)220);
        }
    }
    else if (player.health == 2){					// Player health > 2, Health bar will be yellow
        for (int m = 0; m < player.health * 2; m++){
            c.X = console.getConsoleSize().X - 21 + m;
            c.Y = console.getConsoleSize().Y - 15;
            console.writeToBuffer(c, (char)220, 0x0E);
        }
    }
    else if (player.health == 1){					// Player health == 1, Health bar will be red
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
        if (classes == WARRIOR) {
            console.writeToBuffer(c, (char)236);
        }
    }
    //Bomb
    c.X = console.getConsoleSize().X - 21;
    c.Y = console.getConsoleSize().Y - 10;
    console.writeToBuffer(c, "BOMB");
    for (int m = 0; m < player.bomb; m++){
        c.X = console.getConsoleSize().X - 21 + m;
        c.Y = console.getConsoleSize().Y - 9;
        console.writeToBuffer(c, (char)235);
    }
    //Ultimate
    c.X = console.getConsoleSize().X - 21;
    c.Y = console.getConsoleSize().Y - 7;
    console.writeToBuffer(c, "Ultimate");
    c.X = console.getConsoleSize().X - 21;
    c.Y = console.getConsoleSize().Y - 6;
    if (elapsedTime > uCooldown) {
        console.writeToBuffer(c, (char)15); // Icon will not show when ultimate is on cooldown
    }
    //Boss HP
    if (level == BOSSROOM){
        c.X = console.getConsoleSize().X - 21;
        c.Y = console.getConsoleSize().Y - 4;
        console.writeToBuffer(c, "BOSS HP"); //only shows when the gamestate is BOSSROOM
        if (Bhealth >= 30){
            for (int m = 0; m <= (Bhealth - 30) / 2; m++){      //Health bar when hp is >= 30
                c.X = console.getConsoleSize().X - 21 + m;
                c.Y = console.getConsoleSize().Y - 3;
                console.writeToBuffer(c, (char)220);
            }
        }
        else if (Bhealth >= 10){					   //Health bar when hp is >= 10, Changes to yellow
            for (int m = 0; m <= (Bhealth - 10) / 2; m++){
                c.X = console.getConsoleSize().X - 21 + m;
                c.Y = console.getConsoleSize().Y - 3;
                console.writeToBuffer(c, (char)220, 0x0E);
            }
        }
        else if (Bhealth < 10){						   //Health bar when hp is < 10, Changes to red
            for (int m = 0; m < Bhealth; m++){
                c.X = console.getConsoleSize().X - 21 + m;
                c.Y = console.getConsoleSize().Y - 3;
                console.writeToBuffer(c, (char)220, 0x0C);
            }
        }
    }
}