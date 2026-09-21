#include "chesswindow.h"
#include "pawnrules.h"
#include "rookrules.h"
#include "bishoprules.h"
#include "queenrules.h"
#include "knightrules.h"
#include "kingrules.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QFile>
#include <QTextStream>

void ChessWindow::blinkInvalidMove(int row, int col)
{
    QString original = "background-color: " + normalColor(row, col) + ";";
    QString red = "background-color: red;";

    board[row][col]->setStyleSheet(red);

    QTimer::singleShot(150, this, [this, row, col, original]()
                       {
                           board[row][col]->setStyleSheet(original);
                       });
    //QTimer::singleShot(150, ...) schedules a lambda to run once, 150 milliseconds later, without blocking the rest of your program (Qt's event loop keeps running normally in the meantime — this is the standard way to do "wait, then do something" in Qt, since you can't just sleep() in a GUI app or the whole window would freeze). The square turns red immediately, then reverts back to its normal color a moment later.
}

void ChessWindow::updateBoardIcons()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            int dataRow = boardFlipped ? 7 - row : row;
            int dataCol = boardFlipped ? 7 - col : col;

            board[row][col]->setIcon(QIcon());  // clear old icon first

            if (boardState[dataRow ][dataCol] == "wP")
            {
                board[row][col]->setIcon(QIcon(":/pieces/wP.png"));
                board[row][col]->setIconSize(QSize(squareSize * 0.8, squareSize * 0.8));
            }
            else if (boardState[dataRow ][dataCol] == "bP")
            {
                board[row][col]->setIcon(QIcon(":/pieces/bP.png"));
                board[row][col]->setIconSize(QSize(squareSize * 0.8, squareSize * 0.8));
            }
            else if (boardState[dataRow ][dataCol] == "bR")
            {
                board[row][col]->setIcon(QIcon(":/pieces/bR.png"));
                board[row][col]->setIconSize(QSize(squareSize * 0.8, squareSize * 0.8));
            }
            else if (boardState[dataRow ][dataCol ] == "bN")
            {
                board[row][col]->setIcon(QIcon(":/pieces/bN.png"));
                board[row][col]->setIconSize(QSize(squareSize * 0.8, squareSize * 0.8));
            }
            else if (boardState[dataRow ][dataCol ] == "bQ")
            {
                board[row][col]->setIcon(QIcon(":/pieces/bQ.png"));
                board[row][col]->setIconSize(QSize(squareSize * 0.8, squareSize * 0.8));
            }
            else if (boardState[dataRow ][dataCol ] == "bB")
            {
                board[row][col]->setIcon(QIcon(":/pieces/bB.png"));
                board[row][col]->setIconSize(QSize(squareSize * 0.8, squareSize * 0.8));
            }
            else if (boardState[dataRow ][dataCol ] == "bK")
            {
                board[row][col]->setIcon(QIcon(":/pieces/bK.png"));
                board[row][col]->setIconSize(QSize(squareSize * 0.8, squareSize * 0.8));
            }
            else if (boardState[dataRow ][dataCol ] == "wR")
            {
                board[row][col]->setIcon(QIcon(":/pieces/wR.png"));
                board[row][col]->setIconSize(QSize(squareSize * 0.8, squareSize * 0.8));
            }
            else if (boardState[dataRow ][dataCol ] == "wQ")
            {
                board[row][col]->setIcon(QIcon(":/pieces/wQ.png"));
                board[row][col]->setIconSize(QSize(squareSize * 0.8, squareSize * 0.8));
            }
            else if (boardState[dataRow ][dataCol ] == "wN")
            {
                board[row][col]->setIcon(QIcon(":/pieces/wN.png"));
                board[row][col]->setIconSize(QSize(squareSize * 0.8, squareSize * 0.8));
            }
            else if (boardState[dataRow ][dataCol ] == "wB")
            {
                board[row][col]->setIcon(QIcon(":/pieces/wB.png"));
                board[row][col]->setIconSize(QSize(squareSize * 0.8, squareSize * 0.8));
            }
            else if (boardState[dataRow ][dataCol ] == "wK")
            {
                board[row][col]->setIcon(QIcon(":/pieces/wK.png"));
                board[row][col]->setIconSize(QSize(squareSize * 0.8, squareSize * 0.8));
            }
        }
    }
}


void ChessWindow::flipBoard()
{
    boardFlipped = !boardFlipped;

    updateBoardIcons();  // redraw pieces in their new positions
}

