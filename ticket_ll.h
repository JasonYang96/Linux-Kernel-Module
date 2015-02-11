#ifndef TICKET_LL
#define TICKET_LL

#include <stdbool.h>
#include <linux/slab.h>

typedef struct ticket_ll {
	unsigned ticket;
	struct ticket_ll* next;
	bool visited;
} ticket_ll_t;

ticket_ll_t* new_node(unsigned t)
{
	ticket_ll_t *new_node = kmalloc(sizeof(ticket_ll_t), GFP_ATOMIC);
	new_node->ticket = t;
	new_node->next = NULL;
	new_node->visited = false;

	return new_node;
}

ticket_ll_t* insert(ticket_ll_t* head, unsigned t)
{
	ticket_ll_t *current_node = head;
	ticket_ll_t *node = new_node(t);

	//first node
	if(current_node == NULL)
		return node;

	//move to end of list
	while(current_node->next != NULL)
		current_node = current_node->next;

	current_node->next = node;

	return head;
}

bool remove(ticket_ll_t *head, unsigned t)
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

void list_free_all (ticket_ll_t *head)
{
	while (remove(head, head->ticket))
	{

	}
}

#endif
