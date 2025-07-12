#include "Comparator.h"

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

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

void Comparator::SetLogCallback(LogCallback cb) { m_LogCb = cb; }

void Comparator::SetProgressCallback(ProgressCallback cb) { m_ProgressCb = cb; }

bool Comparator::Compare() {
  Log("Starting entries comparison...");

  Log("Entry 1 = " + m_Directory1->GetPath().string());
  if (!m_Directory1->IsValid()) {
    Log("Entry 1 is not valid");
  } else {
    Log("Entry 1 is valid");
  }

  Log("Entry 2 = " + m_Directory2->GetPath().string());
  if (!m_Directory2->IsValid()) {
    Log("Entry 2 is not valid");
  } else {
    Log("Entry 2 is valid");
  }

  Log("Counting entries");

  std::vector<Entry *> dir1Entries;
  m_Directory1->GetAllLeafEntries(dir1Entries);
  std::vector<Entry *> dir2Entries;
  m_Directory2->GetAllLeafEntries(dir2Entries);

  if (dir1Entries.size() != dir2Entries.size()) {
    size_t diff = (dir1Entries.size() > dir2Entries.size())
                      ? (dir1Entries.size() - dir2Entries.size())
                      : (dir2Entries.size() - dir1Entries.size());
    Log("Entry count mismatch, diff = " + std::to_string(diff));
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
    Log("Entry's relative path do not match");
    return false;
  } else {
    // std::cout << "Entries match" << std::endl;
    Log("Entry's relative path match");
  }

  if (!AreDirectoriesIdentical(dir1Set, dir2Set)) {
    // std::cout << "Entries not identical" << std::endl;
    return false;
  }

  return true;
}

bool Comparator::CompareEntriesName(RelativeEntrySet dir1Set,
                                    RelativeEntrySet dir2Set) {

  assert(
      dir1Set.size() == dir2Set.size() &&
      "Error: Logic inconsistency, sets for both the directory are not equal");

  for (const auto &re : dir1Set) {
    if (dir2Set.find(re) == dir2Set.end()) {
      // m_ProgressReporter.ReportPathMismatch(re.relativePath, 2);
      Log("Entry relative path mismatch, in Folder 2 for entry = " +
          re.relativePath.string());
      return false;
    }
    dir2Set.erase(re);
  }

  if (!dir2Set.empty()) {
    auto it = dir2Set.begin();
    // m_ProgressReporter.ReportPathMismatch(it->relativePath, 1);
    Log("Entry relative path mismatch, in Folder 1 for entry = " +
        it->relativePath.string());
  }
  return dir2Set.empty();
}

bool Comparator::AreDirectoriesIdentical(const RelativeEntrySet &dir1Set,
                                         const RelativeEntrySet &dir2Set) {

  const std::uintmax_t totalSize = m_Directory1->ComputeTotalSizeInbuilt();
  std::uintmax_t currentCompared = 0;

  for (const auto &relEntry1 : dir1Set) {
    if (relEntry1.entry->GetType() == EntryType::File) {
      const File *file1 = dynamic_cast<File *>(relEntry1.entry);

      const auto relEntry2 = dir2Set.find(relEntry1);
      const File *file2 = dynamic_cast<File *>(relEntry2->entry);

      // m_ProgressReporter.ReportComparingContent(relEntry1.relativePath);
      Log("Comparing entry: " + relEntry1.relativePath.string());

      if (!AreFilesIdentical(file1, file2, totalSize, currentCompared)) {
        // m_ProgressReporter.ReportContentMismatch(relEntry1.relativePath);
        Log("Not okay");
        return false;
      }
      Log("Okay");
    }
  }

  return true;
}

bool Comparator::AreFilesIdentical(const File *file1, const File *file2,
                                   const std::uintmax_t totalSize,
                                   std::uintmax_t &currentCompared) {
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

    currentCompared += bytesRead1;
    int percent = (float)currentCompared / (float)totalSize * 100;
    ReportProgress(percent);
  }

  return true;
}

void Comparator::Log(const std::string &msg) {
  if (m_LogCb) {
    m_LogCb(msg);
  }
}

void Comparator::ReportProgress(int percent) {
  if (m_ProgressCb) {
    m_ProgressCb(percent);
  }
}
