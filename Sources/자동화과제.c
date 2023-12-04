#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_USER 100
#define MAX_WEBSITE 6
#define MAX_CHAR 15
#define MAX_WEBSITE_LIST 8

typedef struct Data_Bace {
  char name[MAX_CHAR];
  char user_id[MAX_CHAR];
  char user_pw[MAX_CHAR];
}DB;

int LOGIN(int web_number, char DB[][MAX_USER][4][MAX_CHAR], int user_Count[],
          int log_in[][3],
          char website_name[][MAX_CHAR]);  // ����Ʈ �α��� �ý���
int sign_up(int web_number, char DB[][MAX_USER][4][MAX_CHAR], int user_Count[],
            int log_in[][3],
            char website_name[][MAXCHAR]);  // ȸ������ �ý���(�� ����Ʈ�� DB
                                            // �迭�� ���̵�/��� �߰�)
void website_print(char website_name[][MAX_CHAR], int y);  // ������Ʈ ��� ���
void CursorView();  // ȭ�鿡�� �ڵ� ������ �ڵ�
int website_connect(int log_in[][3], char website_name[][MAX_CHAR], int select,
                    char DB[MAX_WEBSITE][MAX_USER][4][MAX_CHAR],
                    int user_Count[]);
// int scroll_control(int max_scroll_number, int now_scroll_number);
void keyboard_control(int* cursur_position_y, int max_scroll_num, int* select);
// �α��� �ý��� ex)�б� ����Ʈ

int main() {
  CursorView();  // Ŀ�� ������
  int run = 1, select = -1,
      log_in[MAX_WEBSITE][3] = {
          0, 0, 0};  // 0��-�α��� ���� 1�� �α��� ���� ���(0-�����
                     // 1-���) 2��-�α��� ���� ��ȣ
  char DB[MAX_WEBSITE][MAX_USER][4][MAX_CHAR] = {
      {""},
      {""},
      {""},
  };  // �г���,id,pw
  char website_name[MAX_WEBSITE][MAX_CHAR] = {
      "GOOGLE", "NAVER",   "JNU PORTAL",
      "GITHUB", "YOUTUBE", "PROGRAMMERS"};  // ����Ʈ �̸� ���
  int user_Count[MAX_WEBSITE] = {0};        // DB�� �����ϴ� ���� ��
  int cursur_position_y = 0;
  // Ŀ�� ��ġ(����)��
  int tester = 0;  // �׽�Ʈ�� ���� ���� (while�� �ݺ� Ƚ��)
  while (1) {
    system("cls");
    printf("%d", tester);
    printf("=====������ ����Ʈ ����=====\n");
    website_print(website_name, cursur_position_y);

    // case 4 : �����͸� Ȱ��
    keyboard_control(&cursur_position_y, MAX_WEBSITE, &select);

    printf("%d\n", select);
    if (select != -1) {
      system("cls");
      website_connect(log_in, website_name, select, DB, user_Count);
      select = -1;
    }

    tester += 1;
  }
}

