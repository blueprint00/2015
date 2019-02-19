/*
음악 입력
- 제목 (곡 명)
- 아티스트
- 앨범 명

MENU
===============================
1. 음악 추가
2. 음악 검색 후 삭제
3. 전체 음악 출력
	>> 곡 명을 사전 순으로 출력
		>> 메인 화면 돌아가기 : 0
4. 아티스트 별
	>> 아티스트 이름별로 사전 순으로 출력
		>>　메인 화면 돌아가기 : 0
5. 앨범 별
	>> 앨범 명으로 사전 순으로 출력
		>>　메인 화면 돌아가기 : 0
6. 랜덤 재생
	>> 저장 된 음악 중 랜덤으로 하나 재생
		>>　메인 화면 돌아가기 : 0
7. 검색
	1. 제목 검색
	2. 아티스트 검색
	3. 앨범 검색
		>>　메인 화면 돌아가기 : 0
0. 종료

*/

#include <stdio.h>
#include <string.h>
#include <windows.h>
struct music{

	char name[50];
	char artist[50];
	char album[50];
	struct music *next;

};
struct music *M = NULL;

struct music *m;

FILE *fp1, *fp2, *fp3;
	
void _malloc(struct music *M, int *cnt);
void add_list(struct music **M, int *cnt);
void delete_list(struct music **M, int *cnt);
void print_name(int cnt);
void print_artist(int cnt);
void print_album(int cnt);
void randomplay(int cnt);
void search(int cnt);

int main(){

	int n, cnt = 0, i, *c;
	struct music *m; //배열 동적할당
	struct music *new_node, *ptr;
	
	fp1 = fopen("input_name.txt", "r");
	fp2 = fopen("input_artist.txt", "r");
	fp3 = fopen("input_album.txt", "r");
	
	// 파일 오류
	if(fp1 == NULL || fp2 == NULL || fp3 == NULL){
		printf("========FILE OPEN ERROR========\n");
		return 0;
	}
	
	c = &cnt;

	while(1){

		//리스트 저장
		new_node = (struct music *) malloc(sizeof(struct music));

		fgets(new_node -> name, 50, fp1); if(feof(fp1) != 0) break;
		fgets(new_node -> artist, 50, fp2); if(feof(fp2) != 0) break;
		fgets(new_node -> album, 50, fp3); if(feof(fp3) != 0) break; // 파일의 끝일 경우 멈춤

		//뒤에 저장된 enter 지우기
		new_node -> name[strlen(new_node -> name) - 1] = '\0';
		new_node -> artist[strlen(new_node -> artist) - 1] = '\0';
		new_node -> album[strlen(new_node -> album) - 1] = '\0';

		new_node -> next = M;
		M = new_node;
		
		cnt++; // 갯수 세기
	
	}

	// 파일에 아무것도 존재하지 않음
		if(cnt == 0) printf("※ 파일이 비어있습니다\n");

	m = (struct music *) malloc(sizeof(struct music) * cnt); // 배열 동적할당
	
	// 리스트를 배열로 다시 저장
	for(ptr = M, i = 0; ptr != NULL, i < cnt; ptr = ptr -> next, i++){
		strcpy(m[i].name, ptr -> name);
		strcpy(m[i].artist, ptr -> artist);
		strcpy(m[i].album, ptr -> album);
	}

	while(1){

		printf("\n\t>> MENU\n");
		printf("----------------------------------------------------\n");
		printf(" 1. 음악 추가\n");
		printf(" 2. 음악 제목 검색 후 삭제\n");
		printf(" 3. 전체 음악 곡 명 별 출력\n");
		printf(" 4. 전체 음악 아티스트 별 정렬\n");
		printf(" 5. 전체 음악 앨범 별 정렬\n");
		printf(" 6. 랜덤 재생\n");
		printf(" 7. 음악 검색\n");
		printf(" 0. 종료\n");
		printf("----------------------------------------------------\n");
		printf(" 입력 >> "); scanf("%d", &n);

		if(n == 0) break; // 종료

		fflush(stdin);
		
		system("cls"); //화면 비우기

		switch(n){

		case 1 : add_list(&M, c); break;
		case 2 : delete_list(&M, c); break;
		case 3 : print_name(cnt); break;
		case 4 : print_artist(cnt); break;
		case 5 : print_album(cnt); break;
		case 6 : randomplay(cnt); break;
		case 7 : search(cnt); break;
		}
	}
	fclose(fp1); fclose(fp2); fclose(fp3);
}