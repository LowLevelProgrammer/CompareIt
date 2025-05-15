#include "Comparator.h"

#include "Utils.h"

#include <cassert>
#include <fstream>
#include <iostream>

Comparator::Comparator() {}

Comparator::~Comparator() {}

bool Comparator::SetDirectory1(std::filesystem::path directoryPath1) {
  m_Directory1 = std::make_unique<Directory>(directoryPath1);
  return m_Directory1->IsValid();
}

bool Comparator::SetDirectory2(std::filesystem::path directoryPath2) {
  m_Directory2 = std::make_unique<Directory>(directoryPath2);
  return m_Directory2->IsValid();
}

bool Comparator::Compare() {
  if (!m_Directory1->IsValid()) {
    std::cout << "Directory 1 is not valid" << std::endl;
  } else {
    std::cout << "Directory 1 is valid" << std::endl;
  }

  if (!m_Directory2->IsValid()) {
    std::cout << "Directory 2 is not valid" << std::endl;
  } else {
    std::cout << "Directory 2 is valid" << std::endl;
  }

  std::vector<Entry *> dir1Entries;
  m_Directory1->GetAllLeafEntries(dir1Entries);
  std::vector<Entry *> dir2Entries;
  m_Directory2->GetAllLeafEntries(dir2Entries);

  PrintLeafEntries(dir1Entries, "Directory 1");
  PrintLeafEntries(dir2Entries, "Directory 2");

  if (dir1Entries.size() != dir2Entries.size()) {
    return false;
  }

  std::filesystem::path baseDir1Path = m_Directory1->GetPath();
  std::filesystem::path baseDir2Path = m_Directory2->GetPath();

  std::unordered_set<RelativeEntry, RelativeEntryHasher, RelativeEntryEqual>
      dir1Set;
  std::unordered_set<RelativeEntry, RelativeEntryHasher, RelativeEntryEqual>
      dir2Set;

  for (Entry *e : dir1Entries) {
    dir1Set.emplace(e, baseDir1Path);
  }

  for (Entry *e : dir2Entries) {
    dir2Set.emplace(e, baseDir2Path);
  }

  if (!CompareEntriesName(dir1Set, dir2Set)) {
    return false;
  }

  return true;
}

bool Comparator::CompareEntriesName(
    std::unordered_set<RelativeEntry, RelativeEntryHasher, RelativeEntryEqual>
        dir1Set,
    std::unordered_set<RelativeEntry, RelativeEntryHasher, RelativeEntryEqual>
        dir2Set) {

  assert(
      dir1Set.size() == dir2Set.size() &&
      "Error: Logic inconsistency, sets for both the directory are not equal");

  for (const auto &re : dir1Set) {
    if (dir2Set.find(re) == dir2Set.end())
      return false;
    dir2Set.erase(re);
    PrintSet(dir2Set);
  }
  return dir2Set.empty();
}

bool Comparator::AreDirectoriesIdentical(const std::vector<File> &dir1Files,
                                         const std::vector<File> &dir2Files) {

  std::unordered_set<std::string> dir1AbsolutePathSet;
  std::unordered_set<std::string> dir2AbsolutePathSet;

  for (const auto &file : dir1Files) {
    dir1AbsolutePathSet.insert(file.GetPath().string());
  }

  for (const auto &file : dir2Files) {
    dir2AbsolutePathSet.insert(file.GetPath().string());
  }

  for (const auto &filePath : dir1AbsolutePathSet) {
    std::string file1 = filePath;
  }

  return false;
}

bool Comparator::AreFilesIdentical(const File &file1, const File &file2) {
  std::ifstream fileStream1(file1.GetPath(), std::ios::binary);
  std::ifstream fileStream2(file2.GetPath(), std::ios::binary);

  if (!fileStream1.is_open() || !fileStream2.is_open()) {
    std::cerr << "Error opening files.\n";
    return false;
  }

  constexpr std::size_t bufferSize = 4096;
  char buffer1[bufferSize];
  char buffer2[bufferSize];

  while (!fileStream1.eof() && !fileStream2.eof()) {
    fileStream1.read(buffer1, bufferSize);
    fileStream2.read(buffer2, bufferSize);

    std::streamsize bytesRead1 = fileStream1.gcount();
    std::streamsize bytesRead2 = fileStream2.gcount();

    if (bytesRead1 != bytesRead2 ||
        std::memcmp(buffer1, buffer2, bytesRead1) != 0) {
      return false;
    }
  }

  return true;
}
