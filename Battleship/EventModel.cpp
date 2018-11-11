#include "stdafx.h"
#include "EventModel.h"


EventModel::EventModel()
{
	probability = DEFAULT_PROB_EASY;
	stormProb = DEFAULT_STORM_PROB;
	mermaidProb = DEFAULT_MERMAID_PROB;
	calmProb = DEFAULT_CALM_PROB;
	riotProb = DEFAULT_RIOT_PROB;
}

int EventModel::getProbability() const
{
	return probability;
}

int EventModel::getStormProbability() const
{
	return stormProb;
}

int EventModel::getMermaidProbability() const
{
	return mermaidProb;
}

int EventModel::getCalmProbability() const
{
	return calmProb;
}

int EventModel::getRiotProbability() const
{
	return riotProb;
}

void EventModel::setProbability(int prob)
{
	this->probability = prob;
}

void EventModel::setStormProbability(int prob)
{
	this->stormProb = prob;
}

void EventModel::setMermaidProbability(int prob)
{
	this->mermaidProb = prob;
}

void EventModel::setCalmProbability(int prob)
{
	this->calmProb = prob;
}

void EventModel::setRiotProbability(int prob)
{
	this->riotProb= prob;
}



