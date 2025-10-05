#pragma once

#include <map>

#include "base/uid.hpp"
#include "lang/program.hpp"
#include "mine/stats.hpp"

class SequenceProgram {
 public:
  static std::pair<Program, UID> getProgramAndSeqId(
      const std::string& id_or_path);

  static size_t getTransitiveProgramHash(const Program& p);

  static size_t getNumCheckTerms(bool full_check);

  static size_t getNumRequiredTerms(const Program& p);

  static size_t getNumMinimizationTerms(const Program& p);

  static UIDSet collectLatestProgramIds(size_t max_commits,
                                        size_t max_added_programs,
                                        size_t max_modified_programs);

  static void commitAddedPrograms(size_t min_commit_count = 5);

  static void commitUpdateAndDeletedPrograms(
      Stats* stats, const std::unordered_set<UID>* full_check_list);
};
