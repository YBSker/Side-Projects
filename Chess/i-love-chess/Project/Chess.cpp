#include "Chess.h"
#include <iostream>
#include <iterator>
#include <utility>
#include <map>

using std::string;
using std::pair;
using std::map;
using std::cout;
using std::endl;
using std::make_pair;

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Chess::Chess() : is_white_turn(true) {
    // Add the pawns
    for (int i = 0; i < 8; i++) {
        board.add_piece(std::pair<char, char>('A' + i, '1' + 1), 'P');
        board.add_piece(std::pair<char, char>('A' + i, '1' + 6), 'p');
    }

    // Add the rooks
    board.add_piece(std::pair<char, char>('A' + 0, '1' + 0), 'R');
    board.add_piece(std::pair<char, char>('A' + 7, '1' + 0), 'R');
    board.add_piece(std::pair<char, char>('A' + 0, '1' + 7), 'r');
    board.add_piece(std::pair<char, char>('A' + 7, '1' + 7), 'r');

    // Add the knights
    board.add_piece(std::pair<char, char>('A' + 1, '1' + 0), 'N');
    board.add_piece(std::pair<char, char>('A' + 6, '1' + 0), 'N');
    board.add_piece(std::pair<char, char>('A' + 1, '1' + 7), 'n');
    board.add_piece(std::pair<char, char>('A' + 6, '1' + 7), 'n');

    // Add the bishops
    board.add_piece(std::pair<char, char>('A' + 2, '1' + 0), 'B');
    board.add_piece(std::pair<char, char>('A' + 5, '1' + 0), 'B');
    board.add_piece(std::pair<char, char>('A' + 2, '1' + 7), 'b');
    board.add_piece(std::pair<char, char>('A' + 5, '1' + 7), 'b');

    // Add the kings and queens
    board.add_piece(std::pair<char, char>('A' + 3, '1' + 0), 'Q');
    board.add_piece(std::pair<char, char>('A' + 4, '1' + 0), 'K');
    board.add_piece(std::pair<char, char>('A' + 3, '1' + 7), 'q');
    board.add_piece(std::pair<char, char>('A' + 4, '1' + 7), 'k');

}

