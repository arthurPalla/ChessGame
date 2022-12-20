#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../header/gamerules.h"


int main(int argc, char const *argv[]){

    InitWindow(HEIGHT,WIDTH,"Fenetre");
    piece game[64];
    SetTargetFPS(50);
    init_game(game);
    draw_field();
    drawgame(game);
    piece* selected = NULL;
    Vector2 mouse_pos = { -100.0f, -100.0f };
    couleur to_play = BLANC;
    Image test1;
    while(!WindowShouldClose()){
        mouse_pos = GetMousePosition();
        test1 = LoadImageFromScreen();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            if(selected == NULL){
                get_piece_atco((int)((mouse_pos.x*8)/WIDTH), (int)((mouse_pos.y * 8)/ HEIGHT), game, &selected);
                if(selected != NULL){
                    if(1){//(*selected).col == to_play){
                        if(!echec_color(game, (*selected).col)){
                            highlight(*selected, true, LIGHTGRAY);
                        }
                        else if((*selected).type_piece == ROI){
                            highlight(*selected,true,MAROON);
                        } 
                    }
                    else{
                        selected = NULL;
                    }
                }
            }
            else{
                if(!roque(selected,game, (int)((mouse_pos.x*8)/WIDTH), (int)((mouse_pos.y * 8)/ HEIGHT)) && !move_piece_to(selected,game, (int)((mouse_pos.x*8)/WIDTH), (int)((mouse_pos.y * 8)/ HEIGHT))){
                    if(!echec_color(game, (*selected).col)){
                        highlight(*selected, false, LIGHTGRAY);
                    }
                    else if((*selected).type_piece == ROI){
                        highlight(*selected,true,RED);
                    }
                }
                else{
                    to_play = get_other_color(to_play);
                }
                selected = NULL;
            }
        }
        if(IsKeyPressed(KEY_ENTER) || GetPixelColor(test1.data, 7).r == 0){
            draw_field();
            drawgame(game);
        }
        UnloadImage(test1);
        BeginDrawing();
        EndDrawing();
    }
    free_game(game);
    CloseWindow();
    return 0;
}
