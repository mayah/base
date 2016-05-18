#include <iostream>
#include <string>
#include <vector>

#include "base/strings/strings.h"
#include "base/file/file.h"
#include "third_party/glog/glog/logging.h"

using namespace std;

// format
// A: B C D E F
//    G H I J K

// test:hoge.o: test2.c hoge\ fuga/a.h fuga:hoge/b.h

struct ParseResult {
    std::string key;
    std::vector<std::string> files;
};

bool parse(const std::string& content, ParseResult* result)
{
    size_t pos = 0;
    {
        std::string::size_type x = content.find(' ');
        if (x == std::string::npos || x == 0) {
            LOG(ERROR) << "failed to find key";
            return false;
        }
        std::string key = content.substr(0, x);
        DCHECK(!key.empty());

        if (!strings::has_suffix(key, ":")) {
            LOG(ERROR) << "key does not have last ':': key=" << key;
            return false;
        }

        result->key = key.substr(0, key.size() - 1);
        pos = x + 1;
    }

    while (pos < content.size() && pos != string::npos) {
        pos = content.find_first_not_of(" \t\r\n", pos);
        if (pos == string::npos)
            break;

        stringstream ss;
        while (pos < content.size()) {
            if (content[pos] == ' ' || content[pos] == '\t' || content[pos] == '\r' || content[pos] == '\n') {
                break;
            }
            if (content[pos] == '\\') {
                ++pos;
                if (pos == content.size())
                    return false;
                if (content[pos] == '\r' || content[pos] == '\n') {
                    continue;
                }
                ss << content[pos++];
                continue;
            }

            ss << content[pos++];
        }

        std::string s = ss.str();
        if (!s.empty())
            result->files.push_back(s);
    }

    return true;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Usage: deps_parser <filename>" << endl;
        return EXIT_FAILURE;
    }

    std::string content;
    if (!file::read_file(argv[1], &content)) {
        LOG(ERROR) << "failed to read file: file=" << argv[1];
        return EXIT_FAILURE;
    }

    ParseResult result;
    if (!parse(content, &result)) {
        LOG(ERROR) << "failed to rewrite";
        return EXIT_FAILURE;
    }

    cout << "key: " << result.key << endl;
    cout << "files:" << endl;
    for (const auto& file : result.files) {
        cout << file << endl;
    }

    return EXIT_SUCCESS;
}
