#include "List_linked_list.h"

#include <iostream>
#include <cassert>

using namespace std;

/*
 * The following #define allows us to use Card_Node as a type.
 * Because the node structure is private, we would otherwise
 * have to write List_linked_list::Card_node everywhere.
 *
 * I put a few of those in, so you can see what I mean (see
 * the copy constructor.
 */
#define Card_Node List_linked_list::Card_Node

/*
 * Constructor
 */
List_linked_list::List_linked_list()
{
	front = NULL;		//set the front to NULL
}

/*
 * Destructor
 */
List_linked_list::~List_linked_list()
{
	make_empty();		 // deletes list
}

List_linked_list::Card_Node 
*List_linked_list::copy_card_list(List_linked_list::Card_Node *lst)
{
    // Easy to copy an empty list
    if (lst == NULL)
        return NULL;

    // Otherwise make a new node
    List_linked_list::Card_Node *new_node_p
        = new List_linked_list::Card_Node;

    // Copy node data
    new_node_p->card = lst->card;

    // and copy the rest of the nodes
    new_node_p->next = copy_card_list(lst->next);

    // Return pointer to first node in copied list
    return new_node_p;
}

/*
 * Explicit copy constructor necessary because of cards list 
 * in the heap.
 */
List_linked_list::List_linked_list(const List_linked_list &source)
{
    front = copy_card_list(source.front);
}

/*
 * Explicit operator= overload necessary because of heap-allocated 
 * card nodes
 */
List_linked_list List_linked_list::operator =(const List_linked_list &source)
{
	// check for self-assignment -- return without doing anything
	if (this == &source) {
		return *this;
	}
	// delete all current cards
	while (front != NULL) {
		Card_Node *next = front->next;
		delete front;
		front = next;
	}
	// copy over all cards from source list
	if (source.front == NULL) return *this; // nothing to do

	front = new Card_Node;
	Card_Node *this_current   = front;
	Card_Node *source_current = source.front;

	while (source_current != NULL) {
		// deep copy each Card_Node
		this_current->card = source_current->card;
		if (source_current->next != NULL) {
			Card_Node *new_node = new Card_Node();
			this_current->next  = new_node;
		} else {
			this_current->next = NULL; // at back
		}
		source_current = source_current->next;
		this_current   = this_current->next;
	}
	return *this;
}

// return number of cards in hand
int List_linked_list::cards_in_hand()
{
	int count = 0;
	Card_Node *current_node = front;

	//traverse list and count objects
	while (current_node != NULL){
		current_node = current_node->next;
		count++;
	}
	return count;
}       

// empties the list; front should be NULL
void List_linked_list::make_empty()
{
	make_empty_recursively(front);
	front = NULL;
}  

// empties the list recursively
void List_linked_list::make_empty_recursively(Card_Node *current_node)
{
	if (current_node == NULL) {		//recurse until last node
		return;
	}
	else {
		make_empty_recursively(current_node->next);
		delete current_node;
	}
}

// insert a card at the front
// Should allow insert into an empty list
void List_linked_list::insert_at_front(Card c)
{
	Card_Node *new_node = new Card_Node;
	new_node->card = c;
	new_node->next = front;
	front = new_node;
}

// insert a card at the back (after the end)
void List_linked_list::insert_at_back(Card c)
{
	Card_Node *new_node = new Card_Node;
	new_node->card = c;
	new_node->next = NULL;		// new node points to NULL

	if (front == NULL)		// if empty
		front = new_node;	// insert at front
	else {
		Card_Node *current_node = front;
		// if current points to NULL, point current to new
		while (current_node != NULL){
			if (current_node->next == NULL){
				current_node->next = new_node;		
				break;
			}	
			current_node = current_node->next;	//taverses
		}
	}
}

