#include "Piece.h"
#include "King.h"

bool King::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    char a = end.first;
    char b = end.second;
    if (((int)a > 72 && (int) a < 65) || ((int) b < 49 && (int) b > 56)) {
        return false;
    }
    if (((start.first == end.first || start.first == end.first + 1 || start.first == end.first - 1) &&
         (start.second == end.second || start.second == end.second + 1 || start.second == end.second - 1)) &&
        !(start.first == end.first && start.second == end.second)){
        return true;
    }
    else{
        return false;
    }
}