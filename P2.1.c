/*  P2.1
    Author: Alif Merchant
    Id: 1113741
    email: amerch04@uoguelph.ca  
*/
#include "helpers.h"

int readFile(char *filename, Point **array);
int convBF(Point **array, Point **extreme, int size);

int main(int argc, char **argv) {

    if(argc < 2){
        printf("Usage: ./P21 data.txt\n");
        return 0;
    }

    clock_t t;
    Point **array = malloc(sizeof(Point *) * SIZE);
    Point **extreme = malloc(sizeof(Point *) * SIZE);
    int size = readFile(argv[1],array);

    t = clock();
    int total = convBF(array, extreme, size);
    t = clock() - t;

    print(extreme,total);
    printf("Total number of extreme points: %d\n",total);
    printf("Time taken with Brute Force: %f seconds\n", (double)((double)t/CLOCKS_PER_SEC));

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

/*  This is a brute force algorithm to find the extreme points.  */
int convBF(Point **array, Point **extreme, int size){
    int n = 0;
    for(int i = 0; i < size-1; i++){
        for(int j = i+1; j<size; j++) {
            if(!isSame(array[i],array[j])){     //to make sure these two points are not the same.
                double a = array[j]->y - array[i]->y;
                double b = array[i]->x - array[j]->x;
                double c = ((array[i]->x) * (array[j]->y)) - ((array[i]->y) * (array[j]->x));
                int signChange = 0;
                Point *close = NULL;
                Point *far = NULL;
                int l = 0;
                int r = 0;
                for(int k = 0; k < size; k++){      //check if all the points are on the same side of the line array[i] -> array[j]
                    if(!isSame(array[k],array[i]) && !isSame(array[k],array[j])){
                        double check = ((a * array[k]->x) + (b * array[k]->y) - c);
                        if(check > 0){      //if point is on right, increment r
                            r++;
                        }
                        if(check < 0){      //if point is on left, increment l
                            l++;
                        }

                        if(check == 0){     //if the point is on the same line (collinear), then we take the 2 points with the biggest distance between each other.
                            if(distance(array[i],array[j]) > distance(array[j],array[k]) && distance(array[i],array[j]) > distance(array[k],array[i])){
                                close = array[i];
                                far = array[j];
                            }else if(distance(array[j],array[k]) > distance(array[i],array[j]) && distance(array[j],array[k]) > distance(array[k],array[i])){
                                close = array[j];
                                far = array[k];
                            }else{
                                close = array[k];
                                far = array[i];
                            }
                        }

                        if(l != 0 && r != 0){       //if l and r were incremented, that means that the points are not
                            k = size+1;             //on the same side of the line.
                            signChange = 1;
                        }
                    }
                }
                if(close != NULL && close != NULL && !signChange){      //if all the points are on one side of the line, then add the vertices to the hull
                    n = insertToSet(extreme, n, close);
                    n = insertToSet(extreme, n, far);
                }else if(!signChange){
                    //printf("%f, %f -> %f, %f\n", array[i]->x,array[i]->y, array[j]->x, array[j]->y);
                    n = insertToSet(extreme, n, array[i]);
                    n = insertToSet(extreme, n, array[j]);
                }
            }
        }
    }
    qSort(extreme, 0, n-1);
    return n;
}

