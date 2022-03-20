#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void message(char* image);
void hide();
void mix(ObjectID obe);
SceneID scene1;
ObjectID origin, start, end, c, j, g, re;
ObjectID piece[16];
int white = 15, fin[15], t;
double o;

char num[16][100];

char temp[100], go[100], Me[100];

clock_t st_clock, end_clock, diff_clock, ex_clock;

void check(void) {
	bool ch = 1;
	for (int z = 0; z < 15; z++) {

		if (fin[z] != z)
		{
			ch = 0;
			break;
		}
	}

	if (ch) {
		end_clock = clock();
		diff_clock = end_clock - st_clock;
		ex_clock = diff_clock / CLOCKS_PER_SEC;
		o = ex_clock;
		sprintf_s(Me, "축하드립니다. %.0f초만큼 걸렸습니다.", o);
		message(Me);
		hide();
		setObjectImage(start, "restart.png");
		showObject(start);
		showObject(end);
		white = 15;
		for (int a = 0; a < 15; a++) {
			sprintf_s(num[a], "%d.png", a);
		}
		strcpy_s(num[15], "white.png");

		for (int a = 0; a < 15; a++) {
			fin[a] = a;
		}
	}
}

//물체정의함수
ObjectID create1(const char* image, SceneID scene, int x, int y) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	showObject(object);

	return object;
}
//이미지변경
void change(ObjectID object, char* image) {
	setObjectImage(object, image);
}

//물체정의지만 show는 포함x한 함수
ObjectID create2(const char* image, SceneID scene, int x, int y) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	return object;
}

//메세지
void message(char* image) {
	showMessage(image);
}


//조각위치바꾸기함수
void mix(ObjectID obe) {
	if (obe == piece[white + 4])
	{
		strcpy_s(temp, num[white]);
		strcpy_s(num[white], num[white + 4]);
		strcpy_s(num[white + 4], temp);

		t = fin[white];
		fin[white] = fin[white + 4];
		fin[white + 4] = t;

		change(piece[white + 4], num[white + 4]);
		change(piece[white], num[white]);
		white += 4;

	}
	else if (obe == piece[white - 4])
	{
		strcpy_s(temp, num[white]);
		strcpy_s(num[white], num[white - 4]);
		strcpy_s(num[white - 4], temp);

		t = fin[white];
		fin[white] = fin[white - 4];
		fin[white - 4] = t;

		change(piece[white - 4], num[white - 4]);
		change(piece[white], num[white]);
		white -= 4;
	}
	else if (obe == piece[white + 1])
	{
		strcpy_s(temp, num[white]);
		strcpy_s(num[white], num[white + 1]);
		strcpy_s(num[white + 1], temp);

		t = fin[white];
		fin[white] = fin[white + 1];
		fin[white + 1] = t;

		change(piece[white + 1], num[white + 1]);
		change(piece[white], num[white]);
		white += 1;
	}
	else if (obe == piece[white - 1])
	{
		strcpy_s(temp, num[white]);
		strcpy_s(num[white], num[white - 1]);
		strcpy_s(num[white - 1], temp);

		t = fin[white];
		fin[white] = fin[white - 1];
		fin[white - 1] = t;

		change(piece[white - 1], num[white - 1]);
		change(piece[white], num[white]);
		white -= 1;
	}
}

//piece show함수
void show() {
	int i = 0;
	for (; i < 16; i++) {
		showObject(piece[i]);
	}
}

//piece hide함수
void hide() {
	int i = 0;
	for (; i < 16; i++) {
		hideObject(piece[i]);
	}
}

//초보
void chobo(void) {
	mix(piece[white - 4]);
	mix(piece[white - 4]);
	mix(piece[white - 1]);
	mix(piece[white - 1]);
	mix(piece[white + 4]);
	mix(piece[white + 4]);

}

