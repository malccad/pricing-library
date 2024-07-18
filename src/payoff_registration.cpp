#include "../include/payoff_helper.h"
#include "../include/payoff.h"
namespace {
    PayOffHelper<PayOffCall> RegisterCall("call");
    PayOffHelper<PayOffPut> RegisterPut("put");
    PayOffHelper<PayOffDoubleDigital> RegisterDoubleDigital("double_digital");
}