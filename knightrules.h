#ifndef KNIGHTRULES_H
#define KNIGHTRULES_H

#include <QString>

bool isValidKnightMove(QString boardState[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn);

#endif // KNIGHTRULES_H