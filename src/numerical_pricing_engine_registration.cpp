#include "../include/numerical_pricing_engine_helper.h"
#include "../include/explicit_numerical.h"
#include "../include/implicit_vanilla.h"
#include "../include/crank_nicolson.h"

namespace{
    NumericalPricingEngineHelper<Explicit> RegisterExplicit("explicit");
    NumericalPricingEngineHelper<Implicit> RegisterImplicit("implicit");
    NumericalPricingEngineHelper<CrankNicolson> RegisterCrankNicolson("crank_nicolson");
}