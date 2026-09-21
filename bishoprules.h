#ifndef BISHOPRULES_H
#define BISHOPRULES_H

#include <QString>

bool isValidBishopMove(QString boardState[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn);

#endif // BISHOPRULES_H