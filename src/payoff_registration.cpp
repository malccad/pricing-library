#include "../include/payoff_helper.h"
#include "../include/payoff.h"
namespace {
    PayOffHelper<PayOffCall> RegisterCall("call", std::vector<std::string> {"strike"});
    PayOffHelper<PayOffPut> RegisterPut("put", std::vector<std::string> {"strike"});
    PayOffHelper<PayOffDoubleDigital> RegisterDoubleDigital("double_digital", std::vector<std::string> {"lowerStrike", "upperStrike"});
}