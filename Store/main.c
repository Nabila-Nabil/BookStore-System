#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
typedef struct book book;
typedef struct genre genre;
typedef struct bookstore bookstore;

struct book
{
    char titleOfBook[101] ;
    char authorOfBook[51] ;
    char describtionOfBook[501];
    char language[3];

    int quantityOfBook ;
    int releaseYear;

    float price;

    int isBookPartOfSeries ;
    int isDeleted;
    char nameOfGenre[51];
};
struct  genre
{
    char nameOfGenre[51];
    char describtionOfGenre[501];

    int totalNumberOfBooks;
    int numberOfDistinctAvailableBooks;

    book* bookshelf;
};
struct bookstore
{
    int numberOfGenres;
    genre* inventory;
};

//void SetColor(int ForgC);
//void addFirstGenre (bookstore* NabilaForBooks);
//void addNewGenre(bookstore* NabilaForBooks);
//void addFirstBook(genre* topic);
//void addNewBook(genre* topic);
//void fillNewGenreInfo(int indexOfCurrentGenre,genre* topic,bookstore*NabilaForBooks);
//void fillNewBookInfo(int indexOfCurrentBook,book* BOOK,genre*topic);
//void displayGenre(genre topic);
//void displayBook(book BOOK);
//void displayBookList(genre* topic);
//void displayAllBooksInGenreInDetail(genre* topic);
//int getOrderedGenreIndex( char* newGenreName,bookstore*NabilaForBooks);
//int getOrderedBookIndex(char* newBookName,genre*topic)
//int searchForGenreName(int indexOfCurrentGenre, char* newGenreName,bookstore*NabilaForBooks);
//int searchForBookName(int indexOfCurrentBook, char* newBookName,genre*topic);
//void  displayAllGenresInBookstoreInDetail(bookstore* NabilaForBooks);
//void displayGenresList(bookstore* NabilaForBooks);
//int selectingbookGenre(bookstore* NabilaForBooks);
//int selectingbook(genre* topic);
//void removeBook(book* BOOK);
//void increaseBookQuantity(book* BOOK);
//void mainMenu(bookstore* NabilaForBooks);
//void genreMenu(bookstore* NabilaForBooks);
//void bookMenu(bookstore* NabilaForBooks);
//void MoveBookFromGenre(genre* topic,book* BOOK,int indexOfCurrentBook);
//void MoveBookToGenre(genre* topic,book* BOOK);
//int validateOrderedBookName(int indexOfCurrentBook, int sizeOfBookArray,char* newBookName, book*BookArray);
//void order(bookstore* NabilaForBooks);
//int exitSystem(bookstore* NabilaForBooks);
//bookstore initializeBookstoreSystem();
void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}


void addFirstGenre (bookstore* NabilaForBooks)
{
    NabilaForBooks->numberOfGenres=1;
    NabilaForBooks->inventory = (genre*)malloc( (NabilaForBooks->numberOfGenres)*sizeof(genre));
    //initializing before modification to solve errors
    NabilaForBooks->inventory[0].bookshelf = NULL;
    NabilaForBooks->inventory[0].numberOfDistinctAvailableBooks = 0;
    NabilaForBooks->inventory[0].totalNumberOfBooks = 0;
    //  printf("no of genres = %d\n\n\n",   NabilaForBooks->numberOfGenres);
    fillNewGenreInfo(0,&NabilaForBooks->inventory[0],NabilaForBooks);
}
void addNewGenre(bookstore* NabilaForBooks)
{
    int indexOfCurrentGenre=0,genresCount=0;

    NabilaForBooks->numberOfGenres++;

    genresCount = NabilaForBooks->numberOfGenres;


    NabilaForBooks->inventory =(genre*)realloc(NabilaForBooks->inventory,(genresCount)*sizeof(genre));

    indexOfCurrentGenre = (genresCount)-1 ;

    NabilaForBooks->inventory[indexOfCurrentGenre].bookshelf = NULL;
    NabilaForBooks->inventory[indexOfCurrentGenre].numberOfDistinctAvailableBooks = 0;
    NabilaForBooks->inventory[indexOfCurrentGenre].totalNumberOfBooks = 0;

    fillNewGenreInfo( indexOfCurrentGenre,&NabilaForBooks->inventory[indexOfCurrentGenre],NabilaForBooks);

}
void fillNewGenreInfo(int indexOfCurrentGenre,genre* topic,bookstore*NabilaForBooks)
{
// printf("no of genres = %d\n\n\n",   NabilaForBooks->numberOfGenres);

    printf("Please Enter The Name Of Genre : ");
//    fgets(topic->nameOfGenre, sizeof(topic->nameOfGenre), stdin);
//    topic->nameOfGenre[strcspn(topic->nameOfGenre, "\n")] = '\0'; // remove trailing newline
    scanf(" %[^\n]s",topic->nameOfGenre);

    while ((searchForGenreName(indexOfCurrentGenre,topic->nameOfGenre,NabilaForBooks))>=0)
    {
// -1 = unique
//>=0 = duplicate
        printf("Genre of %s already exists !\n\nPlease Enter a Different Genre Name : ", topic->nameOfGenre);
        scanf(" %[^\n]s",topic->nameOfGenre);
    }

    printf("\nPlease Enter a short description about %s genre (NOT  exceeding 500 characters) : ",topic->nameOfGenre);
    scanf(" %[^\n]s",topic->describtionOfGenre);

    printf("\nWould You like to add books to %s now ? (press y to continue ,press any other key to exit) : ",topic->nameOfGenre);
    char choice;
    scanf(" %c", &choice);
    if(choice=='y'||choice=='Y')
    {
        addFirstBook(topic);
        int books=1;
        do
        {
            printf("\nadd another book ? (press y to continue, press any other key to exit) : ",topic->nameOfGenre);
            scanf(" %c", &choice);
            if(choice=='y'||choice=='Y')
            {
                addNewBook(topic);
                books++;
            }
            else
            {
                system("cls");
                printf("\n\n%d  books added successfully: ",books);
                printf("\n\nGenre of %s was added successfully .",topic->nameOfGenre);
            }
        }
        while(choice=='y'||choice=='Y');
    }
    else //initialize the genre data members with 0 or null (for pointers)
    {
        topic->bookshelf=NULL;
        topic->numberOfDistinctAvailableBooks=0;
        topic->totalNumberOfBooks=0;
        system("cls");
        printf("\n\nGenre of %s was added successfully .",topic->nameOfGenre);
    }


    Sleep(1000);
}
void displayGenre(genre topic)
{
    printf("\nGenre Name :\t%s ",topic.nameOfGenre);
    printf("\nDescription :\n\n%s ",topic.describtionOfGenre);
    printf("\nTotal Number Of %s Books  on the bookshelf :\t%d",topic.nameOfGenre,topic.numberOfDistinctAvailableBooks);
    for(int i =0 ; i<topic.numberOfDistinctAvailableBooks; i++)
    {
        printf("book (%d) : %s",i+1,topic.bookshelf[i].titleOfBook);
    }
    printf("\nTotal Number Of %s Books  in-Stock :\t%d\n",topic.nameOfGenre,topic.totalNumberOfBooks);
}

