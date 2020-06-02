#include "common.h"

// int printFlag = 0;

int gambling(knownSet result) {
    vector<int> tmp;
    int estimatePvalue = ((double)result.fake.size() / (double)(result.fake.size() + result.real.size())) * 100;
    tmp.clear();
    if (result.unknown.size() == 1) {
        if(printFlag) cout << "1gamble start" << endl;
        if (estimatePvalue <= 50) {
            int r = balanceWithVector(result.fake, tmp);
            if (r == SUCCESS) {
                if (printFlag) cout << "1 gamble SUC" << endl;
                return SUCCESS;
            }
            else {
                result.fake.push_back(result.unknown.at(0));
                result.unknown.clear();
                r = balanceWithVector(result.fake, tmp);
                if (r == SUCCESS) {
                    return SUCCESS;
                }
                else {
                    cout << "\tFAIL";
                    return ERROR;
                }
            }
        }
        else {
            result.fake.push_back(result.unknown.at(0));
            int r = balanceWithVector(result.fake, tmp);
            if (r == SUCCESS) {
                if (printFlag) cout << "1 gamble SUC" << endl;
                return SUCCESS;
            }
            else {
                result.fake.pop_back();
                result.real.push_back(result.unknown.at(0));
                result.unknown.clear();
                r = balanceWithVector(result.fake, tmp);
                if (r == SUCCESS) {
                    return SUCCESS;
                }
                else {
                    if (printFlag) cout << "\tFAIL";
                    return ERROR;
                }
            }
        }
    }
    else {
        if (printFlag) cout << "2gamble start" << endl;
        if (estimatePvalue <= 50) {
            int r = balanceWithVector(result.fake, tmp);
            if (r == SUCCESS) {
                if (printFlag) cout << "2 gamble SUC" << endl;
                return SUCCESS;
            }
            else {
                vector<int> tmpa;
                vector<int> tmpb;
                tmpa.push_back(result.unknown.at(0));
                tmpb.push_back(result.unknown.at(1));
                r = balanceWithVector(tmpa, tmpb);
                switch (r) {
                case LARGE: {
                    result.real.push_back(result.unknown.at(0));
                    result.fake.push_back(result.unknown.at(1));
                    result.unknown.clear();
                    break;
                }
                case EQUAL: {
                    result.fake.push_back(result.unknown.at(0));
                    result.fake.push_back(result.unknown.at(1));
                    result.unknown.clear();
                    break;
                }
                case SMALL: {
                    result.fake.push_back(result.unknown.at(0));
                    result.real.push_back(result.unknown.at(1));
                    result.unknown.clear();
                    break;
                }
                }
                r = balanceWithVector(result.fake, tmp);
                if (r == SUCCESS) {
                    return SUCCESS;
                }
                else {
                    if (printFlag) cout << "\tFAIL";
                    return ERROR;
                }
            }
        }
        else {
            result.fake.push_back(result.unknown.at(0));
            result.fake.push_back(result.unknown.at(1));
            int r = balanceWithVector(result.fake, tmp);
            if (r == SUCCESS) {
                if (printFlag) cout << "2 gamble SUC" << endl;
                return SUCCESS;
            }
            else {
                result.fake.pop_back();
                result.fake.pop_back();
                vector<int> tmpa;
                vector<int> tmpb;
                tmpa.push_back(result.unknown.at(0));
                tmpb.push_back(result.unknown.at(1));
                r = balanceWithVector(tmpa, tmpb);
                switch (r) {
                case LARGE: {
                    result.real.push_back(result.unknown.at(0));
                    result.fake.push_back(result.unknown.at(1));
                    result.unknown.clear();
                    break;
                }
                case EQUAL: {
                    result.real.push_back(result.unknown.at(0));
                    result.real.push_back(result.unknown.at(1));
                    result.unknown.clear();
                    break;
                }
                case SMALL: {
                    result.fake.push_back(result.unknown.at(0));
                    result.real.push_back(result.unknown.at(1));
                    result.unknown.clear();
                    break;
                }
                }
                r = balanceWithVector(result.fake, tmp);
                if (r == SUCCESS) {
                    return SUCCESS;
                }
                else {
                    if (printFlag) cout << "\tFAIL";
                    return ERROR;
                }
            }
        }
    }
}