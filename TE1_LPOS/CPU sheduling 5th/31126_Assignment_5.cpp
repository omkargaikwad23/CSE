#include <bits/stdc++.h>
using namespace std;
#define MAX_PROCESS 10

class Process
{
private:
  int id;
  int burstTime;
  int arrivalTime;
  int completionTime;
  int turnAroundTime;
  int waitingTime;
  int processPriority;

public:
  int getId()
  {
    return id;
  }
  int getBurstTime()
  {
    return burstTime;
  }
  int getArrivalTime()
  {
    return arrivalTime;
  }
  int getCompletionTime()
  {
    return completionTime;
  }
  int getTurnAroundTime()
  {
    return turnAroundTime;
  }
  int getWaitingTime()
  {
    return waitingTime;
  }
  int getProcessPriority()
  {
    return processPriority;
  }
  void setId(int id)
  {
    this->id = id;
  }
  void setBurstTime(int burstTime)
  {
    this->burstTime = burstTime;
  }
  void setArrivalTime(int arrivalTime)
  {
    this->arrivalTime = arrivalTime;
  }
  void setCompletionTime(int completionTime)
  {
    this->completionTime = completionTime;
  }
  void setTurnAroundTime(int turnAroundTime)
  {
    this->turnAroundTime = turnAroundTime;
  }
  void setWaitingTime(int waitingTime)
  {
    this->waitingTime = waitingTime;
  }
  void setPriority(int processPriority)
  {
    this->processPriority = processPriority;
  }
};

bool compareByArrival(Process p, Process q)
{
  return p.getArrivalTime() < q.getArrivalTime();
}

bool compareByBurst(Process p, Process q)
{
  return p.getBurstTime() < q.getBurstTime();
}

bool compareById(Process p, Process q)
{
  return p.getId() < q.getId();
}

bool compareByPriority(Process p, Process q)
{
  if(p.getArrivalTime() == q.getArrivalTime()){
      return p.getProcessPriority() < q.getProcessPriority();
  }
  else{
    return p.getArrivalTime() < q.getArrivalTime();
  }
}


void display(Process P[], int jobCount, float avgWT = 0, float avgTAT = 0)
{
  sort(P, P + jobCount, compareById);

  cout << "\tID  ||  AT  ||  BT  ||  CT  ||  TAT ||  WT" << endl;
  for (int i = 0; i < jobCount; i++)
  {
    cout << "\t" << P[i].getId()
         << "\t" << P[i].getArrivalTime()
         << "\t" << P[i].getBurstTime()
         << "\t" << P[i].getCompletionTime()
         << "\t" << P[i].getTurnAroundTime()
         << "\t" << P[i].getWaitingTime() << endl;
  }

  cout << "\n\t=> Average waiting time: " << avgWT << endl;
  cout << "\t=> Average turn around time: " << avgTAT << endl;

  cout << "\n\n";
}

void getData(Process P[], int &jobCount)
{
  int x;
  for (int i = 0; i < jobCount; i++)
  {
    P[i].setId(i+1);
    cout << "\n\tprocess ID: ";
    cout << P[i].getId() << endl;
    cout << "\tEnter the process arrival time: ";
    cin >> x;
    P[i].setArrivalTime(x);
    cout << "\tEnter the process burst time: ";
    cin >> x;
    P[i].setBurstTime(x);
  }
}

void getDataForRR(Process P[], int &jobCount){
  int x;
  for (int i = 0; i < jobCount; i++)
  {
    P[i].setId(i+1);
    cout << "\n\tprocess ID: ";
    cout << P[i].getId() << endl;
    cout << "\tEnter the process arrival time: ";
    cin >> x;
    P[i].setArrivalTime(x);
    cout << "\tEnter the process priority: ";
    cin >> x;
    P[i].setPriority(x);
    cout << "\tEnter the process burst time: ";
    cin >> x;
    P[i].setBurstTime(x);
  }
}

