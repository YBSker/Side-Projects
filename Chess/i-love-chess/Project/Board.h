#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Mystery.h"


class Board {

        // Throughout, we will be accessing board positions using an std::pair<char, char>.
	// The assumption is that the first value is the column with values in
        // {'A','B','C','D','E','F','G','H'} (all caps)
	// and the second is the row, with values in {'1','2','3','4','5','6','7','8'}

public:
	// Default constructor
	Board();

	~Board() {
        std::map < std::pair < char, char >, Piece * > ::iterator
        it;
        for (it = this->occ.begin(); it != this->occ.end(); ++it) {
            delete it->second;
        }
    }


	// Copy Constructor
	Board(const Board &old);
//	    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = old.occ.cbegin();
//                it != old.occ.cend(); ++it) {
//	        add_piece
//	        this->occ[it->first] = add_piece(it->second->to_ascii());
////	        Piece * temp =
////            this->occ.insert({it->first, it->second});
//        }
//	} //I don't know if you're allowed to just copy maps like this

	// Returns a const pointer to the piece at a prescribed location if it exists,
        // or nullptr if there is nothing there.
	const Piece* operator() (std::pair<char, char> position) const;


	// Attempts to add a new piece with the specified designator, at the given location.
	// Returns false if:
	// -- the designator is invalid,
	// -- the specified location is not on the board, or
	// -- if the specified location is occupied
	bool add_piece(std::pair<char, char> position, char piece_designator);

	//Attempts to remove a piece at the given location
	// Returns false if:
	// -- the position does not contain a piece
	// -- the designated piece is a king
	bool remove_piece(std::pair<char, char> position);

	// Displays the board by printing it to stdout
	void display() const;
	// Returns true if the board has the right number of kings on it
	bool has_valid_kings() const;

	std::map<std::pair<char, char>, Piece*> * pt_occ() {
	    return &occ;
	}

    void clear();


private:
	// The sparse map storing the pieces, keyed off locations
	std::map<std::pair<char, char>, Piece*> occ;
};

// Write the board state to an output stream
std::ostream& operator<< (std::ostream& os, const Board& board);

//std::istream& operator>>(std::istream& is, Board &board);

bool remove_piece(std::pair<char, char> position);

std::string hashit(char);


#endif // BOARD_H
