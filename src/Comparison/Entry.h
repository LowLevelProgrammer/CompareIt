#pragma once

#include <filesystem>
#include <string>

class Entry {
public:
  Entry(const std::filesystem::path& path) {

    // TODO: Add validation for path
    m_Path = path;
    m_Name = m_Path.filename().string();
    m_IsSymlink = std::filesystem::is_symlink(m_Path);
    m_Size = 0;
  }
  virtual ~Entry() = default;

  virtual void ComputeSize() = 0;

  std::filesystem::path GetPath() const { return m_Path; }
  std::string GetName() const { return m_Name; }
  bool IsSymlink() const { return m_IsSymlink; }
  std::uintmax_t GetSize() const { return m_Size; }

protected:
  std::filesystem::path m_Path;
  std::string m_Name;
  bool m_IsSymlink;
  std::uintmax_t m_Size;
};
