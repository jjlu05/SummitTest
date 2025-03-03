// The log file manager.

#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__
#define LM df::LogManager::getInstance()

 #include <stdio.h>

 #include "Manager.h"

namespace df {

    const std::string LOGFILE_NAME = "dragonfly.log";

    class LogManager : public Manager {

    private:
        LogManager(); 
        LogManager(LogManager const&);  
        void operator=(LogManager const&); 
        bool m_do_flush;  
        FILE* m_p_f;  

    public:
        // If log file is open, close it.
        ~LogManager();

        // Get the one and only instance of the LogManager.
        static LogManager& getInstance();

        // Start up the LogManager (open log file "dragonfly.log").
        int startUp();

        // Shut down the LogManager (close log file).
        void shutDown();

        // Set flush of log file after each write.
        void setFlush(bool do_flush = true);

        // Write to log file. Supports printf() formatting of strings.
        // Returns number of bytes written, -1 if error.
        int writeLog(const char* fmt, ...) const;
    };

} 

#endif  
