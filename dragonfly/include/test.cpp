
//this file can be ignored, I was testing how to store tests on a file.


#include <cassert>
#include "LogManager.h"

void testLogManager_startupShutdown() {
    df::LogManager& logManager = df::LogManager::getInstance();

    assert(logManager.startUp() == 0);   
    logManager.shutDown();               
}

// Test writing to log
void testLogManager_writeLog() {
    df::LogManager& logManager = df::LogManager::getInstance();
    logManager.startUp();

    int bytes_written = logManager.writeLog("Test log entry.\n");
    assert(bytes_written > 0);   

    logManager.shutDown();
}

 int main() {
    testLogManager_startupShutdown();
    testLogManager_writeLog();

    printf("All tests passed!\n");
    return 0;
}
