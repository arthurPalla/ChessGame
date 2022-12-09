#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../header/graphics.h"


int main(int argc, char const *argv[]){

    InitWindow(HEIGHT,WIDTH,"Fenetre");
    piece game[32];
    SetTargetFPS(120);
    init_game(game);
    ClearBackground(RAYWHITE);
    draw_field();
    drawgame(game);
    piece* selected = NULL;
    Vector2 mouse_pos = { -100.0f, -100.0f };
    while(!WindowShouldClose()){
        mouse_pos = GetMousePosition();
        
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            if(selected == NULL){
                get_piece_atco((int)((mouse_pos.x*8)/WIDTH), (int)((mouse_pos.y * 8)/ HEIGHT), game, &selected);
                highlight(*selected, true);
            }
            else{
                highlight(*selected, false);
                move_piece_to(selected,game, (int)((mouse_pos.x*8)/WIDTH), (int)((mouse_pos.y * 8)/ HEIGHT));
                selected = NULL;
            }
        }
        BeginDrawing();
        EndDrawing();

    }
    free_game(game);
    CloseWindow();
    return 0;
}
