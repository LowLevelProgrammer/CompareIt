#pragma once

#include "Directory.h"
#include "Hasher.h"

#include <cassert>
#include <iostream>
#include <unordered_set>

inline void PrintLeafEntries(std::vector<Entry *> leafEntries,
                             std::string directoryName = "") {
  std::cout << (directoryName == "" ? "Directory's" : directoryName + "'s")
            << " Leaf Entries" << std::endl;
  for (size_t i = 0; i < leafEntries.size(); i++) {
    printf("%4zu. %s\n", i + 1, leafEntries[i]->GetPath().string().c_str());
  }
}

inline void PrintEntries(std::vector<Entry *> entries,
                         Entry *currentEntry = new Directory("")) {
  std::vector<Entry *> directories;
  std::vector<Entry *> files;

  for (const auto &entry : entries) {
    if (entry->GetType() == EntryType::Directory) {
      directories.push_back(entry);
    } else if (entry->GetType() == EntryType::File) {
      files.push_back(entry);
    }
  }

  if (currentEntry->GetType() == EntryType::File) {
    std::cout << currentEntry->GetPath() << std::endl;
  } else if (currentEntry->GetType() == EntryType::Directory) {
    std::cout << currentEntry->GetPath() << "/" << std::endl;
  }

  for (const auto &dir : directories) {
    Directory *dirPtr = dynamic_cast<Directory *>(dir);

    if (dirPtr) {
      PrintEntries(dirPtr->GetDirectoriesEntry(), dir);
    } else {
      std::cerr << "Shouldn't Happen" << std::endl;
    }
  }

  for (const auto &file : files) {
    File *filePtr = dynamic_cast<File *>(file);

    if (filePtr) {
      std::cout << filePtr->GetPath() << std::endl;
    } else {
      std::cerr << "Shouldn't Happen" << std::endl;
    }
  }
}

inline void PrintSet(
    std::unordered_set<RelativeEntry, RelativeEntryHasher, RelativeEntryEqual>
        uset,
    std::string setName = "") {

  std::cout << (setName == "" ? "Set's" : setName + "'s") << " Entries"
            << std::endl;
  size_t i = 1;

  for (const auto &re : uset) {
    printf("%4zu. %s, RE=%s\n", i++, re.entry->GetPath().string().c_str(),
           re.relativePath.string().c_str());
  }
}
