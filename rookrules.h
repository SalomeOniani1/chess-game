#ifndef ROOKRULES_H
#define ROOKRULES_H

#include <QString>

bool isValidRookMove(QString boardState[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn);

#endif // ROOKRULES_H