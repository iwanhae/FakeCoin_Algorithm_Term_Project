#include "common.h"

int main(int argc, char ** argv)
{
    int p = 50;
    if (argc != 1) {
        p = atoi(argv[1]);
    }
    initialize(p);
    vector<int> history;
    knownSet result;
    for (int i = 0; i < 100; i++) result.unknown.push_back(i);
    result = findInitialSet(result.unknown); // real, fake 몇개는 찾아둔 상태.
    while (result.unknown.size() > 2) {
        int estimatePvalue = ((double)result.fake.size() / (double)(result.fake.size() + result.real.size())) * 100;
        if (estimatePvalue <= 23) { // 0~23
            if (result.real.size() >= 4 && result.fake.size() >= 1 && result.unknown.size() >= 5) {
                result = compareBy5(result.real, result.fake, result.unknown);
            }
            else if (result.real.size() >= 2 && result.fake.size() >= 1 && result.unknown.size() >= 3) {
                result = CompareBy3(result.real, result.fake, result.unknown);
            }
            else {
                result = guaranteedFind(result, result.real.at(0));
            }

        }
        else if (estimatePvalue <= 38) { // 24~38
            if (result.real.size() >= 2 && result.fake.size() >= 1 && result.unknown.size() >= 3) {
                result = CompareBy3(result.real, result.fake, result.unknown);
            }
            else {
                result = guaranteedFind(result, result.real.at(0));
            }
        }
        else if (estimatePvalue <= 62) { // 38~62
            result = guaranteedFind(result, result.real.at(0));
        }
        else if (estimatePvalue <= 77) { // 63~77
            if (result.real.size() >= 1 && result.fake.size() >= 2 && result.unknown.size() >= 3) {
                result = CompareBy3_rvs(result.real, result.fake, result.unknown);
            }
            else {
                result = guaranteedFind(result, result.real.at(0));
            }
        }
        else if (estimatePvalue <= 100) { // 78~100
            if (result.real.size() >= 1 && result.fake.size() >= 4 && result.unknown.size() >= 5) {
                result = compareBy5_rvs(result.real, result.fake, result.unknown);
            }
            else if (result.real.size() >= 1 && result.fake.size() >= 2 && result.unknown.size() >= 3) {
                result = CompareBy3_rvs(result.real, result.fake, result.unknown);
            }
            else {
                result = guaranteedFind(result, result.real.at(0));
            }
        }
    }
    if(result.unknown.size()==0){
    	int r = balanceWithVector(result.fake, result.unknown);
    	if (r == SUCCESS) {
        	// cout << "\t" << getResult();
    	}
    	else {
        	cout << "\tFAIL";
    	}
    }
    else{
        int r = gambling(result);
        if (r == SUCCESS) {
            // cout << "\t" << getResult();
        }
        else {
            cout << "\tFAIL";
        }
    }
}