#include <SDL.h>

#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char* args[]) {
	cout << " _   _  ____  _  _  _  _  ____  ____ " << endl
		<< "( )_( )( ___)( \\/ )( \\/ )( ___)(  _ \\" << endl
		<< " ) _ (  )__)  )  (  )  (  )__)  )   /" << endl
		<< "(_) (_)(____)(_/\\_)(_/\\_)(____)(_)\\_)" << endl;
	char selection = 0;
	while (selection != 'p' && selection != 'r' && selection != 'h' && selection != 'f' && selection != 'x') {
		cout << "(p)  Play" << endl
			<< "(r)  Rules" << endl
			<< "(h)  Highscores" << endl
			<< "(f)  Find your rank" << endl
			<< "(x)  Exit" << endl;
		cin >> selection;
		if (selection == 'p') {
			Game game;
			selection = 0;
		}
		if (selection == 'r') {
			cout << "HEXXER is a game that requires three people to play." << endl
				<< "Each player is in control of a colour(magenta, green, or cyan)." << endl
				<< "When a player claims an empty hexagon, they are awarded 10 points." << endl
				<< "When a player manages to claim three adjacent hexagons, they are merged together to become a" << endl
				<< "HEXXERgon, and the player is awarded 50 points." << endl
				<< "The objective of the game is to win as many points as possible" << endl
				<< "before the HEXXER board is completely claimed." << endl;
			selection = 0;
		}
		if (selection == 'h') {
			cout << endl << "~HIGHSCORES~" << endl;
			ifstream inScore;
			inScore.open("resources/highscore.txt");

			if (inScore.fail()) {
				cerr << "error opening file" << endl;
				exit(1);
			}

			string tempNames = "BOB";
			int tempPoints = 0;

			for(int i = 0 ; i < 20; i++){
				if (i % 2 == 0) {
					inScore >> tempNames;
				}
				else if (i % 2 == 1) {
					inScore >> tempPoints;
					cout << i / 2 + 1 << "\t" << tempPoints << "\t" << tempNames << endl;
				}
			}
			cout << endl;
			selection = 0;
		}
		if (selection == 'f') {
			string rankingName = "BOB";
			bool found = false;
			while (!found) {
				cout << "Please enter your name: ";
				cin >> rankingName;

				ifstream inScore;
				inScore.open("resources/highscore.txt");

				if (inScore.fail()) {
					cerr << "error opening file" << endl;
					exit(1);
				}

				string tempNames;
				int count = 0;

				while (!inScore.eof()) {
					if (count % 2 == 0) {
						inScore >> tempNames;
						if (rankingName == tempNames) {
							cout << rankingName << " rank:\t" << count / 4 + 1;
							found = true;
						}
					}
					count++;
				}
			}
			cout << endl;
			selection = 0;
		}
	}
	
	
	
	return 0;
}