
#include <stdbool.h>
#include "../header/graphics.h"
#include "../header/gamerules.h"
#include <stdio.h>

bool can_moove(piece p, piece* game, int x, int y){
    piece* temp = NULL;
    get_piece_atco(x,y,game, &temp);
    if(temp != NULL){
        if((*temp).x == p.x && (*temp).y == p.y){
            return false;
        }
        if((*temp).col == p.col){
            return false;
        }
        if(p.type_piece == PION ){
            return pion_caneat(p, (*temp));
        }
    }
    if(p.type_piece == PION){
            return pion_movements(p, x,y);
        }
    if(p.type_piece == CAVALIER){
        return cavalier_movements(p, x, y);
    }
    if(p.type_piece == TOUR){
        return tour_movements(p,game,x,y);
    }
    if(p.type_piece == FOU){
        return fou_movements(p,x,y,game);
    }
    if(p.type_piece == ROI){
        return king_movements(p,x,y);
    }
    if(p.type_piece == REINE){
        return king_movements(p,x,y) || fou_movements(p,x,y,game) || tour_movements(p,game,x,y);
    }
    return false;
}

bool pion_caneat(piece p, piece toeat){
    if(p.col == NOIR){
        return ((p.x == toeat.x + 1 || p.x == toeat.x -1) && toeat.y == p.y +1);
    }
    return ((p.x == toeat.x + 1 || p.x == toeat.x  -1 ) && toeat.y == p.y -1);
}

bool pion_movements(piece p, int x, int y){
    if(p.col ==NOIR){
        if(p.y == 1){
            return (y <= 3 && p.x == x);
        }
        return (y == p.y + 1 && x == p.x);
    }
    if(p.y == 6){
        return y>=4 && p.x == x;
    }
    return (y == p.y -1 && p.x == x);
}

bool tour_movements(piece p,piece* game, int x, int y){
    if(x == p.x){
        return anyPieceInRoWY(p.x,p.y, y, game);
    }
    if(y == p.y){
        return anyPieceInRoWX(p.x , p.y, x,game);
    }   
    return false;
}
bool anyPieceInRoWX(int x, int y, int xmax, piece* game){
    piece* temp = NULL;
    if(x<xmax){
        for(int i = x + 1; i<xmax; i++){
            get_piece_atco(i,y,game,&temp);
            if(temp != NULL){
                return false;
            }
        }
        return true;
    }
    else{
        for(int i = x -1; i>xmax; i--){
            get_piece_atco(i,y,game,&temp);
            if(temp != NULL){
                return false;
            }
        }
        return true;
    }

}
bool anyPieceInRoWY(int x, int y, int ymax, piece* game){
    piece* temp = NULL;
    if(y<ymax){
        for(int i = y + 1; i<ymax; i++){
            get_piece_atco(x,i,game,&temp);
            if(temp != NULL){
                return false;
            }
        }
        return true;
    }
    else{
        for(int i = y - 1; i>ymax; i--){
            get_piece_atco(x,i,game,&temp);
            if(temp != NULL){
                return false;
            }
        }
        return true;
    }
}
bool cavalier_movements(piece p, int x, int y){
    return((x == p.x + 2 && y == p.y +1) || (x == p.x +2 && y == p.y -1) || (x == p.x -2 && y == p.y +1) || (x == p.x -2 && y == p.y -1)  || (y == p.y + 2 && x == p.x +1) || (y == p.y +2 && x == p.x -1) || (y == p.y -2 && x == p.x +1) || (y == p.y -2 && x == p.x -1));
}
bool fou_movements(piece p, int x, int y, piece* game){
    piece* temp = NULL;
    int c = 0;
    if(p.x < x && p.y <y){
        for(int i = 1; i<x - p.x; i++){
            c++;
            get_piece_atco(p.x + i, p.y + i, game, &temp);
            if(temp != NULL){
                return false;
            }
        }
        if(p.x + c +1 == x && p.y + c + 1 == y){
            return true;
        }
        return false;
    }
    else if(p.x < x && p.y > y){
        for(int i = 1; i<x - p.x; i++){
            c++;
            get_piece_atco(p.x + i, p.y - i, game, &temp);
            if(temp != NULL){
                return false;
            }
        }
        if(p.x + c +1 == x && p.y - c - 1 == y){
            return true;
        }
        return false;     
    }
    else if(p.x > x && p.y < y){
        for(int i = 1; i<y - p.y; i++){
            c++;
            get_piece_atco(p.x - i, p.y + i, game, &temp);
            if(temp != NULL){
                return false;
            }
        }
        if(p.x - c -1 == x && p.y + c + 1 == y){
            return true;
        }
        return false;
    }
    else if(p.x > x && p.y > y){
        for(int i = 1; i<p.x - x; i++){
            c++;
            get_piece_atco(p.x - i, p.y - i, game, &temp);
            if(temp != NULL){
                return false;
            }
        }
        if(p.x - c -1 == x && p.y - c -1 == y){
            return true;
        }
        return false;
    }
    return false;
}
bool king_movements(piece p, int x, int y){
    return x<=p.x+1 && x>=p.x-1 && y<=p.y+1 && y>= p.y-1;
}