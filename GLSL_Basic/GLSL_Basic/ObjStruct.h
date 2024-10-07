#include "ColorStructs.h"

using namespace std;

#define NO7_VERTEX 1
#define NO7_LINE 2
#define NO7_TRIANGLE 3
#define NO7_RECT 6


typedef struct GLPos {
	GLfloat x;
	GLfloat y;
	GLfloat z;

}GLPos;

class Diagram
{
private:
	int posType;
	int vertexcnt;
public:
	GLfloat pos[4][3];
	GLfloat Center[2];
	bool maked;
	GLfloat col[4][3];
	float deltax, deltay, deltaz;
	float radian;

	Diagram() {
		posType = NO7_VERTEX;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				pos[i][j] = 0;
			}

		}
		vertexcnt = 0;
		maked = false;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				col[i][j] = 0.5;
			}
		}
		deltax = 0, deltay = 0, deltaz = 0;
		radian = 0;

		Center[0] = 0, Center[1] = 0;
	}

	int GetposType() {
		return posType;
	}

	void SetCol(MyObjCol col[3]) {
		for (int i = 0; i < 4; i++) {
			this->col[i][0] = col[0].R;
			this->col[i][1] = col[0].G;
			this->col[i][2] = col[0].B;
		}
	}

	void SetposType(int type) {
		posType = type;
	}


	void SetVertex(GLPos newpos){

		pos[0][0] = newpos.x;
		pos[0][1] = newpos.y;
		pos[0][2] = newpos.z;
	}

	void SetLine() {

		pos[1][0] = pos[0][0] + 0.4;
		pos[1][1] = pos[0][1];
		pos[1][2] = pos[0][2];
	}

	void SetPolygon_Basic() 
	{
		float centerX = (pos[1][0] - pos[0][0]) / 2;
		pos[0][0] -= centerX;
		pos[1][0] -= centerX;

		pos[0][1] -= 0.2;
		pos[1][1] -= 0.2;
	}
	void SetTriangle() {
		SetLine();
		SetPolygon_Basic();

		pos[2][0] = (pos[1][0] - pos[0][0]) / 2 + pos[0][0];
		pos[2][1] = pos[0][1] + 0.4;
		pos[2][2] = pos[0][2];
	}

	void SetRect() {
		SetLine();
		SetPolygon_Basic();

		pos[2][0] = pos[1][0];
		pos[2][1] = pos[1][1] + 0.4;
		pos[2][2] = pos[1][2];

		pos[3][0] = pos[0][0];
		pos[3][1] = pos[0][1] + 0.4;
		pos[3][2] = pos[0][2];
	}


	bool SetPos(GLPos newpos) {
		SetVertex(newpos);

		switch (posType) {
		case NO7_VERTEX:
			break;
		case NO7_LINE:
			SetLine();
			break;
		case NO7_TRIANGLE:
			SetTriangle();
			break;
		case NO7_RECT:
			SetRect();
			break;
		default:
			return false;
		}

		maked = true;
		return true;
	}

	bool Clear() {
		posType = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				pos[i][j] = 0;
			}

		}
		vertexcnt = 0;
		maked = false;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				col[i][j] = 0.5;
			}
		}

		return true;
	}

	void SetDelta(float deltax, float deltay, float deltaz) {
		this->deltax = deltax;
		this->deltay = deltay;
		this->deltaz = deltaz;
	}

	bool Move() {
		for (int i = 0; i < 4; i++) {
			pos[i][0] += deltax;
			pos[i][1] += deltay;
			pos[i][2] += deltaz;
		}


		return true;
	}

	bool SetRadian() {
		radian = (float)((float)45 / (float)180);

		return true;
	}

	float AllwaysPositive(float num) {

		if (num < 0)
			return num * -1;
		

		return num;
	}

	GLPos GetSorted(float a, float b) {
		if (a >= b)
			return { b, a };

		return { a, b };
	}

	bool SetCenter() {
		GLPos sorted = { 0 };
		/*Center[0] = ((pos[1][0] - pos[0][0]) / 2 + (pos[0][0]));
		Center[1] = ((pos[1][1] - pos[0][1]) / 2 + pos[0][1]);*/

		sorted = GetSorted(pos[0][0], pos[1][0]);
		Center[0] = ((sorted.y - sorted.x) / 2 + (sorted.x));
		sorted = GetSorted(pos[0][1], pos[1][1]);
		Center[1] = ((sorted.y - sorted.x) / 2 + (sorted.x));

		sorted = GetSorted(Center[0], pos[2][0]);
		Center[0] = (sorted.y - sorted.x) / 2 + sorted.x;
		sorted = GetSorted(Center[1], pos[2][1]);
		Center[1] = (pos[2][1] - Center[1]) / 2 + Center[1];

		/*Center[0] = (pos[2][0] - Center[0]) / 2 + Center[0];
		Center[1] = (pos[2][1] - Center[1]) / 2 + Center[1];*/

		return true;
	}

	bool Spin() {
		// 제자리 스핀은
		// 원점이 중심에 오도록 도형을 움직여서
		// 회전을 적용하고
		// 다시 원래 자리로 가게 해야 한다.

		SetCenter(); // 중앙 좌표 구하기

		for (int i = 0; i < 4; i++) // 모든 정점을 원점 기준으로
		{
			pos[i][0] -= Center[0];
			pos[i][1] -= Center[1];
		}

		float x = 0;

		for (int i = 0; i < 4; i++) //돌려라 돌려
		{
			x = pos[i][0];
			pos[i][0] = pos[i][0] * cos(radian) - pos[i][1] * sin(radian);
			pos[i][1] = x * sin(radian) + pos[i][1] * cos(radian);
		}

		for (int i = 0; i < 4; i++) // 다시 원래 중앙 값으로 복귀
		{
			pos[i][0] += Center[0];
			pos[i][1] += Center[1];
		}



		cout << "(" << pos[1][0] - pos[0][0] << ", " << pos[1][1] - pos[0][1] << ")" << endl;
		return true;
	}


	GLPos GetCenter() {
		SetCenter();
		return { Center[0], Center[1] };
	}
};


class Triangle : public Diagram {

public:

	Triangle() : Diagram() {
		SetposType(NO7_TRIANGLE);
	}

	bool SetPos(GLPos newpos) {
		SetVertex(newpos);

		switch (GetposType()) {
		case NO7_VERTEX:
			break;
		case NO7_LINE:
		case NO7_TRIANGLE:
			SetTriangle();
			break;
		case NO7_RECT:
			SetRect();
			break;
		default:
			return false;
		}

		maked = true;
		return true;
	}
};


GLPos WintoGL(int x, int y, int w, int h) {
	GLPos newpos;


	newpos.x = ((float)x - (float)(w / 2));
	newpos.x /= ((float)w / 2);
	newpos.y = ((float)y - (float)(h / 2));
	newpos.y /= ((float)h / 2);

	newpos.y = newpos.y * -1;

	newpos.z = 0.0;

	return newpos;
}


