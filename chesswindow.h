#ifndef CHESSWINDOW_H
#define CHESSWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QTimer>
#include "movegenerator.h"
#include <QCloseEvent>

class ChessWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChessWindow(QWidget *parent = nullptr);
    ~ChessWindow() override;
private:
    QString boardState[8][8];  // e.g. "wP" = white pawn, "bK" = black king, "" = empty
    QLabel *titleLabel;
    QGridLayout *layout;
    QPushButton *board[8][8];
    QPushButton *flipButton;
    int squareSize;   // for button size
    void updateBoardIcons();     //refreshes icons based on boardState
    int selectedRow = -1;   // -1 means "nothing selected"
    int selectedCol = -1;
    int selectedDataRow = -1;   // data row (for boardState)
    int selectedDataCol = -1;
    QString normalColor(int row, int col);
    bool isWhiteTurn = true;   // white moves first
    QLabel *turnLabel;
    void blinkInvalidMove(int row, int col);
    bool gameStarted = false;
    bool boardFlipped = false;   // replaces the need to rewrite boardState
    int checkHighlightRow = -1;
    int checkHighlightCol = -1;
    void resetGame(); //to start new game

    bool vsComputer = false;      // two players (default), true = vs AI
    QPushButton *modeButton;

    void makeComputerMove();

    void saveGame();
    bool loadGame();   // returns true if a saved game was found and loaded

    QPushButton *newGameButton;
private slots:
    void flipBoard();
    void onSquareClicked(int row, int col);
    void toggleMode();
    void onNewGameClicked();

protected:
    void closeEvent(QCloseEvent *event) override;

};
#endif // CHESSWINDOW_H
