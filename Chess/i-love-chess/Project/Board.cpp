#include <iostream>
#include <utility>
#include <map>
#include "Board.h"
#include "CreatePiece.h"
#include <cassert>
#include <vector>
#include "Terminal.h"

using std::make_pair;
using std::string;
using std::cout;
using std::endl;
using std::pair;
using std::map;

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Board::Board() {}

const Piece *Board::operator()(std::pair<char, char> position) const {
    if (occ.find(position) == occ.end()) {
        return nullptr;
    } else {
        return occ.at(position);
    }
}

Board::Board(const Board &old) {
    std::map < std::pair < char, char >, Piece * > temp;
    for (std::map < std::pair < char, char >, Piece * > ::const_iterator it = old.occ.cbegin();
            it != old.occ.cend();
    ++it) {
        temp[it->first] = create_piece(it->second->to_ascii());
//        this->occ[it->first] = create_piece(it->second->to_ascii());
    }
    this->occ = temp;
}

bool Board::add_piece(std::pair<char, char> position, char piece_designator) {
    char a = position.first;
    char b = position.second;
    if (piece_designator != 'K' && piece_designator != 'k' && piece_designator != 'Q' && piece_designator != 'q'
        && piece_designator != 'B' && piece_designator != 'b' && piece_designator != 'N' && piece_designator != 'n'
        && piece_designator != 'R' && piece_designator != 'r' && piece_designator != 'P' && piece_designator != 'p'
        && piece_designator != 'M' && piece_designator != 'm') {
        return false;
    }
    if ((a > 'H' || (int) a < 'A') || (b < '1' || b > '8')) {
        return false;
    }

    occ[position] = create_piece(piece_designator);
    return true;
}

bool Board::has_valid_kings() const {

    int white_K = 0;
    int black_K = 0;
    for (char r = '8'; r >= '1'; r--) {   //go through all positions
        for (char c = 'A'; c <= 'H'; c++) {
            std::pair<char, char> temp = std::make_pair(c, r);
            if (occ.find(temp) != occ.end()) {
                if (occ.find(temp)->second->to_ascii() == 'K') {
                    white_K++;
                }
                if (occ.find(temp)->second->to_ascii() == 'k') {
                    black_K++;
                }
            }
        }
    }
    if (white_K == 1 && black_K == 1) {
        return true;
    }
    return false;
}

void Board::display() const {
    string row_names("12345678");
    string col_names("ABCDEFGH");

    //column line
    cout << "   ";
    for (string::const_iterator it = col_names.begin(); it != col_names.end();
         ++it) {
        cout << " " << *it << " ";
    }
    cout << endl;
    //header line below column line
    cout << "   ";
    for (string::const_iterator it = col_names.begin(); it != col_names.end();
         ++it) {
        cout << "___";
    }
    cout << endl;

    bool color = true;
    char piece;
    for (string::const_reverse_iterator row_it = row_names.crbegin();
         row_it != row_names.crend(); ++row_it) {
        cout << *row_it << " " << "|";
        color = !color;

        for (string::const_iterator col_it = col_names.cbegin(); col_it != col_names.cend(); ++col_it) {

            pair<char, char> addy = make_pair(*col_it, *row_it);

            map < pair < char, char >, Piece * > ::const_iterator
            coord = occ.find(addy);

            //Red colors
            if (color) {
                Terminal::color_all(true, Terminal::MAGENTA, Terminal::MAGENTA);
                cout << " ";
                //Piece at place?
                if (coord != occ.end()) {

                    //White???
                    if (coord->second->is_white()) {
                        Terminal::color_all(true, Terminal::WHITE, Terminal::MAGENTA);
                        piece = coord->second->to_ascii();
                        cout << hashit(piece);
                        Terminal::set_default();
                    }

                        //Black
                    else {
                        Terminal::color_all(true, Terminal::BLACK, Terminal::MAGENTA);
                        piece = coord->second->to_ascii();
                        cout << hashit(piece);

                        Terminal::set_default();
                    }
                }
                    //No piece at coordinate?
                else {
                    Terminal::color_all(true, Terminal::MAGENTA, Terminal::MAGENTA);

                    cout << " ";
                    Terminal::set_default();
                }

                Terminal::color_all(true, Terminal::MAGENTA, Terminal::MAGENTA);
                cout << " ";
                Terminal::set_default();
            }
                //green
            else {
                Terminal::color_all(true, Terminal::BLUE, Terminal::BLUE);
                cout << " ";
                //if piece existing
                if (coord != occ.end()) {

                    if (coord->second->is_white()) {
                        Terminal::color_all(true, Terminal::WHITE, Terminal::BLUE);
                        piece = coord->second->to_ascii();
                        cout << hashit(piece);

                        Terminal::set_default();
                    } else {
                        Terminal::color_all(true, Terminal::BLACK, Terminal::BLUE);
                        piece = coord->second->to_ascii();
                        cout << hashit(piece);
                    }
                }
                    //if no piece there
                else {
                    Terminal::color_all(true, Terminal::BLUE, Terminal::BLUE);
                    cout << " ";
                    Terminal::set_default();
                }
                Terminal::color_all(true, Terminal::BLUE, Terminal::BLUE);
                cout << " ";
                Terminal::set_default();
            }
            color = !color;
        }
        cout << endl;
    }
}


/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream &operator<<(std::ostream &os, const Board &board) {
    for (char r = '8'; r >= '1'; r--) {
        for (char c = 'A'; c <= 'H'; c++) {
            const Piece *piece = board(std::pair<char, char>(c, r));
            if (piece) {
                os << piece->to_ascii();
            } else {
                os << '-';
            }
        }
        os << std::endl;
    }
    return os;
}

bool Board::remove_piece(std::pair<char, char> position) {
    if (occ.find(position) == occ.end()) {
        return false;
    }

    delete occ[position];
    occ.erase(position);
    return true;
}

//std::istream & operator>>(std::istream& is, Board &board) {
//    //clear the board!
//    board.clear();
//
//    char piece_char;
//    for (char r = '8'; r <= '1'; r--) {
//        for (char c = 'A'; c <= 'H'; c++) {
//            is >> piece_char;
//            if (piece_char == '-') {
//                continue;
//            }
//            board.add_piece(make_pair(c, r), piece_char);
//        }
//    }
//    return is;
//}

void Board::clear() {

//    std::map < std::pair < char, char >, Piece * > ::iterator
//    it;
//    std::vector<std::pair<char,char>> locs;
//    for (it = occ.begin(); it != occ.end(); ++it) {
//
//    }
//
//    for( std::vector<std::pair<char,char>>::iterator i = locs.begin();
//            i != locs.end(); ++i){
//        it = occ.end();
//        if (it != occ.end()) {
//            assert(it->second != nullptr);
//            delete it->second;
//            occ.erase(*i);
//        }
//    }

}

std::string hashit(char piece) {
    switch (piece) {
        case 'K':
            return "\u2654";
        case 'k':
            return "\u265A";
        case 'Q':
            return "\u2655";
        case 'q':
            return "\u265B";
        case 'B':
            return "\u2657";
        case 'b':
            return "\u265D";
        case 'N':
            return "\u2658";
        case 'n':
            return "\u265E";
        case 'P':
            return "\u2659";
        case 'p':
            return "\u265F";
        case 'R':
            return "\u2656";
        case 'r':
            return "\u265C";
        case 'm':
            return "m";
        case 'M':
            return "M";
    }

    return "invalid piece";
}