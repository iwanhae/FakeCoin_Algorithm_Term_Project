#include "common.h"

/**
 * 기본적으로 11개씩 비교를 해서 가짜 진짜가 갈릴때까지 계속 탐색하는 과정
 * 0번 ~ 10번 (11개) 코인에 가짜 진짜가 섞여있다면
*/
// unknown의 개수는 100개를 가정하고 설계됨. 다른경우는 사용하지 말것!
knownSet findInitialSet(vector<int> unknown) {
    int ptr = 0, loop = 0;
    vector<int> unknowns[10];
    knownSet output;


    for (int i = 0; i < 11; i++) unknowns[loop].push_back(unknown.at(ptr++));
    knownSet result = find(unknowns[loop]);
    if (result.unknown.size() == 0) {
        output.real.insert(output.real.end(), result.real.begin(), result.real.end());
        output.fake.insert(output.fake.end(), result.fake.begin(), result.fake.end());
        while (ptr < 100) output.unknown.push_back(unknown.at(ptr++));
        return output;
    }

    while (output.real.size() == 0 && output.fake.size() == 0) {
        loop += 1;
        if (loop == 9) { // Last one is special one
            int a[] = { 0, -1 };
            int b[] = { 99, -1 };
            int r = balance(a, b);
            switch (r)
            {
            case LARGE:
                for (int i = 0; i < loop; i++)output.real.insert(output.real.end(), unknowns[i].begin(), unknowns[i].end());
                output.fake.push_back(99);
                break;
            case EQUAL:
                exit(-1); // IMPOSSIBLE CASE
                break;
            case SMALL:
                for (int i = 0; i < loop; i++)output.fake.insert(output.fake.end(), unknowns[i].begin(), unknowns[i].end());
                output.real.push_back(99);
                break;
            }
            return output;
        }
        for (int i = 0; i < 11; i++) unknowns[loop].push_back(unknown.at(ptr++));
        int r = balanceWithVector(unknowns[0], unknowns[loop]);
        switch (r)
        {
        case LARGE:
            for (int i = 0; i < loop; i++)output.real.insert(output.real.end(), unknowns[i].begin(), unknowns[i].end());
            break;
        case EQUAL:
            break;
        case SMALL:
            for (int i = 0; i < loop; i++)output.fake.insert(output.fake.end(), unknowns[i].begin(), unknowns[i].end());
            break;
        }
    }
    result = find(unknowns[loop]);
    output.real.insert(output.real.end(), result.real.begin(), result.real.end());
    output.fake.insert(output.fake.end(), result.fake.begin(), result.fake.end());
    while (ptr < 100) output.unknown.push_back(unknown.at(ptr++));
    return output;
}
