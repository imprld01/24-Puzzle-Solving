#include<queue>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

#define PUZZLEEDGE		5
#define PUZZLESIZE		25
#define	ACTION_UP		'u'
#define	ACTION_DOWN		'd'
#define	ACTION_LEFT		'l'
#define	ACTION_RIGHT	'r'
#define	BLANK_BLOCK		'0'
#define	QUIT_SIGNAL		"QUIT"

struct stateNode {
	string stateRps, actionSeq;
	int cost_g, cost_h, cost_f;
};

struct cmpsb {
	bool operator()(stateNode stateA, stateNode stateB) {
		int costA = stateA.cost_f;
		int costB = stateB.cost_f;
		return costA > costB;
	}
};

stateNode initialStateInput();
bool CorrectSizeCheck(string);
bool SolvabilityDecision(string);
int ManhattanDistance(string);
vector<stateNode> SuccessorFunction(stateNode);
bool isFinalState(stateNode);
void printActionSequence(string, string);

/* do not record the searched node! */
int main() {

	while (true) {
		priority_queue<stateNode, vector<stateNode>, cmpsb> pq;

		stateNode initialSN = initialStateInput();
		if (!initialSN.stateRps.compare(QUIT_SIGNAL)) {
			cout << "Quit" << endl;
			break;
		}
		if (!SolvabilityDecision(initialSN.stateRps)) {
			cout << "No solution for " << initialSN.stateRps << "!!" << endl;
			continue;
		}

		pq.push(initialSN);
		while (!pq.empty()) {
			stateNode currentNode = pq.top(); pq.pop();

			if (isFinalState(currentNode)) {
				printActionSequence(initialSN.stateRps, currentNode.actionSeq);
				break;
			}

			vector<stateNode> successor = SuccessorFunction(currentNode);
			for (vector<stateNode>::iterator itr = successor.begin(); itr != successor.end(); ++itr) pq.push(*itr);
		}
	}

	return 0;
}

stateNode initialStateInput() {

	stateNode sn;
	bool correct;

	do {
		correct = true;

		cin >> sn.stateRps;

		if (sn.stateRps.compare(QUIT_SIGNAL) && !CorrectSizeCheck(sn.stateRps)) {
			cout << "Input Error: You have the wrong puzzle size!" << endl;
			correct = false;
		}
	} while (!correct);

	sn.actionSeq = "";
	sn.cost_g = 0;
	sn.cost_h = sn.stateRps.compare(QUIT_SIGNAL) ? ManhattanDistance(sn.stateRps) : 0;
	sn.cost_f = sn.cost_g + sn.cost_h;

	return sn;
}

bool CorrectSizeCheck(string state) {
	
	if (state.size() == PUZZLESIZE) return true;
	else return false;
}

bool SolvabilityDecision(string state) {

	if (!CorrectSizeCheck(state)) {
		cout << "SolvabilityDecision Error: You have the wrong puzzle size!" << endl;
		return false;
	}
	bool tileCheck[PUZZLESIZE] = { false };
	for (string::iterator itr = state.begin(); itr != state.end(); ++itr) {
		if (*itr == '0') tileCheck[0] = !tileCheck[0];
		else if(*itr >= 'A' && *itr <= 'X') tileCheck[*itr - 'A' + 1] = !tileCheck[*itr - 'A' + 1];
		else {
			cout << "SolvabilityDecision Error: Wrong puzzle tile, '" << *itr << "'!" << endl;
			return false;
		}
	}
	for (int index = 0; index < PUZZLESIZE; ++index) {
		if (!tileCheck[index]) {
			cout << "SolvabilityDecision Error: You have repeat puzzle tiles!" << endl;
			return false;
		}
	}

	int disorderCounting = 0;

	for (string::iterator itr_i = state.begin(); itr_i != state.end(); ++itr_i) {
		if (*itr_i == BLANK_BLOCK) continue;
		for (string::iterator itr_j = itr_i + 1; itr_j != state.end(); ++itr_j) {
			if (*itr_j == BLANK_BLOCK) continue;
			if (*itr_i > *itr_j) ++disorderCounting;
		}
	}

	return (disorderCounting & 1) ? false : true;
}

