#include "movegenerator.h"
#include "pawnrules.h"
#include "rookrules.h"
#include "bishoprules.h"
#include "queenrules.h"
#include "knightrules.h"
#include "kingrules.h"

void findKing(QString boardState[8][8], bool findWhiteKing, int &outRow, int &outCol)
{
    QString target = findWhiteKing ? "wK" : "bK";

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (boardState[row][col] == target)
            {
                outRow = row;
                outCol = col;
                return;
            }
        }
    }
}

bool isSquareUnderAttack(QString boardState[8][8], int targetRow, int targetCol, bool byWhite)
{
    QString attackerColor = byWhite ? "w" : "b";

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            QString piece = boardState[row][col];
            if (piece == "" || piece.left(1) != attackerColor)
                continue;

            QString pieceType = piece.mid(1, 1);
            bool canReach = false;

            if (pieceType == "P")
                canReach = isValidPawnMove(boardState, row, col, targetRow, targetCol, byWhite);
            else if (pieceType == "R")
                canReach = isValidRookMove(boardState, row, col, targetRow, targetCol, byWhite);
            else if (pieceType == "B")
                canReach = isValidBishopMove(boardState, row, col, targetRow, targetCol, byWhite);
            else if (pieceType == "Q")
                canReach = isValidQueenMove(boardState, row, col, targetRow, targetCol, byWhite);
            else if (pieceType == "N")
                canReach = isValidKnightMove(boardState, row, col, targetRow, targetCol, byWhite);
            else if (pieceType == "K")
                canReach = isValidKingMove(boardState, row, col, targetRow, targetCol, byWhite);

            if (canReach)
                return true;
        }
    }

    return false;
}

bool isKingInCheck(QString boardState[8][8], bool checkWhiteKing)
{
    int kingRow, kingCol;
    findKing(boardState, checkWhiteKing, kingRow, kingCol);
    return isSquareUnderAttack(boardState, kingRow, kingCol, !checkWhiteKing);
}

QList<ChessMove> getAllLegalMoves(QString boardState[8][8], bool forWhite)
{
    QList<ChessMove> legalMoves;
    QString ownColor = forWhite ? "w" : "b";

    for (int fromRow = 0; fromRow < 8; fromRow++)
    {
        for (int fromCol = 0; fromCol < 8; fromCol++)
        {
            QString piece = boardState[fromRow][fromCol];
            if (piece == "" || piece.left(1) != ownColor)
                continue;

            QString pieceType = piece.mid(1, 1);

            for (int toRow = 0; toRow < 8; toRow++)
            {
                for (int toCol = 0; toCol < 8; toCol++)
                {
                    bool basicMoveOk = false;

                    if (pieceType == "P")
                        basicMoveOk = isValidPawnMove(boardState, fromRow, fromCol, toRow, toCol, forWhite);
                    else if (pieceType == "R")
                        basicMoveOk = isValidRookMove(boardState, fromRow, fromCol, toRow, toCol, forWhite);
                    else if (pieceType == "B")
                        basicMoveOk = isValidBishopMove(boardState, fromRow, fromCol, toRow, toCol, forWhite);
                    else if (pieceType == "Q")
                        basicMoveOk = isValidQueenMove(boardState, fromRow, fromCol, toRow, toCol, forWhite);
                    else if (pieceType == "N")
                        basicMoveOk = isValidKnightMove(boardState, fromRow, fromCol, toRow, toCol, forWhite);
                    else if (pieceType == "K")
                        basicMoveOk = isValidKingMove(boardState, fromRow, fromCol, toRow, toCol, forWhite);

                    if (!basicMoveOk)
                        continue;

                    QString tempBoard[8][8];
                    for (int r = 0; r < 8; r++)
                        for (int c = 0; c < 8; c++)
                            tempBoard[r][c] = boardState[r][c];

                    tempBoard[toRow][toCol] = tempBoard[fromRow][fromCol];
                    tempBoard[fromRow][fromCol] = "";

                    if (!isKingInCheck(tempBoard, forWhite))
                    {
                        ChessMove move = {fromRow, fromCol, toRow, toCol};
                        legalMoves.append(move);
                    }
                }
            }
        }
    }

    return legalMoves;
}