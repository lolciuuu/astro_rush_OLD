#ifndef LIVEBAR_HPP
#define LIVEBAR_HPP
#include "Headers.hpp"
#include "Renderer.hpp"
#include "Writer.hpp"
#include "StandardReferences.hpp"
#include "Const.hpp"

class LiveBar: public StandardReferences {
public:
  LiveBar();  
  
  void reset();
  
  void draw();
  
  void update(const float& dt );
  
  void addBonus(){
	  if( pBonusAmount < 3 ) {
	  	  ++pBonusAmount;
	  }
  }

  static Uint32 disableImmortal_callbackTimer(Uint32 interval, void *param);

  bool useBonus();

  static bool isALive() {
		#ifndef IMMORTAL
	  	  	  if( pLiveAmount <= 0.0 ) {
	  	  		  isLive = false;
	  	  		  info("Player is dead");
	  	  		  return( isLive );
	  	  	  }
		#else
	  	  	  return true;
		#endif
  }
  
  static void colision( short type );
  static void increaseLive();
  
  static string getResult() { return( toString<ulong>(pDistNum) ); }
  
  static float getLiveAmount() { return pLiveAmount; }
  static float getMapSpeed() { return pMapSpeed; }
  
  static void nextMeter() { ++pDistNum; }
  static void resetMeter() { pDistNum = 0; } /// @TODO Zapisanie wyniku
  
private:
  static bool isLive;
  static float pLiveAmount;
  
  Rect pDistanceRect;
  string pDistStr;
  static ulong pDistNum;
  static float pMapSpeed;
  
  ushort pBonusAmount;

  static bool isImmortal;
  SDL_TimerID timer;

};
#endif
