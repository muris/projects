#define STOP 0
#define UP 1
#define DOWN 2
#define FREE 3
#define WORK 4
#include <vector>
using namespace std;

class CElevatorSingle
{
protected:
	int direction;//Direction of the elevator, one of "stop", "up", and "down"
	int state;//Current state of the elevator, one of "free" and "work"
	int m_NowFlour;//Current flour 
public:
	int m_id;//id of elevator
	vector<int> m_FlourNum;//flours that the elevator should stop
	HWND m_hWnd;
public:
	CElevatorSingle()
	{
		direction = STOP;
		m_NowFlour = 1;
		state = FREE;
	}
	void WantedFlour(int num);//将需要的楼层按一定次序放入m_FlourNum
	void SetState(int s);
	int GetState();
	void SetDirection(int d);
	int GetDirection();
	void SetNowFlour(int nowflour);
	int GetNowFlour();
};