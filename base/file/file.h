#ifndef BASE_FILE_FILE_H_
#define BASE_FILE_FILE_H_

#include <string>

#include "base/strings/string_piece.h"

namespace file {

bool is_directory(const char* path);

// Reads file from |filename| and copy to |output|.
bool read_file(const strings::StringPiece& filename, std::string* output);

} // namespace file

#endif // BASE_FILE_FILE_H_
