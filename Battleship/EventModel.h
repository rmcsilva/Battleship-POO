#pragma once
class EventModel
{
	const int DEFAULT_PROB_EASY = 20;
	const int DEFAULT_STORM_PROB = 30;
	const int DEFAULT_MERMAID_PROB = 30;
	const int DEFAULT_CALM_PROB = 20;
	const int DEFAULT_RIOT_PROB = 20;
	int probability, stormProb, mermaidProb, calmProb, riotProb;
public:
	EventModel();

	int getProbability() const;
	int getStormProbability() const;
	int getMermaidProbability() const;
	int getCalmProbability() const;
	int getRiotProbability() const;

	void setProbability(int prob);
	void setStormProbability(int prob);
	void setMermaidProbability(int prob);
	void setCalmProbability(int prob);
	void setRiotProbability(int prob);
};

