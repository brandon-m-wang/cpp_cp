#include <iostream>
#include <string>
#include <vector>

/*
 * Problem statement:
 *
 * Given a guaranteed acyclic graph representation of a network of people,
 * create the largest possible party such that nobody in the party knows one
 * another. It is guaranteed that each person in the network is either known by
 * or knows at least one person, otherwise it is trivial to include them in the
 * party (i.e. the network is connected). Further, person 0 will always know
 * people, but nobody knows him.
 *
 * Inputs:
 *
 * vector<vector<int>> network -> where network[i] represents the list of
 * persons that person i knows.
 *
 * Output:
 *
 * vector<int> -> the largest possible party
 */

using namespace std;

// Numerical size value of the largest party only
int lisa(vector<vector<int>> &network) {}

vector<int> lisa(vector<vector<int>> &network, int person, vector<int> &memo) {}

// Largest party
vector<int> lisa(vector<vector<int>> &network) {}

int main() { return 0; }