/*  helpers.c
    Author: Alif Merchant
    Id: 1113741
    email: amerch04@uoguelph.ca  
*/

#include "helpers.h"


//Inversion helpers

/*  This function copies elements from the 
    array of integers from index left to right.  */
int *copy(int array[], int left, int right){
    int *copy = malloc(sizeof(int)* (right-left));
    int j = 0;
    for(int i=left; i<right; i++){
        copy[j] = array[i];
        j++;
    }
    return copy;
}


//ConvexHull helpers

/*  This function prints out all the element
    in the array of Points.  */
void print(Point **extreme, int count){
    for(int i = 0; i < count; i++){
        printf("(%.6g, %.6g)\n", extreme[i]->x, extreme[i]->y);
    }
}

/*  This function swaps two Points datas. */
void swap(Point* a, Point* b){ 
    Point t = *a; 
    *a = *b; 
    *b = t; 
} 

/*  This function takes a pivot and places
    all smaller Points to the left and all
    greater Points to the right. (part of
    quick sort algorithm)  */
int part (Point **arr, int l, int r){ 
    double p = arr[r]->x; 
    int i = (l - 1);   
  
    for (int j = l; j <= r - 1; j++) {  
        if (arr[j]->x < p) { 
            i++;
            swap((arr[i]), (arr[j])); 
        } 
    } 
    swap((arr[i + 1]), (arr[r])); 
    return (i + 1); 
}

/*  This function implements quickSort.
    l is the starting index, and r is the
    ending index.  */
void qSort(Point **arr, int l, int r){ 
    if (l < r){
        int pi = part(arr, l, r); 
        qSort(arr, l, pi - 1); 
        qSort(arr, pi + 1, r); 
    } 
}

/*  This function takes 2 points and returns
    1 if they are the same (same x and same y)
    or 0 if not.  */
int isSame(Point *first, Point*second){
    return (first->x == second->x && first->y == second->y);
}

/*  This function returns the distance between 2 points
    a and b.    */
double distance(Point *a,Point *b){
    double distance = sqrt((b->x - a->x)*(b->x - a->x) + (b->y - a->y) * (b->y - a->y));
    return distance;
}

/*  This function inserts a Point into an array of Points only if 
    the element doesn't already exist.    */
int insertToSet(Point **extreme, int n, Point *key) {
  
    int i;
    int dup = 0;
    if(n == 0){
        extreme[n] = key;
        return 1;
    }else{
        for(i = 0; i < n ; i++){    //check for duplicates
            if(extreme[i]->x == key->x && extreme[i]->y == key->y){
                dup = 1;
            }
        }
        
        if(dup){
            return n;
        }else{
            extreme[n] = key;
            return (n + 1);   
        }
    }
    return n;
}

/*  This function frees all the Point in the array
    of points.   */
void freePoints(Point **array, int size){
    for (int i = 0; i < size; i++){
        free(array[i]);
    }
    free(array);
}
