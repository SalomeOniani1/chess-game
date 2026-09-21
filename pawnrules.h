#ifndef PAWNRULES_H
#define PAWNRULES_H

#include <QString>

bool isValidPawnMove(QString boardState[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn);
//Why pass boardState in as a parameter, rather than having this function reach into ChessWindow directly: this keeps pawnrules.cpp fully independent — it doesn't need to know ChessWindow exists at all, just an 8×8 grid of strings. That's what makes it reusable, and easy to reason about/test in isolation later.

#endif // PAWNRULES_H