void fcfs(Process P[], int jobCount)
{
  cout << "\n\t<<-----------------FCFS------------------>>\n" << endl;

  float avgWaitTime = 0, avgTurnAroundTime = 0;

  // Sorting the processes according to Arrival Time
  sort(P, P + jobCount, compareByArrival);

  for (int i = 0, prevEnd = 0; i < jobCount; i++)
  {
    P[i].setCompletionTime(max(prevEnd, P[i].getArrivalTime()) + P[i].getBurstTime());
    P[i].setTurnAroundTime(P[i].getCompletionTime() - P[i].getArrivalTime());
    P[i].setWaitingTime(P[i].getTurnAroundTime() - P[i].getBurstTime());

    prevEnd = P[i].getCompletionTime();

    avgWaitTime += P[i].getWaitingTime();
    avgTurnAroundTime += P[i].getTurnAroundTime();
  }

  avgWaitTime = (float)avgWaitTime / jobCount;
  avgTurnAroundTime = (float)avgTurnAroundTime / jobCount;

  display(P, jobCount, avgWaitTime, avgTurnAroundTime);
}

// Shortest job first non preemptive
void sjf(Process P[], int jobCount)
{
  cout << "\n\t<<------------------SJF------------------>>\n" << endl;

  int executedCount = 0;
  bool processActive[jobCount];
  fill(processActive, processActive + jobCount, false);
  vector<Process> processInQueue;
  map<int, int> id_compl;

  for (int time = 0; executedCount < jobCount;)
  {
    for (int i = 0; i < jobCount; i++)
    {
      if (!processActive[P[i].getId() - 1] && P[i].getArrivalTime() <= time)
      {                                 // To check if process is executed before and also whether it has arrived or not
        processInQueue.push_back(P[i]); // Pushed to Process Arrived Vector
        processActive[P[i].getId() - 1] = true;
      }
    }
    if (processInQueue.size() != 0)
    {
      vector<Process>::iterator minPosition = min_element(processInQueue.begin(),
                                                          processInQueue.end(), compareByBurst);
      Process processMinBurstTime = *minPosition;
      time += processMinBurstTime.getBurstTime();
      id_compl[processMinBurstTime.getId()] = time;
      executedCount++;
      processInQueue.erase(minPosition);
    }
    else
    {
      time++;
    }
  }
  float avgWaitTime = 0, avgTurnAroundTime = 0;

  for (int i = 0; i < jobCount; ++i)
  {
    P[i].setCompletionTime(id_compl[P[i].getId()]);
    P[i].setTurnAroundTime(P[i].getCompletionTime() - P[i].getArrivalTime());
    P[i].setWaitingTime(P[i].getTurnAroundTime() - P[i].getBurstTime());
    avgWaitTime += P[i].getWaitingTime();
    avgTurnAroundTime += P[i].getTurnAroundTime();
  }

  avgWaitTime = (float)avgWaitTime / jobCount;
  avgTurnAroundTime = (float)avgTurnAroundTime / jobCount;

  display(P, jobCount, avgWaitTime, avgTurnAroundTime);

  // cout << "\tGantt chart" << endl;
  
}

