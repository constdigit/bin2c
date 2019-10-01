#include <experimental/filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::experimental::filesystem;

int
main(int argc, char* argv[])
{
  if (argc < 4) {
    std::cerr << "Usage: bin2cxx binary_file output_file array_name\n";
    return 1;
  }

  std::ifstream binary_file(argv[1], std::ios::in | std::ios::binary);
  if (!binary_file.is_open()) {
    std::cerr << "Invalid binary file: " << argv[1] << '\n';
    return 2;
  }

  auto binary_file_size =
    static_cast<std::size_t>(fs::file_size(fs::path{ argv[1] }));

  std::vector<std::uint8_t> binary_file_data(binary_file_size);
  binary_file.read(reinterpret_cast<char*>(binary_file_data.data()),
                   binary_file_size);
  binary_file.close();

  std::ofstream output_file(argv[2]);
  if (!output_file.is_open()) {
    std::cerr << "Can't create output file: " << argv[2] << '\n';
    return 3;
  }

  std::string identifier = argv[3];
  output_file << "#pragma once\n\n"       // include guard
                 "#include <cstdint>\n\n" // fixed width integer types
                 "namespace "
              << identifier
              << " {\n"
                 "constexpr std::uint8_t data[] = \n\t{ ";

  // Binary data writes as hexadecimal literals inside initializer list. To make
  // output more pretty, one-digit values are amended by insignificant zero.
  // First value should be written without leading comma.
  output_file << "0x" << std::setfill('0') << std::setw(2) << std::hex
              << static_cast<std::uint32_t>(binary_file_data[0]);
  for (size_t i = 1; i < binary_file_size; i++) {
    output_file << ", 0x" << std::setfill('0') << std::setw(2) << std::hex
                << static_cast<std::uint32_t>(binary_file_data[i]);
    if ((i % 11) == 10) { // new line after each
      output_file << "\n\t";
    }
  }
  output_file << " };\n\n"; // close initializer list

  output_file << "constexpr std::size_t size = " << std::dec << binary_file_size
              << ";\n}"; // close namespace

  output_file.close();

  return 0;
}
