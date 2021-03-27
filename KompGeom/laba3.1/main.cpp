#include <bits/stdc++.h>
#include "Settings.h"

using namespace std;

int main(int argc, char** argv) {
    try {
        Settings settings(argc, argv);
    } catch(exception& ex) {
        cout << "ERROR " << ex.what() << endl;
    }
}
