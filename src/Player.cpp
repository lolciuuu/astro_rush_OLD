#include "Player.hpp"
#include "SpriteManager.hpp"
#include "Property.hpp"
#include "App.hpp"


/** */
Player::Player():
  pRunSprite( SpriteManager::getInstance().getSprite("PLAYER_RUN") ),
  pStandSprite( SpriteManager::getInstance().getSprite("PLAYER_STAND") ),
  pFlySprite( SpriteManager::getInstance().getSprite("PLAYER_FLY") ),
  pState( PlayerState::Stand ),
  pCurrentSprite( &pStandSprite ),
  pX( Property::getSetting("PLAYER_OFFSET_X") ),
  pY( App::getScreenHeight() - Property::getSetting("PLAYER_OFFSET_Y") ),
  pJumpAllowed( true ),
  pSpeed( Property::getSetting("PLAYER_SPEED") ), pVY(0.0F), pAY(0.0F),
  PLAYER_Y_ACCELERATION( Property::getSetting("PLAYER_Y_ACCELERATION") ),
  PLAYER_Y_VELOCITY( Property::getSetting("PLAYER_Y_VELOCITY") ),
  PLAYER_MAX_Y_POS( Property::getSetting("PLAYER_MAX_Y_POS")  ),
  PLAYER_Y_OFFSET( Property::getSetting("PLAYER_OFFSET_Y") ),
  MAX_Y_PLAYER( App::getScreenHeight() -PLAYER_Y_OFFSET ),
  PLAYER_OFFSET_X( Property::getSetting("PLAYER_OFFSET_X") ),
  pIsFly( false ), logger("Player"), PLAYER_H( Property::getSetting("PLAYER_H") ),
  PLAYER_W( Property::getSetting("PLAYER_W") ),
  pMaxPlayerOnScreenX( pScreenWidth*0.5f )
{
	logger.methodStart("Player()");
    pStandSprite.setX( 300 );
    logger.methodEnd("Player()");
}


/** */
void Player::run(){
  pCurrentSprite = &pRunSprite;   
  pState = PlayerState::Run;
}


/** @REAL_TIME */
void Player::draw(){ 
  pCurrentSprite->draw( pX, pY, PLAYER_W, PLAYER_H );
}


/** @REAL_TIME */
void Player::update(const float& dt ){
 
  pCurrentSprite->update(dt);
 
  if( pIsFly ) {
      pVY = PLAYER_Y_VELOCITY;
      pAY = PLAYER_Y_ACCELERATION;  
      pCurrentSprite = &pFlySprite;
  }
  
  /** Polozenie w poziomie */
  if( pCurrentSprite != ( &pStandSprite ) ) {
     if( pX < ( LiveBar::getLiveAmount()*pMaxPlayerOnScreenX ) )
    	 pX += dt * pSpeed*.5;
     else if( pX > ( LiveBar::getLiveAmount()*pMaxPlayerOnScreenX ) && pX > PLAYER_OFFSET_X  )
    	 pX -= dt * pSpeed*.5;

  /** Polozenie w pionie */
  float nextY = pY + ( (pVY+pAY) * (dt) * 15);
    
    if( nextY > PLAYER_MAX_Y_POS && nextY < MAX_Y_PLAYER ) {
      pY = nextY;
    }
    else if( nextY >= MAX_Y_PLAYER ) { // gracz laduje na ziemi
      pCurrentSprite = &pRunSprite;
      pY = MAX_Y_PLAYER;      
    }
    
    pVY -= pAY * (dt*0.5);
    
  }
    
} 

/** */
void Player::reset(){
    logger.info("Player::reset() => Reseting hero");
    
    pCurrentSprite = &pStandSprite;
    pX = Property::getSetting("PLAYER_OFFSET_X");
    pY =  pScreenHeight - Property::getSetting("PLAYER_OFFSET_Y");
    
}

/** Obsluga podskakiwania gracza */
void Player::jump() {
  
  if( pCurrentSprite == &pStandSprite ) return; // gracz jeszcze nie zaczal biec

  pVY = PLAYER_Y_VELOCITY;
  pAY = PLAYER_Y_ACCELERATION;
  
  pCurrentSprite = &pFlySprite;
}

