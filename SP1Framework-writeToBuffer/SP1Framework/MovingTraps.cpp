#include "game.h"

extern int healthDMG;
extern COORD	guarda;
extern COORD	guardb;
extern COORD	guardc;
extern COORD	guardd;
extern COORD	guarde;
extern MONSTERSTATE Monster;
extern MAPSTATE level;
extern COORD charLocation;
extern double elapsedTime;
extern double t_invincibility;
extern int iToken;

struct Stats {
    short health;
    short ammo;
    short bomb;
};
extern Stats player;
int monsterdelaya = 0;
int monsterdelayb = 0;
int monsterdelayc = 0;
int monsterdelayd = 0;
int monsterdelaye = 0;
int gdirectiona = 0;
int gdirectionb = 0;
int gdirectionc = 0;
int gdirectiond = 0;
int gdirectione = 0;


/* respawning of guards
Done by Sean, 21 Aug 2015
Checks if Guards are on the same location as player
if true, player takes 1 damage and becomes invulnerable for 0.5 seconds
Updated on 26 Aug 2015 - Added invulnerablity for 0.5 seconds
*/

// guard a death
void guardadeath(){
    guarda.X = 4;
    guarda.Y = 13;
}
// guard b death
void guardbdeath(){
    guardb.X = 14;
    guardb.Y = 13;
}
//guard c death
void guardcdeath(){
    guardc.X = 23;
    guardc.Y = 13;
}
// guard d death
void guardddeath(){
    guardd.X = 31;
    guardd.Y = 13;
}
// guard e death
void guardedeath(){
    guarde.X = 40;
    guarde.Y = 13;
}

/* Check if guards get damaged
Done by Sean, 21 Aug 2015
Checks if Guards are on the same location as player
if true, player takes 1 damage and becomes invulnerable for 0.5 seconds
Updated on 26 Aug 2015 - Added invulnerablity for 0.5 seconds
*/

void collisiona(){
    if (charLocation.X == guarda.X && charLocation.Y == guarda.Y){
        guardadeath();
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
        healthDMG++;
    }
}

//guard b (trap) collision
void collisionb(){
    if (charLocation.X == guardb.X && charLocation.Y == guardb.Y){
        guardbdeath();
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
        healthDMG++;
    }
}

//guard c (trap) collision
void collisionc(){
    if (charLocation.X == guardc.X && charLocation.Y == guardc.Y){
        guardcdeath();
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
        healthDMG++;
    }
}

//guard d (trap) collision
void collisiond(){
    if (charLocation.X == guardd.X && charLocation.Y == guardd.Y){
        guardddeath();
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
        healthDMG++;
    }
}

//guard e (trap) collision
void collisione(){
    if (charLocation.X == guarde.X && charLocation.Y == guarde.Y){
        guardedeath();
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
        healthDMG++;
    }
}

/* moving of guards
Done by Sean, 21 Aug 2015
Checks if Guards are on the same location as player
if true, player takes 1 damage and becomes invulnerable for 0.5 seconds
Updated on 26 Aug 2015 - Added invulnerablity for 0.5 seconds
*/

//guard a movement
void guardamovement(){
    if (Monster == STARTGAME){
        if (level == LIBRARYROOM)
        {
            monsterdelaya++; 
            {
                if (monsterdelaya == 8){
                    if (gdirectiona == 0)
                    {
                        if (guarda.Y < 24)
                        {
                            guarda.Y += 1;
                        }
                        else
                        {
                            gdirectiona = 1;
                        }
                    }

                    if (gdirectiona == 1)
                    {
                        if (guarda.Y > 2)
                        {
                            guarda.Y -= 1;
                        }
                        else
                        {
                            gdirectiona = 0;
                        }
                    }
                    monsterdelaya = 0;
                }
                collisiona();
            }
        }
    }
}

//guard b movement
void guardbmovement(){
    if (Monster == STARTGAME){
        if (level == RIVERROOM){
            monsterdelayb++;
            if (monsterdelayb == 8){
                if (gdirectionb == 0)
                {
                    if (guardb.Y < 24)
                    {
                        guardb.Y += 1;
                    }
                    else
                    {
                        gdirectionb = 1;
                    }
                }

                if (gdirectionb == 1)
                {
                    if (guardb.Y > 2)
                    {
                        guardb.Y -= 1;
                    }
                    else
                    {
                        gdirectionb = 0;
                    }
                }
                monsterdelayb = 0;
            }
            collisionb();
        }
    }
}

//guard c movement
void guardcmovement(){
    if (Monster == STARTGAME){
        if (level == THEHROOM){
            monsterdelayc++;
            if (monsterdelayc == 8){
                if (gdirectionc == 0)
                {
                    if (guardc.Y < 24)
                    {
                        guardc.Y += 1;
                    }
                    else
                    {
                        gdirectionc = 1;
                    }
                }

                if (gdirectionc == 1)
                {
                    if (guardc.Y > 2)
                    {
                        guardc.Y -= 1;
                    }
                    else
                    {
                        gdirectionc = 0;
                    }
                }
                monsterdelayc = 0;
            }
            collisionc();
        }
    }
}

//guard d movement
void guarddmovement(){
        if (level == MERRYGRROOM)
        {
            monsterdelayd++;
            if (monsterdelayd == 8){
                if (gdirectiond == 0)
                {
                    if (guardd.Y < 24)
                    {
                        guardd.Y += 1;
                    }
                    else
                    {
                        gdirectiond = 1;
                    }
                }

                if (gdirectiond == 1)
                {
                    if (guardd.Y > 2)
                    {
                        guardd.Y -= 1;
                    }
                    else
                    {
                        gdirectiond = 0;
                    }
                }
                monsterdelayd = 0;
            }
            collisiond();
        }
}

//guard e movement
void guardemovement(){
    if (Monster == STARTGAME){
        if (level == LECTUREHALLROOM)
        {
            monsterdelaye++;
            if (monsterdelaye == 8){
                if (gdirectione == 0)
                {
                    if (guarde.Y < 24)
                    {
                        guarde.Y += 1;
                    }
                    else
                    {
                        gdirectione = 1;
                    }
                }

                if (gdirectione == 1)
                {
                    if (guarde.Y > 2)
                    {
                        guarde.Y -= 1;
                    }
                    else
                    {
                        gdirectione = 0;
                    }
                }
                monsterdelaye = 0;
            }
            collisione();
        }
    }
}


//collision of moving traps in different maps
void guardCollision(){
    if (level == LIBRARYROOM){
         collisiona();
    }
    else if (level == RIVERROOM){
        collisionb();
    }
    else if (level == THEHROOM){
        collisionc();
    }
    if (level == MERRYGRROOM){
        collisiond();
    }
    if (level == LECTUREHALLROOM)
    {
        collisione();
    }
}

//moving trap function
void guardMovement(){   
    guardamovement();  
    guardbmovement(); 
    guardcmovement(); 
    guarddmovement();
    guardemovement();
    guardCollision();
}
