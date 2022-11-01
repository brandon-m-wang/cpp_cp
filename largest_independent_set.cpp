#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/*
 * Problem statement:
 *
 * Given a graph representation of a network of people, create the largest
 * possible party such that nobody in the party knows one another. It is
 * guaranteed that each person in the network is either known by or knows at
 * least one person, otherwise it is trivial to include them in the party.
 *
 * Inputs:
 *
 * vector<vector<int>> network -> where network[i] represents the list of
 * persons that person i knows.
 *
 * Output:
 *
 * vector<int> -> the largest possible party.
 */

using namespace std;

unordered_set<int> removeNode(vector<unordered_set<int>> &adj, int person) {
    for (int child : adj[person]) {
        adj[child].erase(person);
    }
    unordered_set<int> knowns = adj[person];
    adj[person].clear();
    return knowns;
}

void addNode(vector<unordered_set<int>> &adj, int person,
             unordered_set<int> &knowns) {
    for (int child : knowns) {
        adj[person].insert(child);
        adj[child].insert(person);
    }
}

unordered_set<int> lis(vector<unordered_set<int>> &adj, int person) {
    unordered_set<int> lisChildren = {};            // knowns
    unordered_set<int> lisGrandchildren = {person}; // knowns of knowns and self

    unordered_set<int> personKnowns;
    unordered_map<int, unordered_set<int>> childKnowns;
    unordered_set<int> children;
    unordered_set<int> grandchildren;

    children = adj[person];
    personKnowns = removeNode(adj, person);
    for (int child : children) {
        for (int lissChild : lis(adj, child)) {
            lisChildren.insert(lissChild);
        }
        for (int grandchild : adj[child]) {
            grandchildren.insert(grandchild);
        }
        childKnowns[child] = removeNode(adj, child);
    }
    for (int grandchild : grandchildren) {
        for (int lisGrandchild : lis(adj, grandchild)) {
            lisGrandchildren.insert(lisGrandchild);
        }
    }
    for (int child : children) {
        addNode(adj, child, childKnowns[child]);
    }
    addNode(adj, person, personKnowns);

    if (lisChildren.size() > lisGrandchildren.size()) {
        return lisChildren;
    } else {
        return lisGrandchildren;
    }
}

vector<int> lis(vector<vector<int>> &network) {
    vector<unordered_set<int>> adj(network.size(), unordered_set<int>());
    vector<int> seen(network.size(), 0);
    for (int person = 0; person < network.size(); person++) {
        for (int child : network[person]) {
            adj[person].insert(child);
            adj[child].insert(person);
        }
    }
    // Arbitrarily choose person 0 as starting node (any person is fine).
    vector<int> ans = {};
    unordered_set<int> ansSet = lis(adj, 0);
    ans.insert(ans.end(), ansSet.begin(), ansSet.end());
    return ans;
}

int main() {
    vector<vector<int>> network = {
        {1, 2, 3, 4, 9}, {5, 6}, {6, 7}, {7, 8}, {}, {}, {}, {}, {}, {}};
    for (int person : lis(network)) {
        cout << person << " ";
    }
    cout << "\n";
    return 0;
}

/*
 * Analysis:
 *
 * Where V is the number of persons and E is the number of known connections.
 * Time complexity - O(2^V)
 * Space complexity - O(E)
 */