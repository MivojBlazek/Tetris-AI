#include "../../Tetris/src/config.h"

#include "artificialintelligence.h"
#include "outcome.h"
#include "gamestate.h"
#include "heuristicvalue.h"
#include "../../Tetris/src/shape.h"
#include "../../Tetris/src/block.h"

#include <QDebug>
#include <QList>

ArtificialIntelligence::ArtificialIntelligence(Scene *_scene, QObject *parent)
    : QObject{parent}
{
    scene = _scene;
}

Outcome ArtificialIntelligence::findBestOutcome(GameState &state)
{
    Shape *fallingShape = state.getShape(GameState::ShapeCategory::FALLING);
    if (!fallingShape)
    {
        return Outcome();
    }
    Shape *simulatedShape = new Shape(fallingShape->getShapeType());

    int maxScore = -10000;
    int bestPosition = 0;
    int bestRotation = 0;

    for (int rotation = 0; rotation < 4; rotation++)
    {
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
            while (!scene->isCollision(Scene::CollisionDirection::DOWN, simulatedShape, state.getBlocks()))
            {
                simulatedShape->moveDown();
            }

            // Append fallen blocks
            QList<Block *> blocks = state.getBlocks();
            for (Block *block : simulatedShape->getBlocks())
            {
                blocks.append(block);
            }
            GameState newState(blocks, nullptr, state.getShape(GameState::ShapeCategory::NEXT), state.getShape(GameState::ShapeCategory::HOLDING));

            // Evaluate this position and rotation
            HeuristicValue score = evaluatePosition(simulatedShape->getBlocks(), newState);

            if (score > maxScore)
            {
                maxScore = score;
                bestPosition = simulatedShape->scenePos().x() / CELL_SIZE;
                bestRotation = rotation;
            }

            // Move to next position
            simulatedShape->setPos(simulatedShape->scenePos().x(), 0.0);
            if (!scene->isCollision(Scene::CollisionDirection::RIGHT, simulatedShape, state.getBlocks()))
            {
                simulatedShape->moveRight();
            }
        }

        // Square has only 1 rotation
        if (simulatedShape->getShapeType() == Shape::ShapeType::O)
        {
            break;
        }

        // Another rotation
        simulatedShape->setPos(0.0, CELL_SIZE);
        simulatedShape->rotate();
    }

    Outcome bestMove = printOutcomeFromPosition(bestPosition, bestRotation);
    return bestMove;
}

void ArtificialIntelligence::movePiece(Outcome &bestOutcome, Shape *shape, Shape *previewToUpdate)
{
    Outcome part = bestOutcome.left(2);
    while (!part.isEmpty())
    {
        bestOutcome.remove(0, 2);

        if (part == "Rl")
        {
            shape->rotate();
            if (previewToUpdate && previewToUpdate != nullptr)
            {
                previewToUpdate->rotate();
            }
        }
        else if (part == "Rr")
        {
            shape->rotateBackwards();
            if (previewToUpdate && previewToUpdate != nullptr)
            {
                previewToUpdate->rotateBackwards();
            }
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

HeuristicValue ArtificialIntelligence::evaluatePosition(const QList<Block *> blocks, GameState &state)
{
    //TODO add next and hold state checking for better results

    HeuristicValue score = 100;

    // 1. Score based on drop height
    double highestBlock = blocks[0]->scenePos().y();
    for (Block *block : blocks)
    {
        if (block->scenePos().y() < highestBlock)
        {
            highestBlock = block->scenePos().y();
        }
    }
    score += static_cast<HeuristicValue>(highestBlock / CELL_SIZE);

    // 2. Score based on lines cleared
    HeuristicValue linesCleared = countFullRows(state.getBlocks()) * 50;
    score += linesCleared;

    // 3. Score based on gaps created
    int gapsCreated = state.countGapsCreated();
    HeuristicValue gapsScore = -gapsCreated * 10;
    score += gapsScore;

    // 4. Score based on bumpiness
    HeuristicValue bumpiness = state.evaluateBumpiness();
    score += bumpiness;

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
            bestMove.append("Mr");
            bestPosition--;
        }
    }
    else
    {
        while (bestPosition < 0)
        {
            bestMove.append("Ml");
            bestPosition++;
        }
    }

    return bestMove;
}

int ArtificialIntelligence::countFullRows(QList<Block *> allBlocks)
{
    int numberOfFullRows = 0;

    int blocksInRow;
    for (auto row : scene->getRows())
    {
        blocksInRow = 0;

        for (Block *block : allBlocks)
        {
            if (row->collidesWithItem(block))
            {
                // If block collides with selected row
                blocksInRow++;
            }
        }
        // After 10 collisions (10 blocks in a row)
        if (blocksInRow == 10)
        {
            // Row should be cleared
            numberOfFullRows++;
        }
    }
    return numberOfFullRows;
}
