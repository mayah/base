#include <iostream>
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

using namespace std;

// ----------------------------------------------------------------------

inline std::string JoinPath(const std::string& a, const std::string& b) {
  if (a.empty()) return b;
  if (b.empty()) return a;

  if (a.back() == '/' && b.front() == '/') {
    return a + b.substr(1);
  } else if (a.back() == '/' || b.front() == '/') {
    return a + b;
  } else {
    return a + '/' + b;
  }
}

// ----------------------------------------------------------------------

struct DirEntry {
  DirEntry() : is_dir(false) {}

  string name;
  bool is_dir;
};

bool ListDirectory(const string& dirname, std::vector<DirEntry>* entries) {
  DIR* dir = opendir(dirname.c_str());
  if (dir == nullptr) {
    struct stat st;
    if (stat(dirname.c_str(), &st) != 0) {
      return false;
    }
    return !S_ISDIR(st.st_mode);
  }

  struct dirent* ent;
  while ((ent = readdir(dir)) != nullptr) {
    DirEntry dent;
    dent.name = ent->d_name;
    dent.is_dir = ent->d_type == DT_DIR;
    if (ent->d_type == DT_LNK) {
      struct stat st;
      if (stat(JoinPath(dirname, dent.name).c_str(), &st) == 0) {
        dent.is_dir = S_ISDIR(st.st_mode);
      }
    }
    entries->push_back(std::move(dent));
  }
  closedir(dir);
  return true;
}

template<typename F>
bool Walk(const std::string& dir, const F& f) {
  vector<DirEntry> entries;
  if (!ListDirectory(dir, &entries)) {
    return false;
  }

  for (const auto& entry : entries) {
    if (entry.name == "." || entry.name == "..") continue;
    if (!entry.is_dir) {
      // file pattern
      f(JoinPath(dir, entry.name));
      continue;
    }

    if (!Walk(JoinPath(dir, entry.name), f)) {
      return false;
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "need dir" << endl;
  }

  bool ok = Walk(argv[1], [](const std::string& path) {
    cout << path << endl;
  });

  if (!ok) {
    cerr << "failed to walk: " << argv[1] << endl;
  }

  return 0;
}
