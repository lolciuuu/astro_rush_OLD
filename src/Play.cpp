#include "../include/Play.hpp"


void Play::pressedShift() {
	pPlayer.fall();
}

/**
 * 
 */
Play::Play(): pIsCanStop( false ), pElapsedTime( 0.0f ),
pMap(),PLAYER_SLEEP_TIME( Property::getSetting("PLAYER_SLEEP_TIME") ),
PLAYER_SIZE( Property::getSetting("PLAYER_SIZE") ), pEnemyManager( EnemyManager::getInstance() ),
pCount( SpriteManager::getInstance()->getSprite("COUNTING") )
{
	logger.setClassName( "PLay" );
    logger.info("Constructor class: PLAY");
    pCount.centered();
}

Play::~Play() {
	delete pEnemyManager;
}

/** zapisanie highscore */
void Play::goToMenu() {
	if( ! LiveBar::isALive() )
		pHighScore.save();
}

/** Wpisywanie swojego imienia w przypadku kiedy bohater umarl */
void Play::pressedChar(char Char) {

	if( !  LiveBar::isALive() ) {
		pHighScore.pressedChar( Char );
	}

}

void Play::pressedBackspace() {
	if( ! LiveBar::isALive() )
		pHighScore.pressedBackspace();
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
      pLiveBar.update( dt );

      pEnemyManager->update( dt );
   
      ColisionSide cSide;
      //@TODO optymalizacja
      /** Parametr cSide przekazuje informacje do playera z ktorej strony wystepuje kolizja z platforma */
     short type = pMap.checkColision( pPlayer.getPosX(), pPlayer.getPosY(), cSide );

     if( type != -1 ) {

    	  if( isBonus( type ) ) {
    	 	  pHighScore.colision( type );
    	  }
    	  else if( !isPlatform( type ) ){
    		  pLiveBar.colision( type );
    	  }
      }// type != -1

     if( pEnemyManager->isColidate( Rect( pPlayer.getPosX(), pPlayer.getPosY(), pPlayer.getSize_X(), pPlayer.getSize_Y() ) ) ) {

    	 if( pPlayer.isColisionWithEnemy() ) {
 	     	 pLiveBar.colision( COLISION_WITH_ENEMY ); //@TODO zastapic stala
    		 pPlayer.disableEnemyDetect();
    	 }
     }

      pPlayer.update( dt, cSide );
    
    }
  }
  
}

/** Rysowanie ekranu gry */
void Play::draw(){

  if( LiveBar::isALive() ) {
  
      pRendererPtr->drawBackground( false );
    
      // MapManager rysuje mapy
      pMap.draw();
      
      // rysowanie przeciwnikow na mapie
      pEnemyManager->draw();

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
		pHighScore.draw();
  }
  
}
	
/** */
void Play::resetGame(){
  
  logger.info("Play: Creating New Game");
  pElapsedTime = 0.0f;
  pIsCanStop = false;
  pPlayer.reset();
  
  pMap.stopMap();
  
  pMap.reset();
  pLiveBar.reset();
  pCount.reset();
  pEnemyManager->reset();
  
  LiveBar::resetMeter();

}

/**  */
void Play::SpaceDown() {
 if( !LiveBar::isALive() )
	 pHighScore.pressedChar( ' ' );
 else
	 pPlayer.SpaceDown();
}

/**  */
void Play::SpaceUp() {
 pPlayer.SpaceUp();     

}

