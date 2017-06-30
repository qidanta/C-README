#include <iostream>
#include <vector>
#include <string>
#include "./rect/calculate.h"
#include "./rect/read.h"

using namespace std;

void test_per() {
    vector<string> mps = read("/home/eric/CLionProjects/readme/README/compile-jpg.txt");
    for (int i = 0; i < mps.size(); ++i) {
        //"POLYGON((0 0,0 200,200 200,200 0,0 0))" pg contain rect
        //"POLYGON((200 200,200 400,400 400,400 200,200 200))" pg overlap rect
        // "POLYGON((0 0,0 400,400 400,400 0,0 0))" rect contain pg
        // "" can't calculate pg = rect
        cout << per("POLYGON((0 0,0 200,200 200,200 0,0 0))",  mps[i]);
    }
}

int main() {
    test_per();
    cout << "Hello, World!" << endl;
    return 0;
}