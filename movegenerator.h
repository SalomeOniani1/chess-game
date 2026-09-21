#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include <QString>
#include <QList>

struct ChessMove
{
    int fromRow, fromCol, toRow, toCol;
};

void findKing(QString boardState[8][8], bool findWhiteKing, int &outRow, int &outCol);
bool isSquareUnderAttack(QString boardState[8][8], int targetRow, int targetCol, bool byWhite);
bool isKingInCheck(QString boardState[8][8], bool checkWhiteKing);
QList<ChessMove> getAllLegalMoves(QString boardState[8][8], bool forWhite);

#endif // MOVEGENERATOR_H