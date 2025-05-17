#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <system_error>

enum class EntryType { File, Directory };

class Entry {
public:
  Entry(const std::filesystem::path &path) {
    m_Path = std::filesystem::absolute(path);
    m_Name = m_Path.filename().string();
    std::error_code ec;
    m_IsSymlink = std::filesystem::is_symlink(m_Path, ec);
    m_Size = std::nullopt;
  }
  virtual ~Entry() = default;

  virtual bool Refresh() = 0;
  virtual EntryType GetType() const = 0;
  bool IsValid() { return std::filesystem::exists(m_Path); }

  std::filesystem::path GetPath() const { return m_Path; }
  std::string GetName() const { return m_Name; }
  bool IsSymlink() const { return m_IsSymlink; }

  /**
   * Return the size of the Entry. Call only after calling ComputeTotalSize for
   * Directory
   */
  std::optional<std::uintmax_t> GetSize() const { return m_Size; }

protected:
  std::filesystem::path m_Path;
  std::string m_Name;
  bool m_IsSymlink;
  std::optional<std::uintmax_t> m_Size;
};

using EntryPtr = std::shared_ptr<Entry>;
