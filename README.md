# A pricing library for european and american options

## Overview
A variety of methods for solving european and american option price, with arbitrary payoff functions, are implemented here:
* Monte Carlo
  * Least Square Monte Carlo for american option [2]
* Finite difference methods on solving Black-Scholes PDE:
  * Explicit
  * Implicit
  * Crank Nicolson
* Binomial Tree

## Prerequisites
C++ Compiler: Apple Clang 14.0.0\
Make: GNU Make 3.81

## Building the project
Clone the repo:
```
git clone https://github.com/malccad/pricing-library
```
Navigate to the project directory:
```
cd pricing-library
```
Compile the project: Use the make command to compile the source code. This will use the provided Makefile to manage the build process.
```
make
```
This will generate the executable in the ```bin``` directory.

## Usage
After building the project, you can run the executable as follows:
* ```bin/finite_difference.out``` or
* ```bin/monte_carlo.out``` or
* ```bin/binomial.out```,
depending on the pricing method that you want to choose.

## Parameters
The user needs to enter:

1. Parameters for the payoff function.
2. Type of payoff function (Other than the standard call and put payoffs, we have also implemented some binary and power options.)
3. Expiry
4. Whether early execution is allowed (european vs american)
5. Interest rate
6. Dividend rate
7. Volatility
8. Initial price of the asset
9. Parameters for each solver:
   * finite difference methods:
        the number of asset steps, the number of time steps and the upper bound for the asset price to set up the mesh (lower bound for asset price is set as $0$). It is recommended to set the upper bound to be $3$ to $4$ times the strike for call and put options.
   * Binomial pricing: 
        the number of time steps to determine the size of the binomial tree.

   * Monte Carlo:
        the number of asset paths sampled. When pricing american options, the user needs to enter the number of time steps, since we need to generate the whole path, instead of just one big step as in the case of pricing an european option. The user will also need to provide the number of basis functions used for least square Monte Carlo when pricing an american option.

## Example
| Parameters                         |                |
|------------------------------------|----------------|
| Expiry                             | 1              |
| PayOff                             | power_put      |
| Option type                        | american       |
| strike                             | 100            |
| Volatility                         | 0.2            |
| Interest rate                      | 0.05           |
| Dividend rate                      | 0.02           |
| Initial asset price                | 120            |
| # Least square Monte Carlo paths   | 100000         |
| # basis functions (LS Monte Carlo) | 3              |
| # Time steps (LS Monte Carlo)      | 100            |
| # Finite difference asset steps    | 400            |
| # Finite difference time steps     | 16000          |
| Finite difference upper asset limit| 400            |
| # binomial time steps              | 1000           |


| Results                 |          |
|-------------------------|----------|
| Least square Monte Carlo| 23.3309  |
| Explicit                | 23.4067  |
| Implicit                | 23.4055  |
| Crank Nicolson          | 23.4061  |
| Binomial                | 23.402   |

The option prices obtained from the finite difference methods are very close to one another.

## Implementation details
### Monte Carlo
### Basis functions for Least square Monte Carlo
The method of least square Monte Carlo [2] involves, for each time step, a model that predicts the continuation value given the current asset price that is in the money. This model is of the form:
$$
\sum_{j=0}^k a_j L_j(X) + b, \quad a_j, b \in \mathbb{R}
$$
where $L_j$ are the basis functions; $X$ is the underlying asset price; the coefficients $a_j$'s and $b$ are learned via minimizing the least square error, i.e. linear regression. We used the weighted Laguerre functions as basis functions, as suggested in [2]:
$$
L_n(X) = e^{-X/2}\cdot \frac{e^X}{n!}\cdot \frac{d^n}{dX^n}(X^n e^{-X}).
$$
We found that this can easily introduce rounding error, thanks to the $e^{-X/2}$ term. (For example, $L_0(X)=e^{-X/2}$. If the asset price $X=100$, $L_0(X)$ is an extremely small number.) As such, we used a min-max scaler to scale $X$ to $[0,1]$ before applying the basis functions. We found that the pricer behaves a lot more stable after this change.

### Only sample final price for Monte Carlo (European option)
When pricing a European option, we only care about the distribution of the final asset price. Thus, we sample only the final price of the asset, instead of the entire path for each run.

### Low discrepancy sequence for (Least square) Monte Carlo
To ensure a more even coverage, we used Halton sequence, combined with Box Muller transform, to sample from a Gaussian distribution.

### Finite difference methods
### Boundary conditions
On the boundary condition at asset price $=0$, we assume that

$$\frac{\partial V}{\partial t} (0,t) - rV(0,t) = 0$$

where we denote the option price by $V$.

On the boundary condition at the upper limit, we assume that the second derivative vanishes, i.e.

$$\frac{\partial^2 V}{\partial t^2}\rightarrow 0 \quad\text{as}\quad t\rightarrow \infty.$$

### Linear interpolation
Finite difference methods compute the option price when asset price lies on the grid points. Given an initial asset price, we use the nearest two points on the grid to deduce the option price via linear interpolation.
### Stability for explicit method
We have included a stability check for explicit method - the solution is stable if
$\partial t\cdot \sigma^2 I^2\leq 1$
where $I$ is the number of asset steps.

---



### Assumptions
* Fixed interest rate and volatility
* The asset pays dividend continously at a fixed rate.
* Asset price follows geometric Brownian motion.

## Reference
1. Paul Wilmott on Quantitative Finance (Chapter 77, 78, 80, 81)
2. F. Longstaff, E. Schwatz. Valuing American Options by Simulation: A Simple Least-Squares Approach. The Review of Financial Studies, Volume 14, Issue 1, January 2001, Pages 113–147,
