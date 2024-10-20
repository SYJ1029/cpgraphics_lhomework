#include "ColorStructs.h"

using namespace std;

#define NO7_VERTEX 1
#define NO7_LINE 2
#define NO7_TRIANGLE 3
#define NO7_RECT 6

#define PI 3.14159265358979

void Myswap(float* value1, float* value2) {

	float token = *value1;

	(*value1) = *value2;
	*value2 = token;
}


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


		for(int i = 0; i < 2; i++)
			Center[i] = (pos[0][i] + pos[1][i] + pos[2][i]) / 3;


		/*sorted = GetSorted(pos[0][0], pos[1][0]);
		Center[0] = ((sorted.y - sorted.x) / 2 + (sorted.x));
		sorted = GetSorted(pos[0][1], pos[1][1]);
		Center[1] = ((sorted.y - sorted.x) / 2 + (sorted.x));

		sorted = GetSorted(Center[0], pos[2][0]);
		Center[0] = (sorted.y - sorted.x) / 2 + sorted.x;
		sorted = GetSorted(Center[1], pos[2][1]);
		Center[1] = (pos[2][1] - Center[1]) / 2 + Center[1];*/

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


#define NOT_MOVE 0
#define MOVE_STRAIGHT 1
#define MOVE_ZIGZAG 2
#define MOVE_RECTSPIRAL 3
#define MOVE_CIRCLESPIRAL 4
#define MOVE_TORNADO 5


class TriAnimation : public Diagram {

public:
	float delta[3];
	float MaxX, MaxY, MaxZ;
	float minx, miny, minz;
	float pluscount;
	int mulcount;
	int MoveType;
	
	float theta;
	float r, prevpos[2];
	float Spincenter[3];

	bool direct;
	int cw;

	TriAnimation() : Diagram() {

		SetposType(NO7_TRIANGLE);

		radian = 0;
		r = 0, prevpos[0] = 0, prevpos[1] = 0;
		MoveType = NOT_MOVE;

		for (int i = 0; i < 3; i++)
			Spincenter[i] = 0.0;

		delta[0] = 0.01, delta[1] = 0.01, delta[2] = 0.01;
		MaxX = 0, MaxY = 0, MaxZ = 0;
		minx = 0, miny = 0, minz = 0;

		pluscount = 0.01;
		mulcount = 4;
		theta = 0;
		direct = true; // true는 x방향 아니면 y
		cw = 1;
	}


	bool SubTri() {

		pos[0][0] += 0.1;
		pos[1][0] -= 0.1;
		
		pos[0][1] += 0.1;
		pos[1][1] += 0.1;
		pos[2][1] -= 0.1;
		/*for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 2; j++) {
				pos[i][j] *= 0.5;
			}
		}*/

		return true;
	}

	bool Settheta(float radian) {
		theta = radian;

		if (radian < 0)
			mulcount = -1;
		else
			mulcount = 1;

		return true;
	}

	void SetMoveType(int option) {
		MoveType = option;
	}

	void SetDelta(float deltax, float deltay, float deltaz) {
		this->delta[0] = deltax;
		this->delta[1] = deltay;
		this->delta[2] = deltaz;
	}

	void SetMax(float maxx, float maxy, float maxz, bool option) {
		switch (MoveType) {
		case MOVE_ZIGZAG:
			if (option) {
				// x는 벽까지, y는 고정된 범위만큼
				MaxX = 1, minx = -1;
				MaxY = pos[0][1] + 5 * pluscount;
				miny = 5 * maxy;
				MaxZ = 0, minz = 0;

				if (delta[1] != 0) {
					direct = !(direct);
				}

				if (delta[1] < 0 || delta[0] < 0) {
					miny *= -1;
				}

			}
			break;
		case MOVE_RECTSPIRAL:
			// 사각 스파이럴에서 이 함수의 매개변수는 pluscount에 반영한다.
			// 기본 pluscount에 maxx, maxy 곱
			MaxX = pluscount * (float)mulcount;

			if (maxx > 0)
				direct = true;
			if (maxy > 0)
				direct = false;

			/*for (int i = 0; i < 3; i++) {
				if (delta[i] < 0)
					delta[i] *= -1;
			}*/

			

			break;
		}
	}



