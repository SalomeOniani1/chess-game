#ifndef QUEENRULES_H
#define QUEENRULES_H

#include <QString>

bool isValidQueenMove(QString boardState[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn);

#endif // QUEENRULES_H