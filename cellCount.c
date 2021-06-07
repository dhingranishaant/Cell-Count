#include<stdio.h>
#include<stdlib.h>
#define IMAGE_SIZE 10

int qcount[100] = {0};
int frontcount = 0;
int rearcount = -1;
int itemcount = 0;
int count = 1;
int qx[IMAGE_SIZE], qy[IMAGE_SIZE];
int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0},
    dy[8] = {1, 0, -1, 1, 1, 0, -1, -1};
int ind = 0; //for qx and qy
int frontqx = 0;
int frontqy = 0;
int rearqx = -1;
int rearqy = -1;
int itemCountqx = 0;
int itemCountqy = 0;


// this function prints the array
void printImgArray(int array[IMAGE_SIZE][IMAGE_SIZE])
{
  
    printf("------ Image Contents -------\n");
    int i, j;
    for (i=0; i<IMAGE_SIZE; i++)
    {
    for (j=0; j<IMAGE_SIZE; j++)
        printf("%02d, ",array[i][j]);
    printf("\n");
    }
    printf("-----------------------------\n");
}

/**
* This function checks if the index parsed to it is valid or not.
* This helps compiler to know if the search continues or not. 
* returns 1 if i, j is a valid index in the image, else returns 0.
*/
int checkIndex(int i, int j){
    return i >= 0 && j >= 0 && i < IMAGE_SIZE && j < IMAGE_SIZE;
}

/** This function helps identify groups of 1's as a unique number.
* Algorithm used is Depth First Search. This function marks one position visited
* and then visits the adjacent positions of the position we first visited.
* This is a recursive implementation. 
*/

void distinctCount(int image[IMAGE_SIZE][IMAGE_SIZE], int i, int j, int copyArray[IMAGE_SIZE][IMAGE_SIZE], int counter){
    copyArray[i][j] = 1;
    image[i][j] = counter;

    int new_i, new_j;
    for(new_i = -1; new_i < 2; new_i ++){
        for(new_j = -1; new_j < 2; new_j++){
            if(new_i != 0 || new_j != 0){
                if(checkIndex(i + new_i, j + new_j)){
                    if(copyArray[i + new_i][j + new_j] != 1 && image[i + new_i][j + new_j] != 0){
                        distinctCount(image, i + new_i , j + new_j, copyArray, counter);
                    }
                }
            }
        }
    }  
}

/**
 * This function counts the number of distinct 
 * number (i.e. the number of cells)
 *
 * feel free to add auxiliary data structures and helper functions
 **/

/**
* This function is a helper function for "cellCount()".
* It checks whether the element exists in the queue or not. 
* Array Implementation of Queues is mainly done for bonus questions
* but also used in Task 1.2 and Task 2.2 
*/
int isElementInQueue(int e) {
    int flag = 0;
    int i;

    for (i = 0; i < 100; i++) {
        if (qcount[i] == e) {
            flag = 1;
            break;
        }
    }

    if (flag) {
        return 1;
    }
  
    return 0;
}

/**
 * This function colors each cell with a unique color
 * (i.e., unique number).
 * This implementation of cellCount works both for Task 1.2 and BONUS question.
 **/
int cellCount(int image[IMAGE_SIZE][IMAGE_SIZE]) {
    int i, j;
    for (i = 0; i < IMAGE_SIZE; i++) {
        for (j = 0; j < IMAGE_SIZE; j++) { 
            if (isElementInQueue(image[i][j]) == 0) {
                qcount[++rearcount] = image[i][j];
                itemcount++;
            }
        }
    }

    return itemcount;
}

/**
 * This function colors each blood cell with a unique color
 * (i.e. unique number)
 * Hint: scan the array element by element, and explore each element as much as possible, 
 * when come to an already labelled one, relabell the array to form larger cell
 * 
 * feel free to add auxiliary data structures and helper functions
 **/
void color(int image[IMAGE_SIZE][IMAGE_SIZE])
{
    //initializing an array copyArray with all zeroes to check for visited positions. 
    int copyArray[IMAGE_SIZE][IMAGE_SIZE] = {0};
    int i, j;

    // going to all adjacent positions of one position and running distinctCount function 
    int counter = 1;
    for(i = 0; i < IMAGE_SIZE; i++){
        for(j = 0; j < IMAGE_SIZE; j++){
            if (copyArray[i][j] == 0 && image[i][j] != 0){
                distinctCount(image, i, j, copyArray, counter);
                counter++;
            }
        }
    }
}

