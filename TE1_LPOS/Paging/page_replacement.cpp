// Program to simulate page replacement in os

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

class PageReplacementAlgos {
    vector<int> ref;
    int frame_size;
public:
    PageReplacementAlgos(){
        this->frame_size = 3;
    }

    void setRef(vector<int> ref){
        this->ref = ref;
    } 

    void setFrameSize(int frame_size){
        this->frame_size = frame_size;
    }

    void fifoMethod(){
        int frames[frame_size];
        int current_add_index = 0, current_rep_index = 0, page_faults = 0;

        for (int i=0; i<ref.size(); i++){
            if (current_add_index < frame_size){
                frames[current_add_index] = ref[i];
                current_add_index++;
                page_faults++;
                cout << "Element " << ref[i] << " has generated page fault. (Frame limit not exceeded)" << endl;
            }
            else if (find(frames, min(frames+current_add_index+1, frames+frame_size), ref[i]) == frames+frame_size) {
                int rep_element = frames[current_rep_index];
                frames[current_rep_index] = ref[i];
                current_rep_index = (current_rep_index+1) % frame_size; 
                page_faults++;
                cout << "Element " << ref[i] << " has generated page fault by replacing " << rep_element << endl;
            }
        }
        cout << "\nThe Number of page faults found using FIFO method is: " << page_faults << endl;
    }

    void optimalMethod(){
        int frames[frame_size];
        int current_add_index = 0, current_rep_index = 0, page_faults = 0;

        for (int i=0; i<ref.size(); i++){
            if (current_add_index < frame_size){
                frames[current_add_index] = ref[i];
                current_add_index++;
                page_faults++;
                cout << "Element " << ref[i] << " has generated page fault. (Frame limit not exceeded)" << endl;
            }
            else if (find(frames, min(frames+current_add_index+1, frames+frame_size), ref[i]) == frames+frame_size) {
                int max_dist = 0;
                for (int j=0; j<frame_size; j++){
                    int dist = find(ref.begin()+i, ref.end(), frames[j]) - ref.begin() - i;
                    if (dist > max_dist){
                        max_dist = dist;
                        current_rep_index = j;
                    }
                }
                int rep_element = frames[current_rep_index];
                frames[current_rep_index] = ref[i];
                page_faults++;
                cout << "Element " << ref[i] << " has generated page fault by replacing " << rep_element << endl;
            }
        }
        cout << "\nThe Number of page faults found using Optimal Replacement method is: " << page_faults << endl;
    }

    void leastRecentMethod(){
        int frames[frame_size];
        int current_add_index = 0, current_rep_index = 0, page_faults = 0;

        for (int i=0; i<ref.size(); i++){
            if (current_add_index < frame_size){
                frames[current_add_index] = ref[i];
                current_add_index++;
                page_faults++;
                cout << "Element " << ref[i] << " has generated page fault. (Frame limit not exceeded)" << endl;
            }
            else if (find(frames, min(frames+current_add_index+1, frames+frame_size), ref[i]) == frames+frame_size) {
                int max_dist = 0;
                for (int j=0; j<frame_size; j++){
                    auto it = find(ref.rbegin()+ref.size()-i, ref.rend(), frames[j]);
                    int dist = (it - ref.rend()) + 1 + i;
                    if (dist > max_dist){
                        max_dist = dist;
                        current_rep_index = j;
                    }
                }
                int rep_element = frames[current_rep_index];
                frames[current_rep_index] = ref[i];
                page_faults++;
                cout << "Element " << ref[i] << " has generated page fault by replacing " << rep_element << endl;
            }
        }
        cout << "\nThe Number of page faults found using Least Recently Used Replacement method is: " << page_faults << endl;
    }

};

