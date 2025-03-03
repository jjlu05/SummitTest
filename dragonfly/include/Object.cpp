#include "Object.h"
#include "Vector.h"
#include "WorldManager.h" // Required for adding/removing objects
#include <string>
#include "ResourceManager.h"
namespace df {

    // Define the static ID counter as a class member
    int Object::id_count = 0;

    Object::Object() : m_id(id_count), m_altitude(MAX_ALTITUDE/2), m_type("Object"), m_position(Vector()) {
        id_count++;  
        WorldManager::getInstance().insertObject(this);
    }

    // Destructor - Removes object from the world automatically
    Object::~Object() {
        WorldManager::getInstance().removeObject(this);
    }

    // Set Object ID
    void Object::setId(int new_id) {
        m_id = new_id;
    }

    // Get Object ID
    int Object::getId() const {
        return m_id;
    }

    // Set type identifier of Object
    void Object::setType(std::string new_type) {
        m_type = new_type;
    }

    // Get type identifier of Object
    std::string Object::getType() const {
        return m_type;
    }

    // Set position of Object
    void Object::setPosition(Vector new_pos) {
        m_position = new_pos;
    }

    // Get position of Object
    Vector Object::getPosition() const {
        return m_position;
    }

    // Handle event (default is to ignore everything).
    // Return 0 if ignored, else 1 if handled.
    int Object::eventHandler(const Event* p_e) {
        return 0;//Ready to be overridden
    }

    int Object::draw() {
        Vector pos = getPosition();
        return m_animation.draw(pos);

    }


    void Object::setBox(Box new_box) {
        m_box = new_box;
    }
    Box Object::getBox()const {
        return m_box;
    }
    // Set Sprite for this Object to animate.
// Return 0 if successful, else -1.
    int Object::setSprite(std::string sprite_label) {
        // Retrieve the sprite from the ResourceManager.
        Sprite* p_sprite = RM.getSprite(sprite_label);

        // Check if the sprite retrieval was successful.
        if (p_sprite == nullptr) {
            return -1; // Return error if sprite is not found.
        }

        // Set the sprite in the animation object.
        m_animation.setSprite(p_sprite);

        // Return success.
        setBox(m_animation.getBox());
        return 0;
    }
    int Object::setAltitude(int new_altitude){
        if (new_altitude<0||new_altitude>MAX_ALTITUDE) {
            return -1;
        }
        m_altitude = new_altitude;

        return 0;
    }
    int Object::getAltitude() const {
        return m_altitude;
    };

    void Object::setSpeed(float speed) {
    
    };
    float Object::getSpeed() const {
        return m_speed;
    };
    void Object::setDirection(Vector new_direction) {
        m_direction = new_direction;
    };
    Vector Object::getDirection() const {
        return m_direction;
    };
    void Object::setVelocity(Vector new_Velocity) {
        m_speed = new_Velocity.getMagnitude();
        new_Velocity.normalize();
        m_direction = new_Velocity;
        
    };

    //COPY OR DIRECT CHANGE?
    Vector Object::getVelocity() {
        Vector velocity = m_direction;
        velocity.scale(m_speed);
        return velocity;
    };
    Vector Object::predictPosition() {
        Vector new_pos = m_position + getVelocity();
        return new_pos;
    };

    bool Object::isSolid() const {
        if (m_solidness == SPECTRAL) {
            return false;
        }
        else {
            return true;
        }
    };
    int Object::setSolidness(Solidness new_solid) {
        m_solidness = new_solid;
        
        //checks? return -1?
        return 0;
    };
    Solidness Object::getSolidness() const {
        return m_solidness;
    };
    void Object::setAnimation(Animation new_animation) {
        m_animation = new_animation;
    }

    // Get the current Animation of the Object.
    Animation Object::getAnimation() const {
        return m_animation;
    }
}