	float GetMin(bool IsX) {
		float min = 2;
		if (IsX) {
			for (int i = 0; i < 3; i++) {
				if (pos[i][0] < min)
					min = pos[i][0];
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				if (pos[i][1] < min)
					min = pos[i][1];
			}
		}

		return min;
	}

	float GetMax(bool IsX) {
		float max = -2;
		if (IsX) {
			for (int i = 0; i < 3; i++) {
				if (pos[i][0] > max)
					max = pos[i][0];
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				if (pos[i][1] > max)
					max = pos[i][1];
			}
		}

		return max;
	}

	void MoveBasic() {
		// 쭉 가다가 부딪히면 튕기는 아주 기본적인 움직임을 나타낸 함수

		for (int i = 0; i < 4; i++) {
			pos[i][0] += delta[0];
			pos[i][1] += delta[1];
		}

		if (GetMin(true) <= -1.0 || GetMax(true) >= 1.0) {
			delta[0] *= -1;
		}

		if (GetMin(false) <= -1.0 || GetMax(false) >= 1.0) {
			delta[1] *= -1;
		}
		
	}

	bool GetDirect() {
		if (MaxX == 1.0)
			return true;

		return false;
	}

	void MoveZigZag() {
		// 그냥 일직선으로 가다가 벽과 충돌시에 방향 전환

		bool nowdirect = GetDirect();

		//direct = !(direct);


		for (int i = 0; i < 4; i++) {
			pos[i][1 - direct] += delta[1 - direct];

		}


		if (direct == false && MaxY > 0)
			pluscount += 0.01;

		if (direct == false && MaxY < 0)
			pluscount -= 0.01;
		

		
		if (direct) {

			if ((GetMax(direct) >= MaxX || GetMin(direct) <= minx) && delta[1 - direct] != 0) {
				if (GetMax(!(direct)) >= 1.0 || GetMin(!(direct)) <= -1.0) {
					miny *= -1;
				}
				direct = false;
				MaxY = miny * pluscount;
				delta[direct] = 0, delta[1 - direct] = 0.01;
				if (miny < 0)
					delta[1 - direct] *= -1;
			}
			
		}
		else {
			if ((MaxY > 0 && pluscount >= MaxY)||
				(MaxY < 0 && pluscount <= MaxY)||
				(GetMax(false) >= 1.0 && MaxY > 0) ||
				(GetMin(false) <= -1.0 && MaxY < 0)) {
				direct = true;
				delta[0] = 0.01, delta[1] = 0;
				pluscount = 0.01;

				if (GetMax(true) >= MaxX)
					delta[1 - direct] *= -1;

			}

		}
		
		//direct = !(direct);


	}

	bool CheckValidChange(float delta) {
		if (delta > 0 && pluscount >= MaxX)
			return true;
		if (delta < 0 && pluscount <= MaxX)
			return true;

		return false;
	}

	void MoveRectSpiral() {
		for (int i = 0; i < 4; i++) {
			pos[i][1 - direct] += delta[1 - direct];

		}

		if (delta[1 - direct] > 0)
			pluscount = pluscount + 0.01;
		else if (delta[1 - direct] < 0)
			pluscount = pluscount - 0.01;

		if (CheckValidChange(delta[1 - direct])) {
			direct = !(direct);
			delta[1 - direct] *= -1;
			
			mulcount += 4 * cw;

			pluscount = delta[1 - direct];


			/*if (cw) {
				if ((delta[direct] > 0 && direct == false) ||
					(delta[direct] < 0 && direct)) {
					cout << "cnt: " << MaxX << "direct: " << direct << endl << endl;
					pluscount = pluscount * -1;
				}
			}
			else {
				if (delta[1 - direct] != delta[direct]) {
					pluscount = pluscount * -1;

				}

			}*/
			

			MaxX = pluscount * (float)mulcount;
		}

		if (GetMax(true) >= 1.0 || GetMin(true) <= -1.0 ||
			GetMax(false) >= 1.0 || GetMin(false) <= -1.0) {
			delta[1 - direct] *= -1;
			cw *= -1;

			pluscount = delta[1 - direct];
			MaxX = pluscount * (float)mulcount;
		}


		else if (mulcount < 4) {
			delta[1 - direct] *= -1;
			cw *= -1;

			pluscount = delta[1 - direct];
			MaxX = pluscount * (float)mulcount;
		}
	}

