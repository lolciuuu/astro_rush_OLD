#ifndef COLISIONTYPE_HPP
#define COLISIONTYPE_HPP

// Kolizje ktore sa powyzej tej wartosci sa przetwarzane przez highScore
// Kolizje o mniejszej wartosci sa przetwarzane przez LiveBar
const ushort COLISION_BASE = 1000;

enum ColisionType {
  // brak kolizji
  EMPTY_COLISION = 0,
  
  // Kolizje z przeszkodami
  STANDARD_COLISION = 1,
  
  // Bonusy
  STANDARD_BONUS = 1001
  
};

#endif