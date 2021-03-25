
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

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
void creat_book_list(char*, char*, char*, char*, char*, int);  //创建图书链表
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
	printf("You successfully quit the system! Thank you for using it!\n\n");
	system("pause"); system("cls");
	return 0;
}

/********程序功能区***********/
void welcome_page()  //欢迎页面
{
	load();
	while (1)
	{

		printf("+---------------------------------------------+\n\n");
		printf("Welcome to use the management system of books!\n\n");

		printf("Please operate according to the number!\n\n");
		printf("1 go to the function page\n\n");
		printf("2 the account of Super Administrator \n\n");

		printf("0 Quit\n\n");
		printf("+---------------------------------------------+\n\n");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: main_menu(); break;
		case 2:manual(); break;
		case 0: return;
		default: printf("Sorry, your input is wrong. Please input again!\n\n"); system("pause"); system("cls"); break;
		}
	}
}

void manual() //使用手册
{
	printf("*******************************************************************************\n\n");
	printf("User notice:\n\nInitial administrator account：leeds\tpassword：leeds\n\n name：leeds\n\n\n\n");
	printf("*******************************************************************************\n\n");
	system("pause"); system("cls");
}

void main_menu()  //主菜单
{
	while (1)
	{
		printf("+---------------------------------------------+\n\n");
		printf("Welcome to use the management system of books!\n\n");
		printf("Please operate according to the number\n\n");
		printf("1 users registe\n\n");
		printf("2 users login\n\n");
		printf("3 Administrator login\n\n");
		printf("0 Quit\n\n");
		printf("+---------------------------------------------+\n\n");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: user_register(); break;
		case 2: user_login();  break;
		case 3: admin_login();  break;
		case 0: return;
		default: printf("Sorry, your input is wrong. Please input again!\n\n"); system("pause"); system("cls"); break;
		}
	}
}


/********主菜单功能区***********/
void user_register()  //用户注册
{
	char name[30];
	printf("Please input your username(less than 30 alphabet)：\n\n");
	scanf("%s", name);

	while(strlen(name)>30){
		printf("Your username is too long! Please input again!");
		system("pause"); system("cls");
		printf("Please input your username(less than 30 alphabet)：\n\n");
		scanf("%s", name);
	}
	User* account;
	while(account = serch_username(name), account != NULL)
	{
		printf("This username exist! Please change and input again! \n\n");
		system("pause"); system("cls"); 
		printf("Please input your username(less than 30 alphabet)：\n\n");
		scanf("%s", name);
	}
	printf("Please input your password!(less than 30 alphabet)：\n\n");
	char password[30];
	scanf("%s", password);
	while(strlen(password)>30){
		printf("Your username is too long! Please input again!");
		system("pause"); system("cls");
		printf("Please input your password!(less than 30 alphabet)：\n\n");
		scanf("%s", password);
	}
	printf("Please input your name：\n\n");
	char ID[30];
	scanf("%s", ID);
	creat_user_list(name, password, ID);
	printf("Dear %s, you successfully registe the account!\n\n",name);
	++user_amount;
	system("pause"); system("cls");
}

void user_login()  //用户登录
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

