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
	//���� 3�� ���� �߰�
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


// ���ο� �ڽ� Ŭ���� ���찳�� ������ �簢���� ����� �� ũ�⸦ �Ҹ���.
// �簢���� �θ� Ŭ����ó�� Ű��� ����ϴ�.���ʿ� �װ� ���� Ŀ���� �ʾҴ°�

/* 
�׷� ���������� �� Ŭ������ 
�´��� �簢���� ����������, 
�� �簢���� calvalue�� �ڽ��� calvalue�� ���ϰ�,
���� calvalue�� �ڽ��� �߽� ������
���ο� �簢���� �����

����� �� ������ �⺻ �簢���� ũ�� ���� ���Խ�Ű��
�ٽ� �ҷ��� �� �� ũ�⸸ŭ ������ ���ָ� ���� �ʴ°�
*/

/*
SetPos()�� �� �ٲ���� �Ѵ�.
��ȯ�� �Ϸ�� ���콺�� ��ǥ�� �ް�, 
������ calvalue�� ���߾� 
�簢���� ��ǥ�� �����ϴ� �Լ��� ������

������ calvalue�� ũ�⸸ŭ '��'�� �ø���
�� '��'�� �簢���� �Ǵϱ�.


�ٵ� �ٽ� �����غ���.
'��'�� �÷��� �簢���� ����� ����� ä���Ѵٸ�
ó������ '��'�� ����� SetPos()�� ���� ����

ũ�⸦ �ø��� void NewPosDimension() �Լ��� �ᵵ �ȴ�
�ٸ� ���� �����ÿ� ���콺�� ��ǥ�� ����
���� ��ǥ�� �� pos�� �����ؾ� �ϴϱ�
SetPos()�� �Ű������� Pos����ü �ϳ��� �ް� �ϸ� �ǰڴ�
*/


class Erazer : public GL_RECT {

public:

	Erazer() : GL_RECT() {



	}


	void SetPos(Pos newpos) //���� ��п� ���缭
	{

		pos[0] = { newpos.x, newpos.y };
		pos[1] = { newpos.x, newpos.y };

		calvalue = 0.125;
		NewPosDimension(0.125);
		maked = true;

	}
	
	GL_RECT DeleteRect(GL_RECT dummyRect)
	{
		//�´��� �簢���� ���� ũ�⸦ �Թ��ϰ� �����
		col = dummyRect.col;
		//calvalue�� ������ ����
		//�� ó�� �簢������ ���� �� �� Ű������
		NewPosDimension(dummyRect.calvalue);
		dummyRect.Clear();


		return dummyRect;
	}

	/*
	�� Ŭ�������� calvalue�� 'ũ��'�� ��ü��
	
	�� ����� Ű��� �� �ƴ϶�
	ũ��� ��ǥ�� ������� ���Ӱ� ����� ����?
	�ٸ� ���찳�� �߰��� ������ ���ư��� �ȵ�
	������ �����ϵ� Move()�� ���� �ٱ���
	*/



};



