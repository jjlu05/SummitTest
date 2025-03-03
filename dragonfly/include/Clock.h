#include <Windows.h>
namespace df {

    class Clock {
    private:
        long int m_previous_time;

    public:
        // Sets previous time to current time.
        Clock();

        // Return time elapsed since delta() was last called, -1 if error.
        // Resets previous time.
        // Units are microseconds.
        long int delta();
        SYSTEMTIME before_st, after_st;

        long int test = 0;
        // Return time elapsed since delta() was last called, -1 if error.
        // Does not reset previous time.
        // Units are microseconds.
        long int split() const;
    };
}
