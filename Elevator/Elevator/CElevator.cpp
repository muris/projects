#include "stdafx.h"
#include "CElevator.h"
#include <algorithm>

void CElevatorSingle::WantedFlour(int num)
{
	vector<int>::iterator it = m_FlourNum.begin();
	if (num > m_NowFlour)
	{
		direction = UP;
	}
	else if (num < m_NowFlour)
	{
		direction = DOWN;
	}
	else
	{
		direction = STOP;
	}
	switch (direction)
	{
	case UP:
		{
			for (; it != m_FlourNum.end(); it++)
			{
				if (num > (*it))
					continue;
				else
					break;
			}
			if (it != m_FlourNum.end())
				m_FlourNum.insert(it, num);
			else
				m_FlourNum.push_back(num);
		}
		break;
	case DOWN:
		{
			for (; it != m_FlourNum.end(); it++)
			{
				if (num < (*it))
					continue;
				else
					break;
			}
			if (it != m_FlourNum.end())
				m_FlourNum.insert(it, num);
			else
				m_FlourNum.push_back(num);
		}
		break;
	}
}

int CElevatorSingle::GetNowFlour()
{
	return m_NowFlour;
}

void CElevatorSingle::SetNowFlour(int nowflour)
{
	m_NowFlour = nowflour;
}

void CElevatorSingle::SetState(int s)
{
	state = s;
}

int CElevatorSingle::GetState()
{
	return state;
}

void CElevatorSingle::SetDirection(int d)
{
	direction = d;
}

int CElevatorSingle::GetDirection()
{
	return direction;
}
