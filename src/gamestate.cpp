#include "gamestate.h"
#include "../../Tetris/src/block.h"
#include "../../Tetris/src/shape.h"

#include <QDebug>
#include <QList>
#include <QPointF>
#include <QSet>
#include <QPair>

// Custom hash function for QPointF
inline uint qHash(const QPointF &point, uint seed = 0)
{
    return qHash(QPair<qreal, qreal>(point.x(), point.y()), seed);
}


GameState::GameState(QList<Block *> blocks_, Shape *fallingShape_, Shape *nextShape_, Shape *holdShape_, QObject *parent)
    : QObject{parent}
{
    blocks = blocks_;
    fallingShape = fallingShape_;
    nextShape = nextShape_;
    holdingShape = holdShape_;
}

QList<Block *> GameState::getBlocks()
{
    return blocks;
}

Shape *GameState::getShape(ShapeCategory type)
{
    switch (type)
    {
        case FALLING:
            return fallingShape;
        case NEXT:
            return nextShape;
        case HOLDING:
            return holdingShape;
    }
    return nullptr;
}

int GameState::countGapsCreated()
{
    QSet<QPointF> blockSet;
    for (Block *block : blocks)
    {
        blockSet.insert((block->scenePos() + QPointF(5 * CELL_SIZE, 0)) / CELL_SIZE);
    }

    int gaps = 0;

    // Iterate over each column
    for (int x = 0; x < 10; x++)
    {
        // Iterate from bottom to top of the column
        bool blockFound = false;
        for (int y = 0; y < 20; y++)
        {
            QPointF currentPos(x, y);
            if (blockSet.contains(currentPos))
            {
                blockFound = true;
            }
            else if (blockFound)
            {
                gaps++;
            }
        }
    }

    return gaps;
}
