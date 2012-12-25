#ifndef PLAY_HPP
#define PLAY_HPP

#include "Player.hpp"
#include "MapManager.hpp"
#include "Highscore.hpp"
#include "LiveBar.hpp"
#include "SpriteManager.hpp"
#include "StandardReferences.hpp"

/** Obsluga taki jednostek jak: mapa, gracz, pasek zycia, highscore...stan gry*/
class Play: StandardReferences {
public:
    Play();
    void resetGame();
    
    void update (const float& dt );
    void draw();
    
    bool isCanStop() const { return( pIsCanStop ); } // czy mozna wyjsc z gry do menu
    void jump();
    
    void SpaceUp();
    void SpaceDown();
  
    void pressedShift();
    
private:
    void drawGameOverScreen();

private:
    Player pPlayer;
    
    bool pIsCanStop;
    float pElapsedTime;
    
    MapManager pMap;
    Highscore pHighScore;
    LiveBar pLiveBar;
    
    float PLAYER_SLEEP_TIME;
    ushort PLAYER_SIZE;
    
    Sprite pCount;
    

};

#endif // PLAY_HPP
