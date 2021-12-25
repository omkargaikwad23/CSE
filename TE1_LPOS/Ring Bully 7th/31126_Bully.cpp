// #include <stdio.h>
// #include <string.h>
// #include <iostream>
// #include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;

struct rr
{
  char name[10];
  int prior;
  char state[10];
} proc[10];

int i, j, k, l, m, n;
int main()
{
  cout << "\n enter the number of processes: ";
  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    cout << "\nenter the name of process: ";
    cin >> proc[i].name;
    cout << "\nenter the priority of process: ";
    cin >> proc[i].prior;
    strcpy(proc[i].state, "active");
  }

  for (i = 0; i < n - 1; i++)
  {
    for (j = 0; j < n - 1; j++)
    {
      if (proc[j].prior < proc[j + 1].prior)
      {
        char ch[5];
        int t = proc[j].prior;
        proc[j].prior = proc[j + 1].prior;
        proc[j + 1].prior = t;
        strcpy(ch, proc[j].name);
        strcpy(proc[j].name, proc[j + 1].name);
        strcpy(proc[j + 1].name, ch);
      }
    }
  }
  int min = 0;
  for (i = 0; i < n; i++)
    cout << "\n"
         << proc[i].name << "\t" << proc[i].prior;
  for (i = 0; i < n; i++)
  {
    for (i = 0; i < n; i++)
    {
      if (min < proc[i].prior)
        min = proc[i].prior;
    }
  }
  for (i = 0; i < n; i++)
  {
    if (proc[i].prior == min)
    {
      cout << "\nprocess " << proc[i].name << " selected as coordinator";
      strcpy(proc[i].state, "is active");
      break;
    }
  }
  int pr;
  while (1)
  {
    int ch;
    cout << "\n\n1) election\t";
    cout << "\n2) exit  \t\n";
    cin >> ch;
    int max = 0;
    int ar[20];
    k = 0;
    int fl = 0;
    switch (ch)
    {
    case 1:
      char str[5];
      cout << "\n 1)initialize election\t";
      cin >> str;
      fl = 0;
    l1:
      // get priority of the one who initialised algo
      for (i = 0; i < n; i++)
      {
        if (strcmp(str, proc[i].name) == 0)
        {
          pr = proc[i].prior;
        }
      }
      // send msg from him to higher processes
      for (i = 0; i < n; i++)
      {
        if (pr < proc[i].prior)
        {
          cout << "\nprocess " << str << " send message to " << proc[i].name;
        }
      }

      // higher priority process sends ok back msg if it is active
      for (i = 0; i < n; i++)
      {
        if (pr < proc[i].prior && strcmp(proc[i].state, "active") == 0)
        {
          if (fl == 0)
          {
            ar[k] = proc[i].prior;
            k++;
          }
          cout << "\nprocess " << proc[i].name << " send OK message to " << str;
          if (proc[i].prior > max)
            max = proc[i].prior;
        }
      }
      fl = 1;

      if (k != 0)
      {
        k = k - 1;
        for (i = 0; i < n; i++)
        {
          if (ar[k] == proc[i].prior)
            strcpy(str, proc[i].name);
        }
        // repeat the same if ok msg is received
        goto l1;
      }
      m = 0;
      for (j = 0; j < n; j++)
      {
        if (proc[j].prior > m && strcmp(proc[j].state, "active") == 0)
        {
          cout << "\nprocess " << proc[j].name << " is select as new coordinator";
          strcpy(proc[j].state, "inactive");
          break;
        }
      }

      for (i = 0; i < n; i++)
      {
        if (strcmp(proc[i].state, "active") == 0 && proc[j].prior > proc[i].prior)
        {
          cout << "\nprocess " << proc[j].name << " send alert message to " << proc[i].name;
        }
      }

      break;
    case 2:
      exit(1);
    }
  }
  return 0;
}

/*
 enter the number of processes: 4

enter the name of process: p4

enter the priority of process: 4

enter the name of process: p3

enter the priority of process: 3

enter the name of process: p2

enter the priority of process: 2

enter the name of process: p1

enter the priority of process: 1

p4      4
p3      3
p2      2
p1      1
process p4 selected as coordinator

1) election
2) exit
1

 1)initialize election  p2

process p2 send message to p4
process p2 send message to p3
process p3 send OK message to p2
process p3 send message to p4
process p3 is select as new coordinator
process p3 send alert message to p2
process p3 send alert message to p1

1) election
2) exit
2
*/