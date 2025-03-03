//Clock.cpp
#include <Windows.h>  

#include "Clock.h"
#include <iostream>

namespace df {


    Clock::Clock() : m_previous_time(0) {

        GetSystemTime(&before_st);

    }

    long int Clock::delta() {
        GetSystemTime(&after_st);

        long int before_msec = (before_st.wDay * 24 * 60 * 60 * 1000 * 1000)
            + (before_st.wHour * 60 * 60 * 1000 * 1000)
            + (before_st.wMinute * 60 * 1000 * 1000)
            + (before_st.wSecond * 1000 * 1000)
            + (before_st.wMilliseconds * 1000);

        long int after_msec = (after_st.wDay * 24 * 60 * 60 * 1000 * 1000)
            + (after_st.wHour * 60 * 60 * 1000 * 1000)
            + (after_st.wMinute * 60 * 1000 * 1000)
            + (after_st.wSecond * 1000 * 1000)
            + (after_st.wMilliseconds * 1000);

        m_previous_time = after_msec;
        before_st = after_st;
        test = after_msec;
        return after_msec - before_msec;
    }
    long int Clock::split() const {
        SYSTEMTIME current_time;
        GetSystemTime(&current_time);

        long int after_msec = (current_time.wDay * 24 * 60 * 60 * 1000 * 1000)
            + (current_time.wHour * 60 * 60 * 1000 * 1000)
            + (current_time.wMinute * 60 * 1000 * 1000)
            + (current_time.wSecond * 1000 * 1000)
            + (current_time.wMilliseconds * 1000);

        return after_msec - m_previous_time;
    }


}