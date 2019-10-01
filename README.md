### bin2cxx

It's C++ port of `bin2c` - simple utility for converting a binary file 
to a C/C++ header/source file which can then be included within an application.

Files generated by original `bin2c` contains "narrowing conversion" errors
and compile time constants (`const` keyword). In this fork format of output 
files was refined for compatibility with C++.

### Usage
```shell
bin2cxx input_file output_file identifier
```

### Example

Take some binary file:

![qr](test/qr.png)

Convert it to C++ header:

```shell
bin2cxx qr.png qr.hxx qr
```

Output file must be like:

```C++
#pragma once

#include <cstdint>

namespace qr {
constexpr std::uint8_t data[] = 
  { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d
  , 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 0xc8
  ...
  , 0x1d, 0xb4, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae
  , 0x42, 0x60, 0x82 };

constexpr std::size_t size = 2019;
}
```

Also you can use it as a single-header library. Just add `bin2cxx.hxx` file to 
your project and see `test` directory for examples.