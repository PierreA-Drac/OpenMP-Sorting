#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

/* Parameters. */

/** Number of tables (a.k.a. blocks). */
static int N;
/** Size of one table (one block). */
static int K;


void tri(double *tab, int size);
void generator(double tab[], int size);
void tri_merge(double *tab1, double *tab2, int size);

int main(int argc, char *argv[])
{
    /* Initialize parameters of the algorithm. */
    if (argc <= 2)
        return fprintf(stderr, "Usage: %s [NUMBER OF BLOCKS] [SIZE OF ONE BLOCK]\n", argv[0]), 1;
    if ((N = atoi(argv[1])) < 1 || (K = atoi(argv[2])) < 1)
        return fprintf(stderr, "Usage: %s [NUMBER OF BLOCKS > 0] [SIZE OF ONE BLOCK > 0]\n", argv[0]), 1;
    srand(time(NULL));

    /* Database to sort: N tables of K random elements each. */
    double blocks[N][K];
    for (int i = 0; i < N; i++)
        generator(blocks[i], K);
        
    
    for (int i = 0; i < N; i++)
        tri(blocks[i],K);
  
    tri_merge(blocks[0],blocks[1],K);
    
    
    return 0;
}

/**
 * Fill a table with random values.
 * @param tab the table to fill.
 * @param size the size of the table.
 */
void generator(double tab[], int size)
{
    for (int i = 0; i < size; i++)
        tab[i] = rand()/3.33; /* Generate real numbers. */
}

/**
 * Bubble sort
 */
void tri(double *tab, int size)
{
    int i,j=0, test=1;
    double tmp;
    
    while(test)
    {
        test=0;
        for(i=0;i<size-j;i++)
        {
            if(tab[i+1]<tab[i])
            {
                tmp=tab[i];
                tab[i]=tab[i+1];
                tab[i+1]=tmp;
                test=1;
            }
         }
      }
}


/**
 * Merge 2 table 
 */
void tri_merge(double *tab1, double *tab2, int size)
{
    double tmp1[size], tmp2[size];
    int count1=0, count2=0;
   
    for(int i=0;i<size;i++)
    {
        tmp1[i]=tab1[i];
        tmp2[i]=tab2[i];
    }
    
    for(int k=0;k<size;k++)
    {
        if( (tmp1[count1]<tmp2[count2] && count1<size) || count2>=size) 
        {
            tab1[k]=tmp1[count1];
            count1++;
        }
        else
        {
            tab1[k]=tmp2[count2];
            count2++;
        }
    }
    
    for(int k=0;k<size;k++)
    {
        if( (tmp1[count1]<tmp2[count2] && count1<size) || count2>=size ) 
        {
            tab2[k]=tmp1[count1];
            count1++;
        }
        else
        {
            tab2[k]=tmp2[count2];
            count2++;
        }
    }
    
    
}

