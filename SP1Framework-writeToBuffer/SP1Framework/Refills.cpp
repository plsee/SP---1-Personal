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

//Refill Health, Ammo & Bomb
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