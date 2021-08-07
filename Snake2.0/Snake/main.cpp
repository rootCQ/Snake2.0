/**
测试：跑一个主线程死循环，接收外设事件响应，大二时如果学习面向对象编程会了解到Window编程的事件驱动模式。
作者：luye@nankai.edu.cn
日期：2018年3月5日
*/
#include "Function.h"

int main()//主函数
{
	Start();//游戏开始
	Playing();//游戏进行时
	newstart();
	newplaying();
	return 0;
}