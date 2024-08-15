#include "../../Tetris/src/config.h"

#include "artificialintelligence.h"
#include "outcome.h"
#include "gamestate.h"
#include "heuristicvalue.h"
#include "../../Tetris/src/shape.h"
#include "../../Tetris/src/block.h"

#include <QDebug>
#include <QList>

ArtificialIntelligence::ArtificialIntelligence(Scene *scene_, QObject *parent)
    : QObject{parent}
{
    scene = scene_;
}

Outcome ArtificialIntelligence::findBestOutcome(GameState &state)
{
    Shape *fallingShape = state.getShape(GameState::ShapeCategory::FALLING);
    if (!fallingShape)
    {
        return Outcome();
    }
    Shape *simulatedShape = new Shape(fallingShape->getShapeType());

    int maxScore = 0;
    int bestPosition = 0;
    int bestRotation = 0;

    simulatedShape->rotateBackwards();
    for (int rotation = 0; rotation < 4; rotation++)
    {
        simulatedShape->rotate();

        // Move to the left corner for testing each position
        for (int maxMovement = 0; maxMovement < 10; maxMovement++)
        {
            if (!scene->isCollision(Scene::CollisionDirection::LEFT, simulatedShape, state.getBlocks()))
            {
                simulatedShape->moveLeft();
            }
        }

        for (int column = 0; column < 10; column++)
        {
            int dropHeight = 0;
            while (!scene->isCollision(Scene::CollisionDirection::DOWN, simulatedShape, state.getBlocks()))
            {
                simulatedShape->moveDown();
                dropHeight++;
            }

            // Append fallen blocks
            QList<Block *> blocks = state.getBlocks();
            for (Block *block : simulatedShape->getBlocks())
            {
                blocks.append(block);
            }
            GameState newState(blocks, nullptr, state.getShape(GameState::ShapeCategory::NEXT), state.getShape(GameState::ShapeCategory::HOLDING));

            // Evaluate this position and rotation
            HeuristicValue score = evaluatePosition(dropHeight, newState);

            if (score > maxScore)
            {
                maxScore = score;
                bestPosition = simulatedShape->scenePos().x() / CELL_SIZE;
                bestRotation = rotation;
            }

            // Move to next position
            if (!scene->isCollision(Scene::CollisionDirection::RIGHT, simulatedShape, state.getBlocks()))
            {
                simulatedShape->moveRight();
            }
        }
    }

    Outcome bestMove = printOutcomeFromPosition(bestPosition, bestRotation);
    qDebug() << bestMove << " " << maxScore; //! DEBUG
    return bestMove;
}

void ArtificialIntelligence::movePiece(Outcome &bestOutcome, Shape *shape)
{
    Outcome part = bestOutcome.left(2);
    while (!part.isEmpty())
    {
        bestOutcome.remove(0, 2);

        if (part == "Rl")
        {
            shape->rotate();
        }
        else if (part == "Rr")
        {
            shape->rotateBackwards();
        }
        else if (part == "Ml")
        {
            shape->moveLeft();
        }
        else if (part == "Mr")
        {
            shape->moveRight();
        }

        part = bestOutcome.left(2);
    }
}

HeuristicValue ArtificialIntelligence::evaluatePosition(const int dropHeight, GameState &state)
{
    //TODO add GameState checking for better results
    //TODO issue with calculating gaps

    HeuristicValue score = 0;

    // 1. Score based on drop height
    score += dropHeight;

    // 2. Score based on lines cleared
    HeuristicValue linesCleared = scene->checkFullRows(state.getBlocks()) * 100;
    score += linesCleared;

    // 3. Score based on gaps created
    int gapsCreated = state.countGapsCreated();
    HeuristicValue gapsScore = 100 - gapsCreated * 10;
    score += gapsScore;

    return score;
}

Outcome ArtificialIntelligence::printOutcomeFromPosition(int bestPosition, int bestRotation)
{
    Outcome bestMove = "";
    while (bestRotation > 0)
    {
        bestMove.append("Rl"); 
        bestRotation--;
    }
    if (bestPosition > 0)
    {
        while (bestPosition > 0)
        {
            bestMove.append("Ml");
            bestPosition--;
        }
    }
    else
    {
        while (bestPosition < 0)
        {
            bestMove.append("Mr");
            bestPosition++;
        }
    }

    return bestMove;
}
