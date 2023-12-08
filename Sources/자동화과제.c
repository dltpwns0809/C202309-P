#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "key.h"
#include "print_list.h"

#define MAX_USER 100
#define MAX_WEBSITE 6
#define MAX_CHAR 30
#define MAX_WEBSITE_LIST 8

typedef struct Data_Bace {
  char name[MAX_CHAR];
  char user_id[MAX_CHAR];
  char user_pw[MAX_CHAR];
} USER_DB;
int connect_sign_up(int web_number, int connect_web, USER_DB DB[][MAX_USER],
                    int user_Count[], int log_in[][3],
                    char website_name[][MAX_CHAR]);
int LOGIN(int web_number, USER_DB DB[][MAX_USER], int user_Count[],
          int log_in[][3],
          char website_name[][MAX_CHAR]);  // ����Ʈ �α��� �ý���
int sign_up(int web_number, USER_DB DB[][MAX_USER], int user_Count[],
            int log_in[][3],
            char website_name[][MAX_CHAR]);  // ȸ������ �ý���(�� ����Ʈ�� DB
                                             // �迭�� ���̵�/��� �߰�)
void website_print(char website_name[][MAX_CHAR], int y,
                   int list_length);  // ������Ʈ ��� ���
void CursorView();                    // ȭ�鿡�� �ڵ� ������ �ڵ�
int website_connect(int log_in[][3], char website_name[][MAX_CHAR], int select,
                    USER_DB DB[MAX_WEBSITE][MAX_USER], int user_Count[]);
// �α��� �ý��� ex)�б� ����Ʈ