int getOrderedGenreIndex( char* newGenreName,bookstore*NabilaForBooks)
{

    for(int i =0; i<NabilaForBooks->numberOfGenres; i++)
    {
        if(strcmp(NabilaForBooks->inventory[i].nameOfGenre,newGenreName)==0)
        {
            return i;
        }
    }

    return -1;
}
int searchForGenreName(int indexOfCurrentGenre, char* newGenreName,bookstore*NabilaForBooks)
{
    int currentIndex=(NabilaForBooks->numberOfGenres)-1;
    if(currentIndex==0)
    {
        return -1;
    }
    else
    {
        for(int i =0; i<currentIndex; i++)
        {
            if(strcmp(NabilaForBooks->inventory[i].nameOfGenre,newGenreName)==0)
            {
                return i;
            }
        }
    }
    return -1;
}
void  displayAllGenresInBookstoreInDetail(bookstore* NabilaForBooks)
{
    for( int i =0, k=1; i<NabilaForBooks->numberOfGenres; i++,k++)
    {
        printf("\n---------------------------------(%d)---------------------------------\n",k);
        displayGenre(NabilaForBooks->inventory[i]);
        printf("\nAvailable Books :\n");
        for(int j=0; j<NabilaForBooks->inventory[i].numberOfDistinctAvailableBooks; j++)
        {
            if(NabilaForBooks->inventory[i].bookshelf[j].isDeleted==0)
            {
                displayBook(NabilaForBooks->inventory[i].bookshelf[j]);
            }
        }
    }

    Sleep(5000);
}
void displayGenresList(bookstore* NabilaForBooks)
{

    for( int i =0 ; i<NabilaForBooks->numberOfGenres; i++)
    {
        printf("\n----------------------------------------------------------------------\n");
        printf("%d)  %s\n",(i+1),NabilaForBooks->inventory[i].nameOfGenre);
    }
    Sleep(2000);
}

