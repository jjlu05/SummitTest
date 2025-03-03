#include "GameManager.h"
#include <iostream>
#include "LogManager.h"
#include "Clock.h"
#include "Windows.h"
#include "WorldManager.h"
#include "Object.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "InputManager.h"
namespace df {
    GameManager::GameManager() : game_over(false), frame_time(FRAME_TIME_DEFAULT), n(0) {
        setType("GameManager");
    }

    GameManager& GameManager::getInstance() {
        static GameManager instance;
        return instance;
    }

    // Startup all GameManager services.
    int GameManager::startUp() {



        LM.startUp();
        if (timeBeginPeriod(1) != TIMERR_NOERROR) {
            return -1;
        }
        DM.startUp();
        IM.startUp();
        WM.startUp();

     /*   WM.setBoundary(Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical()));
        WM.setView(Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical()));*/

        return 0;
    }

    // Shut down GameManager services.
    void GameManager::shutDown() {
        WM.shutDown();
        LM.shutDown();
        game_over = true;
        timeEndPeriod(1);
    }

    // Run game loop.
    void GameManager::run() {
        Clock clock;
        
        int l = 0;
        while (!game_over) {
            clock.delta();
            n++;
          

            //get a list of all objects from WorldManager
            //ObjectList all_objects = WM.getAllObjects();

            ////create Step Event
            //EventStep s(n);

            //for (int i = 0; i<all_objects.getCount(); i++) {
            //    all_objects[i]->eventHandler(&s);
            //}

            //WM.update();
            //
            EventStep s;
            onEvent(&s);
            IM.getInput();
            //sleep based on the frame time
            /*long int loop_time = clock.split()/1000;
            std::cout << frame_time - loop_time;
            Sleep(frame_time-loop_time);
            */
            //Get input // e . g . , keyb o a r d /mouse
            WM.update();
            WM.draw();
            DM.swapBuffers();
            int loop_time = clock.split() / 1000;
    
            int sleep_time = frame_time - loop_time;
            if (sleep_time < 0)
                sleep_time = 0;
            Sleep(sleep_time);



        }
    }

    // Set game over status to indicated value.
    void GameManager::setGameOver(bool new_game_over) {
        game_over = new_game_over;
    }

    // Get game over status.
    bool GameManager::getGameOver() const {
        return game_over;
    }

    // Return frame time.
    int GameManager::getFrameTime() const {
        return frame_time;
    }

    int GameManager::getTest() {
        return n;
    }

}