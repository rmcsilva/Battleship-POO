#include "stdafx.h"
#include "EventModel.h"


EventModel::EventModel(int max_turns) : turnDuration(max_turns)
{
}

bool EventModel::isOver() {return currentTurn == turnDuration;}

void EventModel::incrementTurn() {currentTurn++;}
