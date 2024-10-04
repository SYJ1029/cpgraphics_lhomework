


class PiecedRect
{
public: 
	bool pieced;
	Pos pos[2];
	PiecedRect (*piece)[4];
	float deltaX, deltaY;
	float calvalue;

	PiecedRect() {
		pieced = false;
		pos[0] = { 0 };
		pos[1] = { 0 };

		deltaX = 0, deltaY = 0;
		calvalue = 0;
	}

	PiecedRect(Pos newpos1, Pos newpos2, float deltaX, float deltaY) {
		pos[0] = newpos1;
		pos[1] = newpos2;

		this->deltaX = deltaX;
		this->deltaY = deltaY;
	}

	void NewDimension() {

	}

	void Move() {
		pos[0] = { pos[0].x + deltaX, pos[0].y + deltaY };
		pos[1] = { pos[1].x + deltaX, pos[1].y + deltaY };


	}


}PiecedRect;


//typedef struct PiecedRect {
//	bool pieced;
//	Pos pos[2];
//	PiecedRect (*piece)[2];
//}PiecedRect;



