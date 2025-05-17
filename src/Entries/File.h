#pragma once

#include "Entry.h"

class File : public Entry {
public:
  explicit File(const std::filesystem::path &path);
  ~File() = default;

  bool Refresh() override;

  std::string GetExtension() const { return m_Extension; }
  EntryType GetType() const override { return EntryType::File; }

private:
  void ComputeSize();
  void DetectExtension();

private:
  std::string m_Extension;
};