	void SetSpincenter() {
		SetCenter();
		Spincenter[0] = Center[0];
		Spincenter[1] = Center[1];
		r = 0;
		prevpos[0] = Center[0];
		prevpos[1] = Center[1];
		


	}

	bool Spin() {
		// 우린 제자리 돌기가 아니라 지정된 좌표를 중심으로 돌릴 것


		for (int i = 0; i < 4; i++) // 설정된 중심 좌표 만큼 이동
		{
			pos[i][0] -= Spincenter[0];
			pos[i][1] -= Spincenter[1];
			pos[i][2] -= Spincenter[2];
		}

		float x = 0;

		for (int i = 0; i < 4; i++) //돌려라 돌려
		{
			x = pos[i][0];
			pos[i][0] = pos[i][0] * cos(theta / 180) - pos[i][1] * sin(theta / 180);
			pos[i][1] = x * sin(theta / 180) + pos[i][1] * cos(theta / 180);
		}

		for (int i = 0; i < 4; i++) // 다시 원래 값으로 복귀
		{
			pos[i][0] += Spincenter[0];
			pos[i][1] += Spincenter[1];
		}



		cout << "(" << pos[1][0] - pos[0][0] << ", " << pos[1][1] - pos[0][1] << ")" << endl;
		return true;
	}

	bool AdjustwithRadian() {
		// 반지름의 길이가 바뀌면 바뀐 반지름에 맞춰서 좌표를 옮겨줘야 한다.
		// 새 반지름과 기존 반지름으로 만들어지는 삼각형은 서로 닮음이고, 두 반지름이 비율이 곧 x, y값끼리의 비율과 같다.
		// 새 반지름 / 기존 반지름 = 새 x / 기존 x
		// 새 x = 기존 x (새 반지름 / 기존 반지름)
		// y도 같음
		// 회전을 진행하기 전에 실행하는 함수


		Center[0] -= Spincenter[0];
		Center[1] -= Spincenter[1];

		Center[0] = r * cos(radian / 180);
		Center[1] = r * sin(radian / 180);

		Center[0] += Spincenter[0];
		Center[1] += Spincenter[1];

		for (int i = 0; i < 4; i++) {
			//x, y 기준 spin


			pos[i][0] += (Center[0] - prevpos[0]);
			pos[i][1] += (Center[1] - prevpos[1]);

			
		}

		for (int i = 0; i < 2; i++)
			prevpos[i] = Center[i];

		return true;
	}

	float dist(float x1, float x2, float y1, float y2) {

		float token = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);

		return sqrt(token);
	}

	void MoveCirlceSpiral() {
		radian += theta;
		r += theta * mulcount/50000;
		AdjustwithRadian();
		//Spin();		

		if (GetMax(true) >= 1.0 || GetMin(true) <= -1.0 ||
			GetMax(false) >= 1.0 || GetMin(false) <= -1.0) {
			theta *= -1;
		}


		if (r <= 0 && theta < 0) {
			theta *= -1;
		}

	}


	void Move() {
		switch (MoveType) {
		case MOVE_STRAIGHT:
			MoveBasic();
			break;
		case MOVE_ZIGZAG:
			MoveZigZag();
			break;
		case MOVE_RECTSPIRAL:
			MoveRectSpiral();
			break;
		case MOVE_CIRCLESPIRAL:
			MoveCirlceSpiral();
			break;
		default:
			break;
		}
	}
};


#define NO11_TOLINE 6
#define NO11_TOTRIANGLE 3
#define NO11_TORECT 4
#define NO11_TOPENTAGON 5


class PlusDiagram {

public:
	int Vertexcnt;
	float r, radian, theta;
	GLPos Spinindex[3];
	GLfloat Pos[6][3];
	GLfloat col[6][3];
	bool maked, first;


	void Clear() {
		Vertexcnt = 0;
		r = 0, radian = 0, theta = 0;
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 3; j++)
				Pos[i][j] = 0;

		for (int i = 0; i < 3; i++) {
			Spinindex[i] = { 0, 0, 0 };
		}

