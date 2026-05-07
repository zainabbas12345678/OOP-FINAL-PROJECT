#pragma once
#ifndef Piece_H
#define Piece_H

#include <iostream>
#include <string>

using namespace std;

// Colors & Formatting
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define WHITE_PIECE "\033[97m"
#define BLACK_PIECE "\033[30m"
#define BG_LIGHT    "\033[48;5;250m"
#define BG_DARK     "\033[48;5;240m"
#define ERROR_COLOR "\033[91m"
#define TURN_BOX    "\033[94m"

class Piece {
public:
    virtual string getIcon() const = 0;
    virtual bool isWhite() const = 0;
    virtual ~Piece() {}
};

// Piece Subclasses
class Pawn : public Piece {
    bool white;
public:
    Pawn(bool w) : white(w) {}
    bool isWhite() const override { return white; }
    string getIcon() const override { return " P "; }
};

class Rook : public Piece {
    bool white;
public:
    Rook(bool w) : white(w) {}
    bool isWhite() const override { return white; }
    string getIcon() const override { return " R "; }
};

class Knight : public Piece {
    bool white;
public:
    Knight(bool w) : white(w) {}
    bool isWhite() const override { return white; }
    string getIcon() const override { return " N "; }
};

class Bishop : public Piece {
    bool white;
public:
    Bishop(bool w) : white(w) {}
    bool isWhite() const override { return white; }
    string getIcon() const override { return " B "; }
};

class Queen : public Piece {
    bool white;
public:
    Queen(bool w) : white(w) {}
    bool isWhite() const override { return white; }
    string getIcon() const override { return " Q "; }
};

class King : public Piece {
    bool white;
public:
    King(bool w) : white(w) {}
    bool isWhite() const override { return white; }
    string getIcon() const override { return " K "; }
};

class Board {
    Piece* grid[8][8];
public:
    Board();
    ~Board();
    void setup();
    void display() const;
    bool move(string from, string to, bool whiteTurn);
};

#endif