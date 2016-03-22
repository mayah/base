#include <iostream>

#include "base/file/path.h"

using namespace std;

int main()
{
    cout << file::get_current_directory() << endl;

    return 0;
}
