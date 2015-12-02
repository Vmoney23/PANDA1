// Algorithms worksheet 3
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<time.h>
#include<math.h>
#include<ctype.h>

// Struct for List. Contains the word at node, pointer to the next node and counting variables.
typedef struct List {
    struct List *next;
    char word[20];
    int count;
    int nOfWords;
} list;

// Reads in a word and adds it as either a new node or increases the count at that node.
// If the file ends, EOF is appended. 
void readLinkList(FILE *book, char word[20]) {
    char c;
    if (fscanf(book, "%c", &c) != EOF) {
        char ref[] = ". ,;:*!?)'-\n\r\0";
        int i;
        i = 0;
        while (strchr(ref, c) == 0) {
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

// Inputs: new word, list. Output: updated list.
// Inserts a new new node for new_word, adds it in before next_word.
list *insert(char new_word[20], list *next_node) {
    list *new_node = calloc(1, sizeof(list));
    strcpy(new_node->word, new_word);
    new_node->count = 1;
    new_node->next = next_node;
    return new_node;
}

// Inputs: new word, list. Output: updated list.
// Adds a new node for new_word as the next in the list.
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

// Input: word, list. Output: 1 if word found, 0 if not found.
// This compares the values in the list with the word being searched for.
int exists(list *t_list, char what[20]) {
    for (; t_list != NULL; t_list = t_list->next) {
        if (strcasecmp(what, t_list->word) == 0) {
            return 1;
        }
    }
    return 0;
}

// Input: word, list. Output: updated list.
// Finds the word being searched for and returns a pointer to its node.
list *findWord(list *t_list, char word[20]) {
    int steps = 0;
    for (; t_list != NULL; t_list = t_list->next) {
        steps += 1;
        if (strcasecmp(word, t_list->word) == 0) {
            return t_list;
        }
    }
    return 0;
}

// Input: file, list. Output: updated list.
// Reads a word then looks for it in the linked list (with a_list at the head).
// It either gets added to the list, or if it already exists, the count increments.
list *insertWordList(FILE *book, list *a_list) {
    char word[20];
    int t;
    list *point;
    readLinkList(book, word);
    if (word[0] != '\0' && word[0] != '\n' && strcmp(word, "EOF") != 0) {
        a_list = add(a_list, word);
        a_list->nOfWords += 1;
    }
    while (strcmp(word, "EOF") != 0) {
        readLinkList(book, word);
        if (word[0] != '\0' && word[0] != '\n' && strcmp(word, "EOF") != 0) {
            if (exists(a_list, word) == 0) {
                a_list = add(a_list, word);
                a_list->nOfWords += 1;
                t++;
            }
            else {
                point = findWord(a_list, word);
                point->count++;
            }
        }
    }
    return a_list;
}

// Input: string. Output: Hash value.
// Takes in the string to be hashed, then returns the hash value.
int hash(char *str) {
// Converts all characters to lower case so that the same word doesn't
// have different hash values as a result of capitalisation.
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
    long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = (((hash << 5) + hash) + c) % 15000;
    }
    return hash;
}

// Input: File, hash table. Output: none.
// This reads the words from the text, checks that it is not EOF, then
// calculates the hash value and adds the word to the hash table
void insertwordtable(FILE *book, list **hashTable) {
    char word[20];
    readLinkList(book, word);
    while (strcmp("EOF", word) != 0) {
        int index = hash(word);
        hashTable[index] = insert(word, hashTable[index]);
        readLinkList(book, word);
    }
}

// Input: file, hash table, character. Output: none.
// This adds the word to the hash table and times how long it takes to add
// the words, printing out the time taken.
void createHashTable(FILE *book, list **hashTable, char *argv[]) {
    book = fopen(argv[1], "r");
    clock_t start = clock();
    insertwordtable(book, hashTable);
    clock_t stop = clock();
    double time_taken = (stop - start) / (double) CLOCKS_PER_SEC;
    printf("Reading into the hash table took %fs.\n", time_taken);
    fclose(book);
}

// Input: File, list, character. Output: populated list.
// This adds the word to the linked list and times how long it takes to add
// the words, printing out the time taken.
list *createLinkedList(FILE *book, list *linked_list, char *argv[]) {
    book = fopen(argv[1], "r");
    clock_t start = clock();
    linked_list = insertWordList(book, linked_list);
    clock_t stop = clock();
    double time_taken = (stop - start) / (double) CLOCKS_PER_SEC;
    printf("Reading into the linked list took %fs.\n", time_taken);
    fclose(book);
    return linked_list;
}

// Input: Hash table. Output: none.
// This function finds the number of empty indexes in the hash table
// and prints them, then calculates the space used by the hash table.
// Currently space used is not working.
void hashEfficiency(list **hashTable) {
    int hashIndexes = 0;
    for (int i = 0; i < 15000; i++) {
        if (hashTable[i] != NULL) {
            hashIndexes += 1;
        } else {
            hashIndexes = hashIndexes;
        }
    }
    printf("The number of empty indexes is %d.\n", 15000 - hashIndexes);
    int a = hashIndexes / 15000;
    double b = a * 100;
    printf("Space used: %f%c.\n", b, 37);
}

// Input: Hash table. Output: none.
// This function finds the length of the longest overflow list in the hash table.
void hashSize(list **hashTable) {
    int size, maxsize = 0;
    for (int i = 0; i < 15000; i++) {
        size = 0;
        while (hashTable[i] != NULL) {
            hashTable[i] = hashTable[i]->next;
            size = size + 1;
        }
        if (size > maxsize) {
            maxsize = size;
        }
    }
    printf("The length of the longest overflow list is %d.\n", maxsize);
}

// Input: Word, hash table. Output: pointer to word in table.
// This finds a word in the hash table
list *findInTable(char *wordToFind, list **hashTable) {
    int i = hash(wordToFind);
    return findWord(hashTable[i], wordToFind);
}

// Input: list, hash table, character. Output: none.
// This function queries the linked list and hash table for the word requested.
// It also times how long the query takes and prints out the result. It then offers
// the user the option of querying for new words.
void querying(list *linked_list, list **hashTable, char *argv[]) {
    _Bool newQ = 1;
    while (newQ == 1) {
        char wordToFind[20];
        char nl;
        printf("Enter word to query: ");
        scanf("%s%c", wordToFind, &nl);
        list *location;
        if (exists(linked_list, wordToFind) == 1) {
            printf("Querying for %s\n", wordToFind);
            clock_t start = clock();
            location = findWord(linked_list, wordToFind);
            clock_t stop = clock();
            double time_taken = (stop - start) / (double) CLOCKS_PER_SEC;
            int this_count = location->count;
            printf("'%s' occurs %i times.\n", wordToFind, this_count);
            printf("It took %f seconds in the Linked List.\n", time_taken);
            clock_t start2 = clock();
            location = findInTable(wordToFind, hashTable);
            clock_t stop2 = clock();
            time_taken = (stop2 - start2) / (double) CLOCKS_PER_SEC;
            printf("It took %f seconds in the Hash Table.\n", time_taken);
        }
        else {
            printf("The word '%s', does not exist in the text.\n", wordToFind);
        }
        char query;
        printf("Another query? [y/n] \n");
        scanf("%c", &query);
        switch (query) {
        case 'y':
            break;
        case 'n':
            newQ = 0;
            printf("Quitting program!\n");
            break;
        }
    }
}

// Main function that creates and initialises Linked List and Hash Table
// and then runs through the program. Passes the book to be read into the
// data structures and then allows the use to query for specific words.
int main(int argc, char *argv[]) {
    FILE *book;

    // Initiialise Linked List
    list *linkedList;
    linkedList = NULL;

    // Initialise Hash Table
    list *hash_table[15000];
    list **hashTable = hash_table;
    for (int i = 0; i < 15000; i++) {
        hash_table[i] = NULL;
    }

    // Run program
    createHashTable(book, hashTable, argv);
    linkedList = createLinkedList(book, linkedList, argv);
    hashEfficiency(hashTable);
    hashSize(hashTable);
    querying(linkedList, hashTable, argv);
    return 0;
}