QString ChessWindow::normalColor(int row, int col)
{
    if ((row + col) % 2 == 0)
        return "white";
    else
        return "gray";
}

void ChessWindow::onSquareClicked(int row, int col)
{
    int dataRow = boardFlipped ? 7 - row : row;
    int dataCol = boardFlipped ? 7 - col : col;

    // If nothing was selected yet, just select this square
    if (selectedRow == -1)
    {
        // check the piece's color matches whose turn it is
        QString pieceColor = boardState[dataRow][dataCol].left(1);  // "w" or "b"
        //What .left(1) does: since every piece string is 2 characters (e.g. "wP", "bK"), .left(1) grabs just the first character — the color prefix — as a QString, which we then compare against "w" or "b".

        // Nothing selected yet — only select if this square actually has a piece
        if (boardState[dataRow][dataCol] != "")
        {
            if ((isWhiteTurn && pieceColor == "w") || (!isWhiteTurn && pieceColor == "b"))
            {
                selectedRow = row; // visual — for highlighting the button
                selectedCol = col;
                selectedDataRow = dataRow;   // data — for reading/writing boardState
                selectedDataCol = dataCol;
                board[row][col]->setStyleSheet("background-color: yellow;");
            }
        }
    }
    else
    {
        QString movingPiece = boardState[selectedDataRow][selectedDataCol];

        bool moveIsValid = false;

        if (movingPiece == "wP" || movingPiece == "bP")
        {
            moveIsValid = isValidPawnMove(boardState, selectedDataRow, selectedDataCol, dataRow, dataCol, isWhiteTurn);
        }
        else if (movingPiece == "wR" || movingPiece == "bR")
        {
            moveIsValid = isValidRookMove(boardState, selectedDataRow, selectedDataCol, dataRow, dataCol, isWhiteTurn);
        }
        else if (movingPiece == "wB" || movingPiece == "bB")
        {
            moveIsValid = isValidBishopMove(boardState, selectedDataRow, selectedDataCol, dataRow, dataCol, isWhiteTurn);
        }
        else if (movingPiece == "wQ" || movingPiece == "bQ")
        {
             moveIsValid = isValidQueenMove(boardState, selectedDataRow, selectedDataCol, dataRow, dataCol, isWhiteTurn);
        }
        else if (movingPiece == "wN" || movingPiece == "bN")
        {
            moveIsValid = isValidKnightMove(boardState, selectedDataRow, selectedDataCol, dataRow, dataCol, isWhiteTurn);
        }
        else if (movingPiece == "wK" || movingPiece == "bK")
        {
            moveIsValid = isValidKingMove(boardState, selectedDataRow, selectedDataCol, dataRow, dataCol, isWhiteTurn);
        }

        if (moveIsValid)
        {
            // Simulate the move on a temporary board
            QString tempBoard[8][8];
            for (int r = 0; r < 8; r++)
                for (int c = 0; c < 8; c++)
                    tempBoard[r][c] = boardState[r][c];

            tempBoard[dataRow][dataCol] = tempBoard[selectedDataRow][selectedDataCol];
            tempBoard[selectedDataRow][selectedDataCol] = "";

            if (isKingInCheck(tempBoard, isWhiteTurn))
            {
                moveIsValid = false;   // reject — real boardState was never touched, so nothing to undo
            }
        }

        if (moveIsValid)
        {

            // A square was already selected — treat this click as the destination

            // Move the piece in the data model
            boardState[dataRow][dataCol] = boardState[selectedDataRow][selectedDataCol];
            boardState[selectedDataRow][selectedDataCol] = "";


            // Restore the old square's color (it's empty now)
            board[selectedRow][selectedCol]->setStyleSheet(
                "background-color: " + normalColor(selectedRow, selectedCol) + ";"
                );


            gameStarted = true;         // game start
            flipButton->setEnabled(false);   // disable flipping once game has started
            modeButton->setEnabled(false);   // lock mode choice once the game has started


            isWhiteTurn = !isWhiteTurn;   // switch turns after every move

            turnLabel->setStyleSheet(
                isWhiteTurn
                    ? "background-color: white; border: 1px solid black;"
                    : "background-color: black; border: 1px solid black;"
                );
            //we're changing the label's background color — white square means it's white's turn, gray square means black's turn. The border: 1px solid black; keeps a visible outline so the white square doesn't disappear against the light window background.


            updateBoardIcons(); // Redraw all icons to reflect the move

            // clear any previous check highlight
            if (checkHighlightRow != -1)
            {
                board[checkHighlightRow][checkHighlightCol]->setStyleSheet(
                    "background-color: " + normalColor(checkHighlightRow, checkHighlightCol) + ";"
                    );
                checkHighlightRow = -1;
                checkHighlightCol = -1;
            }

            // check whether the player who is about to move (isWhiteTurn, already flipped) is now in check
            int kingDataRow, kingDataCol;
            findKing(boardState, isWhiteTurn, kingDataRow, kingDataCol);

            bool inCheck = isSquareUnderAttack(boardState, kingDataRow, kingDataCol, !isWhiteTurn);

            if (inCheck)
            {
                int kingVisualRow = boardFlipped ? 7 - kingDataRow : kingDataRow;
                int kingVisualCol = boardFlipped ? 7 - kingDataCol : kingDataCol;

                board[kingVisualRow][kingVisualCol]->setStyleSheet("background-color: red;");

                checkHighlightRow = kingVisualRow;
                checkHighlightCol = kingVisualCol;

                //check if this is checkmate
                if (getAllLegalMoves(boardState, isWhiteTurn).isEmpty())
                {
                    QString winner = isWhiteTurn ? "Black" : "White";

                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Checkmate");
                    msgBox.setText(winner + " wins by checkmate!");
                    msgBox.setStyleSheet("QLabel{font-size: 20px; font-weight: bold;} QPushButton{font-size: 14px;}");
                    QPushButton *playAgainButton = msgBox.addButton("Play Again", QMessageBox::AcceptRole);
                    msgBox.exec();

                    if (msgBox.clickedButton() == playAgainButton)
                    {
                        resetGame();
                        return; //to stop here, don't run any more of onSquareClicked
                    }
                }
            }

            //trigger computer's move right here, as the last thing in this block
            if (vsComputer && isWhiteTurn == false)
            {
                QTimer::singleShot(500, this, [this]()
                                   {
                                       makeComputerMove();
                                   });
            }

        }
        else
        {
            blinkInvalidMove(row, col);   // flash the square they tried to move to
        }


        // always restore the origin square's color, valid move or not
        board[selectedRow][selectedCol]->setStyleSheet(
            "background-color: " + normalColor(selectedRow, selectedCol) + ";"
            );
        // Clear selection
        selectedRow = -1;
        selectedCol = -1;
        selectedDataRow = -1;
        selectedDataCol = -1;
    }
}

