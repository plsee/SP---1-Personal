#include "game.h"
#include "Map.h"
#include "Framework\console.h"
/*
Boss projectiles coordinates for all 8 directions
*/
COORD   Bprojectile1;
COORD   Bprojectile2;
COORD	Bprojectile3;
COORD	Bprojectile4;
COORD	Bprojectile5;
COORD	Bprojectile6;
COORD	Bprojectile7;
COORD	Bprojectile8;
/* Game State for Boss*/
BOSS fight = NORMAL;
int iToken = 0;
int BAdelay1 = 0; // for btm right
int RandAtk1; // random atk 
int BAdelay2 = 0; // for btm left
int RandAtk2;
int BAdelay3 = 0; //for top right
int RandAtk3;
int BAdelay4 = 0; // for top left
int RandAtk4;
int BAdelay5 = 0; // for top
int RandAtk5;
int BAdelay6 = 0; // for right
int RandAtk6;
int BAdelay7 = 0; //for down
int RandAtk7;
int BAdelay8 = 0; //for left
int RandAtk8;
int seed;
extern int healthDMG;
extern char printMap[MAP_HEIGHT][MAP_WIDTH];
extern char BossMap[MAP_HEIGHT][MAP_WIDTH];
extern double elapsedTime;
extern double bossFightTime;
extern double t_invincibility;
extern Console console;
extern COORD charLocation;
extern MAPSTATE level;

struct Stats {
    short health;
    short ammo;
    short bomb;
};
extern Stats player;

/*
Boss attack
Done by Cher Yi, modified by Ashley, 26 Aug 2015
Function for boss to attack in each direction
Arguments - When boss delay == random attack
Updates
26 Aug 2015 - Ashley updated the projectile randomness and delay
*/

//-----------------------//
// Boss projectile speed //
//-----------------------//

void bossSpeed(){
    seed = rand(); // seeding
    srand(seed);
    // random atk 
    //btm right
    RandAtk1 = rand() % 4 + 1; 
    //btm left
    RandAtk2 = rand() % 4 + 1;
    //top right
    RandAtk3 = rand() % 4 + 1;
    //top left
    RandAtk4 = rand() % 4 + 1;
    //top
    RandAtk5 = rand() % 2 + 1;
    //right
    RandAtk6 = rand() % 2 + 1;
    //down
    RandAtk7 = rand() % 2 + 1;
    //left
    RandAtk8 = rand() % 2 + 1;
    BAdelay1 = 0;
    BAdelay2 = 0;
    BAdelay3 = 0;
    BAdelay4 = 0;
    BAdelay5 = 0;
    BAdelay6 = 0;
    BAdelay7 = 0;
    BAdelay8 = 0;
}

//-----------------//
// Boss projectile //
//-----------------//

