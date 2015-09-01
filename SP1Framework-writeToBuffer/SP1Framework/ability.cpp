#include "game.h"

extern CLASSES classes;
extern int iToken;
extern int Bhealth;
extern int bombUsed;
extern double elapsedTime; 
extern double uCooldown; // Ultimate skill cooldown
extern double t_tDamage; // Triple damage for warrior
extern double t_maxRange; // Ultimate skill for archer
extern double elapsedTime;
extern double uCooldown;
extern double t_tDamage;
extern double t_maxRange;
extern bool keyPressed[K_COUNT];

extern BOSS fight;

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
            bombUsed++;
        }
    }
}