ChessWindow::ChessWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Chess Game");
    setWindowIcon(QIcon(":/pieces/chess.png"));

    // Get the screen the window will appear on
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();

    // Use e.g. 70% of the screen's smaller dimension, keeping it square
    int side = qMin(screenGeometry.width(), screenGeometry.height()) * 0.7; resize(side, side);
    squareSize = side / 8;

    // Center the window on screen
    //move(screenGeometry.center() - rect().center());

    //if we want uo window little
    QPoint centerPos = screenGeometry.center() - rect().center();
    move(centerPos.x(), centerPos.y() - 100);  // shift up by 100px

    if (!loadGame())
    {
        // inicialise start position of game
        QString backRank[8] = {"R", "N", "B", "Q", "K", "B", "N", "R"};
        for (int col = 0; col < 8; col++)
        {
            boardState[6][col] = "wP";  // row 6 = white pawns' starting row
            boardState[1][col] = "bP";  // row 1 = black pawns' starting row
            boardState[7][col] = "w" + backRank[col];  // white back rank
            boardState[0][col] = "b" + backRank[col];  // black back rank
        }
    }

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // Outer vertical layout: title on top, board below
    QVBoxLayout *mainLayout = new QVBoxLayout();
    central->setLayout(mainLayout);

    QHBoxLayout *topRow = new QHBoxLayout();       // horizontal row for title + button

    turnLabel = new QLabel();
    turnLabel->setFixedSize(30, 30);            // small square
    turnLabel->setStyleSheet(
        isWhiteTurn
            ? "background-color: white; border: 1px solid black;"
            : "background-color: black; border: 1px solid black;"
        );
    mainLayout->addWidget(turnLabel, 0, Qt::AlignLeft);  // aligned to the left
    //Why Qt::AlignLeft here: by default, a widget added to a QVBoxLayout stretches to fill the row's width. Since we want a small square sitting at the left edge (not centered or stretched), we tell the layout to align it left and let it keep its setFixedSize.


    titleLabel = new QLabel("Chess Game");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 28px; color: darkblue; font-weight: bold; margin: 10px;");

    modeButton = new QPushButton("Two Player");
    modeButton->setFixedSize(110, 30);
    modeButton->setText(vsComputer ? "Against AI" : "Two Player");
    connect(modeButton, &QPushButton::clicked, this, &ChessWindow::toggleMode);

    newGameButton = new QPushButton("New Game");
    newGameButton->setFixedSize(90, 30);
    connect(newGameButton, &QPushButton::clicked, this, &ChessWindow::onNewGameClicked);



    flipButton = new QPushButton();
    flipButton->setIcon(QIcon(":/pieces/flipIcon.png"));
    flipButton->setIconSize(QSize(40, 40));
    flipButton->setFixedSize(50, 50);
    flipButton->setFlat(false);
    flipButton->setStyleSheet(
        "QPushButton {"
        "   border: 2px solid gray;"
        "   border-radius: 6px;"
        "   background-color: #f5f0f0;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d9d9d9;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #c5c0c0;"
        "}"
        );
    connect(flipButton, &QPushButton::clicked, this, &ChessWindow::flipBoard);
     //What connect(...) does: this is Qt's signal/slot mechanism — it tells Qt "whenever flipButton emits its clicked signal (i.e., someone clicks it), call this object's flipBoard() function." This is why flipBoard() needed to be declared under private slots: in the header — only slots (or any regular function, in modern Qt) can be connected this way.

    topRow->addWidget(turnLabel);   // far left
    topRow->addStretch();
    topRow->addWidget(newGameButton);   // add wherever fits in your row order
    topRow->addStretch(); // pushes title toward center
    topRow->addWidget(titleLabel);
    topRow->addStretch(); //balances the left stretch
    topRow->addWidget(modeButton);   // add before or after flipButton, your choice
    topRow->addWidget(flipButton); //button sits at the far right

    mainLayout->addLayout(topRow);   // topRow goes INTO mainLayout



   // Board grid goes inside its own layout, added into mainLayout
    layout = new QGridLayout();
    mainLayout->addLayout(layout);



    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {

            board[row][col] = new QPushButton();
            board[row][col]->setFixedSize(squareSize,squareSize);

            if((row + col) % 2 == 0)
            {
                board[row][col]->setStyleSheet("background-color:white;");
            }
            else
            {
                board[row][col]->setStyleSheet("background-color:gray;");
            }

            layout->addWidget(board[row][col],row,col);
            connect(board[row][col], &QPushButton::clicked, this, [this, row, col]()
                    {
                        onSquareClicked(row, col);
                    }); //QPushButton::clicked doesn't carry any information about which button was clicked, or what row/col it belongs to — that context only exists in loop variables. A lambda lets us "capture" row and col at the moment each button is created, so when that specific button is later clicked, it calls onSquareClicked with the correct coordinates baked in. [this, row, col] means: capture this (so we can call the member function) plus the current values of row and col.
        }
    }
    updateBoardIcons();
}

