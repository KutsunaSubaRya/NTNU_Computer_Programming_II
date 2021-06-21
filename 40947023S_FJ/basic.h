
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
	uint32_t cargo;
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
	uint32_t Chapel_vp;
} __attribute__ ((__packed__)) player;

player Player[5];
Cards All_Cards[120]; 