void admin_login()  //管理员登陆
{
	char name[30];
	printf("Dear Administrator:\n\n");
	printf("Please input your username(less than 30 alphabet):\n\n");
	scanf("%s", name);
	User* account;
	if (account = serch_username(name), account == NULL)
	{
		printf("Sorry the username is not exist, please input again!\n\n");
		system("pause"); system("cls"); return;
	}
	if (!account->admin)
	{
		printf("Sorry, your usrename do not have the jurisdiction of administrator! Please contect other administraror!\n\n");
		system("pause"); system("cls"); return;
	}
	printf("Please input your password(less than 30 alphabet)\n\n");
	scanf("%s", name);
	if (strcmp(account->password, name))
	{
		printf("Password is wrong, please log in again!\n\n");
		system("pause"); system("cls"); return;
	}
	printf("Dear %s, you successfully registe the account!\n\n",name);
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


/********用户功能区***********/
void user_menu(User* account)  //用户菜单
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
		printf("0 Quit\n\n");
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

void user_change(User* account)  //更改用户信息
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

int delete_user(User* account)  //删除账号
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

void borrow_book(User* account)  //借阅管理
{
	printf("Dear %s, please input your name \n\n", account->user_name);
	char ID[30]; scanf("%s", ID); system("cls");
	if (strcmp(account->ID, ID))
	{
		printf("Sorry, your name is wrong! Please input again.\n\n");
		system("pause"); system("cls"); return;
	}
	while (1)
	{
		int ans = account->user_book.borrow_amount, Max = account->user_book.max_amount;
		if (ans == Max)
		{
			printf("用户%s：借阅图书数量 %d 本，已达上限 %d 本，请先归还部分图书！\n", account->user_name, ans, Max);
			system("pause"); system("cls"); return;
		}
		browse_book();
		printf("请输入您需要借阅的书籍序号(输入 -1 退出删除操作)：\n");
		int cnt; scanf("%d", &cnt);
		if (cnt == -1)
		{
			printf("已成功退出借阅系统！\n"); system("pause"); system("cls");
			return;
		}
		else if (cnt > book_amount || cnt <= 0)
		{
			printf("请正确输入上图中已有的图书序号！\n");
		}
		else
		{
			printf("请设置您需要借阅的时间(不超过90天)：\n");
			int day; scanf("%d", &day);
			if (day > 90 || day <= 0)
				printf("输入借阅时间不被允许，请重新输入！\n");
			else
			{
				Book* tb = (Book*)malloc(sizeof(Book));
				tb = book_head->next;
				for (int i = 1; i < cnt; ++i)
					tb = tb->next;
				account->user_book.borrow_book[ans] = *tb;
				account->user_book.borrow_time[ans] = time(NULL);
				account->user_book.return_time[ans] = time(NULL) + day * 3600 * 24;
				++account->user_book.borrow_amount;
				save();
				printf("用户%s：借阅图书《%s》成功！\n", account->user_name, tb->title);
			}
		}
		system("pause"); system("cls");
	}
}

void return_book(User * account)  //还书管理
{

	while (1)
	{
		history(account);
		if (!account->user_book.borrow_amount)
		{
			system("pause"); system("cls"); return;
		}
		printf("请输入您需要归还的书籍序号（输入-1以退出还书系统）！\n");
		int cnt = 0; scanf("%d", &cnt); system("cls");
		if (cnt == -1)
		{
			printf("正在退出还阅系统，请稍后...\n");
			system("pause"); system("cls"); return;
		}
		if (cnt > account->user_book.borrow_amount || cnt < 0)
		{
			printf("请正确输入上述书籍序号！\n");
		}
		else
		{
			int i = 0;
			for (--cnt; i < cnt; ++i);

			char title[100];
			strcpy(title, account->user_book.borrow_book[i].title);
			time_t t = time(NULL);
			printf("*************************************************\n");
			printf("规定还书时间：%s", ctime(&account->user_book.return_time[i]));
			printf("当前时间：%s", ctime(&t));
			t -= account->user_book.return_time[i];
			if (t > 0)
			{
				double cost = t / 3600.0 / 24 * account->user_book.tax;
				printf("由于您未在指定日期内归还《%s》,您需要支付违约金%.2lf元\n", title, cost);
			}
			else printf("书籍《%s》借阅未超出时间，无需支付违约金！\n", title);
			for (; i < account->user_book.borrow_amount; ++i)
			{
				account->user_book.borrow_book[i] = account->user_book.borrow_book[i + 1];
				account->user_book.borrow_time[i] = account->user_book.borrow_time[i + 1];
				account->user_book.return_time[i] = account->user_book.return_time[i + 1];
			}
			--account->user_book.borrow_amount;
			save();
			printf("书籍《%s》归还成功！\n", title);
		}
		system("pause"); system("cls");
	}
}

void history(User * account)  //历史借阅浏览
{
	int n = account->user_book.borrow_amount;
	printf("*************************************************************\n");
	printf("用户%s：\n", account->user_name);
	if (!n)
	{
		printf("暂无书籍在借阅记录！\n"); return;
	}
	printf("借阅书籍序号：\n");
	for (int i = 0; i < n; ++i)
	{
		struct node t = account->user_book;
		time_t nt = time(NULL) - t.return_time[i];
		double cost = 0.0;
		if (nt > 0) cost = t.tax * (nt / 3600.0 / 24);
		printf("%d：\n", i + 1);
		printf("  书名：《%s》\n", t.borrow_book[i].title);
		printf("  借阅日期：%s", ctime(&t.borrow_time[i]));
		printf("  规定还书日期：%s", ctime(&t.return_time[i]));
		if (nt > 0) printf("  是否超时：是\n");
		else printf("  是否超时：否\n");
		printf("  借阅费用：%.2lf\n", cost);
	}
}


/********管理员功能区***********/
void admin_initi()  //超级管理员账号初始化
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
	user_initi(leeds);
	user_head->next = leeds;
	user_amount = 1;
	save();
	fclose(fp);
}

User* serch_username(char* name)  //查找用户名
{
	User* np = user_head->next;
	while (np)
	{
		if (!strcmp(np->user_name, name)) return np;
		np = np->next;
	}
	return NULL;
}

void admin_menu(User * account)  //管理员菜单
{
	while (1)
	{
		system("color 9F");
		printf("*************************************************\n");
		printf("Dear administrator, %s\n Welcome you!\n", account->user_name);
		printf("Please operate according to the number\n");
		printf("1 increase books\n");
		printf("2 delete books\n");
		printf("3 browse books\n");
		printf("4 manage users' information\n");
		printf("0 Quit\n");
		printf("*************************************************\n");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: add_book(); break;
		case 2: delete_book(); break;
		case 3: browse_book(); system("pause"); system("cls"); break;
		case 4: admin_user(); break;
		case 0: printf("Exit the admin account successfully!\n"); system("pause"); system("cls"); return;
		default: printf("Sorry, your input is wrong. Please input again!！\n"); system("pause"); system("cls"); break;
		}
	}
}