// insert a card at an index such that
// all cards following the index will be 
// moved farther down the list by one.
void List_linked_list::insert_at_index(Card c, int index)
{
	assert((index <= cards_in_hand()) && (index >= 0)); 

	// if index is 0, insert at front
	if (index == 0){
		insert_at_front(c);
		return;
	}

	// if index is max, insert at back
	if (index == cards_in_hand()){
		insert_at_back(c);
		return;
	}

	Card_Node *new_node = new Card_Node;
	new_node->card = c;
	
	Card_Node *current_node = front;
	
	// for noncorner indexes
	for (int i=0; i < index; i++){
		current_node = current_node->next;  //traverses
	}
	// rearrange pointers
	new_node->next = current_node->next;	//seg fault: cause of failure for all tests: 4 6 7 8 10
	current_node->next = new_node;
}

// replace the card at index
// A card at index must already exist
void List_linked_list::replace_at_index(Card c, int index)		//tested
{
	assert((index < cards_in_hand()) && (index >= 0));

	Card_Node *current_node = front;
	for (int i=0; i <= index; i++){
		if (i == index){
			//just replacing Card value in Card_Node
			current_node->card = c;
		}		
		current_node = current_node->next;	//taverses
	}
}

// return the card at index.
// allowed to crash if index is not in the list
Card List_linked_list::card_at(int index)
{
	assert((index < cards_in_hand()) && (cards_in_hand() > 0) && (index >= 0));

	Card_Node *current_node = front;
	for (int i=0; i <= index; i++){
		if (i == index)
			return current_node->card;
		current_node = current_node->next;	//taverses
	}
	return current_node->card; //fix warning given b/c of assert
}

// return true if the card is in the list
// return false if the card is not in the list
bool List_linked_list::has_card(Card c)
{
	Card_Node *current_node = front;
	while (current_node != NULL){
		if (current_node->card.same_card(c))
			return true;
		current_node = current_node->next;	//taverses
	}
	return false;
}

// finds index of card that will be removed
// Returns true if the card was removed
// Returns false if the card was not in the list
bool List_linked_list::remove(Card c)
{
	Card_Node *current_node = front;
	int index = 0;
	while (current_node != NULL){
		if (current_node->card.same_card(c)){
			//remove from index does all removing
			remove_from_index(index);
			return true;
		}
		current_node = current_node->next;	//taverses
		index++;
	}
	return false;
}

// Remove the card from the front and
// return the card that was removed
// Allowed to fail if list is empty
// NB:  Doesn't lose cards after the first card.
Card List_linked_list::remove_from_front()
{
	assert(cards_in_hand() > 0);

	Card_Node *temp_node = front;
	Card c = front->card;
	front = front->next;
	delete temp_node;
	return c;
}

// Remove the card from the back
// Return the card that was removed
// Allowed to fail if the list is empty
Card List_linked_list::remove_from_back()
{
	assert(cards_in_hand() > 0);

	Card_Node *current_node = front;
	Card_Node *temp_node;
	Card c;

	// taverses list until end
	while (current_node->next != NULL){
		temp_node = current_node;
		current_node = current_node->next;
	}

	// reassigns pointers
	c = current_node->card;
	temp_node->next = NULL;
	delete current_node;
	return c;
	
}

// Remove the card from index
// Return the card that was removed
// Allowed to fail if index is beyond the end of the list
Card List_linked_list::remove_from_index(int index)	
{
	assert((index < cards_in_hand()) && (cards_in_hand() > 0));

	Card_Node *current_node = front;
	Card_Node *prev_node;
	Card c;

	// if index is 0, remove from front
	if (index == 0)
		return remove_from_front();

	// if index is max, remove from back
	if (index == cards_in_hand()-1)
		return remove_from_back();

	// for other indexes, traverse
	for (int i=0; i < index; i++){
		prev_node = current_node;
		current_node = current_node->next;
	}

	// reassign pointers and delete removed node
	c = current_node->card;		//keep card values in c
	prev_node->next = current_node->next;
	delete current_node;
	return c;
}

void List_linked_list::print_list()
{
	Card_Node *current = front;
	while (current != NULL) {
		current->card.print_card();
		if (current->next != NULL) {
			cout << ",";
		} else {
			cout << "\n";
		}
		current = current->next;
	}
}

void List_linked_list::print_list_int()
{
	Card_Node *current = front;
	while (current != NULL) {
		current->card.print_card_int();
		if (current->next != NULL) {
			cout << ",";
		} else {
			cout << "\n";
		}
		current = current->next;
	}
}