bool Chess::is_legal_move(std::pair<char, char> start, std::pair<char, char> end) {
    //std::cout<<"running make_move: " << start.first<<start.second <<" to "<<end.first<<end.second<<"\n";
    //Stan's Variables
    char a1 = start.first;
    char b1 = start.second;
    char a2 = end.first;
    char b2 = end.second;
    const Piece *pieceMoving; //changed to const so it can work with board(pair) function

    //changed some ands to ors because any of these being false means it's illegal
    if (((int) a1 > 72 || (int) a1 < 65) || ((int) b1 < 49 || (int) b1 > 56)) {
        std::cerr<<"Location out of bounds\n";
        return false;
    }
    if (((int) a2 > 72 || (int) a2 < 65) || ((int) b2 < 49 || (int) b2 > 56)) {
        std::cerr<<"Location out of bounds\n";
        return false;
    }


    //Stan's Iterator
    map < std::pair < char, char >, Piece * > ::iterator
    it;


    if (!this->board(start)) {
        std::cerr<<"No piece at start location\n";
        return false; }; // there has to be a piece in the starting spot
    pieceMoving = this->board(start); //if there is, let pieceMoving get it

    if (this->get_turn() !=
        pieceMoving->is_white()) {
        std::cerr<<"Not this player's turn\n";
        return false; } //make sure it's the right turn, only need 1 line to do this

    if (this->board(end)) { //it's a capture
        if (pieceMoving->is_white() == this->board(
                end)->is_white()) {
            std::cerr<<"Friendly fire is not allowed\n";
            return false; } //can't capture your own piece, only need 1 line to do this i think
        if (!pieceMoving->legal_capture_shape(start,
                                              end)) {
            std::cerr<<"Not in the piece's legal capture shape\n";
            return false; } //check that the move is in the piece's capture shape
    } else { //it's not a capture
        if (!pieceMoving->legal_move_shape(start,
                                           end)) {
            std::cerr<<"Not is the piece's legal move shape\n";
            return false; } //check that the move is in the piece's move shape

    }

    //piece collision checkers ( I didn't check these, I'm trusting that they work ) ----------------------------------------
    if ((start.first == end.first) && (start.second < end.second)) {
        for (int i = 1; i < end.second - start.second; ++i) {
            pair<char, char> position(a1, (char) (b1 + i));
            if (this->board(position) != nullptr) {
                std::cerr<<"There's another piece in the way\n";
                return false;
            }
        }
    }
    if ((start.first == end.first) && (start.second > end.second)) {
        for (int i = -1; i > end.second - start.second; --i) {
            pair<char, char> position(a1, (char) (b1 + i));
            if (this->board(position) != nullptr) {
                std::cerr<<"There's another piece in the way\n";
                return false;
            }
        }
    }
    if ((start.first < end.first) && (start.second == end.second)) {
        for (int i = 1; i < end.first - start.first; ++i) {
            pair<char, char> position((char) (a1 + i), b1);
            if (this->board(position) != nullptr) {
                std::cerr<<"There's another piece in the way\n";
                return false;
            }
        }
    }
    if ((start.first > end.first) && (start.second == end.second)) {
        for (int i = -1; i > end.first - start.first; --i) {
            pair<char, char> position((char) (a1 + i), b1);
            if (this->board(position) != nullptr) {
                std::cerr<<"There's another piece in the way\n";
                return false;
            }
        }
    }
    //Check diagonal piece collisions
    if ((abs(end.first - start.first) == abs(end.second - start.second)) &&
        !(start.first == end.first && start.second == end.second)) {
        if (end.first - start.first < 0 && end.second - start.second < 0) {
            for (int i = -1; i > end.first - start.first; --i) {
                pair<char, char> position((char) (a1 + i), (char) (b1 + i));
                if (this->board(position) != nullptr) {
                    std::cerr<<"There's another piece in the way\n";
                    return false;
                }
            }
        }
        if (end.first - start.first > 0 && end.second - start.second > 0) {
            for (int i = 1; i < end.first - start.first; ++i) {
                pair<char, char> position((char) (a1 + i), (char) (b1 + i));
                if (this->board(position) != nullptr) {
                    std::cerr<<"There's another piece in the way\n";
                    return false;
                }
            }
        }
        if (end.first - start.first < 0 && end.second - start.second > 0) {
            for (int i = -1; i > end.first - start.first; --i) {
                pair<char, char> position((char) (a1 + i), (char) (b1 - i));
                if (this->board(position) != nullptr) {
                    std::cerr<<"There's another piece in the way\n";
                    return false;
                }
            }
        }
        if (end.first - start.first > 0 && end.second - start.second < 0) {
            for (int i = 1; i < end.first - start.first; ++i) {
                pair<char, char> position((char) (a1 + i), (char) (b1 - i));
                if (this->board(position) != nullptr) {
                    std::cerr<<"There's another piece in the way\n";
                    return false;
                }
            }
        }
    }
    //end of piece collision checkers ------------------------------------------------------------------------------------
    return true;
}



