#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {

public:
    bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const; //defined in pawn.cpp

//        bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
//            char a = end.first;
//            char b = end.second;
//            if (((int) a > 72 && (int) a < 65) || ((int) b < 49 && (int) b > 56)) {
//                return false;
//            }
//            if (!hasMoved) {
//                if (this->is_white()) {
//                    return (start.first == end.first && (end.second == start.second + 1
//                                                         || end.second == start.second + 2));
//                } else {
//                    return (start.first == end.first && (end.second == start.second - 1
//                                                         || end.second == start.second - 2));
//                }
//            } else {
//                if (this->is_white()) {
//                    return (start.first == end.first && end.second == start.second + 1);
//                } else {
//                    return (start.first == end.first && end.second == start.second - 1);
//                }
//            }
//
//        }

        bool legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const;
//            if (this->is_white()) {
//                return (end.second == start.second + 1 &&
//                        (end.first == start.first + 1 || end.first == start.first - 1));
//            } else {
//                return (end.second == start.second - 1 &&
//                        (end.first == start.first + 1 || end.first == start.first - 1));
//            }
//        }

//    ~Pawn() { delete this; }

//    bool is_white() const;

//    void changeHasMoved();


    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    char to_ascii() const {
        return is_white() ? 'P' : 'p';
    }

private:
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    Pawn(bool is_white) : Piece(is_white) {}

    friend Piece* create_piece(char piece_designator);

  //  bool white;
//    bool hasMoved = false;
};

#endif // PAWN_H
