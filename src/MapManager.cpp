#include "MapManager.hpp"
#include "Sprite.hpp"
#include "SpriteManager.hpp"
#include "App.hpp"


// Blok inicjowania zmiennych statycznych
Map *MapManager::pMapMain;
vector<Rect> MapManager::pMap_rects;
uint MapManager::LEVEL_VARIANTS;

/** Tworzy tablice w ktorej znajduja sie wszystkie mozliwe wersje kafelkow mapy */
MapManager::MapManager(): pIsRunMap( false )
{
    gInfo("Constructor class: MapManager");
    LEVEL_VARIANTS = (uint)Property::getSetting("LEVEL_VARIANTS");

    for(uint i = 0; i <= LEVEL_VARIANTS; ++i) {
        std::ostringstream ss;
        ss << i;
        string ID(ss.str());
        Sprite spriteTmp = SpriteManager::getInstance().getSprite("MAP_" + ID);
        pMap_rects.push_back(spriteTmp.getRect());
    }
    
    pMapMain->enableCheckColision();
  
}

/** */
void MapManager::update(const float& dt)
{
  if( pIsRunMap == false ) return;
    pMapMain->update( dt );
    if( pMapMain->nextMeter() ) LiveBar::nextMeter();
}


/** */
void MapManager::draw()
{
    pMapMain->draw();
}

/** Metoda wczytuje mape do tablicy dwuwymiarowej,
 * levelNo - ID mapy w ustawieniach, potrzebny do okreslenia rozmiaru kafelka
 */
Map* MapManager::loadMapFromFile(string fileName,short levelNo) {
  
    Map* result;
    std::fstream mapFile;
    mapFile.open( fileName.c_str(), std::ios::in);

    uint row(0);
    uint column(0);

    if(mapFile.is_open()) {

        gInfo("Loading main map");

        // pobranie wymiarow mapy
        mapFile >> row;
        mapFile >> column;

        short **map = new short*[column];
        for(uint i = 0; i < column; ++i)
            map[i] = new short[row];

        // wczytanie mapy
        vector< vector<short> > map1;
        for(uint i = 0; i < row; ++i) {
            vector<short> v_tmp;
            for(uint j = 0; j < column; ++j) {
                short shortTmp;
                mapFile >> shortTmp;
		
                map[j][i] = shortTmp;
            }
        }

        string settingsName( "MAP_LEVEL_" + toString<short>(levelNo) + "_SIZE" );
        result = new Map( map,(int)Property::getSetting(settingsName),row,column);

        mapFile.close();
        return( result );
	
    }
    else {
      gCritical("Can`t open file: " + fileName );
      throw("MapManager::loadMapFromFile");
    }
}

/** Wczytanie wszystkich map. Metoda wolana podczas ladowania zasobow, poza glownym watkiem */
void MapManager::load()
{
  pMapMain = loadMapFromFile( "data/level.lua", 1 );  
  pMapMain->setSpeed( Property::getSetting("MAP_LEVEL_1_SPEED") );
}

/** */
void MapManager::reset() {
  pMapMain->reset();
  
  

}

/** */ 
short MapManager::checkColision(short Player_x, short Player_y, ColisionSide& cSide ) {

	//cSide.up = pMapMain->isAnyPlatformAbove( Player_x, Player_y-2 );
	//cSide.down = pMapMain->isAnyPlatformBelow( Player_x, Player_y );

   return( pMapMain->checkColision( Player_x, Player_y, cSide ) );
}


