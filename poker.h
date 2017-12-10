#include <wchar.h>

#define SPADE_B   (wint_t)9824
#define HEART_B   (wint_t)9829
#define DIAMOND_B (wint_t)9830
#define CLUB_B    (wint_t)9827

#define SPADE_W   (wint_t)9828
#define HEART_W   (wint_t)9825
#define DIAMOND_W (wint_t)9826
#define CLUB_W    (wint_t)9831

typedef struct card{
  char num;
  wint_t sym;
} card;

typedef struct player{
  card hand[2];
  int chips;
  int bet;
} player;

typedef struct community_cards{
  card cards[5];
  int num_of_cards;
} community_cards;

extern int deck_top; // deck[deck_top] is the top card of the deck
extern community_cards com_cards;
extern int sb;
extern int bb;
extern int init_stack;

void initialize_players(player* players, int n_players);

void print_card_from_deck(const card* deck, int i);

void print_card(const card card_to_print);

void print_deck(const card* deck);

void initialize_deck(card* deck); // initialize an empty deck with cards

void shuffle_deck(card* deck); // shuffle the deck

void swap_cards_in_deck(card* deck, int i, int j); // swap deck[i] with deck[j]

void give_cards(player* players,int n_players, card* deck);

void print_community_cards();

void flop_cards(card* deck);

void turn_cards(card* deck);

void river_cards(card* deck);

void print_player_hand(player p);
