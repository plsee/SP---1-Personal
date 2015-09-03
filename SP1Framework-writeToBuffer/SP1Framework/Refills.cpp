#include "game.h"
#include "Map.h"

extern int MaxHP;
extern char printMap[MAP_HEIGHT][MAP_WIDTH];
extern CLASSES classes;

extern COORD charLocation;

struct Stats {
    short health;
    short ammo;
    short bomb;
};

extern Stats player;

/* Refill
Done by Cher Yi , 26 Aug 2015
Checks for player ammo and refills it by 5 if possible when player steps on ammo pack
Checks player health and increases it by 1 when player steps on health pack
Checks player bomb and increases it by 1 when players steps on bomb kit
*/

void refill(){
    if (printMap[charLocation.Y][charLocation.X] == 7){
        if (player.ammo == 20){

        }
        else if (player.ammo + 5 > 20){
            printMap[charLocation.Y][charLocation.X] = 0;
            player.ammo = 20; // Does not allow player ammo to be above 20 
        }
        else if (classes == WARRIOR) {
            player.ammo = 1; // doesnt change for warrior as he has infinite ammo
        }
        else{
            printMap[charLocation.Y][charLocation.X] = 0;
            player.ammo += 5; // Add 5 to player ammo
        }

    }

    if ((printMap[charLocation.Y][charLocation.X] == 8)){
        if (player.health < MaxHP){
            player.health += 1; // Add 1 to player health
            printMap[charLocation.Y][charLocation.X] = 0;
        }
    }

    if (printMap[charLocation.Y][charLocation.X] == 6){
        if (player.bomb < 6) {
            printMap[charLocation.Y][charLocation.X] = 0;
            player.bomb += 1; // Add 1 to player bomb
        }
    }
}