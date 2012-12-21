--[[ cxx_addProperty(string klucz,string wartosc) -> w grze: string Property::get(string klucz);
     cxx_addSetting(string klucz,double wartosc) -> w grze: double Property::getSetting(string klucz); --]]



-- Sciezki do plikow
print("[ LUA ] Load files path");
cxx_addProperty("ATLAS_PATH" , "data/atlas.png");
cxx_addProperty("FONT_BOLD_PATH" , "data/ubuntu_bold.ttf");
cxx_addProperty("FONT_REGULAR_PATH" , "data/ubuntu_regular.ttf");
cxx_addProperty("FONT_MEDIUM_PATH" , "data/ubuntu_medium.ttf");

-- Czcionki
print( "[ LUA ] Loads font name" );
cxx_addSetting("SMALL_FONT", 0.3 );
cxx_addSetting("NORMAL_FONT", 18 );
cxx_addSetting("BIG_FONT", 22 );

-- Ustawienia aplikacji
print( "[ LUA ] Loading application settings" );
cxx_addSetting("TIME_STEP", 500/60 );
cxx_addSetting("ITEM_SPACE", 50 );

--Ustawienia playera
print( "[ LUA ] Loading player settings" );
TILES_VERTICAL=20;
cxx_addSetting("PLAYER_OFFSET_X", 100 );
cxx_addSetting("PLAYER_OFFSET_Y", (SCREEN_H/TILES_VERTICAL)*3 );
cxx_addSetting("PLAYER_SLEEP_TIME", 1  );
cxx_addSetting("PLAYER_SPEED", 200 );
cxx_addSetting("PLAYER_Y_ACCELERATION", -300.0 );
cxx_addSetting("PLAYER_Y_VELOCITY", 260 );
cxx_addSetting("PLAYER_MAX_Y_POS", 120 );
cxx_addSetting("PLAYER_SIZE", SCREEN_H/( (SCREEN_H/TILES_VERTICAL)*2) );

cxx_addSetting("PLAYER_W", ( (SCREEN_H/TILES_VERTICAL)) );
cxx_addSetting("PLAYER_H", ( (SCREEN_H/TILES_VERTICAL)*2) );

--Ustawienia mapy
print( "[ LUA ] Loading map settings" );
cxx_addSetting("MAP_LEVEL_1_SIZE", SCREEN_H/TILES_VERTICAL );
cxx_addSetting("MAP_LEVEL_1_SPEED", 1200 );
cxx_addSetting("LEVEL_VARIANTS", 39 );

-- Ustawienia HighScore
cxx_addSetting("HIGH_OFFSET_Y", 20 );

-- Ustawienia Menu
cxx_addSetting("MENU_SPRITE_SIZE", 220 );

