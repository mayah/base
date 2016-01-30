#include "base/file/scoped_temp_file.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    file::ScopedTempFile tf("test");
    cout << tf.path() << endl;
    cout << tf.fd() << endl;

    return 0;
}