void query_user()  //用户信息查询
{
	int cnt = 1;
	User* np = (User*)malloc(sizeof(User));
	np = user_head->next;
	printf("number  username\t\tpassword\t\tname\t\twhether administrator\n");
	while (np)
	{
		printf("%d、 %-20s %-20s %-20s", cnt, np->user_name, np->password, np->ID);
		if (np->admin) printf(" yes\n");
		else printf(" no\n");
		np = np->next;
		++cnt;
	}
}

void admin_user()  //管理用户信息
{
	while (1)
	{

		printf("*************************************************\n");
		printf("Welcome to the user administration interface!\n");
		printf("In this interface you can freely view, change the user information!\n");
		printf("Please operate according to the number\n");
		printf("1 View the user's personal information\n");
		printf("2 Change user's personal information\n");
		printf("3 Check the return and borrow informatio of the user's book\n");
		printf("4 Set admin rights\n");
		printf("5 Delete user account\n");
		printf("0 Back to the previous page\n");
		printf("*************************************************\n");
		User* np = (User*)malloc(sizeof(User));
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: query_user(); system("pause"); system("cls"); break;
		case 2: if (np = serch_user(), np != NULL) user_change(np);
				else
		{
			system("pause"); system("cls");
		}
				break;
		case 3: all_history(); break;
		case 4: if (np = serch_user(), np != NULL) set_admin(np);
				else
		{
			system("pause"); system("cls");
		}
				break;
		case 5:if (np = serch_user(), np != NULL)
		{
			int admin = np->admin;
			if (delete_user(np) && admin)
				printf("This account has been deleted, please login again!\n");
			system("pause"); system("cls");
			return;
		}
			   else
		{
			system("pause"); system("cls");
		}
			   break;
		case 0: printf("Exit user admin interface successfully!\n"); system("pause"); system("cls"); return;
		default: printf("Sorry, your input is wrong. Please input again!\n"); system("pause"); system("cls"); break;
		}
	}
}

void all_history() //查看用户图书借阅归还情况
{
	while (1)
	{
		printf("###########################################################\n");
		printf("Welcome to use the user library borrowing return query system!\n");
		User* account = (User*)malloc(sizeof(User));
		account = serch_user();
		if (account)
		{
			history(account);
			printf("Check successfully! Returning to the upper level!\n");
			system("pause"); system("cls"); return;
		}
		system("pause"); system("cls");
	}
}

User* serch_user()  //按序号搜索用户
{
	query_user();
	printf("Please enter the serial number of the user to be operated:\n");
	int cnt; scanf("%d", &cnt); system("cls");
	if (cnt > user_amount || cnt <= 0)
		printf("Please correctly enter the user serial number to be operated in the figure above!\n");
	else
	{
		User* tb = (User*)malloc(sizeof(User));
		tb = user_head->next;
		for (int i = 1; i < cnt; ++i)
			tb = tb->next;
		return tb;
	}
	return NULL;
}

void set_admin(User * account)  //设置管理员
{
	printf("*******************************************************************\n");
	if (!strcmp(account->user_name, leeds->user_name))
	{
		printf("User %s has the highest management authority, can not be modified!! Returning to the upper level\n", leeds->user_name);
		system("pause"); system("cls"); return;
	}
	printf("Are you sure to set the user %s as administrator?\n", account->user_name);
	printf("Please enter the corresponding number to continue!\n");
	printf("1. Set as administrator\t0. Cancel administrator privileges\n");
	int op; scanf("%d", &op);
	if (op == 1)
	{
		account->admin = op;
		printf("User %s\t administrator privileges set successfully!\n", account->user_name);
	}
	else if (op == 0)
	{
		account->admin = op;
		printf("User%s\tAdministrator privileges have been revoked!\n", account->user_name);
	}
	else
	{
		printf("Failed to set administrator permissions, please enter as required!\n");
	}
	printf("*******************************************************************\n");
	save();
	system("pause"); system("cls");
}

/********图书功能区***********/
void add_book()  //增加图书信息
{
	char title[100], isbn[100], author[100], publisher[100], year[4];
	int cnt;
	printf("Please enter the name of the book to be added:\n");
	scanf("%s", title);
	printf("Please enter the book ISBN to be added:\n");
	scanf("%s", isbn);
	printf("Please enter the author of the book to be added:\n");
	scanf("%s", author);
	printf("Please enter the book publisher to be added:\n");
	scanf("%s", publisher);
	printf("Please enter the year of books to be added:\n");
	scanf("%s", year);
	printf("Please enter the number of books to be added:\n");
	scanf("%d", &cnt);

	++book_amount;
	creat_book_list(title, isbn, author, publisher,year, cnt);
	printf("Added book %s successfully!\n", title);
	system("pause"); system("cls");
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


