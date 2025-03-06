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
    df::Box world_boundary(corner, 160, 100);
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
    RM.loadSprite("skeleton.txt", "skeleton");
    RM.loadSprite("mole-right.txt", "mole-right");
    RM.loadSprite("background.txt", "background");
    RM.loadSprite("hero-extend.txt", "hero-extend");


    
    RM.loadSprite("win.txt", "win1");

    RM.loadSprite("mole.txt", "mole");
    RM.loadSprite("arrow.txt", "arrow");
    RM.loadSprite("hero-crouch.txt", "hero-crouch");
    RM.loadSprite("hero-squat.txt", "hero-squat");
    RM.loadSprite("bar.txt", "bar");
    RM.loadSprite("barPower.txt", "barPower");
    RM.loadSprite("checkpoint.txt", "checkpoint");
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
    RM.loadSound("jump-sound.wav", "jump");
    RM.loadSound("footsteps.wav", "footsteps");



    RM.loadSound("chargeUp.wav", "chargeUp");
    RM.loadSound("win.wav", "win");
    RM.loadSound("fall.wav", "fall");
    RM.loadSound("game-over.wav", "game over");
    RM.loadSound("scream.wav", "scream");
    RM.loadSound("boom.wav", "boom");



    RM.loadMusic("wind.wav", "wind");
    RM.loadMusic("start-music.wav", "start music");
    RM.loadMusic("In-game-music.wav", "igm");
    RM.loadMusic("menu-music.wav", "menu");


}

// Populate world with some objects.
void populateWorld(void) {

  

    // Create GameStart object.
    GameStart *test = new GameStart();
   
    
}
























