#include <stdio.h>
#include <stdlib.h>
/**
 * This will return the new word added
 */
char *add(char *name, int size){
    char *added = malloc((size + 1) * sizeof(char));
    for (int i = 0; i < size; i++){
        added[i] = name[i];
    }
    added[size] = '\0';
    return added;
}
/**
 * this will check if the character is a letter
 * @param l - the character
 * @return - if it is a letter
 */
int isLetter(char l){
    int c = (int)l;
    if  ((c < 91 && c > 64) || (c < 123 && c > 96)){
        return 1;
    }
    return 0;
}

/**
 * this will return the length of the word
 * @param word - the word we want to find the length of
 * @return - the length
 */
int length(char *word){
    int i = 0;
    char *c = word;
    while(*c != '\0'){
        c++;
        i++;
    }
    return i;
}


/**
 * This will return an array of strings from a file
 * @param f
 * @param initial
 * @param onlyWord
 * @return
 */
char **increaseSize(char ** original, int newSize, int oldSize){
    char **new = malloc((newSize+1) * sizeof(char *));
    for (int i = 0; i < newSize && i < oldSize; i++){
        new[i] = original[i];
    }
    free(original);
    new[newSize] = '\0';
    return new;
}


/**
 * this will compare two strings
 * @param nameOne - StringA
 * @param nameTwo - StringA
 * @return - this will return whether they are the same or not
 */
int compare(char *nameOne, char *nameTwo){

    int firstLength = length(nameOne);
    int secondLength = length(nameTwo);
    int run;
    if (secondLength > firstLength){
        run = firstLength;
    }else{
        run = secondLength;
    }

    for (int i = 0; i < run; i++){
        if(nameOne[i] != nameTwo[i]){
            if((int)nameOne[i] < (int)nameTwo[i]){
                return 1;
            }else{
                return 0;
            }
        }
    }
    if (secondLength > firstLength){
        return 1;
    }
    return 0;
}

/**
 * this will swap the words a and b
 */
void swap(char** a, char** b){
    char *t = *a;
    *a = *b;
    *b = t;
}

/**
 * this will make quick sort work
 * this will split the array into two differnet lists and will than recall quicksort
 * @return
 */
int partition (char **arr, int low,int high){
    char *pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++){
        if (compare(arr[j], pivot) == 1){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);
    return (i+1);
}

/**
 * this is quick sort method which will recursively call itself
 */
void quickSort( char **arr, int low,int high){
    if (low < high){

    int pi = partition(arr, low, high);

    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
    }
}

/**
 * this is the main class
 * here we will read from the names file and write to another file
 * we use malloc to make the memory dynamic
 */
int main() {
    FILE *file  = fopen("names.txt", "r");


    if (file == NULL) {
        printf("no file found");
        exit(1);
    }


    int initial = 2000;
    char **names = (char**)malloc((initial)*sizeof(char*));
    char *currentName = malloc(20 * sizeof(char));
    int wordCounter = 0;
    int letterCounter = 0;
    int longest =0;
    int nextC = fgetc((FILE *) file);
    char c ;
    while (nextC != EOF) {
        c = (char) nextC;
        if (isLetter(c) == 1) {
            currentName[letterCounter++] = c;
        } else if (letterCounter > 0) {
            if (wordCounter >= initial-1){
                names = increaseSize(names, initial+1000, initial);
                initial = initial + 1000;
            }
            if(letterCounter > longest){
                longest = letterCounter;
            }

            names[wordCounter++] = add(currentName,letterCounter);
            letterCounter = 0;
        }
        nextC = getc(file);
    }
    fclose((FILE *) file);
    free(currentName);
    names = increaseSize(names, wordCounter, initial);

    quickSort(names, 0, wordCounter-1);

    FILE *file2  = fopen("quicksort.txt", "w");
    if (file2 == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    fprintf(file2, "\"");
    fprintf(file2, "%s", names[0]);
    for(int i = 1; i < wordCounter; i++) // Prints for formatting
    {
        fprintf(file2, "\",\"");
        fprintf(file2, "%s", names[i]);
    }
    fprintf(file2, "\"");
    fclose(file2);
}

