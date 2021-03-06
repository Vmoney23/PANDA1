/* this program wouldn't get full marks even it was complete, the
   comments are terrible, the variables names poor and there are
   global variables.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<time.h>
#include<math.h>
#include<ctype.h>
FILE* book;
FILE* output;

//a node in the linked list
typedef struct List
{
  struct List *next;
  char word[20];
  int count;
  int number_of_words;
} list;

//reads in a word, if the file is at the end, adds the word EOF
void read(char word[20])
{
  char c;
  if(fscanf(book,"%c",&c)!=EOF)
    {
      char a[]=". ,;:*!?'-\n\0\r";
      int i;
      i=0;
      while(strchr(a,c)==0)
	{
	  word[i]=c;
	  i++;
	  if(fscanf(book,"%c",&c)==EOF)
	    break;
	}
      word[i]='\0';
    }
  else
    {
      strcpy(word,"EOF");
    }

}

//inserts a new new node called T for new_word, adds it before B
list *insert( char new_word[20], list *next_node)
{
  list *new_node=calloc(1, sizeof(list));
  strcpy(new_node->word,new_word);
  new_node->count=1;
  new_node->next=next_node;
  return new_node;
}

//adds a new node for new_word as the next of the list
list *add(list *old_list, char new_word[20])
{

  if(old_list==NULL)
    {
      return insert(new_word,NULL);
    }
  else
    {
      list *new_list;
      for(new_list=old_list;new_list->next!=NULL;new_list=new_list->next)
	{
	}
      new_list->next=insert(new_word,NULL);
      return old_list;
    }
}

//lods for what in the list, returns 1 if it is there, 0 otherwise
int exists_in_text(list *t_list, char what[20])
{
  for(;t_list!=NULL;t_list=t_list->next)
    {
      if(strcasecmp(what,t_list->word)==0)
	{
	  return 1;
	}
    }
  return 0;
}

//finds word, returns a pointer to its node
list *find_word(list *t_list, char word[20], int *steps)
{
  *steps=0;
  for(;t_list!=NULL;t_list=t_list->next)
    {
      *steps=*steps+1;
      if(strcasecmp(word,t_list->word)==0)
	{
	  return t_list;
	}
    }
  return 0;
}

//reads a word, looks for it in the linked list with a_list at the head
//and either finds it and increases the count, or adds it.
list *insertwordlist(list *a_list)
{
  char word[20];
  int steps,t;
  list *point;
  read(word);
  if (word[0]!='\0'&&word[0]!='\n'&&strcmp(word,"EOF")!=0)
    {
      a_list=add(a_list,word);
    }
  while(strcmp(word,"EOF")!=0)
    {
      read(word);
      if (word[0]!='\0'&&word[0]!='\n'&&strcmp(word,"EOF")!=0)
	{

	  if(exists_in_text(a_list,word)==0)
	    {
	      a_list=add(a_list,word);
	      t++;
	    }
	  else
	    {
	      point=find_word(a_list,word,&steps);
	      point->count++;
	    }
	}
    }

  return a_list;
}

int main(int argc,char *argv[])
{
  list *linked_list;
  linked_list=NULL;

  book=fopen(argv[1],"r");
  clock_t start=clock();
  linked_list=insertwordlist(linked_list);
  clock_t stop=clock();
  fclose(book);

  double time_taken=(stop-start)/CLOCKS_PER_SEC;

  printf("%f\n",time_taken);

  printf("%i\n",exists_in_text(linked_list,"Tralala"));
  printf("%i\n",exists_in_text(linked_list,"computer"));



// retrieval
  _Bool yes=1;
  while(yes==1) {
    char word_for_retrieval[20];
    char scanffixer[4];
    printf("Enter word for retrieval: ");
    scanf("%s", word_for_retrieval);
    int step;
    list *location;
    if(exists_in_text(linked_list,word_for_retrieval)==1)
    {
      location=find_word(linked_list,word_for_retrieval,&step);
      int this_count=location->count;
      printf("'%s' occurs %i times.\n",word_for_retrieval,this_count);
    }
    else
    {
      printf("The word '%s', does not exist in the text\n", word_for_retrieval);
    }
    char query;
    printf("Another query? [y/n] ");
    //scanf("%s", &scanffixer);
    scanf("%c", &query);
    switch (query) {
      case 'y':
      break;

      case 'n':
      yes=0;
      break;

    }
  }
  return 0;
}
