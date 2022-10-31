#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
int lisaNumerical(vector<vector<int>> &network) {}

vector<int> lisa(vector<vector<int>> &network, int person,
                 unordered_map<int, vector<int>> &memo) {
    if (memo.count(person) != 0) {
        return memo[person];
    }
    vector<int> lisaChildren = {};
    vector<int> lisaGrandchildren = {person};
    for (int child : network[person]) {
        for (int lisaChild : lisa(network, child, memo)) {
            lisaChildren.push_back(lisaChild);
        }
        for (int grandchild : network[child]) {
            lisaGrandchildren.push_back(grandchild);
        }
    }
    if (lisaChildren.size() > lisaGrandchildren.size()) {
        memo[person] = lisaChildren;
    } else {
        memo[person] = lisaGrandchildren;
    }
    return memo[person];
}

// Largest party
vector<int> lisa(vector<vector<int>> &network) {
    unordered_map<int, vector<int>> memo = {};
    vector<int> ans = lisa(network, 0, memo);
    unordered_set<int> ansSet(ans.begin(), ans.end());
    ans.assign(ansSet.begin(), ansSet.end());
    return ans;
}

int main() {
    vector<vector<int>> network = {
        {1, 2, 3, 4, 9}, {5, 6}, {6, 7}, {7, 8}, {}, {}, {}, {}, {}, {}};
    for (int person : lisa(network)) {
        cout << person << " ";
    }
    cout << "\n";
    return 0;
}

/*
 * Analysis:
 *
 * Where V is the number of persons and E is the number of known connections.
 * Time complexity - O(V)
 * Space complexity - O(E)
 *
 * Here, we only need to check each node for it's LIS once, and subsequent LIS
 * calculations for that node is memoized. Therefore our time complexity is O(V)
 * which is the number of persons in our input.
 */