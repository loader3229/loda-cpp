#include "mine/distribution.hpp"

#include "lang/program_util.hpp"
#include "sys/util.hpp"
#include "math/semantics.hpp"

std::discrete_distribution<> uniformDist(size_t size) {
  std::vector<double> p(size, 100.0);
  return std::discrete_distribution<>(p.begin(), p.end());
}

std::discrete_distribution<> constantsDist(const std::vector<Number> &constants,
                                           const Stats &stats) {
  std::vector<double> p(constants.size());
  for (size_t i = 0; i < constants.size(); i++) {
    Number tmp = Semantics::gcd(constants[i], 0);
    tmp = Semantics::trn(25, tmp);
    tmp = Semantics::mul(tmp, 1000);
    tmp = Semantics::max(tmp, 1);
    p[i] = tmp.asInt();
  }
  return std::discrete_distribution<>(p.begin(), p.end());
}

std::discrete_distribution<> operationDist(
    const Stats &stats, const std::vector<Operation::Type> &operation_types) {
  std::vector<double> p(operation_types.size());
  for (size_t i = 0; i < operation_types.size(); i++) {
    int64_t rate =
        stats.num_ops_per_type.at(static_cast<size_t>(operation_types[i]));
    rate = std::max<int64_t>(1000000 / (rate + 1000), 1);
    p[i] = rate;
    if (ProgramUtil::isWritingRegion(operation_types[i]) || operation_types[i] == Operation::Type::SEQ || operation_types[i] == Operation::Type::LPB || operation_types[i] == Operation::Type::LPE) {
      p[i] = 0;
    }
  }
  return std::discrete_distribution<>(p.begin(), p.end());
}
