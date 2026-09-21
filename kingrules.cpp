#include "kingrules.h"

bool isValidKingMove(QString boardState[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn)
{
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    // A king moves exactly one square in any direction (including diagonally)
    if (rowDiff > 1 || colDiff > 1)
        return false;

    if (rowDiff == 0 && colDiff == 0)
        return false;   // "moving" to the same square isn't a move

    // Destination must be empty, or contain an enemy piece
    if (boardState[toRow][toCol] == "")
        return true;

    QString targetColor = boardState[toRow][toCol].left(1);
    QString ownColor = isWhiteTurn ? "w" : "b";
    return targetColor != ownColor;
}