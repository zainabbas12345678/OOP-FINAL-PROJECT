#include <iostream>
#include <string>
#include "opp.h"
using namespace std;

bool parseSquare(const string& s, int& row, int& col) {
    if (s.size() < 2) return false;
    char colCh = tolower(s[0]);
    char rowCh = s[1];
    if (colCh < 'a' || colCh > 'h') return false;
    if (rowCh < '1' || rowCh > '8') return false;
    col = colCh - 'a';
    row = rowCh - '1';
    return true;
}

string toLower(string s) {
    for (int i = 0; i < (int)s.size(); i++)
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] + 32;
    return s;
}

int main() {
    const string divider = "==========================================";
    cout << divider << "\n";
    cout << "             CHESS GAME\n";
    cout << divider << "\n\n";
    cout << "  1. Play Game\n";
    cout << "  2. Exit\n";
    cout << "  Enter choice: ";

    int choice;
    cin >> choice;
    if (choice == 2) { cout << "\n  Goodbye!\n\n"; return 0; }
    cin.ignore();

    Board game;

    while (true) {
        system("cls");
        game.displayBoard();

        cout << "\n  TURN: "
             << (game.isWhiteTurn() ? "\033[97mWHITE" : "\033[90mBLACK")
             << "\033[0m\n";
        cout << "  Enter move (e.g., e2 e4) or 'exit': ";

        string from, to;
        if (!(cin >> from)) break;

        if (toLower(from) == "exit" || toLower(from) == "quit") {
            cout << "\n  Thanks for playing!\n\n";
            break;
        }

        if (!(cin >> to)) break;

        int fromRow, fromCol, toRow, toCol;
        if (!parseSquare(from, fromRow, fromCol) ||
            !parseSquare(to,   toRow,   toCol)) {
            cout << "  Invalid format. Use e.g. e2 e4\n";
            continue;
        }

        if (!game.movePiece(fromRow, fromCol, toRow, toCol))
            cout << "  Invalid move. Try again.\n";
    }

    return 0;
}
