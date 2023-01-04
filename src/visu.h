typedef enum type {
  PION, TOUR, CAVALIER, FOU, REINE, ROI, NONE
} type;

typedef enum couleur {
  NOIR, BLANC
} couleur;

typedef struct {
  Texture2D sprite;
  couleur col;
  type type_piece;
  int x;
  int y;
  bool init;
  bool has_moved;
} piece;

void init_game(piece *);
void highlight(piece, bool, Color);
void drawgame(piece *);
void init_sprite_piece(piece *);
void get_piece_atco(int, int, piece *, piece **);
bool move_piece_to(piece * p, piece * game, int x, int y);
void draw_field();
void free_game(piece *);
void change_color(couleur * c);
couleur get_other_color(couleur c);
bool roque(piece * p, piece * game, int x, int y);
