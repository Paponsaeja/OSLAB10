#include <iomanip>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std ;

typedef struct  { 
int pid;
int burst_time;
int arrival_time;
int start_time;
int completion_time;
int turnaround_time;
int waiting_time;
}Process ;

// pid , burst , arrival
Process p[]= {
    {1, 9, 1},
    {2, 5, 1},
    {3, 1, 3},
    {4, 4, 4},
    {5, 2, 7},
};

vector<int> get_process_sequence(Process p[], int n) {
    vector<int> sequence;
    int current_time = 0;
    int completed = 0;

    while (completed != n) {
        int idx = -1;
        int mn = 10000000;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].burst_time > 0) {
                if (p[i].burst_time < mn) {
                    mn = p[i].burst_time;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            sequence.push_back(p[idx].pid);
            p[idx].burst_time--;
            current_time++;

            if (p[idx].burst_time == 0) {
                completed++;
            }
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
    float throughput;
    int burst_remaining [n];
    int is_completed [100];   // บอกถึงการหมดหน้าที่ 0 = ยัง , 1 = หมดแล้ว
    memset(is_completed,0,sizeof(is_completed));  // กำหนดค่าเริ่มต้น = 0

    cout << setprecision(2) << fixed ;   // กำหนดให้ cout จะแสดงทศนิยมเพียง 2 ตำแหน่งเท่านั้น โดยไม่ต้องสั่งซ้ำอีก

    //  เก็บ bursttime ไว้คำนวณ เนื่องจากใช้แบบเข้าและออกอาจหลงเหลือเพราะเป็น preemp
    for( int i = 0; i < n ; i++) {
        burst_remaining[i] = p[i].burst_time ;
        // cout<< "bursttimeremain[%d] = "<< burst_remaining[i]<<endl ;
    }

    int current_time = 0 ;   // เวลาปัจจุบัน
    int completed = 0 ;      // เวลาจบการทำงาน

     
    while(completed != n) {
        int idx = -1;
        int mn = 10000000;
        // forloop as Queue
        for(int i = 0; i < n; i++) {   // หาโปรเซสที่ bursttime น้อยที่สุด จากการวนล฿ป process 5 ตัว
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {   // จะไม่ทำงานที่ current = 0 หากไม่มี Process เกิด
                if(burst_remaining[i] < mn) {
                    mn = burst_remaining[i];
                    idx = i ;
                }
                if(burst_remaining[i] == mn) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mn = burst_remaining[i];
                        idx = i ;
                    }
                }
            }
        }

        if(idx != -1 ) {
            if(burst_remaining[idx] == p[idx].burst_time) { // bursttime มีค่าตรงกับ processตำแหน่ง idx ล่าสุด 
                p[idx].start_time = current_time ;   // ให้ process ที่ชนะได้ครอบครอง cpu ในวินาทีปัจจุบัน
            }
            burst_remaining[idx] -= 1 ;
            current_time++ ;

            if(burst_remaining[idx] == 0) {  // เก็บตัวที่ทำงานจบแล้ว
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time; 
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                
                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                
                
                is_completed [idx] = 1;
                completed++;   // บอกให้ while รับรู้
            }
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
    

    cout<<"#P\t"<<"AT\t"<<"TAT\t"<<"WT\t"<<"ST\t"<<"CT\t"<<"\n"<<endl ;

    for(int i = 0; i < n; i++) {
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<endl ;
    }
    cout<<"Average Turnaround = "<< avg_turnaround_time<<endl ;
    cout<<"Average waiting = "<< avg_waiting_time<<endl ;
}