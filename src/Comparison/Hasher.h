#pragma once

#include "Entry.h"
#include <functional>

struct RelativeEntry {
  Entry *entry;
  std::filesystem::path relativePath;

  RelativeEntry(Entry *e, const std::filesystem::path &basePath)
      : entry(e), relativePath(std::filesystem::relative(e->GetPath(), basePath)
                                   .lexically_normal()) {}
};

struct RelativeEntryHasher {
  std::size_t operator()(const RelativeEntry &re) const {
    return std::hash<std::string>()(re.relativePath.string());
  }
};

struct RelativeEntryEqual {
  bool operator()(const RelativeEntry &a, const RelativeEntry &b) const {
    return a.relativePath == b.relativePath;
  }
};
