#include "Object.h"
#include "ObjectList.h"
#include "LogManager.h"
#include "Clock.h"
#include <cassert>
#include <cstdio>
#include "GameManager.h"
#include <Windows.h>   
#pragma comment(lib, "Winmm.lib")
#include <thread>
#include "Saucer.h"
#include "WorldManager.h"
#include <iostream>
#include "EventStep.h"
#include "DisplayManager.h"
#include <SFML/Graphics.hpp >
#include "GameManager.h"
#include "InputManager.h"
#include "EventMouse.h"
#include "EventKeyboard.h"
#include "Hero.h"
#include "utility.h"
//#include "Sprite.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "Sound.h"
#include "Music.h"
#include "ViewObject.h"
#include "EventView.h"
bool testLog();
bool testClock();
bool testGameManagerRunTime();
bool testObjectList();   
bool testS();
bool testInsert();
bool testVector();
bool testObject();
bool testEventStep();
bool testObjectConDestr();
bool testGameManagerRun();
bool testVector1();
bool testGameManagerClock();



//Project 2b
bool testDisplayStart();
bool testDrawStr();
bool  testCustomGameObjectDraw();
bool testAltitude();
bool testIMStart();
bool testEventsMK();
bool testGetInput();
bool testInputMovesObjects();
bool testVelocity();
bool testCollisions1();
bool testCollisionsSoft();
bool testBorders();
bool testEverything();
bool testingDM();



bool testFrameDraw();
bool testFrame();
bool testSprite();
bool testGetFrame();
bool testSpriteDraw();
bool testResourceManager1();
bool testAnimationDraw();
bool testAnimationDrawSkip();
bool testBox();
bool testObjectBox();

bool testBoxIntersectsBox();
bool testSpriteCollisions();
bool testAniView();
void pri();
bool testViewBounds();
bool testSound();
bool testMusic();
bool testDrawViewObj();
bool testViewObject();
int main(int argc, char* argv[]) {
    //testEverything();
    //testingDM();
    //Project 2b tests
    //testCollisionsSoft();
    //testBorders();
    //testCollisions1();
    //testVelocity();

    /*if (testEventsMK())
        puts("Pass");
    else
        puts("Fail");*/
    //testAltitude();
    //testCustomGameObjectDraw();
    //testDrawStr();
    //testDisplayStart();
    //testFrame();
    //Sleep(500);
    //testFrameDraw();
    //Sleep(500);
    //testSprite();
    //Sleep(500);
    //testGetFrame();
    //testSpriteDraw();
    //testResourceManager1();
    //testAnimationDraw();
    //testAnimationDrawSkip();
    //testBox();
    //testObjectBox();
    //testBoxIntersectsBox();
    //testSpriteCollisions();
    //pri();
    //testAniView();
    //testViewBounds();

    //testSound();
    //testMusic();
    //testDrawViewObj();
    testViewObject();








    // Project 2a Tests Below
    // 
    // 
    // 
    // 
   // if (testLog())
   //     puts("Pass");
   // else
   //     puts("Fail");

   // if (testClock())
   //     puts("Pass");
   // else
   //     puts("Fail");

   // if (testGameManagerRun())
   //     puts("Pass");
   // else
   //     puts("Fail");
   ///* if (testGameManagerRunTime())
   //     puts("Pass");
   // else
   //     puts("Fail");*/

   // if (testObjectList())
   //     puts("Pass");
   // else
   //     puts("Fail");

   // if (testS())
   //     puts("Pass");
   // else
   //     puts("Fail");

   // if (testInsert())
   //     puts("Pass");
   // else
   //     puts("Fail");

   // if (testVector())
   //     puts("Pass");
   // else
   //     puts("Fail");

   // if (testObject())
   //     puts("Pass");
   // else
   //     puts("Fail");

   // /*if (testEventStep())
   //     puts("Pass");
   // else
   //     puts("Fail");*/
   // if (testGameManagerClock())
   //     puts("Pass");
   // else
   //     puts("Fail");
   // if (testObjectConDestr())
   //     puts("Pass");
   // else
   //     puts("Fail");


   // if (testVector1())
   //     puts("Pass");
   // else
   //     puts("Fail");

    return 0;
}
bool testViewObject() {
    // Create a ViewObject for tracking "Points"
    df::ViewObject* p_vo = new df::ViewObject;
    p_vo->setViewString("Points");  // Label it "Points"
    p_vo->setValue(0);              // Initial value = 0
    p_vo->setLocation(TOP_RIGHT);
    p_vo->setColor(df::YELLOW);

    // Create a ViewObject for tracking "Health" (to verify event filtering)
    df::ViewObject* p_health_vo = new df::ViewObject;
    p_health_vo->setViewString("Health");
    p_health_vo->setValue(100);
    p_health_vo->setLocation(TOP_LEFT);
    p_health_vo->setColor(df::RED);

    // Create events to modify the value
    df::EventView ev1("Points", 10, true);  // Increase points by 10
    df::EventView ev2("Points", 5, true);   // Increase points by 5
    df::EventView ev3("Health", -20, true); // Decrease health by 20
    df::EventView ev4("Unknown", 50, true); // Should be ignored

    // Send the events to WorldManager (which will dispatch them)
    WM.onEvent(&ev1);
    WM.onEvent(&ev2);
    WM.onEvent(&ev3);
    WM.onEvent(&ev4);

    // Check if the values were updated correctly
    if (p_vo->getValue() != 15) {
        std::cout << "Test Failed: ViewObject 'Points' value incorrect." << std::endl;
        return false;
    }
    if (p_health_vo->getValue() != 80) {
        std::cout << "Test Failed: ViewObject 'Health' value incorrect." << std::endl;
        return false;
    }

    std::cout << "Test Passed: ViewObject correctly handled events!" << std::endl;
    return true;
}
bool testDrawViewObj() {
    // Create a ViewObject dynamically
    df::ViewObject* vo = new df::ViewObject();

    // Set arbitrary values for testing
    vo->setViewString("Score");
    vo->setValue(100);
    vo->setColor(df::BLUE);
    vo->setBorder(true);

    // Test fixed locations
    df::Vector test_positions[] = {
        df::Vector(5, 5),   // Top-left
        df::Vector(50, 5),  // Top-center
        df::Vector(95, 5),  // Top-right
        df::Vector(5, 50),  // Middle-left
        df::Vector(50, 50), // Middle-center
        df::Vector(95, 50)  // Middle-right
    };

    bool test_passed = true;

    for (int i = 0; i < 6; i++) {
        vo->setPosition(test_positions[i]);
        if (vo->draw() != 0) {  // Ensure draw() runs without errors
            std::cout << "DRAW FAILED";
            test_passed = false;
        }
    }

    // Clean up dynamically allocated ViewObject
    delete vo;

    return test_passed;
}




