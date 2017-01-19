#ifndef POINTS_H
#define POINTS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Points{
private:
	string mName, gName, cName;
	int mPoints = 0;
	int gPoints = 0;
	int cPoints = 0;

	vector <int> highscorePoints;
	vector <string> highscoreNames;
public:
	Points(std::string, std::string, std::string);
	~Points();
	void ResetPoints();
	void AddPoints(char, char);
	int GetPoints(char);
	void CopyInfo(string, string, string, int, int, int);
	void PasteInfo();
};
#endif // !POINTS_H