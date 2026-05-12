#ifndef OPP_H
#define OPP_H
#include <iostream>
#include <string>
using namespace std;

// ANSI COLOR CODES
#define RESET    "\033[0m"
#define BOLD     "\033[1m"
#define BG_DARK  "\033[48;5;238m"
#define BG_LIGHT "\033[48;5;245m"
#define FG_WHITE "\033[97m"
#define FG_BLACK "\033[30m"
#define FG_LABEL "\033[37m"

// PIECE BASE CLASS
class Piece {
protected:
    bool WhiteOrNo;
    char Symbol;
public:
    Piece(bool white, char sym);
    virtual ~Piece();
    bool getColor()  const;
    char getSymbol() const;
    virtual bool canMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) = 0;
};

// DERIVED PIECE CLASSES
class Pawn   : public Piece { public: Pawn(bool w);   bool canMove(int, int, int, int, Piece* [8][8]) override; };
class Rook   : public Piece { public: Rook(bool w);   bool canMove(int, int, int, int, Piece* [8][8]) override; };
class Knight : public Piece { public: Knight(bool w); bool canMove(int, int, int, int, Piece* [8][8]) override; };
class Bishop : public Piece { public: Bishop(bool w); bool canMove(int, int, int, int, Piece* [8][8]) override; };
class Queen  : public Piece { public: Queen(bool w);  bool canMove(int, int, int, int, Piece* [8][8]) override; };
class King   : public Piece { public: King(bool w);   bool canMove(int, int, int, int, Piece* [8][8]) override; };

// BOARD
class Board {
private:
    Piece* board[8][8];
    bool   whiteTurn;
    bool   gameOver;
public:
    Board();
    ~Board();
    void   setupBoard();
    void   displayBoard() const;
    Piece* getPiece(int row, int col) const;
    bool   movePiece(int fromRow, int fromCol, int toRow, int toCol);
    void   switchTurn();
    bool   isWhiteTurn() const;
    bool   isGameOver()  const;
    bool   isKingInCheck(bool whiteKing);
    bool   isCheckmate(bool whiteKing);
};

#endif
