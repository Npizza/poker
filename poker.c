#include <stdio.h>
#include <stdlib.h>
#include "poker.h"

int deck_top;
community_cards com_cards;
int sb;
int bb;
int init_stack;

void initialize_players(player* players, int n_players){
  int i;
  for (i = 0; i < n_players; i++) {
    players[i].chips = init_stack;
  }
}

void print_player_hand(player p){ // print hand of player p
  print_card(p.hand[0]);
  printf(" ");
  print_card(p.hand[1]);
  printf("\n");
}

void print_community_cards(){ // print the current community cards
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

void flop_cards(card* deck){ // take 3 cards from deck to community cards
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

void turn_cards(card* deck){ // take 1 card from deck to community cards
  com_cards.cards[3].num = deck[deck_top].num;
  com_cards.cards[3].sym = deck[deck_top--].sym;
  com_cards.num_of_cards += 1;
}

void river_cards(card* deck){ // take 1 card from deck to community cards
  com_cards.cards[4].num = deck[deck_top].num;
  com_cards.cards[4].sym = deck[deck_top--].sym;
  com_cards.num_of_cards += 1;
}

/*
 * give each of n players 2 cards from the deck
 */
void give_cards(player* players, int n_players, card* deck){
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < n_players; j++) {
      players[j].hand[i] = deck[deck_top--];
    }
  }
}

void print_card_from_deck(const card* deck, int i){ // print i-th card from deck
  printf("[%c%lc]\n", deck[i].num, deck[i].sym);
}

void print_card(const card card_to_print){ // print a card
  printf("[%c%lc]", card_to_print.num, card_to_print.sym);
}

void print_deck(const card* deck){ // print the whole available deck
  int i;
  for (i = 0; i <= deck_top; i++) {
    print_card_from_deck(deck, i);
  }
}

/*
 * swap i-th and j-th card from deck
 */
void swap_cards_in_deck(card* deck, int i, int j){
  card tmp;
  tmp.num = deck[i].num;
  tmp.sym = deck[i].sym;
  deck[i].num = deck[j].num;
  deck[i].sym = deck[j].sym;
  deck[j].num = tmp.num;
  deck[j].sym = tmp.sym;
}

void shuffle_deck(card* deck){ // shuffle the available deck
  int i;
  int j;
  int a;
  for (a = 0; a < 150000; a++) {
    i = rand() % (deck_top+1);
    j = rand() % (deck_top+1);
    if (i != j) {
      swap_cards_in_deck(deck, i, j);
    }
    else{
      a--;
    }
  } // for
}

void initialize_deck(card* deck){ // initialize deck but not shuffled
  int i;
  for (i = 0; i < 52; i++) {
    int num = i % 13;
    if (num == 0) { deck[i].num = 'A'; }
    else if (num == 9) { deck[i].num = 'T'; }
    else if (num == 10) { deck[i].num = 'J'; }
    else if (num == 11) { deck[i].num = 'Q'; }
    else if (num == 12) { deck[i].num = 'K'; }
    else if (num < 9) { sprintf(&(deck[i].num), "%d", num+1); }
    else {
      printf("error: num = %d\n", num);
      exit(1);
    }

    int sym = i/13;
    if (sym == 0) { deck[i].sym = SPADE_B; }
    else if (sym == 1) { deck[i].sym = HEART_W; }
    else if (sym == 2) { deck[i].sym = DIAMOND_W; }
    else { deck[i].sym = CLUB_B; }
  } // for
}
