#include "game.h"
#include "Map.h"
#include "Framework\console.h"

extern char printMap[MAP_HEIGHT][MAP_WIDTH];
extern bool keyPressed[K_COUNT];
extern CLASSES classes;
extern BOSS fight;
extern Console console;
extern double elapsedTime;
extern double t_dDamage;
extern double t_maxRange;
extern int Bhealth;
extern int ammoUsed;

extern COORD g_cProjectile;
extern COORD charLocation;

struct Stats {
    short health;
    short ammo;
    short bomb;
};

extern Stats player;

/* projectiles for the different classes
Done by Kwan Liang , 21 Aug 2015
Checks if theres ammo, direction of projectile, walls, enemies and class
Checks classes and range of projectile
*/
double t_wProjectile = elapsedTime;

//--------------------------------//
// Damage to boss with projectile //
//--------------------------------//

void damageBoss() {
    if (fight == BATTLE){
        if (printMap[g_cProjectile.Y][g_cProjectile.X] == 'I'){
            if (elapsedTime < t_dDamage) {
                Bhealth -= 2;
            }
            else {
                Bhealth -= 1;
            }
        }
    }
}

//-----------------------------//
// Projectile damage direction //
//-----------------------------//

void damageUp() {
    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
        console.writeToBuffer(g_cProjectile, (char)30, 0x0B);
        projKill();
        projKill1();
        g_cProjectile.Y -= 1;
    }
}

void damageLeft() {
    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
        console.writeToBuffer(g_cProjectile, (char)17, 0x0B);
        projKill();
        projKill1();
        g_cProjectile.X -= 1;
    }
}

void damageDown() {
    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
        console.writeToBuffer(g_cProjectile, (char)31, 0x0B);
        projKill();
        projKill1();
        g_cProjectile.Y += 1;
    }
}

void damageRight() {
    if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
        console.writeToBuffer(g_cProjectile, (char)16, 0x0B);
        projKill();
        projKill1();
        g_cProjectile.X += 1;
    }
}

//---------------------------------//
// Projectile for specific Classes //
//---------------------------------//

void projectile() {
    if (player.ammo > 0){
        if (keyPressed[K_W]) {					//Shoot upwards when player presses W
            player.ammo -= 1;
            ammoUsed++;
            g_cProjectile.X = charLocation.X;
            g_cProjectile.Y = charLocation.Y - 1;
            if (classes == WARRIOR) {
                player.ammo = 1;				// Does not reduce ammo for warrior as he as infinite ammo
                if (elapsedTime > t_wProjectile) {
                    t_wProjectile = elapsedTime + 0.5;
                    for (int i = 0; i < 1; ++i) {
                        damageBoss();
                        damageUp();
                    }
                }
            }
            else if (classes == ARCHER) {
                if (elapsedTime < t_maxRange) {
                    for (int i = 0; i < 22; ++i) {
                        damageBoss();
                        damageUp();
                    }
                }
                else {
                    for (int i = 0; i < 4; ++i) {
                        damageBoss();
                        damageUp();
                    }
                }
            }
            else {
                for (int i = 0; i < 2; ++i) {
                    damageBoss();
                    damageUp();
                }
            }
        }
        else if (keyPressed[K_A]) {				//Shoots left when player presses A
            player.ammo -= 1;
            ammoUsed++;
            g_cProjectile.X = charLocation.X - 1;
            g_cProjectile.Y = charLocation.Y;
            if (classes == WARRIOR) {
                player.ammo += 1;
                if (elapsedTime > t_wProjectile) {
                    t_wProjectile = elapsedTime + 0.5;
                    for (int i = 0; i < 1; ++i) {
                        damageBoss();
                        damageLeft();
                    }
                }
            }
            else if (classes == ARCHER) {
                if (elapsedTime < t_maxRange) {
                    for (int i = 0; i < 75; ++i) {
                        damageBoss();
                        damageLeft();
                    }
                }
                else {
                    for (int i = 0; i < 4; ++i) {
                        damageBoss();
                        damageLeft();
                    }
                }
            }
            else {
                for (int i = 0; i < 2; ++i) {
                    damageBoss();
                    damageLeft();
                }
            }
        }
        else if (keyPressed[K_S]) {					//Shoots downwards when player presses S
            player.ammo -= 1;
            ammoUsed++;
            g_cProjectile.X = charLocation.X;
            g_cProjectile.Y = charLocation.Y + 1;
            if (classes == WARRIOR) {
                player.ammo += 1;
                if (elapsedTime > t_wProjectile) {
                    t_wProjectile = elapsedTime + 0.5;
                    for (int i = 0; i < 1; ++i) {
                        damageBoss();
                        damageDown();
                    }
                }
            }
            else if (classes == ARCHER) {
                if (elapsedTime < t_maxRange) {
                    for (int i = 0; i < 22; ++i) {
                        damageBoss();
                        damageDown();
                    }
                }
                else {
                    for (int i = 0; i < 4; ++i) {
                        damageBoss();
                        damageDown();
                    }
                }
            }
            else {
                for (int i = 0; i < 2; ++i) {
                    damageBoss();
                    damageDown();
                }
            }
        }
        else if (keyPressed[K_D]) {						//Shoots right when player presses D
            player.ammo -= 1;
            ammoUsed++;
            g_cProjectile.X = charLocation.X + 1;
            g_cProjectile.Y = charLocation.Y;
            if (classes == WARRIOR) {
                player.ammo += 1;
                if (elapsedTime > t_wProjectile) {
                    t_wProjectile = elapsedTime + 0.5;
                    for (int i = 0; i < 1; ++i) {
                        damageBoss();
                        damageRight();
                    }
                }
            }
            else if (classes == ARCHER) {
                if (elapsedTime < t_maxRange) {
                    for (int i = 0; i < 71; ++i) {
                        damageBoss();
                        damageRight();
                    }
                }
                else {
                    for (int i = 0; i < 4; ++i) {
                        damageBoss();
                        damageRight();
                    }
                }
            }
            else {
                for (int i = 0; i < 2; ++i) {
                    damageBoss();
                    damageRight();
                }
            }
        }
    }
}