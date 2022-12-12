#ifndef GRAPHICS_H
#define GRAPHICS_H
#define HEIGHT 1000
#define WIDTH 1000
#include "raylib.h"

typedef enum type type;
typedef enum couleur couleur;
enum type{
    PION,TOUR,CAVALIER,FOU,REINE,ROI,NONE
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
    bool init;
}piece;

void init_game(piece*);
void highlight(piece, bool);
void drawgame(piece*);
void init_sprite_piece(piece*);
void get_piece_atco(int, int, piece*, piece**);
bool move_piece_to(piece* p,piece* game, int x, int y);
void draw_field();
void free_game(piece*);
void change_color(couleur* c);

#endif