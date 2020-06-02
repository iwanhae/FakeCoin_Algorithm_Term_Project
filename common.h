#include<iostream>
#include<vector>
#include "balance.h"

using namespace std;

struct knownSet {
    vector<int> real, fake, unknown;
};

extern int printFlag;

knownSet find(vector<int> unknowns);
knownSet findInitialSet(vector<int> unknown);
knownSet guaranteedFind(knownSet result, int realCoin);
/*
동전개수, 최악의 비교횟수
2          1
3          2
4          3
5          4
6          5
7          5
8          6
9          6
10         7
11         7
*/
int balanceWithVector(vector<int> va, vector<int> vb);
knownSet CompareBy3(vector<int> real, vector<int> fake, vector<int> unknown);
knownSet CompareBy3_rvs(vector<int> real, vector<int> fake, vector<int> unknown);
knownSet compareBy5(vector<int> real, vector<int> fake, vector<int> unknown);
knownSet compareBy5_rvs(vector<int> real, vector<int> fake, vector<int> unknown);
int gambling(knownSet result);