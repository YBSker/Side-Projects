CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

chess: main.o Board.o Chess.o CreatePiece.o Pawn.o Bishop.o Rook.o Knight.o Queen.o King.o 
	$(CC) main.o Board.o Chess.o CreatePiece.o Pawn.o Bishop.o Rook.o Knight.o Queen.o King.o -o chess


main.o: main.cpp Chess.h
	$(CC) $(CFLAGS) -c main.cpp
Pawn.o: Piece.h Pawn.h Pawn.cpp
	$(CC) $(CFLAGS) -c Pawn.cpp
Bishop.o: Piece.h Bishop.h Bishop.cpp
	$(CC) $(CFLAGS) -c Bishop.cpp
Rook.o: Piece.h Rook.h Rook.cpp
	$(CC) $(CFLAGS) -c Rook.cpp
Knight.o: Piece.h Knight.h Knight.cpp
	$(CC) $(CFLAGS) -c Knight.cpp
Queen.o: Piece.h Queen.h Queen.cpp
	$(CC) $(CFLAGS) -c Queen.cpp
King.o: Piece.h King.h King.cpp
	$(CC) $(CFLAGS) -c King.cpp

Board.o: Board.cpp Board.h CreatePiece.h Piece.h Rook.h Bishop.h Pawn.h Knight.h Queen.h King.h Mystery.h
	$(CC) $(CFLAGS) -c Board.cpp

Chess.o: Chess.cpp Chess.h Piece.h Board.h
	$(CC) $(CFLAGS) -c Chess.cpp

CreatePiece.o: CreatePiece.cpp CreatePiece.h Pawn.h Rook.h Bishop.h Knight.h King.h Queen.h Piece.h Mystery.h
	$(CC) $(CFLAGS) -c CreatePiece.cpp

clean:
	rm -f *.o chess
