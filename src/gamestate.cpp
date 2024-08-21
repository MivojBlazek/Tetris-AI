#include "gamestate.h"
#include "../../Tetris/src/block.h"
#include "../../Tetris/src/shape.h"

#include <QDebug>
#include <QList>
#include <QPointF>
#include <QSet>
#include <QPair>
#include <QVector>

// Custom hash function for QPointF
inline uint qHash(const QPointF &point, uint seed = 0)
{
    return qHash(QPair<qreal, qreal>(point.x(), point.y()), seed);
}


GameState::GameState(QList<Block *> _blocks, Shape *_fallingShape, Shape *_nextShape, Shape *_holdShape, bool _holdDoneThisRound, QObject *parent)
    : QObject{parent}
{
    blocks = _blocks;
    fallingShape = _fallingShape;
    nextShape = _nextShape;
    holdingShape = _holdShape;
    holdDoneThisRound = _holdDoneThisRound;
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
        // Iterate from top to bottom of the column
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

int GameState::evaluateBumpiness()
{
    QSet<QPointF> blockSet;
    for (Block *block : blocks)
    {
        blockSet.insert((block->scenePos() + QPointF(5 * CELL_SIZE, 0)) / CELL_SIZE);
    }

    int bumpinessScore = 0;
    QVector<int> bumpinessOnColumns(10, 20);

    // Iterate over each column
    for (int x = 0; x < 10; x++)
    {
        // Iterate from top to bottom
        for (int y = 0; y < 20; y++)
        {
            QPointF currentPos(x, y);
            if (blockSet.contains(currentPos))
            {
                bumpinessOnColumns[x] = y;
                break;
            }
        }
    }

    for (int i = 0; i < bumpinessOnColumns.size() - 1; i++)
    {
        bumpinessScore += std::abs(bumpinessOnColumns[i] - bumpinessOnColumns[i + 1]);
    }

    return -bumpinessScore;
}

bool GameState::getHold()
{
    return holdDoneThisRound;
}
