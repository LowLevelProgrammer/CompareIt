#include "File.h"

File::File(const std::filesystem::path &path)
    : m_Path(path), m_Name(m_Path.filename().string()) {
  m_Size = std::filesystem::file_size(m_Path);
  m_Extension = m_Path.extension().string();
}

