#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../../Tetris/src/block.h"
#include "../../Tetris/src/shape.h"

#include <QList>


class GameState : public QObject
{
    Q_OBJECT
public:
    explicit GameState(QList<Block *> _blocks, Shape *_fallingShape, Shape *_nextShape, Shape *_holdShape, bool _holdDoneThisRound, QObject *parent = nullptr);

    enum ShapeCategory { FALLING, NEXT, HOLDING };

    QList<Block *> getBlocks();
    Shape *getShape(ShapeCategory type = FALLING);
    int countGapsCreated();
    int evaluateBumpiness();
    bool getHold();

private:
    QList<Block *> blocks;
    Shape *fallingShape;
    Shape *nextShape;
    Shape *holdingShape;
    bool holdDoneThisRound;
};

#endif // GAMESTATE_H