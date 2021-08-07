/**
贪吃蛇功能函数实现
作者：luye@nankai.edu.cn
时间：2018年3月5日
*/
#pragma once
#include"Function.h"

Snake *head, *food, *poison;//全局指针，head是永远指向第一个节点的指针，food是指向食物的指针
Snake *q;//遍历整个蛇所用到的指针
Snakemonster *mq;
int condition;//代表按键情况，上述把按键四种情况分别赋了整数值，所以这里的情况也是int 类型
int monstercondition;
int end_condition = 0;//表示结束的情况，=1，撞墙；=2，咬到自己；=3，自己结束;4 撞到障碍物而死
int score = 0, add = 1,life=2, monsterscore=0;//得分和每个食物的分数
Obstacle o[30];//定义一个存放障碍物的结构体数组用来存放每一块障碍物的x，y坐标
Snakemonster *monsterhead;

inline void Green_color()//这里用到一个SetConsoleTextAttribute，是API设置控制台窗口颜色属性的函数，这里和句柄搭配
{                               // 设置颜色为绿色
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		FOREGROUND_GREEN |//设置绿色
		FOREGROUND_INTENSITY);//让字体变得更加明亮
}
inline void Blue_color()//这里用到一个SetConsoleTextAttribute，是API设置控制台窗口颜色属性的函数，这里和句柄搭配
{                               // 设置颜色为蓝色
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		FOREGROUND_BLUE |//设置蓝色
		FOREGROUND_INTENSITY);//让字体变得更加明亮
}

inline void Red_color()//设置颜色为红色
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		FOREGROUND_RED |
		FOREGROUND_INTENSITY);//intensity就是让这个字体的颜色更亮
}

inline void Yellow_color()//设置颜色为黄色
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		FOREGROUND_RED |
		FOREGROUND_GREEN |
		FOREGROUND_INTENSITY);
}

inline void White_color(){
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		FOREGROUND_RED |
		FOREGROUND_GREEN |
		FOREGROUND_BLUE |
		FOREGROUND_INTENSITY);
}

void Set_location(int x, int y)//定位函数，作用是定位给出坐标的位置方便打印出想要的东西
{
	COORD cd;
	HANDLE hOut;
	cd.X = x;
	cd.Y = y;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, cd);//定位坐标
}
void Creat_obs(Obstacle o[], int n)//制造障碍物,一共五大块障碍物，所以内部有五块循环
{
	int a = 14, b = 24, c = 8, d = 40, e = 32, f = 10;//这些数都是我自己随即挑选的，是可以更换的，只要不超出地图范围
	for (int i = 0; i < 6; i++)
	{
		o[i].x = a;
		a += 2;//这里的+2是因为由于打印"■"横坐标占两个纵坐标占一个
		o[i].y = c;
	}
	a = 15; b = 24; c = 8; d = 40; e = 32; f = 10;
	for (int i = 6; i < 15; i++)
	{
		o[i].x = b;
		o[i].y = c++;
	}
	a = 15; b = 23; c = 8; d = 40; e = 10; f = 17;
	for (int i = 15; i < 20; i++)
	{
		o[i].x = e;
		e += 2;
		o[i].y = f;
		f++;
	}
	a = 15; b = 23; c = 8; d = 40; e = 32; f = 13;
	for (int i = 20; i < 26; i++)
	{
		o[i].x = d;
		o[i].y = f;
		f++;
	}
	a = 15; b = 23; c = 8; d = 40; e = 44; f = 4;
	for (int i = 26; i < 30; i++)
	{
		o[i].x = e;
		e -= 2;
		o[i].y = f;
	}
	a = 15; b = 23; c = 8; d = 40; e = 32; f = 10;
	for (int i = 0; i < 30; i++)//把上述设置的障碍物打印到地图上
	{
		Set_location(o[i].x, o[i].y);
		cout << "■";
	}
}


