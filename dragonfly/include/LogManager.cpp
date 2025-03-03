// LogManager.cpp

#include "LogManager.h"
#include <stdarg.h>
#include <ctime>
#include <cstring>
#include <iostream>
#include <fstream>

namespace df {//the only manager I used namspace df for, I forgot for the other ones

    LogManager::LogManager() : m_p_f(nullptr), m_do_flush(false) {}

    LogManager::~LogManager() {
        if (m_p_f) {
            fclose(m_p_f);//close the opened file path
        }
    }

    LogManager& LogManager::getInstance() {//single instance
        static LogManager instance;  
        return instance;
    }

    int LogManager::startUp() {
        if (fopen_s(&m_p_f, LOGFILE_NAME.c_str(), "a") != 0 || !m_p_f) {
            std::cerr << "Error opening log file, try again!" << std::endl;
            return -1;
        }

        writeLog("LogManager started.\n");

        return 0;  
    }

    void LogManager::shutDown() {
         writeLog("LogManager shutting down.\n");

         if (m_p_f) {
            fclose(m_p_f);
            m_p_f = nullptr;
        }
    }

    void LogManager::setFlush(bool do_flush) {
        m_do_flush = do_flush;
    }

    int LogManager::writeLog(const char* fmt, ...) const {
        if (!m_p_f) {
            std::cerr << "Log file is not open!" << std::endl;
            return -1; 
        }

        va_list args;
        va_start(args, fmt);

        //create a buffer to store the formatted message
        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), fmt, args);  // format

        va_end(args);

        //write the formatted message as string
        int bytes_written = fprintf(m_p_f, "%s", buffer);

        if (m_do_flush) {
            fflush(m_p_f);   
        }

        return bytes_written;  //return the number of bytes written or -1 if an error occurred
    }

} 
