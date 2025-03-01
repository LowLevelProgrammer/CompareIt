#pragma once

#include "Entry.h"

class Directory : public Entry {
public:
  Directory(const std::filesystem::path &path);
  ~Directory() = default;

  virtual void ComputeSize() override;
};
