#include "artificialintelligence.h"
#include "outcome.h"
#include "gamestate.h"

ArtificialIntelligence::ArtificialIntelligence(QObject *parent)
    : QObject{parent}
{

}

Outcome ArtificialIntelligence::findBestOutcome(const GameState &state) const
{
    //TODO
    Outcome outcome = "BestOutcome";
    return outcome;
}

void ArtificialIntelligence::movePiece(const Outcome &bestOutcome)
{
    //TODO
}
