//
// Created by coral on 2021/3/27.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "users.h"
#include "book_mangement.h"

void creat_book_list(char* title, char* isbn, char* author, char* publisher, char* year, int cnt)  //创建图书链表
{
    Book* np = (Book*)malloc(sizeof(Book));
    np = book_head;
    while (np->next) np = np->next;
    Book* tb = (Book*)malloc(sizeof(Book));
    strcpy(tb->title, title);
    strcpy(tb->isbn, isbn);
    strcpy(tb->author, author);
    strcpy(tb->publisher, publisher);
    strcpy(tb->year, year );
    tb->cnt = cnt;
    tb->next = NULL;
    np->next = tb;
    save();
}

void user_initi(User* account)  //用户图书管理初始化
{
    account->user_book.borrow_amount = 0;
    account->user_book.max_amount = 10;
    account->user_book.tax = 1.0;
    memset(account->user_book.borrow_time, 0, sizeof(account->user_book.borrow_time));
    memset(account->user_book.return_time, 0, sizeof(account->user_book.return_time));
    memset(account->user_book.borrow_book, 0, sizeof(account->user_book.borrow_book));
}

void load()  //从文件中加载数据
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

void save()  //保存数据到文件
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

void add_book()  //增加图书信息
{
    char title[100], isbn[100], author[100], publisher[100], year[4];
    int cnt;
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

void delete_book()  //删除图书信息
{
    while (1)
    {
        browse_book();
        printf("Please enter the serial number of the book to be deleted(Enter -1 to exit the delete operation):\n");
        int cnt; scanf("%d", &cnt);
        if (cnt == -1)
        {
            printf("The deletion system has been successfully exited!\n"); system("pause"); system("cls");
            return;
        }
        else if (cnt > book_amount || cnt <= 0)
        {
            printf("Please correctly enter the number of books to be deleted in the picture above!\n");
        }
        else
        {
            Book* tb = (Book*)malloc(sizeof(Book));
            Book* np = (Book*)malloc(sizeof(Book));
            np = book_head;
            tb = book_head->next;
            for (int i = 1; i < cnt; ++i)
            {
                np = tb;
                tb = tb->next;
            }
            np->next = tb->next;
            free(tb); --book_amount;
            save();
            printf("The book has been removed from the library successfully!\n");
        }
        system("pause"); system("cls");
    }
}

void browse_book()  //图书浏览
{
    int cnt = 1;
    if (!book_amount)
    {
        printf("\n");
        return;
    }
    Book* tb = (Book*)malloc(sizeof(Book));
    tb = book_head->next;
    printf("There are no books in the library, please contact the librarian to add books!\n");
    printf("序号\t书名\t书号\t作者\t出版社\t年代\t总库存量\n");
    while (tb)
    {
        printf("%-4d《%s》 %-20s %-20s %-20s %-20s %d\n", cnt, tb->title, tb->isbn,
               tb->author, tb->publisher,tb->year ,tb->cnt);
        tb = tb->next; ++cnt;
    }
}

void findbook(){
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
        printf("Sorry, the book is not found! Please try to find other book!");
    };
    return a;
}

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
        printf("Sorry, the book is not found! Please try to find other book!");
    };
    return a;
}

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
        }
        np = np->next;
    }
    if(a==0){system("cls");
        printf("Sorry, the book is not found! Please try to find other book!");
    };
    return a;
}

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
