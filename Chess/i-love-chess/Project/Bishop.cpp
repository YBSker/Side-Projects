#include "Piece.h"
#include "Bishop.h"
#include <stdlib.h>

bool Bishop::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    char a = end.first;
    char b = end.second;
    if (((int)a > 72 && (int) a < 65) || ((int) b < 49 && (int) b > 56)) {
        return false;
    }
    if((abs(end.first - start.first) == abs(end.second - start.second)) &&
       !(start.first == end.first && start.second == end.second)) {
        return true;
    }
    else{
        return false;
    }
}
