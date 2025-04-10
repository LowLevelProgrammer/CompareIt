#pragma once

#include "Entry.h"

class File : public Entry {
public:
  explicit File(const std::filesystem::path &path);
  ~File() = default;

  bool Refresh() override;

  std::string GetExtension() const { return m_Extension; }

private:
  void ComputeSize();
  void DetectExtension();

private:
  std::string m_Extension;
};
