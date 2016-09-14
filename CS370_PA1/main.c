//----------------------------------------------------
//CS370 Partial Code for PA1
//Authors: Leon, Rejina
//Students: Provide your own header here.
//----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define DEBUG 0

// Defining the records structure for Library Systems Book list
typedef struct _Book
{
  int ISBN;
  char Title[20];
  char Author[20];
  char Description[40];
  int CopiesAtCSU;


  struct _Book *next;
} Book;



//------------------------------------------------------
// Display the menu and return the user choices
char Menu(void)
{
char ch;
do{
    printf("\n Main Menu");
    printf("\n ------------------");
    printf("\n1- Add Book");
    printf("\n2- Delete Book");
    printf("\n3- List All Books");
    printf("\n4- Save data to file & exit");
    printf("\n -------------------------------");
    printf("\n Enter your choice(1-4):");

    char line[80];
    fgets(line, 80, stdin);
    ch = *line;


} while(ch>'4' || ch<'1');
return ch;
}

//------------------------------------------------------
//Function to Add Book info to the linked list
//@parameters :
// listHead : Pointer to the head of the list. [Q1: We need a pointer to pointer in this function, Why?]
//
//      We need a pointer because we are looking at a list of pointers, and we would need to pass the first
//      element of that list (listHead) to start iterating through the linked list, and we need to pass by pointer
//      so we can manipulate the Book struct and not do a shallow copy.
//
//
// ISBN,Author,Title, Description CopiesAtCsu : Book's ISBN,Author, Title, CopiesAtCsu and Description respectively
// sortIndx : The field number used for sorting the list, 1 is ISBN, 2 is Title, and 3 is Author.

int AddBook(Book **listHead,int ISBN,char *Title,char *Author, int CopiesAtCsu, char *description,  int sortIndx, int sort) {
// [Q2: This function has too many value parameters ISBN,Title,Author,... etc. Is there a better way to pass
//  those values? if Yes, write a prototype for it]
//
//    Yes there is another way. Instead of having individual parameters we could do the following:
//    int AddBook(Book **listHead, Book *newNode, int sortIndx)
//
//    Where newNode is the book struct that can be passed into the function, and created in readfile


    Book *current = *listHead, *prev, *newNode;
    int locFound = 0;

    while (current != NULL) {
        if (current->ISBN == ISBN) {
            printf("\nRecord already exists - Adding %i copies to ISBN:%i\n", CopiesAtCsu, ISBN);
            current->CopiesAtCSU += CopiesAtCsu;
            return 1;
        }
        current = current->next;
    }
    newNode = (Book *) malloc(sizeof(Book));
    newNode->ISBN = ISBN;
    strcpy(newNode->Title, Title);
    strcpy(newNode->Author, Author);
    strcpy(newNode->Description, description);
    newNode->CopiesAtCSU = CopiesAtCsu;
    newNode->next = NULL;

    if(sortIndx == 1) {
        // ISBN
        if(sort == 0) {
            if (*listHead == NULL) {
                *listHead = newNode;
                return 1;
            } else if (newNode->ISBN < (*listHead)->ISBN) {
                newNode->next = *listHead;
                *listHead = newNode;
            } else {
                current = *listHead;
                while (current->next != NULL) {
                    if (newNode->ISBN > current->ISBN) {
                        if (newNode->ISBN < current->next->ISBN) {
                            Book *temp = current->next;
                            current->next = newNode;
                            newNode->next = temp;
                            break;
                        }
                    }
                    current = current->next;
                }
                current->next = newNode;
            }
        }else{
            if (*listHead == NULL) {
                *listHead = newNode;
                return 1;
            } else if (newNode->ISBN > (*listHead)->ISBN) {
                newNode->next = *listHead;
                *listHead = newNode;
            } else {
                current = *listHead;
                while (current->next != NULL) {
                    if (newNode->ISBN < current->ISBN) {
                        if (newNode->ISBN > current->next->ISBN) {
                            Book *temp = current->next;
                            current->next = newNode;
                            newNode->next = temp;
                            break;
                        }
                    }
                    current = current->next;
                }
                current->next = newNode;
            }
        }
    }else if(sortIndx == 2) {
        //Title
        if(sort == 0) {
            if (*listHead == NULL) {
                *listHead = newNode;
                return 1;
            } else if (strcmp(newNode->Title, (*listHead)->Title) < 0) {
                newNode->next = *listHead;
                *listHead = newNode;
            } else {
                current = *listHead;
                while (current->next != NULL) {
                    if (strcmp(newNode->Title, current->Title) >= 0) {
                        if (strcmp(newNode->Title, current->next->Title) < 0) {
                            Book *temp = current->next;
                            current->next = newNode;
                            newNode->next = temp;
                            break;
                        }
                    }
                    current = current->next;
                }
                current->next = newNode;
            }
        }else {
            if (*listHead == NULL) {
                *listHead = newNode;
                return 1;
            } else if (strcmp(newNode->Title, (*listHead)->Title) > 0) {
                newNode->next = *listHead;
                *listHead = newNode;
            } else {
                current = *listHead;
                while (current->next != NULL) {
                    if (strcmp(newNode->Title, current->Title) <= 0) {
                        if (strcmp(newNode->Title, current->next->Title) > 0) {
                            Book *temp = current->next;
                            current->next = newNode;
                            newNode->next = temp;
                            break;
                        }
                    }
                    current = current->next;
                }
                current->next = newNode;
            }
        }
    }else if(sortIndx == 3) {
        //Author
        if (sort == 0) {
            if (*listHead == NULL) {
                *listHead = newNode;
                return 1;
            } else if (strcmp(newNode->Author, (*listHead)->Author) < 0) {
                newNode->next = *listHead;
                *listHead = newNode;
            } else {
                current = *listHead;
                while (current->next != NULL) {
                    if (strcmp(newNode->Author, current->Author) >= 0) {
                        if (strcmp(newNode->Author, current->next->Author) < 0) {
                            Book *temp = current->next;
                            current->next = newNode;
                            newNode->next = temp;
                            break;
                        }
                    }
                    current = current->next;
                }
                current->next = newNode;
            }
        } else {
            if (*listHead == NULL) {
                *listHead = newNode;
                return 1;
            } else if (strcmp(newNode->Author, (*listHead)->Author) > 0) {
                newNode->next = *listHead;
                *listHead = newNode;
            } else {
                current = *listHead;
                while (current->next != NULL) {
                    if (strcmp(newNode->Author, current->Author) <= 0) {
                        if (strcmp(newNode->Author, current->next->Author) > 0) {
                            Book *temp = current->next;
                            current->next = newNode;
                            newNode->next = temp;
                            break;
                        }
                    }
                    current = current->next;
                }
                current->next = newNode;
            }
        }
    }
return 1;
}

