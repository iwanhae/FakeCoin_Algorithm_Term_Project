#include "common.h"
#include "staticList.h"

int balanceWithVector(vector<int> va, vector<int> vb) {
    int a[100], b[100], i;
    for (i = 0; i < va.size(); i++)
        a[i] = va.at(i);
    a[i] = -1;
    for (i = 0; i < vb.size(); i++)
        b[i] = vb.at(i);
    b[i] = -1;
    return balance(a, b);
}

knownSet find2(vector<int> unknowns) {
    knownSet output;
    vector<int> a, b;
    a.push_back(unknowns.at(0));
    b.push_back(unknowns.at(1));
    int result = balanceWithVector(a, b);
    switch (result)
    {
    case LARGE:
        output.real.push_back(a.front());
        output.fake.push_back(b.front());
        break;
    case EQUAL:
        output.unknown = unknowns;
        break;
    case SMALL:
        output.real.push_back(b.front());
        output.fake.push_back(a.front());
    default:
        break;
    }
    return output;
}

knownSet find(vector<int> unknowns) {
    int num = unknowns.size();
    int* list = &list11[0][0];
    knownSet output;

    switch (num)
    {
    case 1:
        output.real = unknowns;
        return output;
    case 2:
        return find2(unknowns);
    case 3:
        list = &list3[0][0];
        break;
    case 4:
        list = &list4[0][0];
        break;
    case 5:
        list = &list5[0][0];
        break;
    case 6:
        list = &list6[0][0];
        break;
    case 7:
        list = &list7[0][0];
        break;
    case 8:
        list = &list8[0][0];
        break;
    case 9:
        list = &list9[0][0];
        break;
    case 10:
        list = &list10[0][0];
        break;
    default:
        list = &list11[0][0];
        num = 11;
        break;
    }
    vector<int> tmpa, tmpb, a, b;
    int ptr = 1;

    for (int i = 0; i < num; i++) {
        if (list[(ptr - 1) * num + i] == 1) tmpa.push_back(i);
        if (list[(ptr - 1) * num + i] == 2) tmpb.push_back(i);
    }
    for (int i = 0; i < tmpa.size(); i++) a.push_back(unknowns.at(tmpa.at(i)));
    for (int i = 0; i < tmpb.size(); i++) b.push_back(unknowns.at(tmpb.at(i)));

    while (tmpb.size() != 0) {
        int result = balanceWithVector(a, b);
        if (result == LARGE) ptr = ptr * 3 + 1;
        else if (result == EQUAL) ptr = ptr * 3;
        else if (result == SMALL) ptr = ptr * 3 - 1;
        a.clear(); b.clear(); tmpa.clear(); tmpb.clear();
        for (int i = 0; i < num; i++) {
            if (list[(ptr - 1) * num + i] == 1) tmpa.push_back(i);
            if (list[(ptr - 1) * num + i] == 2) tmpb.push_back(i);
        }
        for (int i = 0; i < tmpa.size(); i++) a.push_back(unknowns.at(tmpa.at(i)));
        for (int i = 0; i < tmpb.size(); i++) b.push_back(unknowns.at(tmpb.at(i)));
    }
    output.fake = a;
    for (int i = 0; i < num; i++) {
        bool flag = true;
        for (int j = 0; j < a.size(); j++) if (a.at(j) == unknowns.at(i)) flag = false;
        if (flag) output.real.push_back(unknowns.at(i));
    }
    if (output.fake.size() == 0) {
        output.unknown = output.real;
        output.real.clear();
    }
    return output;
}

knownSet guaranteedFind(knownSet result, int realCoin) {
    knownSet tmp;
    if (2 <= result.unknown.size()) tmp = find(result.unknown);
    else tmp.unknown = result.unknown;


    if (tmp.unknown.size() == 0) {
        result.fake.insert(result.fake.end(), tmp.fake.begin(), tmp.fake.end());
        result.real.insert(result.real.end(), tmp.real.begin(), tmp.real.end());
    }
    else {
        vector<int> a, b;
        a.push_back(realCoin);
        b.push_back(tmp.unknown.at(0));
        int r = balanceWithVector(a, b);
        switch (r) {
        case EQUAL:
            result.real.insert(result.real.end(), tmp.unknown.begin(), tmp.unknown.end());
            break;
        case LARGE:
            result.fake.insert(result.fake.end(), tmp.unknown.begin(), tmp.unknown.end());
            break;
        }
    }

    for (int i = 0; i < tmp.real.size() + tmp.fake.size() + tmp.unknown.size(); i++) {
        result.unknown.erase(result.unknown.begin());
    }

    return result;
}

