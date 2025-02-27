#include "File.h"

#include <iostream>

int main(int argc, char* argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  std::filesystem::path cwd = std::filesystem::current_path();
  std::filesystem::path filePath = cwd / argv[1];

  if (!std::filesystem::exists(filePath)) {
    std::cerr << "File " << filePath.string() << " does not exist" << std::endl;
    return 1;
  }

  File file(filePath);

  std::cout << "File: " << file.GetName() << std::endl;
  std::cout << "Size of file: " << file.GetSize() << std::endl;
  std::cout << "Extension: " << file.GetExtension() << std::endl;
  std::cout << "Path: " << file.GetPath() << std::endl;
}
