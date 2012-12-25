#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Headers.hpp"
#include "Sprite.hpp"
#include "Logger.hpp"
#include "StandardReferences.hpp"

class Player: StandardReferences
{
public:
    Player();
    void draw();
    void update(const float& dt,ColisionSide& side );
    void reset();
    void run();
    void jump();
    
    void fall();

    short getPosX() const { return( pX ); }
    short getPosY() const { return( pY ); }
    
    void SpaceUp() {   pIsFly = false; }
    void SpaceDown(){   pIsFly = true; }

    float getSize_X() const { return PLAYER_W; }
    float getSize_Y() const { return PLAYER_H; }

private:
    void roundY( bool down );

private:
  Sprite pRunSprite;
  Sprite pStandSprite;
  Sprite pFlySprite;
  PlayerState pState;
  Sprite* pCurrentSprite;
  
  short pX;
  short pY;

  bool pJumpAllowed;

  float pSpeed;
  float pVY;
  float pAY;
  
  // stale wczytane z zasobow
  const float PLAYER_Y_ACCELERATION;
  const float PLAYER_Y_VELOCITY;
  float PLAYER_MAX_Y_POS;
  const float PLAYER_Y_OFFSET;
  const float MAX_Y_PLAYER;
  const float PLAYER_OFFSET_X;
  
  bool pIsFly;

  Logger logger;

  const float PLAYER_H;
  const float PLAYER_W;

  float pMaxPlayerOnScreenX;

  float lastVY;
};

#endif // PLAYER_HPP
