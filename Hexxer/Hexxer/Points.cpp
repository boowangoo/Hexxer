#include "Points.h"
using namespace std;



Points::Points(std::string nameOne, std::string nameTwo, std::string nameThree){
	mName = nameOne;
	gName = nameTwo;
	cName = nameThree;
	mPoints = 0;
	gPoints = 0;
	cPoints = 0;
}

Points::~Points()
{
}

void Points::ResetPoints() {
	mPoints = 0;
	gPoints = 0;
	cPoints = 0;
}

void Points::AddPoints(char state, char control) {
	if (state == 'c') {
		if (control == 'm') {
			mPoints += 10;
		}
		else if (control == 'g') {
			gPoints += 10;
		}
		else if (control == 'c') {
			cPoints += 10;
		}
	}
	if (state == 'u') {
		if (control == 'm') {
			mPoints += 50;
		}
		else if (control == 'g') {
			gPoints += 50;
		}
		else if (control == 'c') {
			cPoints += 50;
		}
	}
}

int Points::GetPoints(char control) {
	if (control == 'm') {
		return mPoints;
	}
	else if (control == 'g') {
		return gPoints;
	}
	else if (control == 'c') {
		return cPoints;
	}
	else {
		return 0;
	}
}

void Points::CopyInfo(string newMName, string newGName, string newCName, 
						int newMPoints, int newGPoints, int newCPoints) {
	ifstream inScore;
	inScore.open("highscore.txt");
	
	if (inScore.fail()) {
		cerr << "error opening file" << endl;
		exit(1);
	}

	string tempNames;
	int tempPoints;
	int count = 0;

	while (!inScore.eof()) {
		if (count % 2 == 0) {
			inScore >> tempNames;
			highscoreNames.push_back(tempNames);
		}
		else if (count % 2 == 1) {
			inScore >> tempPoints;
			highscorePoints.push_back(tempPoints);
		}
		count++;
	}
	
	highscoreNames.push_back(newMName);
	highscorePoints.push_back(newMPoints);
	highscoreNames.push_back(newGName);
	highscorePoints.push_back(newGPoints);
	highscoreNames.push_back(newCName);
	highscorePoints.push_back(newCPoints);

}

void Points::PasteInfo() {
	int current;
	for (int i = highscorePoints.size() - 2; i >= 0; i--) {
		current = i;
		while (current < highscorePoints.size() - 1 && highscorePoints[current] < highscorePoints[current + 1]) {
			int tempPoints = highscorePoints[current];
			string tempName = highscoreNames[current];

			highscorePoints[current] = highscorePoints[current + 1];
			highscoreNames[current] = highscoreNames[current + 1];

			highscorePoints[current + 1] = tempPoints;
			highscoreNames[current + 1] = tempName;
			current++;
		}
	}

	ofstream outScore;
	outScore.open("resources/highscore.txt");

	if (outScore.fail()) {
		cerr << "error opening file" << endl;
		exit(1);
	}

	for (int i = 0; i < highscoreNames.size(); i++) {
		outScore << highscoreNames[i] << endl;
		if (i < highscorePoints.size() - 1) {
			outScore << highscorePoints[i] << endl;
		}
		else {
			outScore << highscorePoints[i];
		}
	}
}