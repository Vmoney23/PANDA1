#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<time.h>
#include<math.h>
#include<ctype.h>

//a node in the linked list
typedef struct List {
    struct List *next;
    char word[20];
    int count;
    int number_of_words;
} list;

//reads in a word, if the file is at the end, adds the word EOF
void linkedListRead(FILE *book, char word[20]) {
    char c;
    if (fscanf(book, "%c", &c) != EOF) {
        char a[] = ". ,;:*!?'-\n\r\0";
        int i;
        i = 0;
        while (strchr(a, c) == 0) {
            word[i] = c;
            i++;
            if (fscanf(book, "%c", &c) == EOF)
                break;
        }
        word[i] = '\0';
    }
    else {
        strcpy(word, "EOF");
    }

}

//inserts a new new node called T for new_word, adds it before B
list *insert(char new_word[20], list *next_node) {
    list *new_node = calloc(1, sizeof(list));
    strcpy(new_node->word, new_word);
    new_node->count = 1;
    new_node->next = next_node;
    return new_node;
}

//adds a new node for new_word as the next of the list
list *add(list *old_list, char new_word[20]) {

    if (old_list == NULL) {
        
        return insert(new_word, NULL);
    }
    else {
        list *new_list;
        for (new_list = old_list; new_list->next != NULL; new_list = new_list->next) {
        }
        new_list->next = insert(new_word, NULL);
        return old_list;
    }
}

//This function takes the list and word to be searched for, and compares the
//values in the list with the word to be searched for.
//Returns 1 if it is found, 0 otherwise.
int exists_in_text(list *t_list, char what[20]) {
    for (; t_list != NULL; t_list = t_list->next) {
        if (strcasecmp(what, t_list->word) == 0) {
            return 1;
        }
    }
    return 0;
}

//finds word, returns a pointer to its node
list *find_word(list *t_list, char word[20], int *steps) {
    *steps = 0;
    for (; t_list != NULL; t_list = t_list->next) {
        *steps = *steps + 1;
        if (strcasecmp(word, t_list->word) == 0) {
            return t_list;
        }
    }
    return 0;
}


//reads a word, looks for it in the linked list with a_list at the head
//and either finds it and increases the count, or adds it.
list *insertwordlist(FILE *book, list *a_list) {
    char word[20];
    int steps, t;
    list *point;
    linkedListRead(book, word);
    if (word[0] != '\0' && word[0] != '\n' && strcmp(word, "EOF") != 0) {
        a_list = add(a_list, word);
    }
    while (strcmp(word, "EOF") != 0) {
        linkedListRead(book, word);
        if (word[0] != '\0' && word[0] != '\n' && strcmp(word, "EOF") != 0) {

            if (exists_in_text(a_list, word) == 0) {
                a_list = add(a_list, word);
                t++;
            }
            else {
                point = find_word(a_list, word, &steps);
                point->count++;
            }
        }
    }

    return a_list;
}

//Takes in the string whose hash value is to be calculated, then returns
//it's value.
int hash(char *str) {
    for (int i = 0; str[i]; i++) { //converts all characters to lower case as otherwise the hash value for different capitalisations of the same word will be different.
        str[i] = tolower(str[i]);
    }
    long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = (((hash << 5) + hash) + c) % 10000;
    }
    return hash;
}

//This function reads the worda from the text then, if it isn't at the end of the file, proceed to calculate the hash value and insert the word into the hashtable.
void insertwordtable(FILE *book, list **hashtable) {
    char word[20];
    linkedListRead(book, word);
    while (strcmp("EOF", word) != 0) {
        int index = hash(word);
        hashtable[index] = insert(word, hashtable[index]);
        linkedListRead(book, word);
    }
}

//This function adds the words to the hashtable and also times the time it takes to finish adding the words. It prints the time taken.
void createHashTable(FILE *book, list **hashtable, char *argv[]) {
    book = fopen(argv[1], "r");
    clock_t start = clock();
    insertwordtable(book, hashtable);
    clock_t stop = clock();
    double time_taken = (stop - start) / (double) CLOCKS_PER_SEC;
    printf("Time taken for hash table: %f\n", time_taken);
    fclose(book);
}