int main() {
  CursorView();  // Ŀ�� ������
  int run = 1, select = -1,
      log_in[MAX_WEBSITE][3] = {
          0, 0, 0};  // 0��-�α��� ���� 1�� �α��� ���� ���(0-�����
                     // 1-���) 2��-�α��� ���� ��ȣ
  /* char DB[MAX_WEBSITE][MAX_USER][4][MAX_CHAR] = {
      {""},
      {""},
      {""},
  };  // �г���,id,pw
  */
  USER_DB DB[MAX_WEBSITE][MAX_USER];
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
    website_print(website_name, cursur_position_y, MAX_WEBSITE);

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

int website_connect(int log_in[][3], char website_name[][MAX_CHAR], int select,
                    USER_DB DB[MAX_WEBSITE][MAX_USER], int user_Count[]) {
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
      if (strcmp(DB[select][i].name, "")) {
        printf("%s %s %s\n", DB[select][i].name, DB[select][i].user_id,
               DB[select][i].user_pw);
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
        int list_checker_2 = -1;
        int list_checker_3 = -1;
        if (log_in[select][0] == 0) {
          int scroll_position = 0;
          char login_button[3][MAX_CHAR] = {"�α���", "ȸ������", "������"};
          while (list_checker == -1) {
            system("cls");
            /* for (int i = 0; i < 3; i++) {
              if (scroll_position == i) {
                printf("> ");
              } else {
                printf("   ");
              }
              printf("(%d) %s\n", i + 1, login_button[i]);
            }*/
            website_print(login_button, scroll_position, 3);
            keyboard_control(&scroll_position, 3, &list_checker);
          }
        }
        if (list_checker == 0) {
          system("cls");
          LOGIN(select, DB, user_Count, log_in, website_name);
        } else if (list_checker == 1) {
          int scroll_position_2 = 0;
          int scroll_position_3 = 0;
          while (list_checker_2 == -1) {
            char sign_up_button[3][MAX_CHAR] = {
                "���� ȸ������", "Ÿ ����Ʈ�� ȸ������", "������"};
            system("cls");
            website_print(sign_up_button, scroll_position_2, 3);
            keyboard_control(&scroll_position_2, 3, &list_checker_2);
          }
          system("cls");
          if (list_checker_2 == 0) {
            sign_up(select, DB, user_Count, log_in, website_name);
          } else if (list_checker_2 == 1) {
            int connected_site[MAX_WEBSITE][4] = {
                {-1, -1, -1, -1}, {0, -1, -1, -1}, {0, 1, -1, -1},
                {0, 1, -1, -1},   {0, 1, -1, -1},  {0, 1, 3, -1}};
            int connected_site_number[MAX_WEBSITE] = {0, 1, 2, 2, 2, 3};
            char site_name_list[4][MAX_CHAR] = {"", "", "", ""};
            for (int i = 0; i < 4; i++) {
              if (connected_site[select][i] != -1)
                strcpy_s(site_name_list[i], MAX_CHAR,
                         website_name[connected_site[select][i]]);
            }
            // scroll_position_2 = 0;
            while (1) {
              system("cls");
              website_print(site_name_list, scroll_position_3,
                            connected_site_number[select]);
              keyboard_control(&scroll_position_3,
                               connected_site_number[select], &list_checker_3);
              if ((list_checker_3 != -1) &&
                  (connected_site_number[select] > 0)) {
                connect_sign_up(select, list_checker_3, DB, user_Count, log_in,
                                website_name);
                break;
              }
              if (connected_site_number[select] == 0) {
                printf("Ÿ ����Ʈ�� �α��� �� �� �����ϴ�.");
                Sleep(2000);
              }
            }
          }
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

int connect_sign_up(int web_number, int connect_web, USER_DB DB[][MAX_USER],
                    int user_Count[], int log_in[][3],
                    char website_name[][MAX_CHAR]) {
  char react[MAX_CHAR];
  if (log_in[connect_web][0] == 0) {
    printf("%s ����Ʈ�� �α��εǾ����� �ʽ��ϴ�.", website_name[connect_web]);
    Sleep(2000);
    return 0;
  } else {
    printf("-----�ش� ����Ʈ �α��� ����-----\n");
    printf("name : %s\n", DB[connect_web][log_in[connect_web][2]].name);
    printf("id : %s\n", DB[connect_web][log_in[connect_web][2]].user_id);
    printf("pw : %s\n", DB[connect_web][log_in[connect_web][2]].user_pw);
    printf("�ش� ������ ȸ�������Ͻðڽ��ϱ�? (yes/no) : \n");
    scanf_s("%s", react, (int)sizeof(react));
    if (!strcmp(react, "yes")) {
      strcpy_s(DB[web_number][user_Count[web_number]].user_id,
               (int)sizeof(DB[web_number][user_Count[web_number]].user_id),
               DB[connect_web][log_in[connect_web][2]].user_id);
      strcpy_s(DB[web_number][user_Count[web_number]].user_pw,
               (int)sizeof(DB[web_number][user_Count[web_number]].user_pw),
               DB[connect_web][log_in[connect_web][2]].user_pw);
      strcpy_s(DB[web_number][user_Count[web_number]].name,
               (int)sizeof(DB[web_number][user_Count[web_number]].name),
               DB[connect_web][log_in[connect_web][2]].name);
      user_Count[web_number] += 1;
    }
  }
}

// ��ȯ�� :0 ȸ������ ���
int sign_up(int web_number, USER_DB DB[][MAX_USER], int user_Count[],
            int log_in[][3], char website_name[][MAX_CHAR]) {
  char check_id[100], check_pw[100], check_name[100];
  int checker = -1;
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
      if (!strcmp(DB[web_number][i].user_id, check_id)) {
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
      if (!strcmp(DB[web_number][i].name, check_name)) {
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
  strcpy_s(DB[web_number][user_Count[web_number]].user_id,
           (int)sizeof(DB[web_number][user_Count[web_number]].user_id),
           check_id);
  strcpy_s(DB[web_number][user_Count[web_number]].user_pw,
           (int)sizeof(DB[web_number][user_Count[web_number]].user_pw),
           check_pw);
  strcpy_s(DB[web_number][user_Count[web_number]].name,
           (int)sizeof(DB[web_number][user_Count[web_number]].name),
           check_name);
  user_Count[web_number] += 1;
}

int LOGIN(int web_number, USER_DB DB[][MAX_USER], int user_Count[],
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
    if ((strcmp(DB[web_number][i].user_id, login_id)) == 0) {
      if ((strcmp(DB[web_number][i].user_pw, login_pw)) == 0) {
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
        printf("===%s�� �α��οϷ�Ǽ̽��ϴ�===\n", DB[web_number][i].name);
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