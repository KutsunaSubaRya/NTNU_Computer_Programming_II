#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stddef.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include "basic.h"
void print_player_card(int32_t p){
	printf(YEL_BOLD);
	printf("-----------------------------------------------------------\n");
	printf("Player%d have %d hand cards.\n",p ,Player[p].cnt_hand_card);
	int32_t flags=1;
	//for(int i=1;i<=110;i++) if(Player[p].hand_cards[i]==1) printf("card%d number: %d cost: %d vp: %d\n",flags++,i,All_Cards[i].cost,All_Cards[i].vp);
	printf(RESET);
}
void print_player_building(int32_t p){
	printf(YEL_BOLD);
	printf("Player%d have %d building(s).\n",p ,Player[p].cnt_have_building);
	int32_t flags=1;
	for(int i=1;i<=110;i++) if(Player[p].building_cards[i].status==1) printf("card%d number: %d\n",flags++,i);
	for(int i=1;i<=42;i++) if(Player[p].building_cards[i].cargo==1) printf("factory_num %d have one cargo.\n",i);
	printf("-----------------------------------------------------------\n");
	printf(RESET);
}