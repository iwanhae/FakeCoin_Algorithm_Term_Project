#include <cstdlib>
#include <iostream>
#include <ctime>
#include "balance.h"
#include "common.h"
#include<vector>

int arr[100];
int fcount = 0;  // 가짜 코인 
int bCount = 0;
int printFlag = 1;
int initrand = 0;

int getResult() {
    return bCount;
}
void initialize(int p) {
    /*
    std::vector<int> fakes{1,3,7,9,12,15,21,25,27,36,44,48,54,55,58,60,63,64,66,68,73,78,83,87,91,96,99};
    for(int i=0; i<100; i++) arr[i] = 100;
    for(int i=0; i<fakes.size(); i++){
        arr[fakes.at(i)] = 73;
        count++;
    }
    if(printFlag) std::cout << std::endl << "총" << count << "개 가짜코인" << std::endl;
    */

    if (initrand++ == 0) srand((unsigned int)time(0));
    fcount = 0;
    bCount = 0;
    for (int i = 0; i < 98; i++) {
        if (rand() % 100 < p) {
            arr[i] = 73;    // 가짜코인
            fcount++;
            if (printFlag) std::cout << "[" << i << "] ";
        }
        else {
            arr[i] = 100;   // 진짜코인
        }
    }

    arr[99] = 73;
    arr[98] = 100;
    fcount++;






    if (printFlag) std::cout << std::endl << "총" << fcount << "개 가짜코인" << std::endl;
}

int balance(int a[], int b[]) {
    int* tmpa = a;
    bCount++;
    if (printFlag) std::cout << bCount << "회 실행중" << std::endl;
    int suma = 0, sumb = 0, len = 0;
    if (printFlag) std::cout << "a: ";
    while (*a != -1) {
        suma += arr[*a];
        if (arr[*a] == 100) { if (printFlag) std::cout << *a << " "; }
        else { if (printFlag) std::cout << "[" << *a << "] ";; }
        a++;
    }
    if (printFlag) std::cout << std::endl << "b: ";
    while (*b != -1) {
        sumb += arr[*b];
        if (arr[*b] == 100) { if (printFlag) std::cout << *b << " "; }
        else { if (printFlag) std::cout << "[" << *b << "] ";; }
        b++;
        len++;
    }
    if (printFlag) std::cout << std::endl << std::endl;
    if (len == 0) {
        while (*tmpa != -1) {
            if (arr[*tmpa] != 73) {
                if (printFlag) std::cout << "실패" << std::endl;
                return ERROR;
            }
            tmpa++;
        }
        if (suma / 73 == fcount) {
            if (printFlag) std::cout << bCount << "회 만에 성공!!" << std::endl;
            return SUCCESS;
        }
        else {
            if (printFlag) std::cout << "실패" << std::endl;
            return ERROR;
        }
    }
    if (suma < sumb) {
        return SMALL;
    }
    else if (suma > sumb) {
        return LARGE;
    }
    else if (suma == sumb) {
        return EQUAL;
    }
}