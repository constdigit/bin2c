#include "bin2cxx.hxx"
#include "qr.hxx"

int
main(int argc, char* argv[])
{
  auto binary_data = bin2cxx::read_binary_file(argv[1]);
  std::string encoded_data(binary_data.begin(), binary_data.end());

  if (bin2cxx::encode(std::vector<std::uint8_t>(qr::data, qr::data + qr::size),
                      "qr") == encoded_data) {
    std::cout << "pass\n";
  } else {
    std::cout << "failed\n";
  }
  return 0;
}