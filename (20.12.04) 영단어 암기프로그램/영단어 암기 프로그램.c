#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word{
	char eng[16];
	char kor[61];
	struct Word * next;
}Word;

Word * head;
Word * tail;

int a=1,func;

void menu();
Word * makeNode();
Word * load_data();
void word_test(Word * list);
void sort_word(Word * list);

int main(){
	head=(Word*)malloc(sizeof(Word));
	tail=head;
	tail->next=NULL;
	
	Word *list = load_data();
	while(a){
		menu();
		printf("번호를 선택하세요: ");
		scanf("%d",&func);

		switch(func){
			case 1:
				sort_word(list);
				word_test(list);
				break;
			case 2:
				a=0;
				system("clear");
				break;
			default:
				printf("잘못된 입력입니다.\n");
				continue;
				break;
		}
	}
}

void menu(){
	printf(">> 영어 단어 맞추기 프로그램 <<\n");
	printf("1.영어 단어 맞추기       ");
	printf("2.프로그램 종료\n");
}

Word * makeNode(){
	Word * node = (Word*)malloc(sizeof(Word));
	node->next=NULL;
	tail->next=node;
	tail=node;
	tail->next=NULL;
	return tail;
}

Word * load_data(){
	char eng[16];
	char kor[61];
	FILE *fp = fopen("dic.txt","r");
	if(fp==NULL){
		printf("file open error\n");
		return 0;
	}
	else{
		fscanf(fp,"%s %s",eng,kor);
		strcpy(head->eng,eng);
		strcpy(head->kor,kor);
	   	while(fscanf(fp,"%s %s",eng,kor)!=EOF){
			Word *t=makeNode();
			strcpy(t->eng,eng);
			strcpy(t->kor,kor);
		}
	}
	fclose(fp);
	return head;
}

void sort_word(Word * list){
	Word *temp = (Word*)malloc(sizeof(Word));
	Word *p;
	Word *q;
	for(p = list;p!=tail;p=p->next){
		for(q = p->next;q!=NULL;q=q->next){
			if(strcmp(p->eng,q->eng)>0){
				strcpy(temp->eng,q->eng);
				strcpy(q->eng,p->eng);
				strcpy(p->eng,temp->eng);
				strcpy(temp->kor,q->kor);
				strcpy(q->kor,p->kor);
				strcpy(p->kor,temp->kor);
			}
		}
	}
}

void word_test(Word * list){
	char answer[16];
	int num=0,correct=0;
	printf(">> 영어 단어 맞추기 <<\n");
	while(list!=NULL){
		printf("%s -> ",list->kor);
		scanf("%s",answer);
		if(!strcmp(list->eng,answer)){
			printf("correct!\n");
			num++;
			correct++;
		}
		else if(!strcmp(answer,".quit")){
			break; 
		}
		else{
			printf("incorrect!\n");
			num++;
		}
		list=list->next;
	}
	printf("당신의 점수는 %.2f 점 입니다.\n",(100/(float)num)*correct);
	getchar();
	getchar();
}
