### Full Steps to Run the Code:

#### 1. Download the Project:
- Open the link and download the project from GitHub.
- Alternatively, use the following command in your terminal:
  ```bash
  git clone https://github.com/yossef-ashraf/FIFO-Served-Scheduling.git
  ```

#### 2. Navigate to the Project Folder:
- After downloading, go to the project directory:
  ```bash
  cd FIFO-Served-Scheduling
  ```

#### 3. Locate the Main Code File:
- In this repository, the main file is `FIFO.c`. This is the file that contains the code.

#### 4. Compile the Code:
- Use the following command to compile the code:
  ```bash
  gcc FIFO.c -o FIFO
  ```
  - This command compiles the code and creates an executable file named `FIFO`.

#### 5. Run the Program:
- After compiling, run the program using:
  ```bash
  ./FIFO
  ```

---

### Explanation of the Code in `FIFO.c`:

#### 1. Defining Processes (Tasks):
- The code starts by defining the number of processes and their data:
  ```c
  int num_processes = 5; // Number of processes
  int arrival_time[] = {0, 2, 4, 6, 8}; // Arrival times
  int burst_time[] = {3, 5, 2, 4, 1}; // Burst times
  ```
  - Here, we have 5 processes with specific arrival and burst times.

#### 2. Calculating Waiting and Turnaround Times:
- The waiting time (`waiting_time`) and turnaround time (`turnaround_time`) are calculated for each process:
  ```c
  int waiting_time[5], turnaround_time[5];
  waiting_time[0] = 0; // The first process has no waiting time
  for (int i = 1; i < num_processes; i++) {
      waiting_time[i] = burst_time[i-1] + waiting_time[i-1];
  }
  for (int i = 0; i < num_processes; i++) {
      turnaround_time[i] = burst_time[i] + waiting_time[i];
  }
  ```

#### 3. Displaying the Results:
- The results, such as waiting time and turnaround time for each process, are printed:
  ```c
  printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
  for (int i = 0; i < num_processes; i++) {
      printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i+1, arrival_time[i], burst_time[i], waiting_time[i], turnaround_time[i]);
  }
  ```

---

### Example of the Output:
If you run the code, the output will look like this:
```
Process Arrival Time    Burst Time      Waiting Time    Turnaround Time
1       0               3               0               3
2       2               5               3               8
3       4               2               8               10
4       6               4               10              14
5       8               1               14              15
```

#### Explanation of the Output:
- **Process**: Process number.
- **Arrival Time**: Time at which the process arrives.
- **Burst Time**: Time required to execute the process.
- **Waiting Time**: Time the process waits before it starts execution.
- **Turnaround Time**: Total time (waiting + execution).

---

### How the Algorithm Works:
1. Processes are executed in the order of their arrival (FIFO).
2. The waiting time for each process is calculated based on the completion time of the previous process.
3. The turnaround time for each process is calculated by adding the waiting time and burst time.

