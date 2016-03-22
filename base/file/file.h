#ifndef BASE_FILE_FILE_H_
#define BASE_FILE_FILE_H_

// file.h contains utility method to read a file.

#include <string>

#include "base/strings/string_piece.h"

namespace file {

// Reads file from |filename| and copy to |output|.
bool read_file(strings::StringPiece filename, std::string* output);

// Writes |data| to |filename|.
bool write_file(strings::StringPiece filename, const std::string& data);

// Copies file from |src| to |dest|.
bool copy_file(const char* src, const char* dest);

} // namespace file

#endif // BASE_FILE_FILE_H_