bool testToString() {
   
    assert("5" == df::toString(5));
    return true;
}
bool testMusic() {
    df::Music music;

    // Attempt to load music file
    if (music.loadMusic("start-music.wav") == -1) {
        std::cout << "MUSIC NOT FOUND" << std::endl;
        return false;
    }

    // Play the music
    music.play();
    Sleep(2000); // Let the music play for 2 seconds

    // Adjust volume
    music.getMusic()->setVolume(50);
    Sleep(1000); // Wait to hear volume change

    // Pause music
    music.pause();
    Sleep(1000);

    // Resume music
    music.play();
    Sleep(1000);

    // Stop music
    music.stop();

    return true;
}
bool testSound() {
    df::Sound sound;
    
    if (sound.loadSound("fire.wav") == -1) {
        std::cout << "SOUND NOT FOUND";
        return false;
    }
    sound.play();
    Sleep(500);
    sound.getSound().setVolume(0);
    Sleep(500);
    sound.play();
    Sleep(500);

    sound.stop();
    return true;

}


void pri() {
    GM.startUp();
    std::cout << WM.getView().getHorizontal();
    df::Box view = df::Box(df::Vector(50, 50), 50, 50);
    WM.setView(view);
    std::cout << WM.getView().getHorizontal();
}


bool testAniView() {
    RM.startUp();
    GM.startUp();
    std::cout << WM.getView().getHorizontal();
    df::Box view = df::Box(df::Vector(-1, -1), 80, 80);
    WM.setView(view);
    std::cout << WM.getView().getHorizontal();
    df::Object* saucer1 = new df::Object();

    saucer1->setPosition(df::Vector(50, 0));
    saucer1->setVelocity(df::Vector(-0.3, 0));
    saucer1->setSolidness(HARD);

    df::Object* saucer2 = new df::Object();

    saucer2->setPosition(df::Vector(80, 0));
    saucer2->setSolidness(SOFT);
    saucer2->setAltitude(0);

    df::Object* saucer3 = new df::Object();

    saucer3->setPosition(df::Vector(100, 0));
    saucer3->setSolidness(SOFT);
    saucer3->setAltitude(0);
    RM.loadSprite("explosion.txt", "sprite2");

    RM.loadSprite("saucer.txt", "sprite1");

    saucer1->setSprite("sprite1");
    saucer2->setSprite("sprite2");

    GM.run();
    return true;
}

void testWorldManagerViews() {

    // Create boundary and view boxes
    df::Box boundary(df::Vector(0,0), 100, 100);
    df::Box view(df::Vector(10,10), 50, 50);

    // Set boundary and view
    WM.setBoundary(boundary);
    WM.setView(view);

    // Get boundary and view
    df::Box retrievedBoundary = WM.getBoundary();
    df::Box retrievedView = WM.getView();



    // Verify correctness
    if (retrievedBoundary.getVertical() == boundary.getVertical()) {
        std::cout << "Boundary test passed!" << std::endl;
    }
    else {
        std::cout << "Boundary test failed!" << std::endl;
    }

    if (retrievedView.getHorizontal()==view.getHorizontal()) {
        std::cout << "View test passed!" << std::endl;
    }
    else {
        std::cout << "View test failed!" << std::endl;
    }
}


