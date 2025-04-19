# Continuous Glider Simulation  
**Name:** Kellen Knop  
**Date:** April 16, 2025  

This project simulates a **continuous glider** using color animation in C++. The main file is: `CAAnimator.cpp`.

## Overview

The program simulates a **cellular automaton** (CA) in which each cell's state is represented by a color gradient. The cells evolve based on a **Fuzzy Game of Life** update rule. This rule builds on the classic Conway's Game of Life but with adjustments allowing for a smoother transition of cell states, instead of simple binary life/death behavior.

A continuous glider pattern is used as the initial seed, which moves diagonally across the grid, demonstrating the evolution of living cells.

## CA Pattern: Fuzzy Game of Life

This simulation demonstrates a variation of **Conway's Game of Life** called **Fuzzy Game of Life**. The grid is populated with cells that have a continuous range of states from 0 (dead) to 1 (fully alive). The cell state is updated based on the number of neighbors:

- **Alive cell**: A cell stays alive if it has 2 or 3 neighbors. If it has more or fewer, it decays (its state decreases). The decay is gradual, making the cell transition to death more smoothly over time.
- **Dead cell**: A dead cell becomes alive if it has exactly 3 live neighbors. Otherwise, its state decreases gradually.

This creates a more dynamic and colorful simulation where the states of the cells are not binary but rather a continuous range, giving the simulation a "fuzzy" behavior.

## Update Rule

The update rule in the Fuzzy Game of Life is as follows:

- **For living cells**:
  - If a cell has 2 or 3 live neighbors, its state increases by 0.1 (to a maximum of 1.0).
  - Otherwise, its state decays by half.
  
- **For dead cells**:
  - If a cell has exactly 3 live neighbors, it becomes alive (state = 1.0).
  - Otherwise, it decays by a smaller factor (multiplying its state by 0.96).

Additionally, the simulation applies a smoothing effect, ensuring that cells never reach an extreme state too quickly. Any cell with a state below 0.01 is considered dead.

The result is a colorful, evolving pattern of cells that simulate movement across the grid.

## Technologies Used

- **C++**: The core programming language used to implement the simulation.
- **emp/web**: A C++ web library used for the visualization and interactive controls (e.g., step button, toggle button).
- **GitHub Copilot & Gemini**: Used for code assistance, debugging, and solving issues during development.

## Sources Consulted

- **Conway's Game of Life**: The foundational concept for this simulation, which served as the basis for the fuzzy logic update rule.
- **Wikipedia - Conway's Game of Life**: [Game of Life Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) for detailed rules and history.