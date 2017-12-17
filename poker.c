#include <stdio.h>
#include <stdlib.h>
#include "poker.h"

int deck_top; // deck[deck_top] is the top card of the deck
community_cards com_cards; // the community cards
int sb; // small blind amount (in units of chips)
int bb; // big blind amount
int button_player; // which player is button
int sb_player; // which player is sb
int bb_player; // which player is bb
int init_stack; // initial stack (chips) of each player
int pot; // how many chips are in the pot currently


/*
 * Initialize the structure of each player in an array of n_players players
 */
void initialize_players(player* players, const int n_players){
  int i;
  for (i = 0; i < n_players; i++) {
    players[i].chips = init_stack;
  }
}

/*
 * Print hand of player p
 */
void print_player_hand(const player p){
  print_card(p.hand[0]);
  printf(" ");
  print_card(p.hand[1]);
  printf("\n");
}

/*
 * Print the current community cards
 */
void print_community_cards(){
  int i;
  printf("community cards: ");
  for (i = 0; i < com_cards.num_of_cards; i++) {
    print_card(com_cards.cards[i]);
    if (i < com_cards.num_of_cards-1) {
      printf(" ");
    }
  }
  printf("\n");
}

/*
 * Put 3 cards from deck to community cards (Flop)
 */
void flop_cards(const card* deck){
  com_cards.cards[0].num = deck[deck_top].num;
  com_cards.cards[0].sym = deck[deck_top--].sym;
  com_cards.num_of_cards += 1;
  com_cards.cards[1].num = deck[deck_top].num;
  com_cards.cards[1].sym = deck[deck_top--].sym;
  com_cards.num_of_cards += 1;
  com_cards.cards[2].num = deck[deck_top].num;
  com_cards.cards[2].sym = deck[deck_top--].sym;
  com_cards.num_of_cards += 1;
}

/*
 * Put 1 card from deck to community cards (Turn)
 */
void turn_cards(const card* deck){
  com_cards.cards[3].num = deck[deck_top].num;
  com_cards.cards[3].sym = deck[deck_top--].sym;
  com_cards.num_of_cards += 1;
}

/*
 * Put 1 card from deck to community cards (River)
 */
void river_cards(const card* deck){
  com_cards.cards[4].num = deck[deck_top].num;
  com_cards.cards[4].sym = deck[deck_top--].sym;
  com_cards.num_of_cards += 1;
}

/*
 * Give each of n players their 2 cards (their hard)
 */
void give_cards(player* players, const int n_players, const card* deck){
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < n_players; j++) {
      players[j].hand[i] = deck[deck_top--];
    }
  }
}

/*
 * Print i-th card from deck (i = 0 is first card)
 */
void print_card_from_deck(const card* deck, const int i){
  printf("[%c%lc]\n", deck[i].num, deck[i].sym);
}

/*
 * Print a card
 */
void print_card(const card card_to_print){
  printf("[%c%lc]", card_to_print.num, card_to_print.sym);
}

/*
 * Print the current deck
 */
void print_deck(const card* deck){
  int i;
  for (i = 0; i <= deck_top; i++) {
    print_card_from_deck(deck, i);
  }
}

/*
 * Swap i-th and j-th card from current deck
 */
void swap_cards_in_deck(card* deck, const int i, const int j){
  if (i > deck_top || j > deck_top) {
    fprintf(stderr, "swap_cards_in_deck: cannot swap i-th card: out of current deck\n");
    exit(1);
  }
  card tmp;
  tmp.num = deck[i].num;
  tmp.sym = deck[i].sym;
  deck[i].num = deck[j].num;
  deck[i].sym = deck[j].sym;
  deck[j].num = tmp.num;
  deck[j].sym = tmp.sym;
}

/*
 * Shuffle the available deck
 */
void shuffle_deck(card* deck){
  int i, j, a;
  for (a = 0; a < 150000; a++) { // swap 2 different random cards 150,000 times
    i = rand() % (deck_top+1);
    j = rand() % (deck_top+1);
    if (i != j) {
      swap_cards_in_deck(deck, i, j);
    } // if
    else{
      a--;
    } // else
  } // for
}

/*
 * Initialize deck but not shuffled
 */
void initialize_deck(card* deck){
  int i, num, sym;
  for (i = 0; i < 52; i++) {
    num = i % 13;
    if (num == 0) { deck[i].num = 'A'; }
    else if (num == 9) { deck[i].num = 'T'; }
    else if (num == 10) { deck[i].num = 'J'; }
    else if (num == 11) { deck[i].num = 'Q'; }
    else if (num == 12) { deck[i].num = 'K'; }
    else if (num < 9) { sprintf(&(deck[i].num), "%d", num+1); }
    else {
      printf("initialize_deck: error, num = %d\n", num);
      exit(1);
    }

    sym = i/13;
    if (sym == 0) { deck[i].sym = SPADE_B; }
    else if (sym == 1) { deck[i].sym = HEART_W; }
    else if (sym == 2) { deck[i].sym = DIAMOND_W; }
    else if (sym == 3) { deck[i].sym = CLUB_B; }
    else {
      printf("initialize_deck: error, sym = %d\n", sym);
      exit(1);
    }
  } // for
}

/*
 * Return number of players that are still playing (that have chips)
 */
int players_still_playing(const player* p, const int num_of_players){
  int i;
  int ret = 0;
  for (i = 0; i < num_of_players; i++) {
    if (is_player_still_playing(p[i])) {
      ret++;
    }
  }
  return ret;
}

/*
 * Return if the player is still playing (has chips)
 */
int is_player_still_playing(const player p){
  return (p.chips > 0) ? 1 : 0;
}

/*
 * Return who is the next player who is still playing
 */
int next_avail_player(const int current_player_turn,
                     const player* p,
                     const int num_of_players){
  int next = (current_player_turn + 1) % num_of_players;
  if (!is_player_still_playing(p[next])) {
    return next_avail_player(next, p, num_of_players);
  }

  return next;
}

/*
 * Print the players who are The Button, Small Blind and Big Blind
 */
void print_button_sb_bb_players(const int p_turn, const player* p, const int n){
  button_player = p_turn;
  sb_player = next_avail_player(button_player, p, n);
  bb_player = next_avail_player(sb_player, p, n);
  if (button_player == bb_player) { // if there are only 2 players, button is sb
    bb_player = sb_player;
    sb_player = button_player;
  }
  printf("p%d:\tThe Button\n", button_player + 1);
  printf("p%d:\tSmall Blind\n", sb_player + 1);
  printf("p%d:\tBig Blind\n", bb_player + 1);
}