bool testSpriteCollisions(){
    RM.startUp();
    GM.startUp();
    df::Object* saucer1 = new df::Object();

    saucer1->setPosition(df::Vector(50, 0));
    saucer1->setVelocity(df::Vector(-0.3, 0));
    saucer1->setSolidness(HARD);

    df::Object* saucer2 = new df::Object();

    saucer2->setPosition(df::Vector(20, 0));
    saucer2->setSolidness(SOFT);
    saucer2->setAltitude(0);
    
    RM.loadSprite("saucer.txt", "sprite1");
    RM.loadSprite("saucer (5).txt", "sprite2");
    df::Sprite* sprite1 = RM.getSprite("sprite1");
    saucer1->setSprite("sprite1");
    saucer2->setSprite("sprite2");
    GM.run();
    return true;
}




bool testBoxIntersectsBox() {
    bool success = true;

    // Test 1: Overlapping boxes
    df::Box box1(df::Vector(0, 0), 10, 10);
    df::Box box2(df::Vector(5, 5), 10, 10);
    if (!boxIntersectsBox(box1, box2)) {
        std::cout << "Test 1 failed: Overlapping boxes not detected!" << std::endl;
        success = false;
    }

    // Test 2: Non-overlapping boxes
    df::Box box3(df::Vector(20, 20), 5, 5);
    if (boxIntersectsBox(box1, box3)) {
        std::cout << "Test 2 failed: Non-overlapping boxes incorrectly detected as overlapping!" << std::endl;
        success = false;
    }

    // Test 3: Box fully inside another
    df::Box box4(df::Vector(2, 2), 3, 3);
    if (!boxIntersectsBox(box1, box4)) {
        std::cout << "Test 3 failed: Containment case not detected!" << std::endl;
        success = false;
    }

    // Test 4: Edge-touching boxes (should not be considered overlapping)
    df::Box box5(df::Vector(10, 0), 5, 5);
    if (!boxIntersectsBox(box1, box5)) {
        std::cout << "Test 4 failed: Edge-touching boxes not detected!" << std::endl;
        success = false;
    }

    // Test 5: Identical boxes (should be overlapping)
    df::Box box6(df::Vector(0, 0), 10, 10);
    if (!boxIntersectsBox(box1, box6)) {
        std::cout << "Test 5 failed: Identical boxes not detected as overlapping!" << std::endl;
        success = false;
    }

    if (success) {
        std::cout << "All tests passed successfully!" << std::endl;
        return true;
    }
    return false;
    
}
bool testObjectBox() {
    df::Box objBox = df::Box(df::Vector(5,5),5,5);
    df::Object obj;
    obj.setBox(objBox);
    if (obj.getBox().getHorizontal() == 5.0) {
        return true;
    }
    else {
        return false;
    }


}
bool testBox() {
    bool success = true;

    // Default constructor test
    df::Box defaultBox;
    if (defaultBox.getCorner().getX() != 0 || defaultBox.getCorner().getY() != 0 ||
        defaultBox.getHorizontal() != 0 || defaultBox.getVertical() != 0) {
        std::cout << "Default constructor test failed!" << std::endl;
        success = false;
    }

    // Constructor with parameters test
    df::Vector corner(5, 10);
    df::Box paramBox(corner, 20, 15);
    if (paramBox.getCorner().getX() != 5 || paramBox.getCorner().getY() != 10 ||
        paramBox.getHorizontal() != 20 || paramBox.getVertical() != 15) {
        std::cout << "Parameterized constructor test failed!" << std::endl;
        success = false;
    }

    // Setter & Getter tests
    paramBox.setCorner(df::Vector(3, 7));
    if (paramBox.getCorner().getX() != 3 || paramBox.getCorner().getY() != 7) {
        std::cout << "setCorner() test failed!" << std::endl;
        success = false;
    }

    paramBox.setHorizontal(25);
    if (paramBox.getHorizontal() != 25) {
        std::cout << "setHorizontal() test failed!" << std::endl;
        success = false;
    }

    paramBox.setVertical(30);
    if (paramBox.getVertical() != 30) {
        std::cout << "setVertical() test failed!" << std::endl;
        success = false;
    }

    if (success) {
        std::cout << "All Box tests passed!" << std::endl;
    }

    return success;
}



bool testAnimationDrawSkip() {
    DM.startUp();
    RM.startUp();
    RM.loadSprite("saucer (5).txt", "sprite1");

    df::Animation* animation = new df::Animation();
    df::Sprite* sprite = RM.getSprite("sprite1");
    animation->setSprite(sprite);
    sf::RenderWindow* window = DM.getWindow();

    // Set slowdown for animation (higher = slower)
    sprite->setSlowdown(10);  // Delay animation frame changes
    while (true) {
        window->clear();
        animation->setIndex(0);
        animation->draw(df::Vector(5, 5));  // Draw animation
        DM.swapBuffers();  // Refresh display
        Sleep(500);
        animation->setIndex(4);
        animation->draw(df::Vector(5, 5));  // Draw animation
        DM.swapBuffers();  // Refresh display
        Sleep(500);
        


    }

    return true;
}
bool testAnimationDraw() {
    DM.startUp();
    RM.startUp();
    RM.loadSprite("saucer.txt", "sprite1");

    df::Animation* animation = new df::Animation();
    df::Sprite* sprite = RM.getSprite("sprite1");
    animation->setSprite(sprite);
    sf::RenderWindow* window = DM.getWindow();

    // Set slowdown for animation (higher = slower)
    sprite->setSlowdown(10);  // Delay animation frame changes
    bool a = true;
    while (true) {
        a = !a;
        window->clear();

        animation->draw(df::Vector(5, 5));  // Draw animation
        DM.swapBuffers();  // Refresh display
        
        animation->draw(df::Vector(5, 5));  // Draw animation
        DM.swapBuffers();  // Refresh display
        animation->draw(df::Vector(5, 5));  // Draw animation
        DM.swapBuffers();  // Refresh display
        animation->draw(df::Vector(5, 5));  // Draw animation
        DM.swapBuffers();  // Refresh display
        animation->draw(df::Vector(5, 5));  // Draw animation
        DM.swapBuffers();  // Refresh display
        animation->draw(df::Vector(5, 5));  // Draw animation
        DM.swapBuffers();  // Refresh display
        Sleep(100);
        sprite->setSlowdown(20);  // Delay animation frame changes


    }

    return true;
}




