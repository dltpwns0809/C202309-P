#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include <conio.h>

#define MAX_USER 100
#define MAX_WEBSITE 6
#define MAX_CHAR 15


int LOGIN(int web_number,char DB[][MAX_USER][4],int user_Count[], int log_in[][3], char website_name[]);//사이트 로그인 시스템
void sign_up(int web_number, char DB[][MAX_USER][4], int user_Count[], int log_in[][3], char website_name[]);// 회원가입 시스템(각 사이트의 DB 배열에 아이디/비번 추가)
void website_print(char website_name[][MAX_CHAR],int y);//웹사이트 목록 출력
void CursorView();//화면에서 코드 가리는 코드
int website_connect(int log_in[][3], char website_name[][MAX_CHAR], int select);

// 로그인 시스템 ex)학교 사이트
int main()
{
	CursorView();// 커서 가리기
	int key, run = 1,select=-1, log_in[MAX_WEBSITE][3] = {0,0,0};//0번-로그인 상태 1번 로그인 유지 허용(0-불허용 1-허용) 2번-로그인 유저 번호
	char DB[MAX_WEBSITE][MAX_USER][4] = {{""},{""},{""},};//닉네임,id,pw
	char website_name[MAX_WEBSITE][MAX_CHAR] = {"GOOGLE","NAVER","JNU PORTAL","GITHUB","YOUTUBE","PROGRAMMERS"};//사이트 이름 목록
	int user_Count[MAX_WEBSITE] = {0,0,0,0,0,0};//DB에 존재하는 유저 수
	int cursur_position_y=0;//커서 위치(높이)값
	while (1) {
		Sleep(100);
		system("cls");
		cursur_position_y += scroll_control(MAX_WEBSITE,cursur_position_y);//위 아래 키 입력받기(위:-1,아래:-1)
		printf("=====접속할 사이트 선택=====\n");
		if (_kbhit()) {
			key = _getch();
			if (key == 13) {
				select=cursur_position_y;
			}
		}
		website_print(website_name,cursur_position_y);
		printf("%d\n",select);
		if (select != -1) {
			website_connect(log_in, website_name, select);
		}
	}
}


void CursorView()//화면에서 커서를 가리는 코드
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int scroll_control(int max_scroll_number,int now_scroll_number) {
	int key;
	if (_kbhit()) {
		key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72:
				if (now_scroll_number > 0) {
					return -1;
				}
				break;
			case 80:
				if (now_scroll_number < max_scroll_number-1) {
					return 1;
				}
			}
		}
	}
	return 0;
}

int website_connect(int log_in[][3], char website_name[][MAX_CHAR], int select) {
	//int choice;
	char website_collection[MAX_WEBSITE][8][20] = {//index=0 은 그 배열에 포함된 빈 칸이 아닌 배열 갯수
		{"7","메일","NAVER","JNU PORTAL","GITHUB","YOUTUBE","PROGRAMMERS","내 정보/로그인"},
		{"7","네이버메일","NAVER","JNU PORTAL","GITHUB","YOUTUBE","PROGRAMMERS","내 정보/로그인"},
		{"3","내학사행정","e클래스","내 정보/로그인","","",""},
		{"2","Repositories","내 정보/로그인","","","",""},
		{"3","쇼츠","뮤직","내 정보/로그인","","",""},
		{"2","코딩테스트","내 정보/로그인","","","",""}
	};
	printf("====접속된 사이트 : %s====\n", website_name[select - 1]);
	for (int i = 1;i < atoi(website_collection[select-1][0])+1;i++) {
		if (i==atoi(website_collection[select-1][0])) {
			if (log_in[select - 1][0] == 1) {
				printf("(%d) 내 정보\n", i );
			}
			else {
				printf("(%d) 로그인\n", i );
			}
			break;
		}
		else {
			printf("(%d) %s\n", i, website_collection[select - 1][i]);
		}
	}
}

void website_print(char website_name[][MAX_CHAR],int y) {

	for (int i = 0;i < MAX_WEBSITE;i++) {
		if (y == i) {
			printf("> ");
		}
		else {
			printf("   ");
		}
		printf("(%d) %s\n", i + 1, website_name[i]);
	}
}


void sign_up(int web_number, char DB[][MAX_USER][4], int user_Count[], int log_in[][3], char website_name[]) {
	char check_id[MAX_CHAR], check_pw[MAX_CHAR],check_name[MAX_CHAR];
	while (1) {
		printf("==========%s==========\n", website_name[web_number]);
		printf("=======SIGNUP=======\n");
		printf("=ID=");
		scanf_s("%s", check_id, (int)sizeof(check_id));
		printf("===================\n");
		if (strlen(check_id) >= MAX_CHAR) {
			printf("문자 최대 제한 초과(MAX=%d)",MAX_CHAR);
		}
		else {
			break;
		}
	}
	char ch = getchar();
	while (1) {
		printf("==========%s==========\n", website_name[web_number]);
		printf("=======SIGNUP=======\n");
		printf("=PW=");
		scanf_s("%s", check_pw, (int)sizeof(check_pw));
		printf("===================\n");
		if (strlen(check_pw) >= MAX_CHAR) {
			printf("문자 최대 제한 초과(MAX=%d)",MAX_CHAR);
		}
		else {
			break;
		}
	}
	printf("==========%s==========\n", website_name[web_number]);
	printf("=======닉네임설정=======\n");
	printf("=name=");
	scanf_s("%s",check_name,(int)sizeof(check_name));
}

int LOGIN(int web_number,char DB[][MAX_USER][4], int user_Count[], int log_in[][3], char website_name[]) {
	char login_id[MAX_CHAR], login_pw[MAX_CHAR];
	char ch, response;
	int check=-1;
	while (1) {
		printf("==========%s==========\n", website_name[web_number]);
		printf("=======LOGIN=======\n");
		printf("=ID=");
		scanf_s("%s", login_id, (int)sizeof(login_id));
		printf("===================\n");
		if (strlen(login_id) >= MAX_CHAR) {
			printf("문자 최대 제한 초과(MAX=14)");
		}
		else {
			break;
		}
	}
	ch = getchar();
	while (1) {
		printf("==========%s==========\n", website_name[web_number]);
		printf("=======LOGIN=======\n");
		printf("=PW=");
		scanf_s("%s", login_pw, (int)sizeof(login_pw));
		printf("===================\n");
		if (strlen(login_pw) >= MAX_CHAR) {
			printf("문자 최대 제한 초과(MAX=14)");
		}
		else {
			break;
		}
	}
	for (int i = 0;i < *user_Count; i++) {
		if ((strcmp(DB[web_number][i][1], login_id))==0) {
			if ((strcmp(DB[web_number][i][2],login_pw))==0) {
				log_in[web_number][0] = 1;
				log_in[web_number][2] = i;
				check = 1;
				printf("====================\n");
				printf("====상시 로그인(예/아니요)====\n");
				scanf_s("%s", &response,(int)sizeof(response));
				if (!strcmp(response, "예")) {
					log_in[web_number][1] = 1;
				}
				else {
					log_in[web_number][1] = 0;
				}
				printf("====================\n");
				printf("===%s님 로그인완료되셨습니다===\n",DB[i][0]);
				printf("====================\n");
				return 1;
			}
		}
	}
	if (check != 1) {
		printf("=======로그인 실패=======\n");
		return 0;
	}
	return 0;
}
