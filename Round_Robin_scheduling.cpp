#include <stdio.h>

struct Process
{
    int index ;
    int burstTime;
    int arrivalTime;
    int priority;
    int startTime;
    int endTime;
    int waitingTime;
    int turnaroundTime;
    int processed;
};

int stackmember[5] ={ 0,0,0,0,0} ;
int Q[30] ;
int sp = 0 ;
int QuantumT = 5 ;


/*void sortProcesses(Process processes[], int n)
{
    struct Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].burstTime > processes[j + 1].burstTime)
            {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}*/

int mostarrival(Process processes[] ){
    int mostarrivalT = processes[0].arrivalTime ;
    for ( int i = 0 ; i < 5 ; i++ ){
        if ( processes[i].arrivalTime > mostarrivalT ){
            mostarrivalT = processes[i].arrivalTime ;
        }
    }
    return  mostarrivalT ;
}
int timeallprocesss(Process processes[] ){
    int mostarrivalT = mostarrival(processes) ;
    int sum ;
    for ( int i = 0 ; i < 5 ; i++ ){
        sum += processes[i].burstTime ;
    }
    return  mostarrivalT + mostarrivalT ;
}

float sumwait(Process processes[]){
    int sum = 0 ;
    for ( int i = 0 ; i < 5 ; i++ ){
        sum = sum + processes[i].waitingTime ;
    }
    return sum ;
}

/*int waitcal(Process processes[], int indexp, int increase ) {
    processes[indexp].waitingTime += increase;
}*/

void printing_result(Process processes[], int n)
{
    int alltime = timeallprocesss(processes) ;
    int currentTime = 0;
    int indexP ;
    int endP = 0 ;
    for (int i = 0; i < 5; i++)
    {
        processes[i].processed = processes[i].burstTime ;
    }
    
    printf("\nSequence process is: ");
    for (int i = 0; i < alltime ; i++)
    {   for (int j = 0; j < 5 ; j++ )
        {   
        if ( processes[j].arrivalTime == i && processes[j].processed > 0)
            {
                if ( processes[j].processed > 5 ){
                    processes[j].processed -= 5 ;
                    stackmember[sp] += 5 ; 
                    currentTime++ ;
                }
                else{
                    stackmember[sp] += processes[j].processed ; 
                    currentTime ++ ;
                    processes[j].processed = 0 ;       
                } 
                Q[sp] = j ;
                sp++ ; 
                
            }
        else if ( i >= mostarrival(processes) && processes[j].processed > 0 && currentTime >=5 )
        {
                if ( processes[j].processed > 5 ){
                    processes[j].processed -= 5 ;
                    stackmember[sp] = 5 ; 
                }
                else{
                    stackmember[sp] = processes[j].processed ; 
                    processes[j].processed = 0 ;
                    
                } 
                Q[sp] = j ;
                sp++ ; 
        }
        }
    }
    for ( int i = 0; i < sp ; i++)
    {
        indexP = Q[i] ;
        printf("P%d", processes[indexP].index);
        if (i < sp-1 )
        {
            printf("->");
        }
    }

    for ( int i = 0; i < 5 ; i++){
        int sumtime = processes[ Q[0] ].arrivalTime ;
        int holderA = processes[i].arrivalTime ;
        for (int j = 0; j < sp ; j++)
        {
            if( processes[i].index == processes[ Q[j] ].index ){
                processes[i].waitingTime += ( sumtime - holderA  ) ;
                holderA = sumtime + stackmember[j] ;
            }
            sumtime += stackmember[j] ;
        }
    }
    
    printf("\n\nWait time of process (millisecond)\n");
    printf("|");
    for (int i = 0; i < n; i++)
    {
        printf(" P%d\t|  ", processes[i].index);
    }
    printf("\n|");
    for (int i = 0; i < n; i++)
    {
        // Ensure waiting time is non-negative
        printf(" %.2f\t|", (float)processes[i].waitingTime);
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
    }
    printf("\n\nAverage time is %.2f", sumwait(processes) / 5 );

    printf("\n\nTurnaround time\n");
    for (int i = 0; i < n; i++)
    {
        printf("|P%d = %d ms ", processes[i].index, processes[i].turnaroundTime);
    }
    printf("\n\n");
}

void nameuser(){
    printf("------------------------------------------------------------\n");
    printf("\n# Mr.Sarayut Meepanya ID:65543206080-5 Sec_01     #\n");
    printf("# OUTPUT LAB6 CPU Scheduling                       #\n");
    printf("## Round Robin ##\n");
    printf("\n------------------------------------------------------------");
}

int main()
{ 
    Process processes[] = {
        {1, 9, 1, 3},
        {2, 3, 1, 5},
        {3, 5, 3, 1},
        {4, 4, 4, 4},
        {5, 2, 7, 2},
    };

    nameuser();
    int n = sizeof(processes) / sizeof(processes[0]);

    printing_result(processes, n);

    return 0;
}