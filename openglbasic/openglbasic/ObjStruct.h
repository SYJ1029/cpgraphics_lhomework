#include "ColorStructs.h"

#define COMPARE_MAX 10
#define COMPARE_MIN -10

typedef struct Pos {
	float x;
	float y;
}Pos;


class GL_RECT {
private:
	

public:
	Pos pos[2];
	MyObjCol col;
	float calvalue;
	//과제 3번 문항 추가
	bool maked;
	bool chosen;

	GL_RECT() {
		for(int i = 0; i < 2; i++)
			pos[i] = {-2, -2};

		col = { 0.0, 0.0, 0.0 };
		calvalue = 0;
		maked = false;
		chosen = false;
	}

	

	void SetPos(float x1, float y1, float x2, float y2) {
		pos[0] = {x1, y1};
		pos[1] = { x2, y2 };
		maked = true;
	}

	void SetCol(GLfloat R, GLfloat G, GLfloat B) {
		col = { R, G, B };
	}

	void NewPosDimension(float value) {
		float token = value / 2;

		if (pos[1].x - pos[0].x < 0.2 && value < 0)
			return;

		pos[0].x -= token;
		pos[1].x += token;

		pos[0].y += token;
		pos[1].y -= token;

		calvalue += value;
	}
	

	void Move(float deltaX, float deltaY) {

		std::cout << "x: " << deltaX << std::endl;
		std::cout << "y: " << deltaY << std::endl;
		pos[0].x += deltaX;
		pos[1].x += deltaX;

		pos[0].y += deltaY;
		pos[1].y += deltaY;
	}

	void Clear() {
		for (int i = 0; i < 2; i++)
			pos[i] = { -2, -2 };

		col = { 0.0, 0.0, 0.0 };
		calvalue = 0;
		maked = false;
		chosen = false;

	}
	
};

class RECTAnimaion : public GL_RECT {
private:
	Pos original[2];

public:
	float gradient;
	float deltax;
	bool zigzag;
	float zzlimit;
	float xflag;
	float upcnt;
	float yflag;

	RECTAnimaion() : GL_RECT(){
		original[0] = pos[0];
		original[1] = pos[1];

		gradient = 1;
		deltax = 0.01;
		zigzag = false;
		zzlimit = 0.9;
		xflag = 0.0;
		yflag = 0.0;
		upcnt = 0;
	}


	void Setanimation() {
		zzlimit = pos[1].x + 0.25;
		if(zzlimit >= 1.0)
			zzlimit = 1.0;


		xflag = (pos[1].x - pos[0].x) / 2 + pos[0].x;
		yflag = (pos[0].y - pos[1].y) / 2 + pos[1].y;

	}

	void SetPos(float x1, float y1, float x2, float y2) {
		pos[0] = { x1, y1 };
		pos[1] = { x2, y2 };
		maked = true;

		//Setanimation();
		/*zzlimit = pos[1].x + 0.3;
		if (zzlimit >= 1.0)
			zzlimit = 0.9;*/

		original[0] = pos[0];
		original[1] = pos[1];

	}

	void changesign() {
		deltax *= -1;
	}

	bool bounce(float xlimit, float ylimit, float xsub) {
		if (pos[0].x > xsub * 2 - xlimit && pos[1].x < xlimit
			&& pos[0].y < ylimit && pos[1].y > ylimit * -1 )
			return false;

		if (pos[1].x >= xlimit || pos[0].x <= xsub * 2 - xlimit)
			deltax *= -1;


		gradient *= -1;

		return true;
	}

	void RevertPos() {
		pos[0] = original[0];
		pos[1] = original[1];
	}


	void Move() {
		pos[0].x += deltax;
		pos[1].x += deltax;

		pos[0].y += deltax * gradient;
		pos[1].y += deltax * gradient;

		if (zigzag) {
			/*MoveZigZag();*/
			
			bounce(zzlimit, 1.0, xflag);

			

		}
		else {
			xflag = 0.0;
			bounce(1.0, 1.0, xflag);
		}
	}

	
	void SetUpCnt() {
		upcnt = (float)((float)rand() / RAND_MAX) / 5;

		upcnt -= 0.1;
	}

	void ChangeSize() {
		SetUpCnt();


		if (upcnt < 0) {
			std::cout << upcnt << std::endl;
		}

		pos[1].x += upcnt;
		pos[0].y += upcnt;


		/*switch (option) {
		case COMPARE_MAX:
			NewPosDimension(randnum);
			break;
		case COMPARE_MIN:
			NewPosDimension(randnum * -1);
			break;
		default:
			break;
		}*/
	}

	void Clear() {
		for (int i = 0; i < 2; i++)
			pos[i] = { -2, -2 };

		col = { 0.0, 0.0, 0.0 };
		maked = false;


		original[0] = pos[0];
		original[1] = pos[1];

		gradient = 1;
		deltax = 0.01;
		zigzag = false;
		zzlimit = 0.9;
		xflag = 0.0;
		upcnt = 0;
	}
};


// 새로운 자식 클래스 지우개는 기존의 사각형을 지우며 그 크기를 불린다.
// 사각형은 부모 클래스처럼 키우면 충분하다.애초에 그게 골고루 커지지 않았는가

/* 
그럼 실질적으로 밑 클래스는 
맞닿은 사각형을 지워버리고, 
그 사각형의 calvalue를 자신의 calvalue에 더하고,
더한 calvalue와 자신의 중심 값으로
새로운 사각형을 만들고

사라질 땐 지정한 기본 사각형의 크기 값을 대입시키고
다시 불러올 때 그 크기만큼 세팅을 해주면 되지 않는가
*/

/*
SetPos()를 좀 바꿔줘야 한다.
변환만 완료된 마우스의 좌표를 받고, 
지정한 calvalue에 맞추어 
사각형의 좌표를 생성하는 함수를 만들자

지정한 calvalue의 크기만큼 '점'을 늘리면
그 '점'은 사각형이 되니까.


근데 다시 생각해보자.
'점'을 늘려서 사각형을 만드는 방식을 채택한다면
처음부터 '점'을 만드는 SetPos()는 쓸모가 없다

크기를 늘리는 void NewPosDimension() 함수만 써도 된다
다만 최초 생성시에 마우스의 좌표를 토대로
같은 좌표의 두 pos를 생성해야 하니까
SetPos()의 매개변수를 Pos구조체 하나만 받게 하면 되겠다
*/


class Erazer : public GL_RECT {

public:

	Erazer() : GL_RECT() {



	}


	void SetPos(Pos newpos) //위의 결론에 맞춰서
	{

		pos[0] = { newpos.x, newpos.y };
		pos[1] = { newpos.x, newpos.y };

		calvalue = 0.125;
		NewPosDimension(0.125);
		maked = true;

	}
	
	GL_RECT DeleteRect(GL_RECT dummyRect)
	{
		//맞닿은 사각형의 색과 크기를 먹방하고 지우기
		col = dummyRect.col;
		//calvalue는 증가량 변수
		//즉 처음 사각형들을 만들 때 좀 키워놓자
		NewPosDimension(dummyRect.calvalue);
		dummyRect.Clear();


		return dummyRect;
	}

	/*
	이 클래스에서 calvalue는 '크기'그 자체다
	
	즉 만들고 키우는 게 아니라
	크기와 좌표를 기반으로 새롭게 만드는 느낌?
	다만 지우개는 중간에 점으로 돌아가면 안됨
	원형을 유지하되 Move()를 조금 바구자
	*/



};