void RoundRobin(Process P[], int jobCount)
{
  cout << "\n\t<<----------Round Robin---------->>\n" << endl;
  int tQuantum;
  cout << "\tEnter time quantum: ";
  cin >> tQuantum;
  bool inQueue[jobCount + 1];
  fill(inQueue, inQueue + jobCount + 1, false);
  map<int, int> id_compl;
  int jobDone = 0, curTime = 0;
  queue<Process> ready_queue;

  do
  {
    for (int i = 0; i < jobCount; ++i)
    {
      if (!inQueue[P[i].getId()] && P[i].getArrivalTime() == curTime)
      {
        ready_queue.push(P[i]);
        inQueue[P[i].getId()] = true;
      }
    }
    if (!ready_queue.empty())
    {
      Process p = ready_queue.front();
      ready_queue.pop();
      int tq = min(tQuantum, p.getBurstTime());
      // cout<<"p"<<p.getId()<<"->";
      int b = p.getBurstTime();
      p.setBurstTime(p.getBurstTime() - tq);
      for (int i = curTime + 1; i <= curTime + tq; ++i)
      {
        for (int j = 0; j < jobCount; ++j)
        {
          if (!inQueue[P[j].getId()] && P[j].getArrivalTime() == i)
          {
            ready_queue.push(P[j]);
            inQueue[P[j].getId()] = true;
          }
        }
      }
      curTime += tq;
      if (p.getBurstTime() == 0)
      {
        jobDone++;
        p.setCompletionTime(curTime);
        id_compl[p.getId()] = p.getCompletionTime();
      }
      else
      {
        ready_queue.push(p);
      }
    }
    else
    {
      curTime++;
    }
  } while (jobDone != jobCount);

  float avgWaitTime = 0, avgTurnAroundTime = 0;

  for (int i = 0; i < jobCount; ++i)
  {
    P[i].setCompletionTime(id_compl[P[i].getId()]);
    P[i].setTurnAroundTime(P[i].getCompletionTime() - P[i].getArrivalTime());
    P[i].setWaitingTime(P[i].getTurnAroundTime() - P[i].getBurstTime());
    avgWaitTime += P[i].getWaitingTime();
    avgTurnAroundTime += P[i].getTurnAroundTime();
  }

  avgWaitTime = (float)avgWaitTime / jobCount;
  avgTurnAroundTime = (float)avgTurnAroundTime / jobCount;

  display(P, jobCount, avgWaitTime, avgTurnAroundTime);
}

void PriorityScheduler(Process P[], int jobCount){
  cout << "\n\t<<---------Priority Scheduler--------->>\n" << endl;
  
  sort(P, P+jobCount, compareByPriority);
  float avgWaitTime = 0, avgTurnAroundTime = 0;

  for(int i=0; i<jobCount; i++){
    p[i].setCompletionTime(p[i].getArrivalTime() + p[i].getBurstTime());
    p[i].setTurnAroundTime(p[i].getCompletionTime() - p[i].getArrivalTime());
    p[i].setWaitingTime(p[i].getTurnAroundTime() - p[i].getBurstTime());
    avgWaitTime += P[i].getWaitingTime();
    avgTurnAroundTime += P[i].getTurnAroundTime();
  }

  avgWaitTime = (float)avgWaitTime / jobCount;
  avgTurnAroundTime = (float)avgTurnAroundTime / jobCount;
}

int main()
{
  int choice, jobCount;
  int flag = 1;
  while(flag!=5)
  { 
    cout << "\t<<----CPU Scheduling Algorithms---->>\n"
         << "\t\t1. fcfs\n"
         << "\t\t2. sjf\n"
         << "\t\t3. priority scheduler\n"
         << "\t\t4. round robin\n"
         << "\t\t5. EXIT\n"
         << "\t<<--------------------------------->>"
         << "\n\n\tEnter your choice[1-5]: ";

    cin >> choice;
    cout << "\tNo of processes: ";
    cin >> jobCount;

    Process P[jobCount];

    //Enter data manually
    if(choice == 3){
      getDataForRR(P, jobCount);
    }
    else{
      getData(P, jobCount);
    }

    switch (choice)
    {
    case 1:
      fcfs(P, jobCount);
      break;
    case 2:
      sjf(P, jobCount);
      break;
    case 3:
      PriorityScheduler(P, jobCount);
      break;
    case 4:
      RoundRobin(P, jobCount);
      break;
    case 5:
      cout << "\n\tEXIT!! BYE!!";
      flag = 5;
      break;
    default:
      cout << "\tEnter valid choice" << endl;
    }
  }

  return 0;
}

