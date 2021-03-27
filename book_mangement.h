//
// Created by coral on 2021/3/27.
//

#ifndef CW1_BOOK_MANGEMENT_H
#define CW1_BOOK_MANGEMENT_H

Book* book_head;  //图书头指针
int book_amount;  //图书总数量

void add_book();  //增加图书信息
void delete_book();  //删除图书信息
void browse_book();  //图书浏览

void findbook();
int find_book_by_title(char* title);
int find_book_by_author(char* author);
int find_book_by_year(char* year);

Book* serch_booknumber(char* isbn);

Book* find_book_bu_isbn(char* isbn);

void creat_book_list(char*, char*, char*, char*, char*, int);  //创建图书链表
void user_initi(User*);  //用户图书管理初始化
#endif //CW1_BOOK_MANGEMENT_H
