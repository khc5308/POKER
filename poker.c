#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//High Card : 숫자가 높은 카드 1장
//One Pair : 숫자가 같은 카드 2장
//Two Pairs : 2쌍의 페어
//Three of a Kind : 숫자가 같은 카드 3장
//Straight : 숫자가 이어지는 카드 5장
//Flush : 무늬가 같은 카드 5장
//Full House : Three of a Kind + Pair
//Four of a Kind : 숫자가 같은 카드 4장
//Straight Flush : 숫자가 이어지고 무늬가 같은 카드 5장
int deck[5][15] = { 0 };
int Card_Player[7][2] = { 0 },
	Card_Dealer[7][2] = { 0 };
int Score_Player,Score_Dealer;
//숫자 출력(숫자num)
void num(int randNum) {
	switch (randNum) {
	case 1: printf("A"); break;
	case 11: printf("J"); break;
	case 12: printf("Q"); break;
	case 13: printf("K"); break;
	default: printf("%d", randNum); break;
	}
}
//모양 출력(모양num)
void shape_(int shape) {
	switch (shape) {
	case 0: printf(" ♠ "); break;
	case 1: printf(" ♥ "); break;
	case 2: printf(" ◆ "); break;
	case 3: printf(" ♣ "); break;
	}
}
//중복 없이 카드 뽑기(1 == player,2 == open, 3 == deal)
int card(int AorU,int number) {
	while (1)
	{
		int CardNum = rand() % 13 + 1;
		int CardShape = rand() % 4;
		if (deck[CardShape][CardNum] == 0) {
			deck[CardShape][CardNum] = 1;
			if (AorU == 1) {
				shape_(CardShape);
				num(CardNum);
				Card_Player[number][0] = CardShape;
				Card_Player[number][1] = CardNum;
				break;
			}
			else if (AorU == 2) {
				shape_(CardShape);
				num(CardNum);

				Card_Player[number + 2][0] = CardShape;
				Card_Player[number + 2][1] = CardNum;
				Card_Dealer[number + 2][0] = CardShape;
				Card_Dealer[number + 2][1] = CardNum;
				break;
			}
			else if (AorU == 3) {
				Card_Dealer[number][0] = CardShape;
				Card_Dealer[number][1] = CardNum;
				break;
			}
			break;
		}
		return 0; 
	}
}
//족보 판단
int genealogy(int AorU) {
//Full House : Three of a Kind + Pair

	if (AorU == 1) {
		int same_num = -1,same_shape = -1,min_num = 21374836,qwer = 0;
		//같은 모양 갯수 세기
		for (int i = 1; i < 7; i++) {
			int tmp = 0;
			for (int j = 0; j < 7; j++) 
				if (Card_Player[i][0] == Card_Player[j][0]) 
					tmp++;
			
			if (same_shape < tmp)
				same_shape = tmp;
		}
		//같은 숫자 세기
		int lastsame_num = 0;
		for (int i = 0; i < 7;i++) {
			int tmp = 0;
			for (int j = 0; j < 7; j++) {
				if (Card_Player[i][1] == Card_Player[j][1])
					tmp++;
			}
			if (min_num > Card_Player[i][1])
				min_num = Card_Player[i][1];
			if (same_num < tmp)
				same_num = tmp;
			if (lastsame_num == tmp && tmp == 2) {
				printf("Two Pairs");
				Score_Player = 3;
				return 0;
			}
			lastsame_num = same_num;
		}
		for (int i = 1; i < 5; i++) {
			int tmp = 0;
			for (int j = 0; j < 7; j++) 
				if (min_num + i == Card_Player[j][1]) 
					tmp++;
			if (tmp != i)
				break;
			if (tmp == 4)
				qwer = 1;
		}
		if (qwer == 1) {
			if (same_shape == 5) {
				printf("Straight Flush");
				Score_Player = 9;
				return 0;
			}
			else {
				printf("Straight");
				Score_Player = 5;
				return 0;
			}
		}
		
		if (same_shape == 5) {
			printf("Flush");
			Score_Player = 6;
			return 0;
		}

		if (same_num == 2) {
			printf("One Pair");
			Score_Player = 2;
			return 0;
		}
		else if (same_num == 3) {
			printf("Three of a Kind");
			Score_Player = 4;
			return 0;
		}
		else if (same_num == 4) {
			printf("Four of a Kind");
			Score_Player = 8;
			return 0;
		}

		//High Card
		printf("High Card");
		Score_Player = 1;
		return 0;
		
	}	
	/*else if (AorU == 3) {


	}*/
	return 0;
}


int main() {
	srand(time(NULL));
	//카드 출력
	printf("User Card :");
	card(1,0);
	card(1,1);
	printf("\n");
	printf("community Card :");
	card(2,0);
	card(2,1);
	card(2,2);
	card(2,3);
	card(2,4);

	//card(3, 0);
	//card(3, 1);

	printf("\n");
	printf("User genealogy : ");
	genealogy(1);
	printf("\n");
	printf("Dealer genealogy :");
	genealogy(3);

}