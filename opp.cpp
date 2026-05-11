#include "opp.h"
#include <cmath>
using namespace std;

// ===================== PIECE BASE CLASS ==============================
Piece::Piece(bool white, char sym) : WhiteOrNo(white), Symbol(sym) {}
Piece::~Piece() {}
bool Piece::getColor()  const { return WhiteOrNo; }
char Piece::getSymbol() const { return Symbol; }

// ===================== PAWN ==========================================
Pawn::Pawn(bool white) : Piece(white, white ? 'P' : 'p') {}
bool Pawn::canMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) {
    int dir = (WhiteOrNo ? 1 : -1);
    if (c1 == c2) {
        if (r2 == r1 + dir && board[r2][c2] == nullptr) return true;
        if ((WhiteOrNo && r1 == 1) || (!WhiteOrNo && r1 == 6))
            if (r2 == r1 + 2 * dir && board[r1 + dir][c1] == nullptr && board[r2][c2] == nullptr)
                return true;
    }
    if (abs(c1 - c2) == 1 && r2 == r1 + dir)
        if (board[r2][c2] && board[r2][c2]->getColor() != WhiteOrNo)
            return true;
    return false;
}

// ===================== ROOK ==========================================
Rook::Rook(bool white) : Piece(white, white ? 'R' : 'r') {}
bool Rook::canMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) {
    if (r1 != r2 && c1 != c2) return false;
    if (r1 == r2) {
        int step = (c2 > c1 ? 1 : -1);
        for (int c = c1 + step; c != c2; c += step) if (board[r1][c]) return false;
    } else {
        int step = (r2 > r1 ? 1 : -1);
        for (int r = r1 + step; r != r2; r += step) if (board[r][c1]) return false;
    }
    return true;
}

// ===================== KNIGHT ========================================
Knight::Knight(bool white) : Piece(white, white ? 'N' : 'n') {}
bool Knight::canMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) {
    int dr = abs(r1 - r2), dc = abs(c1 - c2);
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

// ===================== BISHOP ========================================
Bishop::Bishop(bool white) : Piece(white, white ? 'B' : 'b') {}
bool Bishop::canMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) {
    if (abs(r1 - r2) != abs(c1 - c2)) return false;
    int rS = (r2 > r1 ? 1 : -1), cS = (c2 > c1 ? 1 : -1);
    int r = r1 + rS, c = c1 + cS;
    while (r != r2) { if (board[r][c]) return false; r += rS; c += cS; }
    return true;
}

// ===================== QUEEN =========================================
Queen::Queen(bool white) : Piece(white, white ? 'Q' : 'q') {}
bool Queen::canMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) {
    Rook   rv(WhiteOrNo);
    Bishop bv(WhiteOrNo);
    return rv.canMove(r1, c1, r2, c2, board) || bv.canMove(r1, c1, r2, c2, board);
}

// ===================== KING ==========================================
King::King(bool white) : Piece(white, white ? 'K' : 'k') {}
bool King::canMove(int r1, int c1, int r2, int c2, Piece* board[8][8]) {
    return abs(r1 - r2) <= 1 && abs(c1 - c2) <= 1 && (r1 != r2 || c1 != c2);
}

// ===================== BOARD =========================================
Board::Board() : whiteTurn(true), gameOver(false) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board[i][j] = nullptr;
    setupBoard();
}

Board::~Board() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            delete board[i][j];
}

void Board::setupBoard() {
    // White pieces (row 0 = rank 1)
    board[0][0] = new Rook(true);   board[0][1] = new Knight(true);
    board[0][2] = new Bishop(true); board[0][3] = new Queen(true);
    board[0][4] = new King(true);   board[0][5] = new Bishop(true);
    board[0][6] = new Knight(true); board[0][7] = new Rook(true);
    for (int i = 0; i < 8; i++) board[1][i] = new Pawn(true);

    // Black pieces (row 7 = rank 8)
    board[7][0] = new Rook(false);   board[7][1] = new Knight(false);
    board[7][2] = new Bishop(false); board[7][3] = new Queen(false);
    board[7][4] = new King(false);   board[7][5] = new Bishop(false);
    board[7][6] = new Knight(false); board[7][7] = new Rook(false);
    for (int i = 0; i < 8; i++) board[6][i] = new Pawn(false);
}

