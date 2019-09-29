#include "Piece.h"
#include "Queen.h"

bool Queen::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    char a = end.first;
    char b = end.second;
    if (((int)a > 72 && (int) a < 65) || ((int) b < 49 && (int) b > 56)) {
        return false;
    }
    if ( ( (abs(end.first - start.first) == abs(end.second - start.second)) || //Diagonal Movement
           ((start.first == end.first)||(start.second == end.second))  ) && //Straight Movement
         !(start.first == end.first && start.second == end.second)){ //Not The Same Spot
        return true;
    }
    else {
        return false;
    }
}