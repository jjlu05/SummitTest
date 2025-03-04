//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
//// Game includes.
#include "GameStart.h"
#include "Star.h"

// Function prototypes.
void loadResources(void);
void populateWorld(void);

int main(int argc, char* argv[]) {
    df::Vector corner(0, 0);
    df::Box world_boundary(corner, 160, 160);
    WM.setBoundary(world_boundary);
 


    // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 0;
    }

    // Set flush of logfile during development (when done, make false).
    LM.setFlush(true);

    // Load game resources.
    loadResources();

    // Populate game world with some objects.
    populateWorld();

    // Run game (this blocks until game loop is over).
    GM.run();

    // Shut everything down.
    GM.shutDown();
}

// Load resources (sprites, sound effects, music).
void loadResources(void) {
    RM.loadSprite("ledge.txt", "ledge");
    RM.loadSprite("wall.txt", "wall");
    RM.loadSprite("saucer-spr.txt", "saucer");
    RM.loadSprite("bat.txt", "bat");
    RM.loadSprite("ground.txt", "ground");
    RM.loadSprite("hero.txt", "hero");
    RM.loadSprite("bullet-spr.txt", "bullet");
    RM.loadSprite("explosion-spr.txt", "explosion");
    RM.loadSprite("gamestart-spr.txt", "gamestart");
    RM.loadSprite("gameover-spr.txt", "gameover");
    RM.loadSound("fire.wav", "fire");
    RM.loadSound("explode.wav", "explode");
    RM.loadSound("nuke.wav", "nuke");
    RM.loadSound("game-over.wav", "game over");
    RM.loadMusic("start-music.wav", "start music");
}

// Populate world with some objects.
void populateWorld(void) {

    // Spawn some Stars.
    for (int i = 0; i < 16; i++)
        new Star;

    // Create GameStart object.
    GameStart *test = new GameStart();
   
    
}
























