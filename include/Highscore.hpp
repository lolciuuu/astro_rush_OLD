#ifndef HIGHSCORE_HPP
#define HIGHSCORE_HPP

#include "Headers.hpp"
#include "ColisionType.hpp"
#include "StandardReferences.hpp"

class Highscore: StandardReferences
{
public:
  Highscore();
  
  void show();
  
  void colision( ColisionType type );
  
  void load();
  
  void save();
  
  void draw();

private:
  
private:
  
  struct HighscoreItem {
    string name;
    string distance;
    string points;

    HighscoreItem( string n, string d, string p = "" ) :
    			  name( n ), distance( d ), points( p )
    			  {}
  };

  vector<HighscoreItem> pList;
  

 
};

#endif // HIGHSCORE_HPP
