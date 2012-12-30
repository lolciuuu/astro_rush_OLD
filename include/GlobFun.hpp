/** Plik zawiera funkcje globalne inline, ktore pelnia role pomocnicze,
 *  i sa one dostepne w calym systemie.
 */

#ifndef GLOBFUN_HPP
#define GLOBFUN_HPP
#include "Headers.hpp"


//#define LINUX


/// @note zmienna statyczna globalna przechowuje logi zbierane podczas pracy aplikacji
static string LOGI("");

//@TODO dopisac komentarz
//@TODO zrobic na szablonie, wywalic info,
//@TODO dodac argv - zmienna liczbe parametrow!!
inline void info( const string& t ) {
    cout<<"[ Info ] "<< t <<endl;
}

//@TODO dopisac komentarz
//@TODO zrobic na szablonie, wywalic info,
//@TODO dodac argv - zmienna liczbe parametrow!!
inline void debug( const string& t ) {
#ifdef DEBUG
    cout<<"[ Debug ] "<< t <<endl;
#endif
}


/** */
inline bool isPlatform( short ID ) {
	if( ID == 39 ) return true;
	return false;
}

/** */
inline bool isBonus( const short& ID ) {
	if( ID == 38 || ID ==  37 ) return true;
	return false;
}

/** */
inline bool isAdditionalBonus( const short& ID ) {
	if( ID == 41 ) return true;
	return false;
}

/** */
inline bool isEnemy( const short& ID ) {
	if( ID == 40 ) return true;
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
	info( name + "| start" );
}

inline void gEndMethod( string name ) {
	info( name + "| end" );
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


/** Zamienia liczbe na string */
//@TODO sprawdzanie czy podano liczbe?
template <typename T>
inline string toString( T number ) {
  std::ostringstream ss;
  ss<<number;
  return( ss.str() );
}

/** Drukuje na ekranie info o SDL_Rect oraz jego nazwe podana jako parametr */
inline void gPrintRect( const string& Name, Rect& rect ) {
  info( "Rect:\"" + Name +"\"\n"
	+ "\tX: " + toString<Sint16>(rect.x)
	+ " | Y: " + toString<Sint16>(rect.y)
	+ " | W: " + toString<Uint16>(rect.w)
	+ " | H: " + toString<Uint16>(rect.h) );
}
#endif
