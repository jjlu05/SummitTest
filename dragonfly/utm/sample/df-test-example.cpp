//
// df-test-example.cpp
//
// Example test suite for Dragonfly.
//

// System includes.
#include <errno.h>		// for errno
#include <stdlib.h>		// for atoi()
#include <string>		// for string
#include <string.h>		// for stringcmp(), strerror()
#include <unistd.h>		// for access(), sleep()

// Engine includes.
#include "Clock.h"
#include "GameManager.h"
#include "LogManager.h"

// Test includes.
#include "UnitTestManager.h"

// Individual tests.
bool testClock_deltaAndSplit(void);
bool testGameManager_getSetGameOver(void);
bool testLogManager_bytesWritten(void);
bool testManager_startStop(void);
bool testObject_setGetMethods(void);

// Location of logfiles.
#define LOG_DIR "log/";

// Support function prototypes.
void testSetup(void);
void testCleanup(void);
void testBefore(string test_name);
void testAfter(string test_name);

//////////////////////////////////////////////////////
// Main.

int main(int argc, char *argv[]) {

  // Check for correct number of arguments.
  if (argc != 2) {
    fprintf(stderr, "Usage: %s {all | number}\n", argv[0]);
    return -1;
  }

  ///////////////////////////////////////////////
  // Setup unit test manager.
  UnitTestManager &utm = UnitTestManager::getInstance();
  utm.setSetupFunc(&testSetup);
  utm.setCleanupFunc(&testCleanup);
  utm.setBeforeFunc(&testBefore);
  utm.setAfterFunc(&testAfter);
  
  ///////////////////////////////////////////////
  // Setup tests for Dragonfly.

  // Object.
  utm.registerTestFunction("testObject_setGetMethods",
			   &testObject_setGetMethods);

  // LogManager.
  utm.registerTestFunction("testLogManager_bytesWritten", 
			   &testLogManager_bytesWritten);

  // Manager.
  utm.registerTestFunction("testManager_startStop",
			   &testManager_startStop);

  // GameManager.
  utm.registerTestFunction("testGameManager_getSetGameOver",
			   &testGameManager_getSetGameOver);

  // Clock.
  utm.registerTestFunction("testClock_deltaAndSplit",
			   testClock_deltaAndSplit);

  ///////////////////////////////////////////////
  // Run tests.
  int passed;
  if (strcmp(argv[1], "all") == 0)
    passed = utm.run(UTM_ALL_TESTS);
  else
    passed = utm.run(atoi(argv[1]));

  ///////////////////////////////////////////////
  // Return number of tests passed.
  return passed;
}

//////////////////////////////////////////////////////
// Unit test setup functions.
//

// Setup conditions before all tests.
void testSetup(void) {

  // Remove log directory and everything inside.
  string command = "rm -rf ";
  command += LOG_DIR;
  if (system(command.c_str()) == -1) {
    fprintf(stderr, "Error calling system(%s): %s\n", 
	    command.c_str(), strerror(errno));
    exit(1);
  }

  // Re-create log directory.
  command = "mkdir ";
  command += LOG_DIR;
  if (system(command.c_str()) == -1) {
    fprintf(stderr, "Error calling system(%s): %s\n", 
	    command.c_str(), strerror(errno));
    exit(1);
  }
}

// Cleanup conditions after all tests.
void testCleanup(void) {
}

// Setup conditions before individual tests.
void testBefore(string test_name) {

  df::LogManager::getInstance().setLogLevel(20);

  // Start up the game manager.
  df::GameManager::getInstance().startUp();
  
  // Make sure LogManager flushes in case of crashes.
  df::LogManager::getInstance().setFlush(true);
}

// Cleanup conditions after individual tests.
void testAfter(string test_name) {

  // Shut down the game manager.
  df::GameManager::getInstance().shutDown();

  // If there is a Dragonfly logfile, rename it to be log/test_name.log.
  if (access("dragonfly.log", F_OK) != -1) {
    string new_name = LOG_DIR;
    new_name += test_name;
    new_name += ".log";
    if (rename("dragonfly.log", new_name.c_str()) == -1)
      fprintf(stderr, "testAfter(%s) rename() error: %s\n",
	      test_name.c_str(), strerror(errno));
  }
}

