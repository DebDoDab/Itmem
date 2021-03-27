#include <iostream>
#include "pe.h"

using namespace std;

int main() {
    PE bolgenos("test.ekze");
/// PE bolgenos("api-ms-win-core-file-l1-1-0.dll");
    bolgenos.showHeaderInfo();
    bolgenos.showSectionsInfo();
    bolgenos.showRelocationInfo();
    bolgenos.showSymbolTableinfo();
    bolgenos.showExportTable();
    bolgenos.showImportTable();
}
