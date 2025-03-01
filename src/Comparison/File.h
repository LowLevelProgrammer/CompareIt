#pragma once

#include "Entry.h"
#include <string>

class File : public Entry {
public:
  explicit File(const std::filesystem::path &path);
  ~File() = default;

  std::string GetExtension() const { return m_Extension; }

private:
  virtual void ComputeSize() override;
  void DetectExtension();

private:
  std::string m_Extension;
};