void BossAttack(){
    //btm right
    console.writeToBuffer(Bprojectile1, (char)30, 0x0B);
    if (BAdelay1 == RandAtk1){
        if (printMap[Bprojectile1.Y][Bprojectile1.X] == 1){
            Bprojectile1.X = 26;
            Bprojectile1.Y = 13;
        }
        else{
            Bprojectile1.X += 2;
            Bprojectile1.Y += 1;
        }
        BAdelay1 = 0;
    }
    //btm left
    console.writeToBuffer(Bprojectile2, (char)30, 0x0B);
    if (BAdelay2 == RandAtk2){
        if (printMap[Bprojectile2.Y][Bprojectile2.X] == 1){
            Bprojectile2.X = 26;
            Bprojectile2.Y = 13;
        }
        else{
            Bprojectile2.X -= 2;
            Bprojectile2.Y += 1;
        }
        BAdelay2 = 0;
    }
    //top right
    console.writeToBuffer(Bprojectile3, (char)30, 0x0B);
    if (BAdelay3 == RandAtk3){
        if (printMap[Bprojectile3.Y][Bprojectile3.X] == 1){
            Bprojectile3.X = 26;
            Bprojectile3.Y = 13;
        }
        else{
            Bprojectile3.X += 2;
            Bprojectile3.Y -= 1;
        }
        BAdelay3 = 0;
    }
    // top left
    console.writeToBuffer(Bprojectile4, (char)30, 0x0B);
    if (BAdelay4 == RandAtk4){
        if (printMap[Bprojectile4.Y][Bprojectile4.X] == 1){
            Bprojectile4.X = 26;
            Bprojectile4.Y = 13;
        }
        else{
            Bprojectile4.X -= 2;
            Bprojectile4.Y -= 1;
        }
        BAdelay4 = 0;
    }
    //top
    console.writeToBuffer(Bprojectile5, (char)30, 0x0B);
    if (BAdelay5 == RandAtk5){
        if (printMap[Bprojectile5.Y][Bprojectile5.X] == 1){
            Bprojectile5.X = 26;
            Bprojectile5.Y = 13;
        }
        else{
            Bprojectile5.Y -= 1;
        }
        BAdelay5 = 0;
    }
    // right
    console.writeToBuffer(Bprojectile6, (char)30, 0x0B);
    if (BAdelay6 == RandAtk6){
        if (printMap[Bprojectile6.Y][Bprojectile6.X] == 1){
            Bprojectile6.X = 26;
            Bprojectile6.Y = 13;
        }
        else{
            Bprojectile6.X += 1;

        }
        BAdelay6 = 0;
    }
    // down
    console.writeToBuffer(Bprojectile7, (char)30, 0x0B);
    if (BAdelay7 == RandAtk7){
        if (printMap[Bprojectile7.Y][Bprojectile7.X] == 1){
            Bprojectile7.X = 26;
            Bprojectile7.Y = 13;
        }
        else{
            Bprojectile7.Y += 1;
        }
        BAdelay7 = 0;
    }
    //left
    console.writeToBuffer(Bprojectile8, (char)30, 0x0B);
    if (BAdelay8 == RandAtk8){
        if (printMap[Bprojectile8.Y][Bprojectile8.X] == 1){
            Bprojectile8.X = 26;
            Bprojectile8.Y = 13;
        }
        else{
            Bprojectile8.X -= 1;
        }
        BAdelay8 = 0;
    }
    BAdelay1++;
    BAdelay2++;
    BAdelay3++;
    BAdelay4++;
    BAdelay5++;
    BAdelay6++;
    BAdelay7++;
    BAdelay8++;
    Getdamagedbyboss();     // Damage by boss
}

/* Damage Check for boss
Done by Cher Yi 26 Aug 2015
Check if character location == projectile location
if its true,  player health - 1 and gives player invincibility for 0.5seconds
*/

//-------------------//
// Boss damage check //
//-------------------//

void Getdamagedbyboss(){
    if (charLocation.X == Bprojectile1.X && charLocation.Y == Bprojectile1.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
        healthDMG++;
    }
    else if (charLocation.X == Bprojectile2.X && charLocation.Y == Bprojectile2.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
        healthDMG++;
    }
    else if (charLocation.X == Bprojectile3.X && charLocation.Y == Bprojectile3.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
        healthDMG++;
    }
    else if (charLocation.X == Bprojectile4.X && charLocation.Y == Bprojectile4.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
        healthDMG++;
    }
    else if (charLocation.X == Bprojectile5.X && charLocation.Y == Bprojectile5.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
        healthDMG++;
    }
    else if (charLocation.X == Bprojectile6.X && charLocation.Y == Bprojectile6.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
        healthDMG++;
    }
    else if (charLocation.X == Bprojectile7.X && charLocation.Y == Bprojectile7.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
        healthDMG++;
    }
    else if (charLocation.X == Bprojectile8.X && charLocation.Y == Bprojectile8.Y){
        if (iToken == 0){
            player.health -= 1;
            iToken += 1;
            t_invincibility = elapsedTime + 0.5;
        }
        healthDMG++;
    }

}

/* Boss projectile location
Done by Cher Yi 26 Aug 2015
if gamestate = BATTLE
Boss and projectile will spawn
*/

//------------------------------//
// Boss & Boss projectile spawn //
//------------------------------//

void BossFight(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            printMap[i][j] = BossMap[i][j];
        }
    }
    setmonsterlocation();
    fight = BATTLE;
    //Boss Projectile
    Bprojectile1.X = 26;
    Bprojectile1.Y = 13;
    Bprojectile2.X = 26;
    Bprojectile2.Y = 13;
    Bprojectile3.X = 26;
    Bprojectile3.Y = 13;
    Bprojectile4.X = 26;
    Bprojectile4.Y = 13;
    Bprojectile5.X = 26;
    Bprojectile5.Y = 13;
    Bprojectile6.X = 26;
    Bprojectile6.Y = 13;
    Bprojectile7.X = 26;
    Bprojectile7.Y = 13;
    Bprojectile8.X = 26;
    Bprojectile8.Y = 13;
    level = BOSSROOM;

}