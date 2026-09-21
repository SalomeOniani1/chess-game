#include "rookrules.h"

bool isValidRookMove(QString boardState[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn)
{
    // Rooks move only in straight lines: same row, or same column
    if (fromRow != toRow && fromCol != toCol)
        return false;

    // Determine step direction along row or column (one of these will be 0)
    int rowStep = (toRow > fromRow) ? 1 : (toRow < fromRow) ? -1 : 0;
    int colStep = (toCol > fromCol) ? 1 : (toCol < fromCol) ? -1 : 0;

    // Walk the path from (fromRow, fromCol) to (toRow, toCol), checking every square in between is empty
    int checkRow = fromRow + rowStep;
    int checkCol = fromCol + colStep;

    while (checkRow != toRow || checkCol != toCol)
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