void ChessWindow::onNewGameClicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "New Game",
        "Start a new game? Current progress will be lost.",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes)
    {
        resetGame();
        modeButton->setEnabled(true);   // NEW — re-allow choosing mode for the new game
    }
}

void ChessWindow::toggleMode()
{
    vsComputer = !vsComputer;
    modeButton->setText(vsComputer ? "Against AI" : "Two Player");
}

void ChessWindow::resetGame()
{
    // Clear any check highlight still showing
    if (checkHighlightRow != -1)
    {
        board[checkHighlightRow][checkHighlightCol]->setStyleSheet(
            "background-color: " + normalColor(checkHighlightRow, checkHighlightCol) + ";"
            );
        checkHighlightRow = -1;
        checkHighlightCol = -1;
    }

    // Clear boardState completely
    for (int row = 0; row < 8; row++)
        for (int col = 0; col < 8; col++)
            boardState[row][col] = "";

    // Re-set starting position (same logic as constructor)
    QString backRank[8] = {"R", "N", "B", "Q", "K", "B", "N", "R"};
    for (int col = 0; col < 8; col++)
    {
        boardState[6][col] = "wP";
        boardState[1][col] = "bP";
        boardState[7][col] = "w" + backRank[col];
        boardState[0][col] = "b" + backRank[col];
    }

    isWhiteTurn = true;
    turnLabel->setStyleSheet("background-color: white; border: 1px solid black;");

    selectedRow = -1;
    selectedCol = -1;
    selectedDataRow = -1;
    selectedDataCol = -1;

    updateBoardIcons();
}

