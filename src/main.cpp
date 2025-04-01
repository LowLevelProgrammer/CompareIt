#include "Directory.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

	Directory dir("D:\\Projects\\Cpp\\CompareIt");
  dir.ComputeTotalSize();
  std::cout << "Size of dir = " << (dir.GetSize().has_value() ? std::to_string(dir.GetSize().value()) : "N/A") << std::endl;

  dir.PrintDirectory();

}
