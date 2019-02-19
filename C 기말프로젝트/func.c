/*

���� �Է�
- ���� (�� ��)
- ��Ƽ��Ʈ
- �ٹ� ��

MENU
====================================
1. ���� �߰�
2. ���� �˻� �� ����
3. ��ü ���� ���
	>> �� ���� ���� ������ ���
		>> ���� ȭ�� ���ư��� : 0
4. ��Ƽ��Ʈ ��
	>> ��Ƽ��Ʈ �̸����� ���� ������ ���
		>>������ ȭ�� ���ư��� : 0
5. �ٹ� ��
	>> �ٹ� ������ ���� ������ ���
		>>������ ȭ�� ���ư��� : 0
6. ���� ���
	>> ���� �� ���� �� �������� �ϳ� ���
		>>������ ȭ�� ���ư��� : 0
7. �˻�
	1. ���� �˻�
	2. ��Ƽ��Ʈ �˻�
	3. �ٹ� �˻�
		>>������ ȭ�� ���ư��� : 0
0. ����

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

// ����Ʈ�� �迭�� ����
void _malloc(struct music *M, int *cnt){

	struct music *ptr;
	int i;

	m = (struct music *) malloc(sizeof(struct music) * (*cnt)); // �迭 �����Ҵ�

	// ����Ʈ�� �迭�� �ٽ� ����
	for(ptr = M, i = 0; ptr != NULL, i < (*cnt) ; ptr = ptr -> next, i++){
		strcpy(m[i].name, ptr -> name);
		strcpy(m[i].artist, ptr -> artist);
		strcpy(m[i].album, ptr -> album);
	}

}

// 1�� �迭 & ����Ʈ �߰�
void add_list(struct music **M, int *cnt){

	struct music *node, *ptr;
	int n;

	fp1 = fopen("input_name.txt", "w");
	fp2 = fopen("input_artist.txt", "w");
	fp3 = fopen("input_album.txt", "w");

	node = (struct music *) malloc(sizeof(struct music));

	printf("\t���� �߰�\n");
	printf("----------------------------------------------------\n");
	printf(" �� �� >> "); gets(node -> name); 
	printf(" ��Ƽ��Ʈ >> "); gets(node -> artist);
	printf(" �ٹ� >> "); gets(node -> album);

	(*cnt)++;

	//����Ʈ ó���� �߰�
	node -> next = *M;
	*M = node;

	// �߰��� �������� ���Ͽ� ���� ����
	for(ptr = *M; ptr != NULL; ptr = ptr -> next){
		fprintf(fp1, "%s\n", ptr -> name);
		fprintf(fp2, "%s\n", ptr -> artist);
		fprintf(fp3, "%s\n", ptr -> album);
	}

	_malloc(*M, cnt); // �迭�� �Ű��ֱ�
	
	printf("\t\t\t\t\t�������� ���ư��� (0) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}

	fclose(fp1); fclose(fp2); fclose(fp3);

}

// 2. ���� ����. ����Ʈ���� ���� �� �迭 ������
void delete_list(struct music **M, int *cnt){ 

	struct music *prev, *cur, *ptr;
	char name[50];
	int n;

	fp1 = fopen("input_name.txt", "w");
	fp2 = fopen("input_artist.txt", "w");
	fp3 = fopen("input_album.txt", "w");

	printf("\t���\n");
	printf("----------------------------------------------------\n");
	for(ptr = *M; ptr != NULL; ptr = ptr -> next) printf("   %s\n", ptr -> name);
	printf("----------------------------------------------------\n");

	printf("������ ���� ���� �Է� >> "); gets(name);

	for(prev = NULL, cur = *M; cur != NULL; prev = cur, cur = cur -> next){
		if(strcmp(cur -> name, name) == 0){
			if(prev == NULL){ // ù��° ��忡 ������
				*M = cur -> next;
				free(cur);
				(*cnt)--;
				printf(" ** ���� �Ϸ� **\n");
				break;
			}

			else{ // �߰� ��忡 ������ ��
				prev -> next = cur -> next;
				free(cur);
				(*cnt)--;				
				printf(" ** ���� �Ϸ� **\n");
				break;
			}
		}
	}
	// �������� ����
	if(cur == NULL) printf("** %s�� �뷡�� �������� �ʽ��ϴ�. **\n", name);

	//���� �� ���Ͽ� �ٽ� ����
	for(ptr = *M; ptr != NULL; ptr = ptr -> next){
		fprintf(fp1, "%s\n", ptr -> name);
		fprintf(fp2, "%s\n", ptr -> artist);
		fprintf(fp3, "%s\n", ptr -> album);
	}

	_malloc(*M, cnt); // �迭�� �Ű��ֱ�

	printf("\t\t\t\t\t�������� ���ư��� (0) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}

	fclose(fp1); fclose(fp2); fclose(fp3);

}

// 3. ��ü ���� ����� ����
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

	printf("\t�� �� �� ����\n");
	printf("----------------------------------------------------\n");

	for(i = 0; i < cnt; i++){
		printf(" �� �� >> %s\n", m[i].name);
		printf(" ��Ƽ��Ʈ >> %s\n", m[i].artist);
		printf(" �ٹ� >> %s\n", m[i].album);
		printf("----------------------------------------------------\n");
	}


	printf("\t\t\t\t\t�������� ���ư��� (0) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}

}

// 4. ��ü ���� ��Ƽ��Ʈ ���� ����
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
	
	printf("\t��Ƽ��Ʈ �� ����\n");
	printf("----------------------------------------------------\n");

	for(i = 0; i < cnt; i++){
		printf(" ��Ƽ��Ʈ >> %s\n", m[i].artist);
		printf(" �� �� >> %s\n", m[i].name);
		printf(" �ٹ� >> %s\n", m[i].album);
		printf("----------------------------------------------------\n");
	}


	printf("\t\t\t\t\t�������� ���ư��� (0) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}

}

// 5. ��ü ���� �ٹ��� ���� ����
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
	
	printf("\t�ٹ� �� ����\n");
	printf("----------------------------------------------------\n");

	for(i = 0; i < cnt; i++){
		printf(" �ٹ� >> %s\n", m[i].album);
		printf(" �� �� >> %s\n", m[i].name);
		printf(" ��Ƽ��Ʈ >> %s\n", m[i].artist);
		printf("----------------------------------------------------\n");
	}

	printf("\t\t\t\t\t�������� ���ư��� (0) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}

}
// 6. ���� ���
void randomplay(int cnt){

	int n, x;

	srand(time(NULL));

	x = rand() % cnt; // 0 ���� (cnt - 1) ����

	printf("\t���� ���\n");
	printf("----------------------------------------------------\n");
	printf("    ����      :  %s\n", m[x].name);
	printf("    ��Ƽ��Ʈ  :  %s\n", m[x].artist);
	printf("    �ٹ�      :  %s\n", m[x].album);
	

	printf("\t\t\t\t\t�������� ���ư��� (0) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}

}

// 7. ���� �˻�

void search_name(int cnt);
void search_artist(int cnt);
void search_album(int cnt);

void search(int cnt){ 

	int n;

	printf("\t���ǰ˻�\n");
	printf("----------------------------------------------------\n");
	printf(" 1. ���� �˻�\n");
	printf(" 2. ��Ƽ��Ʈ �˻�\n");
	printf(" 3. �ٹ� �˻�\n\n");
	printf(" 0. �������� ���ư���\n");
	printf("----------------------------------------------------\n");
	printf(" �Է� >> "); scanf("%d", &n);

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
		printf("�߸� �� �Է��Դϴ�\n");
		system("pause"); system("cls");
		search(cnt);//���� ������ �ٸ� ��ȣ �Է½� �ٽ� 7������ ���ư�
		break;
			 }
	}

}

// 7 - 1 .���� �˻�
void search_name(int cnt){ 

	int n, i, cnt1 = 0;
	char name[50];

	system("cls");

	printf("�˻��� ���� ���� >> "); gets(name);
	
	//���� �̸� ��� ���
	for(i = 0; i < cnt; i++){
		if(strcmp(m[i]. name, name) == 0){
			printf("----------------------------------------------------\n");
			printf(" �� �� >> %s\n", m[i].name);
			printf(" ��Ƽ��Ʈ >> %s\n", m[i].artist);
			printf(" �ٹ� >> %s\n", m[i].album);
			cnt1++;
		}
	}
		
	//���� ���� ������ cnt1 == 0
	if(cnt1 == 0) printf("** %s �� �뷡�� �������� �ʽ��ϴ� **\n", name);
	
	printf("\t\t\t\t\t�������� ���ư��� (0)\n");
	printf("\t\t\t\t\t�˻����� ���ư��� (1) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}
	if(n == 1){
		system("cls");
		search(cnt);
	}
}

// 7 - 2. ��Ƽ��Ʈ �˻�
void search_artist(int cnt){ 

	int n, i, cnt1 = 0;
	char artist[50];
	
	system("cls");

	printf("�˻��� ���� ��Ƽ��Ʈ >> "); gets(artist);
	
	//���� �̸� ��� ���
	for(i = 0; i < cnt; i++){
		if(strcmp(m[i]. artist, artist) == 0){
			printf("----------------------------------------------------\n");
			printf(" �� �� >> %s\n", m[i].name);
			printf(" ��Ƽ��Ʈ >> %s\n", m[i].artist);
			printf(" �ٹ� >> %s\n", m[i].album);
			cnt1++;
		}
	}
		
	//���� ���� ������ cnt1 == 0
	if(cnt1 == 0) printf("** %s �� �뷡�� �������� �ʽ��ϴ� **\n", artist);

	printf("\t\t\t\t\t�������� ���ư��� (0)\n");
	printf("\t\t\t\t\t�˻����� ���ư��� (1) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}
	if(n == 1){
		system("cls");
		search(cnt);
	}

}

// 7 - 3. album �˻�
void search_album(int cnt){ 

	int n, i, cnt1 = 0;
	char album[50];

	system("cls");

	printf("�˻��� ���� �ٹ� �� >> "); gets(album);
	
	//���� �̸� ��� ���
	for(i = 0; i < cnt; i++){
		if(strcmp(m[i]. album, album) == 0){
			printf("----------------------------------------------------\n");
			printf(" �� �� >> %s\n", m[i].name);
			printf(" ��Ƽ��Ʈ >> %s\n", m[i].artist);
			printf(" �ٹ� >> %s\n", m[i].album);
			cnt1++; 

		}
	}
	
	//���� ���� ������ cnt1 == 0
	if(cnt1 == 0) printf("** %s �� �뷡�� �������� �ʽ��ϴ� **\n", album);
	

	printf("\t\t\t\t\t�������� ���ư��� (0)\n");
	printf("\t\t\t\t\t�˻����� ���ư��� (1) :: "); scanf("%d", &n);
	if(n == 0){
		system("cls");
	}
	if(n == 1){
		system("cls");
		search(cnt);
	}

}
