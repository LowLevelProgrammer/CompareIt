#include "ProgressReporter.h"
#include "ProgressStatus.h"

ProgressReporter::ProgressReporter(ProgressCallback callback)
    : m_Callback(callback) {}

ProgressReporter::~ProgressReporter() {}

void ProgressReporter::ReportStarted(const std::filesystem::path &dir1,
                                     const std::filesystem::path &dir2) {
  m_Status.status = Status::InProgress;
  m_Status.stage = Stage::Started;

  m_Status.dir1 = dir1;
  m_Status.dir2 = dir2;
  m_Callback(m_Status);
}

void ProgressReporter::ReportNotValidEntry1(const std::filesystem::path &dir) {
  m_Status.status = Status::Done;
  m_Status.result = Result::DirectoryNotValid;
  m_Callback(m_Status);
}
void ProgressReporter::ReportNotValidEntry2(const std::filesystem::path &dir) {
  m_Status.status = Status::Done;
  m_Status.result = Result::DirectoryNotValid;
  m_Callback(m_Status);
}

void ProgressReporter::ReportCountingEntriesStart() {
  m_Status.stage = Stage::CollectingEntries;
  m_Callback(m_Status);
}
void ProgressReporter::ReportDir1EntryCount(size_t count) {
  m_Status.dir1EntryCount = count;
  m_Callback(m_Status);
}
void ProgressReporter::ReportDir2EntryCount(size_t count) {
  m_Status.dir2EntryCount = count;
  m_Callback(m_Status);
}
void ProgressReporter::ReportCountMismatch(size_t difference) {
  m_Status.status = Status::Done;
  m_Status.result = Result::CountMismatch;
  m_Status.mismatchOffset = difference;
  m_Callback(m_Status);
}

void ProgressReporter::ReportComparingPathsStart() {
  m_Status.stage = Stage::CompareEntryPathStart;
  m_Callback(m_Status);
}
void ProgressReporter::ReportComparingFilePath(
    const std::filesystem::path &relPath) {
  m_Status.stage = Stage::ComparingEntryPaths;
  m_Status.currentFileRelPath = relPath;
  m_Callback(m_Status);
}
void ProgressReporter::ReportPathMismatch(
    const std::filesystem::path &offendingPath, int dirNumber) {
  m_Status.status = Status::Done;
  m_Status.result = Result::EntryMismatch;

  if (dirNumber == 1) {
    m_Status.offendingPath1 = offendingPath;
  } else if (dirNumber == 2) {
    m_Status.offendingPath2 = offendingPath;
  }
  m_Callback(m_Status);
}

void ProgressReporter::ReportComparingContentStart() {
  m_Status.stage = Stage::ComparingContentStart;
  m_Callback(m_Status);
}
void ProgressReporter::ReportComparingContent(
    const std::filesystem::path &relPath) {
  m_Status.stage = Stage::ComparingContent;
  m_Status.currentFileRelPath = relPath;
  m_Callback(m_Status);
}
// void ProgressReporter::ReportComparingFileProgress(
//     const std::filesystem::path &relPath, size_t bytesCompared) {}
void ProgressReporter::ReportContentMismatch(
    const std::filesystem::path &offendingPath) {
  m_Status.status = Status::Done;
  m_Status.result = Result::ContentMismatch;
  m_Status.offendingPath1 = offendingPath;
  m_Callback(m_Status);
}

void ProgressReporter::ReportIdentical() {
  m_Status.status = Status::Done;
  m_Status.result = Result::Identical;
  m_Callback(m_Status);
}
void ProgressReporter::ReportError() {}
