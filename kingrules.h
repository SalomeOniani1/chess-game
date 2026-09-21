#ifndef KINGRULES_H
#define KINGRULES_H

#include <QString>

bool isValidKingMove(QString boardState[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn);

#endif // KINGRULES_H