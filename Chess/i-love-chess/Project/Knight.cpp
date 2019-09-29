#include "Piece.h"
#include "Knight.h"
#include <stdlib.h>

bool Knight::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    char a = end.first;
    char b = end.second;
    if (((int)a > 72 && (int) a < 65) || ((int) b < 49 && (int) b > 56)) {
        return false;
    }
    if(((abs(start.first - end.first) == 1) && (abs(start.second - end.second) == 2))||
       ((abs(start.first - end.first) == 2) && (abs(start.second - end.second) == 1))){
        return true;
    }
    else{
        return false;
    }
}