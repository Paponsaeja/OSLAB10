#include<stdio.h>

struct pageReplacement
{
    int page[4] ;
    int call ;
}typedef pr;

int process[19] = {2,1,2,3,7,6,2,3,4,2,1,5,6,3,2,3,6,2,1} ;
pr fifo[19] ;
pr lru[19] ;
pr optimal[19] ;

int prfifo() {
    int n = 0;
    int pointer = 0 ;
    int holder[4] ;
    int track = 0 ;
    for( int i = 0 ; i < 19 ; i++ ){
        fifo[i].call = process[i] ;
        for(int j = 0 ; j < 4 ; j++){
            if ( holder[j] == process[i] ){
                track = 1 ;
                break;
            }
        }
        if ( track == 1 )
        {
            for ( int j = 0; j < 4 ; j++)
            {
                fifo[i].page[j] = -1 ;
            }
        }
        if ( track == 0 )
        {
            
            if ( pointer == 4 ){
                pointer = 0 ;
            }
            holder[pointer] = process[i] ;
            if ( pointer != 4 )
            {   
                pointer++;
                n++ ;
            }
                for ( int j = 0; j < 4 ; j++)
            {
                if( j < n ){
                    fifo[i].page[j] =  holder[j];
                }
                else{
                    fifo[i].page[j] = -1 ;
                    
                }
            }
        }
        track = 0;
    }
    return n ;
}

int propt() {
    int n = 0;
    int pointer = 0 ;
    int holder[4] ;
    int takeout[4] = {0, 0, 0, 0} ;
    int track = 0 ;
    int mostop = 0 ;
    for( int i = 0 ; i < 19 ; i++ ){
        optimal[i].call = process[i] ;
        for(int j = 0 ; j < 4 ; j++){
            if ( holder[j] == process[i] ){
                track = 1 ;
                break;
            }
        }
        if ( track == 1 )
        {
            for ( int j = 0; j < 4 ; j++)
            {
                optimal[i].page[j] = -1 ;
            }
        }
        if ( track == 0 )
        {   
            for ( int j = 0; j < 4; j++)
            {   
                takeout[j] = 0;
                for ( int k = i; k < 19 ; k++)
                {
                    if ( process[k] == holder[j] ){
                        break;
                    }
                    takeout[j]++ ;
                }
            }
            mostop = 0 ;
            if ( n >= 4)
            {   for ( int j = 0; j < 4 ; j++)
                {   
                    if( mostop < takeout[j] ){
                        mostop = takeout[j] ;
                        pointer = j ;
                    }
                }
                holder[pointer] = process[i] ;
                n++ ;
            }
            else {
                holder[pointer] = process[i] ;
                pointer++ ;
                n++ ;
            }
                for ( int j = 0; j < 4 ; j++)
            {
                if( j < n ){
                    optimal[i].page[j] =  holder[j];
                }
                else{
                    optimal[i].page[j] = -1 ;
                    
                }
            }
        }
        
        track = 0;
    }
    return n ;
}

int prlru() {
    int n = 0;
    int pointer = 0 ;
    int holder[4] ;
    int takeout[4] = {0, 0, 0, 0} ;
    int track = 0 ;
    int mostlu = 0 ;
    for( int i = 0 ; i < 19 ; i++ ){
        lru[i].call = process[i] ;
        for ( int j = 0; j < 4; j++)
            {   
                takeout[j]++ ;
            }
        for(int j = 0 ; j < 4 ; j++){
            if ( holder[j] == process[i] ){
                track = 1 ;
                takeout[j] = 0 ;
                break;
            }
        }
        if ( track == 1 )
        {
            for ( int j = 0; j < 4 ; j++)
            {
                lru[i].page[j] = -1 ;
            }
        }
        if ( track == 0 )
        {   
            
            mostlu = 0 ;
            if ( n >= 4)
            {   for ( int j = 0; j < 4 ; j++)
                {   
                    if( mostlu < takeout[j] ){
                        mostlu = takeout[j] ;
                        pointer = j ;
                    }
                }
                holder[pointer] = process[i] ;
                takeout[pointer] = 0 ;
                n++ ;
            }
            else {
                holder[pointer] = process[i] ;
                takeout[pointer] = 0 ;
                pointer++ ;
                n++ ;
            }
                for ( int j = 0; j < 4 ; j++)
            {
                if( j < n ){
                    lru[i].page[j] =  holder[j];
                }
                else{
                    lru[i].page[j] = -1 ;
                    
                }
            }
        }
        
        track = 0;
    }
    return n ;
}

void  showdata( pr* prtype){
    for ( int i = 0; i < 19; i++)
    {
        printf("%d ", process[i]) ;
    }
    
    printf("\n----------------------------------------------------------\n") ;
    for ( int  i = 0; i < 4 ; i++)
    {
        for ( int j = 0; j < 19; j++)
        {   
            if (  prtype[j].page[i] == -1)
            {
                printf( "  ") ;
            }
            else{
                printf( "%d ", prtype[j].page[i] ) ;
            }
        }
        printf("\n") ;
    }
    printf("----------------------------------------------------------\n") ;
    for ( int i = 0; i < 19 ; i++)
    {
        printf( "%d ", prtype[i].call ) ;
    }
}

int main(){
    int dfifo = prfifo() ;
    printf( "Least Recently Used (FIFO) replacement\n" ) ;
    showdata( fifo ) ;
    printf("\t Page fault: %d\n", dfifo) ;
    int dlrp = prlru() ;
    printf( "\nLeast Recently Used (LRU) replacement\n" ) ;
    showdata( lru ) ;
    printf("\t Page fault: %d\n", dlrp) ;
    int dopt = propt() ;
    printf( "\nOptimal replacement \n" ) ;
    showdata( optimal ) ;
    printf("\t Page fault: %d\n", dopt) ;
    
}