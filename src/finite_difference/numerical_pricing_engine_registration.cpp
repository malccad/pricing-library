#include "../../include/finite_difference/numerical_pricing_engine_helper.h"
#include "../../include/finite_difference/explicit_numerical.h"
#include "../../include/finite_difference/implicit_vanilla.h"
#include "../../include/finite_difference/crank_nicolson.h"

namespace{
    NumericalPricingEngineHelper<Explicit> RegisterExplicit("explicit");
    NumericalPricingEngineHelper<Implicit> RegisterImplicit("implicit");
    NumericalPricingEngineHelper<CrankNicolson> RegisterCrankNicolson("crank_nicolson");
}