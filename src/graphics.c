#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../header/graphics.h"
#include "../header/gamerules.h"


void init_game(piece* jeu){
    type pieces[8] = {TOUR, CAVALIER, FOU, REINE,ROI,FOU,CAVALIER,TOUR};
    for(int i = 0; i<8;i++){
        jeu[i].type_piece = pieces[i];
        jeu[i].x = i;
        jeu[i].y = 0;
        jeu[i].col = NOIR;
        jeu[i].init = true;
        jeu[i].has_mooved = false;
        init_sprite_piece(&jeu[i]);
        jeu[i+56].type_piece = pieces[i];
        jeu[i+56].x = i;
        jeu[i+56].y = 7;
        jeu[i+56].col = BLANC;
        jeu[i+56].init = true;
        jeu[i+56].has_mooved = false;
        init_sprite_piece(&jeu[i+56]);
    }
    for(int i = 0; i<8;i++){
        jeu[i+8].type_piece = PION;
        jeu[i+8].x = i;
        jeu[i+8].y = 1;
        jeu[i+8].col = NOIR;
        jeu[i+8].init = true;
        jeu[i+8].has_mooved = false;
        init_sprite_piece(&jeu[i+8]);
        jeu[i+48].type_piece = PION;
        jeu[i+48].x = i;
        jeu[i+48].y = 6;
        jeu[i+48].col = BLANC;
        jeu[i+48].init = false;
        jeu[i+48].has_mooved = false;
        init_sprite_piece(&jeu[i+48]);
    }
    for(int i = 16; i < 48;i++){
        jeu[i].type_piece = NONE;
        jeu[i].init = false;
    }
}

void highlight(piece p, bool flag, Color col){
    BeginDrawing();
    if(flag){
        DrawRectangle(p.x*WIDTH/8,p.y*HEIGHT/8,WIDTH/8,WIDTH/8,col);
        DrawTexture(p.sprite, p.x*WIDTH/8, p.y*WIDTH/8,WHITE);
    }
    else{
        if((p.y % 2 == 0 && p.x %2 == 0) || (p.y %2 == 1 && p.x % 2  == 1)){
            DrawRectangle(p.x*WIDTH/8,p.y*HEIGHT/8,WIDTH/8,WIDTH/8,GRAY);
        }
        else{
            DrawRectangle(p.x*WIDTH/8,p.y*HEIGHT/8,WIDTH/8,WIDTH/8,RAYWHITE);
        }
        DrawTexture(p.sprite, p.x*WIDTH/8, p.y*WIDTH/8,WHITE);
    }
    EndDrawing();
}

void drawgame(piece* jeu){
    BeginDrawing();
    for(int i = 0; i <64; i++){
        if(jeu[i].type_piece != NONE){
            DrawTexture(jeu[i].sprite,jeu[i].x*WIDTH/8 ,jeu[i].y*HEIGHT/8,WHITE);
        }
        if(jeu[i].type_piece == ROI && echec_color(jeu,jeu[i].col)){
            highlight(jeu[i],true,RED);
        }
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
    if((game[8*y +x]).type_piece != NONE){
        *p = &game[8*y+x];
    }
    else{
        *p = NULL;
    }
}
bool roque(piece* p, piece* game, int x , int y){
    if(!can_roque((*p), game, x ,y)){
        return false;
    }
    int x1,x2;
    BeginDrawing();
        if(((*p).y % 2 == 0 && (*p).x %2 == 0) || ((*p).y %2 == 1 && (*p).x % 2  == 1)){
            DrawRectangle((*p).x*WIDTH/8,(*p).y*HEIGHT/8,WIDTH/8,WIDTH/8,GRAY);
        }
        else{
            DrawRectangle((*p).x*WIDTH/8,(*p).y*HEIGHT/8,WIDTH/8,WIDTH/8,RAYWHITE);
        }
        if((y % 2 == 0 && x %2 == 0) || (y %2 == 1 && x % 2  == 1)){
            DrawRectangle(x*WIDTH/8,y*HEIGHT/8,WIDTH/8,WIDTH/8,GRAY);
        }
        else{
            DrawRectangle(x*WIDTH/8,y*HEIGHT/8,WIDTH/8,WIDTH/8,RAYWHITE);
        }
    EndDrawing();
    piece* tower = NULL;
    get_piece_atco(x,y,game,&tower);
    x1 = (*p).x;
    x2 = (*tower).x;
    if(x == 0){ 
        (*tower).x = 2;
        (*p).x = 1;
    }
    else{
        (*tower).x = 5;
        (*p).x = 6;
    }
    game[8*(*tower).y + (*tower).x] = (*tower);
    game[8*(*p).y + (*p).x] = (*p);
    game[8*y + x1].type_piece = NONE;
    game[8*y + x2].type_piece = NONE;
    BeginDrawing();
    DrawTexture((*p).sprite,(*p).x*WIDTH/8 ,(*p).y*HEIGHT/8,WHITE);
    DrawTexture((*tower).sprite,(*tower).x*WIDTH/8 ,(*tower).y*HEIGHT/8,WHITE);
    EndDrawing();
    return true;

}
bool move_piece_to(piece* p,piece* game, int x, int y){
    if(can_moove((*p),game,x,y, true) == false){
        return false;
    }
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
    int x1,y1;
    x1 = (*p).x;
    y1 = (*p).y;
    (*p).has_mooved = true;
    (*p).x = x;
    (*p).y = y;
    if(can_promote((*p), game,x,y)){
        UnloadTexture((*p).sprite);
        (*p).type_piece = REINE;
        init_sprite_piece(p);
    }
    game[8*y + x] = (*p);
    game[8*y1 + x1].type_piece = NONE;
    game[8*y1 + x1].init = true;
    BeginDrawing();
    if(temp != NULL){
        //(*temp).alive = false;
        if((y % 2 == 0 && x %2 == 0) || (y %2 == 1 && x % 2  == 1)){
            DrawRectangle(x*WIDTH/8,y*HEIGHT/8,WIDTH/8,WIDTH/8,GRAY);
        }
        else{
            DrawRectangle(x*WIDTH/8,y*HEIGHT/8,WIDTH/8,WIDTH/8,RAYWHITE);
        }
    }
    DrawTexture((*p).sprite,(*p).x*WIDTH/8 ,(*p).y*HEIGHT/8,WHITE);
    EndDrawing();
    piece king;
    getking((*p).col, game,&king);
    highlight(king, false, BLACK);
    if(echec_color(game, get_other_color((*p).col))){
        piece temp;
        getking(get_other_color((*p).col),game,&temp);
        highlight(temp,true,RED);
    }
    return true;
}

void draw_field(){
    int h_square = HEIGHT/8;
    int w_square = WIDTH/8;
    int start = 0;
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for(int j=0;j<HEIGHT; j+=h_square){
        for(int i = start; i<WIDTH; i+=w_square * 2){
            DrawRectangle(i,j,w_square,h_square,GRAY);
        }
        if(!start) start = h_square;
        else start = 0;
    }
    EndDrawing();
}

void free_game(piece* game){
    for(int i = 0; i<64; i++){
        if(game[i].init == true){
            UnloadTexture(game[i].sprite);
        }
    }
    printf("ALL GAME TEXTURE UNLOADED\n");
}

void change_color(couleur* c){
    if((*c) == BLANC){
        (*c) = NOIR;
        return;
    }
    (*c) = BLANC;
}
couleur get_other_color(couleur c){
    if(c == BLANC){
        return NOIR;
    }
    return BLANC;
}