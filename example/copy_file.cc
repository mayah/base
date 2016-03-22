#include <iostream>
#include <string>

#include "base/file/file.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cerr << "copy_file <src> <dest>" << endl;
        return 1;
    }

    if (!file::copy_file(argv[1], argv[2])) {
        cerr << "failed to copy file:"
             << " src=" << argv[1]
             << " dest=" << argv[2] << endl;
        return 1;
    }

    return 0;
}
