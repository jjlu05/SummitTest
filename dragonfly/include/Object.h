#ifndef OBJECT_H
#define OBJECT_H

// System includes.
#include <string>

// Engine includes.
#include "Vector.h"
#include "Event.h"
#include "Animation.h"
#include "Box.h"

namespace df {
    enum Solidness {
        HARD,
        SOFT,
        SPECTRAL,
    };

    class Object {
    private:
        static int id_count;
        int m_altitude;
        int m_id;
        std::string m_type;
        Vector m_position;
        Vector m_direction;
        float m_speed;
        Solidness m_solidness; 
        bool m_outEventSent;
        Animation m_animation;  
        Box m_box;


    public:
        void setBox(Box new_box);
        Box getBox() const;

        bool isSolid() const;
        int setSolidness(Solidness new_solid);
        Solidness getSolidness() const;

        // Construct Object, set default parameters, and add to the game world.
        Object();

        // Destroy Object and remove it from the game world.
        virtual ~Object();
     

        // Set Object ID.
        void setId(int new_id);

        // Get Object ID.
        int getId() const;

        // Set type identifier of Object.
        void setType(std::string new_type);


        // Get type identifier of Object.
        std::string getType() const;

        // Set position of Object.
        void setPosition(Vector new_pos);

        // Get position of Object.
        Vector getPosition() const;

        // Handle event (default is to ignore everything).
        // Return 0 if ignored, else 1 if handled.
        virtual int eventHandler(const Event* p_e);
        int setAltitude(int new_altitude);
        int getAltitude() const;
        void setSpeed(float speed);
        float getSpeed() const;
        void setDirection(Vector new_direction);
        Vector getDirection() const;
        void setVelocity(Vector new_Velocity);
        Vector getVelocity();
        Vector predictPosition();


        bool getOutEventSent() const { return m_outEventSent; }
        void setOutEventSent(bool status) { m_outEventSent = status; }
        int setSprite(std::string sprite_label);
        void setAnimation(Animation new_animation);
        Animation getAnimation() const;
        virtual int draw();


    };  
}

#endif 
