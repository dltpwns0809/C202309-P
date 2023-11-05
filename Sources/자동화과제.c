#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include <conio.h>

#define MAX_USER 100
#define MAX_WEBSITE 6
#define MAX_CHAR 15


int LOGIN(int web_number,char DB[][MAX_USER][4],int user_Count[], int log_in[][3], char website_name[]);//����Ʈ �α��� �ý���
void sign_up(int web_number, char DB[][MAX_USER][4], int user_Count[], int log_in[][3], char website_name[]);// ȸ������ �ý���(�� ����Ʈ�� DB �迭�� ���̵�/��� �߰�)
void website_print(char website_name[][MAX_CHAR],int y);//������Ʈ ��� ���
void CursorView();//ȭ�鿡�� �ڵ� ������ �ڵ�
int website_connect(int log_in[][3], char website_name[][MAX_CHAR], int select);

// �α��� �ý��� ex)�б� ����Ʈ
int main()
{
	CursorView();// Ŀ�� ������
	int key, run = 1,select=-1, log_in[MAX_WEBSITE][3] = {0,0,0};//0��-�α��� ���� 1�� �α��� ���� ���(0-����� 1-���) 2��-�α��� ���� ��ȣ
	char DB[MAX_WEBSITE][MAX_USER][4] = {{""},{""},{""},};//�г���,id,pw
	char website_name[MAX_WEBSITE][MAX_CHAR] = {"GOOGLE","NAVER","JNU PORTAL","GITHUB","YOUTUBE","PROGRAMMERS"};//����Ʈ �̸� ���
	int user_Count[MAX_WEBSITE] = {0,0,0,0,0,0};//DB�� �����ϴ� ���� ��
	int cursur_position_y=0;//Ŀ�� ��ġ(����)��
	while (1) {
		Sleep(100);
		system("cls");
		cursur_position_y += scroll_control(MAX_WEBSITE,cursur_position_y);//�� �Ʒ� Ű �Է¹ޱ�(��:-1,�Ʒ�:-1)
		printf("=====������ ����Ʈ ����=====\n");
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


void CursorView()//ȭ�鿡�� Ŀ���� ������ �ڵ�
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
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
	char website_collection[MAX_WEBSITE][8][20] = {//index=0 �� �� �迭�� ���Ե� �� ĭ�� �ƴ� �迭 ����
		{"7","����","NAVER","JNU PORTAL","GITHUB","YOUTUBE","PROGRAMMERS","�� ����/�α���"},
		{"7","���̹�����","NAVER","JNU PORTAL","GITHUB","YOUTUBE","PROGRAMMERS","�� ����/�α���"},
		{"3","���л�����","eŬ����","�� ����/�α���","","",""},
		{"2","Repositories","�� ����/�α���","","","",""},
		{"3","����","����","�� ����/�α���","","",""},
		{"2","�ڵ��׽�Ʈ","�� ����/�α���","","","",""}
	};
	printf("====���ӵ� ����Ʈ : %s====\n", website_name[select - 1]);
	for (int i = 1;i < atoi(website_collection[select-1][0])+1;i++) {
		if (i==atoi(website_collection[select-1][0])) {
			if (log_in[select - 1][0] == 1) {
				printf("(%d) �� ����\n", i );
			}
			else {
				printf("(%d) �α���\n", i );
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
			printf("���� �ִ� ���� �ʰ�(MAX=%d)",MAX_CHAR);
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
			printf("���� �ִ� ���� �ʰ�(MAX=%d)",MAX_CHAR);
		}
		else {
			break;
		}
	}
	printf("==========%s==========\n", website_name[web_number]);
	printf("=======�г��Ӽ���=======\n");
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
			printf("���� �ִ� ���� �ʰ�(MAX=14)");
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
			printf("���� �ִ� ���� �ʰ�(MAX=14)");
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
				printf("====��� �α���(��/�ƴϿ�)====\n");
				scanf_s("%s", &response,(int)sizeof(response));
				if (!strcmp(response, "��")) {
					log_in[web_number][1] = 1;
				}
				else {
					log_in[web_number][1] = 0;
				}
				printf("====================\n");
				printf("===%s�� �α��οϷ�Ǽ̽��ϴ�===\n",DB[i][0]);
				printf("====================\n");
				return 1;
			}
		}
	}
	if (check != 1) {
		printf("=======�α��� ����=======\n");
		return 0;
	}
	return 0;
}