bool testResourceManager1() {
    DM.startUp();
    RM.startUp();
    RM.loadSprite("saucer.txt", "sprite1");

    //assert(RM.getSprite("sprite1")->getLabel() == "sprite1");//normal sprite file
    assert(RM.loadSprite("saucer (2).txt", "sprite2")==-1);//width parameter too small
    //assert(RM.loadSprite("saucer (4).txt", "sprite4") == -1);//height too small, there are lines missing from the file

    //assert(RM.getSprite("sprite1")->getLabel() == "sprite1");

    return 0;

}
bool testSpriteDraw() {
    DM.startUp();
    sf::RenderWindow* window = DM.getWindow();
   
    df::Sprite* sprite = new df::Sprite(5);
    df::Frame* frame0 = new df::Frame(6, 2, " ____ /____\\");
    df::Frame* frame1 = new df::Frame(6, 2, " ____ /___o\\");
    df::Frame* frame2 = new df::Frame(6, 2, " ____ /__o_\\");
    df::Frame* frame3 = new df::Frame(6, 2, " ____ /_o__\\");
    df::Frame* frame4 = new df::Frame(6, 2, " ____ /o___\\");
    sprite->addFrame(*frame0);
    sprite->addFrame(*frame1);
    sprite->addFrame(*frame2);
    sprite->addFrame(*frame3);
    sprite->addFrame(*frame4);
    int i = 0;
    while (window->isOpen()) {
        // Clear the window.
        window->clear();

        sprite->draw(i, df::Vector(5,5));
        DM.swapBuffers();

        i++;
        if (i > 4) {
            DM.shutDown();
        }
        Sleep(500);
       
    }
    return true;
}


bool testSprite() {
    DM.startUp();
    df::Sprite* sprite = new df::Sprite(5);
    sprite->setHeight(5);
    assert(sprite->getHeight() == 5);
    sprite->setWidth(10);
    assert(sprite->getWidth() == 10);

    sprite->setLabel("HELLO WORLD");
    assert(sprite->getLabel() == "HELLO WORLD");
    DM.shutDown();
    return true;
}
bool testFrame() {

    DM.startUp();
    sf::RenderWindow* window = DM.getWindow();

    // Main loop: keep drawing until the window is closed.
    while (window->isOpen()) {
        // Clear the window.
        window->clear();

        df::Frame* frame = new df::Frame(5, 1, "Hello");


        // Swap buffers to display what was drawn.
        DM.swapBuffers();
        Sleep(500);
        frame = new df::Frame(4, 1, "Test");
        DM.swapBuffers();

        Sleep(500);
        frame = new df::Frame(5, 3, "Test Number Two");
        DM.swapBuffers();
        Sleep(500);

        DM.shutDown();
    }
    return true;
}

bool testGetFrame() {

    DM.startUp();
    sf::RenderWindow* window = DM.getWindow();   

        df::Frame* frame = new df::Frame(5, 1, "Hello");
        df::Sprite* sprite = new df::Sprite(5);
        std::cout << sprite->getFrameCount();

        sprite->addFrame(*frame);
        std::cout << sprite->getFrameCount();

        frame = new df::Frame(4, 1, "Test");
        sprite->addFrame(*frame);
        std::cout << sprite->getFrameCount();

        frame = new df::Frame(5, 3, "Test Number Two");
        sprite->addFrame(*frame);
        std::cout << sprite->getFrameCount();

        frame = new df::Frame(5, 3, "Test Number Three");
        sprite->addFrame(*frame);
        std::cout << sprite->getFrameCount();

        frame = new df::Frame(5, 3, "Test Number Three");
        sprite->addFrame(*frame);
        std::cout << sprite->getFrameCount();
        assert(sprite->getFrameCount() == 5);
        
        return true;
}




