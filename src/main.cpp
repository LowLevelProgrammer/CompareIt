#include "Comparator.h"
#include <iostream>

int main(int argc, char *argv[]) {

  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <file1Path> <file2Path>" << std::endl;
    return 1;
  }

  File file1(argv[1]);
  File file2(argv[2]);
  std::cout << "File 1 = " << file1.GetPath() << ", Is Valid: " << (file1.IsValid() ? "Yes" : "No") << std::endl;
  std::cout << "File 2 = " << file2.GetPath() << ", Is Valid: " << (file2.IsValid() ? "Yes" : "No") << std::endl;


  Comparator comparator;
  bool areIdentical = comparator.AreFilesIdentical(file1, file2);

  std::cout << "Are files identical: " << (areIdentical? "Yes" : "No") << std::endl;
}
