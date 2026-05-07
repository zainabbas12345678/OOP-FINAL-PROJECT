#include "piece.h"

Board::Board() {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++) grid[r][c] = nullptr;
    setup();
}

Board::~Board() {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++) delete grid[r][c];
}

void Board::setup() {
    // Black pieces
    grid[0][0] = new Rook(false);   grid[0][1] = new Knight(false);
    grid[0][2] = new Bishop(false); grid[0][3] = new Queen(false);
    grid[0][4] = new King(false);   grid[0][5] = new Bishop(false);
    grid[0][6] = new Knight(false); grid[0][7] = new Rook(false);
    for (int i = 0; i < 8; i++) grid[1][i] = new Pawn(false);

    // White pieces
    grid[7][0] = new Rook(true);    grid[7][1] = new Knight(true);
    grid[7][2] = new Bishop(true);  grid[7][3] = new Queen(true);
    grid[7][4] = new King(true);    grid[7][5] = new Bishop(true);
    grid[7][6] = new Knight(true);  grid[7][7] = new Rook(true);
    for (int i = 0; i < 8; i++) grid[6][i] = new Pawn(true);
}

void Board::display() const {
    cout << "\n     a  b  c  d  e  f  g  h\n";
    for (int r = 0; r < 8; r++) {
        cout << " " << (8 - r) << " ";
        for (int c = 0; c < 8; c++) {
            if ((r + c) % 2 == 0) cout << BG_LIGHT;
            else cout << BG_DARK;

            if (grid[r][c]) {
                cout << (grid[r][c]->isWhite() ? WHITE_PIECE : BLACK_PIECE);
                cout << grid[r][c]->getIcon();
            }
            else {
                cout << "   ";
            }
            cout << RESET;
        }
        cout << " " << (8 - r) << "\n";
    }
    cout << "     a  b  c  d  e  f  g  h\n\n";
}

bool Board::move(string from, string to, bool whiteTurn) {
    if (from.length() < 2 || to.length() < 2) return false;

    int fc = from[0] - 'a', fr = 8 - (from[1] - '0');
    int tc = to[0] - 'a', tr = 8 - (to[1] - '0');

    // Bounds checking
    if (fc < 0 || fc > 7 || fr < 0 || fr > 7 || tc < 0 || tc > 7 || tr < 0 || tr > 7) return false;

    Piece* p = grid[fr][fc];

    // Check if space is empty or wrong color
    if (!p || p->isWhite() != whiteTurn) return false;

    // Simple move (no rule validation yet)
    delete grid[tr][tc];
    grid[tr][tc] = grid[fr][fc];
    grid[fr][fc] = nullptr;
    return true;
}