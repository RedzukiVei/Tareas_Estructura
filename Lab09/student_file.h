#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

class UnionFind {
private:
    map<string, string> parent;
    map<string, int> rank;

public:
    void initialize(const string& s) {
        parent[s] = s;
        rank[s] = 0;
    }

    string findSet(const string& s) {
        if (parent[s] != s)
            parent[s] = findSet(parent[s]);
        return parent[s];
    }

    bool mergeSets(const string& a, const string& b) {
        string rootA = findSet(a);
        string rootB = findSet(b);

        if (rootA == rootB)
            return false;

        if (rank[rootA] < rank[rootB])
            parent[rootA] = rootB;
        else if (rank[rootA] > rank[rootB])
            parent[rootB] = rootA;
        else {
            parent[rootB] = rootA;
            rank[rootA]++;
        }

        return true;
    }
};

class Road {
public:
    string id;
    string city1;
    string city2;
    int cost;

    Road(string i, string c1, string c2, int co = 0) : id(i), city1(c1), city2(c2), cost(co) {}
};

string reconstructRoads(vector<string> roadStrings) {
    vector<Road> damagedRoads;
    UnionFind unionFind;
    set<string> cities;
    set<string> selectedRoads;

    for (const auto& roadStr : roadStrings) {
        stringstream ss(roadStr);
        string id, city1, city2;
        ss >> id >> city1 >> city2;
        unionFind.initialize(city1);
        unionFind.initialize(city2);
        cities.insert(city1);
        cities.insert(city2);
    }

    for (const auto& roadStr : roadStrings) {
        stringstream ss(roadStr);
        string id, city1, city2;
        int cost = 0;
        ss >> id >> city1 >> city2;
        if (!(ss >> cost)) {
            unionFind.mergeSets(city1, city2);
        } else {
            damagedRoads.emplace_back(id, city1, city2, cost);
        }
    }

    sort(damagedRoads.begin(), damagedRoads.end(), [](const Road& a, const Road& b) {
        return (a.cost != b.cost) ? (a.cost < b.cost) : (a.id < b.id);
    });

    for (const auto& road : damagedRoads) {
        if (unionFind.findSet(road.city1) != unionFind.findSet(road.city2)) {
            unionFind.mergeSets(road.city1, road.city2);
            selectedRoads.insert(road.id);
        }
    }

    string root = unionFind.findSet(*cities.begin());
    for (const auto& city : cities) {
        if (unionFind.findSet(city) != root) {
            return "IMPOSSIBLE";
        }
    }

    string result;
    for (const auto& id : selectedRoads) {
        result += id + " ";
    }

    return result.empty() ? "" : result.substr(0, result.length() - 1);
}