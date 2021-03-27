//
// Created by coral on 2021/3/27.
//

#ifndef CW1_USERS_H
#define CW1_USERS_H
typedef struct _Book
{
    char title[100];
    char isbn[100];
    char author[100];
    char publisher[100];
    char year[30];
    int cnt;
    struct _Book* next;
}Book;
struct node //用户所借书籍
{
    int borrow_amount, max_amount; //所借书籍数量， 最大借书数
    double tax;  //超出时限收费比率
    time_t borrow_time[10], return_time[10];  //借、还时间
    Book borrow_book[100];  //每位最多借10本书籍
};

typedef struct user //用户
{
    char user_name[30];  //用户名
    char password[30];  //密码
    char ID[100]; //有效证件号码
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

#endif //CW1_USERS_H