bool Chess::is_legal_movex(std::pair<char, char> start, std::pair<char, char> end) {
    //std::cout<<"running make_move: " << start.first<<start.second <<" to "<<end.first<<end.second<<"\n";
    //Stan's Variables
    char a1 = start.first;
    char b1 = start.second;
    char a2 = end.first;
    char b2 = end.second;
    const Piece *pieceMoving; //changed to const so it can work with board(pair) function

    //changed some ands to ors because any of these being false means it's illegal
    if (((int) a1 > 72 || (int) a1 < 65) || ((int) b1 < 49 || (int) b1 > 56)) {
        //std::cerr<<"Location out of bounds\n";
        return false;
    }
    if (((int) a2 > 72 || (int) a2 < 65) || ((int) b2 < 49 || (int) b2 > 56)) {
        //std::cerr<<"Location out of bounds\n";
        return false;
    }


    //Stan's Iterator
    map < std::pair < char, char >, Piece * > ::iterator
    it;


    if (!this->board(start)) {
        //std::cerr<<"No piece at start location\n";
        return false; }; // there has to be a piece in the starting spot
    pieceMoving = this->board(start); //if there is, let pieceMoving get it

    if (this->get_turn() !=
        pieceMoving->is_white()) {
        //std::cerr<<"Not this player's turn\n";
        return false; } //make sure it's the right turn, only need 1 line to do this

    if (this->board(end)) { //it's a capture
        if (pieceMoving->is_white() == this->board(
                end)->is_white()) {
            //  std::cerr<<"Friendly fire is not allowed\n";
            return false; } //can't capture your own piece, only need 1 line to do this i think
        if (!pieceMoving->legal_capture_shape(start,
                                              end)) {
            //std::cerr<<"Not in the piece's legal capture shape\n";
            return false; } //check that the move is in the piece's capture shape
    } else { //it's not a capture
        if (!pieceMoving->legal_move_shape(start,
                                           end)) {
            //std::cerr<<"Not is the piece's legal move shape\n";
            return false; } //check that the move is in the piece's move shape

    }

    //piece collision checkers ( I didn't check these, I'm trusting that they work ) ----------------------------------------
    if ((start.first == end.first) && (start.second < end.second)) {
        for (int i = 1; i < end.second - start.second; ++i) {
            pair<char, char> position(a1, (char) (b1 + i));
            if (this->board(position) != nullptr) {
                //  std::cerr<<"There's another piece in the way\n";
                return false;
            }
        }
    }
    if ((start.first == end.first) && (start.second > end.second)) {
        for (int i = -1; i > end.second - start.second; --i) {
            pair<char, char> position(a1, (char) (b1 + i));
            if (this->board(position) != nullptr) {
                //std::cerr<<"There's another piece in the way\n";
                return false;
            }
        }
    }
    if ((start.first < end.first) && (start.second == end.second)) {
        for (int i = 1; i < end.first - start.first; ++i) {
            pair<char, char> position((char) (a1 + i), b1);
            if (this->board(position) != nullptr) {
                //std::cerr<<"There's another piece in the way\n";
                return false;
            }
        }
    }
    if ((start.first > end.first) && (start.second == end.second)) {
        for (int i = -1; i > end.first - start.first; --i) {
            pair<char, char> position((char) (a1 + i), b1);
            if (this->board(position) != nullptr) {
                //std::cerr<<"There's another piece in the way\n";
                return false;
            }
        }
    }
    //Check diagonal piece collisions
    if ((abs(end.first - start.first) == abs(end.second - start.second)) &&
        !(start.first == end.first && start.second == end.second)) {
        if (end.first - start.first < 0 && end.second - start.second < 0) {
            for (int i = -1; i > end.first - start.first; --i) {
                pair<char, char> position((char) (a1 + i), (char) (b1 + i));
                if (this->board(position) != nullptr) {
                    //  std::cerr<<"There's another piece in the way\n";
                    return false;
                }
            }
        }
        if (end.first - start.first > 0 && end.second - start.second > 0) {
            for (int i = 1; i < end.first - start.first; ++i) {
                pair<char, char> position((char) (a1 + i), (char) (b1 + i));
                if (this->board(position) != nullptr) {
                    //std::cerr<<"There's another piece in the way\n";
                    return false;
                }
            }
        }
        if (end.first - start.first < 0 && end.second - start.second > 0) {
            for (int i = -1; i > end.first - start.first; --i) {
                pair<char, char> position((char) (a1 + i), (char) (b1 - i));
                if (this->board(position) != nullptr) {
                    // std::cerr<<"There's another piece in the way\n";
                    return false;
                }
            }
        }
        if (end.first - start.first > 0 && end.second - start.second < 0) {
            for (int i = 1; i < end.first - start.first; ++i) {
                pair<char, char> position((char) (a1 + i), (char) (b1 - i));
                if (this->board(position) != nullptr) {
                    //std::cerr<<"There's another piece in the way\n";
                    return false;
                }
            }
        }
    }
    //end of piece collision checkers ------------------------------------------------------------------------------------
    return true;
}











