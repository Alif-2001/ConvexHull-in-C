/*  P1.1
    Author: Alif Merchant
    Id: 1113741
    email: amerch04@uoguelph.ca  
*/
#include "helpers.h"

int readFile(char *filename, int *array);
int countInversionsBF(int array[], int size);

int main(int argc, char **argv) {

    if(argc < 2){
        printf("Usage: ./P11 data.txt\n");
        return 0;
    }

    clock_t t;
    int * array = malloc(sizeof(int) * SIZE);
    int size = readFile(argv[1], array);

    t = clock();
    int count = countInversionsBF(array,size);
    t = clock() - t;
    printf("Time taken with brute force: %f seconds\n", (double)((double)t/CLOCKS_PER_SEC));
    printf("result: %d\n", count);
    
    free(array);
    return 0;
}

/*  This function reads data into the array of integers
from the given file name.  */
int readFile(char *filename, int *array){
    FILE * fp;
    fp = fopen(filename,"r");
    int i = 0;
    if(fp != NULL){
        while(fscanf(fp, "%d", &array[i]) != EOF){
            //printf("%d\n", array[i]);
            i++;
        }
    }
    fclose(fp);
    return i;
}

/*  This is a brute force algorithm that checks
    for inversions in an array of integers.
    It returns the total number of recursion.*/
int countInversionsBF(int array[], int size){
    int count = 0;
    for(int i = 0; i < size-1; i++){
        for(int j = i+1; j < size; j++){
            if(array[i]> array[j]){
                count++;
            }
        }
    }
    return count;
}
