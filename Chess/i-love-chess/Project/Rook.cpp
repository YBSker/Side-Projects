#include "Piece.h"
#include "Rook.h"

bool Rook::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    char a = end.first;
    char b = end.second;
    if (((int)a > 72 && (int) a < 65) || ((int) b < 49 && (int) b > 56)) {
        return false;
    }
    if(((start.first == end.first)||(start.second == end.second)) &&
       !(start.first == end.first && start.second == end.second)){
        return true;
    }

    return false;
}