/*
PS D:\Documents\TE SEM5-labs\LPOS> cd "d:\Documents\TE SEM5-labs\LPOS\" ; if ($?) { g++ 31126_Assignment_1.cpp -o 31126_Assignment_1 } ; if 
($?) { .\31126_Assignment_1 }
        <<----CPU Scheduling Algorithms---->>
                1. fcfs
                2. sjf
                3. priority scheduler        
                4. round robin
                5. EXIT
        <<--------------------------------->>

        Enter your choice[1-5]: 4
        No of processes: 5

        process ID: 1
        Enter the process arrival time: 0
        Enter the process burst time: 5

        process ID: 2
        Enter the process arrival time: 1
        Enter the process burst time: 3

        process ID: 3
        Enter the process arrival time: 2
        Enter the process burst time: 1

        process ID: 4
        Enter the process arrival time: 3
        Enter the process burst time: 2

        process ID: 5
        Enter the process arrival time: 4
        Enter the process burst time: 3

        <<----------Round Robin---------->>

        Enter time quantum: 2
        ID  ||  AT  ||  BT  ||  CT  ||  TAT ||  WT
        1       0       5       13      13      8
        2       1       3       12      11      8
        3       2       1       5       3       2
        4       3       2       9       6       4
        5       4       3       14      10      7

        => Average waiting time: 5.8
        => Average turn around time: 8.6


        <<----CPU Scheduling Algorithms---->>
                1. fcfs
                2. sjf
                3. priority scheduler
                4. round robin
                5. EXIT
        <<--------------------------------->>

        Enter your choice[1-5]: 1
        No of processes: 6

        process ID: 1
        Enter the process arrival time: 3
        Enter the process burst time: 4

        process ID: 2
        Enter the process arrival time: 5
        Enter the process burst time: 3

        process ID: 3
        Enter the process arrival time: 0
        Enter the process burst time: 2

        process ID: 4
        Enter the process arrival time: 5
        Enter the process burst time: 1

        process ID: 5
        Enter the process arrival time: 4
        Enter the process burst time: 3

        process ID: 6
        Enter the process arrival time: 0
        Enter the process burst time: 0

        <<-----------------FCFS------------------>>

        ID  ||  AT  ||  BT  ||  CT  ||  TAT ||  WT
        1       3       4       7       4       0
        2       5       3       13      8       5
        3       0       2       2       2       0
        4       5       1       14      9       8
        5       4       3       10      6       3
        6       0       0       2       2       2

        => Average waiting time: 3
        => Average turn around time: 5.16667


        <<----CPU Scheduling Algorithms---->>
                1. fcfs
                2. sjf
                3. priority scheduler
                4. round robin
                5. EXIT
        <<--------------------------------->>

        Enter your choice[1-5]: 1
        No of processes: 5

        process ID: 1
        Enter the process arrival time: 3
        Enter the process burst time: 4

        process ID: 2
        Enter the process arrival time: 5
        Enter the process burst time: 3

        process ID: 3
        Enter the process arrival time: 0
        Enter the process burst time: 2

        process ID: 4
        Enter the process arrival time: 5
        Enter the process burst time: 1

        process ID: 5
        Enter the process arrival time: 4
        Enter the process burst time: 3

        <<-----------------FCFS------------------>>

        ID  ||  AT  ||  BT  ||  CT  ||  TAT ||  WT
        1       3       4       7       4       0
        2       5       3       13      8       5
        3       0       2       2       2       0
        4       5       1       14      9       8
        5       4       3       10      6       3

        => Average waiting time: 3.2
        => Average turn around time: 5.8


        <<----CPU Scheduling Algorithms---->>
                1. fcfs
                2. sjf
                3. priority scheduler
                4. round robin
                5. EXIT
        <<--------------------------------->>

        Enter your choice[1-5]: 2
        No of processes: 5

        process ID: 1
        Enter the process arrival time: 3
        Enter the process burst time: 1

        process ID: 2
        Enter the process arrival time: 1
        Enter the process burst time: 4

        process ID: 3
        Enter the process arrival time: 4
        Enter the process burst time: 2

        process ID: 4
        Enter the process arrival time: 0
        Enter the process burst time: 6

        process ID: 5
        Enter the process arrival time: 2
        Enter the process burst time: 3

        <<------------------SJF------------------>>

        ID  ||  AT  ||  BT  ||  CT  ||  TAT ||  WT
        1       3       1       7       4       3
        2       1       4       16      15      11
        3       4       2       9       5       3
        4       0       6       6       6       0
        5       2       3       12      10      7

        => Average waiting time: 4.8
        => Average turn around time: 8


        <<----CPU Scheduling Algorithms---->>
                1. fcfs
                2. sjf
                3. priority scheduler
                4. round robin
                5. EXIT
        <<--------------------------------->>

        Enter your choice[1-5]: 5
*/