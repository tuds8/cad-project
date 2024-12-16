# OMNeT++ LTE Scheduling Simulation

This project simulates a simplified LTE-like network scenario using the OMNeT++ discrete event simulator. The simulation models multiple users, each generating packets, buffering them in a queue, and transmitting them to a sink via a limited number of radio resources (RBs). A scheduler allocates RBs to users based on a Proportional Fair (PF)-like metric, optionally considering different user priority weights.

## Overview

### Components

- **User**: Each user consists of a **Source** (traffic generator) and a **Queue** module (`myQ`) that buffers packets before transmission.
- **Scheduler**: The central entity that allocates radio resources (RBs) to users each scheduling cycle. It computes a PF-like metric that considers:
  - Radio link quality for each user and RB.
  - Time elapsed since the user was last served.
  - User priority weight.
  
  Users with higher PF metrics receive more RBs.

- **Sink**: The sink module receives packets from users, computes their delay (lifetime), records statistics, and discards them.

### Key Features

- **Proportional Fair Scheduling**: Each RB is assigned to the user with the highest PF metric for that RB.
- **Weighted Users**: Users can have different weight factors (e.g., HP users get higher weights, LP users get lower weights). This influences their PF metric and thus how frequently and how many RBs they receive.
- **Varying Network Load**: The network load can be easily adjusted via parameters in the `omnetpp.ini` file. This allows for performance evaluation (mean packet delay) under different load conditions.
- **Per-Category Statistics**: Packets are tagged with a user ID, and the sink categorizes them into High Priority (HP), Medium Priority (MP), and Low Priority (LP) classes. Separate signals and statistics are recorded for each category.

## Directory Structure

- `Source.cc/h`: Implements the traffic generation logic. Each user’s source creates packets and sends them towards the queue.
- `myQ.cc/h`: Implements the queue that buffers packets until instructed by the scheduler to send them.
- `Scheduler.cc/h`: Implements the scheduling algorithm, computing per-RB metrics and allocating resources to users.
- `Sink.cc/h`: Receives packets, calculates their lifetime, and records lifetime statistics for all and per-category (HP, MP, LP) users.
- `*.ned`: NED files that define the module structure (e.g., `RadioSch2.ned`, `Scheduler.ned`, `Sink.ned`, `Source.ned`, `user.ned`, `myQ.ned`).
- `omnetpp.ini`: Configuration file specifying parameters like number of users, network load, scheduling period, number of RBs, and traffic patterns.

## Configuring Parameters

### Number of Users (`usersCount`)
- Set in `omnetpp.ini`.

### Network Load (`netwload`)
- Adjust this parameter in `omnetpp.ini` to run multiple scenarios (e.g., `0.3`, `0.5`, `0.7`, `0.9`).

### Weights (`W[i]`)
- User weights are hardcoded in `Scheduler.cc` for now. 
- If you have exactly 10 users, the weights are as assigned in the code:
  - **2 HP users:** `W=6` or `8`
  - **5 MP users:** `W=2`
  - **3 LP users:** `W=1`

## Output and Analysis

### After Running the Simulation
- OMNeT++ generates result files (`.sca` and `.vec`).
- Use the **Analysis Tool** in the OMNeT++ IDE to plot and analyze results.

### Key Metrics
- **`lifetime (overall):`** Average delay of all packets.
- **`hpLifetime, mpLifetime, lpLifetime:`** Mean delay metrics for each user category, allowing you to compare performance under different loads and weight configurations.

## Example Workflows

### Compare Mean Delay vs. Network Load
1. Run simulations at loads: `30%`, `50%`, `70%`, `90%`.
2. Analyze:
   - `hpLifetime:mean`
   - `mpLifetime:mean`
   - `lpLifetime:mean` for each scenario.
3. Plot **mean delay** (`y-axis`) vs. **network load** (`x-axis`) to see how different priority groups fare under increasing load.

### Impact of Weights
1. Adjust weights in `Scheduler.cc`.
2. Run simulations and compare:
   - How the allocation changes.
   - How the **HP**, **MP**, and **LP** mean delays are affected by the new weights.
