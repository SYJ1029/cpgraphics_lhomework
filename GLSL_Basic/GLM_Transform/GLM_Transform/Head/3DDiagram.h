#include "GetShader.h"


#define POINT 1
#define CUBE 8



class Diagram {



public:
	int postype;
	glm::vec3 axis;
	GLPos center;
	float radian;
	int radcnt;
	GLPos delta;
	GLPos Stretch;

	Diagram() {

		postype = POINT;

		radian = 0;
		center = { 0, 0, 0 };
		axis = glm::vec3( 0.0f, 1.0f, 0.0f );
		delta = { 0, 0, 0 };

		radcnt = 1;

		for (int i = 0; i < 3; i++) {
			Stretch = { 1.0f };
		}
	}


	void Revert() {
		delta = { 0, 0, 0 };
	}

	void Clear() {
		Revert();
		radian = 0;
		axis = { 0, 0, 0 };
		
		radcnt = 1;
	}

	void Setcol(MyObjCol col[]) {

	}

	void SetPos(){

	}

	int* AddIndexList(){

	}

	~Diagram() {
		cout << "Diagram is deleted" << endl << endl;
	}


	void SetSpin(bool ccw, glm::vec3 axis) {

		this->axis = axis;

		if (ccw)
			radcnt = 1;
		else
			radcnt = -1;
	}

	void Spin() {
		radian += radcnt;
	}

	void Move(GLPos delta) {
		this->delta.x += delta.x;
		this->delta.y += delta.y;
		this->delta.z += delta.z;
	}



};


class GL_Cube : public Diagram {

public:
	GLfloat col[8][3];
	GLfloat pos[8][3];
	bool maked[6];
	int start_index;

	GL_Cube() : Diagram() {
		postype = CUBE;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 3; j++) {
				pos[i][j] = 0;
				col[i][j] = 0;
			}

			if (i < 6)
				maked[i] = false;
		}	

		start_index = 0;
	}

	void Setcol(MyObjCol col[8]) {
		for (int i = 0; i < 8; i++) {
			this->col[i][0] = col[i].R;
			this->col[i][1] = col[i].G;
			this->col[i][2] = col[i].B;

		}
	}

	void SetPos() {
		pos[0][0] = -0.5f; pos[0][1] = -0.5f; pos[0][2] = -0.5f;
		pos[1][0] = 0.5f; pos[1][1] = -0.5f;  pos[1][2] = -0.5f;
		pos[2][0] = 0.5f; pos[2][1] = 0.5f; pos[2][2] = -0.5f;
		pos[3][0] = -0.5f; pos[3][1] = 0.5f; pos[3][2] = -0.5f;
		pos[4][0] = 0.5f; pos[4][1] = -0.5f; pos[4][2] = 0.5f;
		pos[5][0] = -0.5f; pos[5][1] = -0.5f;  pos[5][2] = 0.5f;
		pos[6][0] = -0.5f; pos[6][1] = 0.5f; pos[6][2] = 0.5f;
		pos[7][0] = 0.5f; pos[7][1] = 0.5f; pos[7][2] = 0.5f;
	}



	int* AddIndexList() {
		static int* p = (int*)malloc(3 * 12 * sizeof(int));

		cout << sizeof(*p) << endl << endl;

		int index_num = 0;
		int index_array_cnt = 0;
		int i = 1;

		p[0] = 0;
		p[1] = 1;
		p[2] = 2;

		p[3] = 0;
		p[4] = 2;
		p[5] = 3;

		p[6] = 4;
		p[7] = 5;
		p[8] = 6;

		p[9] = 4;
		p[10] = 6;
		p[11] = 7;


		p[12] = 1;
		p[13] = 4;
		p[14] = 7;

		p[15] = 1;
		p[16] = 7;
		p[17] = 2;

		p[18] = 5;
		p[19] = 0;
		p[20] = 3;

		p[21] = 5;
		p[22] = 3;
		p[23] = 6;

		p[24] = 2;
		p[25] = 7;
		p[26] = 6;

		p[27] = 2;
		p[28] = 6;
		p[29] = 3;

		p[30] = 0;
		p[31] = 5;
		p[32] = 4;

		p[33] = 0;
		p[34] = 4;
		p[35] = 1;


		return p;
	}
};



class GL_Tetrahedron : public Diagram {


public:

	GLfloat col[4][3];
	GLfloat pos[4][3];
	bool maked[4];
	int start_index;

	GL_Tetrahedron() : Diagram() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				col[i][j] = 0;
				pos[i][j] = 0;
			}

			if (i < 4)
				maked[i] = false;
		}

		start_index = 0;
	}

	void Setcol(MyObjCol col[8]) {
		for (int i = 0; i < 4; i++) {
			this->col[i][0] = col[i].R;
			this->col[i][1] = col[i].G;
			this->col[i][2] = col[i].B;

		}
	}

	void SetPos() {
		pos[0][0] = 0.0f, pos[0][1] = 0.5f, pos[0][2] = 0.0f;
		pos[1][0] = 0.0f, pos[1][1] = 0.0f, pos[1][2] = 0.5f;
		pos[2][0] = 0.5f, pos[2][1] = 0.0f, pos[2][2] = 0.0f;
		pos[3][0] = 0.0f, pos[3][1] = 0.0f, pos[3][2] = -0.5f;

	}


	int* AddIndexList() {
		static int* p = (int*)malloc(3 * 4 * sizeof(int));

		cout << sizeof(*p) << endl << endl;

		p[0] = 0;
		p[1] = 1;
		p[2] = 2;

		p[3] = 0;
		p[4] = 2;
		p[5] = 3;

		p[6] = 0;
		p[7] = 1;
		p[8] = 3;

		p[9] = 1;
		p[10] = 2;
		p[11] = 3;

		return p;
	}

};




class GL_Pyramid : public Diagram{


public:
	GLfloat col[5][3];
	GLfloat pos[5][3];
	bool maked[5];
	int start_index;
	

	GL_Pyramid() : Diagram() {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++) {
				col[i][j] = 0;
				pos[i][j] = 0;
			}

			if (i < 5)
				maked[i] = false;
		}

		start_index = 0;
	}

	void Setcol(MyObjCol col[5]) {
		for (int i = 0; i < 5; i++) {
			this->col[i][0] = col[i].R;
			this->col[i][1] = col[i].G;
			this->col[i][2] = col[i].B;

		}
	}


	void SetPos() {
		pos[0][0] = 0.0f, pos[0][1] = 0.5f, pos[0][2] = 0.0f;
		pos[1][0] = -0.5f, pos[1][1] = -0.5f, pos[1][2] = -0.5f;
		pos[2][0] = 0.5f, pos[2][1] = -0.5f, pos[2][2] = -0.5f;
		pos[3][0] = 0.5f, pos[3][1] = -0.5f, pos[3][2] = 0.5f;
		pos[4][0] = -0.5f, pos[4][1] = -0.5f, pos[4][2] = 0.5f;

	}

	int* AddIndexList() {
		static int* p = (int*)malloc(3 * 6 * sizeof(int));

		cout << sizeof(*p) << endl << endl;

		p[0] = 0;
		p[1] = 1;
		p[2] = 2;

		p[3] = 0;
		p[4] = 2;
		p[5] = 3;

		p[6] = 0;
		p[7] = 3;
		p[8] = 4;

		p[9] = 0;
		p[10] = 4;
		p[11] = 1;

		p[12] = 1;
		p[13] = 2; 
		p[14] = 3;

		p[15] = 1;
		p[16] = 3;
		p[17] = 4;

		return p;
	}

};