//31126 the Lamport's Logical Clock

//sending: (timestamp+1)
//receiving: max(own, sender+1)

#include <bits/stdc++.h>
using namespace std;

// to find the maximum timestamp between 2 events
int max1(int a, int b)
{
	// Return the greatest of these two
	if (a > b)
		return a;
	else
		return b;
}

// display the logical timestamp
void display(int e1, int e2, int p1[5], int p2[3])
{
	int i;

	cout << "\nThe time stamps of events in P1:\n";

	for (i = 0; i < e1; i++)
	{
		cout << p1[i] << " ";
	}

	cout << "\nThe time stamps of events in P2:\n";

	for (i = 0; i < e2; i++)
		cout << p2[i] << " ";
}

void lamportLogicalClock(int e1, int e2, int m[5][3])
{
	int i, j, k, p1[e1], p2[e2];

	// Initialize p1[] and p2[]
	for (i = 0; i < e1; i++)
		p1[i] = i + 1;

	for (i = 0; i < e2; i++)
		p2[i] = i + 1;

	for (i = 0; i < e2; i++)
		cout << "\te2" << i + 1;

	for (i = 0; i < e1; i++)
	{

		cout << "\n e1" << i + 1 << "\t";

		for (j = 0; j < e2; j++)
			cout << m[i][j] << "\t";
	}

	for (i = 0; i < e1; i++)
	{
		for (j = 0; j < e2; j++)
		{

			// Change the timestamp if the message is sent (message is sent from ei to ej)
			//sending: (timestamp+1)
			if (m[i][j] == 1)
			{
				p2[j] = max1(p2[j], p1[i] + 1);
				for (k = j + 1; k < e2; k++)
					p2[k] = p2[k - 1] + 1;
			}

			// Change the timestamp if the message is received (message is received by ei from ej)
			// receiving: max(own, sender+1)
			if (m[i][j] == -1)
			{
				p1[i] = max1(p1[i], p2[j] + 1);
				for (k = i + 1; k < e1; k++)
					p1[k] = p1[k - 1] + 1;
			}
		}
	}
	display(e1, e2, p1, p2);
}

int main()
{
	int e1 = 5, e2 = 3;
	int m[5][3] = {{0, 0, 0}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, {0, -1, 0}};

	// message is sent and received between two process

	/*m[i][j] = 1, if message is sent from ei to ej
	m[i][j] = -1, if message is received by ei from ej
	m[i][j] = 0, otherwise*/

	lamportLogicalClock(e1, e2, m);

	return 0;
}

//         e21     e22     e23
//  e11     0      0       0
//  e12     0      0       1
//  e13     0      0       0
//  e14     0      0       0
//  e15     0      -1      0
// The time stamps of events in P1:
// 1 2 3 4 5
// The time stamps of events in P2:
// 1 2 3