int main (){
    vector<int> input_ref;
    PageReplacementAlgos pg1;
    int n, frame_input;
    cout << "\nEnter the number of references you want to add: ";
    cin >> n;
    cout << "Enter the frame size you want: ";
    cin >> frame_input;
    cout << endl;

    for (int i=0; i<n; i++){
        int in;
        cout << "Enter a reference: ";
        cin >> in;
        input_ref.push_back(in);
    }

    cout << "\n\n";

    pg1.setFrameSize(frame_input);
    pg1.setRef(input_ref);

    int choice;
    bool flag = true;
    while (flag){
        cout << "\nMenu:"
             << "\n1. Get Page Faults with FIFO method: "
             << "\n2. Get Page Faults with Optimal Page Replacement: "
             << "\n3. Get Page Faults with Least Recently Used: "
             << "\n4. Change the input Reference string: "
             << "\n5. Change the number of frames: "
             << "\n6. Exit" << endl;
        
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice){
            case 1:
            {
                pg1.fifoMethod();
                break;
            }
            case 2:
            {
                pg1.optimalMethod();
                break;
            }
            case 3:
            {
                pg1.leastRecentMethod();
                break;
            }
            case 4:
            {
                vector<int> input_ref;
                int n;
                cout << "\nEnter the number of references you want to add: ";
                cin >> n;
                for (int i=0; i<n; i++){
                    int in;
                    cout << "Enter a reference: ";
                    cin >> in;
                    input_ref.push_back(in);
                }
                pg1.setRef(input_ref);
                break;
            }
            case 5:
            {
                int frame_input;
                cout << "Enter the frame size you want: ";
                cin >> frame_input;
                cout << endl;
                break;
            }
            case 6:
                cout << "\nGood Bye!!!";
                flag = false;
                break;
        }
    }
    return 0;
}

/*
Output:
Enter the number of references you want to add: 14
Enter the frame size you want: 3

Enter a reference: 7
Enter a reference: 0
Enter a reference: 1
Enter a reference: 2
Enter a reference: 0
Enter a reference: 3
Enter a reference: 0
Enter a reference: 4
Enter a reference: 2
Enter a reference: 3
Enter a reference: 0
Enter a reference: 3
Enter a reference: 2
Enter a reference: 3



Menu:
1. Get Page Faults with FIFO method: 
2. Get Page Faults with Optimal Page Replacement: 
3. Get Page Faults with Least Recently Used:      
4. Change the input Reference string:
5. Change the number of frames:
6. Exit

Enter your choice: 1
Element 7 has generated page fault. (Frame limit not exceeded)
Element 0 has generated page fault. (Frame limit not exceeded)
Element 1 has generated page fault. (Frame limit not exceeded)
Element 2 has generated page fault by replacing 7
Element 3 has generated page fault by replacing 0
Element 0 has generated page fault by replacing 1
Element 4 has generated page fault by replacing 2
Element 2 has generated page fault by replacing 3
Element 3 has generated page fault by replacing 0
Element 0 has generated page fault by replacing 4

The Number of page faults found using FIFO method is: 10

Menu:
1. Get Page Faults with FIFO method:
2. Get Page Faults with Optimal Page Replacement:
3. Get Page Faults with Least Recently Used:
4. Change the input Reference string:
5. Change the number of frames:
6. Exit

Enter your choice: 2
Element 7 has generated page fault. (Frame limit not exceeded)
Element 0 has generated page fault. (Frame limit not exceeded)
Element 1 has generated page fault. (Frame limit not exceeded)
Element 2 has generated page fault by replacing 7
Element 3 has generated page fault by replacing 1
Element 4 has generated page fault by replacing 0
Element 0 has generated page fault by replacing 4

The Number of page faults found using Optimal Replacement method is: 7

Menu:
1. Get Page Faults with FIFO method:
2. Get Page Faults with Optimal Page Replacement:
3. Get Page Faults with Least Recently Used:
4. Change the input Reference string:
5. Change the number of frames:
6. Exit

Enter your choice: 3
Element 7 has generated page fault. (Frame limit not exceeded)
Element 0 has generated page fault. (Frame limit not exceeded)
Element 1 has generated page fault. (Frame limit not exceeded)
Element 2 has generated page fault by replacing 7
Element 3 has generated page fault by replacing 1
Element 4 has generated page fault by replacing 2
Element 2 has generated page fault by replacing 3
Element 3 has generated page fault by replacing 0
Element 0 has generated page fault by replacing 4

The Number of page faults found using Least Recently Used Replacement method is: 9

Menu:
1. Get Page Faults with FIFO method:
2. Get Page Faults with Optimal Page Replacement:
3. Get Page Faults with Least Recently Used:
4. Change the input Reference string:
5. Change the number of frames:
6. Exit

Enter your choice: 6

Good Bye!!!

*/