void ChessWindow::makeComputerMove()
{
    QList<ChessMove> legalMoves = getAllLegalMoves(boardState, false);   // false = black's moves

    if (legalMoves.isEmpty())
        return;   // no legal moves — checkmate/stalemate handling elsewhere will catch this

    int randomIndex = QRandomGenerator::global()->bounded(legalMoves.size());
    ChessMove chosenMove = legalMoves[randomIndex];

    boardState[chosenMove.toRow][chosenMove.toCol] = boardState[chosenMove.fromRow][chosenMove.fromCol];
    boardState[chosenMove.fromRow][chosenMove.fromCol] = "";

    isWhiteTurn = true;   // back to white's turn after computer moves
    turnLabel->setStyleSheet("background-color: white; border: 1px solid black;");

    updateBoardIcons();

    // Check/checkmate detection after computer's move, same pattern as after human moves
    if (checkHighlightRow != -1)
    {
        board[checkHighlightRow][checkHighlightCol]->setStyleSheet(
            "background-color: " + normalColor(checkHighlightRow, checkHighlightCol) + ";"
            );
        checkHighlightRow = -1;
        checkHighlightCol = -1;
    }

    int kingDataRow, kingDataCol;
    findKing(boardState, true, kingDataRow, kingDataCol);   // check white's king now
    bool inCheck = isSquareUnderAttack(boardState, kingDataRow, kingDataCol, false);

    if (inCheck)
    {
        int kingVisualRow = boardFlipped ? 7 - kingDataRow : kingDataRow;
        int kingVisualCol = boardFlipped ? 7 - kingDataCol : kingDataCol;

        board[kingVisualRow][kingVisualCol]->setStyleSheet("background-color: red;");
        checkHighlightRow = kingVisualRow;
        checkHighlightCol = kingVisualCol;

        if (getAllLegalMoves(boardState, true).isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Checkmate");
            msgBox.setText("Black wins by checkmate!");
            msgBox.setStyleSheet("QLabel{font-size: 20px; font-weight: bold;} QPushButton{font-size: 14px;}");
            QPushButton *playAgainButton = msgBox.addButton("Play Again", QMessageBox::AcceptRole);
            msgBox.exec();

            if (msgBox.clickedButton() == playAgainButton)
            {
                resetGame();
            }
        }
    }
}

void ChessWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Save Game?",
        "Do you want to save the current game before closing?",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
        );

    if (reply == QMessageBox::Yes)
    {
        if (reply == QMessageBox::Yes)
        {
            saveGame();
            event->accept();
        }
        event->accept();   // allow the window to close
    }
    else if (reply == QMessageBox::No)
    {
        QFile::remove("savegame.txt");   // clear any old save, so next launch starts fresh
        event->accept();   // close without saving
    }
    else
    {
        event->ignore();   // Cancel — keep the window open
    }
}

void ChessWindow::saveGame()
{
    QFile file("savegame.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;   // couldn't open the file — silently give up for now

    QTextStream out(&file);

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            QString piece = boardState[row][col];
            out << (piece == "" ? "--" : piece) << " ";
        }
        out << "\n";
    }

    out << (isWhiteTurn ? "white" : "black") << "\n";
    out << (vsComputer ? "vsComputer" : "vsPlayer") << "\n";
    out << (boardFlipped ? "flipped" : "normal") << "\n";

    file.close();
}

bool ChessWindow::loadGame()
{
    QFile file("savegame.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;   // no save file exists — nothing to load

    QTextStream in(&file);

    for (int row = 0; row < 8; row++)
    {
        QString line = in.readLine();
        QStringList tokens = line.split(" ", Qt::SkipEmptyParts);

        for (int col = 0; col < 8; col++)
        {
            boardState[row][col] = (tokens[col] == "--") ? "" : tokens[col];
        }
    }

    QString turnLine = in.readLine();
    isWhiteTurn = (turnLine == "white");

    QString modeLine = in.readLine();
    vsComputer = (modeLine == "vsComputer");

    QString flipLine = in.readLine();
    boardFlipped = (flipLine == "flipped");

    file.close();
    return true;
}
ChessWindow::~ChessWindow() = default;
