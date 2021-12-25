#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct rr
{
  int index;
  int id;
  int f;
  char state[10];
} proc[10];



int main()
{
  int i, j, k, m, n;
  int temp;
  char str[10];
  cout << "\n enter the number of process: ";
  cin >> n;
  for (i = 0; i < n; i++)
  {
    proc[i].index;
    cout << "\n enter id of process: ";
    cin >> proc[i].id;
    strcpy(proc[i].state, "active");
    proc[i].f = 0;
  }
  // sorting
  for (i = 0; i < n - 1; i++)
  {
    for (j = 0; j < n - 1; j++)
    {
      if (proc[j].id > proc[j + 1].id)
      {
        temp = proc[j].id;
        proc[j].id = proc[j + 1].id;
        proc[j + 1].id = temp;
      }
    }
  }
  for (i = 0; i < n; i++)
    printf("[%d] %d\t", i, proc[i].id);
  int init;
  int ch;
  int temp1;
  int temp2;
  int arr[10];
  //make higher priority process inactive
  strcpy(proc[n - 1].state, "inactive");
  cout << "\nprocess " << proc[n - 1].id << " selected as coordinator";
  while (1)
  {
    cout << "\n\n1)election \n2)quit\n";
    scanf("%d", &ch);
    for (i = 0; i < n; i++)
    {
      proc[i].f = 0;
    }
    switch (ch)
    {
    case 1:
      cout << "\nenter the process Number who intialized election: ";
      scanf("%d", &init);
      temp2 = init;
      temp1 = init + 1;
      i = 0;
      while (temp2 != temp1)
      {
        if (strcmp(proc[temp1].state, "active") == 0 && proc[temp1].f == 0)
        {
          cout << "process " << proc[init].id << " send message to " << proc[temp1].id << "\n";
          proc[temp1].f = 1;
          init = temp1;
          arr[i] = proc[temp1].id;
          i++;
        }
        if (temp1 == n)
          temp1 = 0;
        else
          temp1++;
      }

      cout << "process " << proc[init].id << "send message to " << proc[temp1].id << "\n";
      arr[i] = proc[temp1].id;
      i++;
      int max = -1;
      for (j = 0; j < i; j++)
      {
        if (max < arr[j])
          max = arr[j];
      }
      cout << "\nprocess " << max << " select as coordinator";
      for (i = 0; i < n; i++)
      {
        if (proc[i].id == max)
        {
          strcpy(proc[i].state, "inactive");
          // cout<<"\n"<<i<<" "<<proc[i].id<<"deactivate\n";
        }
      }
      break;
    }
  }
  return 0;
}


//  enter the number of process: 7

//  enter id of process: 2

//  enter id of process: 3

//  enter id of process: 4

//  enter id of process: 5

//  enter id of process: 7

//  enter id of process: 8

//  enter id of process: 1

// [0] 1   [1] 2   [2] 3   [3] 4   [4] 5   [5] 7   [6] 8
// process 8 selected as coordinator
// 1)election
// 2)quit
// 1

// enter the process Number who intialized election: 4
// process 5 send message to 7
// process 7 send message to 1
// process 1 send message to 2
// process 2 send message to 3
// process 3 send message to 4
// process 4 send message to 5

// process 7 select as coordinator
// 1)election
// 2)quit
// 2