#include "Piece.h"
#include "Pawn.h"

//void Pawn::changeHasMoved() {
//    hasMoved = true;
//}

//Do we need to say staying in the same position is legal or smth??
bool Pawn::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    char a = end.first;
    char b = end.second;
    if (((int) a > 72 && (int) a < 65) || ((int) b < 49 && (int) b > 56)) {
        return false;
    }
    if ((start.second == '2' && this->is_white()) || (start.second == '7' && this->is_white() == false)) {
//        this->changeHasMoved();
        if (this->is_white() && start.second == '2') {
            return (start.first == end.first && (end.second == start.second + 1
                                                 || end.second == start.second + 2));
        } else {
            return (start.first == end.first && (end.second == start.second - 1
                                                 || end.second == start.second - 2));
        }
    } else {
        if (this->is_white()) {
            return (start.first == end.first && end.second == start.second + 1);
        } else {
            return (start.first == end.first && end.second == start.second - 1);
        }
    }

}

bool Pawn::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    if (this->is_white()) {
        return (end.second == start.second + 1 &&
                (end.first == start.first + 1 || end.first == start.first - 1));
    } else {
        return (end.second == start.second - 1 &&
                (end.first == start.first + 1 || end.first == start.first - 1));
    }
}



//bool Pawn::is_white() const {
//    return white;
//}