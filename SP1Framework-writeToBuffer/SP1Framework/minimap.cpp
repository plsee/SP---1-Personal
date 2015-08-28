#include "game.h"
#include "Framework\console.h"

extern Console console;
extern MAPSTATE level;

//---------//
// minimap //
//---------//
void minimap() {
COORD c;
#define MINIMAP_WIDTH 22
#define MINIMAP_HEIGHT 10

    for (int i = 0; i < MINIMAP_HEIGHT; i++) {
        c.Y = i;
        console.writeToBuffer(c, '#');
        for (int j = 0; j < MINIMAP_WIDTH; j++) {
            c.X = console.getConsoleSize().X + j - 22;
            console.writeToBuffer(c, ' ');
        }
    }

    for (int k = 0; k < MINIMAP_WIDTH; k++) {
        for (int i = 0; i < 3; i++){
            c.X = console.getConsoleSize().X + k - 22;
            console.writeToBuffer(c, '_');
        }
    }

    //Tutorial
    if (level == TUTORIALROOM) {
        c.X = 55;
        c.Y = 4;
        console.writeToBuffer(c, (char)234, 0x0A);
    }
    else {
        c.X = 55;
        c.Y = 4;
        console.writeToBuffer(c, (char)234);
    }

    //connect Tutorial - A
    for (int i = 0; i < 3; i++) {
        c.X = 56 + i;
        c.Y = 4;
        console.writeToBuffer(c, (char)196);
    }

    //A
    if (level == RIVERROOM) {
        c.X = 59;
        c.Y = 4;
        console.writeToBuffer(c, "A", 0x0A);
    }
    else {
        c.X = 59;
        c.Y = 4;
        console.writeToBuffer(c, "A");
    }

    //connect A - B
    for (int i = 0; i < 3; i++) {
        c.X = 60 + i;
        c.Y = 4;
        console.writeToBuffer(c, (char)196);
    }

    //connect A - C
    for (int i = 0; i < 2; i++) {
        c.X = 59;
        c.Y = 5 + i;
        console.writeToBuffer(c, (char)179);
    }

    //B
    if (level == LECTUREHALLROOM) {
        c.X = 63;
        c.Y = 4;
        console.writeToBuffer(c, "B", 0x0A);
    }
    else {
        c.X = 63;
        c.Y = 4;
        console.writeToBuffer(c, "B");
    }

    //connect B - C
    for (int i = 0; i < 2; i++) {
        c.X = 62 - i;
        c.Y = 5 + i;
        console.writeToBuffer(c, (char)47);
    }

    //connect B - E
    for (int i = 0; i < 2; i++) {
        c.X = 63;
        c.Y = 2 + i;
        console.writeToBuffer(c, (char)179);
    }

    //C
    if (level == LIBRARYROOM) {
        c.X = 59;
        c.Y = 7;
        console.writeToBuffer(c, "C", 0x0A);
    }
    else {
        c.X = 59;
        c.Y = 7;
        console.writeToBuffer(c, "C");
    }

    //connect C - D
    for (int i = 0; i < 3; i++) {
        c.X = 60 + i;
        c.Y = 7;
        console.writeToBuffer(c, (char)196);
    }

    //D
    if (level == MERRYGRROOM) {
        c.X = 63;
        c.Y = 7;
        console.writeToBuffer(c, "D", 0x0A);
    }
    else {
        c.X = 63;
        c.Y = 7;
        console.writeToBuffer(c, "D");
    }

    //E
    if (level == THEHROOM) {
        c.X = 63;
        c.Y = 1;
        console.writeToBuffer(c, "E", 0x0A);
    }
    else {
        c.X = 63;
        c.Y = 1;
        console.writeToBuffer(c, "E");
    }

    //connect E <-> D
    for (int i = 0; i < 2; i++) {
        c.X = 64 + i;
        c.Y = 1;
        console.writeToBuffer(c, (char)196);
    }
    c.X = 66;
    c.Y = 1;
    console.writeToBuffer(c, (char)194);
    for (int i = 0; i < 5; i++) {
        c.X = 66;
        c.Y = 2 + i;
        console.writeToBuffer(c, (char)179);
    }
    c.X = 66;
    c.Y = 7;
    console.writeToBuffer(c, (char)193);
    for (int i = 0; i < 2; i++) {
        c.X = 64 + i;
        c.Y = 7;
        console.writeToBuffer(c, (char)196);
    }

    //connect E & D - Boss
    for (int i = 0; i < 3; i++) {
        c.X = 67 + i;
        c.Y = 1;
        console.writeToBuffer(c, (char)196);
    }
    c.X = 70;
    c.Y = 1;
    console.writeToBuffer(c, (char)191);
    for (int i = 0; i < 5; i++) {
        c.X = 70;
        c.Y = 2 + i;
        console.writeToBuffer(c, (char)179);
    }
    c.X = 70;
    c.Y = 7;
    console.writeToBuffer(c, (char)217);
    for (int i = 0; i < 3; i++) {
        c.X = 67 + i;
        c.Y = 7;
        console.writeToBuffer(c, (char)196);
    }

    //Boss
    if (level == BOSSROOM) {
        c.X = 70;
        c.Y = 4;
        console.writeToBuffer(c, (char)234, 0x0A);
    }
    else {
        c.X = 70;
        c.Y = 4;
        console.writeToBuffer(c, (char)234);
    }
}