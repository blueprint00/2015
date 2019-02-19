/*

음악 입력
- 제목 (곡 명)
- 아티스트
- 앨범 명

MENU
====================================
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
#include <time.h>
#include <windows.h>
struct music{

	char name[50];
	char artist[50];
	char album[50];
	struct music *next;

};

FILE *fp1, *fp2, *fp3;

struct music *m;

// 리스트를 배열로 저장
void _malloc(struct music *M, int *cnt){

	struct music *ptr;
	int i;

	m = (struct music *) malloc(sizeof(struct music) * (*cnt)); // 배열 동적할당

	// 리스트를 배열로 다시 저장
	for(ptr = M, i = 0; ptr != NULL, i < (*cnt) ; ptr = ptr -> next, i++){
		strcpy(m[i].name, ptr -> name);
		strcpy(m[i].artist, ptr -> artist);
		strcpy(m[i].album, ptr -> album);
	}

}

// 1번 배열 & 리스트 추가
void add_list(struct music **M, int *cnt){

	struct music *node, *ptr;
	int n;

	fp1 = fopen("input_name.txt", "w");
	fp2 = fopen("input_artist.txt", "w");
	fp3 = fopen("input_album.txt", "w");

	node = (struct music *) malloc(sizeof(struct music));

	printf("\t음악 추가\n");
	printf("----------------------------------------------------\n");
	printf(" 곡 명 >> "); gets(node -> name); 
	printf(" 아티스트 >> "); gets(node -> artist);
	printf(" 앨범 >> "); gets(node -> album);

	(*cnt)++;

	//리스트 처음에 추가
	node -> next = *M;
	*M = node;

	// 추가된 정보까지 파일에 새로 저장
	for(ptr = *M; ptr != NULL; ptr = ptr -> next){
		fprintf(fp1, "%s\n", ptr -> name);
		fprintf(fp2, "%s\n", ptr -> artist);
		fprintf(fp3, "%s\n", ptr -> album);
	}

	_malloc(*M, cnt); // 배열로 옮겨주기
	
	printf("\t\t\t\t\t메인으로 돌아가기 (0) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}

	fclose(fp1); fclose(fp2); fclose(fp3);

}

// 2. 음악 삭제. 리스트에서 삭제 후 배열 재저장
void delete_list(struct music **M, int *cnt){ 

	struct music *prev, *cur, *ptr;
	char name[50];
	int n;

	fp1 = fopen("input_name.txt", "w");
	fp2 = fopen("input_artist.txt", "w");
	fp3 = fopen("input_album.txt", "w");

	printf("\t목록\n");
	printf("----------------------------------------------------\n");
	for(ptr = *M; ptr != NULL; ptr = ptr -> next) printf("   %s\n", ptr -> name);
	printf("----------------------------------------------------\n");

	printf("삭제할 음악 제목 입력 >> "); gets(name);

	for(prev = NULL, cur = *M; cur != NULL; prev = cur, cur = cur -> next){
		if(strcmp(cur -> name, name) == 0){
			if(prev == NULL){ // 첫번째 노드에 있을때
				*M = cur -> next;
				free(cur);
				(*cnt)--;
				printf(" ** 삭제 완료 **\n");
				break;
			}

			else{ // 중간 노드에 존재할 때
				prev -> next = cur -> next;
				free(cur);
				(*cnt)--;				
				printf(" ** 삭제 완료 **\n");
				break;
			}
		}
	}
	// 존재하지 않음
	if(cur == NULL) printf("** %s인 노래는 존재하지 않습니다. **\n", name);

	//삭제 후 파일에 다시 저장
	for(ptr = *M; ptr != NULL; ptr = ptr -> next){
		fprintf(fp1, "%s\n", ptr -> name);
		fprintf(fp2, "%s\n", ptr -> artist);
		fprintf(fp3, "%s\n", ptr -> album);
	}

	_malloc(*M, cnt); // 배열로 옮겨주기

	printf("\t\t\t\t\t메인으로 돌아가기 (0) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}

	fclose(fp1); fclose(fp2); fclose(fp3);

}

// 3. 전체 음악 곡명별로 정렬
void print_name(int cnt){
	
	int n, i, repeat;
	struct music temp;

	for(repeat = 1; repeat < cnt; repeat++){
		for(i = 0; i < cnt - repeat; i ++){
			if(strcmp(m[i].name, m[i+1].name) > 0){
				temp = m[i];
				m[i] = m[i+1];
				m[i+1] = temp;
			}
		}
	}

	printf("\t곡 명 별 정렬\n");
	printf("----------------------------------------------------\n");

	for(i = 0; i < cnt; i++){
		printf(" 곡 명 >> %s\n", m[i].name);
		printf(" 아티스트 >> %s\n", m[i].artist);
		printf(" 앨범 >> %s\n", m[i].album);
		printf("----------------------------------------------------\n");
	}


	printf("\t\t\t\t\t메인으로 돌아가기 (0) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}

}

// 4. 전체 음악 아티스트 별로 정렬
void print_artist(int cnt){ 
	
	int n, i, repeat;
	struct music temp;

	for(repeat = 1; repeat < cnt; repeat++){
		for(i = 0; i < cnt - repeat; i ++){
			if(strcmp(m[i].artist, m[i+1].artist) > 0){
				temp = m[i];
				m[i] = m[i+1];
				m[i+1] = temp;
			}
		}
	}
	
	printf("\t아티스트 별 정렬\n");
	printf("----------------------------------------------------\n");

	for(i = 0; i < cnt; i++){
		printf(" 아티스트 >> %s\n", m[i].artist);
		printf(" 곡 명 >> %s\n", m[i].name);
		printf(" 앨범 >> %s\n", m[i].album);
		printf("----------------------------------------------------\n");
	}


	printf("\t\t\t\t\t메인으로 돌아가기 (0) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}

}

// 5. 전체 음악 앨범명 별로 정렬
void print_album(int cnt){ 

	int n, i, repeat;
	struct music temp;

	for(repeat = 1; repeat < cnt; repeat++){
		for(i = 0; i < cnt - repeat; i ++){
			if(strcmp(m[i].album, m[i+1].album) > 0){
				temp = m[i];
				m[i] = m[i+1];
				m[i+1] = temp;
			}
		}
	}
	
	printf("\t앨범 별 정렬\n");
	printf("----------------------------------------------------\n");

	for(i = 0; i < cnt; i++){
		printf(" 앨범 >> %s\n", m[i].album);
		printf(" 곡 명 >> %s\n", m[i].name);
		printf(" 아티스트 >> %s\n", m[i].artist);
		printf("----------------------------------------------------\n");
	}

	printf("\t\t\t\t\t메인으로 돌아가기 (0) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}

}
// 6. 랜덤 재생
void randomplay(int cnt){

	int n, x;

	srand(time(NULL));

	x = rand() % cnt; // 0 부터 (cnt - 1) 까지

	printf("\t랜덤 재생\n");
	printf("----------------------------------------------------\n");
	printf("    제목      :  %s\n", m[x].name);
	printf("    아티스트  :  %s\n", m[x].artist);
	printf("    앨범      :  %s\n", m[x].album);
	

	printf("\t\t\t\t\t메인으로 돌아가기 (0) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}

}

// 7. 음악 검색

void search_name(int cnt);
void search_artist(int cnt);
void search_album(int cnt);

void search(int cnt){ 

	int n;

	printf("\t음악검색\n");
	printf("----------------------------------------------------\n");
	printf(" 1. 제목 검색\n");
	printf(" 2. 아티스트 검색\n");
	printf(" 3. 앨범 검색\n\n");
	printf(" 0. 메인으로 돌아가기\n");
	printf("----------------------------------------------------\n");
	printf(" 입력 >> "); scanf("%d", &n);

	fflush(stdin);

	if(n == 0){
		system("cls");
		return;
	}

	switch(n){
	case 1 : search_name(cnt); break;
	case 2 : search_artist(cnt); break;
	case 3 : search_album(cnt); break;
	default :{
		printf("잘못 된 입력입니다\n");
		system("pause"); system("cls");
		search(cnt);//보기 제외한 다른 번호 입력시 다시 7번으로 돌아감
		break;
			 }
	}

}

// 7 - 1 .제목 검색
void search_name(int cnt){ 

	int n, i, cnt1 = 0;
	char name[50];

	system("cls");

	printf("검색할 음악 제목 >> "); gets(name);
	
	//같은 이름 모두 출력
	for(i = 0; i < cnt; i++){
		if(strcmp(m[i]. name, name) == 0){
			printf("----------------------------------------------------\n");
			printf(" 곡 명 >> %s\n", m[i].name);
			printf(" 아티스트 >> %s\n", m[i].artist);
			printf(" 앨범 >> %s\n", m[i].album);
			cnt1++;
		}
	}
		
	//존재 하지 않으면 cnt1 == 0
	if(cnt1 == 0) printf("** %s 의 노래는 존재하지 않습니다 **\n", name);
	
	printf("\t\t\t\t\t메인으로 돌아가기 (0)\n");
	printf("\t\t\t\t\t검색으로 돌아가기 (1) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}
	if(n == 1){
		system("cls");
		search(cnt);
	}
}

// 7 - 2. 아티스트 검색
void search_artist(int cnt){ 

	int n, i, cnt1 = 0;
	char artist[50];
	
	system("cls");

	printf("검색할 음악 아티스트 >> "); gets(artist);
	
	//같은 이름 모두 출력
	for(i = 0; i < cnt; i++){
		if(strcmp(m[i]. artist, artist) == 0){
			printf("----------------------------------------------------\n");
			printf(" 곡 명 >> %s\n", m[i].name);
			printf(" 아티스트 >> %s\n", m[i].artist);
			printf(" 앨범 >> %s\n", m[i].album);
			cnt1++;
		}
	}
		
	//존재 하지 않으면 cnt1 == 0
	if(cnt1 == 0) printf("** %s 의 노래는 존재하지 않습니다 **\n", artist);

	printf("\t\t\t\t\t메인으로 돌아가기 (0)\n");
	printf("\t\t\t\t\t검색으로 돌아가기 (1) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}
	if(n == 1){
		system("cls");
		search(cnt);
	}

}

// 7 - 3. album 검색
void search_album(int cnt){ 

	int n, i, cnt1 = 0;
	char album[50];

	system("cls");

	printf("검색할 음악 앨범 명 >> "); gets(album);
	
	//같은 이름 모두 출력
	for(i = 0; i < cnt; i++){
		if(strcmp(m[i]. album, album) == 0){
			printf("----------------------------------------------------\n");
			printf(" 곡 명 >> %s\n", m[i].name);
			printf(" 아티스트 >> %s\n", m[i].artist);
			printf(" 앨범 >> %s\n", m[i].album);
			cnt1++; 

		}
	}
	
	//존재 하지 않으면 cnt1 == 0
	if(cnt1 == 0) printf("** %s 의 노래는 존재하지 않습니다 **\n", album);
	

	printf("\t\t\t\t\t메인으로 돌아가기 (0)\n");
	printf("\t\t\t\t\t검색으로 돌아가기 (1) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}
	if(n == 1){
		system("cls");
		search(cnt);
	}

}