void Initial()//初始化蛇，蛇一开始有四节
{
	Snake *tail;
	int i;
	tail = new Snake;
	head = tail;
	head->s_x = 24;//给蛇头赋上x，y的坐标值
	head->s_y = 5;//这里的坐标值是我自己定的，可以更改，从而达到更改蛇起始位置的目的，但是不能超越地图范围的大小
	head->next = NULL;
	for (i = 1; i <= 4; i++)//申请四个空间放入四个蛇的身体
	{
		head = new Snake;
		head->next = tail;
		head->s_x = 24 + 2 * i;
		head->s_y = 5;
		tail = head;
	}
	while (tail->next != NULL)//从头到尾，输出蛇身
	{
		Set_location(tail->s_x, tail->s_y);
		Green_color();
		cout << "■";
		tail = tail->next;
	}
}
void Initialmonster()
{
	Snakemonster *tail;
	int i;
	tail = new Snakemonster;
	monsterhead = tail;
	monsterhead->m_x = 64;//给蛇头赋上x，y的坐标值
	monsterhead->m_y = 6;//这里的坐标值是我自己定的，可以更改，从而达到更改蛇起始位置的目的，但是不能超越地图范围的大小
	monsterhead->mnext = NULL;
	for (i = 1; i <= 4; i++)//申请四个空间放入四个蛇的身体
	{
		monsterhead = new Snakemonster;
		monsterhead->mnext = tail;
		monsterhead->m_x = 64 + 2 * i;
		monsterhead->m_y = 6;
		tail = monsterhead;
	}
	while (tail->mnext != NULL)//从头到尾，输出蛇身
	{
		Set_location(tail->m_x, tail->m_y);
		Green_color();
		cout << "■";
		tail = tail->mnext;
	}
}
void creat_food()//随机生成食物的函数
{
	Snake *food_1;//创造出来的食物是先由food_1指向的，等创建好食物之后，再赋值给全局food指针
	srand((unsigned)time(NULL));//给srand一个种子，它与rand函数是有区别的，同学们可以查一查这两个函数的区别，以及为什么叫伪随机
	L1:food_1 = new Snake;
	while ((food_1->s_x % 2) != 0)    //保证其为偶数，使得食物能与蛇头对其,这里为偶数是因为“■”横行占2个位置，竖行占1个位置
	{
		food_1->s_x = (3 + rand() % 50) + 2;//%52表示在0到51的横坐标范围内随机
	}
	food_1->s_y = (3 + rand() % 22) + 1;//同理
	q = head;//q是定义的一个全局指针，用来遍历整个蛇身
	while (q->next != NULL)
	{
		if (q->s_x == food_1->s_x && q->s_y == food_1->s_y) //判断蛇身是否与食物重合
		{
			delete food_1;//如果创造出来的食物和存在的蛇的身体重合就要删除这个食物重新创造一个食物
			/*creat_food();*/
			goto L1;
		}
		q = q->next;
	}
	for (int i = 0; i < 30; i++)
	{
		if (o[i].x == food_1->s_x && o[i].y == food_1->s_y)
		{
			delete food_1;//如果食物和地图中的障碍物重合，就要删除食物重新创造食物
			/*creat_food();*/
			goto L1;
		}
	}
	Set_location(food_1->s_x, food_1->s_y);//创造食物成功就要把食物打印出来
	food = food_1;
	Red_color();//让食物变成红色
	cout << "★";//输出食物
}
void creat_poison()
{
	Snake *poison_1;//创造出来的食物是先由poison_1指向的，等创建好食物之后，再赋值给全局food指针
	srand((unsigned)time(NULL));//给srand一个种子，它与rand函数是有区别的，同学们可以查一查这两个函数的区别，以及为什么叫伪随机
	L2:poison_1 = new Snake;
	while ((poison_1->s_x % 2) != 0)    //保证其为偶数，使得食物能与蛇头对其,这里为偶数是因为“■”横行占2个位置，竖行占1个位置
	{
		poison_1->s_x = (3+rand() % 50) + 2;//%52表示在0到51的横坐标范围内随机
	}
	poison_1->s_y = (3+rand() % 22) + 1;//同理
	q = head;//q是定义的一个全局指针，用来遍历整个蛇身
	while (q->next != NULL)
	{
		if (q->s_x == poison_1->s_x && q->s_y == poison_1->s_y) //判断蛇身是否与食物重合
		{
			delete poison_1;//如果创造出来的食物和存在的蛇的身体重合就要删除这个食物重新创造一个食物
			/*creat_poison();*/
			goto L2;
		}
		q = q->next;
	}
	for (int i = 0; i < 30; i++)
	{
		if (o[i].x == poison_1->s_x && o[i].y == poison_1->s_y)
		{
			delete poison_1;//如果食物和地图中的障碍物重合，就要删除食物重新创造食物
			/*creat_poison();*/
			goto L2;
		}
	}
	if(poison_1->s_x == food->s_x && poison_1->s_y == food->s_y)
	{
		delete poison_1;
		/*creat_poison();*/
		goto L2;
	}
	Set_location(poison_1->s_x, poison_1->s_y);//创造食物成功就要把食物打印出来
	poison = poison_1;
	Blue_color();//让食物变成蓝色
	cout << "★";//输出食物
}
void creatMap()//创建地图
{
	White_color();
	int i;
	for (i = 0; i<58; i += 2)//打印上下边框,这里是上下同时打印
	{
		Set_location(i, 0);
		cout << "■";
		Set_location(i, 26);
		cout << "■";
	}
	Set_location(10, 0);//打印出穿越口
	cout << " ";
	Set_location(50, 26);
	cout << " ";
	for (i = 1; i<26; i++)//打印左右边框，左右同时打印
	{
		Set_location(0, i);
		cout << "■";
		Set_location(56, i);
		cout << "■";
	}
	Set_location(0, 20);
	cout << " ";
	Set_location(56, 6);
	cout << " ";
	Creat_obs(o, 30);
}

