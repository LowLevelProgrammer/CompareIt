#include "File.h"

File::File(const std::filesystem::path &path) : Entry(path) { Refresh(); }

bool File::Refresh() {

  if (!IsValid()) {
    return false;
  }

  ComputeSize();
  DetectExtension();
  return true;
}

void File::ComputeSize() { m_Size = std::filesystem::file_size(m_Path); }

void File::DetectExtension() { m_Extension = m_Path.extension().string(); }
