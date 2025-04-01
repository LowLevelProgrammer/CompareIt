#include "Comparator.h"

Comparator::Comparator() {}

Comparator::~Comparator() {}

void Comparator::SetDirectory1(std::filesystem::path directoryPath1) {
  m_Directory1 = std::make_unique<Directory>(directoryPath1);
}

void Comparator::SetDirectory2(std::filesystem::path directoryPath2) {
  m_Directory2 = std::make_unique<Directory>(directoryPath2);
}

void Comparator::SetComparisonMode(Mode mode) { m_ComparisonMode = mode; }

bool Comparator::Compare() {
  return false;
}

bool Comparator::CompareEntriesName() {
  
  return false;
}