//This function adds words to the linked list and also times the time it takes to finish adding the words. Prints the time taken.
list *createLinkedList(FILE *book, list *linked_list, char *argv[]) {
    book = fopen(argv[1], "r");
    clock_t start = clock();
    linked_list = insertwordlist(book, linked_list);
    clock_t stop = clock();
    double time_taken = (stop - start) / (double) CLOCKS_PER_SEC;
    printf("Time taken for linked list: %f\n", time_taken);
    fclose(book);
    return linked_list; 
}

//hash efficiency function
void hashTableEffiency(list **hashtable) {
    int hashIndexesUsed = 0;
    for (int i = 0; i < 10000; i++) {
        if (hashtable[i] != NULL) {
            hashIndexesUsed = hashIndexesUsed + 1;
        }
    }
    printf("The number of empty indexes is %d\n", 10000 - hashIndexesUsed);
    int a = hashIndexesUsed/10000;
    double b = a*100;
    printf("The percentage of space used is %f\n", b);
}

void hashTableSize(list **hashtable) {
    int size, maxsize = 0;
    for (int i = 0; i < 10000; i++) {
        size = 0;
            while (hashtable[i] != NULL) {
                hashtable[i] = hashtable[i]->next;
                size = size + 1;
            }
            if (size > maxsize) {
                maxsize = size;
            }
    }
    printf("The size of the longest list in the hash table is %d.\n", maxsize);
}

list *findInTheHashTable(char *word_for_retrieval, list **hashtable, int *step) {
    int i = hash(word_for_retrieval);
    return find_word(hashtable[i], word_for_retrieval, step);
}

void querying(list *linked_list, list **hashtable, char *argv[]) {
    _Bool yes = 1;
    while (yes == 1) {
        char word_for_retrieval[20];
        char nl;
        printf("Enter word for retrieval: ");
        scanf("%s%c", word_for_retrieval, &nl);
        //printf("%s\n", word_for_retrieval);
        int step;
          //printf("%i\n",exists_in_text(linked_list,"upon"));

        list *location;
        if (exists_in_text(linked_list, word_for_retrieval) == 1) {
            printf("IN query\n");
            clock_t start = clock();
            location = find_word(linked_list, word_for_retrieval, &step);
            clock_t stop = clock();
            double time_taken = (stop - start) / (double) CLOCKS_PER_SEC;
            int this_count = location->count;
            printf("'%s' occurs %i times, and took %f seconds in the linked list.\n", word_for_retrieval, this_count,
                   time_taken);

            clock_t start2 = clock();
            location = findInTheHashTable(word_for_retrieval, hashtable, &step);
            clock_t stop2 = clock();
            time_taken = (stop2 - start2) / (double) CLOCKS_PER_SEC;
            printf("'%s' occurs %i times, and took %f seconds in the hashtable.\n", word_for_retrieval, this_count,
                   time_taken);
        }
        else {
            printf("The word '%s', does not exist in the text\n", word_for_retrieval);
        }
        char query;
        printf("Another query? [y/n] \n");
        scanf("%c", &query);
        switch (query) {
            case 'y':
                break;

            case 'n':
                yes = 0;
                printf("Quitting\n");
                break;

        }
    }

}


int main(int argc, char *argv[]) {
    FILE *book;
    list *linked_list;
    linked_list = NULL;

    list *hash_table[10000];
    list **hashtable = hash_table; //initialises the hash table.
    for (int i = 0; i < 10000; i++) {
        hash_table[i] = NULL;
    }

    createHashTable(book, hashtable, argv);
    linked_list = createLinkedList(book, linked_list, argv);
    hashTableEffiency(hashtable);
    hashTableSize(hashtable);
    querying(linked_list, hashtable, argv);
    return 0;
}