/********************************************************************************/
//the function and all the helper functions (if any) should use pointer notation, 
// instead of array index notation []. It is okey to use [] only when declaring extra arrays

/**
* This is a helper function for "colorPtr()".
* This function helps in grouping cells and works recursively using pointers.
* This function checks for 1s in the 2D array given and it's adjacent elements through recursion. 
*/
void distinctCountPointer(int * image, int i, int j, int * copyArray, int counter){  
    *(copyArray + i*IMAGE_SIZE + j) = 1;
    *(image + i*IMAGE_SIZE + j) = counter;

    int new_i, new_j;
    for(new_i = -1; new_i < 2; new_i ++){
        for(new_j = -1; new_j < 2; new_j++){
            if(new_i  != 0 || new_j != 0){
                if(checkIndex(i + new_i, j + new_j)){
                    if(*(copyArray + (i + new_i) * IMAGE_SIZE + (j + new_j)) !=1 
                        && *(image + (i + new_i) * IMAGE_SIZE + (j + new_j)) !=0){
                        distinctCountPointer(image, i+new_i , j+new_j, copyArray, counter);
                    }
                }
            }
        }
    }
}

//the function and all the helper functions (if any) should use pointer notation, 
// instead of array index notation []. It is okey to use [] only when declaring extra arrays
/**
 * This function colors each cell with a unique color
 * (i.e., unique number).
 **/
int cellCountPtr(int* image) {
    int i, j;
    for (i = 0; i < IMAGE_SIZE; i++) {
        for (j = 0; j < IMAGE_SIZE; j++) { 
            if (isElementInQueue(*(image + i*IMAGE_SIZE + j)) == 0) {
                *(qcount + (++rearcount)) = *(image + i*IMAGE_SIZE + j);
                itemcount++;
            }
        }
    }

    return itemcount;
}
void colorPtr(int* image){
    // insert your code for task 2.1 here
    int copyArray[IMAGE_SIZE][IMAGE_SIZE];
    int i, j;

    for(i = 0; i < IMAGE_SIZE; i++)
        for(j = 0; j < IMAGE_SIZE; j++){
            *(*(copyArray + i) + j) = 0;
        }

    // going to all adjacent positions and running distinctCount function 
    int counter = 1;
    for(i = 0; i < IMAGE_SIZE; i++){
        for(j = 0; j < IMAGE_SIZE; j++){
            if(*(*(copyArray + i) + j) != 1 && *(image + i * IMAGE_SIZE + j) !=0){
                distinctCountPointer(image, i, j, copyArray, counter);
                counter++;
            }
        }
    }
}

/********************************************************************************/

/**
* Added the following helper functions for Array Implementation of Queues to complete BONUS question.
*   insertInQueue()   Adding respective elements in queues "qx" and "qy" at their rear positions.
*   popQueueX()       Remove the front element from the queue "qx".
*   popQueueY()       Remove the front element from the queue "qy".
*   isQueueEmpty()    Checks whether the queue qx or qy is empty or not. Returns 1 if it is or 0 if it is not.
*/

void insertInQueue(int i_ele, int j_ele) {
    if (rearqx == IMAGE_SIZE - 1 || rearqy == IMAGE_SIZE - 1) {
        rearqx = -1;
        rearqy = -1;
    }

    qx[++rearqx] = i_ele;
    qy[++rearqy] = j_ele;

    itemCountqx++;
    itemCountqy++;
}

int popQueueX() { 
    int element = qx[frontqx++];

    if (frontqx == IMAGE_SIZE) {
        frontqx = 0;
    }

    itemCountqx--;

    return element;
}

int popQueueY() {       
    int element = qy[frontqy++];

    if (frontqy == IMAGE_SIZE) {
        frontqy = 0;
    }

    itemCountqy--;

    return element;
}

int isQueueEmpty() {
    if (itemCountqx == 0 || itemCountqy == 0) {
        return 1;
    }

    return 0;
}


