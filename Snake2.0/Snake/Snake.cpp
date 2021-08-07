/**
̰�������Ա����ʵ��
���ߣ�luye@nankai.edu.cn
���ڣ�2018��3��5��
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

bool Snake::Bite_self()//����Ƿ�ҧ���Լ�,���Ǽ��ͷ�ڵ��Ƿ������������κ�һ���ڵ�����
{
	Snake *self;//���������߼���Ƿ�ҧ���Լ���ָ��
				//�Ѿ�����һ��q����ָ�룬��q��һ��ȫ��ָ�룬������ɻ��ң����Կ��Զ���һ���ֲ���selfָ�룬ͬѧ��Ҳ���԰����Լ��ķ�ʽ����
	self = head->Get_next();//self����ͷ����һ���ڵ����
	while (self->Get_next() != NULL)//��û�б��������һ���ڵ�ʱ
	{
		if (self->Get_x() == head->Get_x() && self->Get_y() == head->Get_y())//���self��ָ���x��y����������ͷ��x��y��ȣ�˵��ҧ���Լ���
			return 1;//ҧ����
		self = self->Get_next();//self����һ���ڵ�
	}
	return 0;//ûҧ��
}

bool Snake::Bite_monster()//Ҳ��
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
	return 0;//ûҧ��
}

void Snake::Can_not_crowall()//������ǽ��ײ
{
	for (int i = 0; i < 30; i++)//���for�Ǳ��������ϰ���������Ƿ�ײ���ϰ���
	{
		if (head->s_x == o[i].x && head->s_y == o[i].y)
		{
			end_condition = 4;//�����end_condition�ǽ�������ı�־
			Die();
		}
	}
	if ((head->s_x == 0 && head->s_y != 20) || (head->s_x == 56 && head->s_y != 6) || (head->s_y == 0 && head->s_x != 10) || (head->s_y == 26 && head->s_x != 50))//����Ĳ���������Ϊ���ĸ����Ǵ�������ľ������꣬���ǿ���������
	{
		end_condition = 1;//�����end_condition�ǽ�������ı�־�����ݽ��������ֵ��
		Die();           //������Ӧ����Ľ�������

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

void Snake::Move()//���ƶ��ĺ���
{
	Snake *nexthead;//����next_head������ߵ��ƶ�
	nexthead = new Snake;//next_head����������ƶ�����һ��λ�õĽڵ�
	head->Can_not_crowall();//Ҫ���ж�һ���Ƿ�ײǽ����Ϊ���ײǽ�Ͳ���move��

	if (condition == UP)//�ϵ����
	{
		nexthead->s_x = head->s_x;//����ͷ�Ƶ�nexthead����ʵ���ǽ���ͷ�ĺ������긽��nexthead
		nexthead->s_y = head->s_y - 1;//����Ҫ˵���ߵ��˶����ɣ�.
		if (nexthead->s_x == food->s_x && nexthead->s_y == food->s_y)//Ҫ�˶�����һ��λ����ʳ��
		{
			nexthead->next = head;//����һ���µģ���Ҫ�˶����Ľڵ������е�ͷ�ڵ�����
			head = nexthead;//head������ǰ���ﵽhead��Զָ��ͷ��Ŀ��
			q = head;//����ȫ���qָ�����ڴ�head����
			Set_location(q->s_x,q->s_y);
			cout << "��";
			score += add;//�Ե�ʳ��ӷ�
			creat_food();
		}
		else if(nexthead->s_x == poison->s_x && nexthead->s_y == poison->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "��";
			while (q->next->next->next != NULL)  {q=q->next;}
			Set_location(q->s_x, q->s_y);//��λ�����һ���ڵ��λ��
			cout <<" ";//�������ƶ��ˣ�������ʾ�����ľ�Ӧ����û���ߵ����壬�������һ���ո�
			Set_location(q->next->s_x,q->next->s_y);
			cout<<" ";
			delete q->next->next;//�ߵ��ƶ��½�����һ���ڵ㣬����û�гԵ���ʵ�����������߶���һ���ڵ㣬����Ҫ������Ǹ��ڵ��ͷ�
			q->next->next = NULL;
			delete q->next;
			q->next=NULL;
			life -= add;//�Ե���ҩ������
			if(life<=0)
			{
				end_condition=5;
				Die();
			}
			creat_poison();
		}
		else//��һ��λ��û��ʳ��
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
				cout << "��";
				q=q->next;
			while (q->next->next != NULL)//���ߴ�ӡһ��
			{
				if (q->s_y < 0)//��ǽʵ�֣����Ǽ򵥵�����任�������ͷ��y����С��0��Ҳ�����ڵ�ͼ�����Ϸ�����ô�ͽ�������任
				{
					q->s_y += 27;//�����x��y���任������Ϊ����ڲ����Ƕ���ģ����Ի���x��Ҳ�б仯
					q->s_x += 40;//����Ϊʲô��27��40�Ǹ��ݴ�����趨λ��������������������Ҫͬѧ�Ǹ����Լ�����Ļ��С�����㡣
				}
				q = q->next;
			}
			Set_location(q->s_x, q->s_y);//��λ�����һ���ڵ��λ��
			cout <<" ";//�������ƶ��ˣ�������ʾ�����ľ�Ӧ����û���ߵ����壬�������һ���ո�
			delete q->next;//�ߵ��ƶ��½�����һ���ڵ㣬����û�гԵ���ʵ�����������߶���һ���ڵ㣬����Ҫ������Ǹ��ڵ��ͷ�
			q->next = NULL;
		}
	}
	//����������������������������ԭ����ȫ��ͬ
	if (condition == DOWN)//�� ���
	{
		nexthead->s_x = head->s_x;
		nexthead->s_y = head->s_y + 1;
		if (nexthead->s_x == food->s_x && nexthead->s_y == food->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "��";
			score += add;
			creat_food();
		}
		else if(nexthead->s_x == poison->s_x && nexthead->s_y == poison->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "��";
			while (q->next->next->next != NULL)  {q=q->next;}
			Set_location(q->s_x, q->s_y);//��λ�����һ���ڵ��λ��
			cout <<" ";//�������ƶ��ˣ�������ʾ�����ľ�Ӧ����û���ߵ����壬�������һ���ո�
			Set_location(q->next->s_x,q->next->s_y);
			cout<<" ";
			delete q->next->next;//�ߵ��ƶ��½�����һ���ڵ㣬����û�гԵ���ʵ�����������߶���һ���ڵ㣬����Ҫ������Ǹ��ڵ��ͷ�
			q->next->next = NULL;
			delete q->next;
			q->next=NULL;
			life -= add;//�Ե���ҩ������
			if(life<=0)
			{
				end_condition=5;
				Die();
			}
			creat_poison();
		}
		else//��һ��λ��û��ʳ��
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
				cout << "��";
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
	if (condition == LEFT)//�����
	{
		nexthead->s_x = head->s_x - 2;
		nexthead->s_y = head->s_y;
		if (nexthead->s_x == food->s_x && nexthead->s_y == food->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "��";
			score += add;
			creat_food();
		}
		else if(nexthead->s_x == poison->s_x && nexthead->s_y == poison->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "��";
			while (q->next->next->next != NULL)  {q=q->next;}
			Set_location(q->s_x, q->s_y);//��λ�����һ���ڵ��λ��
			cout <<" ";//�������ƶ��ˣ�������ʾ�����ľ�Ӧ����û���ߵ����壬�������һ���ո�
			Set_location(q->next->s_x,q->next->s_y);
			cout<<" ";
			delete q->next->next;//�ߵ��ƶ��½�����һ���ڵ㣬����û�гԵ���ʵ�����������߶���һ���ڵ㣬����Ҫ������Ǹ��ڵ��ͷ�
			q->next->next = NULL;
			delete q->next;
			q->next=NULL;
			life -= add;//�Ե���ҩ������
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
				cout << "��";
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
	if (condition == RIGHT)//�����
	{
		nexthead->s_x = head->s_x + 2;
		nexthead->s_y = head->s_y;
		if (nexthead->s_x == food->s_x && nexthead->s_y == food->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "��";
			score += add;
			creat_food();
		}
		else if(nexthead->s_x == poison->s_x && nexthead->s_y == poison->s_y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Set_location(q->s_x,q->s_y);
			cout << "��";
			while (q->next->next->next != NULL)  {q=q->next;}
			Set_location(q->s_x, q->s_y);//��λ�����һ���ڵ��λ��
			cout <<" ";//�������ƶ��ˣ�������ʾ�����ľ�Ӧ����û���ߵ����壬�������һ���ո�
			Set_location(q->next->s_x,q->next->s_y);
			cout<<" ";
			delete q->next->next;//�ߵ��ƶ��½�����һ���ڵ㣬����û�гԵ���ʵ�����������߶���һ���ڵ㣬����Ҫ������Ǹ��ڵ��ͷ�
			q->next->next = NULL;
			delete q->next;
			q->next=NULL;
			life -= add;//�Ե���ҩ������
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
				cout << "��";
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
	if (Bite_self()||Bite_monster())//��ÿ���ƶ���Ҫ������ƶ����Ƿ�ҧ���Լ�,ֻ����move����п���ҧ���Լ����Է��ں����ж�
	{
		end_condition = 2;//���Ҫ���Լ���Ҫ��end_condition������Ӧ���������ֵ
		Die();//ҧ���Լ�����die����
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
			cout << "��";
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
				cout << "��";
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
			cout << "��";
			monsterscore += 2;
		}
		else
		{
			nexthead->mnext = monsterhead;
			monsterhead = nexthead;
			mq = monsterhead;
			Set_location(mq->m_x, mq->m_y);
				Green_color();
				cout << "��";
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
			cout << "��";
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
				cout << "��";
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
			cout << "��";
			monsterscore += 2;
		}
		else
		{
			nexthead->mnext = monsterhead;
			monsterhead = nexthead;
			mq = monsterhead;
			Set_location(mq->m_x, mq->m_y);
				Green_color();
				cout << "��";
			while (mq->mnext->mnext != NULL)
			{mq=mq->mnext;}
			Set_location(mq->m_x, mq->m_y);
			cout << " ";
			delete mq->mnext;
			mq->mnext = NULL;
		}
	}
}