void Board::displayBoard() const {
    const string divider = "==========================================";
    cout << "\n" << FG_LABEL << divider << RESET << "\n";
    cout << BOLD << FG_LABEL << "             CHESS GAME" << RESET << "\n";
    cout << FG_LABEL << divider << RESET << "\n\n";

    cout << "  ";
    for (char c = 'a'; c <= 'h'; c++)
        cout << FG_LABEL << "  " << c << RESET;
    cout << "\n";

    for (int row = 7; row >= 0; row--) {
        cout << FG_LABEL << (row + 1) << " " << RESET;
        for (int col = 0; col < 8; col++) {
            bool light = (row + col) % 2 == 0;
            string bg = light ? BG_LIGHT : BG_DARK;
            Piece* p = board[row][col];
            if (p) {
                string fg = p->getColor() ? FG_WHITE : FG_BLACK;
                cout << bg << fg << BOLD << " " << p->getSymbol() << " " << RESET;
            } else {
                cout << bg << "   " << RESET;
            }
        }
        cout << " " << FG_LABEL << (row + 1) << RESET << "\n";
    }

    cout << "  ";
    for (char c = 'a'; c <= 'h'; c++)
        cout << FG_LABEL << "  " << c << RESET;
    cout << "\n";
}

Piece* Board::getPiece(int row, int col) const {
    if (row < 0 || row >= 8 || col < 0 || col >= 8) return nullptr;
    return board[row][col];
}

bool Board::isGameOver() const { return gameOver; }

bool Board::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    Piece* p = board[fromRow][fromCol];
    if (!p) return false;
    if (p->getColor() != whiteTurn) { cout << "  Not your turn!\n"; return false; }
    if (board[toRow][toCol] && board[toRow][toCol]->getColor() == p->getColor()) return false;
    if (!p->canMove(fromRow, fromCol, toRow, toCol, board)) return false;

    Piece* target = board[toRow][toCol];
    bool kingCaptured = false;

    if (target) {
        if (target->getSymbol() == 'K' || target->getSymbol() == 'k')
            kingCaptured = true;

        cout << "\n  >> " << (p->getColor() ? "White" : "Black")
             << " " << p->getSymbol() << " captures "
             << (target->getColor() ? "White" : "Black")
             << " " << target->getSymbol() << "!\n";
        delete target;
    }

    board[toRow][toCol]    = p;
    board[fromRow][fromCol] = nullptr;

    // King captured — show message, game continues
    if (kingCaptured) {
        string winner = p->getColor() ? "WHITE" : "BLACK";
        string loser  = p->getColor() ? "BLACK" : "WHITE";
        cout << "\n  ==========================================\n";
        cout << "  ***  " << loser << " KING KILLED!           ***\n";
        cout << "  ***  " << winner << " WINS THIS ROUND!      ***\n";
        cout << "  ==========================================\n";
        // game continues — no break, no exit
    }

    switchTurn();
    return true;
}

bool Board::isWhiteTurn() const { return whiteTurn; }
void Board::switchTurn()        { whiteTurn = !whiteTurn; }

bool Board::isKingInCheck(bool whiteKing) {
    int kr = -1, kc = -1;
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (board[r][c] && board[r][c]->getColor() == whiteKing &&
               (board[r][c]->getSymbol() == 'K' || board[r][c]->getSymbol() == 'k'))
            { kr = r; kc = c; }

    if (kr == -1) return false;

    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++) {
            Piece* p = board[r][c];
            if (p && p->getColor() != whiteKing && p->canMove(r, c, kr, kc, board))
                return true;
        }
    return false;
}

bool Board::isCheckmate(bool whiteKing) {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++) {
            Piece* p = board[r][c];
            if (p && p->getColor() == whiteKing) {
                for (int tr = 0; tr < 8; tr++)
                    for (int tc = 0; tc < 8; tc++) {
                        Piece* bk = board[tr][tc];
                        if (p->canMove(r, c, tr, tc, board) && (!bk || bk->getColor() != whiteKing)) {
                            board[tr][tc] = p; board[r][c] = nullptr;
                            bool safe = !isKingInCheck(whiteKing);
                            board[r][c] = p;   board[tr][tc] = bk;
                            if (safe) return false;
                        }
                    }
        }
    }
    return true;
}
