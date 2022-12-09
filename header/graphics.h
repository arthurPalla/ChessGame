#ifndef HEADERFILE_H
#define HEADERFILE_H

typedef enum type type;
typedef enum couleur couleur;
enum type{
    PION,TOUR,CAVALIER,FOU,REINE,ROI
};
enum couleur{
    NOIR, BLANC
};
typedef struct{
    Texture2D sprite;
    couleur col;
    type type_piece;
    int x;
    int y;
    bool alive;
    int deplacements[4];
}piece;

void init_game(piece*);
void highlight(piece, bool);
void drawgame(piece*);
void init_sprite_piece(piece*);
void get_piece_atco(int, int, piece*, piece**);
void move_piece_to(piece* p,piece* game, int x, int y);
void draw_field();
void free_game(piece*);
#endif
#ifndef HEIGHT
#define HEIGHT 1000
#endif
#ifndef WIDTH
#define WIDTH 1000
#endif