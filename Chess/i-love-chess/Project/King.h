#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {

public:
	bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const;
//	{
//        if (((start.first == end.first || start.first == end.first + 1 || start.first == end.first - 1) &&
//            (start.second == end.second || start.second == end.second + 1 || start.second == end.second - 1)) &&
//            !(start.first == end.first && start.second == end.second)){
//            return true;
//        }
//        else{
//            return false;
//        }
//	}

	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	char to_ascii() const {
		return is_white() ? 'K' : 'k';
	}

//    ~King() {delete this;}

private:
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	King(bool is_white) : Piece(is_white) {}

	friend Piece* create_piece(char piece_designator);

};

#endif // KING_H
