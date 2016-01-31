#include <iostream>
#include <string>

#include "base/file/file.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "write_file <filename>" << endl;
        return 1;
    }

    string data("This is an example string.\nHello, World!\n");
    if (!file::write_file(argv[1], data)) {
        cerr << "failed to write file: " << argv[1] << endl;
        return 1;
    }

    return 0;
}
