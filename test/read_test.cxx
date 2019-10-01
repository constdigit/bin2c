#include "bin2cxx.hxx"
#include "qr.hxx"

int
main(int argc, char* argv[])
{
  if (bin2cxx::read_binary_file(argv[1]) ==
      std::vector<std::uint8_t>(qr::data, qr::data + qr::size)) {
    std::cout << "pass\n";
  } else {
    std::cout << "failed\n";
  }
  return 0;
}