void pause()//暂停函数，当按下空格，表示要暂停游戏
{
	while (1)
	{
		Sleep(300);//延时函数，1000表示延时1s，这里是延时0.3s
		if (GetAsyncKeyState(VK_SPACE))//VK表示键盘按键行为，“_”表示是哪一个按键，这里判断是空格按键
			break;                   //这里判断如果按键是SPACE 就要终止游戏  async异步的，同步异步的概念同学们会在大二时学到。
	}
}
void Start()//开始游戏
{
	system("mode con cols=100 lines=30");//设置运行框的大小，这个是自己定义的
	//White_color();
	int i;
	for (i = 33; i<60; i += 2)//打印上下边框,这里是上下同时打印，左右同时打印
	{
		Set_location(i, 10);
		cout << "■";
		Set_location(i, 14);
		cout << "■";
	}
	for (i = 10; i<15; i++)//打印左右边框
	{
		Set_location(33, i);
		cout << "■";
		Set_location(61, i);
		cout << "■";
	}
	Set_location(40, 12);
	cout << "贪吃蛇@_@小游戏" << endl;
	system("pause");//是画面停留在当前
	system("cls");//清屏
	Set_location(30, 12);
	cout << "用↑.↓.←.→分别控制蛇的移动" << endl;
	Set_location(30, 13);
	cout << "游戏设置时空隧道，贪吃蛇可以穿越图中障碍物不能碰撞！"<<endl;
	Set_location(30,14);
	cout<<"开始时右侧蛇怪属于休眠状态"<<endl;
	system("pause");
	system("cls");
	creatMap();
 	Initial();
	Initialmonster();
	creat_food();
	creat_poison();
}
void Playing()//进行游戏中
{
	Set_location(64, 15);
	Yellow_color();
	cout << "不能穿墙，不能咬到自己" << endl;
	Set_location(64, 16);
	Yellow_color();
	cout << "用↑.↓.←.→分别控制蛇的移动" << endl;
	Set_location(64, 17);
	Yellow_color();
	cout << "贪吃蛇可以穿越隧道，障碍物不能碰撞！"<<endl;
	Set_location(64, 18);
	Yellow_color();
	cout << "ESC ：退出游戏.space：暂停游戏" << endl;
	while (1)//
	{
		if(score<5)
		{
		Set_location(64, 10);
		Yellow_color();
		cout << "Score=" << score<<"   "<<"Life="<<life;
		Set_location(64, 11);
		Yellow_color();
		cout << "每个食物" << add << "分";
		
		if (GetAsyncKeyState(VK_UP) || GetKeyState(87) && condition != DOWN)//判断按键状态函数
			condition = UP;
		else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(83) && condition != UP)
			condition = DOWN;
		else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(65) && condition != RIGHT)
			condition = LEFT;
		else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(68)&& condition != LEFT)
			condition = RIGHT;
		else if (GetAsyncKeyState(VK_SPACE))
			pause();
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			end_condition = 3;
			break;
		}
		Sleep(200-8*score);
		head->Move();
		}
		else {break;}
	}
}
void newstart()
{
	Set_location(0,28);
	system("pause");
	Set_location(60,3);
	cout<<"蛇怪激活，蛇怪不惧墙和障碍，吃蛇便得2分";
	Set_location(60,4);
	cout<<"先得10分者胜利";
}
void newplaying()
{
	while (1)//
	{
		Set_location(60,3);
		cout<<"蛇怪激活，蛇怪不惧墙和障碍，吃蛇便得2分";
		Set_location(60,4);
		cout<<"先得10分者胜利";
		creatMap();
		Yellow_color();
		Set_location(64, 15);
		cout << "不能穿墙，不能咬到自己" << endl;
		Set_location(64, 16);
		Yellow_color();
		cout << "用↑.↓.←.→分别控制蛇的移动" << endl;
		Set_location(64, 17);
		Yellow_color();
		cout << "用WSAD分别控制蛇怪的移动"<<endl;
		Set_location(64, 18);
		Yellow_color();
		cout << "ESC ：退出游戏.space：暂停游戏" << endl;
		Set_location(64, 10);
		Yellow_color();
		cout << "Score=" << score<<"  "<<"Life="<<life<<"  "<<"Monsterscore="<<monsterscore;
		Set_location(64, 11);
		Yellow_color();
		cout << "吃个食物蛇得" << add << "分"<<"  "<<"被咬一次蛇怪得2分";
		if(score==10)
		{
			end_condition=6;
			break;
		}
		if(monsterscore==10)
		{
			end_condition=7;
			break;
		}
		if (GetAsyncKeyState(VK_UP) && condition != DOWN)//判断按键状态函数
			condition = UP;
		else if (GetAsyncKeyState(VK_DOWN) && condition != UP)
			condition = DOWN;
		else if (GetAsyncKeyState(VK_LEFT) && condition != RIGHT)
			condition = LEFT;
		else if (GetAsyncKeyState(VK_RIGHT) && condition != LEFT)
			condition = RIGHT;
		else if (GetAsyncKeyState(VK_SPACE))
			pause();
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			end_condition = 3;
			break;
		}
		if (GetAsyncKeyState(87) && condition != DOWN)//判断按键状态函数
			monstercondition = UP;
		else if (GetAsyncKeyState(83) && condition != UP)
			monstercondition = DOWN;
		else if (GetAsyncKeyState(65) && condition != RIGHT)
			monstercondition = LEFT;
		else if (GetAsyncKeyState(68) && condition != LEFT)
			monstercondition = RIGHT;
		Sleep(100-8*score);
		monsterhead->monster_move();
		head->Move();
	}
}

void Die()//游戏结束
{
	system("cls");
	Set_location(30, 12);
	if (end_condition == 1)//不同情况会导致游戏结束时现实的文字不同
	{
		Yellow_color();
		cout << "撞墙而死！！！！！";
	}
	else if (end_condition == 2)
	{
		Yellow_color();
		cout << "竟然咬到了蛇！！！！";
	}

	else if (end_condition == 3)
	{
		Yellow_color();
		cout << "你自己结束了游戏。。。";
	}
	else if (end_condition == 4)
	{
		Yellow_color();
		cout << "你撞倒了障碍物！！！！";
	}
	else if(end_condition==5)
	{
		Yellow_color();
		cout<<"你把自己毒死了。。。";
	}
	else if(end_condition==6)
	{
		Yellow_color();
		cout<<"你打败了蛇怪！";
	}
	else if(end_condition==7)
	{
		Yellow_color();
		cout<<"你被蛇怪打败了";
	}
	Set_location(30, 13);
	Yellow_color();
	cout << "得分：" << score << endl;
	system("pause");
    exit(0);
    //Start();
}