//------------------------------------------------------
// Function to read books' info from a file and add them to the
//  Books linked list sorted based on the sortIndx
// Use the function AddBook
//@ Params:
// fileName : the file to read from. The file contains info separated by
//		commas and/or spaces  and each line belongs to a book.
// list: Pointer to the head of the list. [Q3: We need a pointer to pointer in this function, Why?]
//
//      Again, as in the first question, we are looking at a specific Book in the list of books. We need
//      the pointer to a Book because we are passing by pointer, so we can manipulate the Book struct in
//      addBook function with a call by reference.
//

// @Return:
//  1 on success and 0 on failure.
int
readfile (char *fileName, Book **list, int sortIndx, int sort)
{
  FILE *fd;
  char Title[20],Author[20],Description[40];
  int ISBN;
  int CopiesAtCsu;
  char *buff;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  if (DEBUG)
    printf ("Entering readfile\n");

  fd = fopen (fileName, "r");
  if (!fd){
	printf("\n Error reading input file");
    	return 0;
	}
  while ((read = getline(&line, &len, fd)) != -1) {
               buff = strtok(line, ",");
               ISBN = atoi(buff);
               buff = strtok(NULL, ",");
               strcpy(Title, buff);
               buff = strtok(NULL, ",");
               strcpy(Author, buff);
               buff = strtok(NULL, ",");
               strcpy(Description, buff);
               buff = strtok(NULL, ",");
               CopiesAtCsu = atoi(buff);
               AddBook(list, ISBN, Title, Author, CopiesAtCsu, Description,  sortIndx, sort);
           }

 //close the file
 free(line);
 fclose (fd);
 return 1;
}

//------------------------------------------------------
//function to write data from the list to a text file
// fileName : the file to Write to. Each record of the data is written as separated by commas and/or spaces
//               and each record is written in a separate line.

// list: The head of the list pointer. Q4: We didn't use a pointer to pointer in this function, Why?
//
//      Because we don't need to manipulate the elements of the list. We are just passing a pointer to
//      the list which allows us to iterate throguh and read the values of the linked list.
//
//
void writefile (char *fileName, Book *list)
{
  FILE *fd;
  Book *p=list;
  fd = fopen (fileName, "w");
    while (p != NULL) {
        char line[100];
        sprintf(line, "%i,%s,%s,%s,%i\n", p->ISBN,p->Title,p->Author, p->Description, p->CopiesAtCSU);
        fprintf(fd, line);
        p = p->next;
    }

  fclose (fd);
  return;

}

