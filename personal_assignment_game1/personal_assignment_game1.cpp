#include<bangtal.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

SceneID mainscene;
ObjectID assignment[4], stress_gauge, lol, sleep, stop, date_image, end;

int stress = 1, task = 0, date = 0, finished_assignment = 0;

bool check_assignment1 = false;
bool check_assignment2 = false;
bool check_assignment3 = false;
bool check_assignment4 = false;

bool ending = false;

void set_stress() {
	if (stress < 0) stress = 0;
	if (stress > 5) stress = 5;
}

void Gameset() {
	if (finished_assignment == 4 && date <= 4) {
		showMessage("축하합니다. 기한 안에 모든 과제를 끝내셨습니다. \n 그렇지만 다음주에는 중간고사가 있네요. \n 파이팅!");
		ending = true;
	}
	else if (date == 5) {
		showMessage("기한 안에 과제를 끝내지 못했습니다. \n 하지만 괜찮습니다. \n 바로 앞에는 중간고사가 있거든요.");
		ending = true;
	}
	else if (stress == 5) {
		showMessage("스트레스 과다로 사망하셨습니다. 가장 현실적인 엔딩이네요.");
		ending = true;
	}
}

void date_set() {
	if (task == 2) {
		task = 0;
		date += 1;
	}
}

void date_image_set() {
	if (date == 1) setObjectImage(date_image, "images\\date_1.png");
	else if (date == 2) setObjectImage(date_image, "images\\date_2.png");
	else if (date == 3) setObjectImage(date_image, "images\\date_3.png");
	else if (date == 4) setObjectImage(date_image, "images\\date_4.png");
	else if (date == 5) setObjectImage(date_image, "images\\date_5.png");
}

void set_stress_image() {
	if (stress == 0) setObjectImage(stress_gauge, "images\\stress_0.png");
	else if (stress == 1) setObjectImage(stress_gauge, "images\\stress_1.png");
	else if(stress == 2) setObjectImage(stress_gauge, "images\\stress_2.png");
	else if (stress == 3) setObjectImage(stress_gauge, "images\\stress_3.png");
	else if (stress == 4) setObjectImage(stress_gauge, "images\\stress_4.png");
	else if (stress == 5) setObjectImage(stress_gauge, "images\\stress_5.png");
} 

ObjectID createObject(const char* name, const char* image, SceneID scene, int x, int y) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	showObject(object);

	return object;
}

void mouseCallBack(ObjectID object, int x, int y, MouseAction action) {
	if (object == assignment[0] && check_assignment1 == false && ending == false) {
		setObjectImage(assignment[0], "images\\1_finished.png");
		stress += 1;
		set_stress_image();
		task += 1;
		finished_assignment += 1;
		date_set();
		date_image_set();
		Gameset();
		set_stress();
		check_assignment1 = true;
	}
	else if (object == assignment[1] && check_assignment2 == false && ending == false) {
		setObjectImage(assignment[1], "images\\2_finished.png");
		stress += 2;
		set_stress_image();
		task += 1;
		finished_assignment += 1;
		date_set();
		date_image_set();
		Gameset();
		set_stress();
		check_assignment2 = true;
	}
	else if (object == assignment[2] && check_assignment3 == false && ending == false) {
		setObjectImage(assignment[2], "images\\3_finished.png");
		stress += 3;
		set_stress_image();
		task += 1;
		finished_assignment += 1;
		date_set();
		date_image_set();
		Gameset();
		set_stress();
		check_assignment3 = true;
	}
	else if (object == assignment[3] && check_assignment4 == false && ending == false) {
		setObjectImage(assignment[3], "images\\4_finished.png");
		stress += 2;
		set_stress_image();
		task += 1;
		finished_assignment += 1;
		date_set();
		date_image_set();
		Gameset();
		set_stress();
		check_assignment4 = true;
	}
	else if (object == lol && ending == false) {
		srand(time(NULL));

		int num = rand() % 2;

		if (num == 0) {
			stress += 1;
			set_stress();
		}
		else {
			stress -= 2;
			set_stress();
		}
		set_stress_image();
		task += 1;
		date_set();
		date_image_set();
		Gameset();
	}
	else if (object == sleep && ending == false) {
		stress -= 1;
		set_stress_image();
		task = 0;
		date += 1;
		date_image_set();
		set_stress();
		Gameset();
	}
	else if (object == stop && ending == false) {
		showMessage("축하합니다. 당신은 낭만과 행복을 찾아 대학교를 떠났습니다. \n 모든 대하생이 부러워 할 것입니다. \n 하지만 몇 년 뒤에는 바뀔지도 모르니 지금 즐기시길 바랍니다.");
	}
	else if (object == end) endGame();
}

int main() {
	setMouseCallback(mouseCallBack);
	mainscene = createScene("mainscene", "images\\background.png");

	assignment[0] = createObject("과제1", "images\\1_unfinished.png", mainscene, 115, 60 + 200*2);
	assignment[1] = createObject("과제2", "images\\2_unfinished.png", mainscene, 115 + 150*2, 60 + 200 * 2);
	assignment[2] = createObject("과제3", "images\\3_unfinished.png", mainscene, 115 + 150*4, 60 + 200 * 2);
	assignment[3] = createObject("과제4", "images\\4_unfinished.png", mainscene, 115 + 150*6, 60 + 200 * 2);
	stress_gauge = createObject("Stress", "images\\stress_1.png", mainscene, 1280-115, 720-61);
	lol = createObject("Lol", "images\\lol.png", mainscene, 115 + 150*1, 60);
	sleep = createObject("Sleep", "images\\sleep.png", mainscene, 115 + 150 * 3, 60);
	stop = createObject("Stop", "images\\stop.png", mainscene, 115+150*5, 60);
	date_image = createObject("Date", "images\\date_0.png", mainscene, 0, 60+200);
	end = createObject("End", "images\\End.png", mainscene, 1280 - 115, 30);

	showMessage("오늘은 4월 13일. 17일까지 과제를 끝내야 해...");
	startGame(mainscene);
}
