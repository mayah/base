// Reads file, and convert it to C-like array.

#include <gflags/gflags.h>
#include <iostream>
#include <sstream>

#include "base/file/file.h"

DEFINE_string(name, "name", "filename. This should not contain space.");

char to_hex[] = "0123456789abcdef";

int main(int argc, char* argv[])
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if (argc < 2) {
        std::cerr << "binary_to_c <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string name = FLAGS_name;

    std::string content;
    CHECK(file::read_file(argv[1], &content))
        << "failed to load file: " << argv[1];

    // Writes header file.
    std::stringstream header;
    header << "#pragma once" << std::endl;
    header << "#include <cstddef>" << std::endl;
    header << "#include <cstdint>" << std::endl;
    header << "extern const std::size_t " << name << "_size;" << std::endl;
    header << "extern const std::uint8_t " << name << "[];" << std::endl;

    CHECK(file::write_file(name + ".h", header.str()));

    // Writes body file.
    std::stringstream body;
    body << "#include \"" << name << ".h" << "\"" << std::endl;
    body << "const std::size_t " << name << "_size = " << content.size() << ";" << std::endl;
    body << "const std::uint8_t " << name << "[] = {" << std::endl;
    int size = 0;
    for (unsigned char c : content) {
        if (size >= 72) {
            body << std::endl;
            size = 0;
        }

        if (size == 0) {
            body << "   ";
            size += 3;
        }

        body << " 0x" << to_hex[c / 16] << to_hex[c % 16] << ",";
        size += 6;
    }

    body << std::endl;
    body << "};" << std::endl;
    CHECK(file::write_file(name + ".cc", body.str()));

    return EXIT_SUCCESS;
}