int ManhattanDistance(string state) {

	if (!CorrectSizeCheck(state)) {
		cout << "ManhattanDistance Error: You have the wrong puzzle size!" << endl;
		return false;
	}

	int resultCost = 0;

	for (char currentGoal = 'A'; currentGoal <= 'X'; ++currentGoal) {
		int crntPos = state.find(currentGoal);
		int GoalPos = currentGoal - 64;
		resultCost += abs(crntPos / PUZZLEEDGE - GoalPos / PUZZLEEDGE) + abs(crntPos % PUZZLEEDGE - GoalPos % PUZZLEEDGE);
	}

	return resultCost;
}

vector<stateNode> SuccessorFunction(stateNode inputSN) {

	vector<stateNode> result;
	int blankIndex = inputSN.stateRps.find(BLANK_BLOCK);
	bool up_ = true, down_ = true, right_ = true, left_ = true;

	if (!CorrectSizeCheck(inputSN.stateRps)) {
		cout << "SuccessorFunction Error: You have the wrong puzzle size! " << inputSN.stateRps.size() << endl;
		return result;
	}

	switch (blankIndex) {
	case 0: up_ = left_ = false; break;
	case 1: up_ = false; break;
	case 2: up_ = false; break;
	case 3: up_ = false; break;
	case 4: up_ = right_ = false; break;
	case 5: left_ = false; break;
	case 9: right_ = false; break;
	case 10: left_ = false; break;
	case 14: right_ = false; break;
	case 15: left_ = false; break;
	case 19: right_ = false; break;
	case 20: down_ = left_ = false; break;
	case 21: down_ = false; break;
	case 22: down_ = false; break;
	case 23: down_ = false; break;
	case 24: down_ = right_ = false; break;
	}

	if (up_) {
		stateNode outSN;
		outSN.stateRps = inputSN.stateRps;
		int nextPosition = blankIndex - PUZZLEEDGE;
		swap(outSN.stateRps[blankIndex], outSN.stateRps[nextPosition]);
		outSN.actionSeq = inputSN.actionSeq + ACTION_UP;
		outSN.cost_g = inputSN.cost_g + 1;
		outSN.cost_h = ManhattanDistance(outSN.stateRps);
		outSN.cost_f = outSN.cost_h + outSN.cost_g;
		result.push_back(outSN);
	}
	if (down_) {
		stateNode outSN;
		outSN.stateRps = inputSN.stateRps;
		int nextPosition = blankIndex + PUZZLEEDGE;
		swap(outSN.stateRps[blankIndex], outSN.stateRps[nextPosition]);
		outSN.actionSeq = inputSN.actionSeq + ACTION_DOWN;
		outSN.cost_g = inputSN.cost_g + 1;
		outSN.cost_h = ManhattanDistance(outSN.stateRps);
		outSN.cost_f = outSN.cost_h + outSN.cost_g;
		result.push_back(outSN);
	}
	if (left_) {
		stateNode outSN;
		outSN.stateRps = inputSN.stateRps;
		int nextPosition = blankIndex - 1;
		swap(outSN.stateRps[blankIndex], outSN.stateRps[nextPosition]);
		outSN.actionSeq = inputSN.actionSeq + ACTION_LEFT;
		outSN.cost_g = inputSN.cost_g + 1;
		outSN.cost_h = ManhattanDistance(outSN.stateRps);
		outSN.cost_f = outSN.cost_h + outSN.cost_g;
		result.push_back(outSN);
	}
	if (right_) {
		stateNode outSN;
		outSN.stateRps = inputSN.stateRps;
		int nextPosition = blankIndex + 1;
		swap(outSN.stateRps[blankIndex], outSN.stateRps[nextPosition]);
		outSN.actionSeq = inputSN.actionSeq + ACTION_RIGHT;
		outSN.cost_g = inputSN.cost_g + 1;
		outSN.cost_h = ManhattanDistance(outSN.stateRps);
		outSN.cost_f = outSN.cost_h + outSN.cost_g;
		result.push_back(outSN);
	}

	return result;
}

bool isFinalState(stateNode inputSN) {

	return (inputSN.cost_h == 0) ? true : false;
}

void printActionSequence(string initialState, string actSeq) {

	if (actSeq.empty()) cout << initialState << " is already a goal state." << endl;
	else {
		cout << "Solution for " << initialState << " is:" << endl;
		for (string::iterator itr = actSeq.begin(); itr != actSeq.end(); ++itr) {
			switch (*itr) {
			case 'u': cout << "move 0 to up" << endl; break;
			case 'd': cout << "move 0 to down" << endl; break;
			case 'l': cout << "move 0 to left" << endl; break;
			case 'r': cout << "move 0 to right" << endl; break;
			}
		}
	}
}