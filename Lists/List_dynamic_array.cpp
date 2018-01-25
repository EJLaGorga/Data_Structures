#include "List_dynamic_array.h"

#include <iostream>
#include <cassert>

using namespace std;

/*
 * Constructer
 */
List_dynamic_array::List_dynamic_array()
{
	// create list
	cards_held = 0;
	hand_capacity = INITIAL_CAPACITY;

	cards = new Card[hand_capacity];
	for (int i = 0; i < cards_held; i++) {
		cards[i] = Card();
	}

}

/*
 * Destructer
 */
List_dynamic_array::~List_dynamic_array()
{
	// delete list
	delete [] cards;
}

/*
 * explicit copy constructor necessary because of pointer to cards
 * array 
 */
List_dynamic_array::List_dynamic_array(const List_dynamic_array &source)
{

	cards_held    = source.cards_held;
	hand_capacity = source.hand_capacity;

	cards = new Card[hand_capacity];
	for (int i = 0; i < cards_held; i++) {
		cards[i] = source.cards[i];
	}
}

/*
 * explicit operator= overload necessary because of pointer to cards
 * array 
 */
List_dynamic_array
List_dynamic_array::operator=(const List_dynamic_array &source)
{
	Card *new_cards;

	// check for self-assignment -- return without doing anything
	if (this == &source) {
		return *this;
	}

	hand_capacity = source.hand_capacity;
	cards_held    = source.cards_held;
	new_cards     = new Card[hand_capacity];

	for (int i = 0; i < hand_capacity; i++) {
		new_cards[i] = source.cards[i];
	}
	delete [ ] cards;
	cards = new_cards;
	return *this;
}

bool List_dynamic_array::is_empty()
{
        return cards_held == 0;
}

void List_dynamic_array::make_empty()
{
        cards_held = 0;
}


int List_dynamic_array::cards_in_hand()
{
        return cards_held;
}

void List_dynamic_array::print_list()
{
	for (int i = 0; i < cards_held; i++) {
		cards[i].print_card();
		if (i != cards_held - 1) {
			cout << ", ";
		} else {
			cout << "\n";
		}
	}
}

void List_dynamic_array::print_list_int()
{
	for (int i = 0; i < cards_held; i++) {
		cards[i].print_card_int();
		if (i != cards_held - 1) {
			cout << ", ";
		} else {
			cout << "\n";
		}
	}
}

void List_dynamic_array::insert_at_front(Card c)
{
	// check if we need to expand, and expand if necessary
	if (cards_held == hand_capacity){
		expand();
	}

	// move all items over one, starting from the last one
	for (int i = cards_held; i > 0; i--){
		cards[i] = cards[i-1];
	}

	// insert the new card
	cards[0] = c;

	// update cards_held
	cards_held++;
}

void List_dynamic_array::insert_at_back(Card c)
{
	// check if we need to expand, and expand if necessary
	if (cards_held == hand_capacity){
		expand();
	}
	// insert the new card at the end
	cards[cards_held] = c;

	// update cards_held
	cards_held++;
}

void List_dynamic_array::insert_at_index(Card c, int index)
{
	// if index is greater than cards_held, then fail
	assert(index <= cards_held);
	
	// check if we need to expand, and expand if necessary
	if (cards_held == hand_capacity){
		expand();
	}

	// move all elements past the insertion point up one
	for (int i = cards_held; i > index; i--){
		cards[i] = cards[i-1];
	}

	// insert the card
	cards[index] = c;

	// update cards_held
	cards_held++;
}

void List_dynamic_array::replace_at_index(Card c, int index)
{
	// if index is greater than cards_held-1, then fail
	assert(index < cards_held);

	// replace the card at index with c
	cards[index] = c;
}

Card List_dynamic_array::card_at(int index)
{
	// if index is out of bounds, fail
	assert (index >= 0 && index < cards_held);
	
	// return the card at index
	return cards[index];
}

bool List_dynamic_array::has_card(Card c)
{
    // loop through the cards and use the same_card()
    // method in Card.cpp to compare the cards
    // Returns true if the card is in the hand, false otherwise
	for (int i = 0; i < cards_held; i++){
		if (c.same_card(cards[i])){
			return true;
		}
	}
	return false;
}

bool List_dynamic_array::remove(Card c)
{
	// find the card and remove from the hand
	// Returns true if the card was found and removed,
	// false otherwise
	if (!has_card(c)){
		return false;
	}
	for (int i = 0; i < cards_held; i++){
		if (c.same_card(cards[i])){
			if (i == 0){
				remove_from_front();
				return true;
			}
			if (i == (cards_held-1)){
				remove_from_back();
				return true;
			}
			else{
				remove_from_index(i);
				return true;
			}
		}
	}
	return false;
}

Card List_dynamic_array::remove_from_front()
{
	// if the list is empty, fail
	assert(cards_held > 0);

    // remove the card at the front, and move all the other
    // cards back one spot
    // Returns the card that was removed
    Card c = cards[0];
    for (int i = 0; i < cards_held; i++){
    	cards[i] = cards[i+1];
    }
    cards_held--;
    return c;
}

Card List_dynamic_array::remove_from_back()
{
	// if the list is empty, fail
	assert(cards_held > 0);

	// removes the card that is at the back, and returns it
	Card c = cards[cards_held-1];
	cards_held--;
	return c;
}

Card List_dynamic_array::remove_from_index(int index)
{
	// if the list is empty, fail
	assert(cards_held > 0);
	// if loc is outside of bounds, fail
	assert(index >= 0 && index < cards_held);

	// similar to remove_from_front(), but
	// we remove the card at index
	// Returns the card that was removed
    Card c = cards[index];
    for (int i = index; i < cards_held; i++){
    	cards[i] = cards[i+1];
    }
    cards_held--;
	return c;
}

void List_dynamic_array::expand()
{
	// 1. create new list with twice the capacity
	Card *temp = new Card[hand_capacity*2];
	// 2. copy all cards to the new list
	for (int i = 0; i < hand_capacity; i++){
		temp[i] = cards[i];
	}
	// 3. delete the old list
	delete [] cards;
	// 4. set cards variable to point to the new list
	cards = temp;
	// 5. update hand_capacity
	hand_capacity = hand_capacity*2;
}
