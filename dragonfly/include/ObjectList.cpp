#include "Object.h"
#include "Vector.h"
#include "ObjectList.h"
#include <string>
namespace df {


    // Constructor
    ObjectList::ObjectList() : m_count(0) {
    }

    // Return 0 if ok, else -1.
    int ObjectList::insert(df::Object* p_o) {
        if (m_count == MAX_OBJECTS)
            return -1;
        else {
            m_p_obj[m_count] = p_o;
            m_count++;
            return 0;
        }
    }

    // Remove object pointer from list.
    // Return 0 if found, else -1.
    int ObjectList::remove(Object* p_o) {
        for (int i = 0; i < m_count; i++) {
            if (m_p_obj[i] == p_o) {
                for (int j = i; j < m_count - 1; j++) {//as shown in the textbook, shift objects to the left 1
                    m_p_obj[j] = m_p_obj[j + 1];
                }
                m_count--;
                return 0;
            }
        }
        return -1;
    }

    // Clear list (setting count to 0).
    void ObjectList::clear() {
        m_count = 0;
    }

    // Return count of number of objects in list.
    int ObjectList::getCount() const {
        return m_count;
    }

    // Return true if list is empty, else false.
    bool ObjectList::isEmpty() const {
        return m_count == 0;
    }

    // Return true if list is full, else false.
    bool ObjectList::isFull() const {
        return m_count == MAX_OBJECTS;
    }

    // Index into list (access objects by index).
    Object* ObjectList::operator[](int index) const {
        if (index >= 0 && index < m_count) {
            return m_p_obj[index];
        }
        static Object* null = nullptr;//null point throw
        return null;
    }

}
