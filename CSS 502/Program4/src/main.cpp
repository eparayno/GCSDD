#define _CRTBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#include <iostream>
#include "Store.h"
#include <string>
using namespace std;

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(272); // coin
    //_CrtSetBreakAlloc(273); // comic
    //_CrtSetBreakAlloc(296); // sportscard
    //_CrtSetBreakAlloc(297); // displayhistory
    //_CrtSetBreakAlloc(319); // comic
    //_CrtSetBreakAlloc(320); // coin
    //_CrtSetBreakAlloc(321); // comic
    // _CrtSetBreakAlloc(322); // comic
    //_CrtSetBreakAlloc(351); // comic
    //_CrtSetBreakAlloc(354); // comic
    //_CrtSetBreakAlloc(384); // sportscard
    // _CrtSetBreakAlloc(411); // vector stringstream
    //_CrtSetBreakAlloc(668); // sportscard
    //_CrtSetBreakAlloc(673); // sportscard
    //_CrtSetBreakAlloc(768); // sportscard
    //_CrtSetBreakAlloc(774); // sportscard

    Store collectiblesStore;
    collectiblesStore.execute();

    return 0;
}
