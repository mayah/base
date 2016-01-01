#include <iostream>
#include <string>

#include "base/file/file.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "read_file <filename>" << endl;
        return 1;
    }

    string output;
    if (!file::readFile(argv[1], &output)) {
        cerr << "failed to read file: " << argv[1] << endl;
        return 1;
    }

    cout << output;
    return 0;
}
