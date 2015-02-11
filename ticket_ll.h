#ifndef TICKET_LL
#define TICKET_LL

#include <stdbool.h>
#include <linux/slab.h>

typedef struct ticket_ll {
	unsigned ticket;
	struct ticket_ll* next;
} ticket_ll_t;

ticket_ll_t* new_ticket_node(unsigned t)
{
	ticket_ll_t *new_node = kmalloc(sizeof(ticket_ll_t), GFP_ATOMIC);
	new_node->ticket = t;
	new_node->next = NULL;
	return new_node;
}

void insert_ticket_node(ticket_ll_t* head, unsigned t)
{
	ticket_ll_t *current_node = head;
	ticket_ll_t *node = new_ticket_node(t);

	//move to end of list
	while(current_node->next != NULL)
		current_node = current_node->next;

	current_node->next = node;
	return;
}

bool remove_ticket_node(ticket_ll_t *head, unsigned t)
{
	ticket_ll_t *current_node, *last_node;

	if(head == NULL)
		return false;

	//if ticket was head ticket
	if(head->ticket == t)
	{
		current_node = head;
		head = head->next;
		kfree(current_node);
		return true;
	}

	current_node = last_node = head;
	while((current_node = current_node->next) != NULL)
	{
		if(current_node->ticket == t)
		{
			last_node->next = current_node->next;
			kfree(current_node);
			return true;
		}

		last_node = current_node;
	}

	// Element not found
	return false;
}

void free_all_ticket_node(ticket_ll_t *head)
{
	while (remove_ticket_node(head, head->ticket))
	{

	}
}

#endif
