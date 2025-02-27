#pragma once

#include <filesystem>
#include <string>

class File {
public:
  explicit File(const std::filesystem::path &path);
  ~File() = default;

  inline std::string GetName() const { return m_Name; }
  inline std::uintmax_t GetSize() const { return m_Size; }
  inline std::string GetExtension() const { return m_Extension; }
  inline std::string GetPath() const { return m_Path.string(); }

private:
  std::filesystem::path m_Path;
  std::string m_Name;
  std::uintmax_t m_Size = 0;
  std::string m_Extension;
};
