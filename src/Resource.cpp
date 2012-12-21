#include "Resource.hpp"
#include "Property.hpp"
#include "Property.hpp"
#include "MapManager.hpp"
#include <App.hpp>

/// Inicjowanie zmiennych statycznych
map< string,SDL_Surface* >  Resource::pSurfaces;
map< string,TTF_Font* >  Resource::pFonts;
/// END


/** W razie niepowodzenia wczytania czcionki wyswietlanie informacji
 * i rzucenie wyjatku
 */
void Resource::fontError() {

    gCritical("Brak czcionki");
    gCritical( TTF_GetError() );
    throw("Resource:load");

}


/**
 *
 */
void Resource::load() {

    atexit( clearResource );

    loadImages();
    loadFonts();

    // wczytanie map
    MapManager::load();
}

/** Wczytywane w osobnym watku podczas startu aplikacji */
void Resource::loadImages() {
   
  /** TODO W razie nowych pozycji, przerobic na osobna metode */
  
    // Atlas spritow
    SDL_Surface* atlas = IMG_Load("data/pic/atlas.png");
    if ( atlas == NULL ) {
        gCritical("Atlas file not found");
        throw("Resource::load");
    }
    pSurfaces.insert( std::pair<string,SDL_Surface*>( "ATLAS",atlas ) );
    
    
    // Tlo w grze
    SDL_Surface* background = IMG_Load("data/pic/background.jpg");
    if( background == NULL ) {
       gCritical("Background file not found");
       throw("Resource::load");
    }
      else {
    //  SDL_Rect dest = SDL_Rect({0,0,App::getScreenWidth(),App::getScreenHeight()});
   //   SDL_SoftStretch(background, NULL, background, &dest);
      pSurfaces.insert( std::pair<string,SDL_Surface*>( "BACKGROUND_MAP",background ) );
    }   
    
    //
    SDL_Surface* menuTitle = IMG_Load("data/pic/menu_background.jpg");
    if( background == NULL ) {
       gCritical("Menu_title file not found");
       throw("Resource::load");
    }
  
    pSurfaces.insert( std::pair<string,SDL_Surface*>( "MENU_BACKGROUND",menuTitle ) );
    
 
}

void Resource::loadFonts() {

    //bold small
    {
        TTF_Font* font = TTF_OpenFont(
                             Property::get("FONT_BOLD_PATH").c_str(),
                             Property::getSetting("SMALL_FONT")
                         );

        if ( font == NULL )  Resource().fontError();
        pFonts.insert( std::pair<string,TTF_Font*>( "bold_small",font ));
    }

    //bold normal
    {
        TTF_Font* font = TTF_OpenFont(
                             Property::get("FONT_BOLD_PATH").c_str(),
                             Property::getSetting("NORMAL_FONT")
                         );

        if ( font == NULL )  Resource().fontError();
        pFonts.insert( std::pair<string,TTF_Font*>( "bold",font ));
    }

    //bold big
    {
        TTF_Font* font = TTF_OpenFont(
                             Property::get("FONT_BOLD_PATH").c_str(),
                             Property::getSetting("BIG_FONT")
                         );

        if ( font == NULL )  Resource().fontError();
        pFonts.insert( std::pair<string,TTF_Font*>( "bold_big",font ));
    }

    ///@TODO dodac reszte czcionek

}


/** statyczny deskrtuktor- wylacza zaladowane w load moduly i czysci pamiec  */
void Resource::clearResource() {
    /// @TODO Zwlanianie z pamieci wszystkich fontow
}


/** Metoda wyszukuje w tablicy asocjacyjnej fontu o podanej
 *  nazwie i zwraca wskaznik do niego
 */
TTF_Font* Resource::getFont(string name) {

    if (containsFont( name ) ) {
        return pFonts.find( name )->second;
    }
    else
    {
        gError(name + ":Not found font" );
        throw("Resource::getFont");
    }

}

/** Metoda zwraca adres powierchni przechowywanej w pamieci. Powierzchnie sa 
 *  wypelnione wczytanymi obrazkami.
 * @throw const char* : nazwa metody
 */
SDL_Surface* Resource::getSurf( string Name ){
  
  if(  containsSurf(Name) ){
    return pSurfaces.find( Name )->second;
  }
  else{
    gError(Name + ":Not found surfaces" );
    throw(string("Resource::getSurf")); 
  }
  
}


