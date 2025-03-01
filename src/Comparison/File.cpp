#include "File.h"

#include "Entry.h"

File::File(const std::filesystem::path &path) : Entry(path) {
  ComputeSize();
  DetectExtension();
}

void File::ComputeSize() { m_Size = std::filesystem::file_size(m_Path); }

void File::DetectExtension() {
  m_Extension = m_Path.extension().string();
}
