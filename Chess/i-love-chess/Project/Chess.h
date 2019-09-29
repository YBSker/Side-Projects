#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include "Piece.h"
#include "Board.h"

class Chess {

public:
	// This default constructor initializes a board with the standard
	// piece positions, and sets the state to white's turn
	Chess();

	Chess(const Chess *old) {
	    this->board = *(new Board(old->board));
	    this->is_white_turn = old->is_white_turn;
	}

	~Chess() {
	}
    bool make_movex(std::pair<char, char> start, std::pair<char, char> end);
    bool is_legal_move(std::pair<char, char> start, std::pair<char, char> end);
    bool is_legal_movex(std::pair<char, char> start, std::pair<char, char> end);
	// Returns a constant reference to the board 
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	const Board& get_board() const { return board; }

	// Returns true if it is white's turn
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	bool turn_white() const { return is_white_turn; }

	// Attempts to make a move. If successful, the move is made and
	// the turn is switched white <-> black
	bool make_move(std::pair<char, char> start, std::pair<char, char> end);

	// Returns true if the designated player is in check
	bool in_check(bool white) const;

	// Returns true if the designated player is in mate
	bool in_mate(bool white) const;

	// Returns true if the designated player is in mate
	bool in_stalemate(bool white) const;

	Board get_ncboard() {
	    return this->board;
	}

	void set_white() {
	    this->is_white_turn = true;
	}

    void set_black() {
        this->is_white_turn = false;
    }

    bool get_turn() {
	    return this->is_white_turn;
	}

    void change_turn(bool white) {
        if (white){
            this->is_white_turn = false;
        }
        if (!white){
            this->is_white_turn = true;
        }
    }

//    void set_board(Board newb) {
//	    this->board = newb;
//	}

    Board * pt_board() {
	    return &board;
	}

private:
	// The board
	Board board;

	// Is it white's turn?
	bool is_white_turn;

};

// Writes the board out to a stream
std::ostream& operator<< (std::ostream& os, const Chess& chess);

// Reads the board in from a stream
std::istream& operator>> (std::istream& is, Chess& chess);





#endif // CHESS_H
