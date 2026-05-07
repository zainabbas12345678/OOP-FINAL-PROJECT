#include "Piece.h"

int main() {
    Board b;
    bool whiteTurn = true;
    string errorMsg = "";

    while (true) {
        // Use "cls" for Windows, "clear" for Linux/Mac
        system("cls");

        cout << BOLD << "  ========================================" << RESET << endl;
        cout << BOLD << "               CHESS GAME                 " << RESET << endl;
        cout << BOLD << "  ========================================" << RESET << endl;

        b.display();

        if (!errorMsg.empty()) {
            cout << ERROR_COLOR << BOLD << "  ERROR: " << errorMsg << RESET << endl;
            errorMsg = "";
        }

        cout << TURN_BOX << WHITE_PIECE << BOLD << "  TURN: "
            << (whiteTurn ? "WHITE " : "BLACK ") << RESET << endl;
        cout << "  Enter move (e.g., e2 e4) or 'exit': ";

        string m1, m2;
        if (!(cin >> m1)) break;
        if (m1 == "exit") break;
        if (!(cin >> m2)) break;

        if (b.move(m1, m2, whiteTurn)) {
            whiteTurn = !whiteTurn;
        }
        else {
            errorMsg = "Illegal Move! Try again.";
        }
    }
    return 0;
}