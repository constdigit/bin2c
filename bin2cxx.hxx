#pragma once

#include <experimental/filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace bin2cxx {
namespace fs = std::experimental::filesystem;

std::vector<std::uint8_t>
read_binary_file(std::string binary_file_name)
{
  std::ifstream binary_file(binary_file_name, std::ios::in | std::ios::binary);
  if (!binary_file.is_open()) {
    throw std::invalid_argument(binary_file_name);
  }

  auto binary_file_size =
    static_cast<std::size_t>(fs::file_size(fs::path{ binary_file_name }));

  std::vector<std::uint8_t> binary_file_data(binary_file_size);
  binary_file.read(reinterpret_cast<char*>(binary_file_data.data()),
                   binary_file_size);
  binary_file.close();

  return binary_file_data;
}

std::string
encode(std::vector<std::uint8_t> binary_file_data, std::string identifier)
{
  std::ostringstream output_stream;

  output_stream << "#pragma once\n\n"       // include guard
                   "#include <cstdint>\n\n" // fixed width integer types
                   "namespace "
                << identifier
                << " {\n"
                   "constexpr std::uint8_t data[] = \n  { ";

  // Binary data writes as hexadecimal literals inside initializer list. To make
  // output more pretty, one-digit values are amended by insignificant zero.
  // First value should be written without leading comma.
  output_stream << "0x" << std::setfill('0') << std::setw(2) << std::hex
                << static_cast<std::uint32_t>(binary_file_data[0]);
  for (size_t i = 1; i < binary_file_data.size(); i++) {
    output_stream << ", 0x" << std::setfill('0') << std::setw(2) << std::hex
                  << static_cast<std::uint32_t>(binary_file_data[i]);
    if ((i % 12) == 11) { // new line after each 11 values
      output_stream << "\n  ";
    }
  }
  output_stream << " };\n\n"; // close initializer list

  output_stream << "constexpr std::size_t size = " << std::dec
                << binary_file_data.size() << ";\n}"; // close namespace

  return output_stream.str();
}

void
write_output_file(std::string output_file_name, std::string encoded_data)
{
  std::ofstream output_file(output_file_name);
  if (!output_file.is_open()) {
    throw std::invalid_argument(output_file_name);
  }

  output_file << encoded_data;

  output_file.close();
}

void
read_encode_write(std::string binary_file_name,
                  std::string output_file_name,
                  std::string identifier)
{
  auto binary_data = read_binary_file(binary_file_name);
  auto encoded_data = encode(std::move(binary_data), identifier);
  write_output_file(output_file_name, std::move(encoded_data));
}
}