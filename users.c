//
// Created by coral on 2021/3/27.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "users.h"
#include "book_mangement.h"

void user_menu(User* account)
{
    while (1)
    {

        printf("+---------------------------------------------+\n\n");
        printf("Dear,%s\n\n Welcome!\n\n", account->user_name);
        printf("Please operate according to the number\n\n");
        printf("1 Borrow Management\n\n");
        printf("2 Return book Management\n\n");
        printf("3 Browse the borrowing history\n\n");
        printf("4 Browse books\n\n");
        printf("5 Change the account information\n\n");
        printf("6 Delete account\n\n");
        printf("7 Quit\n\n");
        printf("+---------------------------------------------+\n\n");
        int op; scanf("%d", &op); system("cls");
        switch (op)
        {
            case 1: borrow_book(account); break;
            case 2: return_book(account); break;
            case 3: history(account); system("pause"); system("cls"); break;
            case 4: browse_book(); system("pause"); system("cls"); break;
            case 5: user_change(account);  break;
            case 6: if (delete_user(account))
                {
                    printf("This account has been deleted, please log in again\n\n");
                    system("pause"); system("cls");
                    return;
                }
                else break;
            case 0: printf("Account logout is successful!\n\n"); system("pause"); system("cls"); return;
            default: printf("Sorry, your input is wrong. Please input again!\n\n"); system("pause"); system("cls"); break;
        }
    }
}

void user_change(User* account)  //Change user information
{
    printf("Dear：%s\t You could now change your personal information!\n\n", account->user_name);
    printf("Please input your new password (no more than 30 characters):\n\n");
    char password[30];
    scanf("%s", password);
    while(strlen(password)>30){
        printf("Your password is too long! Please input again!");
        system("pause"); system("cls"); return;
        printf("Please input your new password (no more than 30 characters):\n\n");
        scanf("%s", password);
    }
    strcpy(account->password, password);
    printf("Dear%s\t, your password has been changed\n\n", account->user_name);
    printf("Please input your new name:\n\n");
    char ID[100];
    scanf("%s", ID);
    strcpy(account->ID, ID);
    printf("Dear%s\t, your name has been changed!\n\n", account->user_name);
    save();
    printf("Dear%s\t, your personal infoemation has been changed successfully!\n\n", account->user_name);
    system("pause"); system("cls");
}

int delete_user(User* account)  //Delete the account
{
    printf("********************************************\n\n");
    if (!strcmp(account->user_name, leeds->user_name))
    {
        printf("The user %s has the highest authority, so it can not be deleted\n\n", leeds->user_name);
        system("pause"); system("cls"); return 0;
    }
    printf("Whether delete the user%s？\n\n", account->user_name);
    printf("Please input number to continue your operation.\n\n");
    printf("1 yes\t0 no\n\n");
    int op;  scanf("%d", &op);
    if (op == 1)
    {
        if (account->user_book.borrow_amount)
        {
            printf("Delete failed! This user has %d books which need return. \n\n", account->user_book.borrow_amount);
        }
        else
        {
            User* tp = (User*)malloc(sizeof(User));
            tp = user_head;
            User* np = (User*)malloc(sizeof(User));
            np = user_head->next;
            while (np)
            {
                if (!strcmp(np->user_name, account->user_name))
                {
                    tp->next = np->next;
                    free(np); --user_amount;
                    save();
                    printf("This user has been deleted successfully!\n\n");
                    system("pause"); system("cls");
                    return 1;
                }
                tp = np;
                np = np->next;
            }
        }
    }
    else if (!op) printf("This operation has been cancel\n\n");
    else printf("Sorry, your input is wrong. Please input again!\n\n");
    system("pause"); system("cls"); return 0;
}

void borrow_book(User* account)  //Borrow Management
{
    printf("Dear %s, please input your name \n\n", account->user_name);
    char ID[30]; scanf("%s", ID); system("cls");
    if (strcmp(account->ID, ID))
    {
        printf("Sorry, your name is wrong! Please input again.\n\n");
        system("pause"); system("cls"); return;
    }
    int ans = account->user_book.borrow_amount, Max = account->user_book.max_amount;

    findbook();
    printf("Please enter the serial number of the books you need to borrow:\n");
    char isbn[100];

    scanf("%s", isbn);

    if(serch_booknumber(isbn)==NULL){
        system("cls");
        printf("Please correctly input the existing book serial number in the picture above!\n");
        system("pause");
        system("cls");
        return;
    }
    else{

        Book* bk = serch_booknumber(isbn);
        if(bk->cnt<=0){
            system("cls");
            printf("Sorry, this book has been borrowed out!\n ");
            system("pause"); system("cls");
            return;
        }
        bk->cnt=bk->cnt-1;







        account->user_book.borrow_book[ans] = *bk;


        ++account->user_book.borrow_amount;
        save();
        printf("Dear%s, you borrow book %s successfully!\n", account->user_name, bk->title);
        system("pause"); system("cls");



        system("pause"); system("cls");
    }
}

