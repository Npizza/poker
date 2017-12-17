#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "poker.h"


/*******************************************************************
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

#define SPADE_B   (wint_t)9824
#define HEART_B   (wint_t)9829
#define DIAMOND_B (wint_t)9830
#define CLUB_B    (wint_t)9827

#define SPADE_W   (wint_t)9828
#define HEART_W   (wint_t)9825
#define DIAMOND_W (wint_t)9826
#define CLUB_W    (wint_t)9831

int deck_top = 51; // deck[deck_top] is the top card of the deck
community_cards com_cards; // the community cards
int sb = 1; // small blind amount (in units of chips)
int bb = 2; // big blind amount
int button_player; // which player is button
int sb_player; // which player is sb
int bb_player; // which player is bb
int init_stack = 100; // initial stack (chips) of each player
int pot = 0; // how many chips are in the pot currently


int main(int argc, char const *argv[]) {
  srand(time(NULL));
  setlocale(LC_ALL, "");
  int i;

  int num_of_players = 4;
  player players[num_of_players];
  initialize_players(players, num_of_players);

  card deck[deck_top+1];
  initialize_deck(deck);

  int player_turn = 0;
  int betting = 0;

  while (players_still_playing(players, num_of_players) >= 2) {
    com_cards.num_of_cards = 0;
    for (i = 0; i < num_of_players; i++) {
      printf("p%d : chips %d\n", i+1, players[i].chips);
    } // for
    shuffle_deck(deck);
    give_cards(players, num_of_players, deck);
    getchar();

    for (i = 0; i < num_of_players; i++) {
      if (is_player_still_playing(players[i])) {
        clear_screen();
        printf("p%d: ", i+1);
        print_player_hand(players[i]);
        getchar();
      } // if
    } // for














    clear_screen();
    // BETTING PHASE
    print_button_sb_bb_players(player_turn, players, num_of_players);
    players[sb_player].chips -= sb;
    players[sb_player].chips += sb;
    players[bb_player].chips -= bb;
    players[bb_player].chips += bb;
    pot += sb + bb;

    getchar();

















    clear_screen();
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
    } // for
    getchar();

    deck_top = 51;
    player_turn = next_avail_player(player_turn, players, num_of_players);
    clear_screen();
  } // while

  return 0;
}
