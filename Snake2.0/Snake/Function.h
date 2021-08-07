/**
贪吃蛇功能函数列表
作者：luye@nankai.edu.cn
日期：2018年3月5日
*/
#pragma once
#include"Snake.h"
#include<iostream>
#include<stdlib.h>//随即函数就包含在这个头文件
#include<time.h>//时间函数time包含在这个头文件
#include<Windows.h>//HANDLE类（句柄类）与COORD类（坐标类）包含在这个头文件
using namespace std;

/**
方向控制
*/
#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 3


extern Snake *head,*food,*poison;//全局指针，head是永远指向第一个节点的指针，food是指向食物的指针
extern Snake *q;//遍历整个蛇所用到的指针
extern Snakemonster *monsterhead;
extern Snakemonster *mq;
extern int condition;//代表按键情况，上述把按键四种情况分别赋了整数值，所以这里的情况也是int 类型
extern int monstercondition;
extern int end_condition;//表示结束的情况，=1，撞墙；=2，咬到自己；=3，自己结束;4 撞到障碍物而死;5 被毒死;6 打败怪物;7 被打败
extern int score;
extern int add;//得分和每个食物的分数
extern int monsterscore;
extern int life;
extern Obstacle o[30];

inline void Green_color();//字体置绿
inline void Red_color();//字体置红
inline void Yellow_color();//字体置黄
inline void White_color();
inline void Blue_color();

void Set_location(int x, int y);//定位函数
void Creat_obs(Obstacle o[], int n);//创建障碍物
void Initial();//初始化函数
void Initialmonster();
void creat_food();//创建食物
void creat_poison();
void creatMap();//创建地图
void pause();//暂停
void Start();//开始
void Playing();//进行游戏
void Die();//死亡
void newstart();
void newplaying();