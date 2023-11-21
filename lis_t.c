#include "shell.h"

/**
 * create_node - creates a new node with given data
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: newly created node
 */
list_t *create_node(const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
	return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
	new_node->str = _strdup(str);

	if (!new_node->str)
	{
		free(new_node);

		return (NULL);
	}
	}
	new_node->next = NULL;
	return (new_node);
}

/**
 * add_node - adds a node to the end or the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 * @at_end: flag to indicate whether to add
 * at the end (1) or start (0)
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num, int at_end)
{
	list_t *new_node = create_node(str, num);

	if (!new_node)
		return (NULL);

	if (!head)
	{
	free(new_node->str);
	free(new_node);
	return (NULL);
	}

	if (*head)
	{
	if (at_end)
	{
		list_t *last_node = *head;
	while (last_node->next)
		last_node = last_node->next;
		last_node->next = new_node;
	}

	else
	{
		new_node->next = *head;
		*head = new_node;
	}
	}
	else
	{
	*head = new_node;
	}

	return (new_node);
}

/**
 * print_list_str - prints only the str element of
 * a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
	_puts(head->str ? head->str : "(nil)");
	_puts("\n");
	head = head->next;
	count++;
	}
	return (count);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	if (!head || !*head)
		return (0);

	list_t *node_to_delete = NULL;

	if (index == 0)
	{
	node_to_delete = *head;
	*head = (*head)->next;
	}
	else
	{
	list_t *prev_node = NULL;
	list_t *current_node = *head;
	unsigned int i = 0;

	while (current_node && i < index)
	{
		prev_node = current_node;
		current_node = current_node->next;
	i++;
	}

	if (current_node)
	{
		node_to_delete = current_node;
		prev_node->next = current_node->next;
	}
	}

	if (node_to_delete)
	{
	free(node_to_delete->str);
	free(node_to_delete);
	return (1);
	}

	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head)
{
	if (!head || !*head)
	return;

	list_t *current_node = *head;
	list_t *next_node;

	while (current_node)
	{
	next_node = current_node->next;
	free(current_node->str);
	free(current_node);
	current_node = next_node;
	}

	*head = NULL;
}