		maked = false;
		first = true;
	}


	PlusDiagram() {
		Clear();
	}

	void SetposType(int type) {
		Vertexcnt = type;
	}

	void SetPos(GLPos Center) {
		/*Pos = (GLPos**)malloc(sizeof(GLPos*) * Vertexcnt);

		for (int i = 0; i < Vertexcnt; i++) {
			Pos[i] = (GLPos*)malloc(sizeof(GLPos));
		}*/

		switch (Vertexcnt) {
		case NO11_TOLINE: // 얜 5각형이긴 한데 완전한 5각형

			Pos[0][0] = Center.x - 0.1;
			Pos[1][0] = Center.x + 0.1;
			/*Pos[2][0] = Pos[1][0];
			Pos[4][0] = Pos[0][0];*/

			Pos[0][1] = Center.y - 0.1;
			Pos[1][1] = Pos[0][1];
			/*Pos[2][1] = Center.y + 0.1;
			Pos[4][1] = Pos[2][1];*/

			for (int i = 0; i < 3; i++) {
				Pos[2][i] = Pos[0][i];
				Pos[3][i] = Pos[0][i];
				Pos[4][i] = Pos[1][i];
			}

			Spin_by_Index(0, 4, 108);
			Spin_by_Index(1, 2, -108);

			Spin_by_Index(4, 3, 108);


			radian = 108;
			theta = 1;
			r = 0.1;
			break;
		case NO11_TOTRIANGLE:
			Pos[0][0] = Center.x - 0.1;
			Pos[1][0] = Center.x + 0.1;
			
			Pos[0][1] = Center.y - 0.1;
			Pos[1][1] = Pos[0][1];


			for(int i = 0; i < 3; i++)
				Pos[2][i] = Pos[1][i];
			/*Pos[2][1] += 0.1;*/

			radian = 0;
			theta = 1;
			r = 0.2;
			break;
		case NO11_TORECT:
			Pos[0][0] = Center.x - 0.1;
			Pos[1][0] = Center.x + 0.1;
			Pos[2][0] = (Pos[1][0] - Pos[0][0])/2 + Pos[0][0];

			Pos[0][1] = Center.y - 0.1;
			Pos[1][1] = Pos[0][1];
			Pos[2][1] = Pos[0][1] + (Pos[1][0] - Pos[0][0])/2 * 1.717;

			for (int i = 0; i < 2; i++)
				Pos[3][i] = Pos[2][i];
			/*Pos[3][0] -= 0.1;*/


			radian = 60;
			theta = 1;
			r = 0.1;
			break;
		case NO11_TOPENTAGON: // 사각형의 마지막 정점에 마지막 좌표가 숨겨진 놈
			Pos[0][0] = Center.x - 0.1;
			Pos[1][0] = Center.x + 0.1;
			Pos[2][0] = Pos[1][0];
			Pos[3][0] = Pos[0][0];

			Pos[0][1] = Center.y - 0.1;
			Pos[1][1] = Pos[0][1];
			Pos[2][1] = Center.y + 0.1;
			Pos[3][1] = Pos[2][1];

			for (int i = 0; i < 3; i++)
				Pos[4][i] = Pos[0][i];

			/*Pos[4][1] += 0.5;*/

			radian = 0;
			theta = 1;
			r = 0.1;
			break;
		default:
			break;
		}


		maked = true;
	}

	void SetCol(MyObjCol col[3]) {
		for (int i = 0; i < 6; i++) {
			this->col[i][0] = col[0].R;
			this->col[i][1] = col[0].G;
			this->col[i][2] = col[0].B;
		}
	}

	int GetposType() {
		return Vertexcnt;
	}

	void Spin_by_Index(int index1, int index2, float theta) {
		Pos[index2][0] -= Pos[index1][0];
		Pos[index2][1] -= Pos[index1][1];

		/*Pos[index2][0] = r * cos(radian / 180.0f * PI);
		Pos[index2][1] = r * sin(radian / 180.0f * PI);*/
		float x = Pos[index2][0];
		Pos[index2][0] = Pos[index2][0] * cos(theta / 180.0f * PI) - Pos[index2][1] * sin(theta/180 * PI);
		Pos[index2][1] = x * sin(theta / 180.0f * PI) + Pos[index2][1] * cos(theta/180 * PI);

		Pos[index2][0] += Pos[index1][0];
		Pos[index2][1] += Pos[index1][1];
	}


	bool Spin_Line_To_Tri() {
		if (radian >= 60)
			return false;

		Spin_by_Index(0, 2, theta);
		radian += theta;
		
		

		return true;
	}
	
	bool Spin_Tri_To_Rect() {
		if (radian >= 90)
			return false;

		Spin_by_Index(0, 3, theta);
		Spin_by_Index(1, 2, theta * -1);

		radian += theta;

		return true;
	}

	bool Spin_Rect_To_Penta() {
		if (radian < 18) {
			Spin_by_Index(0, 3, theta);
			Spin_by_Index(1, 2, theta * -1);
			first = true;
		}

		if (radian >= 108)
			return false;

		if (radian >= 18 && first) {
			for (int i = 0; i < 3; i++) {
				Pos[4][i] = Pos[3][i];
				Pos[3][i] = Pos[0][i];
			}

			first = false;
		}

		Spin_by_Index(4, 3, theta);

		radian += theta;

		return true;
	}

	bool Spin_Penta_To_Line() {
		if (radian <= 0) {
			first = true;
			return true;
		}

		Spin_by_Index(4, 3, theta * -1);
		Spin_by_Index(1, 2, theta);
		

		radian -= theta;

		return true;
	}

	bool Spin_Penta_To_Line2() {
		if (radian >= 108) {
			first = false;
			return false;
		}
	

		Spin_by_Index(0, 1, theta);

		radian += theta;
		return true;
	}


	bool Spin() {
		switch (Vertexcnt) {
		case NO11_TOLINE:
			if (first == false) {
				return Spin_Penta_To_Line();
			}
			else {
				return Spin_Penta_To_Line2();
			}
			

			break;
		case NO11_TOTRIANGLE:
			return Spin_Line_To_Tri();

			break;
		case NO11_TORECT:
			return Spin_Tri_To_Rect();

			break;
		case NO11_TOPENTAGON:
			return Spin_Rect_To_Penta();

			break;
		default:
			return false;
			break;
		}

		return true;

	}


};


