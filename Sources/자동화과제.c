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
          char website_name[][MAX_CHAR]);  // 사이트 로그인 시스템
int sign_up(int web_number, char DB[][MAX_USER][4][MAX_CHAR], int user_Count[],
            int log_in[][3],
            char website_name[][MAXCHAR]);  // 회원가입 시스템(각 사이트의 DB
                                            // 배열에 아이디/비번 추가)
void website_print(char website_name[][MAX_CHAR], int y);  // 웹사이트 목록 출력
void CursorView();  // 화면에서 코드 가리는 코드
int website_connect(int log_in[][3], char website_name[][MAX_CHAR], int select,
                    char DB[MAX_WEBSITE][MAX_USER][4][MAX_CHAR],
                    int user_Count[]);
// int scroll_control(int max_scroll_number, int now_scroll_number);
void keyboard_control(int* cursur_position_y, int max_scroll_num, int* select);
// 로그인 시스템 ex)학교 사이트

int main() {
  CursorView();  // 커서 가리기
  int run = 1, select = -1,
      log_in[MAX_WEBSITE][3] = {
          0, 0, 0};  // 0번-로그인 상태 1번 로그인 유지 허용(0-불허용
                     // 1-허용) 2번-로그인 유저 번호
  char DB[MAX_WEBSITE][MAX_USER][4][MAX_CHAR] = {
      {""},
      {""},
      {""},
  };  // 닉네임,id,pw
  char website_name[MAX_WEBSITE][MAX_CHAR] = {
      "GOOGLE", "NAVER",   "JNU PORTAL",
      "GITHUB", "YOUTUBE", "PROGRAMMERS"};  // 사이트 이름 목록
  int user_Count[MAX_WEBSITE] = {0};        // DB에 존재하는 유저 수
  int cursur_position_y = 0;
  // 커서 위치(높이)값
  int tester = 0;  // 테스트를 위한 변수 (while문 반복 횟수)
  while (1) {
    system("cls");
    printf("%d", tester);
    printf("=====접속할 사이트 선택=====\n");
    website_print(website_name, cursur_position_y);

    // case 4 : 포인터를 활용
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

void CursorView()  // 화면에서 커서를 가리는 코드
{
  CONSOLE_CURSOR_INFO cursorInfo = {
      0,
  };
  cursorInfo.dwSize = 1;        // 커서 굵기 (1 ~ 100)
  cursorInfo.bVisible = FALSE;  // 커서 Visible TRUE(보임) FALSE(숨김)
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
      // index=0 은 그 배열에 포함된 빈 칸이 아닌 배열 갯수
      {"7", "메일", "NAVER", "JNU PORTAL", "GITHUB", "YOUTUBE", "PROGRAMMERS",
       "내 정보/로그인"},
      {"7", "네이버메일", "GOOGLE", "JNU PORTAL", "GITHUB", "YOUTUBE",
       "PROGRAMMERS", "내 정보/로그인"},
      {"3", "내학사행정", "e클래스", "내 정보/로그인", "", "", ""},
      {"2", "Repositories", "내 정보/로그인", "", "", "", ""},
      {"3", "쇼츠", "뮤직", "내 정보/로그인", "", "", ""},
      {"2", "코딩테스트", "내 정보/로그인", "", "", "", ""}};
  while (1) {
    system("cls");
    printf("====접속된 사이트 : %s====\n", website_name[select]);
    for (int i = 0; i < atoi(website_collection[select][0]) + 1; i++) {
      if (scroll == i) {
        printf("> ");
      } else {
        printf("   ");
      }
      if (i == atoi(website_collection[select][0])) {
        printf("(%d) 나가기\n", i + 1);
        break;
      } else if (i == atoi(website_collection[select][0]) - 1) {
        if (log_in[select][0] == 1) {
          printf("(%d) 내 정보\n", i + 1);
        } else {
          printf("(%d) 로그인\n", i + 1);
        }
      } else {
        printf("(%d) %s\n", i + 1, website_collection[select][i + 1]);
      }
    }
    // db테스트 코드
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
                    website_name[i])) {  // 다른 사이트 접속
          select = i;
          choice = -1;
          scroll = 0;
        }
      }
      if ((choice == atoi(website_collection[select][0]) - 1)) {
        int list_checker = -1;
        if (log_in[select][0] == 0) {
          int scroll_position = 0;
          char login_button[3][MAX_CHAR] = {"로그인", "회원가입", "나가기"};
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
        return 0;  // 나가기 버튼
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

// 반환값 :0 회원가입 취소
int sign_up(int web_number, char DB[][MAX_USER][4][MAX_CHAR], int user_Count[],
            int log_in[][3], char website_name[][MAXCHAR]) {
  char check_id[100], check_pw[100], check_name[100];
  int checker=-1;
  while (1) {
    checker = -1;
    printf("==========%s==========\n", website_name[web_number]);
    printf("=======SIGNUP=======(회원가입 취소:stop)\n");
    printf("=ID=");
    scanf_s("%s", check_id, (int)sizeof(check_id));
    if (!strcmp(check_id, "stop")) {
      return 0;
    }
    printf("===================\n");
    if (strlen(check_id) >= MAX_CHAR) {
      system("cls");
      printf("문자 최대 제한 초과(MAX=%d)\n", MAX_CHAR);
      continue;
    }
    for (int i = 0; i < user_Count[web_number]; i++) {
      if (!strcmp(DB[web_number][i][1], check_id)) {
        system("cls");
        printf("중복된 아이디입니다\n.");
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
    printf("=======SIGNUP=======(회원가입 취소:stop)\n");
    printf("=PW=");
    scanf_s("%s", check_pw, (int)sizeof(check_pw));
    if (!strcmp(check_pw, "stop")) {
      return 0;
    }
    printf("===================\n");
    if (strlen(check_pw) >= MAX_CHAR) {
      printf("문자 최대 제한 초과(MAX=%d)\n", MAX_CHAR);
    } else {
      break;
    }
  }
  while (1) {
    system("cls");
    checker = -1;
    printf("==========%s==========\n", website_name[web_number]);
    printf("=======닉네임설정=======\n");
    printf("=name=");
    scanf_s("%s", check_name, (int)sizeof(check_name));
    for (int i = 0; i < user_Count[web_number]; i++) {
      if (!strcmp(DB[web_number][i][0], check_name)) {
        printf("중복된 닉네임입니다\n.");
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
      printf("문자 최대 제한 초과(MAX=14)");
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
      printf("문자 최대 제한 초과(MAX=14)");
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
        printf("====상시 로그인(예/아니요)====\n");
        scanf_s("%s", response, (int)sizeof(response));
        if (strcmp(response, "예") == 0) {
          log_in[web_number][1] = 1;
        } else {
          log_in[web_number][1] = 0;
        }
        printf("====================\n");
        printf("===%s님 로그인완료되셨습니다===\n", DB[i][0]);
        printf("====================\n");
        return 1;
      }
    }
  }
  if (check != 1) {
    printf("=======로그인 실패=======\n");
    return 0;
  }
}