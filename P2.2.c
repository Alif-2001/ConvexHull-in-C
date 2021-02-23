/*  P2.2
    Author: Alif Merchant
    Id: 1113741
    email: amerch04@uoguelph.ca  
*/
#include "helpers.h"

int convDC(Point **array, Point **extreme, int size);
int readFile(char *filename, Point **array);
int quickHull(Point **array, Point **extreme, Point *first, Point *second, int count, int size);
int createSeg(Point **array, Point **seg, Point * first, Point * second, int size);
Point *findFar(Point **array, Point *first, Point *second, int size);

int main(int argc, char **argv) {

    if(argc < 2){
        printf("Usage: ./P22 data.txt\n");
        return 0;
    }

    clock_t t;
    Point **array = malloc(sizeof(Point *) * SIZE);
    Point **extreme = malloc(sizeof(Point *) * SIZE);
    int size = readFile(argv[1],array);

    t = clock();
    int total = convDC(array, extreme, size);
    t = clock() - t;

    print(extreme,total);
    printf("Total number of extreme points: %d\n",total);
    printf("Time taken with Divide and Conquer: %f seconds\n", (double)((double)t/CLOCKS_PER_SEC));
    
    freePoints(array, size);
    free(extreme);
    return 0;
}

/*  This function reads data into the array of points
from the given file name.  */
int readFile(char *filename, Point **array){
    FILE * fp;
    fp = fopen(filename,"r");
    int i = 0;
    if(fp != NULL){
        double x;
        double y;
        while(fscanf(fp, "%lf %lf", &x, &y) != EOF){
            array[i] = malloc(sizeof(Point));
            array[i]->x = x;
            array[i]->y = y;
            i++;
        }
    }
    fclose(fp);
    return i;
}

int quickHull(Point **array, Point **extreme, Point *first, Point *second, int count, int size);

/*  This function takes in an array of Points, an empty 
    array of extreme Points and the size of the array. It sorts
    the points in the first array, takes the smallest (a) and the biggest (b)
    number in it and divides the array into 2 groups seperated
    by the line created by a and b. Those 2 groups are then passed
    to the quickHull function. The function returns the total number
    of extreme points that were found.  */
int convDC(Point **array, Point **extreme, int size){
    int count = 0;
    qSort(array, 0, size-1);
    Point *low = array[0];
    Point *high = array[size-1];
    count = insertToSet(extreme, count, low);
    count = insertToSet(extreme, count, high);
    Point **seg1 = malloc(sizeof(Point *)*size);
    Point **seg2 = malloc(sizeof(Point *)*size);
    int sizeSeg1 = createSeg(array, seg1, low, high, size);     //get points to the left of line first -> far
    int sizeSeg2 = createSeg(array, seg2,  high, low, size);    //get points to the left of line far -> second
    count = quickHull(seg1, extreme, low, high, count, sizeSeg1);
    count = quickHull(seg2, extreme, high, low, count, sizeSeg2);
    qSort(extreme, 0, count-1);
    //free segments

    free(seg1);
    free(seg2);

    return count;
}

/*  The quickHull function is recursive. Given two points (first and second), it
    looks for the farthest point to the left in the array of Points. Once the 
    point is found, it adds it to the list of extreme points. It then creates
    two groups of points (seg1 and seg2) that are on the left of the lines: 
    first -> far and far -> second. It calls itself and uses the 2 segments to
    look for extreme points. Thhe function returns the number of extreme points
    found.  */
int quickHull(Point **array, Point **extreme, Point *first, Point *second, int count, int size){
    if(size == 0){
        return count;
    }
    Point *far = findFar(array, first, second, size);           //get the farthest point to the left of line first -> second
    count = insertToSet(extreme, count, far);
    Point **seg1 = malloc(sizeof(Point *)*size);
    Point **seg2 = malloc(sizeof(Point *)*size);
    int sizeSeg1 = createSeg(array, seg1, first, far, size);    //get points to the left of line first -> far
    int sizeSeg2 = createSeg(array, seg2,  far, second, size);  //get points to the left of line far -> second
    count = quickHull(seg1, extreme, first, far, count, sizeSeg1);
    count = quickHull(seg2, extreme, far, second, count, sizeSeg2);
    
    free(seg1);
    free(seg2);
    return count;
}

/*  This function stores all the point to the left of the line first -> second into
    the array seg. It returns the number of points that were added to the array seg.  */
int createSeg(Point **array, Point **seg, Point * first, Point * second, int size){
    double a = second->y - first->y;
    double b = first->x - second->x;
    double c = ((first->x) * (second->y)) - ((first->y) * (second->x));
    int i = 0;
    for(int k = 0; k < size; k++){
        if(array[k] != first && array[k] != second){
            double check = (a * array[k]->x + b * array[k]->y - c);
            if(check < 0){      // point is to the left of the line
                seg[i] = array[k];
                i++;
            }
        }
    }
    return i;
}

/*  This function finds and returns the farthest point in the array of 
    Points that are to the left of the line first -> second.  */
Point *findFar(Point **array, Point *first, Point *second, int size){
    double far = 0;
    Point *farPoint = NULL;
    for(int k = 0; k < size; k++){
        if(array[k] != first && array[k] != second){
            double distance = (first->x) * (second->y) + (array[k]->x) * (first->y) +
                            (second->x) * (array[k]->y) - (array[k]->x) * (second->y) -
                            (second->x) * (first->y) - (first->x) * (array[k]->y);
            if(distance > 0){       // point is to the left of the line
                if(distance >= far){
                    far = distance;
                    farPoint = array[k];
                }
            }
        }
    }
    return farPoint;
}
