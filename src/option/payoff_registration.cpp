#include "../../include/option/payoff_helper.h"
#include "../../include/option/payoff.h"
namespace {
    PayOffHelper<PayOffCall> RegisterCall("call", std::vector<std::string> {"strike"});
    PayOffHelper<PayOffPut> RegisterPut("put", std::vector<std::string> {"strike"});
    PayOffHelper<PayOffDoubleDigital> RegisterDoubleDigital("double_digital", std::vector<std::string> {"lowerStrike", "upperStrike"});
    PayOffHelper<PayOffCashOrNthCall> RegisterCashOrNthCall("cash_or_nth_call", std::vector<std::string> {"strike"});
    PayOffHelper<PayOffCashOrNthPut> RegisterCashOrNthPut("cash_or_nth_put", std::vector<std::string> {"strike"});
    PayOffHelper<PayOffAssetOrNthCall> RegisterAssetOrNthCall("asset_or_nth_call", std::vector<std::string> {"strike"});
    PayOffHelper<PayOffAssetOrNthPut> RegisterAssetOrNthPut("asset_or_nth_put", std::vector<std::string> {"strike"});
    PayOffHelper<PayOffPowerCall> RegisterPowerCall("power_call", std::vector<std::string> {"strike", "power"});
    PayOffHelper<PayOffPowerPut> RegisterPowerPut("power_put", std::vector<std::string> {"strike", "power"});
}