bool testFrameDraw() {

    DM.startUp();
    sf::RenderWindow* window = DM.getWindow();

    // Main loop: keep drawing until the window is closed.
    while (window->isOpen()) {
        // Clear the window.
        window->clear();

        df::Frame* frame = new df::Frame(5, 1, "Hello");
        frame->draw(df::Vector(0, 0), df::RED);

        // Swap buffers to display what was drawn.
        DM.swapBuffers();
        Sleep(500);
        frame = new df::Frame(4, 1, "Test");
        frame->draw(df::Vector(5, 5), df::RED);
        DM.swapBuffers();

        Sleep(500);
        frame = new df::Frame(5, 3, "Test Number Two");
        frame->draw(df::Vector(7, 7), df::BLUE);
        DM.swapBuffers();
        Sleep(500);

        DM.shutDown();
    }


    DM.shutDown();
    

    return true;
}












//display manager basic test
bool testingDM() {
    DM.startUp();
    sf::RenderWindow* window = DM.getWindow();

    // Main loop: keep drawing until the window is closed.
    while (window->isOpen()) {


        // Clear the window.
        window->clear();

        DM.drawCh(df::Vector({ 10 ,5 }), '*', df::GREEN);

        // Swap buffers to display what was drawn.
        DM.swapBuffers();
    }


    DM.shutDown();
    return true;

}
//tests altitude, collision detection, mouse input, keyboard input, game borders, velocity, solidness
bool testEverything() {
    GM.startUp();
    Saucer* saucer1 = new Saucer();

    saucer1->setPosition(df::Vector(50, 0));
    saucer1->setVelocity(df::Vector(-0.3, 0));
    saucer1->setSolidness(HARD);

    Saucer* saucer2 = new Saucer();

    saucer2->setPosition(df::Vector(40, 0));
    saucer2->setVelocity(df::Vector(-0.1,0));
    saucer2->setSolidness(SOFT);
    saucer2->setAltitude(0);


    Saucer* obstacle = new Saucer();

    obstacle->setPosition(df::Vector(20, 0));
    obstacle->setSolidness(HARD);


    Saucer* hero1 = new Saucer();

    hero1->setPosition(df::Vector(50, 10));
    hero1->setVelocity(df::Vector(-0.14, 0));
    hero1->setSolidness(SPECTRAL);
    hero1->setAltitude(2);
    Saucer* hero2 = new Saucer();

    hero2->setPosition(df::Vector(45, 10));
    hero2->setVelocity(df::Vector(-0.05, 0));
    hero2->setSolidness(SPECTRAL);
    hero2->setAltitude(3);


    Saucer* hero3 = new Saucer();

    hero3->setPosition(df::Vector(50, 15));
    hero3->setVelocity(df::Vector(-0.14, 0));
    hero3->setSolidness(HARD);
    hero3->setAltitude(2);
    Saucer* hero4 = new Saucer();

    hero4->setPosition(df::Vector(45, 15));
    hero4->setVelocity(df::Vector(0, 0));
    hero4->setSolidness(HARD);
    hero4->setAltitude(3);





    Hero* hero = new Hero();
    hero->setSolidness(SOFT);
    hero->setPosition(df::Vector(0,0));

    
   


    GM.run();
    return true;

}

