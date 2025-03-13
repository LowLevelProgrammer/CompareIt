#include "Directory.h"

#include <filesystem>
#include <iostream>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  std::filesystem::path cwd = std::filesystem::current_path();
  std::filesystem::path path = cwd / argv[1];

  if (!std::filesystem::exists(path)) {
    std::cerr << "File " << path.string() << " does not exist" << std::endl;
    return 1;
  }

  Directory directory(path);

  directory.PrintDirectory();
}
