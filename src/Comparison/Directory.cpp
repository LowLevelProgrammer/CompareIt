#include "Directory.h"

Directory::Directory(const std::filesystem::path &path) : Entry(path) {
  ComputeSize();
}

void Directory::ComputeSize() {}
