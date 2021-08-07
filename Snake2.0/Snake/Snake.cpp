/**
贪吃蛇类成员函数实现
作者：luye@nankai.edu.cn
日期：2018年3月5日
*/

#pragma once
#include"Function.h"

int Snake::Get_x()
{
	return s_x;
}
int Snakemonster::Get_x()
{
	return m_x;
}

int Snake::Get_y()
{
	return s_y;
}
int Snakemonster::Get_y()
{
	return m_y;
}

Snake *Snake::Get_next()
{
	return next;
}
Snakemonster *Snakemonster::Getnext()
{
	return mnext;
}

bool Snake::Bite_self()//检查是否咬到自己,就是检查头节点是否与身体其他任何一个节点碰触
{
	Snake *self;//遍历整个蛇检查是否咬到自己的指针
				//已经有了一个q遍历指针，但q是一个全局指针，容易造成混乱，所以可以定义一个局部的self指针，同学们也可以按照自己的方式处理
	self = head->Get_next();//self从蛇头的下一个节点出发
	while (self->Get_next() != NULL)//当没有遍历到最后一个节点时
	{
		if (self->Get_x() == head->Get_x() && self->Get_y() == head->Get_y())//如果self所指向的x，y的坐标与蛇头的x，y相等，说明咬到自己了
			return 1;//咬到了
		self = self->Get_next();//self后移一个节点
	}
	return 0;//没咬到
}

bool Snake::Bite_monster()//也死
{
	Snakemonster *m;
	m=monsterhead->Getnext();
	while(m->Getnext()!=NULL)
	{
		if(head->Get_x()==m->Get_x()&&head->Get_y()==m->Get_y())
			return 1;
		m=m->Getnext();
	}
	return 0;
}

bool Snakemonster::bite_snake()
{
	Snake *self;
	self = head ->Get_next();
	while (self->Get_next()->Get_next() != NULL)
	{
		if (self->Get_x() == monsterhead->Get_x() && self->Get_y() == monsterhead->Get_y())
			return 1;
		self = self->Get_next();
	}
	return 0;//没咬到
}

void Snake::Can_not_crowall()//不能与墙相撞
{
	for (int i = 0; i < 30; i++)//这个for是遍历所有障碍，检测蛇是否撞到障碍物
	{
		if (head->s_x == o[i].x && head->s_y == o[i].y)
		{
			end_condition = 4;//这里的end_condition是结束情况的标志
			Die();
		}
	}
	if ((head->s_x == 0 && head->s_y != 20) || (head->s_x == 56 && head->s_y != 6) || (head->s_y == 0 && head->s_x != 10) || (head->s_y == 26 && head->s_x != 50))//这里的不等于是因为这四个数是穿梭隧道的具体坐标，蛇是可以碰触的
	{
		end_condition = 1;//这里的end_condition是结束情况的标志，根据结束情况的值，
		Die();           //输出相对应情况的结束画面

	}

}
void Snakemonster::on_the_screen()
{
	if((monsterhead->m_x==0&&monsterhead->m_y!=20)||(monsterhead->m_y==0&&monsterhead->m_x!=10)||monsterhead->m_x==100||monsterhead->m_y==30)
	{
		end_condition=6;
		Die();
	}
}

