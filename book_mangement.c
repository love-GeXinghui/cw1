//
// Created by coral on 2021/3/27.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "users.h"
#include "book_mangement.h"

void creat_book_list(char* title, char* isbn, char* author, int publisher, char* year, int cnt)  //创建图书链表
{
    Book* np = (Book*)malloc(sizeof(Book));
    np = book_head;
    while (np->next) np = np->next;
    Book* tb = (Book*)malloc(sizeof(Book));
    strcpy(tb->title, title);
    strcpy(tb->isbn, isbn);
    strcpy(tb->author, author);
    tb->publisher=publisher;
    strcpy(tb->year, year );
    tb->cnt = cnt;
    tb->next = NULL;
    np->next = tb;
    save();
}



void load()  //Load data from a file
{
    book_head = (Book*)malloc(sizeof(Book));
    book_head->next = NULL;
    book_amount = 0;

    FILE* fp2;
    fp2 = fopen("book.bin", "rb");
    if (fp2 == NULL)
    {
        fp2 = fopen("book.bin", "wb");
        if (fp2 == NULL)
        {
            printf("Book storage failed!\n\n"); exit(0);
        }
        fclose(fp2);
    }
    else
    {
        Book* bp = (Book*)malloc(sizeof(Book));
        bp = book_head;
        Book* tp = (Book*)malloc(sizeof(Book));
        while (fread(tp, sizeof(Book), 1, fp2))
        {
            bp->next = tp;
            ++book_amount;
            tp = tp->next;
            tp = (Book*)malloc(sizeof(Book));
            bp = bp->next;
        }
        fclose(fp2);
    }

    user_head = (User*)malloc(sizeof(User));
    user_head->next = NULL;
    user_amount = 0;

    FILE* fp1;
    fp1 = fopen("user.bin", "rb");
    if (fp1 == NULL)
    {
        admin_initi(); return;
    }
    User* np = (User*)malloc(sizeof(User));
    np = user_head;
    User* temp = (User*)malloc(sizeof(User));
    while (fread(temp, sizeof(User), 1, fp1))
    {
        np->next = temp;
        ++user_amount;
        temp = temp->next;
        temp = (User*)malloc(sizeof(User));
        np = np->next;
    }
    leeds = user_head->next;
    fclose(fp1);
}

void save()  //Save the data to a file
{
    FILE* fp = fopen("user.bin", "wb");
    User* temp = user_head->next;
    while (temp)
    {
        fwrite(temp, sizeof(User), 1, fp);
        temp = temp->next;
    }
    fclose(fp);

    fp = fopen("book.bin", "wb");
    Book* tb = book_head->next;
    while (tb)
    {
        fwrite(tb, sizeof(Book), 1, fp);
        tb = tb->next;
    }
    fclose(fp);
}

void add_book()  //Add Book Information
{
    char title[100], isbn[100], author[100],  year[4];
    int cnt,publisher;
    printf("Please enter the title of the book to be added:\n");
    scanf("%s", title);

    printf("Please enter the author of the book to be added:\n");
    scanf("%s", author);

    printf("Please enter the year of books to be added:\n");
    scanf("%s", year);
    printf("Please enter the amount of books to be added:\n");
    scanf("%d", &cnt);
    printf("Please input the number of the book:\n ");
    scanf("%s",isbn);
    publisher = cnt;
    Book* number;
    while(number = serch_booknumber(isbn),number != NULL)
    {
        printf("This number exist! Please change and input again! \n\n");
        system("pause"); system("cls");
        printf("\nPlease input the number of the book:\n");
        scanf("%s", isbn);
    }

    ++book_amount;
    creat_book_list(title, isbn, author, publisher,year, cnt);
    printf("Added book %s successfully!\n", title);
    system("pause"); system("cls");
}

Book* serch_booknumber(char* isbn)
{
    Book* np = book_head->next;
    while(np)
    {
        if(!strcmp(np->isbn,isbn))return np;
        np = np->next;
    }
    return NULL;
}

