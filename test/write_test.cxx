#include "bin2cxx.hxx"
#include "qr.hxx"

namespace fs = std::experimental::filesystem;

int
main()
{
  std::vector<std::uint8_t> binary_data(qr::data, qr::data + qr::size);
  auto encoded_data = bin2cxx::encode(binary_data, "qr");

  std::string output_file_name = "_qr_test.hxx";
  bin2cxx::write_output_file(output_file_name, encoded_data);
  fs::path output_file(output_file_name);

  if (!fs::exists(output_file)) {
    std::cerr << "File doesn't exist\n";
    return 1;
  }

  constexpr size_t expected_file_size = 12743;
  if (fs::file_size(output_file) != expected_file_size) {
    std::cerr << "Wrong file size: expected " << expected_file_size << " but get "
              << fs::file_size(output_file) << '\n';
    return 2;
  }

  if (!fs::is_regular_file(output_file)) {
    std::cerr << "Wrong file type\n";
    return 3;
  }

  fs::remove(output_file);
  std::cout << "pass\n";
  return 0;
}