void Snake::Move()//蛇移动的函数
{
	Snake *nexthead;//定义next_head来完成蛇的移动
	nexthead = new Snake;//next_head用来存放蛇移动到下一个位置的节点
	head->Can_not_crowall();//要先判断一下是否撞墙，因为如果撞墙就不用move了

	if (condition == UP)//上的情况
	{
		nexthead->s_x = head->s_x;//将蛇头移到nexthead，其实就是将蛇头的横纵坐标附给nexthead
		nexthead->s_y = head->s_y - 1;//这里要说明蛇的运动规律，.
		if (nexthead->s_x == food->s_x && nexthead->s_y == food->s_y)//要运动到下一个位置有食物
		{
			nexthead->next = head;//将下一个新的，蛇要运动到的节点与现有的头节点链接
			head = nexthead;//head移至最前，达到head永远指向头的目的
			q = head;//遍历全身的q指针现在从head出发
			Set_location(q->s_x,q->s_y);
			cout << "■";
			score += add;//吃到食物，加分
			creat_food();
		}
		else if(nexthead->s_x == poison->s_x && nexthead->s_y == poison->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "■";
			while (q->next->next->next != NULL)  {q=q->next;}
			Set_location(q->s_x, q->s_y);//定位蛇最后一个节点的位置
			cout <<" ";//由于蛇移动了，最后的显示出来的就应该是没有蛇的身体，所以输出一个空格
			Set_location(q->next->s_x,q->next->s_y);
			cout<<" ";
			delete q->next->next;//蛇的移动新建立了一个节点，蛇又没有吃到果实，所以这是蛇多了一个节点，所以要把最后那个节点释放
			q->next->next = NULL;
			delete q->next;
			q->next=NULL;
			life -= add;//吃到毒药，减分
			if(life<=0)
			{
				end_condition=5;
				Die();
			}
			creat_poison();
		}
		else//下一个位置没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			if (q->s_y < 0)
				{
					q->s_y += 27;
					q->s_x += 40;
				}
			Set_location(q->s_x, q->s_y);
				Green_color();
				cout << "■";
				q=q->next;
			while (q->next->next != NULL)//将蛇打印一遍
			{
				if (q->s_y < 0)//穿墙实现，就是简单的坐标变换，如果蛇头的y坐标小于0，也就是在地图的最上方，那么就进行坐标变换
				{
					q->s_y += 27;//这里的x，y都变换，是因为穿梭口并不是对齐的，所以会在x上也有变化
					q->s_x += 40;//具体为什么加27和40是根据穿梭口设定位置来定，可以数出来，要同学们根据自己的屏幕大小来计算。
				}
				q = q->next;
			}
			Set_location(q->s_x, q->s_y);//定位蛇最后一个节点的位置
			cout <<" ";//由于蛇移动了，最后的显示出来的就应该是没有蛇的身体，所以输出一个空格
			delete q->next;//蛇的移动新建立了一个节点，蛇又没有吃到果实，所以这是蛇多了一个节点，所以要把最后那个节点释放
			q->next = NULL;
		}
	}
	//接下来的是其他方向的情况，但是原理完全相同
	if (condition == DOWN)//下 情况
	{
		nexthead->s_x = head->s_x;
		nexthead->s_y = head->s_y + 1;
		if (nexthead->s_x == food->s_x && nexthead->s_y == food->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "■";
			score += add;
			creat_food();
		}
		else if(nexthead->s_x == poison->s_x && nexthead->s_y == poison->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "■";
			while (q->next->next->next != NULL)  {q=q->next;}
			Set_location(q->s_x, q->s_y);//定位蛇最后一个节点的位置
			cout <<" ";//由于蛇移动了，最后的显示出来的就应该是没有蛇的身体，所以输出一个空格
			Set_location(q->next->s_x,q->next->s_y);
			cout<<" ";
			delete q->next->next;//蛇的移动新建立了一个节点，蛇又没有吃到果实，所以这是蛇多了一个节点，所以要把最后那个节点释放
			q->next->next = NULL;
			delete q->next;
			q->next=NULL;
			life -= add;//吃到毒药，减分
			if(life<=0)
			{
				end_condition=5;
				Die();
			}
			creat_poison();
		}
		else//下一个位置没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			if (q->s_y > 26)
				{
					q->s_y -= 27;
					q->s_x -= 40;
				}
			Set_location(q->s_x, q->s_y);
				Green_color();
				cout << "■";
				q=q->next;
			while (q->next->next != NULL)
			{
				if (q->s_y > 26)
				{
					q->s_y -= 27;
					q->s_x -= 40;
				}
				q = q->next;
			}
			Set_location(q->s_x, q->s_y);
			cout << " ";
			delete q->next;
			q->next = NULL;
		}
	}
	if (condition == LEFT)//左情况
	{
		nexthead->s_x = head->s_x - 2;
		nexthead->s_y = head->s_y;
		if (nexthead->s_x == food->s_x && nexthead->s_y == food->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "■";
			score += add;
			creat_food();
		}
		else if(nexthead->s_x == poison->s_x && nexthead->s_y == poison->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "■";
			while (q->next->next->next != NULL)  {q=q->next;}
			Set_location(q->s_x, q->s_y);//定位蛇最后一个节点的位置
			cout <<" ";//由于蛇移动了，最后的显示出来的就应该是没有蛇的身体，所以输出一个空格
			Set_location(q->next->s_x,q->next->s_y);
			cout<<" ";
			delete q->next->next;//蛇的移动新建立了一个节点，蛇又没有吃到果实，所以这是蛇多了一个节点，所以要把最后那个节点释放
			q->next->next = NULL;
			delete q->next;
			q->next=NULL;
			life -= add;//吃到毒药，减分
			if(life<=0)
			{
				end_condition=5;
				Die();
			}
			creat_poison();
		}
		else
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			if (q->s_x < 0)
			{
				q->s_x += 58;
				q->s_y -= 14;
			}
			Set_location(q->s_x, q->s_y);
				Green_color();
				cout << "■";
				q=q->next;
			while (q->next->next != NULL)
			{
				if (q->s_x < 0)
				{
					q->s_x += 58;
					q->s_y -= 14;
				}
				q = q->next;
			}
			Set_location(q->s_x, q->s_y);
			cout << " ";
			delete q->next;
			q->next = NULL;
		}
	}
	if (condition == RIGHT)//右情况
	{
		nexthead->s_x = head->s_x + 2;
		nexthead->s_y = head->s_y;
		if (nexthead->s_x == food->s_x && nexthead->s_y == food->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "■";
			score += add;
			creat_food();
		}
		else if(nexthead->s_x == poison->s_x && nexthead->s_y == poison->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "■";
			while (q->next->next->next != NULL)  {q=q->next;}
			Set_location(q->s_x, q->s_y);//定位蛇最后一个节点的位置
			cout <<" ";//由于蛇移动了，最后的显示出来的就应该是没有蛇的身体，所以输出一个空格
			Set_location(q->next->s_x,q->next->s_y);
			cout<<" ";
			delete q->next->next;//蛇的移动新建立了一个节点，蛇又没有吃到果实，所以这是蛇多了一个节点，所以要把最后那个节点释放
			q->next->next = NULL;
			delete q->next;
			q->next=NULL;
			life -= add;//吃到毒药，减分
			if(life<=0)
			{
				end_condition=5;
				Die();
			}
			creat_poison();
		}
		else
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			if (q->s_x > 56)
				{
					q->s_x -= 58;
					q->s_y += 14;
				}
			Set_location(q->s_x, q->s_y);
				Green_color();
				cout << "■";
			while (q->next->next != NULL)
			{
				if (q->s_x > 56)
				{
					q->s_x -= 58;
					q->s_y += 14;
				}
				q = q->next;
			}
			Set_location(q->s_x, q->s_y);
			cout << " ";
			delete q->next;
			q->next = NULL;
		}
	}
	if (Bite_self()||Bite_monster())//在每次移动都要检查在移动中是否咬到自己,只有在move后才有可能咬到自己所以放在后面判断
	{
		end_condition = 2;//如果要到自己就要给end_condition赋上相应死亡情况的值
		Die();//咬到自己调用die函数
	}
}
void Snakemonster::monster_move()
{
	Snakemonster *nexthead;
	nexthead = new Snakemonster;
	monsterhead->on_the_screen();
	if (monstercondition == UP)
	{
		nexthead->m_x = monsterhead->m_x;
		nexthead->m_y = monsterhead->m_y - 1;
		if (bite_snake())
		{
			nexthead->mnext = monsterhead;
			monsterhead = nexthead;
			mq = monsterhead;
			Set_location(mq->m_x,mq->m_y);
			cout << "■";
			monsterscore += 2;
		}
		else
		{
			nexthead->mnext = monsterhead;
			monsterhead = nexthead;
			mq = monsterhead;
			if (mq->m_y < 0)
				{
					mq->m_y += 27;
					mq->m_x += 40;
				}
			Set_location(mq->m_x, mq->m_y);
				Green_color();
				cout << "■";
				mq=mq->mnext;
			while (mq->mnext->mnext != NULL)
			{
				if (mq->m_y < 0)
				{
					mq->m_y += 27;
					mq->m_x += 40;
				}
				mq = mq->mnext;
			}
			Set_location(mq->m_x, mq->m_y);
			cout <<" ";
			delete mq->mnext;
			mq->mnext = NULL;
		}
	}
	if (monstercondition == DOWN)
	{
		nexthead->m_x = monsterhead->m_x;
		nexthead->m_y = monsterhead->m_y + 1;
		if (bite_snake())
		{
			nexthead->mnext = monsterhead;
			monsterhead = nexthead;
			mq = monsterhead;
			Set_location(mq->m_x,mq->m_y);
			cout << "■";
			monsterscore += 2;
		}
		else
		{
			nexthead->mnext = monsterhead;
			monsterhead = nexthead;
			mq = monsterhead;
			Set_location(mq->m_x, mq->m_y);
				Green_color();
				cout << "■";
			while (mq->mnext->mnext != NULL)
			{mq=mq->mnext;}
			Set_location(mq->m_x, mq->m_y);
			cout << " ";
			delete mq->mnext;
			mq->mnext = NULL;
		}
	}
	if (monstercondition == LEFT)
	{
		nexthead->m_x = monsterhead->m_x - 2;
		nexthead->m_y = monsterhead->m_y;
		if (bite_snake())
		{
			nexthead->mnext = monsterhead;
			monsterhead = nexthead;
			mq = monsterhead;
			Set_location(mq->m_x,mq->m_y);
			cout << "■";
			monsterscore += 2;
		}
		else
		{
			nexthead->mnext = monsterhead;
			monsterhead = nexthead;
			mq = monsterhead;
			if (mq->m_x < 0)
			{
				mq->m_x += 58;
				mq->m_y -= 14;
			}
			Set_location(mq->m_x, mq->m_y);
				Green_color();
				cout << "■";
				mq=mq->mnext;
			while (mq->mnext->mnext != NULL)
			{
				if (mq->m_x < 0)
				{
					mq->m_x += 58;
					mq->m_y -= 14;
				}
				mq = mq->mnext;
			}
			Set_location(mq->m_x, mq->m_y);
			cout << " ";
			delete mq->mnext;
			mq->mnext = NULL;
		}
	}
	if (monstercondition == RIGHT)
	{
		nexthead->m_x = monsterhead->m_x + 2;
		nexthead->m_y = monsterhead->m_y;
		if (bite_snake())
		{
			nexthead->mnext = monsterhead;
			monsterhead = nexthead;
			mq = monsterhead;
			Set_location(mq->m_x,mq->m_y);
			cout << "■";
			monsterscore += 2;
		}
		else
		{
			nexthead->mnext = monsterhead;
			monsterhead = nexthead;
			mq = monsterhead;
			Set_location(mq->m_x, mq->m_y);
				Green_color();
				cout << "■";
			while (mq->mnext->mnext != NULL)
			{mq=mq->mnext;}
			Set_location(mq->m_x, mq->m_y);
			cout << " ";
			delete mq->mnext;
			mq->mnext = NULL;
		}
	}
}