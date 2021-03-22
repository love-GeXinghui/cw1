//图书管理系统（单链表版）
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct book //图书
{
    char title[100];  //书名
    char isbn[100];  //书号
    char author[100];  //作者
    char publisher[100];  //出版社
    int cnt; //书籍数量
    struct book* next;  //下一本书籍
}Book;
Book* book_head;  //图书头指针
int book_amount;  //图书总数量

struct node //用户所借书籍
{
    int borrow_amount, max_amount; //所借书籍数量， 最大借书数
    double tax;  //超出时限收费比率
    time_t borrow_time[10], return_time[10];  //借、还时间
    Book borrow_book[10];  //每位最多借10本书籍
};

typedef struct user //用户
{
    char user_name[30];  //用户名
    char password[30];  //密码
    char ID[30]; //有效证件号码
    int admin;  //是否管理员
    struct node user_book;  //用户所借书籍
    struct user* next;  //下一位用户
}User;
User* user_head;  //用户头指针
User* leeds;  //超级管理员账号
int user_amount;  //用户总数量

//程序功能区
void welcome_page();  //欢迎页面
void producer_infor();  //制作人员信息
void manual();  //使用手册
void main_menu();  //主菜单

//主菜单功能区
void user_register();  //用户注册
void user_login();  //用户登录
void admin_login();  //管理员登陆

//核心功能区
void creat_user_list(char*, char*, char*);  //创建用户链表
void creat_book_list(char*, char*, char*, char*, int);  //创建图书链表
void user_initi(User*);  //用户图书管理初始化
void load();  //从文件中加载数据
void save();  //保存数据到文件

//用户功能区
void user_menu(User*);  //用户菜单
void user_change(User*);  //更改用户信息
int delete_user(User*);  //删除账号
void borrow_book(User*);  //借阅管理
void return_book(User*);  //还书管理
void history(User*);  //历史借阅浏览

//管理员功能区
void admin_initi();  //超级管理员账号初始化
User* serch_username(char*);  //查找用户名
void admin_menu(User*);  //管理员菜单
void query_user();  //用户信息查询
void admin_user();  //管理用户信息
void all_history(); //查看用户图书借阅归还情况
User* serch_user();  //按序号搜索用户
void set_admin(User*);  //设置管理员

//图书管理功能区
void add_book();  //增加图书信息
void delete_book();  //删除图书信息
void browse_book();  //图书浏览

int main()
{
    welcome_page();
    printf("You successfully quit the system! Thank you for using it!\n");
    system("pause"); system("cls");
    return 0;
}

/********程序功能区***********/
void welcome_page()  //欢迎页面
{
    load();
    while (1)
    {

        printf("          +---------------------------------------------+\n");
        printf("          Welcome to use the management system of books!\n");

        printf("          Please operate according to the number!\n");
        printf("          1 go to the function page\n");
        printf("          2 the account of Super Administrator \n");

        printf("          0 Quit\n");
        printf("          +---------------------------------------------+\n");
        int op; scanf("%d", &op); system("cls");
        switch (op)
        {
            case 1: main_menu(); break;
            case 2:manual(); break;
            case 0: return;
            default: printf("Sorry, your input is wrong. Please input again!\n"); system("pause"); system("cls"); break;
        }
    }
}

void manual() //使用手册
{
    printf("*******************************************************************************\n");
    printf("User notice:\nInitial administrator account：leeds\tpassword：leeds\n name：leeds\n\n");
    printf("*******************************************************************************\n");
    system("pause"); system("cls");
}

void main_menu()  //主菜单
{
    while (1)
    {
        printf("+---------------------------------------------+\n");
        printf("          Welcome to use the management system of books!\n");
        printf("          Please operate according to the number\n");
        printf("          1 users registe\n");
        printf("          2 users login\n");
        printf("          3 Administrator login\n");
        printf("          0 Quit\n");
        printf("+---------------------------------------------+\n");
        int op; scanf("%d", &op); system("cls");
        switch (op)
        {
            case 1: user_register(); break;
            case 2: user_login();  break;
            case 3: admin_login();  break;
            case 0: return;
            default: printf("Sorry, your input is wrong. Please input again!\n"); system("pause"); system("cls"); break;
        }
    }
}


/********主菜单功能区***********/
void user_register()  //用户注册
{
    char name[30];
    printf("Please input your username(less than 30 alphabet)：\n");
    scanf("%s", name);
    printf("%d",strlen(name));
    if(strlen(name)>30){
        printf("Your username is too long! Please input again!");
        system("pause"); system("cls"); return;
    }
    User* account;
    if (account = serch_username(name), account != NULL)
    {
        printf("This username exist! Please change and input again! \n");
        system("pause"); system("cls"); return;
    }
    printf("Please input your password!(less than 30 alphabet)：\n");
    char password[30];
    scanf("%s", password);
    if(strlen(password)>30){
        printf("Your username is too long! Please input again!");
        system("pause"); system("cls"); return;
    }
    printf("Please input your name：\n");
    char ID[30];
    scanf("%s", ID);
    creat_user_list(name, password, ID);
    printf("Dear %s, you successfully registe the account!\n",name);
    ++user_amount;
    system("pause"); system("cls");
}

void user_login()  //用户登录
{
    char name[30];
    printf("Please input your username:(less than 30 alphabet): \n");
    scanf("%s", name);
    User* account;
    if (account = serch_username(name), account == NULL)
    {
        printf("The username is not be registed! Please registe or login again! \n");
        system("pause"); system("cls"); return;
    }
    printf("Please input your password!(less than 30 alphabet)\n");
    scanf("%s", name);
    if (strcmp(account->password, name))
    {
        printf("Password is wrong, please log in again\n");
        system("pause"); system("cls"); return;
    }
    printf("Log in successfully! You will go to the user page!\n");
    system("pause"); system("cls");
    user_menu(account);
}

void admin_login()  //管理员登陆
{
    char name[30];
    printf("Dear Administrator:\n");
    printf("Please input your username(less than 30 alphabet):\n");
    scanf("%s", name);
    User* account;
    if (account = serch_username(name), account == NULL)
    {
        printf("Sorry the username is not exist, please input again!\n");
        system("pause"); system("cls"); return;
    }
    if (!account->admin)
    {
        printf("Sorry, your usrename do not have the jurisdiction of administrator! Please contect other administraror!\n");
        system("pause"); system("cls"); return;
    }
    printf("Please input your password(less than 30 alphabet)\n");
    scanf("%s", name);
    if (strcmp(account->password, name))
    {
        printf("Password is wrong, please log in again!\n");
        system("pause"); system("cls"); return;
    }
    printf("Dear %s, you successfully registe the account!\n",name);
    system("pause"); system("cls");
    admin_menu(account);
}

/********核心功能区***********/
void creat_user_list(char* name, char* password, char* ID)  //创建用户链表
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
    user_initi(tp);
    np->next = tp;
    save();
}

void creat_book_list(char* title, char* isbn, char* author, char* publisher, int cnt)  //创建图书链表
{
    Book* np = (Book*)malloc(sizeof(Book));
    np = book_head;
    while (np->next) np = np->next;
    Book* tb = (Book*)malloc(sizeof(Book));
    strcpy(tb->title, title);
    strcpy(tb->isbn, isbn);
    strcpy(tb->author, author);
    strcpy(tb->publisher, publisher);
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