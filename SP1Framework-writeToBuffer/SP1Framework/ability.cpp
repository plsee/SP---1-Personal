#include "game.h"

extern CLASSES classes;
extern int iToken;
extern double elapsedTime;
extern double uCooldown;
extern double t_tDamage;
extern double t_maxRange;
extern bool keyPressed[K_COUNT];

struct Stats {
    short health;
    short ammo;
    short bomb;
};
extern Stats player;

//---------------------//
// Ability for Classes //
//---------------------//

void Ultimate() {
    if (classes == BALANCED) {
        if (elapsedTime > uCooldown) {
            if (keyPressed[K_Q]) {
                uCooldown = elapsedTime + 60;
                player.health = 4;
            }
        }
    }
    if (classes == WARRIOR) {
        if (elapsedTime > uCooldown) {
            if (keyPressed[K_Q]) {
                uCooldown = elapsedTime + 60;
                if (iToken == 0){
                    iToken += 1;
                    t_tDamage = elapsedTime + 1;
                }
            }
        }
    }
    if (classes == ARCHER) {
        if (elapsedTime > uCooldown) {
            if (keyPressed[K_Q]) {
                uCooldown = elapsedTime + 60;
                t_maxRange = elapsedTime + 0.5;
            }
        }
    }
}