#include "Animation.h"
namespace df {
    // Constructor
    Animation::Animation() {
        m_p_sprite = nullptr;
        m_name = "";
        m_index = 0;
        m_slowdown_count = 0;
    }

    // Set associated Sprite
    void Animation::setSprite(Sprite* p_new_sprite) {

        m_p_sprite = p_new_sprite;
        m_index = 0;
    }

    // Return pointer to associated Sprite
    Sprite* Animation::getSprite() const {
        return m_p_sprite;
    }

    // Set Sprite name
    void Animation::setName(std::string new_name) {
        m_name = new_name;
    }

    // Get Sprite name
    std::string Animation::getName() const {
        return m_name;
    }

    // Set index of current Sprite frame
    void Animation::setIndex(int new_index) {
        m_index = new_index;

    }

    // Get index of current Sprite frame
    int Animation::getIndex() const {
        return m_index;
    }

    // Set animation slowdown count
    void Animation::setSlowdownCount(int new_slowdown_count) {
        m_slowdown_count = new_slowdown_count;
    }

    // Get animation slowdown count
    int Animation::getSlowdownCount() const {
        return m_slowdown_count;
    }


    // Draw a single frame centered at position (x, y).
    // Drawing accounts for slowdown and advances the sprite frame.
    // Return 0 if successful, else -1.
    int Animation::draw(Vector position) {
        // If sprite is not defined, return -1.
        if (m_p_sprite == nullptr) {
            return -1;
        }

        // Get the current index.
        int index = getIndex();

        // Ask Sprite to draw the current frame at the specified position.
        m_p_sprite->draw(index, position);

        // If slowdown count is -1, animation is frozen.
        if (getSlowdownCount() == -1) {
            return 0;
        }

        // Increment slowdown counter.
        int count = getSlowdownCount();
        count++;

        // Advance sprite index if appropriate.
        if (count >= m_p_sprite->getSlowdown()) {
            count = 0;  // Reset slowdown counter.
            index++;    // Advance frame.

            // If at the last frame, loop back to the beginning.
            if (index >= m_p_sprite->getFrameCount()) {
                index = 0;
            }

            // Set index for next draw().
            setIndex(index);
        }

        // Set slowdown counter for next draw().
        setSlowdownCount(count);

        return 0;
    }


    Box Animation::getBox() const {
        // If no sprite, return unit Box centered at (0,0)
        if (!m_p_sprite) {
            return Box(Vector(-0.5, -0.5), 0.99, 0.99);
        }

        // Create Box around centered Sprite
        Vector corner(-1 * m_p_sprite->getWidth() / 2.0, -1 * m_p_sprite->getHeight() / 2.0);
        return Box(corner, m_p_sprite->getWidth(), m_p_sprite->getHeight());
    }

}

//testing github