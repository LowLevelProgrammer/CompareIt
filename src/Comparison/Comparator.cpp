#include "Comparator.h"

#include "ProgressStatus.h"
#include "Utils.h"

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdlib.h>

Comparator::Comparator(ProgressCallback callback)
    : m_ProgressReporter(callback) {}

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
  m_ProgressReporter.ReportStarted(m_Directory1->GetPath(),
                                   m_Directory2->GetPath());
  if (!m_Directory1->IsValid()) {
    // std::cout << "Directory 1 is not valid" << std::endl;
    m_ProgressReporter.ReportNotValidEntry1(m_Directory1->GetPath());
  } else {
    std::cout << "Directory 1 is valid" << std::endl;
  }

  if (!m_Directory2->IsValid()) {
    // std::cout << "Directory 2 is not valid" << std::endl;
    m_ProgressReporter.ReportNotValidEntry2(m_Directory2->GetPath());
  } else {
    std::cout << "Directory 2 is valid" << std::endl;
  }

  m_ProgressReporter.ReportCountingEntriesStart();

  std::vector<Entry *> dir1Entries;
  m_Directory1->GetAllLeafEntries(dir1Entries);
  std::vector<Entry *> dir2Entries;
  m_Directory2->GetAllLeafEntries(dir2Entries);

  // PrintLeafEntries(dir1Entries, "Directory 1");
  // PrintLeafEntries(dir2Entries, "Directory 2");

  if (dir1Entries.size() != dir2Entries.size()) {
    // std::cout << "Entries count mismatch" << std::endl;
    size_t diff = _abs64(dir1Entries.size() - dir2Entries.size());
    m_ProgressReporter.ReportCountMismatch(diff);
    return false;
  }

  std::filesystem::path baseDir1Path = m_Directory1->GetPath();
  std::filesystem::path baseDir2Path = m_Directory2->GetPath();

  RelativeEntrySet dir1Set;
  RelativeEntrySet dir2Set;

  for (Entry *e : dir1Entries) {
    dir1Set.emplace(e, baseDir1Path);
  }

  for (Entry *e : dir2Entries) {
    dir2Set.emplace(e, baseDir2Path);
  }

  if (!CompareEntriesName(dir1Set, dir2Set)) {
    std::cout << "Entries do not match" << std::endl;
    return false;
  } else {
    std::cout << "Entries match" << std::endl;
  }

  if (!AreDirectoriesIdentical(dir1Set, dir2Set)) {
    // std::cout << "Entries not identical" << std::endl;
    return false;
  }

  m_ProgressReporter.ReportIdentical();
  return true;
}

bool Comparator::CompareEntriesName(RelativeEntrySet dir1Set,
                                    RelativeEntrySet dir2Set) {

  assert(
      dir1Set.size() == dir2Set.size() &&
      "Error: Logic inconsistency, sets for both the directory are not equal");

  for (const auto &re : dir1Set) {
    if (dir2Set.find(re) == dir2Set.end()) {
      m_ProgressReporter.ReportPathMismatch(re.relativePath, 2);
      return false;
    }
    dir2Set.erase(re);
  }

  if (!dir2Set.empty()) {
    auto it = dir2Set.begin();
    m_ProgressReporter.ReportPathMismatch(it->relativePath, 1);
  }
  return dir2Set.empty();
}

bool Comparator::AreDirectoriesIdentical(const RelativeEntrySet &dir1Set,
                                         const RelativeEntrySet &dir2Set) {

  for (const auto &relEntry1 : dir1Set) {
    if (relEntry1.entry->GetType() == EntryType::File) {
      const File *file1 = dynamic_cast<File *>(relEntry1.entry);

      const auto relEntry2 = dir2Set.find(relEntry1);
      const File *file2 = dynamic_cast<File *>(relEntry2->entry);

      m_ProgressReporter.ReportComparingContent(relEntry1.relativePath);

      if (!AreFilesIdentical(file1, file2)) {
        m_ProgressReporter.ReportContentMismatch(relEntry1.relativePath);
        return false;
      }
    }
  }

  return true;
}

bool Comparator::AreFilesIdentical(const File *file1, const File *file2) {
  std::ifstream fileStream1(file1->GetPath(), std::ios::binary);
  std::ifstream fileStream2(file2->GetPath(), std::ios::binary);

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
