#include <stdlib.h>

#define KING_VALUE = 13
#define QUEEN_VALUE = 12
#define JACK_VALUE = 11
#define ACE_VALUE = 1

#define DECK_CAPACITY 52

#define CARD_TYPES 13
#define SUITS 4

typedef struct {
    int value;
    int suit;
} Card;

typedef struct {
    Card *cards;
    size_t size;
    size_t capacity;
} Deck;

void create_deck(Deck *, size_t capacity);

void populate_deck(Deck *);

void shuffle_deck(Deck *);

Card draw_from_deck(Deck *);

void add_card_deck(Deck *, Card card);

void print_deck(Deck *);

void free_deck(Deck *);
