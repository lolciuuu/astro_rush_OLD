/** Plik zawiera funkcje globalne inline, ktore pelnia role pomocnicze,
 *  i sa one dostepne w calym systemie.
 */

#ifndef GLOBFUN_HPP
#define GLOBFUN_HPP
#include "Headers.hpp"


//#define LINUX


/// @note zmienna statyczna globalna przechowuje logi zbierane podczas pracy aplikacji
static string LOGI("");

/** Metoda wyswietla w konsoli informacje.
 * Podana jako parametr informacja to log systemu.
 * @warning Dziala tylko w trybie DEBUG. 
 * @warning jezeli zdefiniowana jest flaga LINUX, wtedy naglowek informacji jest kolorowany
 *
 * @deprecated
*/
inline void gInfo( const string& t ) {

#ifdef DEBUG
    cout<<
#ifdef LINUX
        "[ \033[1;36mInfo\033[0m ] "
#else
        "[ Info ] "
#endif
        << t <<endl;
#endif
	// Dodanie do logow zapisywanych do pliku
	LOGI += "[ Info ] ";
	LOGI += t;
	LOGI +='\n';
}

/** */
inline bool isPlatform( short ID ) {
	if( ID == 39 ) return true;
	return false;
}

/** */
inline bool isBonus( short ID ) {
	if( ID == 38 || ID ==  37 ) return true;
	return false;
}

/** Metoda wyswietla w konsoli informacje.
 * Podana jako parametr informacja to ostrzezenie.
 */
inline void gWarring ( const string& Text ) {
    cerr<<
#ifdef LINUX
        "[ \033[1;33mWarning\033[0m ] "
#else
        "[ Warning ] "
#endif
        << Text <<endl;
		
	// Dodanie do logow zapisywanych do pliku
	LOGI += "[ Warning ] ";
	LOGI += Text;
	LOGI +='\n';
}


/** Metoda wyswietla w konsoli informacje.
* Podana jako parametr informacja to informacja o bledzie.
*/
inline void gError ( const string& Text ) {
    cerr<<
#ifdef LINUX
        "[ \033[1;33mError\033[0m ] "
#else
        "[ Error ] "
#endif
        << Text <<endl;
	
	// Dodanie do logow zapisywanych do pliku
	LOGI += "[ Error ] ";
	LOGI += Text;
	LOGI +='\n';
}

/** */
inline void gStartMethod( string name ) {
	gInfo( name + "| start" );
}

inline void gEndMethod( string name ) {
	gInfo( name + "| end" );
}

/** Metoda wyswietla w konsoli informacje.
* Podana jako parametr informacja to informacja o bledzie krytycznym.
*/
inline void gCritical ( const string& Text ) {
    cerr<<
#ifdef LINUX
        "[ \033[1;33mCritical\033[0m ] "
#else
        "[ Critical ] "
#endif
        << Text <<endl;
	
	// Dodanie do logow zapisywanych do pliku
	LOGI += "[ Critical ] ";
	LOGI += Text;
	LOGI +='\n';
}

/** Metoda odczytuje kod jezyka jaki ma byc ustawiony w grze i zwraca go jako
 *  string. W razie problemow ze znalezieniem pliku zwraca informacje ze jezykiem
 *  w grze jest angielski.
 */
inline string gLoadLanguages() {

    fstream langFile ( "data/lang" , std::ios::in );

    if ( langFile.is_open() ) {

        char bufor[ 1024 ]={ '\0' };
        langFile.getline ( bufor,1023 );
        langFile.close();
        return( string ( bufor ) );

    }
    else return( "ANG" );

}


/** Funkcja zapisuje zebrane logi do pliku ConsoleOut.log,
 *  w razie problemow z otwarciem pliku na konsole idzie komunikat
 */
inline void gSaveLogToFile(){
  /*
  std::fstream log;
  log.open("ConsoleOut.log", std::ios::out );
  
  if( log.is_open() ){
      log<<LOGI;
      log.close();
  }
  else gCritical("Can`t save log!");
  */
}

/** Zamienia liczbe na string */
template <typename T>
inline string toString( T number ) {
  std::ostringstream ss;
  ss<<number;
  return( ss.str() );
}

/** Drukuje na ekranie info o SDL_Rect oraz jego nazwe podana jako parametr */
inline void gPrintRect( const string& Name, Rect& rect ) {
  gInfo( "Rect:\"" + Name +"\"\n"
	+ "\tX: " + toString<Sint16>(rect.x)
	+ " | Y: " + toString<Sint16>(rect.y)
	+ " | W: " + toString<Uint16>(rect.w)
	+ " | H: " + toString<Uint16>(rect.h) );
}
#endif
