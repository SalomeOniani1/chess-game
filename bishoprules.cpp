#include "bishoprules.h"

bool isValidBishopMove(QString boardState[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn)
{
    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    // Bishops move only diagonally: row distance must equal column distance
    if (abs(rowDiff) != abs(colDiff) || rowDiff == 0)
        return false;

    int rowStep = (rowDiff > 0) ? 1 : -1;
    int colStep = (colDiff > 0) ? 1 : -1;

    // Walk the diagonal path, checking every square in between is empty
    int checkRow = fromRow + rowStep;
    int checkCol = fromCol + colStep;

    while (checkRow != toRow)
    {
        if (boardState[checkRow][checkCol] != "")
            return false;   // something is blocking the path

        checkRow += rowStep;
        checkCol += colStep;
    }

    // Destination must be empty, or contain an enemy piece
    if (boardState[toRow][toCol] == "")
        return true;

    QString targetColor = boardState[toRow][toCol].left(1);
    QString ownColor = isWhiteTurn ? "w" : "b";
    return targetColor != ownColor;
}