int selectingbookGenre(bookstore* NabilaForBooks)
{
    if(NabilaForBooks->numberOfGenres>0)
    {
        printf("\nSelect The Genre from the list Provided Below (type the number of the selected genre):");
        displayGenresList(NabilaForBooks);

        int index;
        scanf(" %d",&index);
        while((index>NabilaForBooks->numberOfGenres )||(index<1))
        {
            printf("\ninvalid choice !!\nPlease Select The Genre from the list Provided above :");
            scanf(" %d",&index);
        }

        return --index;
    }
    else
    {
        printf("\nthere are no genres to show please add genres first\n:");
        return -1;
    }
}
void mainMenu(bookstore* NabilaForBooks)
{

    int choice = 0;
    int selectedOption = 1; // index of choice
    while (choice != 4)
    {
        system("cls");

        // Print the menu options
        SetColor(15);
        printf("\t\t\t\t\tWelcome to Nabila's Bookstore\n\nMain Menu\n\n");
        for (int i = 1; i <= 4; i++) // 1 2 3 4
        {
            if (i == selectedOption)
            {
                SetColor(12); // Set color for the selected option
                printf("> ");
            }
            else
            {
                SetColor(15); // Set color for unselected options
                printf("  ");
            }

            if (i == 1)
            {
                printf("1) New Order\n");
            }
            else if (i == 2)
            {
                printf("2) Genre Settings\n");
            }
            else if (i == 3)
            {
                printf("3) Book Settings\n");
            }
            else if (i == 4)
            {
                printf("4) Exit\n");
            }
        }

        // Handle user input
        char ch = getch();
        if (ch == -32) //  this is the first bit of extended key
        {
            ch = getch();
            if (ch == 72) // arrow up
            {
                selectedOption--;
                if (selectedOption < 1)
                {
                    selectedOption = 4;
                }
            }
            else if (ch == 80) //arrow  Down
            {
                selectedOption++;
                if (selectedOption > 4)
                    selectedOption = 1;
            }
        }
        else if (ch == 13) // Enter
        {
            choice = selectedOption;
            switch (choice)
            {
            case 1:
                system("cls");
                if(NabilaForBooks->numberOfGenres==0)
                {
                    printf("\nthere is no added book genres to show \nplease add a genre first\n\n");
                    Sleep(2000);
                }
                else
                {
                    order(NabilaForBooks);
                }
                break;

            case 2:
                system("cls");
                genreMenu(NabilaForBooks);
                break;

            case 3:
                system("cls");
                bookMenu(NabilaForBooks);
                break;

            case 4:
                system("cls");
                SetColor(15);
                printf("\n\n\n\n ---------------------Have a Wonderful Day ---------------------\n\n\n\n\n\n\n\n\n\n\n\n");
                exitSystem(NabilaForBooks);
                break;
            }
       //     Sleep(1000);
       system("pause");
        }
    }
}
void genreMenu(bookstore* NabilaForBooks)
{
    int choice = 0;
    int selectedOption = 1; // index of choice
    while (choice != 4)
    {
        system("cls");

        // Print the menu options
        SetColor(15);
        printf("\n\nGenre Settings\n\n");
        for (int i = 1; i <= 4; i++) // 1 2 3 4
        {
            if (i == selectedOption)
            {
                SetColor(12); // color selected
                printf("> ");
            }
            else
            {
                SetColor(15); // color for unselected options (or else they get the same color as the selected)
                printf("  ");
            }

            if (i == 1)
            {
                printf("1) Display Genre Titles List\n");
            }
            else if (i == 2)
            {
                printf("2) Display Detailed Genres List\n");
            }
            else if (i == 3)
            {
                printf("3) Add New Genre\n");
            }
            else if (i == 4)
            {
                printf("4) Return to Main Menu\n");
            }

        }

        // Handle user input
        char ch = getch();
        if (ch == -32) //  this is the first bit of extended key
        {
            ch = getch();
            if (ch == 72) // arrow up
            {
                selectedOption--;
                if (selectedOption < 1)
                {
                    selectedOption = 4;
                }
            }
            else if (ch == 80) //arrow  Down
            {
                selectedOption++;
                if (selectedOption > 4)
                    selectedOption = 1;
            }
        }
        else if (ch == 13) // Enter
        {
            choice = selectedOption;
            switch (choice)
            {
            case 1:
                system("cls");
                if(NabilaForBooks->numberOfGenres==0)
                {
                    printf("\nthere is no added genres to show \nplease add a genre first\n\n");
                    Sleep(1000);
                }
                else
                {
                    displayGenresList(NabilaForBooks);
                }

                break;

            case 2:
                system("cls");
                if(NabilaForBooks->numberOfGenres==0)
                {
                    printf("\nthere is no added genres to show \nplease add a genre first\n\n");
                    Sleep(1000);
                }
                else
                {
                    displayAllGenresInBookstoreInDetail(NabilaForBooks);
                }
                break;

            case 3:
                system("cls");
                if(NabilaForBooks->numberOfGenres==0)
                {
                    addFirstGenre(NabilaForBooks);
                }
                else if(NabilaForBooks->numberOfGenres>=1)
                {
                    addNewGenre(NabilaForBooks);
                }
                break;

            case 4:
                system("cls");
                mainMenu(NabilaForBooks);
                break;
            }
               //     Sleep(1000);
       system("pause");
        }
    }
}
void bookMenu(bookstore* NabilaForBooks)
{
    int choice = 0;
    int selectedOption = 1; // index of choice
    while (choice != 7)
    {
        system("cls");

        // Print the menu options
        SetColor(15);
        printf("\n\nBook Settings\n\n");
        for (int i = 1; i <= 7; i++) // 1 2 3 4 5 6
        {
            if (i == selectedOption)
            {
                SetColor(12); // Set color for the selected option
                printf("> ");
            }
            else
            {
                SetColor(15); // Set color for unselected options
                printf("  ");
            }

            if (i == 1)
            {
                printf("1) Display Book List in a genre\n");
            }
            else if (i == 2)
            {
                printf("2) Display Detailed Book List in a genre\n");
            }
            else if (i == 3)
            {
                printf("3) Add New Book in a genre\n");
            }
            else if (i == 4)
            {
                printf("4) Remove book\n");
            }
            else if (i == 5)
            {
                printf("5) Increase book copies \n");
            }
            else if (i == 6)
            {
                printf("6) Edit book genre \n");
            }
            else if (i == 7)
            {
                printf("7) Return to Main Menu\n");
            }
        }
        // Handle user input
        char ch = getch();
        if (ch == -32) //  this is the first bit of extended key
        {
            ch = getch();
            if (ch == 72) // arrow up
            {
                selectedOption--;
                if (selectedOption < 1)
                {
                    selectedOption = 7;
                }
            }
            else if (ch == 80) //arrow  Down
            {
                selectedOption++;
                if (selectedOption > 7)
                    selectedOption = 1;
            }
        }
        else if (ch == 13) // Enter
        {
            int indexOfCurrentGenre=0;
            int indexOfCurrentbook=0;

            choice = selectedOption;
            switch (choice)
            {
            case 1:
                system("cls");
//Display Book List in a genre
                if(NabilaForBooks->numberOfGenres==0)
                {
                    printf("\nthere is no added book genres to show \nplease add a genre first\n\n");
                    Sleep(2000);
                }
                else
                {
                    indexOfCurrentGenre=selectingbookGenre(NabilaForBooks);
                    displayBookList(&NabilaForBooks->inventory[indexOfCurrentGenre]);
                }
                break;

            case 2:
                system("cls");
//Display Detailed Book List in a genre
                if(NabilaForBooks->numberOfGenres==0)
                {
                    printf("\nthere is no added book genres to show \nplease add a genre first\n\n");
                    Sleep(2000);
                }
                else
                {
                    indexOfCurrentGenre=selectingbookGenre(NabilaForBooks);
                    displayAllBooksInGenreInDetail(&NabilaForBooks->inventory[indexOfCurrentGenre]);
                }
                break;

            case 3:
                system("cls");
                if(NabilaForBooks->numberOfGenres==0)
                {
                    printf("\nthere is no added book genres \nplease add a genre first to add a book in it\n\n");
                    Sleep(2000);
                }
                else
                {
                    indexOfCurrentGenre=selectingbookGenre(NabilaForBooks);
                    if(NabilaForBooks->inventory[indexOfCurrentGenre].numberOfDistinctAvailableBooks==0)
                    {
                        addFirstBook(&NabilaForBooks->inventory[indexOfCurrentGenre]);
                    }
                    else
                    {
                        addNewBook(&NabilaForBooks->inventory[indexOfCurrentGenre]);
                    }
                }

                break;
            case 4:
                system("cls");
                if(NabilaForBooks->numberOfGenres==0)
                {
                    printf("\nthere is no added book genres \nplease add a genre first to add a book in it\n\n");
                    Sleep(2000);
                }
                else
                {
                    indexOfCurrentGenre=selectingbookGenre(NabilaForBooks);
                    indexOfCurrentbook=selectingbook(&NabilaForBooks->inventory[indexOfCurrentGenre]);
                    removeBook(&NabilaForBooks->inventory[indexOfCurrentGenre].bookshelf[indexOfCurrentbook]);
                    //search for genre and return index
                    //num of books --
                }

                break;
            case 5:
                system("cls");
                if(NabilaForBooks->numberOfGenres==0)
                {
                    printf("\nthere is no added book genres \nplease add a genre first to add a book in it\n\n");
                    Sleep(2000);
                }
                else
                {
                    indexOfCurrentGenre=selectingbookGenre(NabilaForBooks);
                    system("cls");
                    indexOfCurrentbook=selectingbook(&NabilaForBooks->inventory[indexOfCurrentGenre]);
                    system("cls");
                    increaseBookQuantity(&NabilaForBooks->inventory[indexOfCurrentGenre].bookshelf[indexOfCurrentbook]);

                }

                break;
            case 6:
                system("cls");
                int indexOfSourceGenre=0,indexOfDestinationGenre=0;
                if(NabilaForBooks->numberOfGenres==0)
                {
                    printf("\nthere is no added book genres \nplease add a genre first to add a book in it\n\n");
                    Sleep(2000);
                }
                else if(NabilaForBooks->numberOfGenres<2&&NabilaForBooks->numberOfGenres!=0)
                {
                    printf("\nthere should be at least 2 book genres \nplease add some genres first \n\n");
                    Sleep(2000);
                }
                else
                {
                    indexOfSourceGenre=selectingbookGenre(NabilaForBooks);
                    system("cls");
                    if(NabilaForBooks->inventory[indexOfSourceGenre].numberOfDistinctAvailableBooks==0)
                    {
                        printf("\ninvalid choice\nthere are no books in this genre please add books first\nexiting ");
                        Sleep(3000);
                        bookMenu(NabilaForBooks);
                    }
                    indexOfCurrentbook=selectingbook(&NabilaForBooks->inventory[indexOfSourceGenre]);
                    if(indexOfCurrentbook==-1)
                    {
                        printf("\ninvalid choice\nthere are no books to show please add books first\nexiting ");
                        Sleep(3000);
                        bookMenu(NabilaForBooks);
                    }
                    system("cls");
                    indexOfDestinationGenre=selectingbookGenre(NabilaForBooks);
                    MoveBookToGenre(&NabilaForBooks->inventory[indexOfDestinationGenre],&NabilaForBooks->inventory[indexOfSourceGenre].bookshelf[indexOfCurrentbook]);
                    MoveBookFromGenre(&NabilaForBooks->inventory[indexOfSourceGenre],&NabilaForBooks->inventory[indexOfSourceGenre].bookshelf[indexOfCurrentbook],indexOfCurrentbook);
                    printf("genre changed successfully");
                //    sleep(3000);

                }

                break;
            case 7:
                system("cls");
                mainMenu(NabilaForBooks);

                break;
            }
              //     Sleep(1000);
       system("pause");
        }
    }
}
int exitSystem(bookstore* NabilaForBooks)
{
// because if i free the entire store at once all the other dynamiclly allocayed memory access is lost and it isn't freed

//have to go this order   : books -> genres -> store

    for (int i = 0; i < NabilaForBooks->numberOfGenres; ++i)
    {
        free(NabilaForBooks->inventory[i].bookshelf); //book array
    }
    free(NabilaForBooks->inventory); // genre array
    free(NabilaForBooks); // store
    return 0;
}
bookstore initializeBookstoreSystem()
{
    bookstore* NabilaForBooks=(bookstore*)malloc(sizeof(bookstore));

    NabilaForBooks->numberOfGenres = 0;
    NabilaForBooks->inventory = NULL;
    return *NabilaForBooks;
}
void addFirstBook(genre* topic)
{
    topic->numberOfDistinctAvailableBooks=1;

    topic->bookshelf =(book*)malloc((topic->numberOfDistinctAvailableBooks)*sizeof(book));

    topic->bookshelf[0].price=0;
    topic->bookshelf[0].quantityOfBook=0;
    topic->bookshelf[0].releaseYear=0;
    topic->bookshelf[0].isDeleted=0;
    topic->bookshelf[0].isBookPartOfSeries=0;
    strcpy(topic->bookshelf[0].nameOfGenre,topic->nameOfGenre);
    fillNewBookInfo(0,&topic->bookshelf[0],topic);

    topic->totalNumberOfBooks=topic->bookshelf[0].quantityOfBook;
}
void MoveBookFromGenre(genre* topic,book* BOOK,int indexOfCurrentBook)
{
//loop start from book index
    for(int i =indexOfCurrentBook; i<topic->numberOfDistinctAvailableBooks; i++ )
    {
        topic->bookshelf[i]=topic->bookshelf[i+1];// book i=book i+1
    }
    topic->numberOfDistinctAvailableBooks--;//let go of last book
}
void MoveBookToGenre(genre* topic,book* BOOK)
{
    if( topic->numberOfDistinctAvailableBooks==0)
    {
        topic->numberOfDistinctAvailableBooks=1;
        topic->bookshelf =(book*)malloc((topic->numberOfDistinctAvailableBooks)*sizeof(book));

        topic->bookshelf[0].price=0;
        topic->bookshelf[0].quantityOfBook=0;
        topic->bookshelf[0].releaseYear=0;
        topic->bookshelf[0].isDeleted=0;
        topic->bookshelf[0].isBookPartOfSeries=0;
        strcpy(topic->bookshelf[0].nameOfGenre,topic->nameOfGenre);
        topic->bookshelf[0]=*BOOK;
        topic->totalNumberOfBooks=topic->bookshelf[0].quantityOfBook;
    }
    else
    {
        int indexOfCurrentBook=0,booksCount=0;

        indexOfCurrentBook= topic->numberOfDistinctAvailableBooks;
        topic->numberOfDistinctAvailableBooks++;

        booksCount = topic->numberOfDistinctAvailableBooks;

        topic->bookshelf=(book*)realloc(topic->bookshelf,(booksCount)*sizeof(book));

        topic->bookshelf[indexOfCurrentBook].price=0;
        topic->bookshelf[indexOfCurrentBook].quantityOfBook=0;
        topic->bookshelf[indexOfCurrentBook].releaseYear=0;
        topic->bookshelf[indexOfCurrentBook].isDeleted=0;
        topic->bookshelf[indexOfCurrentBook].isBookPartOfSeries=0;
        strcpy(topic->bookshelf[indexOfCurrentBook].nameOfGenre,topic->nameOfGenre);
        topic->bookshelf[indexOfCurrentBook]=*BOOK;
        topic->totalNumberOfBooks+=topic->bookshelf[indexOfCurrentBook].quantityOfBook;
    }

}
void addNewBook(genre* topic)
{
    int indexOfCurrentBook=0,booksCount=0;

    indexOfCurrentBook= topic->numberOfDistinctAvailableBooks;
    topic->numberOfDistinctAvailableBooks++;

    booksCount = topic->numberOfDistinctAvailableBooks;

    topic->bookshelf=(book*)realloc(topic->bookshelf,(booksCount)*sizeof(book));

    topic->bookshelf[indexOfCurrentBook].price=0;
    topic->bookshelf[indexOfCurrentBook].quantityOfBook=0;
    topic->bookshelf[indexOfCurrentBook].releaseYear=0;
    topic->bookshelf[indexOfCurrentBook].isDeleted=0;
    topic->bookshelf[indexOfCurrentBook].isBookPartOfSeries=0;
    strcpy(topic->bookshelf[indexOfCurrentBook].nameOfGenre,topic->nameOfGenre);

    fillNewBookInfo(indexOfCurrentBook,&topic->bookshelf[indexOfCurrentBook],topic);
    topic->totalNumberOfBooks+=topic->bookshelf[indexOfCurrentBook].quantityOfBook;
}
int validateOrderedBookName(int indexOfCurrentBook, int sizeOfBookArray,char* newBookName, book*BookArray)
{

    for(int i =0; i<sizeOfBookArray; i++)
    {
        if(strcmp(BookArray[i].titleOfBook,newBookName)==0)
        {
            return i;
        }
    }

    return -1;
}
int getOrderedBookIndex(char* newBookName,genre*topic)
{

    for(int i =0; i<topic->numberOfDistinctAvailableBooks; i++)
    {
        if(strcmp(topic->bookshelf[i].titleOfBook,newBookName)==0)
        {
            return i;
        }
    }

    return -1;
}
int searchForBookName(int indexOfCurrentBook, char* newBookName,genre*topic)
{
    int currentIndex=(topic->numberOfDistinctAvailableBooks)-1;
    if(currentIndex==0)
    {
        return -1;
    }
    else
    {
        for(int i =0; i<currentIndex; i++)
        {
            if(strcmp(topic->bookshelf[i].titleOfBook,newBookName)==0)
            {
                return i;
            }
        }
    }
    return -1;
}
void fillNewBookInfo(int indexOfCurrentBook,book* BOOK,genre*topic)
{
    system("cls");
    Sleep(500);

    printf("Enter The Book Title : ");
    /*
    try 1 : gets(BOOK->titleOfBook); //buffer contained \0 which caused this input to be skipped next time
    try 2: fgets(BOOK->titleOfBook, sizeof(BOOK->titleOfBook), stdin); // fgets is better than gets because it checkes the boundries of the char array
    BOOK->titleOfBook[strcspn(BOOK->titleOfBook, "\n")] = '\0'; // remove trailing newline*/
    // try 3 :
    scanf(" %[^\n]s",BOOK->titleOfBook);
    while(searchForBookName(indexOfCurrentBook,BOOK->titleOfBook,topic)>=0)
    {
        printf("a Book titled : %s already exists !\n\n", BOOK->titleOfBook);
        printf("Please Enter a Different Book Title  : ");
        scanf(" %[^\n]s",BOOK->titleOfBook);
    }

    printf("\nIs %s part of a series ? (y/n):",BOOK->titleOfBook);

    char choice;
    do  // validate input
    {
        scanf(" %c", &choice);

        if(choice=='y'||choice=='Y')
        {
            BOOK->isBookPartOfSeries=1;
        }
        else  if(choice=='n'||choice=='N')
        {
            BOOK->isBookPartOfSeries=0;
        }
        else
        {
            printf("\nincorrect answer please choose either 'y' or 'n'  :");
        }

    }//                          true if it is  y                                          true if it is  n
    while( ! ( ( choice == 'y' || choice == 'Y' ) || ( choice == 'n' || choice == 'N' ) ) );

    printf("\nEnter The Author Name : ");
    scanf(" %[^\n]s",BOOK->authorOfBook);

    printf("\nEnter a short description about %s: ",BOOK->titleOfBook);
    scanf(" %[^\n]s",BOOK->describtionOfBook);

    printf("\nEnter the Language  (ex.EN,AR) :");
    scanf(" %s",BOOK->language);

    int testingInteger; // a temp for testing the value before storing it .

    printf("\nEnter the release Year (ex.2020) :");
    scanf("%d",&testingInteger);

    while(testingInteger <= 0 || testingInteger >= 2024  )  // validate input .
    {
        printf("\nIncorrect Year !!\nEnter a Valid Year between 0 and 2023 :");
        scanf("%d",&testingInteger);
    }
    BOOK->releaseYear=testingInteger;
    float testingFloat=0;
    printf("\nEnter Price : ");
    scanf("%f",& testingFloat);

    while( testingFloat < 0   )  // validate input .
    {
        printf("\nPrice cannot be a negative Value !!\nEnter a Valid Price:");
        scanf("%f",& testingFloat);
    }
    BOOK->price= testingFloat;

    printf("\nEnter In-Stock Amount : ");
    scanf("%d",&testingInteger);

    while(testingInteger < 0   ) // validate input .
    {
        printf("\nAmount cannot be a negative Value !!\nEnter a Valid Amount:");
        scanf("%d",&testingInteger);
    }
    BOOK->quantityOfBook=testingInteger;
    BOOK->isDeleted=0;
}
void displayBook(book BOOK)
{
    printf("\nTitle :\t%s ",BOOK.titleOfBook);
    printf("\nWritten By :\t%s ",BOOK.authorOfBook);
    printf("\nDescription :\n\n %s",BOOK.describtionOfBook);
    printf("\nLanguage :\t%s",BOOK.language);
    printf("\nRelease Year  :\t%d",BOOK.releaseYear);
    printf("\nPrice :\t%f$ ",BOOK.price);
    printf("\nAmount :\t%d\t In-Stock\n ",BOOK.quantityOfBook);
}
void displayAllBooksInGenreInDetail(genre* topic)
{
    int Empty=1;
    for( int i =0, k=1; i<topic->numberOfDistinctAvailableBooks ; i++,k++)
    {
        printf("\n---------------------------------(%d)---------------------------------\n",k);
        if(topic->bookshelf[i].isDeleted==0)
        {
            displayBook(topic->bookshelf[i]);
            Empty=0;
        }
    }
    if(topic->numberOfDistinctAvailableBooks==0||Empty)
    {
        printf("\nthere are no added books to show in this '%s' genre \nplease add a book first\n\n",topic->nameOfGenre);
    }

    Sleep(2000);
}
void displayBookList(genre* topic)
{
    int Empty=0;
    for( int i =0,k=1 ; i<topic->numberOfDistinctAvailableBooks; i++,k++)
    {
        Empty=1;
        printf("\n-----------------------------------------------------------------------------------------------------------\n");
        if(topic->bookshelf[i].isDeleted==0)
        {
            printf("%d)  %s\t\tin-stock :  %d copies\t\tPrice :  %f $\n",k,topic->bookshelf[i].titleOfBook,topic->bookshelf[i].quantityOfBook,topic->bookshelf[i].price);
            Empty=0;
        }
    }
    if(topic->numberOfDistinctAvailableBooks==0||Empty)
    {
        printf("\nthere are no added books to show in this '%s' genre \nplease add a book first\n\n",topic->nameOfGenre);
    }
    Sleep(2000);
}
void removeBook(book* BOOK)
{
    BOOK->isDeleted=1;
    BOOK->quantityOfBook=0;

    printf("/nbook is removed successfully/n");
}
void increaseBookQuantity(book* BOOK)
{

    int increment;
    printf("\nEnter number of new copies to add : ");
    scanf("%d",&increment);
    BOOK->quantityOfBook+=increment;
}
int selectingbook(genre* topic)
{
    if(topic->numberOfDistinctAvailableBooks>0)
    {
        printf("\nSelect a book from the list Provided Below (type the number of the selected book):");
        displayBookList(topic);

        int index;
        scanf(" %d",&index);
        while((index>topic->numberOfDistinctAvailableBooks)||(index<1))
        {
            printf("\ninvalid choice !!\nPlease Select a book from the list Provided above :");
            scanf(" %d",&index);
        }

        return --index;
    }
    else
    {
        printf("\nthere are no books to show please add books first\n:");
        return -1;
    }

}
void order(bookstore* NabilaForBooks)
{
    book* orderedBooks=(book*)malloc(50*sizeof(book));
    int indexOfGenre=0,
        numOfOrderedbooks=0,
        indexOfBook=0,
        totalPrice=0,
        copies[50]= {0},
                    flag_Ordered_a_book_from_genre=0,
                    genraCounterForCheck=0,
                    temp_books_number =0;
    int  increment=0;
    char bookChoice='y',genChoice;

    do
    {

        indexOfGenre=selectingbookGenre(NabilaForBooks);
        genraCounterForCheck++;
        system("cls");
        do
        {
            if(flag_Ordered_a_book_from_genre)
            {
                printf("select another book from this genre ?(press y to continue )");
                scanf(" %c", &bookChoice);
            }

            if(bookChoice=='y'|| bookChoice=='Y')
            {
                if (NabilaForBooks->inventory[indexOfGenre].numberOfDistinctAvailableBooks>0&&NabilaForBooks->inventory[indexOfGenre].totalNumberOfBooks>0)
                {
                    flag_Ordered_a_book_from_genre=1;
                    system("cls");
                    indexOfBook=selectingbook(&NabilaForBooks->inventory[indexOfGenre]);
                    system("cls");
                    if(NabilaForBooks->inventory[indexOfGenre].bookshelf[indexOfBook].quantityOfBook==0)
                    {
                        printf("\nthis book is not available right now sorry.\n");
                    }
                    else if (validateOrderedBookName(indexOfBook,numOfOrderedbooks,NabilaForBooks->inventory[indexOfGenre].bookshelf[indexOfBook].titleOfBook,orderedBooks)!=-1)
                    {
                        int  indexofTempBook=0;
                        indexofTempBook=validateOrderedBookName(indexOfBook,numOfOrderedbooks,NabilaForBooks->inventory[indexOfGenre].bookshelf[indexOfBook].titleOfBook,orderedBooks);

                        copies[indexofTempBook] +=increment;
                        temp_books_number = (NabilaForBooks->inventory[indexOfGenre].bookshelf[indexOfBook].quantityOfBook)-copies[indexofTempBook];
                        printf("\nnumber of available copies of %s are : %d copies\n ",NabilaForBooks->inventory[indexOfGenre].bookshelf[indexOfBook].titleOfBook, temp_books_number);
                        printf("\nenter number of required copies :");
                        scanf(" %d",& increment);
                        while(  increment>temp_books_number||increment<=0)
                        {
                            printf("\nthat number can NOT exceed number of available copies and \n\n that number can NOT be 0 or less\n");
                            printf("\nre-enter number of required copies :");
                            scanf(" %d",&increment);
                        }
                    }
                    else
                    {

                        printf("\nnumber of available copies of %s are : %d copies\n ",NabilaForBooks->inventory[indexOfGenre].bookshelf[indexOfBook].titleOfBook,NabilaForBooks->inventory[indexOfGenre].bookshelf[indexOfBook].quantityOfBook);
                        printf("\nenter number of required copies :");
                        scanf(" %d",&copies[numOfOrderedbooks]);
                        while(copies[numOfOrderedbooks]>(NabilaForBooks->inventory[indexOfGenre].bookshelf[indexOfBook].quantityOfBook)||copies[numOfOrderedbooks]<=0)
                        {
                            printf("\nthat number can NOT exceed number of available copies and \n\n that number can NOT be 0 or less\n");
                            printf("\nre-enter number of required copies :");
                            scanf(" %d",&copies[numOfOrderedbooks]);
                        }

                        orderedBooks[numOfOrderedbooks].price=0;
                        orderedBooks[numOfOrderedbooks].quantityOfBook=0;
                        orderedBooks[numOfOrderedbooks].releaseYear=0;
                        orderedBooks[numOfOrderedbooks].isDeleted=0;
                        orderedBooks[numOfOrderedbooks].isBookPartOfSeries=0;
                        strcpy(orderedBooks[numOfOrderedbooks].nameOfGenre,NabilaForBooks->inventory[indexOfGenre].nameOfGenre);

                        orderedBooks[numOfOrderedbooks]=NabilaForBooks->inventory[indexOfGenre].bookshelf[indexOfBook];

                        numOfOrderedbooks++;
                    }
                }
                else
                {
                    printf("No more books in this genre.\n");
                    break;
                }
            }
        }
        while(bookChoice=='y'||bookChoice=='Y');
            if(genraCounterForCheck)
        {
            printf("select from another genre? (y to continue ,any other key to finish):");
            scanf(" %c", &genChoice);
        }
        flag_Ordered_a_book_from_genre=0;
        indexOfBook = 0;
        bookChoice='y';
        system("cls");
    }
    while(genChoice=='y'||genChoice=='Y');
    system("cls");

    for(int j=0,k=1; j<numOfOrderedbooks; j++)
    {
        printf("%d)  %s\t\tin-stock :  %d copies\t\tPrice :  %f $\n",k,orderedBooks[j].titleOfBook,copies[j],orderedBooks[j].price);
        totalPrice+=copies[j]*orderedBooks[j].price;
        k++;
    }
    printf("\t\t\t\t\t\t\t\t\t\tTotal Price :%d$\n",totalPrice);

    printf("\nConfirm ? ");
    printf("\n(press y to continue , any other key to cancel)");
    char x;
    scanf(" %c",&x);
    if( x=='y'||x=='Y')
    {
        for(int n=0; n<numOfOrderedbooks; n++)
        {
            int indexOfCurrentGenre=-1,indexOfCurrentBook=-1;

            indexOfCurrentGenre=getOrderedGenreIndex(orderedBooks[n].nameOfGenre,NabilaForBooks);
            indexOfCurrentBook=getOrderedBookIndex(orderedBooks[n].titleOfBook,&NabilaForBooks->inventory[indexOfCurrentGenre]);

            NabilaForBooks->inventory[indexOfCurrentGenre].bookshelf[indexOfCurrentBook].quantityOfBook-=copies[n];
            NabilaForBooks->inventory[indexOfCurrentGenre].totalNumberOfBooks-=copies[n];


        }
        printf("\norder completed successfully\n");
        Sleep(1500);
    }
    else
    {
        printf("\norder canceled\n");
        Sleep(1500);

    }
    Sleep(5000);
}

int main()
{
    bookstore NabilaForBooks=initializeBookstoreSystem(); //creates the bookstore struct to store all the data
    mainMenu(&NabilaForBooks);
    return 0;
}


