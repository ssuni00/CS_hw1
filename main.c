/*
Programming Studio C003
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findRoom(int persons[5]); // 5개의 호실 중 빈 베드가 있는 방을 찾아낸다. (리턴값 1~5)
void printReport(char mn[10][20], int mr[10], int mc, char wn[10][20], int wr[10], int wc); // 배정 결과를 출력한다.

int main(){
	char mnames[10][20]; // 남학생명단(최대 10명)
	int mroom[10];		// 남학생명단별 호실 배정 목록
	char wnames[10][20]; // 여학생명단(최대 10명)
	int wroom[10];		// 여학생명단별 호실 배정 목록
	int person[2][5]={0};   // 2개 층별 5개 호실의 배정 인원 수 
	int mcount=0, wcount=0; // 인원 합계 (남, 여)
	int menu;

	srand(time(0));
	printf("===========================================\n");
	printf("생활관 호실 배정 프로그램\n");
	printf("===========================================\n");
	while(1){
		printf("메뉴 : 1.남학생 등록 2.여학생 등록 0.종료 > ");
		scanf("%d", &menu);
		if(menu==0) break;
		else if(menu==1) {
			if(mcount>=10) {
				printf("정원 초과입니다. 등록불가!\n");
				continue;
			}
			printf("학생 이름은? > ");
			scanf("%s", mnames[mcount]);
			int roomno = findRoom(person[0]);
			mroom[mcount] = 100+roomno;
			printf("%s 학생 %d호실 배정되었습니다.\n", mnames[mcount], mroom[mcount]);
			mcount++;
		}
		else if(menu==2) {
			if(wcount>=10) {
				printf("정원 초과입니다. 등록불가!\n");
				continue;
			}
			printf("학생 이름은? > ");
			scanf("%s", wnames[wcount]);
			int roomno = findRoom(person[1]);
			wroom[wcount] = 200+roomno;
			printf("%s 학생 %d호실 배정되었습니다.\n", wnames[wcount], wroom[wcount]);
			wcount++;
		}
	}

	printf("===========================================\n");
	printf("생활관 호실 배정 결과는 다음과 같습니다.\n");
	printf("===========================================\n");
	printReport(mnames, mroom, mcount, wnames, wroom, wcount);

	return 0;
}

int findRoom(int persons[5]){
	// 배정가능한 방, 방에 있는 사람 count 변수
    int available_room[5], count = 0;
	
	// 방은 5개까지, 사람이 2명 이하면 늘리기
    for (int i = 0; i < 5; i++) {
        if (persons[i] < 2) {
            available_room[count++] = i + 1;
        }
    }
	// 방 숫자 return해야하는데 1~5를 랜덤으로 내야하기 때문에 % 써줌
    return available_room[rand() % count];
}

void printReport(char mn[10][20], int mr[10], int mc, char wn[10][20], int wr[10], int wc){
	// 남학생 명단 출력
    printf("남학생 명단 (%d)명\n", mc);
	for(int i = 0; i < mc; i++){
		printf("%d. %s [%d호] \n", i+1, mn[i], mr[i]);
	}
	// 여학생 명단 출력
    printf("\n여학생 명단 (%d)명\n", wc);
	for(int i = 0; i < wc; i++){
		printf("%d. %s [%d호] \n", i+1, wn[i], wr[i]);
	}
	// 호실별 배정 명단 출력
	printf("\n 호실별 배정 명단\n"); 
	for (int i = 1; i <= 5; i++) {  // 101호 ~ 105호 
		printf("%d : ", 100 + i);   
		for (int j = 0; j < mc; j++) {  // 모든 학생 확인
			if (mr[j] == 100 + i) {  // 이 학생이 현재 방에 배정됐는지?
				printf("%s ", mn[j]);  // 그 학생의 이름 출력
			}
		}
        printf("\n");
    }

	// 여자도 동일
    for (int i = 1; i <= 5; i++) {
        printf("%d호 : ", 200 + i);
        for (int j = 0; j < wc; j++) {
            if (wr[j] == 200 + i) {
                printf("%s ", wn[j]);
            }
        }
        printf("\n");
    }
}
