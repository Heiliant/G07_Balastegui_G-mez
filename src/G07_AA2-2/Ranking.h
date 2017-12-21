#pragma once
#include "Scene.h"
#include <map>
#include <string>
#include <algorithm>
#include <deque>

class Ranking : public Scene
{
public:
	Ranking();
	~Ranking();


private:
	std::map <std::string, int> hallOfFame;
	void eventHandler() override;
	void update() override;
	void draw() override;

	Button* Back;

	Image BG;


	std::deque<Score> beastList;
	void displayScores();

};

