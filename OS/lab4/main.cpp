#include <iostream>
#include "pe.h"

using namespace std;

int main() {
    PE sex("test.ekze");
//    PE sex("api-ms-win-core-file-l1-1-0.dll");
//    sex.showHeaderInfo();
//    sex.showSectionsInfo();
    sex.showSymbolTableinfo();
    sex.showRelocationInfo();
}
