#include "Map.hpp"
#include "App.hpp"

/** */
Map::Map(short **M, ushort EntitySize, uint R, uint C) :
    pMap(M), pos_X(0), pos_Y(0), pOffset_X(0), pOffset_Y(0),
    pSize(EntitySize), rows(R), columns(C), pSpeed(0.0F),   pCheckColision(false),
    pNextMeter( 0 ), pR(R), pC(C), pPlayer_x( 0 ), pPlayer_y( 0 ), pPlayer_sx( 0 ),
    pPlayer_sy( 0 ), logger("Map")
{

    // Obliczanie ile fragmentow mapy miesci sie na ekranie
    pAmountEntityHorizontal = (App::getScreenWidth() / EntitySize) + 1;
    pAmountEntityVertical = (App::getScreenHeight() / EntitySize) + 1;
    
    while( pAmountEntityVertical > R ) {
       --pAmountEntityVertical;
    }

    logger.info("Entity size:" + toString(EntitySize));
    logger.info("Vertical amount of ground:" + toString(pAmountEntityVertical));
    logger.info("Horizontal amount of ground:" + toString(pAmountEntityHorizontal));
        
    itWasReturn =  vector < vector<bool> >( C, vector<bool>( R,false) );
    drawID = new vector < vector<bool> >( pC, vector<bool>( pR,true) );
        
}

/** Sciaga ze stosu ostatni element na ktorym wykryto kolizje */
short Map::checkColision(short Player_x, short Player_y, short Player_sx , short Player_sy)
{
    pPlayer_x = Player_x;
    pPlayer_y = Player_y;
    pPlayer_sy = Player_sy;
    pPlayer_sx = Player_sx;

    if(pColisionStack.size() > 0) {
      Point point = pColisionStack.top();
      pColisionStack.pop();
	
	short X = point.X;
	short Y = point.Y;

      if( !itWasReturn[ X][ Y ] ) {
	   itWasReturn[ X ][ Y ] = true;
	    
	    
	  if( pMap[X][Y] > 20 ) {
	    drawID->at(X)[Y] = false;
	    LiveBar::increaseLive(); 
	  }
	  else if( pMap[X][Y] == -1 ) {}
	  else {
	   LiveBar::colision( ColisionType::STANDARD_COLISION ); 
	  }
	   
           return( pMap[ X ][ Y ] );
      }
   }
    
    return( -1 );
}

/** */
void Map::draw()
{

    register uint currentX = pos_X;
    register uint currentY = pos_Y;

    for(uint x = 0; x <= pAmountEntityHorizontal+1U; ++x, ++currentX) {

        for(uint y = 1; y <= pAmountEntityVertical; ++y, --currentY) {

            short ID = pMap[ x + pos_X ][ rows - y ];

            if(ID == -1 || ( drawID->at( x+pos_X)) [ rows - y ] != true )
            	continue;   // -1 oznacza brak kafla na mapie

            float des_x = (float)(x * pSize) - float(pOffset_X);

            float des_y = ( App::getScreenHeight() - (y * pSize)) ;

            Rect src(MapManager::getRectByID(ID));
            src.h = 50;
            src.w = 50;
			pRendererPtr->draw(src, des_x, des_y, pSize, pSize );

             /// wykrywania kolizji
            if(pCheckColision) {

                if( !(pPlayer_x > (des_x + pSize) || pPlayer_x + pPlayer_sx < des_x || pPlayer_y + pPlayer_sy < des_y || pPlayer_y > des_y + pSize ) )
                {
                    short xTmp = x + pos_X;
                    short yTmp = rows - y;

                    // Zapisanie na stosie ID elementu z ktorym wykryto kolizje
                     pColisionStack.push( Point(xTmp, yTmp) );
                }
            } // END wykrywania kolizji

         }
      }
    }

/** Obliczenie przesuniecie, i ewentulnie przesuniecie pierwszej kolumny macierzy */
void Map::update(const float& dt) {

  pOffset_X += (float)pSpeed  * dt;

 if(pOffset_X > pSize) {
      pOffset_X -= pSize;
      ++pos_X;
	  ++pNextMeter;
  }

}

/** Ustawienie bierzacej kolumny i wiersza na poczatek macierzy mapy */
void Map::reset() {
   pos_X = 0;
   pos_Y = 0;
   logger.info("Reseting main map");

   delete drawID;
   drawID = new  vector < vector<bool> >( pC, vector<bool>( pR,true) );
   itWasReturn =  vector < vector<bool> >( pC, vector<bool>( pR,false) );
   SDL_Delay( 0 );
}




