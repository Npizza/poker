#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "poker.h"


#define SPADE_B   (wint_t)9824
#define HEART_B   (wint_t)9829
#define DIAMOND_B (wint_t)9830
#define CLUB_B    (wint_t)9827

#define SPADE_W   (wint_t)9828
#define HEART_W   (wint_t)9825
#define DIAMOND_W (wint_t)9826
#define CLUB_W    (wint_t)9831

/******************************************************************************
Function : rankHand
Process  : Ranks the hand to determine its type (ie Straight)
Build hand repetition list (singles, pairs, trips, quads)
Switch on the number of unique card number elements in hand
If we have two items in our map,
we have either a full house of a four of a kind
If we have four cards of same number,
we have a four of a kind
Else, it is a full house
If we have three items in our map,
we have either a two pair or a three of a kind
If we have three cards of same number,
we have three of a kind
Else, it is two pair
If we have four items in our map, we have one pair
If we have five items in our map, we need to look further
Check for straight flush, flush, or straight
If this is a low ace straight,
we need to fix the sort order
Check for a flush
Check for a straight
If this is a low ace straight,
we need to fix the sort order
Else, we have a high card
Notes    : None
https://github.com/donnemartin/poker/blob/master/src/HandRanker.cpp
*/

int deck_top = 51; // deck[deck_top] is the top card of the deck
community_cards com_cards;
int sb = 1;
int bb = 2;
int init_stack = 100;


int main(int argc, char const *argv[]) {
  srand(time(NULL));
  setlocale(LC_ALL, "");
  int i;

  int num_of_players = 2;
  player players[num_of_players];
  initialize_players(players, num_of_players);

  card deck[deck_top+1];
  initialize_deck(deck);

  int pot, cur_bet;
  int player_turn = 0;

  while (players[0].chips > 0 && players[1].chips) {
    com_cards.num_of_cards = 0;
    for (i = 0; i < num_of_players; i++) {
      printf("p%d : chips %d\n", i+1, players[i].chips);
    }
    shuffle_deck(deck);
    give_cards(players, num_of_players, deck);
    getchar();

    printf("\e[1;1H\e[2J"); // clear screen
    printf("p1: ");
    print_player_hand(players[0]); // show player1 cards
    getchar();

    printf("\e[1;1H\e[2J"); // clear screen
    printf("p2: ");
    print_player_hand(players[1]); // show player2 cards
    getchar();

    printf("\e[1;1H\e[2J"); // clear screen



// BETTING START
/*
    cur_bet = 0;
    pot = 0;
    int j;
    for (i = 0; i < num_of_players; i++) {
      j = (i + player_turn) % num_of_players;
      if (bet != 0) {
        printf("Bet is %d.\n", bet);
      }
      printf("Player%d: Place bet: ", j+1);
      scanf("%d", &(players[j].bet));
      if (bet == 0) {
        if (players[j].bet == 0) {
          printf("Check.\n");
          continue;
        } // playerbet == 0
        else {
          if (players[j].bet > players[j].chips) {
            printf("You have only %d chips! You must bet less!\n", );
            i--;
            continue;
          } // playerbet > playerchips
          else {
            bet = players[j].bet;
            players[j].chips -= bet;
          }
        } // playerbet > 0
      } // bet == 0
      else {
        if (players[j].bet == 0) {
          printf("Fold!\n");

        }
        else if (players[j].bet < bet) {
          printf("You must bet at lease %d!\n", bet);

        }
      } // bet > 0
      // increase the pot

    }
    player_turn = (j + 1) % num_of_players;
*/
// BETTING END

    getchar();

    printf("\e[1;1H\e[2J"); // clear screen
    flop_cards(deck);
    print_community_cards(); // show flop
    getchar();

    turn_cards(deck);
    print_community_cards(); // show turn
    getchar();

    river_cards(deck);
    print_community_cards(); // show river
    getchar();

    for (i = 0; i < num_of_players; i++) { // show each player's cards
      printf("p%d: ", i+1);
      print_player_hand(players[i]);
    }
    getchar();

    deck_top = 51;
    printf("\e[1;1H\e[2J"); // clear screen
  }

  return 0;
}
