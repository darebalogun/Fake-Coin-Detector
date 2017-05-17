#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

//Define input structure
typedef struct input {
	string left;
	string right;
	bool isLeftHeavier;
	bool isRightHeavier;
} input_t;

int main()
{
	//Ask user for number of measurements
	string Measurements;
	cout << "How many measurements did you do? ";
	getline(cin,Measurements);

	//Abort with error if number is not an int
	int numMeasurements;
	try {
	numMeasurements = stoi(Measurements);
	} 
	catch (...) {
		cout << "That is not a valid number of measurements! " << endl;
	}

	//Build vector of structs to hold all measurement data
	vector<input_t> inputVector(numMeasurements);

	//Ask user for results of all measurements
	for (int i = 1; i <= numMeasurements; i++) {
		cout << "Type in the coins on the left scale (no spaces): ";
		getline(cin, inputVector[i - 1].left);

		//Sort input
		sort(begin(inputVector[i - 1].left), end(inputVector[i - 1].left));

		cout << "Type in the coins on the right scale (no spaces): ";
		getline(cin, inputVector[i - 1].right);
		sort(begin(inputVector[i - 1].right), end(inputVector[i - 1].right));

		string leftOrRight;
		cout << "Which side is heavier? ";
		getline(cin, leftOrRight);

		//Keep asking till user inputs either left, right or equal
		while (leftOrRight.compare("left") != 0 && leftOrRight.compare("right") != 0 && leftOrRight.compare("equal") != 0) {
			cout << "Please enter left or right or equal: ";
			getline(cin, leftOrRight);
		}

		//If left is heaver isLeftHeavier = true isRightHeavier = false and so on
		if (leftOrRight.compare("left") == 0) {
			inputVector[i - 1].isLeftHeavier = true;
			inputVector[i - 1].isRightHeavier = false;
		}
		else if (leftOrRight.compare("right") == 0) {
			inputVector[i - 1].isLeftHeavier = false;
			inputVector[i - 1].isRightHeavier = true;
		} 
		else if (leftOrRight.compare("equal") == 0) {
			inputVector[i - 1].isLeftHeavier = false;
			inputVector[i - 1].isRightHeavier = false;
		}
	}

	//vector storing strings containing fake coins (takes all coins from lighter pile)
	vector <string> fakeCoin;

	//Put lighter coins as a string into fakeCoin vector
	for (int i = 0; i < numMeasurements; i++) {
		if (inputVector[i].isLeftHeavier == true) {
			fakeCoin.push_back(inputVector[i].right);
		}
		else if (inputVector[i].isRightHeavier == true) {
			fakeCoin.push_back(inputVector[i].left);
		}
	}

	if (fakeCoin.empty()) {
		cout << "No fake Coins" << endl;
	}
	else {

	//Create string that should contain all fake coins (looking for repeat offenders)
	if (fakeCoin.size() > 1) {
		for (unsigned int i = 1; i < fakeCoin.size(); i++) {
			string fakeCoinString;
			set_intersection(fakeCoin[0].begin(), fakeCoin[0].end(), fakeCoin[i].begin(), fakeCoin[i].end(), back_inserter(fakeCoinString));
			cout << fakeCoin[0] << endl;
			if (!fakeCoinString.empty()) {
				fakeCoin[0] = fakeCoinString;
			}
		}
	}

	//Create vector of strings that should contain all real coins (all coins on heavy side or equal)
	vector <string> notFakeCoin;

	for (int i = 0; i < numMeasurements; i++) {
		if (inputVector[i].isLeftHeavier == true) {
			notFakeCoin.push_back(inputVector[i].left);
		}
		else if (inputVector[i].isRightHeavier == true) {
			notFakeCoin.push_back(inputVector[i].right);
		}
		else if (inputVector[i].isRightHeavier == false && inputVector[i].isLeftHeavier == false) {
			notFakeCoin.push_back(inputVector[i].left);
			notFakeCoin.push_back(inputVector[i].right);
		}
	}

	//Remove duplicates and store values in first spot in vector
	for (unsigned int i = 1; i < notFakeCoin.size(); i++) {
		string notFakeCoinString;
		set_union(notFakeCoin[0].begin(), notFakeCoin[0].end(), notFakeCoin[i].begin(), notFakeCoin[i].end(), back_inserter(notFakeCoinString));
			notFakeCoin[0] = notFakeCoinString;
	}

	//Remove all coins in fake string that were also in real string
	string finalString;
	set_difference(fakeCoin[0].begin(), fakeCoin[0].end(), notFakeCoin[0].begin(), notFakeCoin[0].end(), back_inserter(finalString));
	fakeCoin[0] = finalString;
	
	//Print results
	if (fakeCoin[0].length() == 1) {
		cout << "Fake coin is " << fakeCoin[0] << endl;
	}
	else if (fakeCoin[0].empty()) {
		cout << "Data is inconsistent" << endl;
	}
	else {
		cout << "Result is indeterminate" << endl;
	}
}

    return 0;
}

