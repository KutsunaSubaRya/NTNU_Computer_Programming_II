#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stddef.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include "comp.h"
#include "basic.h"
/*
//---------define color---------
#define RED_BOLD "\x1b[;31;1m"
#define BLU_BOLD "\x1b[;34;1m"
#define YEL_BOLD "\x1b[;33;1m"
#define GRN_BOLD "\x1b[;32;1m"
#define PURPLE "\e[1;35m"
#define CYAN_BOLD_ITALIC "\x1b[;36;1;3m"
#define RESET "\x1b[0;m"
//-----------typedef------------
typedef struct _Cards {
	uint32_t status; //0: in the card pile  1: discard  2: in the abandoned area
    uint32_t cost;
	uint32_t vp;
	uint32_t w_building; // 1: produce  2: special
	uint32_t cargo; // 46~48 cargo is Chapel attribute
} __attribute__ ((__packed__)) Cards;

typedef struct _player {
	uint32_t Governor;// 0: No 1: Yes
	uint32_t action_card;//0: No 1: Builder 2: Producer 3: Trader 4: Counciler 5: Prospector
	uint32_t cnt_have_building;
	uint32_t cnt_hand_card;
	Cards building_cards[120];// building on the table 
	// 1:have this card  0: ~1  all: 110 building cards 
	uint32_t hand_cards[120];// your hand card
	// 1:have this card  0: ~1  all: 110 building cards
} __attribute__ ((__packed__)) player;

player Player[5];
Cards All_Cards[120]; */
uint32_t ACT_cards[10]={0}; // 0: in the card pile  1: discard
uint32_t Trader_List[6][6]={{0,0,0,0,0,0},{0,1,2,2,3,3},{0,1,1,2,2,3},{0,1,2,2,2,3},{0,1,1,1,2,2},{0,1,1,2,2,2}};
int32_t LT,pg_flag=0,match_flag=0;
//-----------function-----------
uint32_t pick_one_card(void){
	for(int i=0;i<=110;i++) if(All_Cards[i].status==2) All_Cards[i].status=0; 
	uint32_t a;
	srand(time(NULL));
	while(1){
		a = (rand()%110)+1;
		if(All_Cards[a].status==0) {
			All_Cards[a].status=1;
			break;
		}
	}
	return a;
}
uint32_t pick_one_trader_list(void){
	uint32_t a;
	srand(time(NULL));
	a = (rand()%5)+1;
	return a;
}
void print_SANJUAN(void){
	printf(GRN_BOLD"  _// //        _/       _///     _//           _//_//     _//      _/       _///     _//\n_//    _//     _/ //     _/ _//   _//           _//_//     _//     _/ //     _/ _//   _//\n _//          _/  _//    _// _//  _//           _//_//     _//    _/  _//    _// _//  _//\n   _//       _//   _//   _//  _// _//           _//_//     _//   _//   _//   _//  _// _//\n      _//   _////// _//  _//   _/ _//           _//_//     _//  _////// _//  _//   _/ _//\n_//    _// _//       _// _//    _/ //      _/   _//_//     _// _//       _// _//    _/ //\n  _// //  _//         _//_//      _//       _////    _/////   _//         _//_//      _//\n");
	printf(RESET);
}
void init(void){
	Player[1].Governor=1; Player[2].Governor=0; Player[3].Governor=0; Player[4].Governor=0;
	for(int i=1;i<=4;i++){
		Player[i].action_card=0;
		Player[i].Chapel_vp=0;
		Player[i].cnt_have_building=1;
		Player[i].cnt_hand_card=4;
		for(int j=1;j<=110;j++) {
			Player[i].building_cards[j].status=0;
			Player[i].building_cards[j].cargo=0;
		}
		// every one have 1 Indigo plant and 1~4 Indigo plant are diacard
		Player[i].building_cards[i].status=1; 
		All_Cards[i].status=1;
		// every one get four hand card;
		for(int k=0;k<4;k++) Player[i].hand_cards[pick_one_card()]=1;
	}
	//init the card attribute
	for(int i=1;i<=42;i++) All_Cards[i].w_building=1;
	for(int i=43;i<=110;i++) All_Cards[i].w_building=2;
	for(int i=1;i<=10;i++){
		All_Cards[i].cost=1;
		All_Cards[i].vp=1;
	}
	for(int i=11;i<=18;i++){
		All_Cards[i].cost=2;
		All_Cards[i].vp=1;
	}
	for(int i=19;i<=26;i++){
		All_Cards[i].cost=3;
		All_Cards[i].vp=2;
	}
	for(int i=27;i<=34;i++){
		All_Cards[i].cost=4;
		All_Cards[i].vp=2;
	}
	for(int i=35;i<=42;i++){
		All_Cards[i].cost=5;
		All_Cards[i].vp=3;
	}
	for(int i=43;i<=45;i++){
		All_Cards[i].cost=3;
		All_Cards[i].vp=2;
	}
	for(int i=46;i<=48;i++){
		All_Cards[i].cost=3;
		All_Cards[i].vp=2;
	}
	for(int i=49;i<=51;i++){
		All_Cards[i].cost=1;
		All_Cards[i].vp=1;
	}
	for(int i=52;i<=54;i++){
		All_Cards[i].cost=2;
		All_Cards[i].vp=1;
	}
	for(int i=55;i<=57;i++){
		All_Cards[i].cost=2;
		All_Cards[i].vp=1;
	}
	for(int i=58;i<=60;i++){
		All_Cards[i].cost=2;
		All_Cards[i].vp=1;
	}
	for(int i=61;i<=63;i++){
		All_Cards[i].cost=3;
		All_Cards[i].vp=2;
	}
	for(int i=64;i<=66;i++){
		All_Cards[i].cost=4;
		All_Cards[i].vp=2;
	}
	for(int i=67;i<=69;i++){
		All_Cards[i].cost=2;
		All_Cards[i].vp=1;
	}
	for(int i=70;i<=72;i++){
		All_Cards[i].cost=3;
		All_Cards[i].vp=2;
	}
	for(int i=73;i<=75;i++){
		All_Cards[i].cost=2;
		All_Cards[i].vp=1;
	}
	for(int i=76;i<=78;i++){
		All_Cards[i].cost=4;
		All_Cards[i].vp=2;
	}
	for(int i=79;i<=81;i++){
		All_Cards[i].cost=2;
		All_Cards[i].vp=1;
	}
	for(int i=82;i<=84;i++){
		All_Cards[i].cost=1;
		All_Cards[i].vp=1;
	}
	for(int i=85;i<=87;i++){
		All_Cards[i].cost=3;
		All_Cards[i].vp=2;
	}
	for(int i=88;i<=90;i++){
		All_Cards[i].cost=1;
		All_Cards[i].vp=1;
	}
	for(int i=91;i<=93;i++){
		All_Cards[i].cost=5;
		All_Cards[i].vp=3;
	}
	for(int i=94;i<=96;i++){
		All_Cards[i].cost=3;
		All_Cards[i].vp=3;
	}
	for(int i=97;i<=99;i++){
		All_Cards[i].cost=4;
		All_Cards[i].vp=4;
	}
	for(int i=100;i<=102;i++){
		All_Cards[i].cost=5;
		All_Cards[i].vp=5;
	}
	for(int i=103;i<=104;i++){
		All_Cards[i].cost=6;
		All_Cards[i].vp=0;
	}
	for(int i=105;i<=106;i++){
		All_Cards[i].cost=6;
		All_Cards[i].vp=0;
	}
	for(int i=107;i<=108;i++){
		All_Cards[i].cost=6;
		All_Cards[i].vp=0;
	}
	for(int i=109;i<=110;i++){
		All_Cards[i].cost=6;
		All_Cards[i].vp=0;
	}
	
}
void pick_action_card(void){
	printf("Please choose the Action Card you want.(Enter number 1~5)\n(1: Builder 2: Producer 3: Trader 4: Counciler 5: Prospector): ");
	int num; 
	while(scanf("%d",&num)){
		if(ACT_cards[num]==1){
			printf(RED_BOLD);
			printf("It's been chosen. Please choose again.\n");
			printf("Please choose the Action Card you want.(Enter number 1~5)\n(1: Builder 2: Producer 3: Trader 4: Counciler 5: Prospector): ");
			printf(RESET);
		}
		else if(num>=6 || num<=0){
			printf("Please enter 1~5. Please choose again.\n");
			printf("Please choose the Action Card you want.(Enter number 1~5)\n(1: Builder 2: Producer 3: Trader 4: Counciler 5: Prospector): ");
		}
		else break;
	}
	ACT_cards[num]=1;
	if(num==1) printf("You are Builder.\n");
	else if(num==2) printf("You are Producer.\n");
	else if(num==3) printf("You are Trader.\n");
	else if(num==4) printf("You are Counciler.\n");
	else if(num==5) printf("You are Prospector.\n");
	Player[1].action_card=num;
}
void print_number_list_all_cards(void){
	printf(BLU_BOLD"* Produce Building\n    1. Blue\n	    * 1~10: Indigo plant\n	2. White\n	    * 11~18: Sugar mill\n	3. Brown\n	    * 19~26: Tobacco storage\n    4. Beige\n	    * 27~34: Coffee roaster\n	5. Gray\n	    * 35~42: Silver smelter\n* Special Building\n	* To player for every round:\n		* 43~45: 	 Tower\n		* 46~48: 	 Chapel\n	* Action Card -> Builder \n		* 49~51: 	 Smithy\n		* 52~54: 	 Poor house\n		* 55~57: 	 Black market\n		* 58~60: 	 Crane\n		* 61~63: 	 Carpenter\n		* 64~66: 	 Quarry\n	* Action Card -> Producer\n		* 67~69: 	 Well\n		* 70~72: 	 Aqueduct\n	* Action Card -> Trader\n		* 73~75: 	 Market stand\n		* 76~78: 	 Market hall\n		* 79~81: 	 Trading post\n	* Action Card -> Counciler\n		* 82~84: 	 Archive\n		* 85~87:   Prefecture\n	* Action Card -> Prospector\n		* 88~90:   Gold mine\n	* Every Action Card\n		* 91~93:   Library\n	* Nothing Special:\n		* 94~96:   Statue\n		* 97~99:   Victory column\n		* 100~102: Hero\n	* End of Game:\n		* 103,104: Guild hall\n		* 105,106: City hall\n		* 107,108: Triumhal arch\n		* 109,110: Palace\n");
	printf(RESET);
}
void print_hand_card(void){
	printf(YEL_BOLD);
	printf("You have %d hand cards.\n", Player[1].cnt_hand_card);
	int32_t flags=1;
	for(int i=1;i<=110;i++) if(Player[1].hand_cards[i]==1) printf("card%d number: %d cost: %d vp: %d\n",flags++,i,All_Cards[i].cost,All_Cards[i].vp);
	printf(RESET);
}
void print_self_building(void){
	printf(YEL_BOLD);
	printf("You have %d building(s).\n", Player[1].cnt_have_building);
	int32_t flags=1;
	for(int i=1;i<=110;i++) {
		if(Player[1].building_cards[i].status==1){
			if(i>=1 && i<=42) printf("card%d number: %d cargo=%d \n",flags++,i,Player[1].building_cards[i].cargo);	 
			else printf("card%d number: %d\n",flags++,i);
		}
	}
	printf(RESET);
}
void print_table(void){
	printf(PURPLE);
	for(int i=2;i<=4;i++){
		printf("Player%d has %d buildings: \n",i,Player[i].cnt_have_building);
		for(int j=1;j<110;j++) if(Player[i].building_cards[j].status==1) printf("    Card: %d\n",j);
		for(int j=1;j<=42;j++) if(Player[i].building_cards[j].cargo==1) printf("factory_num %d have one cargo.\n",j);
		printf("\n");
	}
	printf(RESET);
}
void choose_number(void){
	printf(CYAN_BOLD_ITALIC);
	print_hand_card();
	print_self_building();
	printf("(1): See the table the buildings that other players builded\n");
	printf("(2): See the number list of all building cards\n");
	printf("(3): Continue.\n");
	printf("Please choose what you want to do (1~3): \n");
	printf(RESET);
}
void abandon_card(int32_t num){
	int32_t flags=0,a_c;
	printf("Please choose %d card to the abandon area.(Enter the number of the card(1~110)):\n",num);
	for(int i=0;i<num;i++){
		printf("card %d: ",++flags);
		while(scanf("%d",&a_c)){
			if(Player[1].hand_cards[a_c]==0) printf("You don't have this card. Please choose again.\ncard %d: ",flags);
			else{
				All_Cards[a_c].status=2;
				Player[1].hand_cards[a_c]=0; Player[1].cnt_hand_card--;
				break;
			}
		}
	}
}
void Carpenter(int32_t n){
	if(Player[n].building_cards[61].status==1 || Player[n].building_cards[62].status==1 || Player[n].building_cards[63].status==1){
		//Carpenter
		int32_t tmp_p=pick_one_card();
		Player[n].cnt_hand_card++;
		Player[n].hand_cards[tmp_p]=1;
	}
}
void Poor_House(int32_t n){
	if(Player[n].building_cards[52].status==1 || Player[n].building_cards[53].status==1 || Player[n].building_cards[54].status==1){
		//Poor_House
		if(Player[n].cnt_hand_card<=1){
			int32_t tmp_p=pick_one_card();
			Player[n].cnt_hand_card++;
			Player[n].hand_cards[tmp_p]=1;
		}
	}
}
int32_t Trading_post(int32_t n){
	if(Player[n].building_cards[79].status==1 || Player[n].building_cards[80].status==1 || Player[n].building_cards[81].status==1){
		//Trading_post
		for(int i=0;i<=42;i++){
			if(Player[n].building_cards[i].cargo==1){
				Player[n].building_cards[i].cargo=0;
				int32_t cnt_card;
				if(i>=1 && i<=10) cnt_card=Trader_List[LT][1];
				else if(i>=11 && i<=18) cnt_card=Trader_List[LT][2];
				else if(i>=19 && i<=26) cnt_card=Trader_List[LT][3];
				else if(i>=27 && i<=34) cnt_card=Trader_List[LT][4];
				else if(i>=35 && i<=42) cnt_card=Trader_List[LT][5];
				for(int j=0;j<cnt_card;j++){
					Player[n].hand_cards[pick_one_card()]=1;
					Player[n].cnt_hand_card+=1;
				}
				return 1;
			}
		}
	}
	return 0;
}
void Market_Hall(int32_t n){
	if(Player[n].building_cards[76].status==1 || Player[n].building_cards[77].status==1 || Player[n].building_cards[78].status==1){
		Player[n].hand_cards[pick_one_card()]=1;
		Player[n].cnt_hand_card++;
	}
}
void Gold_Mine(int32_t n){
	for(int i=1;i<=4;i++){
		if(n==0) n=4;
		if(n==1){
			if(Player[n].building_cards[88].status==1 || Player[n].building_cards[89].status==1 || Player[n].building_cards[90].status==1){
				int a=pick_one_card(),b=pick_one_card(),c=pick_one_card(),d=pick_one_card();
				All_Cards[a].status=2; All_Cards[b].status=2; All_Cards[c].status=2; All_Cards[d].status=2;
				if(All_Cards[a].cost!=All_Cards[b].cost && All_Cards[a].cost!=All_Cards[c].cost && All_Cards[a].cost!=All_Cards[d].cost && All_Cards[b].cost!=All_Cards[c].cost && All_Cards[b].cost!=All_Cards[d].cost && All_Cards[c].cost!=All_Cards[d].cost){
					printf("You find the gold.\n");
					printf("Card1: %d\nCard2: %d\nCard3: %d\nCard4: %d\n",a,b,c,d);
					printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~4.)\n");
					int32_t det;
					while(scanf("%d",&det)){
						if(det==a || det==b || det==c || det==d){
							All_Cards[det].status=1;
							Player[1].hand_cards[det]=1; Player[1].cnt_hand_card++;
							break;
						}
						else{
							printf("Please choose one card of these four cards! Please choose again.\n");
							printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~5.)\n");
							continue;
						}
					}
				}
				else{
					printf("You find no gold.\n");
				}
			}
		}
		else{
			if(Player[n].building_cards[88].status==1 || Player[n].building_cards[89].status==1 || Player[n].building_cards[90].status==1){
				int a=pick_one_card(),b=pick_one_card(),c=pick_one_card(),d=pick_one_card();
				All_Cards[a].status=2; All_Cards[b].status=2; All_Cards[c].status=2; All_Cards[d].status=2;
				if(All_Cards[a].cost!=All_Cards[b].cost && All_Cards[a].cost!=All_Cards[c].cost && All_Cards[a].cost!=All_Cards[d].cost && All_Cards[b].cost!=All_Cards[c].cost && All_Cards[b].cost!=All_Cards[d].cost && All_Cards[c].cost!=All_Cards[d].cost){
					printf("Player%d find the gold.\n",n);
					Player[n].hand_cards[a]=1;
					Player[n].cnt_hand_card++;
					All_Cards[a].status=1;
				}
				else{
					printf("Player%d find no gold.\n",n);
				}
			}
		}
		n=(n+1)%4;
	}
}
void computer_act(int32_t p, int32_t num){//normal action
	/*print_player_card(p);
	print_player_building(p);*/
	if(num==1){
		int32_t deter=0;
		for(int i=1;i<=110;i++){
			if(i>=43){// >=43 building can't build over 1.
				if(Player[p].building_cards[i].status==1) continue;
			}
			if(Player[p].hand_cards[i]==1 && All_Cards[i].cost<=Player[p].cnt_hand_card-1){
				deter=1;
				Player[p].cnt_hand_card--;
				Player[p].hand_cards[i]=0;
				//building + 1
				Player[p].cnt_have_building+=1;
				Player[p].building_cards[i].status=1;
				for(int j=1;j<=All_Cards[i].cost;j++){
					for(int k=1;k<=110;k++){
						if(Player[p].hand_cards[k]==1){
							All_Cards[k].status=2;
							Player[p].hand_cards[k]=0; Player[p].cnt_hand_card--;
							break;
						}
					}
				}
				break;
			}
		}
		if(!deter) printf("Player%d build nothing.\n",p);
		print_player_card(p);
		print_player_building(p);
	}
	else if (num==2){
		int32_t deter=0,cnt_pro=0;
		for(int i=1;i<=42;i++){
			if(Player[p].building_cards[i].status==1 && Player[p].building_cards[i].cargo==0){
				cnt_pro++;
				deter=1;
				Player[p].building_cards[i].cargo=1;
				uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
				break;
			}
		}
		if(Player[p].building_cards[70].status==1 || Player[p].building_cards[71].status==1 || Player[p].building_cards[72].status==1){
			//Aqueduct
			for(int i=1;i<=42;i++){
				if(Player[p].building_cards[i].status==1 && Player[p].building_cards[i].cargo==0){
					deter=1;
					cnt_pro++;
					Player[p].building_cards[i].cargo=1;
					uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
					break;
				}
			}
		}
		if(cnt_pro>=2){//Well card
			if(Player[p].building_cards[67].status==1 || Player[p].building_cards[68].status==1 || Player[p].building_cards[69].status==1){
				int32_t tmp_p=pick_one_card();
				Player[p].cnt_hand_card++;
				Player[p].hand_cards[tmp_p]=1;
			}
		}
		if(!deter) printf("Player%d produce nothing.\n",p);
	}
	else if (num==3){
		int32_t deter=0,been_sold=0; 
		for(int i=0;i<=42;i++){
			if(Player[p].building_cards[i].cargo==1){
				deter=1;
				Player[p].building_cards[i].cargo=0;
				int32_t cnt_card;
				if(i>=1 && i<=10) cnt_card=Trader_List[LT][1];
				else if(i>=11 && i<=18) cnt_card=Trader_List[LT][2];
				else if(i>=19 && i<=26) cnt_card=Trader_List[LT][3];
				else if(i>=27 && i<=34) cnt_card=Trader_List[LT][4];
				else if(i>=35 && i<=42) cnt_card=Trader_List[LT][5];
				for(int j=0;j<cnt_card;j++){
					Player[p].hand_cards[pick_one_card()]=1;
					Player[p].cnt_hand_card+=1;
				}
				been_sold++;
				break;
			}
		}
		been_sold+=Trading_post(p);
		if(been_sold>=2){
			if(Player[p].building_cards[73].status==1 || Player[p].building_cards[74].status==1 || Player[p].building_cards[75].status==1){
				Player[p].hand_cards[pick_one_card()]=1;
				Player[p].cnt_hand_card++;
			}
		}
		if(!deter) printf("Player%d sold nothing.\n",p);
	}
	else if (num==4){
		int a=pick_one_card(),b=pick_one_card();
		Player[p].hand_cards[a]=1; Player[p].cnt_hand_card++;
		All_Cards[b].status=2;
	}
	else if (num==5) {};
	/*print_player_card(p);
	print_player_building(p);*/
}
void computer_act_pri(int32_t p, int32_t num){//privilege action
	/*print_player_card(p);
	print_player_building(p);*/
	if(num==1){
		int32_t deter=0;
		for(int i=1;i<=110;i++){
			if(i>=43){// >=43 building can't build over 1.
				if(Player[p].building_cards[i].status==1) continue;
			}
			if(Player[p].hand_cards[i]==1 && All_Cards[i].cost-1<=Player[p].cnt_hand_card-1){
				Carpenter(p);
				deter=1;
				Player[p].cnt_hand_card--;
				Player[p].hand_cards[i]=0;
				//building + 1
				Player[p].cnt_have_building+=1;
				Player[p].building_cards[i].status=1;
				for(int j=1;j<=All_Cards[i].cost-1;j++){
					for(int k=1;k<=110;k++){
						if(Player[p].hand_cards[k]==1){
							All_Cards[k].status=2;
							Player[p].hand_cards[k]=0; Player[p].cnt_hand_card--;
							break;
						}
					}
				}
				break;
			}
		}
		Poor_House(p);
		if(!deter) printf("Player%d build nothing.\n",p);
		//print_player_card(p);
		//print_player_building(p);
	}
	else if (num==2){
		int32_t deter=0,cnt_pro=0;
		for(int i=1;i<=42;i++){
			if(Player[p].building_cards[i].status==1 && Player[p].building_cards[i].cargo==0){
				deter=1;
				cnt_pro++;
				Player[p].building_cards[i].cargo=1;
				uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
				break;
			}
		}
		for(int i=1;i<=42;i++){
			if(Player[p].building_cards[i].status==1 && Player[p].building_cards[i].cargo==0){
				deter=1;
				cnt_pro++;
				Player[p].building_cards[i].cargo=1;
				uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
				break;
			}
		}
		if(Player[p].building_cards[70].status==1 || Player[p].building_cards[71].status==1 || Player[p].building_cards[72].status==1){
			//Aqueduct
			for(int i=1;i<=42;i++){
				if(Player[p].building_cards[i].status==1 && Player[p].building_cards[i].cargo==0){
					deter=1;
					cnt_pro++;
					Player[p].building_cards[i].cargo=1;
					uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
					break;
				}
			}
		}
		if(cnt_pro>=2){//Well card
			if(Player[p].building_cards[67].status==1 || Player[p].building_cards[68].status==1 || Player[p].building_cards[69].status==1){
				int32_t tmp_p=pick_one_card();
				Player[p].cnt_hand_card++;
				Player[p].hand_cards[tmp_p]=1;
			}
		}
		if(!deter) printf("Player%d produce nothing.\n",p);
	}
	else if (num==3){
		LT=pick_one_trader_list();
		int32_t deter=0,been_sold=0;
		printf(YEL_BOLD);
		printf("Blue: %d , White: %d , Brown: %d , Beige: %d , Gray: %d\n",Trader_List[LT][1],Trader_List[LT][2],Trader_List[LT][3],Trader_List[LT][4],Trader_List[LT][5]);
		printf(RESET);
		for(int h=0;h<2;h++){
			for(int i=0;i<=42;i++){
				if(Player[p].building_cards[i].cargo==1){
					deter=1;
					Player[p].building_cards[i].cargo=0;
					int32_t cnt_card;
					if(i>=1 && i<=10) cnt_card=Trader_List[LT][1];
					else if(i>=11 && i<=18) cnt_card=Trader_List[LT][2];
					else if(i>=19 && i<=26) cnt_card=Trader_List[LT][3];
					else if(i>=27 && i<=34) cnt_card=Trader_List[LT][4];
					else if(i>=35 && i<=42) cnt_card=Trader_List[LT][5];
					for(int j=0;j<cnt_card;j++){
						Player[p].hand_cards[pick_one_card()]=1;
						Player[p].cnt_hand_card+=1;
					}
					been_sold++;
					break;
				}
			}
		}
		been_sold+=Trading_post(p);
		if(been_sold>=2){
			if(Player[p].building_cards[73].status==1 || Player[p].building_cards[74].status==1 || Player[p].building_cards[75].status==1){
				Player[p].hand_cards[pick_one_card()]=1;
				Player[p].cnt_hand_card++;
			}
		}
		Market_Hall(p);
		if(!deter) printf("Player%d sold nothing.\n",p);
	}
	else if (num==4){
		int a=pick_one_card(),b=pick_one_card(),c=pick_one_card(),d=pick_one_card(),e=pick_one_card();
		Player[p].hand_cards[a]=1; Player[p].cnt_hand_card++;
		All_Cards[b].status=2; All_Cards[c].status=2; All_Cards[d].status=2; All_Cards[e].status=2;
	}
	else if (num==5) {Player[p].hand_cards[pick_one_card()]=1; Player[p].cnt_hand_card++;}
	/*print_player_card(p);
	print_player_building(p);*/
}
uint32_t computer_pick_action_card(void){
	uint32_t a;
	srand(time(NULL));
	while(1){
		a = (rand()%5)+1;
		if(ACT_cards[a]==0){
			ACT_cards[a]=1;
			break;
		}
	}
	return a;
}
int32_t game_over_det=0;
void new_match(uint32_t pg){//4 players each 
	//1: Builder 2: Producer 3: Trader 4: Counciler 5: Prospector
	//for(int i=0;i<=6;i++) ACT_cards[i]=0;
	while(1){//when everyone picked the action card, change governor
		//printf("NOW_pg=%d\n",pg);
		if(Player[1].cnt_have_building>=12 || Player[2].cnt_have_building>=12 || Player[3].cnt_have_building>=12 || Player[4].cnt_have_building>=12){
			//until somone build 12 building
			game_over_det=1;
			break;
		}
		pg_flag++;
		pg=(pg+1)%4;
		if(pg_flag==1) printf("Player%d is the Governor.\n",pg);
		if(pg_flag==5){// every action each people do one thing.
			/*match_flag++;
			if(match_flag==4){//four people picked four action card, so break to change governor
				match_flag=0;
				pg_flag=0;
				break;
			}*/
			pg_flag=1;
			pg+=1;
			for(int i=0;i<=6;i++) ACT_cards[i]=0;
			printf("Player%d is the Governor.\n",pg);
			if(Player[1].cnt_hand_card>7 && Player[1].building_cards[43].status==0 && Player[1].building_cards[44].status==0 && Player[1].building_cards[45].status==0){
				printf("You need to let your hand card down to 7\n");
				printf("Choose %d card(s) to the abandon area.\n",Player[1].cnt_hand_card-7);
				int32_t cnt_amount=Player[1].cnt_hand_card-7;
				for(int j=1;j<=cnt_amount;j++){//abandon the card
					printf("Card%d: ",j);
					int32_t det;
					while(scanf("%d",&det)){
						if(Player[1].hand_cards[det]==1){
							All_Cards[det].status=2;
							Player[1].hand_cards[det]=0; Player[1].cnt_hand_card--;
							break;
						}
						else{
							printf("You don't have this card! Please choose again.\nCard%d: ",j);
							continue;
						}
					}
				}
			}
			else if(Player[1].cnt_hand_card>12 && (Player[1].building_cards[43].status==1 || Player[1].building_cards[44].status==1 || Player[1].building_cards[45].status==1)){
				printf("You need to let your hand card down to 12\n");
				printf("Choose %d card(s) to the abandon area.\n",Player[1].cnt_hand_card-12);
				int32_t cnt_amount=Player[1].cnt_hand_card-12;
				for(int j=1;j<=cnt_amount;j++){//abandon the card
					printf("Card%d: ",j);
					int32_t det;
					while(scanf("%d",&det)){
						if(Player[1].hand_cards[det]==1){
							All_Cards[det].status=2;
							Player[1].hand_cards[det]=0; Player[1].cnt_hand_card--;
							break;
						}
						else{
							printf("You don't have this card! Please choose again.\nCard%d: ",j);
							continue;
						}
					}
				}
			}
			for(int pl=2;pl<=4;pl++){
				if(Player[pl].cnt_hand_card>7 && Player[pl].building_cards[43].status==0 && Player[pl].building_cards[44].status==0 && Player[pl].building_cards[45].status==0){
					int32_t cnt_amount=Player[1].cnt_hand_card-7;
					for(int j=1;j<=cnt_amount;j++){//abandon the card
						for(int i=1;i<110;i++){
							if(Player[pl].hand_cards[i]==1){
								All_Cards[i].status=2;
								Player[pl].hand_cards[i]=0; Player[pl].cnt_hand_card--;
								break;
							}
						}
					}
					printf("Player%d down the amount of hand cards to 7.\n",pl);
				}
				else if(Player[pl].cnt_hand_card>12 && (Player[pl].building_cards[43].status==1 || Player[pl].building_cards[44].status==1 || Player[pl].building_cards[45].status==1)){
					int32_t cnt_amount=Player[1].cnt_hand_card-12;
					for(int j=1;j<=cnt_amount;j++){//abandon the card
						for(int i=1;i<110;i++){
							if(Player[pl].hand_cards[i]==1){
								All_Cards[i].status=2;
								Player[pl].hand_cards[i]=0; Player[pl].cnt_hand_card--;
								break;
							}
						}
					}
					printf("Player%d down the amount of hand cards to 12.\n",pl);
				}
			}
			if(Player[1].building_cards[46].status==1 || Player[1].building_cards[47].status==1 || Player[1].building_cards[48].status==1){
				if(Player[1].cnt_hand_card>0){
					printf("You have Chapel building and your hand card is not equal to 0,\nDo you want spend one hand card on the Chapel?\nEnter 1 for Yes, 0 for No: ");
					int32_t dd,Ch_num;
					while(scanf("%d",&dd)){
						if(dd==1){
							printf("Please enter the card number: ");
							while(scanf("%d",&Ch_num)){
								if(Player[1].hand_cards[Ch_num]==0){
									printf("You don't have this card.\nPlease enter the card number: ");
									continue;
								}
								else{
									Player[1].cnt_hand_card--;
									Player[1].hand_cards[Ch_num]=0;
									Player[1].Chapel_vp++;
									break;
								}
							}
						}
						else if(dd==0) continue;
						else printf("Wrong Input. Please enter 1 for Yes or 0 for No: ");
					}
				}
			}
		}
		
		/*printf("NOW_pg=%d\n",pg);
		printf("NOW_match=%d\n",match_flag);
		printf("NOW_pg_flag=%d\n",pg_flag);*/
		/*for(int i=1;i<=5;i++){
			printf("%d ",ACT_cards[i]);
		}
		printf("\n");*/
		if(pg==1){//player1 pick the action card
			pick_action_card();
			choose_number();
			int32_t num;
			while(scanf("%d",&num)){
				if(num==1) print_table();
				else if(num==2) print_number_list_all_cards();
				else if(num==3) break;
				choose_number();
			}
			if(Player[1].action_card==1){
				printf("Please select a card to build (Enter 0 to build nothing.)) : ");
				int32_t c;
				while(scanf("%d",&c)){
					if(c==0){
						printf("You build nothing.\n");
						break;
					}
					if(Player[1].building_cards[c].status==1) { // >=43 building can't build over 1.
						printf("You can't build the same category of special building.\n");
						continue;
					} 
					int Smithy_dis=0,Quarry_dis=0,Lib_dis=0;
					if(Player[1].hand_cards[c]==1){
						if(c<=42){ //Smithy
							if(Player[1].building_cards[49].status==1 || Player[1].building_cards[50].status==1 || Player[1].building_cards[51].status==1) Smithy_dis=1;
						}
						else if(c>=43){ //Quarry
							if(Player[1].building_cards[64].status==1 || Player[1].building_cards[65].status==1 || Player[1].building_cards[66].status==1) Quarry_dis=1;
						}
						if(Player[1].building_cards[91].status==1 || Player[1].building_cards[92].status==1 || Player[1].building_cards[93].status==1){
							Lib_dis=1;// Library for Builder
						}
					}
					int32_t Cost=All_Cards[c].cost-1-Smithy_dis-Quarry_dis-Lib_dis;
					if(Player[1].hand_cards[c]==1 && Player[1].cnt_hand_card-1 < Cost)
						printf("You are too poor to pay for this building. Please choose again.\n");
					else if(Player[1].hand_cards[c]==1 && Player[1].cnt_hand_card-1 >= Cost){
						Carpenter(1);
						Player[1].cnt_hand_card--;
						Player[1].hand_cards[c]=0;
						//building + 1
						Player[1].cnt_have_building+=1;
						Player[1].building_cards[c].status=1;
						if(Cost<=0) break;
						abandon_card(Cost);//cuz you are Builder
						break;
					}
					else if(Player[1].hand_cards[c]==0) printf("You don't have this card. Please choose again.\n");
					printf("Please select a card to build (Enter 0 to build nothing.)) : ");
				}
				Poor_House(1);
				computer_act(2,1);
				computer_act(3,1);
				computer_act(4,1);
			}
			else if(Player[1].action_card==2){
				int cnt_factory_tot=0,c1,c2;
				for(int i=0;i<=42;i++)
					if(Player[1].building_cards[i].status==1 && Player[1].building_cards[i].cargo==0) cnt_factory_tot++;
				if(cnt_factory_tot>=2){
					printf("You can choose 2 buildings to produce the cargo.\n");
					printf("Enter the number of cards:\nCard1: ");
					while(scanf("%d",&c1)){
						if(Player[1].building_cards[c1].status=1 && Player[1].building_cards[c1].cargo==0 && c1<=42){
							Player[1].building_cards[c1].cargo=1;
							uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
							break;
						}
						else printf("Invalid card. Please choose again.\nCard1: ");
					}
					printf("Card2: ");
					while(scanf("%d",&c2)){
						if(Player[1].building_cards[c2].status=1 && Player[1].building_cards[c2].cargo==0 && c2<=42){
							Player[1].building_cards[c2].cargo=1;
							uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
							break;
						}
						else printf("Invalid card. Please choose again.\nCard2: ");
					}
					printf("You produce 2 cargo.\n");
					if(Player[1].building_cards[70].status==1 || Player[1].building_cards[71].status==1 || Player[1].building_cards[72].status==1){
						//Aqueduct
						if(cnt_factory_tot>=3){
							printf("You can choose one more buildings to produce the cargo cuz you have Aqueduct.\n");
							printf("Enter the number of cards:\nCard: ");
							while(scanf("%d",&c1)){
								if(Player[1].building_cards[c1].status=1 && Player[1].building_cards[c1].cargo==0 && c1<=42){
									Player[1].building_cards[c1].cargo=1;
									uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
									break;
								}
								else printf("Invalid card. Please choose again.\nCard: ");
							}
						}
					}
					if(Player[1].building_cards[91].status==1 || Player[1].building_cards[92].status==1 || Player[1].building_cards[93].status==1){
						//Library
						if(cnt_factory_tot>=4){
							printf("You can choose one more buildings to produce the cargo cuz you have Library.\n");
							printf("Enter the number of cards:\nCard: ");
							while(scanf("%d",&c1)){
								if(Player[1].building_cards[c1].status=1 && Player[1].building_cards[c1].cargo==0 && c1<=42){
									Player[1].building_cards[c1].cargo=1;
									uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
									break;
								}
								else printf("Invalid card. Please choose again.\nCard: ");
							}
						}
					}
					if(Player[1].building_cards[67].status==1 || Player[1].building_cards[68].status==1 || Player[1].building_cards[69].status==1){
						//Well card
						int32_t tmp_p=pick_one_card();
						Player[1].cnt_hand_card++;
						Player[1].hand_cards[tmp_p]=1;
					}
				}
				else if(cnt_factory_tot==1){
					for(int i=0;i<=42;i++){
						if(Player[1].building_cards[i].status==1 && Player[1].building_cards[i].cargo==0){
							Player[1].building_cards[i].cargo=1;
							uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
							break;
						}
					}
					printf("You produce 1 cargo.\n");
				}
				else if(cnt_factory_tot<1){
					printf("You produce nothing cuz you don't have empty factory or any factory.\n");
				}
				computer_act(2,2);
				computer_act(3,2);
				computer_act(4,2);
			}
			else if(Player[1].action_card==3){
				LT=pick_one_trader_list();
				printf(YEL_BOLD);
				printf("Blue: %d , White: %d , Brown: %d , Beige: %d , Gray: %d\n",Trader_List[LT][1],Trader_List[LT][2],Trader_List[LT][3],Trader_List[LT][4],Trader_List[LT][5]);
				printf(RESET);
				int32_t cnt_cargo_tot=0,_deter=0,c1,been_sold=0;
				for(int i=0;i<=42;i++)
					if(Player[1].building_cards[i].status==1 && Player[1].building_cards[i].cargo==1) cnt_cargo_tot++;
				if(cnt_cargo_tot>=2){
					printf("You have %d cargo to sell. Please choose any two to sell.(Enter 0 to sell nothing.)\n",cnt_cargo_tot);
					for(int h=1;h<=2;h++)
					{
						printf("Card%d: ",h);
						while(scanf("%d",&c1)){
							if(c1==0 && h==1){
								_deter=1;
								break;
							}
							if(Player[1].building_cards[c1].status==1 && Player[1].building_cards[c1].cargo==1 && c1<=42){
								Player[1].building_cards[c1].cargo=0;
								int32_t cnt_card=0;
								if(c1>=1 && c1<=10) cnt_card+=Trader_List[LT][1];
								else if(c1>=11 && c1<=18) cnt_card+=Trader_List[LT][2];
								else if(c1>=19 && c1<=26) cnt_card+=Trader_List[LT][3];
								else if(c1>=27 && c1<=34) cnt_card+=Trader_List[LT][4];
								else if(c1>=35 && c1<=42) cnt_card+=Trader_List[LT][5];
								for(int j=0;j<cnt_card;j++){
									Player[1].hand_cards[pick_one_card()]=1;
									Player[1].cnt_hand_card+=1;
								}
								been_sold++;
								break;
							}
							else{
								printf("Invalid card. Please choose again.\nCard: ");
							}
						}
						if(_deter){
							printf("You sold nothing.\n");
						}
					}
					_deter=0;
					if(cnt_cargo_tot>=3){
						if(Player[1].building_cards[79].status==1 || Player[1].building_cards[80].status==1 || Player[1].building_cards[81].status==1){
							//Trading_post
							printf("You have Trading Post, you can sold one more product.\nPlease choose one to sell (Enter the card number. Enter 0 to sell nothing): ");
							while(scanf("%d",&c1)){
								if(c1==0){
									_deter=1;
									break;
								}
								if(Player[1].building_cards[c1].status==1 && Player[1].building_cards[c1].cargo==1 && c1<=42){
									Player[1].building_cards[c1].cargo=0;
									int32_t cnt_card=0;
									if(c1>=1 && c1<=10) cnt_card+=Trader_List[LT][1];
									else if(c1>=11 && c1<=18) cnt_card+=Trader_List[LT][2];
									else if(c1>=19 && c1<=26) cnt_card+=Trader_List[LT][3];
									else if(c1>=27 && c1<=34) cnt_card+=Trader_List[LT][4];
									else if(c1>=35 && c1<=42) cnt_card+=Trader_List[LT][5];
									for(int j=0;j<cnt_card;j++){
										Player[1].hand_cards[pick_one_card()]=1;
										Player[1].cnt_hand_card+=1;
									}
									been_sold++;
									break;
								}
								else{
									printf("Invalid card. Please choose again.\nCard: ");
								}
							}
							if(_deter){
								printf("You sold nothing.\n");
							}
						}
					}
					if(cnt_cargo_tot>=4){
						if(Player[1].building_cards[91].status==1 || Player[1].building_cards[92].status==1 || Player[1].building_cards[93].status==1){
							//Library
							printf("You have Library, you can sold one more product.\nPlease choose one to sell (Enter the card number. Enter 0 to sell nothing): ");
							while(scanf("%d",&c1)){
								if(c1==0){
									_deter=1;
									break;
								}
								if(Player[1].building_cards[c1].status==1 && Player[1].building_cards[c1].cargo==1 && c1<=42){
									Player[1].building_cards[c1].cargo=0;
									int32_t cnt_card=0;
									if(c1>=1 && c1<=10) cnt_card+=Trader_List[LT][1];
									else if(c1>=11 && c1<=18) cnt_card+=Trader_List[LT][2];
									else if(c1>=19 && c1<=26) cnt_card+=Trader_List[LT][3];
									else if(c1>=27 && c1<=34) cnt_card+=Trader_List[LT][4];
									else if(c1>=35 && c1<=42) cnt_card+=Trader_List[LT][5];
									for(int j=0;j<cnt_card;j++){
										Player[1].hand_cards[pick_one_card()]=1;
										Player[1].cnt_hand_card+=1;
									}
									been_sold++;
									break;
								}
								else{
									printf("Invalid card. Please choose again.\nCard: ");
								}
							}
							if(_deter){
								printf("You sold nothing.\n");
							}
						}
					}
					if(been_sold>=2){
						if(Player[1].building_cards[73].status==1 || Player[1].building_cards[74].status==1 || Player[1].building_cards[75].status==1){
							printf("You sold at least 2 products and you have Market Stand, so you pick one card to be your hand card.\n");
							Player[1].cnt_hand_card++;
							Player[1].hand_cards[pick_one_card()]=1;
						}
					}
				}
				else if(cnt_cargo_tot==1){
					printf("You only have 1 cargo to sell.(Enter card number to sell the cargo, 0 for selling nothing.)\n");
					printf("Enter the number: ");
					while(scanf("%d",&c1)){
						if(c1==0){
							printf("You sold nothing.\n");
							break;
						}
						if(Player[1].building_cards[c1].status==1 && Player[1].building_cards[c1].cargo==1 && c1<=42){
							Player[1].building_cards[c1].cargo=0;
							int32_t cnt_card=0;
							if(c1>=1 && c1<=10) cnt_card+=Trader_List[LT][1];
							else if(c1>=11 && c1<=18) cnt_card+=Trader_List[LT][2];
							else if(c1>=19 && c1<=26) cnt_card+=Trader_List[LT][3];
							else if(c1>=27 && c1<=34) cnt_card+=Trader_List[LT][4];
							else if(c1>=35 && c1<=42) cnt_card+=Trader_List[LT][5];
							for(int j=0;j<cnt_card;j++){
								Player[1].hand_cards[pick_one_card()]=1;
								Player[1].cnt_hand_card+=1;
							}
							break;
						}
						else{
							printf("Invalid card. Please choose again.\nEnter the number: ");
						}
					}
				}
				else if(cnt_cargo_tot<1){
					printf("You don't have any cargo to sell.\n");
				}
				Market_Hall(1);
				computer_act(2,3);
				computer_act(3,3);
				computer_act(4,3);
			}
			else if(Player[1].action_card==4){
				if(Player[1].building_cards[91].status==1 || Player[1].building_cards[92].status==1 || Player[1].building_cards[93].status==1){
					//Library
					int det,cc[10]={0},tmp;
					for(int i=1;i<=8;i++){
						cc[i]=pick_one_card();
						printf("Card%d: %d\n",i,cc[i]);
					}
					
					printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~8.)\n");
					while(scanf("%d",&det)){
						int32_t fl=0;
						for(int i=1;i<=8;i++){
							if(det==cc[i]){
								fl=1;
								break;
							}
						}
						if(!fl){
							printf("Please choose one card of these eight cards! Please choose again.\n");
							printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~8.)\n");
							continue;
						}
						else{
							for(int i=1;i<=8;i++){
								All_Cards[cc[i]].status=2;
							}
							All_Cards[det].status=1;
							Player[1].hand_cards[det]=1; Player[1].cnt_hand_card++;
							tmp=det;
							break;
						}
					}
					if(Player[1].building_cards[85].status==1 || Player[1].building_cards[86].status==1 || Player[1].building_cards[87].status==1){
						//Prefecture
						printf("You have Prefecture. You can pick one more card.\n");
						printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~8.)\n");
						while(scanf("%d",&det)){
							if(det==tmp){
								printf("You have chosen it before! Please choose again.\n");
								printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~8.)\n");
								continue;
							}
							int32_t fl=0;
							for(int i=1;i<=8;i++){
								if(det==cc[i]){
									fl=1;
									break;
								}
							}
							if(!fl){
								printf("Please choose one card of these eight cards! Please choose again.\n");
								printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~8.)\n");
								continue;
							}
							else{
								All_Cards[det].status=1;
								Player[1].hand_cards[det]=1; Player[1].cnt_hand_card++;
								tmp=det;
								break;
							}
						}
					}
				}
				else{
					int det,cc[10]={0},tmp;
					for(int i=1;i<=5;i++){
						cc[i]=pick_one_card();
						printf("Card%d: %d\n",i,cc[i]);
					}
					printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~5.)\n");
					while(scanf("%d",&det)){
						int32_t fl=0;
						for(int i=1;i<=5;i++){
							if(det==cc[i]){
								fl=1;
								break;
							}
						}
						if(!fl){
							printf("Please choose one card of these five cards! Please choose again.\n");
							printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~5.)\n");
							continue;
						}
						else{
							for(int i=1;i<=8;i++){
								All_Cards[cc[i]].status=2;
							}
							All_Cards[det].status=1;
							Player[1].hand_cards[det]=1; Player[1].cnt_hand_card++;
							tmp=det;
							break;
						}
					}
					if(Player[1].building_cards[85].status==1 || Player[1].building_cards[86].status==1 || Player[1].building_cards[87].status==1){
						//Prefecture
						printf("You have Prefecture. You can pick one more card.\n");
						printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~5.)\n");
						while(scanf("%d",&det)){
							if(det==tmp){
								printf("You have chosen it before! Please choose again.\n");
								printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~5.)\n");
								continue;
							}
							int32_t fl=0;
							for(int i=1;i<=5;i++){
								if(det==cc[i]){
									fl=1;
									break;
								}
							}
							if(!fl){
								printf("Please choose one card of these five cards! Please choose again.\n");
								printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~5.)\n");
								continue;
							}
							else{
								All_Cards[det].status=1;
								Player[1].hand_cards[det]=1; Player[1].cnt_hand_card++;
								tmp=det;
								break;
							}
						}
					}	
				}
				computer_act(2,4);
				computer_act(3,4);
				computer_act(4,4);
			}
			else if(Player[1].action_card==5){
				Gold_Mine(pg);
				if(Player[1].building_cards[91].status==1 || Player[1].building_cards[92].status==1 || Player[1].building_cards[93].status==1){
					Player[1].hand_cards[pick_one_card()]=1; Player[1].cnt_hand_card++;
					Player[1].hand_cards[pick_one_card()]=1; Player[1].cnt_hand_card++;
				}
				else Player[1].hand_cards[pick_one_card()]=1; Player[1].cnt_hand_card++;
			}
		}
		else if(pg==2){//player2 pick the action card
			//printf("HHi\n");
			uint32_t com_ac=computer_pick_action_card();
			printf("Player2 is ");
			if(com_ac==1) printf("Builder\n");
			else if(com_ac==2) printf("Producer\n");
			else if(com_ac==3) printf("Trader\n");
			else if(com_ac==4) printf("Counciler\n");
			else if(com_ac==5) printf("Prospector\n"); 
			computer_act_pri(2,com_ac);
			computer_act(3,com_ac);
			computer_act(4,com_ac);
			// your action
			choose_number();
			int32_t num;
			while(scanf("%d",&num)){
				if(num==1) print_table();
				else if(num==2) print_number_list_all_cards();
				else if(num==3) break;
				choose_number();
			}
			if(com_ac==1){// normal action for building somthing
				printf("Please select a card to build (Enter 0 to build nothing.)) : ");
				int32_t c;
				while(scanf("%d",&c)){
					if(c==0){
						printf("You build nothing.\n");
						break;
					}
					if(Player[1].building_cards[c].status==1) { // >=43 building can't build over 1.
						printf("You can't build the same category of special building.\n");
						continue;
					} 
					if(Player[1].hand_cards[c]==1 && Player[1].cnt_hand_card-1 < All_Cards[c].cost)
						printf("You are too poor to pay for this building. Please choose again.\n");
					else if(Player[1].hand_cards[c]==1 && Player[1].cnt_hand_card-1 >= All_Cards[c].cost){
						Player[1].cnt_hand_card--;
						Player[1].hand_cards[c]=0;
						//building + 1
						Player[1].cnt_have_building+=1;
						Player[1].building_cards[c].status=1;
						//if(All_Cards[c].cost-1<=0) break;
						abandon_card(All_Cards[c].cost);
						break;
					}
					else if(Player[1].hand_cards[c]==0) printf("You don't have this card. Please choose again.\n");
					printf("Please select a card to build (Enter 0 to build nothing.)) : ");
				}
			}
			else if(com_ac==2){// normal action for producing the product
				int cnt_factory_tot=0,c1,c2;
				for(int i=0;i<=42;i++)
					if(Player[1].building_cards[i].status==1 && Player[1].building_cards[i].cargo==0) cnt_factory_tot++;
				if(cnt_factory_tot>=2){
					printf("You can choose 1 buildings to produce the cargo.\n");
					printf("Enter the number of cards:\nCard: ");
					while(scanf("%d",&c1)){
						if(Player[1].building_cards[c1].status=1 && Player[1].building_cards[c1].cargo==0 && c1<=42){
							Player[1].building_cards[c1].cargo=1;
							uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
							break;
						}
						else printf("Invalid card. Please choose again.\nCard: ");
					}
					printf("You produce 1 cargo.\n");
					if(Player[1].building_cards[70].status==1 || Player[1].building_cards[71].status==1 || Player[1].building_cards[72].status==1){
						//Aqueduct
						printf("You can choose one more buildings to produce the cargo cuz you have Aqueduct.\n");
						printf("Enter the number of cards:\nCard2: ");
						while(scanf("%d",&c1)){
							if(Player[1].building_cards[c1].status=1 && Player[1].building_cards[c1].cargo==0 && c1<=42){
								Player[1].building_cards[c1].cargo=1;
								uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
								break;
							}
							else printf("Invalid card. Please choose again.\nCard2: ");
						}
					}
					if(Player[1].building_cards[67].status==1 || Player[1].building_cards[68].status==1 || Player[1].building_cards[69].status==1){
						//Well card
						int32_t tmp_p=pick_one_card();
						Player[1].cnt_hand_card++;
						Player[1].hand_cards[tmp_p]=1;
					}
				}
				else if(cnt_factory_tot==1){
					for(int i=0;i<=42;i++){
						if(Player[1].building_cards[i].status==1 && Player[1].building_cards[i].cargo==0){
							Player[1].building_cards[i].cargo=1;
							uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
							break;
						}
					}
					printf("You produce 1 cargo.\n");
				}
				else if(cnt_factory_tot<1){
					printf("You produce nothing cuz you don't have empty factory or any factory.\n");
				}
			}
			else if(com_ac==3){// normal action for selling product
				int32_t cnt_cargo_tot=0,_deter=0,c1,been_sold=0;
				for(int i=0;i<=42;i++)
					if(Player[1].building_cards[i].status==1 && Player[1].building_cards[i].cargo==1) cnt_cargo_tot++;
				if(cnt_cargo_tot>=1){
					printf("You have %d cargo to sell. Please choose any one to sell.(Enter 0 to sell nothing.)\n",cnt_cargo_tot);
					printf("Card: ");
					while(scanf("%d",&c1)){
						if(c1==0){
							_deter=1;
							break;
						}
						if(Player[1].building_cards[c1].status==1 && Player[1].building_cards[c1].cargo==1 && c1<=42){
							Player[1].building_cards[c1].cargo=0;
							int32_t cnt_card=0;
							if(c1>=1 && c1<=10) cnt_card+=Trader_List[LT][1];
							else if(c1>=11 && c1<=18) cnt_card+=Trader_List[LT][2];
							else if(c1>=19 && c1<=26) cnt_card+=Trader_List[LT][3];
							else if(c1>=27 && c1<=34) cnt_card+=Trader_List[LT][4];
							else if(c1>=35 && c1<=42) cnt_card+=Trader_List[LT][5];
							for(int j=0;j<cnt_card;j++){
								Player[1].hand_cards[pick_one_card()]=1;
								Player[1].cnt_hand_card+=1;
							}
							been_sold++;
							break;
						}
						else{
							printf("Invalid card. Please choose again.\nCard: ");
						}
					}
					if(_deter){
						printf("You sold nothing.\n");
					}
					_deter=0;
					if(cnt_cargo_tot>=2){
						if(Player[1].building_cards[79].status==1 || Player[1].building_cards[80].status==1 || Player[1].building_cards[81].status==1){
							//Trading_post
							printf("You have Trading Post, you can sold one more product.\nPlease choose one to sell (Enter the card number. Enter 0 to sell nothing.): ");
							while(scanf("%d",&c1)){
								if(c1==0){
									_deter=1;
									break;
								}
								if(Player[1].building_cards[c1].status==1 && Player[1].building_cards[c1].cargo==1 && c1<=42){
									Player[1].building_cards[c1].cargo=0;
									int32_t cnt_card=0;
									if(c1>=1 && c1<=10) cnt_card+=Trader_List[LT][1];
									else if(c1>=11 && c1<=18) cnt_card+=Trader_List[LT][2];
									else if(c1>=19 && c1<=26) cnt_card+=Trader_List[LT][3];
									else if(c1>=27 && c1<=34) cnt_card+=Trader_List[LT][4];
									else if(c1>=35 && c1<=42) cnt_card+=Trader_List[LT][5];
									for(int j=0;j<cnt_card;j++){
										Player[1].hand_cards[pick_one_card()]=1;
										Player[1].cnt_hand_card+=1;
									}
									been_sold++;
									break;
								}
								else{
									printf("Invalid card. Please choose again.\nCard: ");
								}
							}
							if(_deter){
								printf("You sold nothing.\n");
							}
						}
					}
					if(been_sold>=2){
						if(Player[1].building_cards[73].status==1 || Player[1].building_cards[74].status==1 || Player[1].building_cards[75].status==1){
							printf("You sold at least 2 products and you have Market Stand, so you pick one card to be your hand card.\n");
							Player[1].cnt_hand_card++;
							Player[1].hand_cards[pick_one_card()]=1;
						}
					}
				}
				else if(cnt_cargo_tot<1){
					printf("You don't have any cargo to sell.\n");
				}
			}
			else if(com_ac==4){// normal action for pick one of two card
				int det,a=pick_one_card(),b=pick_one_card();
				printf("Card1: %d\n",a);
				printf("Card2: %d\n",b);
				printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~2.)\n");
				while(scanf("%d",&det)){
					if(det==a || det==b){
						All_Cards[a].status=2; All_Cards[b].status=2; All_Cards[det].status=1;
						Player[1].hand_cards[det]=1; Player[1].cnt_hand_card++;
						break;
					}
					else{
						printf("Please choose one card of these two cards! Please choose again.\n");
						printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~2.)\n");
						continue;
					}
				}
			}
			else if(com_ac==5){// normal action for nothing
				Gold_Mine(pg);
			}
		}
		else if(pg==3){//player3 pick the action card
		//printf("HHi\n");
			uint32_t com_ac=computer_pick_action_card();
			printf("Player3 is ");
			if(com_ac==1) printf("Builder\n");
			else if(com_ac==2) printf("Producer\n");
			else if(com_ac==3) printf("Trader\n");
			else if(com_ac==4) printf("Counciler\n");
			else if(com_ac==5) printf("Prospector\n"); 
			computer_act_pri(3,com_ac);
			computer_act(4,com_ac);
			// your action
			choose_number();
			int32_t num;
			while(scanf("%d",&num)){
				if(num==1) print_table();
				else if(num==2) print_number_list_all_cards();
				else if(num==3) break;
				choose_number();
			}
			if(com_ac==1){// normal action for building somthing
				printf("Please select a card to build (Enter 0 to build nothing.)) : ");
				int32_t c;
				while(scanf("%d",&c)){
					if(c==0){
						printf("You build nothing.\n");
						break;
					}
					if(Player[1].building_cards[c].status==1) { // >=43 building can't build over 1.
						printf("You can't build the same category of special building.\n");
						continue;
					} 
					if(Player[1].hand_cards[c]==1 && Player[1].cnt_hand_card-1 < All_Cards[c].cost)
						printf("You are too poor to pay for this building. Please choose again.\n");
					else if(Player[1].hand_cards[c]==1 && Player[1].cnt_hand_card-1 >= All_Cards[c].cost){
						Player[1].cnt_hand_card--;
						Player[1].hand_cards[c]=0;
						//building + 1
						Player[1].cnt_have_building+=1;
						Player[1].building_cards[c].status=1;
						//if(All_Cards[c].cost-1<=0) break;
						abandon_card(All_Cards[c].cost);
						break;
					}
					else if(Player[1].hand_cards[c]==0) printf("You don't have this card. Please choose again.\n");
					printf("Please select a card to build (Enter 0 to build nothing.)) : ");
				}
			}
			else if(com_ac==2){// normal action for producing the product
				int cnt_factory_tot=0,c1,c2;
				for(int i=0;i<=42;i++)
					if(Player[1].building_cards[i].status==1 && Player[1].building_cards[i].cargo==0) cnt_factory_tot++;
				if(cnt_factory_tot>=2){
					printf("You can choose 1 buildings to produce the cargo.\n");
					printf("Enter the number of cards:\nCard: ");
					while(scanf("%d",&c1)){
						if(Player[1].building_cards[c1].status=1 && Player[1].building_cards[c1].cargo==0 && c1<=42){
							Player[1].building_cards[c1].cargo=1;
							uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
							break;
						}
						else printf("Invalid card. Please choose again.\nCard: ");
					}
					printf("You produce 1 cargo.\n");
					if(Player[1].building_cards[70].status==1 || Player[1].building_cards[71].status==1 || Player[1].building_cards[72].status==1){
						//Aqueduct
						printf("You can choose one more buildings to produce the cargo cuz you have Aqueduct.\n");
						printf("Enter the number of cards:\nCard2: ");
						while(scanf("%d",&c1)){
							if(Player[1].building_cards[c1].status=1 && Player[1].building_cards[c1].cargo==0 && c1<=42){
								Player[1].building_cards[c1].cargo=1;
								uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
								break;
							}
							else printf("Invalid card. Please choose again.\nCard2: ");
						}
					}
					if(Player[1].building_cards[67].status==1 || Player[1].building_cards[68].status==1 || Player[1].building_cards[69].status==1){
						//Well card
						int32_t tmp_p=pick_one_card();
						Player[1].cnt_hand_card++;
						Player[1].hand_cards[tmp_p]=1;
					}
				}
				else if(cnt_factory_tot==1){
					for(int i=0;i<=42;i++){
						if(Player[1].building_cards[i].status==1 && Player[1].building_cards[i].cargo==0){
							Player[1].building_cards[i].cargo=1;
							uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
							break;
						}
					}
					printf("You produce 1 cargo.\n");
				}
				else if(cnt_factory_tot<1){
					printf("You produce nothing cuz you don't have empty factory or any factory.\n");
				}
			}
			else if(com_ac==3){// normal action for selling product
				int32_t cnt_cargo_tot=0,_deter=0,c1,been_sold=0;
				for(int i=0;i<=42;i++)
					if(Player[1].building_cards[i].status==1 && Player[1].building_cards[i].cargo==1) cnt_cargo_tot++;
				if(cnt_cargo_tot>=1){
					printf("You have %d cargo to sell. Please choose any one to sell.(Enter 0 to sell nothing.)\n",cnt_cargo_tot);
					printf("Card: ");
					while(scanf("%d",&c1)){
						if(c1==0){
							_deter=1;
							break;
						}
						if(Player[1].building_cards[c1].status==1 && Player[1].building_cards[c1].cargo==1 && c1<=42){
							Player[1].building_cards[c1].cargo=0;
							int32_t cnt_card=0;
							if(c1>=1 && c1<=10) cnt_card+=Trader_List[LT][1];
							else if(c1>=11 && c1<=18) cnt_card+=Trader_List[LT][2];
							else if(c1>=19 && c1<=26) cnt_card+=Trader_List[LT][3];
							else if(c1>=27 && c1<=34) cnt_card+=Trader_List[LT][4];
							else if(c1>=35 && c1<=42) cnt_card+=Trader_List[LT][5];
							for(int j=0;j<cnt_card;j++){
								Player[1].hand_cards[pick_one_card()]=1;
								Player[1].cnt_hand_card+=1;
							}
							been_sold++;
							break;
						}
						else{
							printf("Invalid card. Please choose again.\nCard: ");
						}
					}
					if(_deter){
						printf("You sold nothing.\n");
					}
					_deter=0;
					if(cnt_cargo_tot>=2){
						if(Player[1].building_cards[79].status==1 || Player[1].building_cards[80].status==1 || Player[1].building_cards[81].status==1){
							//Trading_post
							printf("You have Trading Post, you can sold one more product.\nPlease choose one to sell (Enter the card number. Enter 0 to sell nothing.): ");
							while(scanf("%d",&c1)){
								if(c1==0){
									_deter=1;
									break;
								}
								if(Player[1].building_cards[c1].status==1 && Player[1].building_cards[c1].cargo==1 && c1<=42){
									Player[1].building_cards[c1].cargo=0;
									int32_t cnt_card=0;
									if(c1>=1 && c1<=10) cnt_card+=Trader_List[LT][1];
									else if(c1>=11 && c1<=18) cnt_card+=Trader_List[LT][2];
									else if(c1>=19 && c1<=26) cnt_card+=Trader_List[LT][3];
									else if(c1>=27 && c1<=34) cnt_card+=Trader_List[LT][4];
									else if(c1>=35 && c1<=42) cnt_card+=Trader_List[LT][5];
									for(int j=0;j<cnt_card;j++){
										Player[1].hand_cards[pick_one_card()]=1;
										Player[1].cnt_hand_card+=1;
									}
									been_sold++;
									break;
								}
								else{
									printf("Invalid card. Please choose again.\nCard: ");
								}
							}
							if(_deter){
								printf("You sold nothing.\n");
							}
						}
					}
					if(been_sold>=2){
						if(Player[1].building_cards[73].status==1 || Player[1].building_cards[74].status==1 || Player[1].building_cards[75].status==1){
							printf("You sold at least 2 products and you have Market Stand, so you pick one card to be your hand card.\n");
							Player[1].cnt_hand_card++;
							Player[1].hand_cards[pick_one_card()]=1;
						}
					}
				}
				else if(cnt_cargo_tot<1){
					printf("You don't have any cargo to sell.\n");
				}
			}
			else if(com_ac==4){// normal action for pick one of two card
				int det,a=pick_one_card(),b=pick_one_card();
				printf("Card1: %d\n",a);
				printf("Card2: %d\n",b);
				printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~2.)\n");
				while(scanf("%d",&det)){
					if(det==a || det==b){
						All_Cards[a].status=2; All_Cards[b].status=2; All_Cards[det].status=1;
						Player[1].hand_cards[det]=1; Player[1].cnt_hand_card++;
						break;
					}
					else{
						printf("Please choose one card of these two cards! Please choose again.\n");
						printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~2.)\n");
						continue;
					}
				}
			}
			else if(com_ac==5){// normal action for nothing
				Gold_Mine(pg);
			}
			computer_act(2,com_ac);
		}
		else if(pg==0 || pg==4){//player4 pick the action card
		//printf("HHi\n");
			uint32_t com_ac=computer_pick_action_card();
			printf("Player4 is ");
			if(com_ac==1) printf("Builder\n");
			else if(com_ac==2) printf("Producer\n");
			else if(com_ac==3) printf("Trader\n");
			else if(com_ac==4) printf("Counciler\n");
			else if(com_ac==5) printf("Prospector\n"); 
			computer_act_pri(4,com_ac);
			// your action
			choose_number();
			int32_t num;
			while(scanf("%d",&num)){
				if(num==1) print_table();
				else if(num==2) print_number_list_all_cards();
				else if(num==3) break;
				choose_number();
			}
			if(com_ac==1){// normal action for building somthing
				printf("Please select a card to build (Enter 0 to build nothing.)) : ");
				int32_t c;
				while(scanf("%d",&c)){
					if(c==0){
						printf("You build nothing.\n");
						break;
					}
					if(Player[1].building_cards[c].status==1) { // >=43 building can't build over 1.
						printf("You can't build the same category of special building.\n");
						continue;
					} 
					if(Player[1].hand_cards[c]==1 && Player[1].cnt_hand_card-1 < All_Cards[c].cost)
						printf("You are too poor to pay for this building. Please choose again.\n");
					else if(Player[1].hand_cards[c]==1 && Player[1].cnt_hand_card-1 >= All_Cards[c].cost){
						Player[1].cnt_hand_card--;
						Player[1].hand_cards[c]=0;
						//building + 1
						Player[1].cnt_have_building+=1;
						Player[1].building_cards[c].status=1;
						//if(All_Cards[c].cost-1<=0) break;
						abandon_card(All_Cards[c].cost);
						break;
					}
					else if(Player[1].hand_cards[c]==0) printf("You don't have this card. Please choose again.\n");
					printf("Please select a card to build (Enter 0 to build nothing.)) : ");
				}
			}
			else if(com_ac==2){// normal action for producing the product
				int cnt_factory_tot=0,c1,c2;
				for(int i=0;i<=42;i++)
					if(Player[1].building_cards[i].status==1 && Player[1].building_cards[i].cargo==0) cnt_factory_tot++;
				if(cnt_factory_tot>=2){
					printf("You can choose 1 buildings to produce the cargo.\n");
					printf("Enter the number of cards:\nCard: ");
					while(scanf("%d",&c1)){
						if(Player[1].building_cards[c1].status=1 && Player[1].building_cards[c1].cargo==0 && c1<=42){
							Player[1].building_cards[c1].cargo=1;
							uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
							break;
						}
						else printf("Invalid card. Please choose again.\nCard: ");
					}
					printf("You produce 1 cargo.\n");
					if(Player[1].building_cards[70].status==1 || Player[1].building_cards[71].status==1 || Player[1].building_cards[72].status==1){
						//Aqueduct
						printf("You can choose one more buildings to produce the cargo cuz you have Aqueduct.\n");
						printf("Enter the number of cards:\nCard2: ");
						while(scanf("%d",&c1)){
							if(Player[1].building_cards[c1].status=1 && Player[1].building_cards[c1].cargo==0 && c1<=42){
								Player[1].building_cards[c1].cargo=1;
								uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
								break;
							}
							else printf("Invalid card. Please choose again.\nCard2: ");
						}
					}
					if(Player[1].building_cards[67].status==1 || Player[1].building_cards[68].status==1 || Player[1].building_cards[69].status==1){
						//Well card
						int32_t tmp_p=pick_one_card();
						Player[1].cnt_hand_card++;
						Player[1].hand_cards[tmp_p]=1;
					}
				}
				else if(cnt_factory_tot==1){
					for(int i=0;i<=42;i++){
						if(Player[1].building_cards[i].status==1 && Player[1].building_cards[i].cargo==0){
							Player[1].building_cards[i].cargo=1;
							uint32_t tmp=pick_one_card(); All_Cards[tmp].status=2;
							break;
						}
					}
					printf("You produce 1 cargo.\n");
				}
				else if(cnt_factory_tot<1){
					printf("You produce nothing cuz you don't have empty factory or any factory.\n");
				}
			}
			else if(com_ac==3){// normal action for selling product
				int32_t cnt_cargo_tot=0,_deter=0,c1,been_sold=0;
				for(int i=0;i<=42;i++)
					if(Player[1].building_cards[i].status==1 && Player[1].building_cards[i].cargo==1) cnt_cargo_tot++;
				if(cnt_cargo_tot>=1){
					printf("You have %d cargo to sell. Please choose any one to sell.(Enter 0 to sell nothing.)\n",cnt_cargo_tot);
					printf("Card: ");
					while(scanf("%d",&c1)){
						if(c1==0){
							_deter=1;
							break;
						}
						if(Player[1].building_cards[c1].status==1 && Player[1].building_cards[c1].cargo==1 && c1<=42){
							Player[1].building_cards[c1].cargo=0;
							int32_t cnt_card=0;
							if(c1>=1 && c1<=10) cnt_card+=Trader_List[LT][1];
							else if(c1>=11 && c1<=18) cnt_card+=Trader_List[LT][2];
							else if(c1>=19 && c1<=26) cnt_card+=Trader_List[LT][3];
							else if(c1>=27 && c1<=34) cnt_card+=Trader_List[LT][4];
							else if(c1>=35 && c1<=42) cnt_card+=Trader_List[LT][5];
							for(int j=0;j<cnt_card;j++){
								Player[1].hand_cards[pick_one_card()]=1;
								Player[1].cnt_hand_card+=1;
							}
							been_sold++;
							break;
						}
						else{
							printf("Invalid card. Please choose again.\nCard: ");
						}
					}
					if(_deter){
						printf("You sold nothing.\n");
					}
					_deter=0;
					if(cnt_cargo_tot>=2){
						if(Player[1].building_cards[79].status==1 || Player[1].building_cards[80].status==1 || Player[1].building_cards[81].status==1){
							//Trading_post
							printf("You have Trading Post, you can sold one more product.\nPlease choose one to sell (Enter the card number. Enter 0 to sell nothing.): ");
							while(scanf("%d",&c1)){
								if(c1==0){
									_deter=1;
									break;
								}
								if(Player[1].building_cards[c1].status==1 && Player[1].building_cards[c1].cargo==1 && c1<=42){
									Player[1].building_cards[c1].cargo=0;
									int32_t cnt_card=0;
									if(c1>=1 && c1<=10) cnt_card+=Trader_List[LT][1];
									else if(c1>=11 && c1<=18) cnt_card+=Trader_List[LT][2];
									else if(c1>=19 && c1<=26) cnt_card+=Trader_List[LT][3];
									else if(c1>=27 && c1<=34) cnt_card+=Trader_List[LT][4];
									else if(c1>=35 && c1<=42) cnt_card+=Trader_List[LT][5];
									for(int j=0;j<cnt_card;j++){
										Player[1].hand_cards[pick_one_card()]=1;
										Player[1].cnt_hand_card+=1;
									}
									been_sold++;
									break;
								}
								else{
									printf("Invalid card. Please choose again.\nCard: ");
								}
							}
							if(_deter){
								printf("You sold nothing.\n");
							}
						}
					}
					if(been_sold>=2){
						if(Player[1].building_cards[73].status==1 || Player[1].building_cards[74].status==1 || Player[1].building_cards[75].status==1){
							printf("You sold at least 2 products and you have Market Stand, so you pick one card to be your hand card.\n");
							Player[1].cnt_hand_card++;
							Player[1].hand_cards[pick_one_card()]=1;
						}
					}
				}
				else if(cnt_cargo_tot<1){
					printf("You don't have any cargo to sell.\n");
				}
			}
			else if(com_ac==4){// normal action for pick one of two card
				int det,a=pick_one_card(),b=pick_one_card();
				printf("Card1: %d\n",a);
				printf("Card2: %d\n",b);
				printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~2.)\n");
				while(scanf("%d",&det)){
					if(det==a || det==b){
						All_Cards[a].status=2; All_Cards[b].status=2; All_Cards[det].status=1;
						Player[1].hand_cards[det]=1; Player[1].cnt_hand_card++;
						break;
					}
					else{
						printf("Please choose one card of these two cards! Please choose again.\n");
						printf("Choose one and put it in your hand card.(Enter the number of the card, not 1~2.)\n");
						continue;
					}
				}
			}
			else if(com_ac==5){// normal action for nothing
				Gold_Mine(pg);
			}
			computer_act(2,com_ac);
			computer_act(3,com_ac);
		}
	}
}
int32_t calculate_vp(int32_t n){
	int vp=0;
	for(int i=1;i<=110;i++) if(Player[n].building_cards[i].status==1) vp+=All_Cards[i].cost;
	printf("Player%d: Building: %d Chapel: %d ",n,vp,Player[n].Chapel_vp);
	vp+=Player[n].Chapel_vp;
	int tmp=vp;
	// Guild Hall
	if(Player[n].building_cards[103].status==1 || Player[n].building_cards[104].status==1){
		for(int i=1;i<=42;i++) if(Player[n].building_cards[i].status==1) vp+=2;
	}
	// City Hall
	if(Player[n].building_cards[105].status==1 || Player[n].building_cards[106].status==1){
		for(int i=43;i<=110;i++) if(Player[n].building_cards[i].status==1) vp+=1;
	}
	// Triumhal arch
	if(Player[n].building_cards[107].status==1 || Player[n].building_cards[108].status==1){
		int32_t tmp_vp=0;
		if(Player[n].building_cards[94].status==1 || Player[n].building_cards[95].status==1 || Player[n].building_cards[96].status==1) tmp_vp++;
		if(Player[n].building_cards[97].status==1 || Player[n].building_cards[98].status==1 || Player[n].building_cards[99].status==1) tmp_vp++;
		if(Player[n].building_cards[100].status==1 || Player[n].building_cards[101].status==1 || Player[n].building_cards[102].status==1) tmp_vp++;
		if(tmp_vp==1) vp+=4;
		else if(tmp_vp==2) vp+=6;
		else if(tmp_vp==3) vp+=8;
	}
	// Palace
	if(Player[n].building_cards[109].status==1 || Player[n].building_cards[110].status==1) vp=(vp*5)/4;
	printf("Special Building: %d Total: %d\n",vp-tmp,vp);
	return vp;
}
int main(void){
	print_SANJUAN();
	printf("\n\n\nYou are player 1.\n");
	init();
	while(1){
		if(game_over_det==1) break;
		//for(int p=0;p<=3;p++){
			//printf("Player%d is the Governor.\n",p+1);
			//check everyone's card are less than 7 (including), instead of someone has tower.
			/*for(int i=1;i<=4;i++){
				printf("player%d's Chapel point = %d\n",i,Player[i].Chapel_vp);
			}*/
			new_match(0);
			/*if(Player[1].cnt_have_building>=12 || Player[2].cnt_have_building>=12 || Player[3].cnt_have_building>=12 || Player[4].cnt_have_building>=12){
				//until somone build 12 building
				game_over_det=1;
				break;
			}*/	
		//}
	}
	int32_t p1_vp=calculate_vp(1),hand1_tot=Player[1].cnt_hand_card,final1=0;
	int32_t p2_vp=calculate_vp(2),hand2_tot=Player[2].cnt_hand_card,final2=0;
	int32_t p3_vp=calculate_vp(3),hand3_tot=Player[3].cnt_hand_card,final3=0;
	int32_t p4_vp=calculate_vp(4),hand4_tot=Player[4].cnt_hand_card,final4=0;
	int32_t cnt_cargo_tot=0,cargo_tot[5]={0};
	for(int j=1;j<=4;j++){
		for(int i=0;i<=42;i++)
			if(Player[j].building_cards[i].status==1 && Player[j].building_cards[i].cargo==1) cnt_cargo_tot++;
		cargo_tot[j]=cnt_cargo_tot;
	}
	final1=cargo_tot[1]+hand1_tot;
	final2=cargo_tot[2]+hand2_tot;
	final3=cargo_tot[3]+hand3_tot;
	final4=cargo_tot[4]+hand4_tot;
	if(p1_vp > p2_vp && p1_vp > p3_vp && p1_vp > p4_vp) return printf("Player1 win.\n"),0;
	else if(p2_vp > p1_vp && p2_vp > p3_vp && p2_vp > p4_vp) return printf("Player2 win.\n"),0;
	else if(p3_vp > p1_vp && p3_vp > p2_vp && p3_vp > p4_vp) return printf("Player3 win.\n"),0;
	else if(p4_vp > p1_vp && p4_vp > p2_vp && p4_vp > p3_vp) return printf("Player4 win.\n"),0;
	if(p1_vp==p2_vp && p2_vp==p3_vp && p3_vp==p4_vp){
		if(final1 > final2 && final1 > final3 && final1 > final4) return printf("Player1 win.\n"),0;
		else if(final2 > final1 && final2 > final3 && final2 > final4) return printf("Player2 win.\n"),0;
		else if(final3 > final1 && final3 > final2 && final3 > final4) return printf("Player3 win.\n"),0;
		else if(final4 > final1 && final4 > final2 && final4 > final3) return printf("Player4 win.\n"),0;
	}
	else if(p1_vp==p2_vp && p2_vp==p3_vp && p3_vp!=p4_vp){
		if(final1 > final2 && final1 > final3) return printf("Player1 win.\n"),0;
		else if(final2 > final1 && final2 > final3) return printf("Player2 win.\n"),0;
		else if(final3 > final1 && final3 > final2) return printf("Player3 win.\n"),0;
	}
	else if(p1_vp==p3_vp && p3_vp==p4_vp && p1_vp!=p2_vp){
		if(final1 > final3 && final1 > final4) return printf("Player1 win.\n"),0;
		else if(final3 > final1 && final3 > final4) return printf("Player3 win.\n"),0;
		else if(final4 > final1 && final4 > final3) return printf("Player4 win.\n"),0;
	}
	else if(p1_vp==p2_vp && p2_vp==p4_vp && p4_vp!=p3_vp){
		if(final1 > final2 && final1 > final4) return printf("Player1 win.\n"),0;
		else if(final2 > final1 && final2 > final4) return printf("Player2 win.\n"),0;
		else if(final4 > final1 && final4 > final2) return printf("Player4 win.\n"),0;
	}
	else if(p2_vp==p3_vp && p3_vp==p4_vp && p1_vp!=p2_vp){
		if(final2 > final3 && final2 > final4) return printf("Player2 win.\n"),0;
		else if(final3 > final2 && final3 > final4) return printf("Player3 win.\n"),0;
		else if(final4 > final2 && final4 > final3) return printf("Player4 win.\n"),0;
	}
	else if(p1_vp==p2_vp){
		if(final1 > final2) return printf("Player1 win.\n"),0;
		else return printf("Player2 win.\n"),0;
	}
	else if(p1_vp==p3_vp){
		if(final1 > final3) return printf("Player1 win.\n"),0;
		else return printf("Player3 win.\n"),0;
	}
	else if(p1_vp==p4_vp){
		if(final1 > final4) return printf("Player1 win.\n"),0;
		else return printf("Player4 win.\n"),0;
	}
	else if(p2_vp==p3_vp){
		if(final2 > final3) return printf("Player2 win.\n"),0;
		else return printf("Player3 win.\n"),0;
	}
	else if(p2_vp==p4_vp){
		if(final2 > final4) return printf("Player2 win.\n"),0;
		else return printf("Player4 win.\n"),0;
	}
	else if(p3_vp==p4_vp){
		if(final3 > final4) return printf("Player3 win.\n"),0;
		else return printf("Player4 win.\n"),0;
	}
	return 0;
}