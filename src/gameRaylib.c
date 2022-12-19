#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../header/gamerules.h"


int main(int argc, char const *argv[]){

    InitWindow(HEIGHT,WIDTH,"Fenetre");
    piece game[64];
    SetTargetFPS(30);
    init_game(game);
    draw_field();
    drawgame(game);
    piece* selected = NULL;
    Vector2 mouse_pos = { -100.0f, -100.0f };
    couleur to_play = BLANC;
    while(!WindowShouldClose()){
        mouse_pos = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            if(selected == NULL){
                get_piece_atco((int)((mouse_pos.x*8)/WIDTH), (int)((mouse_pos.y * 8)/ HEIGHT), game, &selected);
                if(selected != NULL){
                    if((*selected).col == to_play){
                        if((*selected).type_piece != ROI || !echec_color(game, (*selected).col))
                        highlight(*selected, true, LIGHTGRAY);
                    }
                    else{
                        selected = NULL;
                    }
                }
            }
            else{
                if(!roque(selected,game, (int)((mouse_pos.x*8)/WIDTH), (int)((mouse_pos.y * 8)/ HEIGHT))){
                    if(!move_piece_to(selected,game, (int)((mouse_pos.x*8)/WIDTH), (int)((mouse_pos.y * 8)/ HEIGHT))){
                        if((*selected).type_piece != ROI || !echec_color(game, (*selected).col))
                        highlight(*selected, false, LIGHTGRAY);
                    }
                    else{
                        to_play = get_other_color(to_play);
                    }
                }
                else{
                    to_play = get_other_color(to_play);
                }
                selected = NULL;
            }
        }
        if(IsKeyPressed(KEY_ENTER)){
            draw_field();
            drawgame(game);
        }
        BeginDrawing();
        EndDrawing();

    }
    free_game(game);
    CloseWindow();
    return 0;
}
