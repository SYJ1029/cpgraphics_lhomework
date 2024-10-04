#include "ObjStruct.h"
#include "PiecedRect.h"


#define MOVESTRAIGHT 1
#define MOVEDIAGONAL 2
#define MOVETOGETHER 3
#define MOVEALL 4


class Patition : public RECTAnimaion {

public:


	Patition() : RECTAnimaion() {

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 2; j++)
				;
		}

	}



	Pos GetMiddlePos() {

		float midx = (pos[1].x - pos[0].x) / 2 + pos[0].x;
		float midy = (pos[0].y - pos[1].y) / 2 + pos[1].y;


		return { midx, midy };

	}

	Patition SetPatition2(Patition piece1, Patition* piece2) {
		Pos middle = GetMiddlePos();

		piece1.SetPos(pos[0].x, pos[0].y, middle.x, pos[1].y);
		piece2->SetPos(middle.x, pos[0].y, pos[1].x, pos[1].y);
		piece2->SetCol(col.R, col.G, col.B);


		return piece1;
	}

	Patition SetPatition(Patition piece1, Patition* piece2, Patition* piece3, Patition* piece4) {
		Pos middle = GetMiddlePos();

		
		piece1.SetPos(pos[0].x, pos[0].y, middle.x, middle.y); //좌상단

		piece2->SetPos(middle.x, pos[0].y, pos[1].x, middle.y); //우상단
		piece2->SetCol(col.R, col.G, col.B);

		piece3->SetPos(pos[0].x, middle.y, middle.x, pos[1].y); //좌하단
		piece3->SetCol(col.R, col.G, col.B);

		piece4->SetPos(middle.x, middle.y, pos[1].x, pos[1].y); //우하단
		piece4->SetCol(col.R, col.G, col.B);


		/*piece1->pos[0] = pos[0];
		piece1->pos[1] = middle;

		piece2->pos[0] = { middle.x, pos[0].y };
		piece2->pos[1] = { pos[1].x, middle.y };

		piece3->pos[0] = { pos[0].x, middle.y };
		piece3->pos[1] = { middle.x, pos[1].y };

		piece4->pos[0] = middle;
		piece4->pos[1] = pos[1];*/

		return piece1;
	}

	

	void NewPosDimension(float value) {
		float token = value / 2;

		/*if (pos[1].x - pos[0].x < 0.01 && value < 0)
			Clear();*/


		pos[0].x -= token;
		pos[1].x += token;

		pos[0].y += token;
		pos[1].y -= token;

		calvalue += value;

		if (calvalue < -0.03)
			Clear();
	}


	void Move() {
		pos[0].x += xflag;
		pos[1].x += xflag;

		pos[0].y += yflag;
		pos[1].y += yflag;

		
	}

	void SetMove(int xsign, int ysign) {


		xflag += xsign;
		yflag += ysign;

		/*switch (MoveOption) {
		case MOVESTRAIGHT:
			gradient = 0;
			xflag += xsign;
			yflag += ysign;
			break;
		case MOVEDIAGONAL:
			gradient = 1;
			break;
		default:
			break;
		}*/

	}

};