bool Chess::make_movex(std::pair<char, char> start, std::pair<char, char> end) {
    //Stan's Variables
    if (!this->is_legal_movex(start, end)) {
        return false; }
    char b2 = end.second;
    const Piece *pieceMoving; //changed to const so it can work with board(pair) function
    pieceMoving = this->board(start);
    bool capture; //is the move a capture or not

    if (this->board(end)) { //it's a capture
        capture = true;
    } else { //it's not a capture
        capture = false;
    }

    Chess test(*this);
    if (capture) {
        test.board.remove_piece(end);
        char chPieceMoving = pieceMoving->to_ascii();
        test.board.add_piece(end, chPieceMoving);
        test.board.remove_piece(start);
        //change pawn to queen
        if ((b2 == '8' && chPieceMoving == 'P')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'Q');
        }
        if ((b2 == '1' && chPieceMoving == 'p')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'q');
        }

    } else {
        char chPieceMoving = pieceMoving->to_ascii();
        test.board.add_piece(end, chPieceMoving);
        test.board.remove_piece(start);
        //pawn to queen
        if ((b2 == '8' && chPieceMoving == 'P')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'Q');
        }
        if ((b2 == '1' && chPieceMoving == 'p')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'q');
        }
    }
    if (test.in_check(test.get_turn())) {
        //std::cerr<<"You must get out of check\n";
        return false;
    }
    //THE ACTUAL MOVING OF THE PIECES, I TRIMMED THESE DOWN BECAUSE YOU WERE previously still error checking in here, but I moved it out
    if (capture) {
        this->board.remove_piece(end);
        char chPieceMoving = pieceMoving->to_ascii();
        this->board.add_piece(end, chPieceMoving);
        this->board.remove_piece(start);
        this->change_turn(this->turn_white());
        //change pawn to queen
        if ((b2 == '8' && chPieceMoving == 'P')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'Q');
        }
        if ((b2 == '1' && chPieceMoving == 'p')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'q');
        }
        return true;
    } else {
        char chPieceMoving = pieceMoving->to_ascii();
        this->board.add_piece(end, chPieceMoving);
        this->board.remove_piece(start);
        this->change_turn(this->turn_white());
        //pawn to queen
        if ((b2 == '8' && chPieceMoving == 'P')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'Q');
        }
        if ((b2 == '1' && chPieceMoving == 'p')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'q');
        }
        return true;
    }

    return false; //satisfy compiler
}










// check if game can continue, if source and dest valid, if is within chessboard, source not empty
//piece being moved is player piece, piece  move is actually valid, piece move not put you in check.
bool Chess::make_move(std::pair<char, char> start, std::pair<char, char> end) {
    //Stan's Variables
    if (!this->is_legal_move(start, end)) {
       std::cerr<<"Not a legal move\n";
        return false; }
    char b2 = end.second;
    const Piece *pieceMoving; //changed to const so it can work with board(pair) function
    pieceMoving = this->board(start);
    bool capture; //is the move a capture or not

    if (this->board(end)) { //it's a capture
        capture = true;
    } else { //it's not a capture
        capture = false;
    }

    Chess test(*this);
    if (capture) {
        test.board.remove_piece(end);
        char chPieceMoving = pieceMoving->to_ascii();
        test.board.add_piece(end, chPieceMoving);
        test.board.remove_piece(start);
        //change pawn to queen
        if ((b2 == '8' && chPieceMoving == 'P')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'Q');
        }
        if ((b2 == '1' && chPieceMoving == 'p')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'q');
        }

    } else {
        char chPieceMoving = pieceMoving->to_ascii();
        test.board.add_piece(end, chPieceMoving);
        test.board.remove_piece(start);
        //pawn to queen
        if ((b2 == '8' && chPieceMoving == 'P')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'Q');
        }
        if ((b2 == '1' && chPieceMoving == 'p')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'q');
        }
    }
    if (test.in_check(test.get_turn())) {
        //std::cerr<<"You must get out of check\n";
        return false;
    }
    //THE ACTUAL MOVING OF THE PIECES, I TRIMMED THESE DOWN BECAUSE YOU WERE previously still error checking in here, but I moved it out
    if (capture) {
        this->board.remove_piece(end);
        char chPieceMoving = pieceMoving->to_ascii();
        this->board.add_piece(end, chPieceMoving);
        this->board.remove_piece(start);
        this->change_turn(this->turn_white());
        //change pawn to queen
        if ((b2 == '8' && chPieceMoving == 'P')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'Q');
        }
        if ((b2 == '1' && chPieceMoving == 'p')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'q');
        }
        return true;
    } else {
        char chPieceMoving = pieceMoving->to_ascii();
        this->board.add_piece(end, chPieceMoving);
        this->board.remove_piece(start);
        this->change_turn(this->turn_white());
        //pawn to queen
        if ((b2 == '8' && chPieceMoving == 'P')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'Q');
        }
        if ((b2 == '1' && chPieceMoving == 'p')) {
            this->board.remove_piece(end);
            this->board.add_piece(end, 'q');
        }
        return true;
    }

    return false; //satisfy compiler
}

