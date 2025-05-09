# Disk Scheduling Simulator 🚀

Welcome to the **Disk Scheduling Simulator**—an interactive C-based tool that visualizes how operating systems schedule I/O requests on disk heads! Whether you’re a student, a developer, or just curious, explore FCFS, SCAN, and C-SCAN algorithms in action, generate random request sequences, and analyze head movements with ease. Let’s spin those platters! 🌪️

## ✨ Key Features

- **Scheduling Algorithms** 🛠️

  - **First-Come, First-Serve (FCFS):** Handles requests in arrival order—simple and fair.
  - **SCAN (Elevator):** Moves toward one end (0) servicing along the way, then reverses.
  - **C-SCAN (Circular SCAN):** Scans to the end, jumps back to the start, and continues—ensures uniform wait times.

- **Random Request Generation** 🎲
  Optionally generate a random sequence of I/O requests within the range `0..max_cylinder`.

- **Custom Input** ✍️
  Manually enter each request to simulate specific workloads.

- **Detailed Movement Log** 📝
  Step through each head movement, view individual distances, and compute total & average travel.

- **Interactive Menu Loop** 🔄
  Choose algorithms on the fly: FCFS, SCAN, C-SCAN, or run all sequentially.

## 🛠️ Compilation Instructions

### Windows (MinGW or Visual Studio)

```bash
gcc -o disk_sched.exe disk_scheduling_simulator.c
```

### Linux & macOS

```bash
gcc -o disk_sched disk_scheduling_simulator.c
```

<div style="background: #e1f5fe; border-left: 6px solid #0288d1; padding: 15px; border-radius: 5px; margin: 15px 0; box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);">
  <strong>Pro Tip:</strong> Ensure you compile with the C99 or later standard if you encounter any warnings: <code>-std=c99</code> works great!
</div>

## 🚀 Running the Simulator

1. **Launch with parameters** (maximum cylinder and request count):

   ```bash
   ./disk_sched 4999 10     # max_index=4999, n_requests=10
   ```

2. **Or start interactively** and enter prompts:

   ```bash
   ./disk_sched
   Enter maximum cylinder index: 4999
   Enter number of I/O requests: 10
   Enter initial head position (0..4999): 2500
   Generate random requests? (y/n): y
   ```

3. **Use the menu** to select algorithms:

   ```text
   Menu:
     1. FCFS
     2. SCAN
     3. C-SCAN
     4. All
     0. Exit
   Choose: 4
   ```

## 📊 Example Session

```text
Disk Scheduling Simulator
Enter maximum cylinder index (e.g. 4999): 4999
Enter number of I/O requests: 5
Enter initial head position (0..4999): 215
Generate random requests? (y/n): y
Generated requests:
3467 123 4567 2345 89

--- FCFS ---
Initial head position: 215
 215 -> 3467 : movement = 3252
3467 -> 123  : movement = 3344
 123 -> 4567 : movement = 4444
4567 -> 2345 : movement = 2222
2345 ->  89  : movement = 2256
-----------------------------------------------------------------
    Total head movement = 15518
    Average movement per request = 3103.60

--- SCAN (toward 0 first) ---
[...]

--- C-SCAN (toward max then wrap) ---
[...]

Exiting.
```

## 🎯 Team Members

- **Eng. Youssif Seliem** — Supervisor | Operating Systems Lecturer
- **Ahmed Hussien El Sayed** — Project Lead | Web & C Developer
- **Eslam Sa3d Gom3a Mohamed** — Python & Documentation Specialist
- **Asmaa Emad Abd-El3lem** — Developer | Tester
- **Eman Ayman Mabrouk** — Documentation Specialist
- **Mostafa Mohamed Elswaf** — Tester | Documentation Specialist

## 👀 What’s Next?

- **Add LOOK & C-LOOK algorithms** for more nuanced scanning.
- **Track request waiting times** and generate throughput stats.
- **Modularize code** into separate source files for maintenance.
- **Graphical UI** to animate head movements.

Dive in, experiment with different request patterns, and master disk scheduling strategies! 🌟
