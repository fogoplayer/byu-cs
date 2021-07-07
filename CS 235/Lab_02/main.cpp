/**
 * Zarin Loosli - 7/7/21
**/
#include <iostream>
#include <string>

#include "main.h"
#include "Snap.h"
#include "Csg.h"
#include "Cdh.h"

using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int main(int argc, char *argv[])
{
    VS_MEM_CHECK
    Snap snap;
    Csg csg("Course name");
    Cdh cdh("name", "day", "time");
    cout << snap << csg << cdh;
    return 0;
}

/*-------------------------------Function Definitions-------------------------------*/
