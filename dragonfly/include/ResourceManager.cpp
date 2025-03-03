#include "Manager.h"
#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "LogManager.h"
using std::cout;
using std::endl;

namespace df {

    ResourceManager::ResourceManager() {
        setType("ResourceManager");

        //initialize all elements of m_p_sprite to nullptr
        for (int i = 0; i < MAX_SPRITES; i++) {
            m_p_sprite[i] = nullptr;
        }
        m_sprite_count = 0;
    }

    ResourceManager& ResourceManager::getInstance() {
        static ResourceManager instance;
        return instance;
    }

    int ResourceManager::startUp() {
        m_sprite_count = 0;
        Manager::startUp();
        return 0;
    }

    // Load Sprite from file.  
// Assign indicated label to sprite.  
// Return 0 if ok, else -1.  
    int ResourceManager::loadSprite(std::string filename, std::string label) {

        // Check if room in array.  
        if (m_sprite_count == MAX_SPRITES) { // Sprite array full?  
            return -1; // Error  
        }
        std::string line;
        std::ifstream myfile(filename);
        std::vector<std::string> data;
        int i = 0;
        int frames;
        int width;
        int height;
        int slowdown;
        Color color;
        if (!myfile.is_open()) {
            std::cout << "FAILED TO OPEN FILE";
            return -1;
        }
      if (myfile.is_open()) {

            std::cout << "OPEN FILE" << std::endl;

            // Read frames
            if (!getline(myfile, line) || (frames = atoi(line.c_str())) <= 0) {
                std::cerr << "Error: Invalid frame count in file " << filename << std::endl;
                myfile.close();
                return -1;
            }
            std::cout << line<<"frames";

            // Read width
            if (!getline(myfile, line) || (width = atoi(line.c_str())) <= 0) {
                std::cerr << "Error: Invalid width in file " << filename << std::endl;
                myfile.close();
                return -1;
            }
            std::cout << line << "width";

            // Read height
            if (!getline(myfile, line) || (height = atoi(line.c_str())) <= 0) {
                std::cerr << "Error: Invalid height in file " << filename << std::endl;
                myfile.close();
                return -1;
            }
            std::cout << line << "height";


            // Read slowdown
            if (!getline(myfile, line) || (slowdown = atoi(line.c_str())) < 0) {
                std::cerr << "Error: Invalid slowdown value in file " << filename << std::endl;
                myfile.close();
                return -1;
            }
            std::cout << line << "slowdown";


            // Read color
            if (!getline(myfile, line)) {
                std::cerr << "Error: Missing color value in file " << filename << std::endl;
                myfile.close();
                return -1;
            }

            if (line == "black") {
                color = BLACK;
            }
            else if (line == "red") {
                color = RED;
            }
            else if (line == "green") {
                color = GREEN;
            }
            else if (line == "yellow") {
                color = YELLOW;
            }
            else if (line == "blue") {
                color = BLUE;
            }
            else if (line == "magenta") {
                color = MAGENTA;
            }
            else if (line == "cyan") {
                color = CYAN;
            }
            else if (line == "white") {
                color = WHITE;
            }
            else {
                std::cerr << "Error: Invalid color in file " << filename << std::endl;
                myfile.close();
                return -1;
            }
            std::cout << line << "color";

        }

        std::cout << "REACHED";
        Sprite* sprite = new Sprite(frames);
        sprite->setHeight(height);
        sprite->setWidth(width);
        sprite->setSlowdown(slowdown);
        sprite->setColor(color);
        // use f=1 or =0?
        int countLines = 0;
        for (int f = 0; f < frames; f++) {
            std::string test = "";
            for (int h = 0; h < height; h++) {
                getline(myfile, line);
                std::cout << line << ":current line" << endl;
                if (line.length() != width) {
                    std::cout << "Width of body of file incorrect";
                    return -1;
                }
                test += line;
                countLines++;
              
              
            }
            if (f == frames - 1) {
                if (getline(myfile, line)) {
                    std::cout << "Didnt reach end of file";
                    return -1;
                }
            }
            Frame* frame= new Frame(width,height,test);
            std::cout << frame->getString() <<":frame string"<< endl;
            sprite->addFrame(*frame);

        }
        std::cout << countLines << ":clines" << endl;
        if (countLines< frames * height) {
            std::cout << "TOO FEW LINES";
            return -1;
        }
        myfile.close();
        sprite->setLabel(label);
        m_p_sprite[m_sprite_count] = sprite;
 
        m_sprite_count++;
        return 0;

    }




