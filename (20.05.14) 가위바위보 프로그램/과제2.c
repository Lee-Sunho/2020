#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
	char com,user;
	printf("가위(X)바위(O)보(#)게임을 시작합니다.(게임종료:9)\n");

	srand(time(NULL));
	while(1){
		com=rand()%3;
		printf("가위 바위 보를 선택하세요: ");
		user=getchar();
		getchar();

		if(user=='9'){
			printf("다음에 또 만나요");
			break;
		}
		else if(user=='X'){
			if(com==0){
				printf("당신은 %c를 냈고 컴퓨터는 X를 냈습니다.\n",user);
				printf("당신과 컴퓨터는 비겼습니다.");
			}
			else if(com==1){
				printf("당신은 %c를 냈고 컴퓨터는 O를 냈습니다.\n",user);
				printf("컴퓨터가 이겼습니다.");
			}
			else if(com==2){
				printf("당신은 %c를 냈고 컴퓨터는 #를 냈습니다.\n",user);
				printf("당신이 이겼습니다.");
			}
		}
		else if(user=='O'){
			if(com==0){
				printf("당신은 %c를 냈고 컴퓨터는 X를 냈습니다.\n",user);
				printf("당신이 이겼습니다.");
			}
			else if(com==1){
				printf("당신은 %c를 냈고 컴퓨터는 O를 냈습니다.\n",user);
				printf("당신과 컴퓨터는 비겼습니다.");
			}
			else if(com==2){
				printf("당신은 %c를 냈고 컴퓨터는 #를 냈습니다.\n",user);
				printf("컴퓨터가 이겼습니다.");
			}
		}
		else if(user=='#'){
			if(com==0){
				printf("당신은 %c를 냈고 컴퓨터는 X를 냈습니다.\n",user);
				printf("컴퓨터가 이겼습니다.");
			}
			else if(com==1){
				printf("당신은 %c를 냈고 컴퓨터는 O를 냈습니다.\n",user);
				printf("당신이 이겼습니다.");
			}
			else if(com==2){
				printf("당신은 %c를 냈고 컴퓨터는 #를 냈습니다.\n",user);
				printf("당신과 컴퓨터는 비겼습니다.");
			}
		}
	}
	return 0;
}
