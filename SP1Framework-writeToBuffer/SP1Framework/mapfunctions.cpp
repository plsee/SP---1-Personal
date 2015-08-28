#include "Map.h"
#include "game.h"

extern MAPSTATE level;
extern char printMap[MAP_HEIGHT][MAP_WIDTH];
extern MONSTERSTATE Monster;
extern char River[MAP_HEIGHT][MAP_WIDTH];
extern char LectureHall[MAP_HEIGHT][MAP_WIDTH];
extern char library[MAP_HEIGHT][MAP_WIDTH];
extern char MerryGR[MAP_HEIGHT][MAP_WIDTH];
extern char TheH[MAP_HEIGHT][MAP_WIDTH];
extern char Tutorial[MAP_HEIGHT][MAP_WIDTH];

//-----------------//
// Renders Library //
//-----------------//

void mapLibrary(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            printMap[i][j] = library[i][j];
        }
    }
    setmonsterlocation();
    level = LIBRARYROOM;
}

//----------------------//
// Renders Lecture Hall //
//----------------------//

void mapLectureHall(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            printMap[i][j] = LectureHall[i][j];
        }
    }
    setmonsterlocation();
    level = LECTUREHALLROOM;
}

//---------------//
// Renders River //
//---------------//

void mapRiver(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            printMap[i][j] = River[i][j];
        }
    }
    setmonsterlocation();
    level = RIVERROOM;
}

//-----------------//
// Renders MerryGR //
//-----------------//

void mapMerryGR(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            printMap[i][j] = MerryGR[i][j];
        }
    }
    setmonsterlocation();
    level = MERRYGRROOM;
}

//--------------//
// Renders TheH //
//--------------//

void mapTheH(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            printMap[i][j] = TheH[i][j];
        }
    }
    setmonsterlocation();
    level = THEHROOM;
}

//-------------------//
// Restarts the game //
//-------------------//
void tutorial(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            printMap[i][j] = Tutorial[i][j];
        }
    }
    setmonsterlocation();
    Monster = TUTORIAL;
    level = TUTORIALROOM;
}