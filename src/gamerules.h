//  fonctions qui sont définies dans le header
bool pion_caneat(piece p, piece toeat);
bool can_move(piece p, piece * game, int x, int y, bool verify);
bool pion_movements(piece p, int x, int y);
bool cavalier_movements(piece p, int x, int y);
bool tour_movements(piece p, piece * game, int x, int y);
bool anyPieceInRoWY(int x, int y, int ymax, piece * game);
bool anyPieceInRoWX(int x, int y, int xmax, piece * game);
bool fou_movements(piece p, int x, int y, piece * game);
bool king_movements(piece p, int x, int y);
bool echec_color(piece * game, couleur col);
void getking(couleur col, piece * game, piece * p);
bool can_roque(piece p, piece * game, int x, int y);;
bool simule_and_checkpos(int x, int y, piece p, piece * game);
bool can_promote(piece p, piece * game, int x, int y);
