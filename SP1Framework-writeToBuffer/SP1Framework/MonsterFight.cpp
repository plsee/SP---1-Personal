#include "game.h"

int monsterToken = 1;
int monster1Token = 1;
int spawnToken = 0;
int spawn1Token = 0;
extern int monsterdelay;
extern int monster1delay;
extern int iToken;
double t_monsterDied;
double t_monster1Died;
extern double elapsedTime;
extern double t_invincibility;

extern MONSTERSTATE Monster;

extern COORD charLocation;
extern COORD g_cChaserLoc;
extern COORD g_cChaser1Loc;
extern COORD g_cProjectile;

struct Stats {
    short health;
    short ammo;
    short bomb;
};

extern Stats player;

//---------------------//
// Moves the 1st ghost //
//---------------------//

void moveMonster(){
    // CHASER MOVEMENT
    if (Monster == STARTGAME){
        monsterdelay++; //change gamestate so that the monster can move, and with a delay
        if (monsterdelay == 5){
            if (charLocation.Y < g_cChaserLoc.Y){
                g_cChaserLoc.Y -= 1;
                Beep(1440, 30);
            } // up
            if (charLocation.X < g_cChaserLoc.X){
                g_cChaserLoc.X -= 1;
                Beep(1440, 30);
            } // left
            if (charLocation.X > g_cChaserLoc.X){
                g_cChaserLoc.X += 1;
                Beep(1440, 30);
            } // right
            if (charLocation.Y > g_cChaserLoc.Y){
                g_cChaserLoc.Y += 1;
                Beep(1440, 30);
            } // down
            monsterdelay = 0; // resets delay after making a move
        }
    }
}

//---------------------//
// Moves the 2nd ghost //
//---------------------//

void moveMonster1(){
    // CHASER MOVEMENT
    if (Monster == STARTGAME){
        monster1delay++; //change gamestate so that the monster can move, and with a delay
        if (monster1delay == 5){
            if (charLocation.Y < g_cChaser1Loc.Y){
                g_cChaser1Loc.Y -= 1;
                Beep(1440, 30);
            } // up
            if (charLocation.X < g_cChaser1Loc.X){
                g_cChaser1Loc.X -= 1;
                Beep(1440, 30);
            } // left
            if (charLocation.X > g_cChaser1Loc.X){
                g_cChaser1Loc.X += 1;
                Beep(1440, 30);
            } // right
            if (charLocation.Y > g_cChaser1Loc.Y){
                g_cChaser1Loc.Y += 1;
                Beep(1440, 30);
            } // down
            monster1delay = 0; // resets delay after making a move
        }
    }
}

//------------------------------//
// Check if 1st ghost gets shot //
//------------------------------//

void projKill(){
    if (g_cChaserLoc.X == g_cProjectile.X && g_cChaserLoc.Y == g_cProjectile.Y){
        monsterDeath(); // monster dies after getting hit by projectile
    }
}

//------------------------------//
// check if 2nd ghost gets shot //
//------------------------------//

void projKill1(){
    if (g_cChaser1Loc.X == g_cProjectile.X && g_cChaser1Loc.Y == g_cProjectile.Y){
        monster1Death(); // monster dies after getting hit by projectile
    }
}


//-------------------//
// 1st ghost death //
//-----------------//

void monsterDeath(){
    monsterToken = 0;
    t_monsterDied = elapsedTime + 3;
    spawnToken = 1;
    int spawnLocation = rand() % 3; // Spawns the monster randomly between 3 different spawn locations
    g_cChaserLoc.X = 26;
    if (spawnLocation == 0){
        g_cChaserLoc.Y = 2; // location 1
    }
    else if (spawnLocation == 1){
        g_cChaserLoc.Y = 13; // location 2
    }
    else{
        g_cChaserLoc.Y = 24; // location 3
    }
}

//-----------------//
// 2nd ghost death //
//-----------------//

void monster1Death(){
    monster1Token = 0;
    t_monster1Died = elapsedTime + 3;
    spawn1Token = 1;
    int spawnLocation = rand() % 3; // Spawns the monster randomly between 3 different spawn locations
    g_cChaser1Loc.X = 26;
    if (spawnLocation == 0){
        g_cChaser1Loc.Y = 13; // location 1
    }
    else if (spawnLocation == 1){
        g_cChaser1Loc.Y = 24; // location 2
    }
    else{
        g_cChaser1Loc.Y = 2; // location 3
    }
}

//------------------------------------------------//
// 1st ghost collision check & damage calculation //
//------------------------------------------------//

void collision(){
    if (charLocation.X == g_cChaserLoc.X && charLocation.Y == g_cChaserLoc.Y){
        monsterDeath(); // Monster dies after damaging player
        if (iToken == 0){
            player.health -= 1; // reduces player health by 1
            iToken += 1;
            t_invincibility = elapsedTime + 0.5; // allows player to have invicibility for 0.5 sec after being damaged
        }
    }
}

//------------------------------------------------//
// 2nd ghost collision check & damage calculation //
//------------------------------------------------//

void collision1(){
    if (charLocation.X == g_cChaser1Loc.X && charLocation.Y == g_cChaser1Loc.Y){
        monster1Death(); // Monster dies after damaging player
        if (iToken == 0){
            player.health -= 1; // reduces player health by 1
            iToken += 1;
            t_invincibility = elapsedTime + 0.5; // allows player to have invicibility for 0.5 sec after being damaged
        }
    }

}

//--------------------------------------------------//
// Super ghost collision check & damage calculation //
//--------------------------------------------------//

void monsterDamage(){
    if (charLocation.X == g_cChaser1Loc.X && charLocation.Y == g_cChaser1Loc.Y && charLocation.X == g_cChaserLoc.X && charLocation.Y == g_cChaserLoc.Y){
        if (monsterToken == 1){
            if (iToken == 0){
                player.health -= 2;
                iToken += 1;
                t_invincibility = elapsedTime + 0.5;
            }
        }
        monsterDeath();
        monster1Death();
    }
    else{
        if (monsterToken == 1){
            collision();
        }
        if (monster1Token == 1){
            collision1();
        }
    }
}

//-----------------//
// Spawn 1st ghost //
//-----------------//

void spawnMonster(){
    if (elapsedTime > t_monsterDied){
        if (spawnToken == 1){
            monsterToken = 1;
            spawnToken = 0;
        }
    }
}

//-----------------//
// Spawn 2nd ghost //
//-----------------//

void spawnMonster1(){
    if (elapsedTime > t_monster1Died) {
        if (spawn1Token == 1){
            monster1Token = 1;
            spawn1Token = 0;
        }
    }
}