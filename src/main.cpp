#include "Headers.hpp"
#include "App.hpp"
#include "Property.hpp"
#include "Resource.hpp"

/** AstroRush 2D game */
int main( int argc, char* argv[] ) {

  #ifdef DEBUG
    gWarring("Starting in debug mode");
  #endif

    App* app = new App();

    try {
      
	app->startSplash();
	
	// Implementacja timera animujacego splash
	while( ( !app->isSplashDone() ) ){ 
	  SDL_Delay( 20 ); // czas aktualizacji animacji
	  app->drawSplash();
	}
	
	// Zabezpieczenie w razie gdyby splash skonczyl sie wczesniej niz wczytywanie zasobow
	while( !app->isInitDone() ) SDL_Delay(10);
	  
        app->init();	
        app->endSplash();

        gInfo( Property::get("END_STARTING") );
        app->run();//Uruchomienie glownej petli programu

    }
    catch( char const* Error ){
       delete app;
       gCritical( Error );
       gSaveLogToFile();
       gCritical("Aplication terminated");
       return( EXIT_FAILURE );
    }
    catch( std::exception& e ) {
    	 delete app;
    	 gCritical( e.what() );
    	 gSaveLogToFile();
    	 gCritical("Aplication terminated");
    	 return( EXIT_FAILURE );
    }
    catch ( ... ) {
        delete app;
        gCritical("Unexcepted error");
        gSaveLogToFile();
        gCritical("Aplication terminated");
        return( EXIT_FAILURE );
    }

    delete app;
    gInfo(  Property::get("GAME_END_INFO") );
    gSaveLogToFile();
    return( EXIT_SUCCESS );

}
