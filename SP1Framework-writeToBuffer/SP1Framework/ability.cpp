#include "game.h"

extern CLASSES classes;
extern int iToken;
extern int Bhealth;
extern int bombUsed;
extern double elapsedTime; 
extern double uCooldown; // Ultimate skill cooldown
extern double t_dDamage; // Double damage for warrior
extern double t_maxRange; // Ultimate skill for archer
extern bool keyPressed[K_COUNT];

extern BOSS fight;

struct Stats {
    short health;
    short ammo;
    short bomb;
};
extern Stats player;

/* Classes
Done by Kwan Liang , 25 Aug 2015
Changes Gamestate to different states depending on which class is chosen
Changes player health and stats depending on class
*/

//--------------------------------//
// Ultimate skills for each class //
//--------------------------------//

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
                    t_dDamage = elapsedTime + 2;
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

//---------------//
// Bomb function //
//---------------//

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