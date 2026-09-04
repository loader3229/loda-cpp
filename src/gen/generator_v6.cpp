#include "gen/generator_v6.hpp"

#include "lang/parser.hpp"
#include "lang/program_util.hpp"
#include "seq/managed_seq.hpp"
#include "sys/log.hpp"

GeneratorV6::GeneratorV6(const Config &config, const Stats &stats)
    : Generator(config, stats),
      scheduler(5),  // 1 minute; magic number
      mutator(stats, config.mutation_rate) {
  // get first program template
  nextProgram();
}

Program GeneratorV6::generateProgram() {
  if (scheduler.isTargetReached()) {
    scheduler.reset();
    nextProgram();
  }
  Program result(program);
  mutator.mutateRandom(result);
  return result;
}

void GeneratorV6::nextProgram() {
  Parser parser;
  for (int64_t i = 0; i < 100; i++) {
    const auto id = random_program_ids.get();
    const std::string path = ProgramUtil::getProgramPath(id);
    try {
      program = parser.parse(path);
      ProgramUtil::removeOps(program, Operation::Type::NOP);
      if(program.ops.size() < 12 || ProgramUtil::hasRegionOperation(program)
       || ProgramUtil::hasIndirectOperand(program)
       || ProgramUtil::hasOp(program, Operation::Type::SEQ)
       || ProgramUtil::hasOp(program, Operation::Type::LPB)){
        i--; continue;
       } 
      // Log::get().info("Loaded template: " + path);
      return;
    } catch (std::exception &) {
      Log::get().warn("Cannot load program " + path);
    }
  }
  Log::get().error("Error loading template for generator v6", true);
}

std::pair<Operation, double> GeneratorV6::generateOperation() {
  throw std::runtime_error("unsupported operation");
}

bool GeneratorV6::supportsRestart() const { return true; }

bool GeneratorV6::isFinished() const { return false; };