//중급
void juong(void) {
	mix(piece[white - 4]);
	mix(piece[white - 4]);
	mix(piece[white - 1]);
	mix(piece[white - 1]);
	mix(piece[white + 4]);
	mix(piece[white + 4]);
	mix(piece[white - 1]);
	mix(piece[white - 4]);
	mix(piece[white + 1]);
	mix(piece[white - 4]);
	mix(piece[white - 4]);
}

//고수

void gosu(void) {
	mix(piece[white - 4]);
	mix(piece[white - 4]);
	mix(piece[white - 4]);
	mix(piece[white - 1]);
	mix(piece[white - 1]);
	mix(piece[white + 4]);
	mix(piece[white + 1]);
	mix(piece[white + 4]);
	mix(piece[white - 1]);
	mix(piece[white - 1]);
	mix(piece[white - 4]);
	mix(piece[white + 1]);
	mix(piece[white + 4]);
	mix(piece[white + 4]);
	mix(piece[white - 1]);
}


//게임시작함수
void starting(void) {
	show();
	setObjectImage(piece[15], "white.png");
}
//마우스콜백함수
void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (object == end) {
		endGame();
	}
	else if (object == start) {
		showObject(c);
		showObject(j);
		showObject(g);
		hideObject(start);
		hideObject(end);

	}
	else if (object == c)
	{
		starting();
		hideObject(c);
		hideObject(j);
		hideObject(g);
		chobo();
		st_clock = clock();
	}
	else if (object == j)
	{
		starting();
		hideObject(c);
		hideObject(j);
		hideObject(g);
		juong();
		st_clock = clock();
	}
	else if (object == g)
	{
		starting();
		hideObject(c);
		hideObject(j);
		hideObject(g);
		gosu();
		st_clock = clock();
	}
	else
	{
		for (int i = 0; i < 15; i++) {
			if (piece[i]) {
				mix(object);

			}
		}
		check();
	}
}

int main() {

	setMouseCallback(mouseCallback);

	scene1 = createScene("퍼즐맞추기", "orIgin.png");

	start = create1("start.png", scene1, 510, 300);
	end = create1("end.png", scene1, 510, 175);

	for (int a = 0; a < 15; a++) {
		sprintf_s(num[a], "%d.png", a);
	}
	strcpy_s(num[15], "white.png");

	for (int a = 0; a < 15; a++) {
		fin[a] = a;
	}

	piece[0] = create2("0.png", scene1, 288, 718 - 177);
	piece[1] = create2("1.png", scene1, 288 + 177 * 1, 718 - 177);
	piece[2] = create2("2.png", scene1, 288 + 177 * 2, 718 - 177);
	piece[3] = create2("3.png", scene1, 288 + 177 * 3, 718 - 177);
	piece[4] = create2("4.png", scene1, 288, 718 - 177 * 2);
	piece[5] = create2("5.png", scene1, 288 + 177 * 1, 718 - 177 * 2);
	piece[6] = create2("6.png", scene1, 288 + 177 * 2, 718 - 177 * 2);
	piece[7] = create2("7.png", scene1, 288 + 177 * 3, 718 - 177 * 2);
	piece[8] = create2("8.png", scene1, 288, 718 - 177 * 3);
	piece[9] = create2("9.png", scene1, 288 + 177 * 1, 718 - 177 * 3);
	piece[10] = create2("10.png", scene1, 288 + 177 * 2, 718 - 177 * 3);
	piece[11] = create2("11.png", scene1, 288 + 177 * 3, 718 - 177 * 3);
	piece[12] = create2("12.png", scene1, 288, 718 - 177 * 4);
	piece[13] = create2("13.png", scene1, 288 + 177 * 1, 718 - 177 * 4);
	piece[14] = create2("14.png", scene1, 288 + 177 * 2, 718 - 177 * 4);
	piece[15] = create2("15.png", scene1, 288 + 177 * 3, 718 - 177 * 4);

	c = create2("cho.png", scene1, 510, 300);
	j = create2("juong.png", scene1, 510, 175);
	g = create2("go.png", scene1, 510, 50);
	startGame(scene1);
}