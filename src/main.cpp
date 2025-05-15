#include "Comparator.h"
#include <iostream>

int main(int argc, char *argv[]) {

  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <Folder1Path> <Folder2Path>"
              << std::endl;
    return 1;
  }

  std::filesystem::path dir1(argv[1]);
  std::filesystem::path dir2(argv[2]);
  std::cout << "Dir 1 = " << dir1 << std::endl;
  std::cout << "Dir 2 = " << dir2 << std::endl;

  Comparator comparator;
  comparator.SetDirectory1(dir1);
  comparator.SetDirectory2(dir2);
  bool areIdentical = comparator.Compare();

  std::cout << "Are count identical: " << (areIdentical ? "Yes" : "No")
            << std::endl;
}
