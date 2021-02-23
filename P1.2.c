/*  P1.2
    Author: Alif Merchant
    Id: 1113741
    email: amerch04@uoguelph.ca  
*/

#include "helpers.h"

int readFile(char *filename, int *array);
int countInversionsDC(int array[], int size);
int countInversionMerge(int B[], int C[], int array[], int sizeOfB, int sizeOfC);

int main(int argc, char **argv) {

    if(argc < 2){
        printf("Usage: ./P12 data.txt\n");
        return 0;
    }

    clock_t t;
    int * array = malloc(sizeof(int) * SIZE);
    int size = readFile(argv[1], array);

    t = clock();
    int count = countInversionsDC(array,size);
    t = clock() - t;
    printf("Time taken with divide-and-conquer: %f seconds\n", (double)((double)t/CLOCKS_PER_SEC));
    printf("result: %d\n",count);
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

/*  This function is recursive. It takes in an array of integers
    and divides it into two halves. It would then call itself
    on the first half and then the second. The function keeps 
    doing that until there is only one item in the array. It then
    calls countInversionMerge which returns the number of inversions
    in both halves. This function returns the total number of inversions
    int the array.  */
int countInversionsDC(int *array, int size){
    int count = 0;
    if(size > 1){
        int mid = size/2;
        int* B = copy(array, 0, mid);
        int* C = copy(array, mid, size);
        count += countInversionsDC(B, mid);
        count += countInversionsDC(C, size-mid);
        count += countInversionMerge(B, C, array, mid, size-mid);
        free(B);
        free(C);
    }
    return count;
}

/*  This function sorts and add the number of inversions found in B and C  */
int countInversionMerge(int B[], int C[], int array[], int sizeOfB, int sizeOfC){
    int i = 0, j = 0, k = 0, count = 0;
    int p = sizeOfB;
    int q = sizeOfC;

    while(i < p && j < q){
        if(B[i] <= C[j]){
            array[k] = B[i];
            i++;
        }else{
            array[k] = C[j];
            j++;
            count += p - i;
        }
        k++;
    }

    while(i < p){
        array[k] = B[i];
        i++;
        k++;
    }

    while(j < q){
        array[k] = C[j];
        j++;
        k++;
    }
    return count;
}

