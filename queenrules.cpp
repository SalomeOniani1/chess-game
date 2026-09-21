#include "queenrules.h"
#include "rookrules.h"
#include "bishoprules.h"

bool isValidQueenMove(QString boardState[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn)
{
    // A queen's move is legal if it matches EITHER a rook move OR a bishop move
    return isValidRookMove(boardState, fromRow, fromCol, toRow, toCol, isWhiteTurn)
           || isValidBishopMove(boardState, fromRow, fromCol, toRow, toCol, isWhiteTurn);
}