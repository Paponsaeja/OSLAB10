#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include <vector>
using namespace std ;  // ย่อชื่อคลาสเวลานำมาใช้จากlibrary

typedef struct  {
    int pid ;
    int burst_time;
    int arrival_time;
    int priority;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time; 
} Process; 

Process p[]= {
    {1, 9, 1, 3},
    {2, 5, 1, 5},
    {3, 1, 3, 1},
    {4, 4, 4, 4},
    {5, 2, 7, 2},
    
};

vector<int> get_process_sequence(Process p[], int n) {
    vector<int> sequence;
    int is_completed [100];   // บอกถึงการหมดหน้าที่ 0 = ยัง , 1 = หมดแล้ว
    memset (is_completed,0,sizeof(is_completed)) ;
    int current_time = 0;
    int completed = 0;

    while (completed != n) {
        int idx = -1;
        int mx = -1 ;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i]== 0) {
                if(p[i].priority > mx) {
                    mx = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            sequence.push_back(p[idx].pid);
            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
        } else {
            current_time++;
        }
    }

    return sequence;
}


int main() {
    int n = 5 ;
    float avg_turnaround_time; 
    float avg_waiting_time; 
    int total_turnaround_time = 0;
    int total_waiting_time = 0; 
    int is_completed [100];   // บอกถึงการหมดหน้าที่ 0 = ยัง , 1 = หมดแล้ว
    memset (is_completed,0,sizeof(is_completed)) ;

    cout << setprecision(2) << fixed ;   // กำหนดให้ cout จะแสดงทศนิยมเพียง 2 ตำแหน่งเท่านั้น โดยไม่ต้องสั่งซ้ำอีก
    cout << "hello"<< endl ;
    int current_time = 0 ;   // เวลาปัจจุบัน
    int completed = 0 ;      // เวลาจบการทำงาน
    while(completed != n) {
        int idx = -1;
        int mx = -1;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i]== 0) {
                if(p[i].priority > mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time; 
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time; 
            
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;

            p[idx].completion_time = p[idx].burst_time + p[idx].start_time ;
            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
        }
        else {
            current_time++ ;
        }
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;

    cout<<endl<<endl;
    vector<int> sequence = get_process_sequence(p, n);
    cout << "Process Sequence: ";
    for (int pid : sequence) {
        cout << pid << " | ";
    }
    cout << endl;

    cout<<"#P\t"<<"AT\t"<<"TAT\t"<<"WT\t"<<"PRT\t"<<"ST\t"<<"CT\t"<<"\n"<<endl ;

    for(int i = 0; i < n; i++) {
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<p[i].priority<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<endl ;
    }
    cout<<"Average Turnaround = "<< avg_turnaround_time<<endl ;
    cout<<"Average waiting = "<< avg_waiting_time<<endl ;
}