void return_book(User * account)  //Returning Management Module
{


    while (1)
    {
        history(account);
        int pan=0;

        if (!account->user_book.borrow_amount)
        {
            system("pause"); system("cls"); return;
        }
        printf("Please enter the number of the book you need to return (enter -1 to exit the book return system)!\n");
        char num[100],title[100];scanf("%s",num);
        int i;
        for(i=0;i<account->user_book.borrow_amount;i++){
            if(!strcmp(num,account->user_book.borrow_book[i].isbn)){
                Book* np = find_book_bu_isbn(num);
                strcpy(title, account->user_book.borrow_book[i].title);
                np->cnt=np->cnt+1;
                pan = 1;
                break;
            }


        }
        if(pan==0){
            system("cls");
            printf("Sorry, you do not borrow this book!");
            return;

        }


        for (; i < account->user_book.borrow_amount; ++i)
        {
            account->user_book.borrow_book[i] = account->user_book.borrow_book[i + 1];
            account->user_book.borrow_time[i] = account->user_book.borrow_time[i + 1];
            account->user_book.return_time[i] = account->user_book.return_time[i + 1];
        }
        --account->user_book.borrow_amount;
        save();
        printf("Book %s returned successfully!\n", title);

        system("pause"); system("cls");
    }
}

void history(User * account)  //History borrowing for browsing
{
    int n = account->user_book.borrow_amount;
    printf("*************************************************************\n");
    printf("Dear, %s\n", account->user_name);
    if (!n)
    {
        printf("There is no book borrowing record!\n"); return;
    }
    printf("The number of borrowing book:\n");
    for (int i = 0; i < n; ++i)
    {
        struct node t = account->user_book;


        printf("\n%d:\n", i + 1);
        printf("  title:%s\n", t.borrow_book[i].title);
        printf("  author:%s\n", t.borrow_book[i].author);
        printf("  year:%s\n", t.borrow_book[i].year);
        printf("  number:%s\n", t.borrow_book[i].isbn);

    }
}


/********Administrator function area***********/
void admin_initi()  //Super administrator account initialization
{
    FILE* fp = fopen("user.bin", "wb");
    if (fp == NULL)
    {
        printf("Failed to initialize administrator authority!\n"); exit(0);
    }
    leeds = (User*)malloc(sizeof(User));
    strcpy(leeds->user_name, "leeds");
    strcpy(leeds->password, "leeds");
    strcpy(leeds->ID, "leeds");
    leeds->admin = 1;
    leeds->next = NULL;

    user_head->next = leeds;
    user_amount = 1;
    save();
    fclose(fp);
}

User* serch_username(char* name)  //Find the username
{
    User* np = user_head->next;
    while (np)
    {
        if (!strcmp(np->user_name, name)) return np;
        np = np->next;
    }
    return NULL;
}

void admin_menu(User * account)  //Administrator menu
{
    while (1)
    {

        printf("*************************************************\n");
        printf("Dear administrator, %s\n\n       Welcome you!\n\n", account->user_name);
        printf("Please operate according to the number\n\n");
        printf("1 increase books\n\n");
        printf("2 delete books\n\n");
        printf("3 browse books\n\n");
        printf("4 Quit\n\n");
        printf("*************************************************\n\n");
        char py[100];
        int op; scanf("%s", py); system("cls");
        switch (op=atoi(py))
        {
            case 1: add_book(); break;
            case 2: delete_book(); break;
            case 3: browse_book(); system("pause"); system("cls"); break;
            case 4: printf("Exit the admin account successfully!\n"); system("pause"); system("cls"); return;
            default: printf("Sorry, your input is wrong. Please input again!\n"); system("pause"); system("cls"); break;
        }
    }
}

void query_user()  //User Information Inquiry
{
    int cnt = 1;
    User* np = (User*)malloc(sizeof(User));
    np = user_head->next;
    printf("number  username\t\tpassword\t\tname\t\twhether administrator\n");
    while (np)
    {
        printf("%d %-20s %-20s %-20s", cnt, np->user_name, np->password, np->ID);
        if (np->admin) printf(" yes\n");
        else printf(" no\n");
        np = np->next;
        ++cnt;
    }
}











