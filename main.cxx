

#include "bin2cxx.hxx"

int
main(int argc, char* argv[])
{
  if (argc < 4) {
    std::cerr << "Usage: bin2cxx binary_file output_file identifier\n";
    return 1;
  }

  bin2cxx::read_encode_write(argv[1], argv[2], argv[3]);

  return 0;
}