// Function to delete a book data from the list using his ISBN
//@ Params:
//
// BookList: Pointer to the head of the
// [Q5: We need a pointer to pointer in this function, Why?]
//
//      Because we are manipulating the list elements, when we delete an element
//      we have to set the next to null and the data to null, so we need to do
//      a call by reference to change the values.
//
// id : The ISBN of the book whose data is to be deleted.
// @Return:
//  1 on success and 0 on failure.
//------------------------------------------------------

int deleteBook(int ISBN,Book **BookList)
{

	Book *current=*BookList,*prev;
    Book *temp;


    while(current!=NULL)
    {
        if(current->ISBN==ISBN)
        {
            if(current == (*BookList)){
                temp = current;
                current = current->next;
                *BookList = current;
                free(temp);
                return 1;
            }
            prev->next=current->next;
            free(current);
            return 1;

        }
        prev=current;
        current=current->next;
    }

// Not found! OK this means delete wasn't successful. Return 0.
printf("\n Book ISBN not found !");
return 0;

}
//------------------------------------------------------
//function to display Books' info
//@params:
// Pointer to the header of the list
void displayBookList(Book *listHead)
{
Book *p=listHead;
printf("\n%-9s %-20s %-20s %-10s %-40s","Book_ISBN","Title","Author"," Copies@CSU","    Description");
printf("\n------------------------------------------------------------------------------------------------------------------");
while(p!=NULL)
   {  printf("\n%-9d %-20s %-20s %-10d %-40s",p->ISBN,p->Title,p->Author,p->CopiesAtCSU,p->Description);
	p=p->next;

	}

//Adjust it to make sure it display well on CS lab machine

}


//------------------------------------------------------
// Utility function:
// alternative to scanf.
// store white spaces except \n to char*
// scanf neglects characters after it the space
void getText(char *message, char *variable, int size)
{
    printf("\n %s: ", message);
    fgets(variable, sizeof(char) * size, stdin);
    sscanf(variable, "%[^\n]", variable);
}

//------------------------------------------------------
//Main function:
// parses the command line parameters, defines the header of the list,
// initializes the list with data from the file provided with the command line
// then displays the menu, and calls other functions based
// on user choices.


int main(int argc, char **argv)
{
char ch;
char fileName[50];
int sort=0;
int c;
int sortIndx=1;
Book *BookList=NULL;  // the list header is declared and initialized with NULL
int ISBN;
char Title[20],Author[20],Description[40];
int CopiesAtCsu;

  opterr = 0;
  if(argc<2) {
  fprintf (stderr, "Usage: options -f inputfile.txt [-s fileName] [-a] \n");
	return 0;
  }
  while ((c = getopt (argc, argv, "f:s:a")) != -1)
    switch (c)
      {
      case 'f':
        strcpy(fileName, optarg);
        printf("File - %s\n", fileName );


	break;
      case 's':  // the user provided the sorting field, we need to check the optarg
      			// and set the sortIndx accordingly

	if (strcmp(optarg,"ISBN")==0) sortIndx=1;
	else if (strcmp(optarg,"Title")==0)  sortIndx=2;
	   else if (strcmp(optarg, "Author")==0) sortIndx=3;
		      else printf("\n unknown index field, default assumed");

	break;
      case 'a':   // the sorting direction (ascending or descending)
                  //is not used in this code, you need to figure out how and where to use it ?
	sort = 1;
	break;

      case '?':   //there was an error
	 if (optopt == 'f' || optopt == 's' )
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);

      	fprintf (stderr, "Usage: options -f inputfile.txt [-s Title] [-a] \n");
	return 0;

      }

readfile(fileName, &BookList, sortIndx, sort);

do{

ch=Menu();

  switch (ch)
	  {
	  case '1': printf("\n Enter Book info. to add ");
		    getText("Title", Title, 20);
    getText("Author", Author, 20);
    getText("Description", Description, 40);
    printf("\n ISBN:");
    scanf("%d",&ISBN);
    printf("\n copies at CSU:");
    scanf("%d",&CopiesAtCsu);
    getchar();

			  AddBook(&BookList, ISBN, Title, Author, CopiesAtCsu, Description, sortIndx, sort);

		    break;
	  case '2': printf("\n Enter Book ISBN to delete :");
			scanf("%d",&ISBN);
			 deleteBook(ISBN, &BookList);

		    break;
	  case '3':
			displayBookList(BookList);
		    break;
	  case '4':
			writefile (fileName, BookList);
		    break;

	}

}while(ch!='4');

  return 0;
}