void delete_book()  //Delete book information
{
    while (1)
    {
        browse_book();
        printf("Please enter the serial number of the book to be deleted(Enter -1 to exit the delete operation):\n");
        char isbn[100];
        int cnt; scanf("%s", isbn);

        cnt = -1;
        if (cnt == atoi(isbn))
        {
            printf("The deletion system has been successfully exited!\n"); system("pause"); system("cls");
            return;
        }
        else if (find_book_bu_isbn( isbn)==NULL)
        {
            printf("Please correctly enter the number of books to be deleted in the picture above!\n");
        }
        else if(find_book_bu_isbn(isbn)->publisher!=find_book_bu_isbn(isbn)->cnt)
        {printf("The book is loaned so it cannot be deleted");}
        else
        {

            Book* np = book_head;
            Book* temp;
            while(np->next!=NULL)
            {
                if(!strcmp(np->next->isbn,isbn)){
                    temp=np->next;
                    np->next=temp->next;
                    free(temp);
                    break;
                }
                np = np->next;

            }

            --book_amount;
            save();
            printf("The book has been removed from the library successfully!\n");
        }
        system("pause"); system("cls");
    }
}

void browse_book()  //Browse book
{
    int cnt = 1;
    if (!book_amount)
    {
        printf("\n");
        printf("There are no books in the library, please contact the librarian to add books!\n");
        return;
    }
    Book* tb = (Book*)malloc(sizeof(Book));
    tb = book_head->next;

    printf("\ntitle           author          year            copies          number\n");
    while (tb)
    {
        printf("\n%-15s %-15s %-15s %-15d %-5s\n",tb->title,tb->author,tb->year,tb->cnt,tb->isbn);
        tb = tb->next; ++cnt;
    }
}

void findbook() //Find book
{
    int num,a=0;
    char title[30], author[30], year[30];
    Book* books;
    printf("1 find book by title\n\n");
    printf("2 find book by author\n\n");
    printf("3 find book by year\n\n");
    printf("Please input your way to find book:");
    scanf("%d",&num);
    do{
        if(num == 1)
        {

            printf("Please input the title: ");
            scanf("%s",title);

            if(find_book_by_title(title)==0)
            {


                a=1;
            }
            else{
                return;
            }

        }
        else if(num == 2){
            printf("Please input the author: ");
            scanf("%s",author);

            if(find_book_by_author(author)==0)
            {

                a=1;
            }

            else
            {
                return;
            }
        }
        else if(num == 3){
            printf("Please input the year: ");
            scanf("%s",year);


            if(find_book_by_year(year)==0)
            {

                a=1;
            }

            else{
                return;
            }
        }
        else{
            printf("Sorry, please input the right number!");
            printf("Please input your way to find book:");
            scanf("%d",num);
        }
    }while(a=1);
}

// Find book by the title of book
int find_book_by_title(char* title)
{
    int a=0;
    system("cls");
    Book* np = book_head->next;
    if(np!=NULL)printf("\ntitle           author          year            copies          number\n");
    while (np!=NULL)
    {
        if (strstr(np->title, title)){

            printf("\n%-15s %-15s %-15s %-15d %-5s\n",np->title,np->author,np->year,np->cnt,np->isbn);
            a=1;
        }
        np = np->next;
    }
    if(a==0){system("cls");
        printf("Sorry, the book is not found!\n Please try to find other book!\n");
    };
    return a;
}

// Find book by the author of book
int find_book_by_author(char* author)
{
    int a=0;
    system("cls");
    Book* np = book_head->next;
    if(np!=NULL)printf("\ntitle           author          year            copies          number\n");
    while (np!=NULL)
    {
        if (strstr(np->author, author)){

            printf("\n%-15s %-15s %-15s %-15d %-5s\n",np->title,np->author,np->year,np->cnt,np->isbn);
            a=1;
        }
        np = np->next;
    }
    if(a==0){system("cls");
        printf("Sorry, the book is not found!\n Please try to find other book!\n");
    };
    return a;
}

// Find book by the year of book
int find_book_by_year(char* year)
{
    int a=0;
    system("cls");
    Book* np = book_head->next;
    if(np!=NULL)printf("\ntitle           author          year            copies          number\n");
    while (np!=NULL)
    {
        if (strstr(np->year, year)){

            printf("\n%-15s %-15s %-15s %-15d %-5s\n",np->title,np->author,np->year,np->cnt,np->isbn);
            a=1;
        }
        np = np->next;
    }
    if(a==0){system("cls");
        printf("Sorry, the book is not found!\n Please try to find other book!\n");
    };
    return a;
}

// Find book by the isbn of book
Book* find_book_bu_isbn(char* isbn){
    int a=0;
    Book* np = book_head->next;
    while(np!=NULL)
    {
        if(!strcmp(np->isbn,isbn)){
            return np;
        }
        np = np->next;
    }
    return NULL;
}

