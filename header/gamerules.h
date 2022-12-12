#ifndef GAMERULES_H
#define GAMERULES_H
#include "../header/graphics.h"

bool pion_caneat(piece p, piece toeat);
bool can_moove(piece p, piece* game, int x, int y);
bool pion_moovements(piece p, int x, int y);
bool cavalier_moovements(piece p, int x, int y);
bool tour_moovements(piece p,piece* game, int x, int y);
bool anyPieceInRoWY(int x, int y, int ymax, piece* game);
bool anyPieceInRoWX(int x, int y, int xmax, piece* game);
#endif