    int ResourceManager::unloadSprite(std::string label) {
        for (int i = 0; i < m_sprite_count; i++) {
            if (label == m_p_sprite[i]->getLabel()) {
                delete m_p_sprite[i];

                // Scoot over remaining sprites.  
                for (int j = i; j < m_sprite_count - 2; j++) {
                    m_p_sprite[j] = m_p_sprite[j + 1];
                }
                m_sprite_count--;
                return 0;
            }
        }
        return -1;
    }







    // Find Sprite with indicated label.  
// Return pointer to it if found, else NULL.  
    Sprite* ResourceManager::getSprite(std::string label) const {
        std::cout << "FUNCTION LABEL:" << label << endl;
        std::cout << "label label:" << m_p_sprite[0]->getLabel() << endl;
        std::cout << "REACHED GETLABEL";

        for (int i = 0; i < m_sprite_count; i++) {  
            if (label == m_p_sprite[i]->getLabel()) {
                std::cout << "REACHED GETLABEL2";
                return m_p_sprite[i];
            }
        }
        return NULL; // Sprite not found     
    }



    // Shut down manager, freeing up any allocated assets.
    void ResourceManager::shutDown() {
        for (int i = 0; i < m_sprite_count; i++) {
            if (m_p_sprite[i] != nullptr) {
                delete m_p_sprite[i];
            }
        }

        m_sprite_count = 0;

        // Call base class shutdown
        Manager::shutDown();
    }










    int ResourceManager::loadSound(std::string filename, std::string label) {
        if (sound_count == MAX_SOUNDS) {
            LM.writeLog("Sound array full.");
            return -1;
        }

        if (sound[sound_count].loadSound(filename) == -1) {
            LM.writeLog("Unable to load from file");
                return -1;
        }

            // All is well.  
        sound[sound_count].setLabel(label);
            sound_count++;
        return 0;
       
    }

    int ResourceManager::unloadSound(std::string label) {
        for (int i = 0; i < sound_count; ++i) {
            if (sound[i].getLabel() == label) {
                // Shift remaining sounds left
                for (int j = i; j < sound_count - 1; ++j) {
                    sound[j] = sound[j + 1];
                }

                --sound_count; // Decrement the sound count
                return 0; // Success
            }
        }

        return -1; // Sound not found
    }

    Sound* ResourceManager::getSound(std::string label) {
        for (int i = 0; i < sound_count; ++i) {
            if (sound[i].getLabel() == label) {
                return &sound[i];  
            }
        }
        return nullptr; // Sound not found
    }


    int ResourceManager::loadMusic(std::string filename, std::string label) {
        if (label.empty()) {
            LM.writeLog("Empty label is not allowed for Music.");
            return -1;  
        }

        if (music_count >= MAX_MUSICS) {
            LM.writeLog("Music array full.");
            return -1;  
        }

        if (music[music_count].loadMusic(filename) == -1) {
            LM.writeLog("Unable to load music from file.");
            return -1; 
        }

        music[music_count].setLabel(label);
        ++music_count;
        return 0; // Success
    }
    int ResourceManager::unloadMusic(std::string label) {
        for (int i = 0; i < music_count; ++i) {
            if (music[i].getLabel() == label) {
                music[i].setLabel(""); // Mark as unloaded by setting label to empty
                return 0; // Success
            }
        }
        return -1; // Error: Music not found
    }
    Music* ResourceManager::getMusic(std::string label) {
        for (int i = 0; i < music_count; ++i) {
            if (music[i].getLabel() == label) {
                return &music[i]; // Return pointer to found Music
            }
        }
        return nullptr; // Error: Music not found
    }

}



