#ifndef READ_LL
#define READ_LL

#include <stdbool.h>
#include <linux/slab.h>

typedef struct read_ll {
	pid_t pid;
	struct read_ll* next;
} read_ll_t;

read_ll_t* new_read_node(pid_t p)
{
	read_ll_t *new_node = kmalloc(sizeof(read_ll_t), GFP_ATOMIC);
	new_node->pid = p;
	new_node->next = NULL;
	return new_node;
}

void insert_read_node(read_ll_t* head, pid_t p)
{
	read_ll_t *current_node = head;
	read_ll_t *node = new_read_node(p);

	//move to end of list
	while(current_node->next != NULL)
		current_node = current_node->next;

	current_node->next = node;
	return;
}

bool remove_read_node(read_ll_t *head, pid_t p)
{
	read_ll_t *current_node, *last_node;

	if(head == NULL)
		return false;

	//if ticket was head ticket
	if(head->pid == p)
	{
		current_node = head;
		head = head->next;
		kfree(current_node);
		return true;
	}

	current_node = last_node = head;
	while((current_node = current_node->next) != NULL)
	{
		if(current_node->pid == p)
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

void free_all_read_nodes(read_ll_t *head)
{
	while (remove_read_node(head, head->pid))
	{

	}
}

#endif