bool testDisplayStart() {
    LM.startUp();
    DM.startUp();
    //direct start up of DM, no GM
    sf::RenderWindow* window = DM.getWindow();

    sf::Font font;
    if (!font.openFromFile("df-font.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return false;
    }
    sf::Text text(font);
    text.setString("Hello World");
    text.setCharacterSize(32);
    text.setFillColor(sf::Color::Green);
    text.setStyle(sf::Text::Bold);
    text.setPosition({ 96, 134 });
    char buffer[50];
    //logs and tests DM functions
    sprintf_s(buffer, "Window Width: %ld\n", DM.getHorizontal());
    LM.writeLog(buffer);
    char buffer1[50];
    sprintf_s(buffer1, "Window height: %ld\n", DM.getVertical());
    LM.writeLog(buffer1);

    LM.writeLog("HIHIHIHHI");
    while (1 == 1) {

        window->clear();
        window->draw(text);
        window->display();
   }

    DM.shutDown();
    return true;
}



bool testDrawStr() {

    if (DM.startUp() != 0) {
        std::cerr << "Error starting up DisplayManager" << std::endl;
        return false;
    }

    //get the SFML window
    sf::RenderWindow* window = DM.getWindow();

    // Keep drawing until the window is closed
    while (window->isOpen()) {
   

        // Clear the window.
        window->clear();
//test drawing different strings
        DM.drawString(df::Vector(5, 5), "Left Justified", LEFT_JUSTIFIED, df::WHITE);
        DM.drawString(df::Vector(40, 10), "Center Justified", CENTER_JUSTIFIED, df::YELLOW);
        DM.drawString(df::Vector(75, 15), "Right Justified", RIGHT_JUSTIFIED, df::CYAN);

        // Swap buffers to display what was drawn.
        DM.swapBuffers();
    }

    // Shut down the DisplayManager.
    DM.shutDown();

    return true;
}


bool testCustomGameObjectDraw() {
    if (DM.startUp() != 0) {
        std::cerr << "Error: Could not start DisplayManager." << std::endl;
        return false;
    }
    //use saucers draw() method, draw object
    Saucer* saucer = new Saucer();
    // Set a position for the Saucer
    saucer->setPosition(df::Vector(20, 10));

    sf::RenderWindow* window = DM.getWindow();

    sf::Clock clock;
    while (window->isOpen()) {
       

        window->clear();

        // Draw the Saucer.
        saucer->draw();

        DM.swapBuffers();
//testing sleep function
        sf::sleep(sf::milliseconds(16));
    }

    // Shut down the DisplayManager.
    DM.shutDown();
    return true;
}




bool testAltitude() {
    //4 different objects
    //pair on the left, pair on the right
    DM.startUp();
    GM.startUp();
    Saucer backSaucer;
    Saucer frontSaucer;
    Saucer diffFront;
    Saucer diffBack;
    assert(backSaucer.setAltitude(-1)==-1);
    frontSaucer.setAltitude(3);

    backSaucer.setAltitude(1);
    diffFront.setAltitude(3);

    diffBack.setAltitude(1);
    diffFront.setPosition(df::Vector(3, 0.5));
    diffBack.setPosition(df::Vector(3.5, 0.5));

    df::Vector frontVector = df::Vector(0, 0);
    frontSaucer.setPosition(frontVector);

    backSaucer.setPosition(df::Vector(0,0.5));
    //sf::RenderWindow* window1 = DM.getWindow();

    GM.run();

    frontSaucer.setAltitude(GM.getTest());
    std::cout << "ejfodsif";
    return true;

}

//ignore
bool testIMStart() {
    assert(IM.startUp() == -1);
    DM.startUp();
    assert(IM.startUp() == 0);
    return true;
}

bool testEventsMK() {
    bool success = true;

    // Test EventKeyboard
    EventKeyboard ek;
    ek.setKey(Keyboard::A);
    ek.setKeyboardAction(KEY_PRESSED);

    if (ek.getKey() != Keyboard::A) {
        std::cerr << "EventKeyboard: setKey/getKey failed.\n";
        success = false;
    }
    if (ek.getKeyboardAction() != KEY_PRESSED) {
        std::cerr << "EventKeyboard: setKeyboardAction/getKeyboardAction failed.\n";
        success = false;
    }

    // Test EventMouse
    EventMouse em;
    em.setMouseAction(CLICKED);
    em.setMouseButton(Mouse::LEFT);
    em.setMousePosition(df::Vector(10, 20));

    if (em.getMouseAction() != CLICKED) {
        std::cerr << "EventMouse: setMouseAction/getMouseAction failed.\n";
        success = false;
    }
    if (em.getMouseButton() != Mouse::LEFT) {
        std::cerr << "EventMouse: setMouseButton/getMouseButton failed.\n";
        success = false;
    }
    if (em.getMousePosition().getX() != 10 || em.getMousePosition().getY() != 20) {
        std::cerr << "EventMouse: setMousePosition/getMousePosition failed.\n";
        success = false;
    }

    return success;
}


//bool testGetInput() {
//    Saucer saucer;
//    DM.startUp();
//    IM.startUp();
//    while (true) {
//        IM.getInput();
//    }
//    return true;
//}

bool testInputMovesObjects() {
    GM.startUp();
    Saucer saucer;
    saucer.setPosition(df::Vector(5, 5));
    GM.run();
    return true;
}


bool testVelocity() {
    //three objects, top left corner
    GM.startUp();
    Saucer saucer1;
    Saucer saucer2;
    Saucer saucer3;
    saucer1.setPosition(df::Vector(1, 0.5));
    saucer2.setPosition(df::Vector(2, 0.5));
    saucer3.setPosition(df::Vector(3, 0.5));

    saucer1.setVelocity(df::Vector(1.0, 0.05));
    saucer2.setVelocity(df::Vector(0.05, 0.05));
    saucer3.setVelocity(df::Vector(-0.05, -0.05));
    GM.run();
    return true;
}



bool testCollisions1() {
    //Two objects, both hard, both stop movement upon collision
    GM.startUp();
    Saucer saucer1;
    Saucer saucer2;
    saucer1.setPosition(df::Vector(1, 0.5));
    saucer2.setPosition(df::Vector(6, 0.5));
    saucer1.setSolidness(HARD);
    saucer2.setSolidness(HARD);
    Sleep(500);
    saucer2.setVelocity(df::Vector(-0.1, 0));
    GM.run();
    GM.shutDown();

    return true;
}
//Two objects, both soft, pass through each other but still collide. This function used to work with the saucer class as it would log specific messages to the logfile upon objcet collision, but I got rid of it.
bool testCollisionsSoft() {
    GM.startUp();
    Saucer saucer3;
    Saucer saucer4;
    saucer3.setPosition(df::Vector(5, 0.5));
    saucer4.setPosition(df::Vector(10, 0.5));
    saucer3.setSolidness(SOFT);
    saucer4.setSolidness(SOFT);
    saucer4.setVelocity(df::Vector(-0.1, 0));
    GM.run();
    return true;
}
//test if border message goes through
bool testBorders() {
    GM.startUp();
    
    Saucer saucer4;
   
    saucer4.setPosition(df::Vector(40, 0.5));
    saucer4.setSolidness(SOFT);
    saucer4.setVelocity(df::Vector(0.5, 0));
    GM.run();
    return true;
}





















//Project 2a Tests


//Unit tests
bool testLog() {//check dragonfly log
    df::LogManager& logManager = df::LogManager::getInstance();
    if (logManager.startUp() != 0) {
        return false;
    }

    logManager.writeLog("Log Manager Initialized Sharko!\n");
    logManager.writeLog("Game initialized at %d, %d\n", 80, 24);
    logManager.writeLog("Log Test Message #3");
    logManager.writeLog("Log Test Message #5!");
    int bytes_written = logManager.writeLog("Test log entry.\n");
    if (bytes_written <= 0) {
        return false;
    }
    assert(logManager.writeLog("Am I -1?") != -1);
    logManager.shutDown();

    return true;
}

bool testClock() {
    //expected output is 20000 or 21000 given 1ms margin of err
    df::LogManager& logManager = df::LogManager::getInstance();
    logManager.startUp();
    timeBeginPeriod(1);
    df::Clock* clock = new df::Clock();
    int sleep_time = 20;
    Sleep(sleep_time);

    long delta_time = clock->delta() / 1000;
    char buffer[50];
    sprintf_s(buffer, "Delta time: %ld microseconds\n", delta_time * 1000);
    if (delta_time - sleep_time > 2 || delta_time - sleep_time < -2) {
        std::cout << "Difference between sleep time and clock delta time greater than 2";
        return false;
    }
    logManager.writeLog(buffer);

    timeEndPeriod(1);
    delete clock;
    logManager.shutDown();
    return true;
}



bool testVector() {
    df::Vector v(3, 4);

    //initialization
    if (v.getX() != 3 || v.getY() != 4) {
        std::cout << "Position initialization failed";
        return false;

    }


    if (v.getMagnitude() != 5) { // sqrt(3^2 + 4^2) = 5
        std::cout << "Magnitude calculation failed";
        return false;
    }

    return true;
}
bool testObject() {
    df::Object obj;

    //check default ID assignment
    if (obj.getId() != 1011) {
        std::cout << "ID is off";
        std::cout << obj.getId();
        return false;
    }

    //check type setting
    obj.setType("TestType");
    if (obj.getType() != "TestType") {
        std::cout << "Type is off";
        return false;
    }

    return true;
}
bool testEvent() {
    df::Event e;

    //check default event type
    if (e.getType() != df::UNDEFINED_EVENT) {
        std::cout << "event Type is off";
        return false;
    }

    //set and get event type
    e.setType("TestEvent");
    if (e.getType() != "TestEvent") {
        std::cout << "Set type failed";
        return false;
    }
    return true;
}

//est function for ObjectList
bool testObjectList() {
    df::LogManager& logManager = df::LogManager::getInstance();
    logManager.startUp();
    df::ObjectList objectList;
    objectList.clear();

    assert(objectList.getCount() == 0);

    df::Object* obj1 = new df::Object();
    df::Object* obj2 = new df::Object();
    assert(objectList.insert(obj1) == 0);
    assert(objectList.insert(obj2) == 0);
    assert(objectList.getCount() == 2);

    assert(objectList.remove(obj1) == 0);
    assert(objectList.getCount() == 1);

    df::Object* obj3 = new df::Object();
    assert(objectList.remove(obj3) == -1);  //object was not inserted

    assert(objectList.remove(obj2) == 0);
    assert(objectList.getCount() == 0);
    char buffer[50];
    sprintf_s(buffer, "Count objects in list: %ld objects\n", objectList.getCount());
    logManager.writeLog(buffer);
    for (int i = 0; i < df::MAX_OBJECTS; i++) {
        assert(objectList.insert(new df::Object()) == 0);
    }
    assert(objectList.insert(new df::Object()) == -1);
    assert(objectList.isFull() == true);
    assert(objectList.getCount() == df::MAX_OBJECTS);

    objectList.clear();
    assert(objectList.getCount() == 0);  //after clear, count should be 0

    delete obj3;
    logManager.shutDown();

    return true;
}

bool testS() {
    Saucer* saucer1 = new Saucer();
    df::EventStep stepEvent(1);
    saucer1->eventHandler(&stepEvent);
    df::Event genericEvent;
    genericEvent.setType("GenericEvent");
    Saucer* saucer2 = new Saucer();
    saucer2->eventHandler(&genericEvent);
    WM.removeObject(saucer1);
    WM.removeObject(saucer2);
    return true;

}
bool testInsert() {
    df::LogManager& logManager = df::LogManager::getInstance();

    logManager.startUp();

    //WorldManager& WM = WorldManager::getInstance();
    WM.startUp();
    Saucer* saucer1 = new Saucer();
    Saucer* saucer2 = new Saucer();
    Saucer* saucer3 = new Saucer();
    int objectCount = WM.getAllObjects().getCount();

    WM.removeObject(saucer1);

    //get object count
    int objectCountRemoved = WM.getAllObjects().getCount();

    char buffer[50];
    sprintf_s(buffer, "Count objects after new Saucers: %d objects\n", objectCount);
    logManager.writeLog(buffer);
    char buffer1[50];
    sprintf_s(buffer1, "Count objects after removal: %d objects\n", objectCountRemoved);
    logManager.writeLog(buffer1);
    int test = WM.objectsOfType("Saucer").getCount();
    char buffer2[50];
    sprintf_s(buffer2, "Number of objects of type saucer: %d", test);
    if (test != 2) {
        std::cout << "too many/few objects in list";
        return false;
    }
    logManager.writeLog(buffer2);
    WM.shutDown();
    logManager.shutDown();
    return true;
}

bool testEventStep() {
    df::EventStep e1;
    assert(e1.getType() == df::STEP_EVENT);
    assert(e1.getStepCount() == 0);

    df::EventStep e2(5);
    assert(e2.getType() == df::STEP_EVENT);
    assert(e2.getStepCount() == 5);

    e2.setStepCount(10);
    assert(e2.getStepCount() == 10);
    return true;
}


bool testObjectConDestr() {
    //WorldManager& WM = WorldManager::getInstance();
    WM.startUp();

    std::cout << "Creating a Saucer...\n";
    Saucer* saucer = new Saucer();

    //check object was inserted
    int countAfterInsert = WM.getAllObjects().getCount();
    assert(countAfterInsert > 0);

    delete saucer;

    //check that the object was removed
    int countAfterDelete = WM.getAllObjects().getCount();
    assert(countAfterDelete == 0);

    WM.shutDown();
    return true;
}


bool testMarkForDeleteAndUpdate() {
    //WorldManager& wm = WorldManager::getInstance();
    WM.startUp();

    Saucer* saucer1 = new Saucer();
    Saucer* saucer2 = new Saucer();
    Saucer* saucer3 = new Saucer();

    int countAfterInsert = WM.getAllObjects().getCount();
    assert(countAfterInsert == 3);
    std::cout << "insertion pass";

    WM.markForDelete(saucer1);


    WM.update();
    int countAfterUpdate = WM.getAllObjects().getCount();
    assert(countAfterUpdate == 2);
    std::cout << "count pass";
    WM.markForDelete(saucer2);
    WM.markForDelete(saucer3);

    WM.update();
    int countAfterFinalUpdate = WM.getAllObjects().getCount();
    assert(countAfterFinalUpdate == 0);


    WM.shutDown();
    return true;
}







//integration tests
bool testGameManagerClock() {
    //GM& gm = GM::getInstance();
    df::Clock* clock = new df::Clock();
    GM.startUp();
    long int expectedFrameTime = GM.getFrameTime();

    Sleep(expectedFrameTime);
    long int actualFrameTime = clock->delta();


    std::cout << "Expected frame time: " << expectedFrameTime << "ms\n";
    std::cout << "Actual frame time: " << actualFrameTime / 1000 << "ms\n";

    assert(abs(actualFrameTime / 1000 - expectedFrameTime) < 2.2);

    GM.shutDown();
    return true;

}
bool testGameManagerRunTime() {
    //expected 1 loop and is one loop. 35ms is enough for one loop given 30ms cycling.
    GM.startUp();
    //GameManager& gameManager = GameManager::getInstance();

    std::thread gameThread([&]() { GM.run(); });

    Sleep(30);
    GM.setGameOver(true);

    if (gameThread.joinable()) {//in order to setGameOver, must use thread
        gameThread.join();
    }
    char buffer[50];
    sprintf_s(buffer, "Iterations: %ld loops\n", GM.getTest());
    assert(GM.getTest() == 3);
    LM.writeLog(buffer);
    GM.shutDown();
    return true;
}


bool testGameManagerRun() {
    GM.startUp();
    Saucer* saucer3 = new Saucer();
    Saucer* saucer4 = new Saucer();

    std::thread gameThread([]() { GM.run(); });
    WM.markForDelete(saucer3);
    //let game loop run for 60ms.
    Sleep(60);

    GM.setGameOver(true);

    //wait for the game loop to finish.
    if (gameThread.joinable()) {
        gameThread.join();
    }
    std::cout << "TESTGAMEMANAGER RAN";


    GM.shutDown();
    return true;
}


bool testVector1() {
    //test default constructor
    df::Vector v1;
    if (v1.getX() != 0 || v1.getY() != 0) {
        std::cout << "initialization vector failed";
        return false;
    };
    //test initial with values
    df::Vector v2(3.0, 4.0);
    assert(v2.getX() == 3.0 && v2.getY() == 4.0);
    std::cout << "Vector get passed";
    //test sets
    v1.setX(5.0);
    assert(v1.getX() == 5.0);

    v1.setY(-2.0);
    assert(v1.getY() == -2.0);

    // Test setXY
    v1.setXY(7.0, 8.0);
    assert(v1.getX() == 7.0 && v1.getY() == 8.0);
    std::cout << "Sets vector has pased";
    assert(v2.getMagnitude() == 5.0);

    //test scale
    v2.scale(2.0);
    assert(v2.getX() == 6.0 && v2.getY() == 8.0);

    //test normalize
    df::Vector v3(10.0, 0.0);
    v3.normalize();
    assert(v3.getX() == 1.0 && v3.getY() == 0.0);
    std::cout << "Vector directives passed";
    //test addition operator
    df::Vector v4(1.0, 2.0);
    df::Vector v5(3.0, 4.0);
    df::Vector v6 = v4 + v5;
    assert(v6.getX() == 4.0 && v6.getY() == 6.0);

    return true;
}



