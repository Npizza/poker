#ifndef POKER_H
#define POKER_H
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
  card hand[2]; // player's 2 cards (hand)
  int chips; // amount of chips player has
  int bet; // the bet he has put at any given moment
} player;

typedef struct community_cards{
  card cards[5]; // the cards that are down
  int num_of_cards; // how many cards are down at any given moment
} community_cards;

extern int deck_top; // deck[deck_top] is the top card of the deck
extern community_cards com_cards; // the community cards
extern int sb; // small blind amount (in units of chips)
extern int bb; // big blind amount
extern int button_player; // which player is button
extern int sb_player; // which player is sb
extern int bb_player; // which player is bb
extern int init_stack; // initial stack (chips) of each player
extern int pot; // how many chips are in the pot currently

// Clear the terminal screen
static inline void clear_screen(){
  printf("\e[1;1H\e[2J");
}

// Initialize the structure of each player in an array of n_players players
void initialize_players(player* players, const int n_players);

// Print hand of player p
void print_player_hand(const player p);

// Print the current community cards
void print_community_cards();

// Put 3 cards from deck to community cards (Flop)
void flop_cards(const card* deck);

// Put 1 card from deck to community cards (Turn)
void turn_cards(const card* deck);

// Put 1 card from deck to community cards (River)
void river_cards(const card* deck);

// Give each of n players their 2 cards (their hard)
void give_cards(player* players, const int n_players, const card* deck);

// Print i-th card from deck (i = 0 is first card)
void print_card_from_deck(const card* deck, const int i);

// Print a card
void print_card(const card card_to_print);

// Print the current deck
void print_deck(const card* deck);

// Swap i-th and j-th card from current deck
void swap_cards_in_deck(card* deck, const int i, const int j);

// Shuffle the available deck
void shuffle_deck(card* deck);

// Initialize deck but not shuffled
void initialize_deck(card* deck);

// Return number of players that are still playing (that have chips)
int players_still_playing(const player* p, const int num_of_players);

// Return if the player is still playing (has chips)
int is_player_still_playing(const player p);

// Return who is the next player who is still playing
int next_avail_player(const int current_player_turn,
                     const player* p,
                     const int num_of_players);

// Print the players who are The Button, Small Blind and Big Blind
void print_button_sb_bb_players(const int p_turn, const player* p, const int n);

#endif // POKER_H