class MulandMove : public PlusDiagram{


public:
	GLPos Center;
	bool clicked;


	MulandMove() : PlusDiagram() {
		Center = { 0 };
		clicked = false;

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 3; j++) {
				Pos[i][j] = 0;
				col[i][j] = 0;
			}
		}


	}

	void SetCol(MyObjCol col[3]) {
		for (int i = 0; i < 6; i++) {
			this->col[i][0] = col[0].R;
			this->col[i][1] = col[0].G;
			this->col[i][2] = col[0].B;
		}
	}

	void SetPos(GLPos Center) {
		this->Center = Center;

		switch (Vertexcnt) {
		case NO7_VERTEX:
			Pos[0][0] = Center.x - 0.0075;
			Pos[0][1] = Center.y - 0.0075;
			Pos[1][0] = Center.x + 0.0075;
			Pos[1][1] = Center.y - 0.0075;
			Pos[2][0] = Center.x;
			Pos[2][1] = Center.y + 0.0075;
			break;
		case NO7_LINE: // 얜 5각형이긴 한데 완전한 5각형

			Pos[0][0] = Center.x - 0.1;
			Pos[0][1] = Center.x + 0.1;

			Pos[0][1] = Center.y;
			Pos[1][1] = Center.y;

			break;
		case NO11_TOTRIANGLE:
			Pos[0][0] = Center.x - 0.1;
			Pos[1][0] = Center.x + 0.1;

			Pos[0][1] = Center.y - 0.1;
			Pos[1][1] = Pos[0][1];


			for (int i = 0; i < 3; i++)
				Pos[2][i] = Pos[1][i];
			/*Pos[2][1] += 0.1;*/

			radian = 0;
			theta = 1;
			r = 0.2;


			Spin_by_Index(0, 2, 60);
			break;
		case NO11_TORECT:
			Pos[0][0] = Center.x - 0.1;
			Pos[1][0] = Center.x + 0.1;
			Pos[2][0] = (Pos[1][0] - Pos[0][0]) / 2 + Pos[0][0];

			Pos[0][1] = Center.y - 0.1;
			Pos[1][1] = Pos[0][1];
			Pos[2][1] = Pos[0][1] + (Pos[1][0] - Pos[0][0]) / 2 * 1.717;

			for (int i = 0; i < 2; i++)
				Pos[3][i] = Pos[2][i];
			/*Pos[3][0] -= 0.1;*/


			radian = 60;
			theta = 1;
			r = 0.1;

			Spin_by_Index(0, 3, 30);
			Spin_by_Index(1, 2, -30);
			break;
		case NO11_TOPENTAGON: // 사각형의 마지막 정점에 마지막 좌표가 숨겨진 놈

			Pos[0][0] = Center.x - 0.1;
			Pos[1][0] = Center.x + 0.1;
			/*Pos[2][0] = Pos[1][0];
			Pos[4][0] = Pos[0][0];*/

			Pos[0][1] = Center.y - 0.1;
			Pos[1][1] = Pos[0][1];
			/*Pos[2][1] = Center.y + 0.1;
			Pos[4][1] = Pos[2][1];*/

			for (int i = 0; i < 3; i++) {
				Pos[2][i] = Pos[0][i];
				Pos[3][i] = Pos[0][i];
				Pos[4][i] = Pos[1][i];
			}

			Spin_by_Index(0, 4, 108);
			Spin_by_Index(1, 2, -108);

			Spin_by_Index(4, 3, 108);


			radian = 108;
			theta = 1;
			r = 0.1;
			break;

		case NO11_TOLINE:

			Pos[0][0] = Center.x - 0.1;
			Pos[1][0] = Center.x + 0.1;
			Pos[2][0] = (Pos[1][0] - Pos[0][0]) / 2 + Pos[0][0];

			Pos[0][1] = Center.y - 0.1;
			Pos[1][1] = Pos[0][1];
			Pos[2][1] = Pos[0][1] + (Pos[1][0] - Pos[0][0]) / 2 * 1.717;

			for (int i = 0; i < 2; i++)
				Pos[3][i] = Pos[2][i];
			/*Pos[3][0] -= 0.1;*/

			Spin_by_Index(0, 3, 30);
			Spin_by_Index(1, 2, -30);




			for (int i = 0; i < 3; i++) {
				Pos[5][i] = Pos[3][i];
				Pos[4][i] = Pos[0][i];
				Pos[3][i] = Pos[1][i];

			}


			Spin_by_Index(0, 5, 30);
			Spin_by_Index(1, 2, -30);
			Spin_by_Index(5, 4, 120);
			Spin_by_Index(2, 3, -120);
			

			break;
		default:
			break;
		}


		maked = true;
	}



	bool CheckPosIn(GLPos newpos) {
		switch (Vertexcnt)
		{
		case NO7_VERTEX: case NO7_TRIANGLE:
			if (newpos.x >= Pos[0][0] && newpos.x <= Pos[1][0] &&
				newpos.y >= Pos[0][1] && newpos.y <= Pos[2][1])
				return true;

			break;
		case NO7_LINE:
			if (newpos.x >= Pos[0][0] && newpos.x <= Pos[1][0] &&
				newpos.y >= Pos[0][1] && newpos.y <= Pos[1][1])
				return true;


			break;
		case NO11_TORECT:
			if (newpos.x >= Pos[0][0] && newpos.x <= Pos[1][0] &&
				newpos.y >= Pos[0][1] && newpos.y <= Pos[2][1])
				return true;


			break;
		case NO11_TOPENTAGON:
			if (newpos.x >= Pos[4][0] && newpos.x <= Pos[2][0] &&
				newpos.y >= Pos[0][1] && newpos.y <= Pos[3][1])
				return true;

			break;
		default:
			break;
		}



		return false;

	}
	


	bool SetNewDiagram(int postype) {

		Vertexcnt = (Vertexcnt + postype) % 6;
		SetPos(Center);
		


		return true;
	}



	void MoveDrag(float deltax, float deltay, float deltaz) {
		int token = Vertexcnt;
		if (token == 1)token = 3;


		for (int i = 0; i < token; i++) {
			Pos[i][0] += deltax;
			Pos[i][1] += deltay;
			Pos[i][2] += deltaz;
			Center = { Center.x + deltax, Center.y + deltay, Center.z + deltaz };

		}
	}




};