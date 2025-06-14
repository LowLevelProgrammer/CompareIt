#include "Comparator.h"
#include "ProgressStatus.h"
#include <iostream>

void ProgressCallbackFunction(const ProgressStatus &progressStatus) {
  switch (progressStatus.status) {
  case Status::NotStarted:
    break;
  case Status::InProgress: {
    Stage currentStage = progressStatus.stage.value();
    switch (currentStage) {
    case Stage::Started:
      std::cout << "Starting comparing directories:" << std::endl;
      std::cout << "Dir1: " << progressStatus.dir1 << std::endl;
      std::cout << "Dir2: " << progressStatus.dir2 << std::endl;
      break;
    case Stage::CollectingEntries:
      std::cout << "Fetching entry's metadata" << std::endl;
      break;
    case Stage::ComparingEntryCount:
      std::cout << "Comparing entry count start" << std::endl;
      break;
    case Stage::CompareEntryPathStart:
      std::cout << "Comparing entry count start" << std::endl;
      break;
    case Stage::ComparingEntryPaths:
      std::cout << progressStatus.currentFileRelPath << std::endl;
      break;
    case Stage::ComparingContentStart:
      std::cout << "Comparing entry content:" << std::endl;
      break;
    case Stage::ComparingContent:
      std::cout << "Comparing: " << progressStatus.currentFileRelPath << std::endl;
      break;
    case Stage::Finalizing:
      break;
    }
  } break;
  case Status::Done: {
    Result result = progressStatus.result.value();
    switch (result) {
    case Result::DirectoryNotValid:
      std::cout << "DirectoryNotValid" << std::endl;
      break;
    case Result::CountMismatch:
      std::cout << "CountMismatch" << std::endl;
      std::cout << "File difference number: " << progressStatus.mismatchOffset.value() << std::endl;
      break;
    case Result::EntryMismatch:
      std::cout << "EntryMismatch" << std::endl;
      std::cout << "File not matched: " << std::endl;
      std::cout << "DIR 1: "<< ( progressStatus.offendingPath1.has_value()? progressStatus.offendingPath1.value(): "null") << std::endl;
      std::cout << "DIR 2: "<< ( progressStatus.offendingPath2.has_value()? progressStatus.offendingPath2.value(): "null") << std::endl;
      break;
    case Result::ContentMismatch:
      std::cout << "ContentMismatch" << std::endl;
      std::cout << "File that isnt the same: " << progressStatus.offendingPath1.value() << std::endl;
      break;
    case Result::Identical:
      std::cout << "Dirs are identical" << std::endl;
      break;
    case Result::Unknown:
      break;
    }
  } break;
  case Status::Error:
    break;
  }
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <Folder1Path> <Folder2Path>"
              << std::endl;
    return 1;
  }

  std::filesystem::path dir1(argv[1]);
  std::filesystem::path dir2(argv[2]);
  std::cout << "Dir 1 = " << dir1 << std::endl;
  std::cout << "Dir 2 = " << dir2 << std::endl;

  Comparator comparator(ProgressCallbackFunction);
  comparator.SetDirectory1(dir1);
  comparator.SetDirectory2(dir2);
  bool areIdentical = comparator.Compare();

  std::cout << "Are folders identical: " << (areIdentical ? "Yes" : "No")
            << std::endl;
}
