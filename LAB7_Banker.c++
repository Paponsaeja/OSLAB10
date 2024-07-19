#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n, m, i, j, k;
    cout << "how many Process you want " << endl ;
    cin >> n ;
    cout << "\n" << endl ;
    m = 3; // Number of resources
    int Avari[m]  ;
    
    cout << "Enter Instance avariable -> A B C" << endl ;
    for (i = 0; i < m ; i++ ) {
        cin >> Avari[i] ;
    }
    
    int max[n][m] ;
    int alloc[n][m] ;
    

    // Input for Allocation Matrix
    cout << "Enter Allocation Matrix (A B C format) for each process (P0 to P4):" << endl;
    for (i = 0; i < n; i++)
    {
        printf("Enter allocation for P%d: ", i);
        scanf("%d %d %d", &alloc[i][0], &alloc[i][1], &alloc[i][2]);
    }

    // Input for MAX Matrix
    cout << "Enter MAX Matrix (A B C format) for each process (P0 to P4):" << endl;
    for (i = 0; i < n; i++)
    {
        printf("Enter MAX for P%d: ", i);
        scanf("%d %d %d", &max[i][0], &max[i][1], &max[i][2]);
    }
    /*
    int alloc[n][m] = { { 8, 5, 3 }, // P0 // Allocation Matrix
                        { 1, 3, 5 }, // P1
                        { 1, 3, 0 }, // P2
                        { 0, 1, 3 } }; // P3

    int max[n][m] = { { 10, 9, 5 }, // P0 // MAX Matrix
                    { 12, 7, 7 }, // P1
                    { 3, 6, 9 }, // P2
                    { 8, 13, 5 } }; // P3
    */
    int sumAlloc[m] = {0};
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            sumAlloc[j] += alloc[i][j];
        }
    }

    int avail[m];
    int ava[m] ;
    for (int y = 0; y < m; y++)
    {
        avail[y] = Avari[y] - sumAlloc[y];
        ava[y] = avail[y] ;
    }

    int carry[n][m] ;  // carry value of avail into array 5*3
    int state = 0 ; 
    int keepstate[n] ;
    int keepneed[m] ;

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++)
    {
        f[k] = 0;
    }

    int need[n][m];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    // Display header
    cout << "-------------------------------------------------------------------------------------------------------" << endl;
    cout << setw(8) << "Process" << setw(9) << "Alloc" << setw(15) 
    << "Max" << setw(16) << "Need" << setw(17) << "Avail" << setw(10)  << setw(12) << "state" << endl;

    cout << setw(11) 
    << "A" << setw(4) << "B" << setw(4) << "C" 
    << setw(8) << "A" << setw(4) << "B" << setw(4) << "C" 
    << setw(8) << "A" << setw(4) << "B" << setw(4) << "C" 
    << setw(8) << "A" << setw(4) << "B" << setw(4) << "C" << endl;
    cout << "-------------------------------------------------------------------------------------------------------" << endl;

    int y = 0;
    for (k = 0; k < n; k++)
    {
        int flag = 0;
        for (i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {
                flag = 1;  // Set flag to 1 if there's at least one process that can be allocated resources
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 0;  // Reset flag to 0 if the process cannot be allocated resources
                        break;
                    }
                }

                if (flag == 1)
                {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                    {
                        avail[y] = avail[y] + alloc[i][y];
                        carry[i][y] = avail[y];
                    }
                    f[i] = 1;
                    state += 1;
                    keepstate[i] = state;
                    
                    // เก็บค่า  need ของ process ที่ได้ทรัพยากรตัวแรกเอาไว้
                    if (state == 1 ) {
                        for(y = 0; y < m; y++) {
                            keepneed[y] = need[i][y] ;
                        }
                    }

                }
            }
        }

        // If no process can be allocated resources, set state column to "NULL"
        if (flag == 0)
        {
            for (i = 0; i < n; i++)
            {
                if (f[i] == 0)
                {
                    keepstate[i] = -1; // Set state to -1 to indicate deadlock
                }
            }
        }
    }

    for (k = 0; k < n; k++)
    {
        cout << setw(4) << "P" << k
            << setw(6) << alloc[k][0] << setw(4) << alloc[k][1] << setw(4) << alloc[k][2]
            << setw(8) << max[k][0] << setw(4) << max[k][1] << setw(4) << max[k][2]
            << setw(8) << need[k][0] << setw(4) << need[k][1] << setw(4) << need[k][2]
            << setw(8) << (keepstate[k] != -1 ? to_string(carry[k][0]) : " ") // condition deadlock หรือไม่ หากติดให้โชว carry[k][0] = " "
            << setw(4) << (keepstate[k] != -1 ? to_string(carry[k][1]) : " ") // หากไม่ติดdeadlock ให้ carry[k][0] = ตัวเลขที่เก็บไว้และไม่ต้องแสดง " " ;
            << setw(4) << (keepstate[k] != -1 ? to_string(carry[k][2]) : " ")
            << setw(8) << (keepstate[k] != -1 ? to_string(keepstate[k]) : "NULL") << endl;
    }

    int flag = 1;

    // To check if sequence is safe or not
    for (int i = 0; i < n; i++)
    {
        if (f[i] == 0)
        {
            flag = 0;
            printf("avariable drives = ( %d , %d , %d )\n", ava[0],ava[1],ava[2] ) ;
            cout << "If grant last drive to any process may get deadlock = UNSAFE STATE";
            cout << "*ALL PROCESS DON'T RUN TO COMPLETE " << endl ;
            break;
        }
    }

    if (flag == 1)
    {
        cout << "-------------------------------------------------------------------------------------------------------" << endl;
        printf("avariable drives = ( %d , %d , %d )\n", ava[0],ava[1],ava[2] ) ;
        printf(" Frist state allocate (%d,%d,%d) drives to P[%d]\n\n", keepneed[0] , keepneed[1], keepneed[2] ,ans[0]) ;
        for(i = 0; i < n; i++){
            printf(" P[%d] complete and release ", ans[i] );
            for(y = 0 ; y < m; y++ ) {
                printf("%d,", carry[ans[i]][y]) ;
            }
            printf(" Available drives") ;
            cout << "\n" << endl ;
        }
        cout << "\n" << endl ;
        cout << " sequence of prcess is => " << endl ;
        for (i = 0; i < n - 1; i++)
            cout << " P" << ans[i] << " ->";
        cout << " P" << ans[n - 1] << endl;
        cout << "*ALL PROCESS RUN TO COMPLETE = SAFE STATE \n " << endl ;
    }
    return (0);
}
