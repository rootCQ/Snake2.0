/**
̰���߹��ܺ����б�
���ߣ�luye@nankai.edu.cn
���ڣ�2018��3��5��
*/
#pragma once
#include"Snake.h"
#include<iostream>
#include<stdlib.h>//�漴�����Ͱ��������ͷ�ļ�
#include<time.h>//ʱ�亯��time���������ͷ�ļ�
#include<Windows.h>//HANDLE�ࣨ����ࣩ��COORD�ࣨ�����ࣩ���������ͷ�ļ�
using namespace std;

/**
�������
*/
#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 3


extern Snake *head,*food,*poison;//ȫ��ָ�룬head����Զָ���һ���ڵ��ָ�룬food��ָ��ʳ���ָ��
extern Snake *q;//�������������õ���ָ��
extern Snakemonster *monsterhead;
extern Snakemonster *mq;
extern int condition;//����������������Ѱ�����������ֱ�������ֵ��������������Ҳ��int ����
extern int monstercondition;
extern int end_condition;//��ʾ�����������=1��ײǽ��=2��ҧ���Լ���=3���Լ�����;4 ײ���ϰ������;5 ������;6 ��ܹ���;7 �����
extern int score;
extern int add;//�÷ֺ�ÿ��ʳ��ķ���
extern int monsterscore;
extern int life;
extern Obstacle o[30];

inline void Green_color();//��������
inline void Red_color();//�����ú�
inline void Yellow_color();//�����û�
inline void White_color();
inline void Blue_color();

void Set_location(int x, int y);//��λ����
void Creat_obs(Obstacle o[], int n);//�����ϰ���
void Initial();//��ʼ������
void Initialmonster();
void creat_food();//����ʳ��
void creat_poison();
void creatMap();//������ͼ
void pause();//��ͣ
void Start();//��ʼ
void Playing();//������Ϸ
void Die();//����
void newstart();
void newplaying();