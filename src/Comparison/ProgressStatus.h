#pragma once

#include <filesystem>
#include <functional>
#include <optional>
#include <string>

enum class Status { NotStarted, InProgress, Done, Error };

enum class Result {
  Unknown,
  Identical,
  DirectoryNotValid,
  CountMismatch,
  EntryMismatch,
  ContentMismatch
};

enum class Stage {
  Started,
  // ValidatingDirectories,
  CollectingEntries,
  ComparingEntryCount,
  CompareEntryPathStart,
  ComparingContentStart,
  ComparingEntryPaths,
  ComparingContent,
  Finalizing
};

struct ProgressStatus {
  Status status = Status::NotStarted;
  std::optional<Stage> stage;
  std::optional<Result> result;
  std::filesystem::path dir1;
  std::filesystem::path dir2;
  size_t dir1EntryCount;
  size_t dir2EntryCount;
  std::filesystem::path currentFileRelPath;

  // Progress tracking
  size_t totalFiles = 0;
  size_t filesCompared = 0;
  size_t totalBytes = 0;
  size_t bytesCompared = 0;
  std::string currentFile;

  // Optional additional details for failure context
  std::optional<std::string> message;

  // For count mismatch
  std::optional<size_t> dir1Size;
  std::optional<size_t> dir2Size;

  // For entries mismatch
  std::optional<std::filesystem::path> offendingPath1;
  std::optional<std::filesystem::path> offendingPath2;

  // For content mismatch
  std::optional<size_t> mismatchOffset;

  float Progress() const {
    return totalFiles == 0 ? 0.0f
                           : static_cast<float>(filesCompared) / totalFiles;
  }
};

using ProgressCallback = std::function<void(const ProgressStatus &)>;
