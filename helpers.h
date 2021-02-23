#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*  helpers.h
    Author: Alif Merchant
    Id: 1113741
    email: amerch04@uoguelph.ca  
*/

#define SIZE 50000

//Inversion helpers
int* copy(int array[], int left, int right);


//ConvexHull helpers
typedef struct Point{
    double x;
    double y;
} Point;

void print(Point **extreme, int count);
void qSort(Point **arr, int low, int high);
int isSame(Point *first, Point*second);
double distance(Point *a,Point *b);
int insertToSet(Point **extreme, int n, Point *key);

void freePoints(Point **array, int size);

#endif
