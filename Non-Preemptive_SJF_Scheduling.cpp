#include <stdio.h>

struct Process
{
    int index;
    int burstTime;
    int arrivalTime;
    int startTime;
    int endTime;
    int waitingTime;
    int turnaroundTime;
    int processed;
};

Process Q[5];       //ประกาศอาร์เรย์ชื่อ Q ชนิด Process ขนาด 5 ช่อง | ไว้สำหรับเก็บโปรเซสที่กำลังรอทำงาน หรืออยู่ในคิวรอ
int sp = 0;         //ทำหน้าที่เป็นตัวชี้ไปยังตำแหน่งว่างในคิว
int NT;             //เวลาที่โปรเซสทุกตัวทำงานเสร็จสิ้น
int np = 0;         //ทำหน้าที่เก็บจำนวนโปรเซสทั้งหมดในระบบ


void calNT(Process processes[], int n)         // NT ใช้หา เวลาที่ Process ทำงานทั้งหมด
{ // คำนวณหาผลรวมของ burt time
    int sumBurt = 0;
    int minArrival = processes[0].arrivalTime;
    for (int i = 0; i < n; ++i)                     
    {
        if(processes[i].arrivalTime < minArrival){
            minArrival = processes[i].arrivalTime;
        }
        sumBurt = sumBurt + processes[i].burstTime;
    }
    NT = minArrival + sumBurt;     //ทำผลรวมทั้งหมดของ ค่า Burst time
}                                   //NT ใช้หา เวลาที่ Process ทำงานทั้งหมด

void sortProcesses(Process processes[], int n)      //ทำหน้าที่เรียงลำดับโปรเซสในอาร์เรย์ processes ตาม burst time จากมากไปน้อย 
{
    Process temp;
    for (int i = 0; i < n; i++)     //loop ทำหน้าที่ วน Process ลำดับ Array
    {
        for (int j = i + 1; j < n; j++)     //วนเปรียบเทียบโปรเซสตัวถัดไปกับโปรเซสก่อนหน้า โดยเริ่มจากโปรเซสตัวที่ i+1
        {
            if (processes[j].burstTime > processes[i].burstTime)        //เงื่อนไขเทียบค่าของ Bursttime ในแต่ละ loop | busttime J น้อยกว่า 
            {
                temp = processes[j];            
                processes[j] = processes[i];
                processes[i] = temp;        //update ค่า Structure Processes ตามการเรียงลำดับ Burst time 
            }
        }
    }
}

float sumwait(Process processes[])
{
    int sum = 0;
    for (int i = 0; i < 5; i++)         // ใช้ for loop รันลำดับ i 
    {
        sum = sum + processes[i].waitingTime;      //ผลรวมของ waittime ใน struceture
    }

    return sum;
}

void nameuser()
{
    printf("# Mr.Papon Saerja ID:65543206021-9 Sec.01      #\n");
    printf("# OUTPUT LAB6 CPU Scheduling                      #\n");
    printf("# Non preemptive SJF scheduling                   #\n");
    printf("____________________________________________________________");
}

void printing_result(Process processes[], int n)
{
    int endTime = 0;    //ตำแหน่งที่เกิด critcal secction
    
    calNT(processes, n);        // คำนวณ NT เวลาทั้งหมดของ process 
    
    printf("\nSequence process is: ");
    for (int i = 0; i < NT; i++)        //  NT คือ เวลาที่โปรเซสทุกตัวทำงานเสร็จสิ้น | ประมาณ 23 Sec
    {
        for (int j = 0; j < n; j++)
        {
            // หาโปรเซสที่มาเกิดในเวลาของ i ปัจจุบันวนอยู่
            if (processes[j].arrivalTime == i)      //เวลาที่มาถึง (arrival time) ของโปรเซสตัวที่ j เท่ากับเวลาที่ระบบกำลังพิจารณา i นับเป็นวินาที clock การเกิดจบ
            {                                       //การเกิด
                Q[sp] = processes[j];       //เก็บค่า โปรเซสที่กำลังรอทำงานหรืออยู่ในคิวรอ ไว้ในตัวแปร       
                sp++;                       //sp แทนลำดับช่อง Array
            }
        }
        // running to in put 
        if (i >= endTime && sp > 0)       //clock ที่เวลาของโปรเซสมีค่า == เวลาเสร็จสิ้นการทำงาน 
        {
            sortProcesses(Q, sp);       //จัดเรียงโปรเซสในคิว Q ตามเวลามาถึง (Bust time) โดยเรียงจากน้อยไปมาก     
            sp--;                       //Sort คือตัวเทียบคิว
            processes[Q[sp].index - 1].startTime = i  ;         //กำหนดค่า startTime ของโปรเซสตัวที่ Q[sp] ให้เป็น endTime
            processes[Q[sp].index - 1].endTime = i + Q[sp].burstTime ;     //คำนวณเวลาสิ้นสุดของการประมวลผลของโปรเซสที่กำลังทำงานอยู่ และเก็บค่าไว้ในตัวแปร endTime
            endTime = processes[Q[sp].index - 1].endTime;       //คำนวณเวลาสิ้นสุดของการประมวลผลของโปรเซสที่กำลังทำงานอยู่ และเก็บค่าไว้ในตัวแปร endTime
            printf("P%d", processes[Q[sp].index - 1].index);        //แสดงลำดับ Process
            if (np < n - 1)     //np คือจำนวนโปรเซสทั้งหมดในระบบ มากกว่า จำนวนจำนวนโปรเซสในระบบ -1 ต่อรอบ 
            {
                printf("->");
            }
            np++;
        }
    }

    printf("\n\nWait time of process (millisecond)\n\n");
    printf("|");
    for (int i = 0; i < n; i++)
    {
        printf(" P%d\t|  ", processes[i].index);        //แสดงลำดับ Process ROW1
    }
    printf("\n|");            
    for (int i = 0; i < n; i++)
    {
        processes[i].waitingTime = processes[i].startTime - processes[i].arrivalTime;       //start time - arrival time       
        printf(" %.2f\t|", (float)processes[i].waitingTime);                                 //แสดงค่า waittime ของโปรเซส waittime 2
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;       //กำหนดค่าให้ trunaround time มีค่า burstTime + waitingTime
    }
    printf("\n\nAverage time is %.2f\n", sumwait(processes) / n);       //sumwait ผลรวม waittime / 5

    printf("\nTurnaround time\n");
    for (int i = 0; i < n; i++)
    {
        printf("|P%d = %d ms ", processes[i].index, processes[i].turnaroundTime);       //แสดง trunaround time และลำดับ Process
    }
    printf("\n____________________________________________________________");
}

int main()
{
    /*index bursttime arrivaltime*/
    /*Process processes[] = {
        {1, 9, 1},
        {2, 3, 1},
        {3, 5, 3},
        {4, 4, 4},
        {5, 2, 7},
    }; */
        Process processes[] = {
        {5, 2, 7},
        {4, 4, 4},
        {3, 5, 3}, 
        {1, 2, 1},
        {2, 3, 7}, 
        
    };
    nameuser();
    int n = sizeof(processes) / sizeof(processes[0]);  //process 5 ชุด / process 1 ชุดเดียว
    // เรียงลำดับอินเด็กซ์ของกระบวนการจากน้อยไปมาก
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].index > processes[j].index)
            {
                // สลับที่กัน
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
    printing_result(processes, n);
    printf("%d", NT );
    return 0;
}