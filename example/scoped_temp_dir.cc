#include "base/file/scoped_temp_dir.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    file::ScopedTempDir st("test");
    if (st) {
        cout << "path=" << st.path() << endl;
        cout << "press enter to exit.";
        string str;
        getline(cin, str);
    } else {
        cout << "failed to make tempdir." << endl;
    }

    return 0;
}
