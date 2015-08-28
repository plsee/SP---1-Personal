#include "game.h"
#include "Map.h"

extern char printMap[MAP_HEIGHT][MAP_WIDTH];

extern int iToken;
extern int cobwebToken;
extern double elapsedTime;
extern double t_invincibility;
extern double cobweb;
extern double cobwebInvul;

extern COORD charLocation;

struct Stats {
    short health;
    short ammo;
    short bomb;
};

extern Stats player;

//-----------------//
// Traps Functions //
//-----------------//

void trapLava(){
    //LAVA
    if (printMap[charLocation.Y][charLocation.X] == 2){
        if (iToken == 0){
            player.health -= 2;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
    }
    //COBWEBBED
    if (printMap[charLocation.Y][charLocation.X] == 3){
        if (elapsedTime > cobwebInvul){
            if (cobwebToken == 0){
                cobwebToken += 1;
                cobweb = elapsedTime + 1.5;
                cobwebInvul = elapsedTime + 1.7;
            }
        }
    }
	if (elapsedTime < cobwebInvul && elapsedTime > cobweb){
		cobwebToken = 0;
	}
}