#include "../include/Highscore.hpp"
#include "App.hpp"

/** */
Highscore::Highscore()
{
  logger.setClassName( "Highscore" );
  logger.info("Load highscore file");

}

/** */
void Highscore::draw() {
    Rect where( 550,200,300,300 );
    SDL_Color color( {240,240,250} );

    pWriterPtr->draw(where,"GAME OVER", color);

    where.y += 40;

    pWriterPtr->draw(where, "Result: " + LiveBar::getResult() + "m", color );
}

/** */
void Highscore::show(){
    Property::get("HIGH_GAME_DIST");
    pWriterPtr->setFont("bold_big");
    Rect where({40,40,200,200});
    pWriterPtr->draw(where ,"HIGHSCORE" );
    
    pWriterPtr->setFont("bold_small");
  
}

/** */
void Highscore::colision( ColisionType type ) {
  #ifdef DEBUG  
    gInfo("Highscore colision");
  #endif
    LiveBar::increaseLive();
}
  

/** */
void Highscore::load() {
gInfo("Load highscore");
	fstream file;
	file.open("h", std::ios::in );

	if( file.is_open() ) {
		string name = "";
		string points = "";

		file>>name;
		file>>points;
		pList.push_back( HighscoreItem( name, points ) );
	}
	else {
		 logger.error("Highscore not found");
	}
}

/** */
void Highscore::save() {
  
}

