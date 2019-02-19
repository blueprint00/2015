/*
���� �Է�
- ���� (�� ��)
- ��Ƽ��Ʈ
- �ٹ� ��

MENU
===============================
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
	struct music *m; //�迭 �����Ҵ�
	struct music *new_node, *ptr;
	
	fp1 = fopen("input_name.txt", "r");
	fp2 = fopen("input_artist.txt", "r");
	fp3 = fopen("input_album.txt", "r");
	
	// ���� ����
	if(fp1 == NULL || fp2 == NULL || fp3 == NULL){
		printf("========FILE OPEN ERROR========\n");
		return 0;
	}
	
	c = &cnt;

	while(1){

		//����Ʈ ����
		new_node = (struct music *) malloc(sizeof(struct music));

		fgets(new_node -> name, 50, fp1); if(feof(fp1) != 0) break;
		fgets(new_node -> artist, 50, fp2); if(feof(fp2) != 0) break;
		fgets(new_node -> album, 50, fp3); if(feof(fp3) != 0) break; // ������ ���� ��� ����

		//�ڿ� ����� enter �����
		new_node -> name[strlen(new_node -> name) - 1] = '\0';
		new_node -> artist[strlen(new_node -> artist) - 1] = '\0';
		new_node -> album[strlen(new_node -> album) - 1] = '\0';

		new_node -> next = M;
		M = new_node;
		
		cnt++; // ���� ����
	
	}

	// ���Ͽ� �ƹ��͵� �������� ����
		if(cnt == 0) printf("�� ������ ����ֽ��ϴ�\n");

	m = (struct music *) malloc(sizeof(struct music) * cnt); // �迭 �����Ҵ�
	
	// ����Ʈ�� �迭�� �ٽ� ����
	for(ptr = M, i = 0; ptr != NULL, i < cnt; ptr = ptr -> next, i++){
		strcpy(m[i].name, ptr -> name);
		strcpy(m[i].artist, ptr -> artist);
		strcpy(m[i].album, ptr -> album);
	}

	while(1){

		printf("\n\t>> MENU\n");
		printf("----------------------------------------------------\n");
		printf(" 1. ���� �߰�\n");
		printf(" 2. ���� ���� �˻� �� ����\n");
		printf(" 3. ��ü ���� �� �� �� ���\n");
		printf(" 4. ��ü ���� ��Ƽ��Ʈ �� ����\n");
		printf(" 5. ��ü ���� �ٹ� �� ����\n");
		printf(" 6. ���� ���\n");
		printf(" 7. ���� �˻�\n");
		printf(" 0. ����\n");
		printf("----------------------------------------------------\n");
		printf(" �Է� >> "); scanf("%d", &n);

		if(n == 0) break; // ����

		fflush(stdin);
		
		system("cls"); //ȭ�� ����

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