void CursorView()  // ȭ�鿡�� Ŀ���� ������ �ڵ�
{
  CONSOLE_CURSOR_INFO cursorInfo = {
      0,
  };
  cursorInfo.dwSize = 1;        // Ŀ�� ���� (1 ~ 100)
  cursorInfo.bVisible = FALSE;  // Ŀ�� Visible TRUE(����) FALSE(����)
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void keyboard_control(int* cursur_position_y, int max_scroll_num, int* select) {
  int key;
  key = _getch();
  if (key == 224) {
    key = _getch();
    switch (key) {
      case 72:
        if (*cursur_position_y > 0) {
          *cursur_position_y -= 1;
        }
        break;
      case 80:
        if (*cursur_position_y < max_scroll_num - 1) {
          *cursur_position_y += 1;
        }
    }
  } else if (key == 13) {
    *select = *cursur_position_y;
  }
}

int website_connect(int log_in[][3], char website_name[][MAX_CHAR], int select,
                    char DB[MAX_WEBSITE][MAX_USER][4][MAX_CHAR],
                    int user_Count[]) {
  int choice = -1, scroll = 0;
  char website_collection[MAX_WEBSITE][MAX_WEBSITE_LIST][100] = {
      // index=0 �� �� �迭�� ���Ե� �� ĭ�� �ƴ� �迭 ����
      {"7", "����", "NAVER", "JNU PORTAL", "GITHUB", "YOUTUBE", "PROGRAMMERS",
       "�� ����/�α���"},
      {"7", "���̹�����", "GOOGLE", "JNU PORTAL", "GITHUB", "YOUTUBE",
       "PROGRAMMERS", "�� ����/�α���"},
      {"3", "���л�����", "eŬ����", "�� ����/�α���", "", "", ""},
      {"2", "Repositories", "�� ����/�α���", "", "", "", ""},
      {"3", "����", "����", "�� ����/�α���", "", "", ""},
      {"2", "�ڵ��׽�Ʈ", "�� ����/�α���", "", "", "", ""}};
  while (1) {
    system("cls");
    printf("====���ӵ� ����Ʈ : %s====\n", website_name[select]);
    for (int i = 0; i < atoi(website_collection[select][0]) + 1; i++) {
      if (scroll == i) {
        printf("> ");
      } else {
        printf("   ");
      }
      if (i == atoi(website_collection[select][0])) {
        printf("(%d) ������\n", i + 1);
        break;
      } else if (i == atoi(website_collection[select][0]) - 1) {
        if (log_in[select][0] == 1) {
          printf("(%d) �� ����\n", i + 1);
        } else {
          printf("(%d) �α���\n", i + 1);
        }
      } else {
        printf("(%d) %s\n", i + 1, website_collection[select][i + 1]);
      }
    }
    // db�׽�Ʈ �ڵ�
    for (int i = 0; i < user_Count[select]; i++) {
      if (strcmp(DB[select][i][0], "")) {
        printf("%s %s %s\n", DB[select][i][0], DB[select][i][1],
               DB[select][i][2]);
      }
    }
    //
    printf("%d %d\n", choice, select);
    keyboard_control(&scroll, atoi(website_collection[select][0]) + 1, &choice);
    if (choice != -1) {
      for (int i = 0; i < MAX_WEBSITE; i++) {
        if (!strcmp(website_collection[select][choice + 1],
                    website_name[i])) {  // �ٸ� ����Ʈ ����
          select = i;
          choice = -1;
          scroll = 0;
        }
      }
      if ((choice == atoi(website_collection[select][0]) - 1)) {
        int list_checker = -1;
        if (log_in[select][0] == 0) {
          int scroll_position = 0;
          char login_button[3][MAX_CHAR] = {"�α���", "ȸ������", "������"};
          while (list_checker == -1) {
            system("cls");
            for (int i = 0; i < 3; i++) {
              if (scroll_position == i) {
                printf("> ");
              } else {
                printf("   ");
              }
              printf("(%d) %s\n", i + 1, login_button[i]);
            }
            int key;
            key = _getch();
            if (key == 224) {
              key = _getch();
              switch (key) {
                case 72:
                  if (scroll_position > 0) {
                    scroll_position -= 1;
                  }
                  break;
                case 80:
                  if (scroll_position < 2) {
                    scroll_position += 1;
                  }
              }
            } else if (key == 13) {
              list_checker = scroll_position;
            }
          }
        }
        if (list_checker == 0) {
          system("cls");
          LOGIN(select, DB, user_Count, log_in, website_name);
        } else if (list_checker == 1) {
          system("cls");
          sign_up(select, DB, user_Count, log_in, website_name);
        }
        list_checker = -1;
        choice = -1;
      } else if (choice == atoi(website_collection[select][0])) {
        if (!log_in[select][1]) {
          log_in[select][0] = 0;
          log_in[select][2] = 0;
        }
        return 0;  // ������ ��ư
      }
    }
  }
}

void website_print(char website_name[][MAX_CHAR], int y) {
  for (int i = 0; i < MAX_WEBSITE; i++) {
    if (y == i) {
      printf("> ");
    } else {
      printf("   ");
    }
    printf("(%d) %s\n", i + 1, website_name[i]);
  }
}

// ��ȯ�� :0 ȸ������ ���
int sign_up(int web_number, char DB[][MAX_USER][4][MAX_CHAR], int user_Count[],
            int log_in[][3], char website_name[][MAXCHAR]) {
  char check_id[100], check_pw[100], check_name[100];
  int checker=-1;
  while (1) {
    checker = -1;
    printf("==========%s==========\n", website_name[web_number]);
    printf("=======SIGNUP=======(ȸ������ ���:stop)\n");
    printf("=ID=");
    scanf_s("%s", check_id, (int)sizeof(check_id));
    if (!strcmp(check_id, "stop")) {
      return 0;
    }
    printf("===================\n");
    if (strlen(check_id) >= MAX_CHAR) {
      system("cls");
      printf("���� �ִ� ���� �ʰ�(MAX=%d)\n", MAX_CHAR);
      continue;
    }
    for (int i = 0; i < user_Count[web_number]; i++) {
      if (!strcmp(DB[web_number][i][1], check_id)) {
        system("cls");
        printf("�ߺ��� ���̵��Դϴ�\n.");
        checker = 1;
        break;
      }
    }
    if (checker == 1)
      continue;
    else
      break;
    system("cls");
  }
  char ch = getchar();
  while (1) {
    system("cls");
    printf("==========%s==========\n", website_name[web_number]);
    printf("=======SIGNUP=======(ȸ������ ���:stop)\n");
    printf("=PW=");
    scanf_s("%s", check_pw, (int)sizeof(check_pw));
    if (!strcmp(check_pw, "stop")) {
      return 0;
    }
    printf("===================\n");
    if (strlen(check_pw) >= MAX_CHAR) {
      printf("���� �ִ� ���� �ʰ�(MAX=%d)\n", MAX_CHAR);
    } else {
      break;
    }
  }
  while (1) {
    system("cls");
    checker = -1;
    printf("==========%s==========\n", website_name[web_number]);
    printf("=======�г��Ӽ���=======\n");
    printf("=name=");
    scanf_s("%s", check_name, (int)sizeof(check_name));
    for (int i = 0; i < user_Count[web_number]; i++) {
      if (!strcmp(DB[web_number][i][0], check_name)) {
        printf("�ߺ��� �г����Դϴ�\n.");
        printf("1");
        checker = 1;
        break;
      }
    }
    if (checker == 1)
      continue;
    else
      break;
  }
  strcpy_s(DB[web_number][user_Count[web_number]][1],
         (int)sizeof(DB[web_number][user_Count[web_number]][1]),check_id);
  strcpy_s(DB[web_number][user_Count[web_number]][2],
         (int)sizeof(DB[web_number][user_Count[web_number]][2]), check_pw);
  strcpy_s(DB[web_number][user_Count[web_number]][0],
         (int)sizeof(DB[web_number][user_Count[web_number]][0]), check_name);
  user_Count[web_number] += 1;
}



int LOGIN(int web_number, char DB[][MAX_USER][4][MAX_CHAR], int user_Count[],
          int log_in[][3], char website_name[][MAX_CHAR]) {
  char login_id[MAX_CHAR], login_pw[MAX_CHAR];
  char ch, response[MAXCHAR];
  int check = -1;
  while (1) {
    system("cls");
    printf("==========%s==========\n", website_name[web_number]);
    printf("=======LOGIN=======\n");
    printf("=ID=");
    scanf_s("%s", login_id, (int)sizeof(login_id));
    printf("===================\n");
    if (strlen(login_id) >= MAX_CHAR) {
      printf("���� �ִ� ���� �ʰ�(MAX=14)");
    } else {
      break;
    }
  }
  ch = getchar();
  while (1) {
    system("cls");
    printf("==========%s==========\n", website_name[web_number]);
    printf("=======LOGIN=======\n");
    printf("=PW=");
    scanf_s("%s", login_pw, (int)sizeof(login_pw));
    printf("===================\n");
    if (strlen(login_pw) >= MAX_CHAR) {
      printf("���� �ִ� ���� �ʰ�(MAX=14)");
    } else {
      break;
    }
  }
  system("cls");
  for (int i = 0; i < *user_Count; i++) {
    if ((strcmp(DB[web_number][i][1], login_id)) == 0) {
      if ((strcmp(DB[web_number][i][2], login_pw)) == 0) {
        log_in[web_number][0] = 1;
        log_in[web_number][2] = i;
        check = 1;
        printf("====================\n");
        printf("====��� �α���(��/�ƴϿ�)====\n");
        scanf_s("%s", response, (int)sizeof(response));
        if (strcmp(response, "��") == 0) {
          log_in[web_number][1] = 1;
        } else {
          log_in[web_number][1] = 0;
        }
        printf("====================\n");
        printf("===%s�� �α��οϷ�Ǽ̽��ϴ�===\n", DB[i][0]);
        printf("====================\n");
        return 1;
      }
    }
  }
  if (check != 1) {
    printf("=======�α��� ����=======\n");
    return 0;
  }
}