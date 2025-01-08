#include <SDL3/SDL_stdinc.h>
#include <deck.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void create_deck(Deck *deck, size_t capacity) {
    deck->cards = malloc(sizeof(Card) * DECK_CAPACITY);

    deck->capacity = capacity;
    deck->size = 0;
}

void populate_deck(Deck *deck) {
    assert(deck->capacity == DECK_CAPACITY);

    for (int suit = 0; suit < SUITS; suit++) {
        for(int card_value = 0; card_value < CARD_TYPES; card_value++) {
            deck->cards[deck->size].suit = suit;
            deck->cards[deck->size].value = card_value;
            deck->size++;
        }
    }
}

void shuffle_deck(Deck *deck) {
    for (int i = deck->size - 1; i >= 0; i--) {
        int j = SDL_rand(i + 1);

        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

Card draw_from_deck(Deck *deck) {
    assert(deck->size > 0);

    Card card = deck->cards[--deck->size];

    return card;
}

void add_card_deck(Deck *deck, Card card) {
    assert(deck->size < deck->capacity);

    deck->cards[deck->size] = card;
    deck->size++;
}

void print_deck(Deck *deck) {
    char suits[] = {'H', 'D', 'C', 'S'};

    for (int i = 0; i < deck->size; i++) {
        int value = deck->cards[i].value;
        int suit = deck->cards[i].suit;

        if (i != 0 && i % 13 == 0) {
            printf("\n");
        }

        printf("%c", suits[suit]);

        switch (value) {
            case 13:
                printf("K");
                break;
            case 12:
                printf("Q");
                break;
            case 11:
                printf("J");
                break;
            case 1:
                printf("A");
                break;
            default:
                printf("%d", value);
                break;
        }

        printf(" ");
    }

    printf("\n");
}

void free_deck(Deck *deck) {
    free(deck->cards);

    deck->cards = NULL;
    deck->size = 0;
    deck->capacity = 0;
}
