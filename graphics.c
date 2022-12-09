#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "graphics.h"

#define HEIGHT 1000
#define WIDTH 1000
void init_game(piece* jeu){
    type pieces[8] = {TOUR, CAVALIER, FOU, REINE,ROI,FOU,CAVALIER,TOUR};
    for(int i = 0; i<8;i++){
        jeu[i].type_piece = pieces[i];
        jeu[i].x = i;
        jeu[i].y = 0;
        jeu[i].col = NOIR;
        jeu[i].alive = true;
        init_sprite_piece(&jeu[i]);
        jeu[i+24].type_piece = pieces[i];
        jeu[i+24].x = i;
        jeu[i+24].y = 7;
        jeu[i+24].col = BLANC;
        jeu[i+24].alive = true;
        init_sprite_piece(&jeu[i+24]);
    }
    for(int i = 0; i<8;i++){
        jeu[i+8].type_piece = PION;
        jeu[i+8].x = i;
        jeu[i+8].y = 1;
        jeu[i+8].col = NOIR;
        jeu[i+8].alive = true;
        init_sprite_piece(&jeu[i+8]);
        jeu[i+16].type_piece = PION;
        jeu[i+16].x = i;
        jeu[i+16].y = 6;
        jeu[i+16].col = BLANC;
        jeu[i+16].alive = true;
        init_sprite_piece(&jeu[i+16]);
    }
}
void highlight(piece p, bool flag){
    BeginDrawing();
    if(flag){
        DrawRectangle(p.x*WIDTH/8,p.y*HEIGHT/8,WIDTH/8,WIDTH/8,GREEN);
        DrawTexture(p.sprite, p.x*WIDTH/8, p.y*WIDTH/8,WHITE);
    }
    else{
        if((p.y % 2 == 0 && p.x %2 == 0) || (p.y %2 == 1 && p.x % 2  == 1)){
            DrawRectangle(p.x*WIDTH/8,p.y*HEIGHT/8,WIDTH/8,WIDTH/8,GRAY);
        }
        else{
            DrawRectangle(p.x*WIDTH/8,p.y*HEIGHT/8,WIDTH/8,WIDTH/8,RAYWHITE);
        }
    }
    EndDrawing();
}
void drawgame(piece* jeu){
    BeginDrawing();
    for(int i = 0; i <32; i++){
        DrawTexture(jeu[i].sprite,jeu[i].x*WIDTH/8 ,jeu[i].y*HEIGHT/8,WHITE);
    }
    EndDrawing();
}

void init_sprite_piece(piece* p){
    int y = 0;
    int x = 0;
    Texture2D sprite;
    Image test;
    test = LoadImage("Chess1.png");
    if((*p).col == BLANC){
        y += 400;
    }
    if((*p).type_piece == FOU){
        x += 300;
    }
    if((*p).type_piece == REINE){
        x+=600;
    }
    if((*p).type_piece == ROI){
        x+=900;
    }
    if((*p).type_piece == CAVALIER){
        x+=1200;
    }
    if((*p).type_piece == PION){
        x+=1500;
    }
    ImageCrop(&test, (Rectangle){ x, y, 300, 400 });
    ImageResize(&test,WIDTH / 8, HEIGHT/ 8);
    sprite = LoadTextureFromImage(test);
    UnloadImage(test);
    (*p).sprite = sprite;
    

}
void get_piece_atco(int x, int y, piece* game, piece** p){
    for(int i = 0; i < 32; i++){
        if(game[i].x == x && game[i].y == y && game[i].alive){
            *p = &game[i];
            return;
        }
    }
    return;
}
void move_piece_to(piece* p,piece* game, int x, int y){
    BeginDrawing();
        if(((*p).y % 2 == 0 && (*p).x %2 == 0) || ((*p).y %2 == 1 && (*p).x % 2  == 1)){
            DrawRectangle((*p).x*WIDTH/8,(*p).y*HEIGHT/8,WIDTH/8,WIDTH/8,GRAY);
        }
        else{
            DrawRectangle((*p).x*WIDTH/8,(*p).y*HEIGHT/8,WIDTH/8,WIDTH/8,RAYWHITE);
        }
    EndDrawing();
    piece* temp = NULL;
    get_piece_atco(x,y,game,&temp);
    (*p).x = x;
    (*p).y = y;
    BeginDrawing();
    if(temp != NULL){
        (*temp).alive = false;
        if((y % 2 == 0 && x %2 == 0) || (y %2 == 1 && x % 2  == 1)){
            DrawRectangle(x*WIDTH/8,y*HEIGHT/8,WIDTH/8,WIDTH/8,GRAY);
        }
        else{
            DrawRectangle(x*WIDTH/8,y*HEIGHT/8,WIDTH/8,WIDTH/8,RAYWHITE);
        }
    }
   DrawTexture((*p).sprite,(*p).x*WIDTH/8 ,(*p).y*HEIGHT/8,WHITE);
    EndDrawing();
}

void draw_field(){
    int h_square = HEIGHT/8;
    int w_square = WIDTH/8;
    int start = 0;
    BeginDrawing();
    for(int j=0;j<HEIGHT; j+=h_square){
        for(int i = start; i<WIDTH; i+=w_square * 2){
            DrawRectangle(i,j,w_square,h_square,GRAY);
        }
        if(!start) start = h_square;
        else start = 0;
    }
    EndDrawing();
}