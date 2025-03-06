//
// GameStart.h
//

#include "Music.h"
#include "ViewObject.h"
#include "Object.h"
//Object instead of ViewObject
class GameStart : public df::Object {

 private:
  df::Music *p_music;
  df::Music *wind;
  void start();
  
 public:
	 bool started();
  GameStart();
  int eventHandler(const df::Event *p_e);
  int draw();
  void playMusic();
};
