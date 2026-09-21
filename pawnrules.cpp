#include "pawnrules.h"

bool isValidPawnMove(QString boardState[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn)
{
    int direction = isWhiteTurn ? -1 : 1;   // white moves up (decreasing row), black moves down
    int startRow = isWhiteTurn ? 6 : 1;     // starting row for each color

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    // Straight move (no capture)
    if (colDiff == 0 && boardState[toRow][toCol] == "")
    {
        if (rowDiff == direction)
            return true;   // normal 1-square move

        if (fromRow == startRow && rowDiff == 2 * direction && boardState[fromRow + direction][fromCol] == "")
            return true;   // first-move 2-square, only if path is clear
    }

    // Diagonal capture
    if (abs(colDiff) == 1 && rowDiff == direction && boardState[toRow][toCol] != "")
    {
        QString targetColor = boardState[toRow][toCol].left(1);
        QString ownColor = isWhiteTurn ? "w" : "b";
        if (targetColor != ownColor)
            return true;   // capturing an enemy piece
    }

    return false;   // anything else is illegal
}