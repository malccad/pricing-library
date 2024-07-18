## Introduction
A variety of methods for solving european option price are implemented here:
* Finite difference methods on solving Black-Scholes PDE:
  * Explicit
  * Implicit
  * Crank Nicolson
* Binomial Tree
* Monte Carlo
## How to use
The user needs to enter:

1. Parameters for the payoff function.
2. Expiry
3. Interest rate
4. Volatility
5. Initial price of the asset
6. Parameters for each solver:
   * finite difference methods:
        the number of asset steps, the number of time steps and the upper bound for the asset price to set up the mesh (lower bound for asset price is set as $0$). It is recommended to set the upper bound to be $3$ to $4$ times the strike for call and put options.
   * Binomial pricing: 
        the number of time steps to determine the size of the binomial tree.

   * Monte Carlo:
        the number of asset paths sampled.
## Example
| Parameters            |                |
|-----------------------|----------------|
| Expiry                | 1              |
| Option                | double_digital |
| Lower strike          | 80             |
| Upper strike          | 110            |
| Volatility            | 0.2            |
| Interest rate         | 0.05           |
| Initial asset price   | 100            |
| # asset steps         | 400            |
| # time steps          | 8000           |
| Upper asset limit     | 400            |
| # binomial time steps | 10000          |
| # Monte Carlo paths   | 2000000        |

| Results        |          |
|----------------|----------|
| Explicit       | 0.499101 |
| Implicit       | 0.49913  |
| Crank Nicolson | 0.499115 |
| Binomial       | 0.496237 |
| Monte Carlo    | 0.499569 |

The option price obtained from binomial tree is off by a bit, compared with others.

## Implementation details
### Boundary conditions for finite difference methods
On the boundary condition at asset price $=0$, we assume that
$$ \frac{\partial V}{\partial t} (0,t) - rV(0,t) = 0$$
where we denote the option price by $V$.

On the boundary condition at the upper limit, we assume that the second derivative vanishes, i.e.
$$ \frac{\partial^2 V}{\partial t^2}\rightarrow 0 \quad\text{as}\quad t\rightarrow \infty.$$

### Linear interpolation for finite difference methods
Finite difference methods compute the option price for asset price that lies on the grid points. Given an initial asset price, we use the nearest two points on the grid for linear interpolation to deduce the option price.
### Stability for explicit method
We have included a stability check for explicit method - the solution is stable if
$$\partial t\cdot \sigma^2 I^2\leq 1$$
where $I$ is the number of asset steps.

### Only sample final price for Monte Carlo
Since we are pricing a European option, we sample only the final price of the asset, instead of the entire path for each run.

### Low discrepancy sequence for Monte Carlo
To ensure a more even coverage, we used Halton sequence, combined with Box Muller transform, to sample from a Gaussian distribution.
### Assumptions
* Fixed interest rate and volatility
* Asset price follows geometric Brownian motion.

## Reference
* Paul Wilmott on Quantitative Finance (Chapter 77, 78, 80, 81)