/**
* This is a helper function of "colorRecursively()".
* Task 1 (and also Task 2) has been done recursively which is why 
* function "colorRecursively()" is being implemented non-recursively
* to be eligible for the bonus part. 
*
* This function runs iteratively and checks for groups of 1s and assign them a unique value.
* Array Implementation of Queues Data Structure has been used to complete this bonus question.
* The auxilary queue data structure helper functions have been added above.  
*/
int distinctCountNonRecursive(int i, int j, int ind, 
    int copyArray[IMAGE_SIZE][IMAGE_SIZE], int image[IMAGE_SIZE][IMAGE_SIZE]) {
    insertInQueue(i, j);
    copyArray[i][j] = 1;
    image[i][j] = count;

    while (!isQueueEmpty()) {    
        int cur_x = popQueueX();
        int cur_y = popQueueY();

        //this iteration is for 8 adjacent directions from where 1 is found.
        for (int i=0; i<8; i++){
            int new_x = cur_x + dx[i];
            int new_y = cur_y + dy[i];
            if (new_x >= 0 && new_x < IMAGE_SIZE && new_y >= 0 && new_y < IMAGE_SIZE) {
                if (copyArray[new_x][new_y] != 1 && image[new_x][new_y] != 0) {
                    copyArray[new_x][new_y] = 1;
                    insertInQueue(new_x, new_y);
                    image[new_x][new_y] = count;
                }
            }
        }
    }

   return 0;
}

/**
 * This function colors each cell with a unique color
 * (i.e., unique number).
 **/

int colorRecursively(int image[IMAGE_SIZE][IMAGE_SIZE]) {
    int copyArray[IMAGE_SIZE][IMAGE_SIZE] = {0};
    int i, j;

    for (i = 0; i < IMAGE_SIZE; i++) {
        for (j = 0; j < IMAGE_SIZE; j++) {
            if (image[i][j] != 0 && copyArray[i][j] != 1) {
                distinctCountNonRecursive(i, j, ind, copyArray, image);
                count++;
            }
        }
    }

    return 0;
}
 

#ifndef __testing
int main(){

    // DO not change anything in main(), it will confuse the
    // auto-checker.  
    puts("testing the code with color() function");
    int count = 0;
    int cellImg[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
                       {1,0,1,1,0,0,1,1,0,1},\
                       {1,0,0,1,1,0,1,1,0,1},\
                       {1,1,0,0,0,0,0,0,0,0},\
                       {1,0,0,1,1,1,0,0,1,0},\
                       {0,0,0,0,1,0,0,1,1,0},\
                       {0,0,1,0,0,1,0,1,0,0},\
                       {0,0,1,1,0,0,1,0,0,0},\
                       {0,0,1,0,0,0,0,0,1,1},
                       {0,1,1,0,0,0,1,1,1,1}};

    printImgArray(cellImg);
    color(cellImg);
    printImgArray(cellImg);
    count=cellCount(cellImg);
    printf("Total number of cells in the image: %d\n",count);
 

    puts("Testing the code with colorPtr");
    int cellImg_[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
                       {1,0,1,1,0,0,1,1,0,1},\
                       {1,0,0,1,1,0,1,1,0,1},\
                       {1,1,0,0,0,0,0,0,0,0},\
                       {1,0,0,1,1,1,0,0,1,0},\
                       {0,0,0,0,1,0,0,1,1,0},\
                       {0,0,1,0,0,1,0,1,0,0},\
                       {0,0,1,1,0,0,1,0,0,0},\
                       {0,0,1,0,0,0,0,0,1,1},
                       {0,1,1,0,0,0,1,1,1,1}};

    int* ptr = cellImg_;
    printImgArray(ptr);
    colorPtr(ptr);
    printImgArray(ptr);
    count=cellCountPtr(ptr);
    printf("Total number of cells in the image: %d\n",count); 
    
    puts("Testing the code with colorRecursively");
    int cellImg__[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
                       {1,0,1,1,0,0,1,1,0,1},\
                       {1,0,0,1,1,0,1,1,0,1},\
                       {1,1,0,0,0,0,0,0,0,0},\
                       {1,0,0,1,1,1,0,0,1,0},\
                       {0,0,0,0,1,0,0,1,1,0},\
                       {0,0,1,0,0,1,0,1,0,0},\
                       {0,0,1,1,0,0,1,0,0,0},\
                       {0,0,1,0,0,0,0,0,1,1},
                       {0,1,1,0,0,0,1,1,1,1}};
    printImgArray(cellImg__);
    colorRecursively(cellImg__);
    printImgArray(cellImg__);
    count=cellCount(cellImg__);
    printf("Total number of cells in the image: %d\n",count);
    return 0;
}
#endif