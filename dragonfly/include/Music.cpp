#include "Music.h"
#include <iostream>
namespace df {
    Music::Music() {}

    int Music::loadMusic(std::string filename) {
        if (!m_music.openFromFile(filename)) {
            std::cerr << "Error: Could not load music from " << filename << std::endl;
            return -1;
        }
        return 0;
    }

    void Music::setLabel(std::string new_label) {
        m_label = new_label;
    }

    std::string Music::getLabel() const {
        return m_label;
    }

    void Music::play(bool loop) {
        m_music.setLooping(loop);
        m_music.play();
    }

    void Music::stop() {
        m_music.stop();
    }

    void Music::pause() {
        m_music.pause();
    }

    sf::Music* Music::getMusic() {
        return &m_music;
    }
}