//////////////////////////////////////////////////////
// Individual tests.
//

// Clock
// Test that delta() and split() work appropriately.
// Note: only 1 second granularity.  Will want additional 
// tests with finer clock granularity.
bool testClock_deltaAndSplit(void) {
  df::LogManager &log_manager = df::LogManager::getInstance();

  // Make a clock object for testing.
  df::Clock clock;

  // Make calls to delta() and split().
  clock.delta();
  sleep(1);
  int t1 = (int) clock.split() / 1000000; // Should report about 1 second.
  sleep(1);			
  int t2 = (int) clock.split() / 1000000; // Should report about 2 seconds.
  int t3 = (int) clock.delta() / 1000000; // Should report about 2 seconds.
  sleep(1);
  int t4 = (int) clock.delta() / 1000000; // Should report about 1 second.

  // Print times to logfile for debugging.
  log_manager.writeLog("split time t1 is %d", t1);
  log_manager.writeLog("split time t2 is %d", t2);
  log_manager.writeLog("delta time t3 is %d", t3);
  log_manager.writeLog("delta time t4 is %d", t4);

  // See if all reported times are as expected.
  if (t1 != 1 || t2 !=2 || t3 != 2 || t4 != 1)
    return false;

  // If we get here, test has passed.
  log_manager.writeLog("%s passed.", __FUNCTION__);
  return true;
}

// GameManager
// Test get/set game over.
bool testGameManager_getSetGameOver(void) {
  df::LogManager &log_manager = df::LogManager::getInstance();
  df::GameManager &game_manager = df::GameManager::getInstance();

  // Default should be false.
  if (game_manager.getGameOver() != false) {
    log_manager.writeLog("%s failed. Default is not false.", __FUNCTION__);
    return false;
  }

  // Set game over.
  game_manager.setGameOver(true);
  if (game_manager.getGameOver() != true) {
    log_manager.writeLog("%s failed. Unable to set to true.", __FUNCTION__);
    return false;
  }

  // Can set it back.
  game_manager.setGameOver(false);
  if (game_manager.getGameOver() != false) {
    log_manager.writeLog("%s failed. Unable to set to false.", __FUNCTION__);
    return false;
  }
  
  // If we get here, the function has passed.
  log_manager.writeLog("%s passed.", __FUNCTION__);
  return true;
}

// LogManager
// Test that LogManager writeLog() reports correct number of bytes written.
bool testLogManager_bytesWritten(void) {
  df::LogManager &log_manager = df::LogManager::getInstance();

  if (log_manager.writeLog("1") != 1)
    return false;
  if (log_manager.writeLog("12345") != 5)
    return false;
  if (log_manager.writeLog("%s %d", "apple", 123) != 9)
    return false;

  // If we get here, test has passed.
  log_manager.writeLog("%s passed.", __FUNCTION__);
  return true;
}

// Manager
// Test can start and stop properly.
bool testManager_startStop(void) {
  df::LogManager &log_manager = df::LogManager::getInstance();

  // Manager to test.
  df::Manager m;

  // Should begin not-started.
  if (m.isStarted())
    return false;

  // Start it up.
  m.startUp();

  // Should now be started.
  if (!m.isStarted())
    return false;

  // Shut it down.
  m.shutDown();

  // Should now be stopped.
  if (m.isStarted())
    return false;

  // If we get here, test has passed.
  log_manager.writeLog("%s passed.", __FUNCTION__);
  return true;
}

// Object.
// Test set/get attributes.
bool testObject_setGetMethods(void) {
  df::LogManager &log_manager = df::LogManager::getInstance();

  // Create Object to test.
  df::Object *p_o;
  p_o = new df::Object;
  if (p_o == NULL)
    return false;

  // Check id.
  p_o -> setId(100);
  if (p_o -> getId() != 100)
    return false;
  
  // Check position.
  df::Position p1(2,4);
  p_o -> setPosition(p1);
  df::Position p2 = p_o -> getPosition();
  if (p1 != p2)
    return false;

  // Check type.
  p_o -> setType("pizza");
  if (p_o -> getType() != "pizza")
    return false;

  // If we get here, test has passed.
  log_manager.writeLog("%s passed.", __FUNCTION__);
  return true;
}
