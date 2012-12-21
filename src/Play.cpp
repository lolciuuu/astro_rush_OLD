#include "../include/Play.hpp"

/**
 * 
 */
Play::Play(): pIsCanStop( false ), pElapsedTime( 0.0f ),
pMap(),PLAYER_SLEEP_TIME( Property::getSetting("PLAYER_SLEEP_TIME") ),
PLAYER_SIZE( Property::getSetting("PLAYER_SIZE") ),
pCount( SpriteManager::getInstance().getSprite("COUNTING") )
{
	logger.setClassName( "PLay" );
    logger.info("Constructor class: PLAY");
    pCount.centered();
}


/** Aktualizacja gry
 */
void Play::update(const float& dt ){

	if( !LiveBar::isALive() ) return;

  /** @note Przez pierwsze kilka sekund po wybraniu 
      z menu glownego nowej gry zablokowana jest mozliwosc 
      wyjscia do menu. Wtedy na ekranie pojawia sie odliczanie 3,2,1..
      i wtedy hero zaczyna biec. Ponizszy if implementuje ta funkcjonalnosc */  
  if( !pIsCanStop ){ // Gdy gracz stoi w miejscu
 
    if( pElapsedTime > PLAYER_SLEEP_TIME ){ /// Poczatek biegu
      pIsCanStop = true;
      pPlayer.run();
      pMap.runMap();
    }
    else{ /// Aktualizacja stania gracza
      pElapsedTime += dt;
      pCount.update(dt);
    }
  }
  else { /// Gracz biegnie

    if( LiveBar::isALive() ) {
      pMap.update( dt );
      pPlayer.update( dt );  
      pLiveBar.update( dt );
   
      ColisionType type = pMap.checkColision( pPlayer.getPosX(), pPlayer.getPosY(), 50, 50 );
      if( type == ColisionType::EMPTY_COLISION ) { 
      /* ... */
      }
      else if(  type == ColisionType::STANDARD_BONUS ) {
    	  	  pHighScore.colision( type );
      }
      else if( type == ColisionType::STANDARD_COLISION  ) {
    	  	  pLiveBar.colision( type );
      }
      
    
    }
  }
  
}



/** Rysowanie ekranu gry */
void Play::draw(){

  if( LiveBar::isALive() ) {
  
      pRendererPtr->drawBackground( false );
    
      // MapManager rysuje mapy
      pMap.draw();
      
      // Klasa Player rysuje gracza
      pPlayer.draw();
      
      // Klasa LiveBar rysuje pasek zycie u gory
      pLiveBar.draw();    

      // Rysowanie odliczania
      if( !isCanStop() ) {
    	  	 pCount.draw();
      }
  }
  else {
      drawGameOverScreen();
  }
  
}

/** Rysowanie informacji o przegranej grze */
void Play::drawGameOverScreen() {

	pHighScore.draw();
    pWriterPtr->setFont("bold_big");

}
	
/** */
void Play::resetGame(){
  
  gInfo("Play: Creating New Game");
  pElapsedTime = 0.0f;
  pIsCanStop = false;
  pPlayer.reset();
  
  pMap.stopMap();
  pMap.reset(); 
  
  pLiveBar.reset();
  
  pCount.reset();
  
  LiveBar::resetMeter();
  

}

/** Podskakiwanie gracza */
void Play::jump() {
  //pPlayer.jump();
}



/**  */
void Play::SpaceDown() {
 
  pPlayer.SpaceDown();

}

/**  */
void Play::SpaceUp() {
 pPlayer.SpaceUp();     

}

