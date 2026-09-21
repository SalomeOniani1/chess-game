#include "knightrules.h"

bool isValidKnightMove(QString boardState[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn)
{
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    // A knight moves in an "L" shape: 2 squares one way, 1 square the other
    bool isLShape = (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);

    if (!isLShape)
        return false;

    // Destination must be empty, or contain an enemy piece
    if (boardState[toRow][toCol] == "")
        return true;

    QString targetColor = boardState[toRow][toCol].left(1);
    QString ownColor = isWhiteTurn ? "w" : "b";
    return targetColor != ownColor;
}