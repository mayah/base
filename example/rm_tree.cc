#include <iostream>
#include <string>

#include "base/file/path.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "rm_tree <filename or directory>" << endl;
        return 1;
    }

    string output;
    if (!file::delete_tree(argv[1])) {
        cerr << "failed to delete_tree: " << argv[1] << endl;
        return 1;
    }

    return 0;
}