/** ACTUALLY LETS HANDLE THIS BY USING MAKE MOVE SINCE WE'lL HAVE A BUNCH OF ERROR CHECKS THERE. */
bool Chess::in_check(bool white) const {
    Chess test(*this);
    test.change_turn(white);
    for (char r = '8'; r >= '1'; r--) {   //go through all positions
        for (char c = 'A'; c <= 'H'; c++) {
            std::pair<char, char> temp = std::make_pair(c, r);
            if (white) {
                if ((this->board(temp)) && (this->board(temp)->to_ascii() == 'K')) {
                    for (char ra = '8'; ra >= '1'; ra--) {   //go through all positions
                        for (char ca = 'A'; ca <= 'H'; ca++) {
                            std::pair<char, char> temp2 = std::make_pair(ca, ra);
                            if (test.is_legal_movex(temp2, temp)) { return true; }
                        }
                    }
                    return false;
                }
            } else {
                if ((this->board(temp)) && (this->board(temp)->to_ascii() == 'k')) {
                    for (char ra = '8'; ra >= '1'; ra--) {   //go through all positions
                        for (char ca = 'A'; ca <= 'H'; ca++) {
                            std::pair<char, char> temp2 = std::make_pair(ca, ra);
                            if (test.is_legal_movex(temp2, temp)) { return true; }
                        }
                    }
                    return false;
                }
            }
        }
    }
    return false;
}

bool Chess::in_mate(bool white) const {
//    std::cout << "running mate" << std::endl;
    //copy.board.display();
    Chess copy(*this);    //create copy
    if (copy.in_check(white)) {   //check for check
//        std::cout << "Checked for check\n";
        for (char r = '8'; r >= '1'; r--) {   //go through all positions
            for (char c = 'A'; c <= 'H'; c++) {
                std::pair<char, char> temp = std::make_pair(c, r);
                if (copy.board(temp) != nullptr) {    //if there's a piece there
                    for (char rank = '8'; rank >=
                                          '1'; rank--) {    //go through all positions checking for pieces, if make_move checks for the correct player's turn, we don't need to here
                        for (char file = 'A'; file <= 'H'; file++) {
                            std::pair<char, char> temp2 = std::make_pair(file, rank);
                            Chess copy2(*this);    //create copy
                            if (copy2.make_movex(temp, temp2)) {
                                if (!(copy2.in_check(white))) {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }

        return true;
    }
//    std::cout << "Checked for  and it was false\n";
    return false;
}

bool Chess::in_stalemate(bool white) const {
    Chess copy(*this);    //create copy
//    this->get_board().display();
    if (!(copy.in_check(white))) {   //check for no check
        for (char r = '8'; r >= '1'; r--) {   //go through all positions
            for (char c = 'A'; c <= 'H'; c++) {
                std::pair<char, char> temp = std::make_pair(c, r);
                if (copy.board(temp) != nullptr) {    //if there's a piece there
                    for (char rank = '8'; rank >=
                                          '1'; rank--) {    //go through all positions checking for pieces, if make_move checks for the correct player's turn, we don't need to here
                        for (char file = 'A'; file <= 'H'; file++) {
                            std::pair<char, char> temp2 = std::make_pair(file, rank);
                            Chess copy2(*this);    //create copy
                            if (copy2.make_movex(temp, temp2)) {
                                return false;
                            }
                        }
                    }
                }
            }
        }

        return true;
    }
    return false;
}


/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream &operator<<(std::ostream &os, const Chess &chess) {
    // Write the board out and then either the character 'w' or the character 'b',
    // depending on whose turn it is
    return os << chess.get_board() << (chess.turn_white() ? 'w' : 'b');
}


std::istream &operator>>(std::istream &is, Chess &chess) {
    /////////////////////////
    // [REPLACE THIS STUB] //
    /////////////////////////
    for (std::map<std::pair<char,char>,Piece*>::iterator it = chess.pt_board()->pt_occ()->begin();
        it != chess.pt_board()->pt_occ()->end();
        ++it) {
        if (it->second) {
            delete it->second;
        }
    }
    chess.pt_board()->pt_occ()->clear();
//    return pointer to real board
//add function to return pointer to board
    char piece_char;
    for (char r = '8'; r >= '1'; r--) {
        for (char c = 'A'; c <= 'H'; c++) {
            is >> piece_char;
            if (piece_char != '-') {
                chess.pt_board()->add_piece(make_pair(c, r), piece_char);
            }
        }
    }

    char turn;
    is >> turn;
    if (turn == 'w') {
        chess.set_white();
    } else {
        chess.set_black();
    }
    return is;
}