void main_menu()  //Main menu
{
    load();
    while (1)
    {
        printf("*************************************************\n\n");
        printf("Welcome to use the management system of books!\n\n");
        printf("1 users registe\n\n");
        printf("2 users login\n\n");
        printf("3 Administrator login\n\n");
        printf("4 Quit\n\n");
        printf("*************************************************\n\n");
        printf("Please operate according to the number:");
        char py[100];
        int op; scanf("%s", py); system("cls");
        switch (op=atoi(py))
        {
            case 1: user_register(); break;
            case 2: user_login();  break;
            case 3: admin_login();  break;
            case 4: return;
            default: printf("Sorry, your input is wrong. Please input again!\n\n"); system("pause"); system("cls"); break;
        }
    }
}

void user_register()  //users register
{
    char name[30];
    printf("Please input your username(less than 30 alphabet):\n\n");
    scanf("%s", name);

    while(strlen(name)>30){
        printf("Your username is too long! Please input again!");
        system("pause"); system("cls");
        printf("Please input your username(less than 30 alphabet):\n\n");
        scanf("%s", name);
    }
    User* account;
    while(account = serch_username(name), account != NULL)
    {
        printf("This username exist! Please change and input again! \n\n");
        system("pause"); system("cls");
        printf("Please input your username(less than 30 alphabet):\n\n");
        scanf("%s", name);
    }
    printf("Please input your password!(less than 30 alphabet):\n\n");
    char password[30];
    scanf("%s", password);
    while(strlen(password)>30){
        printf("Your username is too long! Please input again!");
        system("pause"); system("cls");
        printf("Please input your password!(less than 30 alphabet):\n\n");
        scanf("%s", password);
    }
    printf("Please input your name:\n\n");
    char ID[30];
    scanf("%s", ID);
    creat_user_list(name, password, ID);
    printf("Dear %s, you successfully registe the account!\n\n",name);
    ++user_amount;
    system("pause"); system("cls");
}

void user_login()  //users log in
{
    char name[30];
    printf("Please input your username:(less than 30 alphabet): \n\n");
    scanf("%s", name);
    User* account;
    if (account = serch_username(name), account == NULL)
    {
        printf("The username is not be registed! Please registe or login again! \n\n");
        system("pause"); system("cls"); return;
    }
    printf("Please input your password!(less than 30 alphabet)\n\n");
    scanf("%s", name);
    if (strcmp(account->password, name))
    {
        printf("Password is wrong, please log in again\n\n");
        system("pause"); system("cls"); return;
    }
    printf("Log in successfully! You will go to the user page!\n\n");
    system("pause"); system("cls");
    user_menu(account);
}

void admin_login()  //Administrator log in
{
    char name[30];
    printf("Dear Administrator:\n\n");
    printf("Please input your username(less than 30 alphabet):\n\n");
    scanf("%s", name);
    while(strlen(name)>30){
        printf("\n\nYour username is too long! Please input again!");
        system("pause"); system("cls");
        printf("Dear Administrator:\n\n");
        printf("Please input your username(less than 30 alphabet):\n\n");
        scanf("%s", name);
    }
    User* account;
    if (account = serch_username(name), account == NULL)
    {
        printf("\n\nSorry the username is not exist, please input again!\n\n");
        system("pause"); system("cls"); return;
    }
    if (!account->admin)
    {
        printf("\n\nSorry, your usrename do not have the jurisdiction of administrator! Please contect other administraror!\n\n");
        system("pause"); system("cls"); return;
    }
    printf("\n\nPlease input your password(less than 30 alphabet)\n\n");
    scanf("%s", name);
    while(strlen(name)>30){
        printf("\n\nDear Administrator:\n\n");
        printf("Your username is too long! Please input again!\n");
        printf("Please input your username(less than 30 alphabet):\n\n");
        scanf("%s", name);
    }
    if (strcmp(account->password, name))
    {

        printf("\n\nPassword is wrong, please log in again!\n\n");
        system("pause"); system("cls"); return;
    }
    system("cls");
    printf("\n\nDear %s, you successfully log in the account!\n\n",name);
    system("pause"); system("cls");
    admin_menu(account);
}

//Core functional area
void creat_user_list(char* name, char* password, char* ID)  //Create a linked list of users
{
    User* np = (User*)malloc(sizeof(User));
    np = user_head;
    while (np->next) np = np->next;
    User* tp = (User*)malloc(sizeof(User));
    strcpy(tp->user_name, name);
    strcpy(tp->password, password);
    strcpy(tp->ID, ID);
    tp->admin = 0;
    tp->next = NULL;

    np->next = tp;
    save();
}
