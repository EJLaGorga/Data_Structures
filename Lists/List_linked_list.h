// List_linked_list.h
//
// Purpose:  Create a list using a standard, singly-linked list.
//

#ifndef List_linked_list_h
#define List_linked_list_h

#include <iostream> // for NULL
#include "card.h"

class List_linked_list
{
public:
	List_linked_list();
	~List_linked_list();

	// Need to define/overload copy constructor and assignment operator
	List_linked_list(const List_linked_list &source);
	List_linked_list operator =(const List_linked_list &source);
	
	void print_list();
	void print_list_int();
	bool is_empty() { return front == NULL; }

	// students must write the following functions in the .cpp file
	int cards_in_hand();       // return number of cards in hand
	void make_empty();       // empties the list; front should be NULL
	
	// insert a card at the front
	// Should allow insert into an empty list
	void insert_at_front(Card c);

	// insert a card at the back (after the end)
	// should allow insert into an empty list
	void insert_at_back(Card c);

	// insert a card at an index such that
	// all cards following the index will be moved farther
	// down the list by one.
	// The index can be one after the back of the list
	// I.e., you can insert at index 0 into an empty list,
	// and you can insert at index 4 in a list with 4 nodes.
	// In the first case, the node inserted would become the front
	// In the second case, the node inserted would be inserted
	// after the current back.
	void insert_at_index(Card c, int index);

	// replace the card at index
	// A card at index must already exist
	void replace_at_index(Card c, int index);
	
	// return the card at index.
	// allowed to crash if index is not in the list
	Card card_at(int index);
	
	// return true if the card is in the list
	// return false if the card is not in the list
	bool has_card(Card c);
	
	// remove the card from the list
	// Returns true if the card was removed
	// Returns false if the card was not in the list
	bool remove(Card c);

	// Remove the card from the front and
	// return the card that was removed
	// Allowed to fail if list is empty
        // NB:  Doesn't lose cards after the first card.
	Card remove_from_front();

	// Remove the card from the back
	// Return the card that was removed
	// Allowed to fail if the list is empty
	Card remove_from_back();

	// Remove the card from index
	// Return the card that was removed
	// Allowed to fail if index is beyond the end of the list
	Card remove_from_index(int index);

private:
        struct Card_Node {
                Card       card;
                Card_Node *next;
        };
	Card_Node *front; // the front of the list

    Card_Node *copy_card_list(Card_Node *lst);

    void make_empty_recursively(Card_Node *current_node);
};

#endif // List_linked_list_h
