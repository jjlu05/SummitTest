#include "Sound.h"
namespace df {
    // Constructor
    Sound::Sound() {
        m_p_sound = nullptr; // Initialize pointer to null
    }

    // Destructor
    Sound::~Sound() {
        if (m_p_sound) {
            delete m_p_sound;
        }
    }

    // Load sound buffer from file
    int Sound::loadSound(std::string filename) {
        if (!m_sound_buffer.loadFromFile(filename)) {
            return -1; // Return -1 on error
        }

        // Allocate sf::Sound and set buffer
        m_p_sound = new sf::Sound(m_sound_buffer);

        return 0; // Return 0 on success
    }

    // Set label associated with sound
    void Sound::setLabel(std::string new_label) {
        m_label = new_label;
    }

    // Get label associated with sound
    std::string Sound::getLabel() const {
        return m_label;
    }

    // Play sound with optional looping
    void Sound::play(bool loop) {
        if (m_p_sound) {
            m_p_sound->setLooping(loop);
            m_p_sound->play();
        }
    }

    // Stop sound
    void Sound::stop() {
        if (m_p_sound) {
            m_p_sound->stop();
        }
    }

    // Pause sound
    void Sound::pause() {
        if (m_p_sound) {
            m_p_sound->pause();
        }
    }

    // Return SFML sound object
    sf::Sound Sound::getSound() const {
        return *m_p_sound; // Return dereferenced pointer (assumes m_p_sound is not null)
    }
}