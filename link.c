#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node_t
{
    double x;
    struct node_t *next;
};

struct node_t *create_node(double n);
void print_node(struct node_t *node);
void print_list(struct node_t *head);
struct node_t *insert_head(struct node_t *head, struct node_t *node);
struct node_t *insert_tail(struct node_t *head, struct node_t *node);
struct node_t *insert_middle(struct node_t *head, struct node_t *node,int pos);
int count_nodes(struct node_t *head);
struct node_t *find(struct node_t *head, double n);
struct node_t *delete(struct node_t *head, double n);
void delete_list(struct node_t *head);

int main(void) 
{

    double n;

    struct node_t *head = NULL;

    int choice;

    while(1)
    {
        printf("1. Add a number\n");
        printf("2. Delete a number\n");
        printf("3. Print all numbers\n");
        printf("4. Count the numbers\n");
        printf("5. Search for a number\n");
        printf("6. Quit\n");
        scanf("%d",&choice);

        switch(choice)
        {

            case 1:

                printf("Enter the number:\n");
                scanf("%lf",&n);
                struct node_t *node = create_node(n);

                printf("1. Insert at the head\n");
                printf("2. Insert in the middle\n");
                printf("3. Insert at the tail\n");
                scanf("%d",&choice);

                switch(choice)
                {
                    case 1:
                        head = insert_head(head,node);
                    break;

                    case 2: ;
                        int pos;

                        printf("Enter the position: ");
                        scanf("%d",&pos);
                        head = insert_middle(head,node,pos);
                    break;

                    case 3:
                        head = insert_tail(head, node);
                    break;
                }

            break;

            case 2:
                printf("Enter the number:\n");
                scanf("%lf",&n);
                head = delete(head,n);
            break;

            case 3:
                print_list(head);
            break;

            case 4: ;
                int count = 0;

                count = count_nodes(head);
                printf("Number of nodes = %d\n",count);
            break;

            case 5:
                printf("Enter the number:\n");
                scanf("%lf",&n);
                struct node_t *found = find(head,n);

                if(found != NULL)
                    printf("%lf was found in the list\n",n);

                if(found == NULL)
                    printf("%lf not found in the list\n",n);
            break;

            case 6:
                delete_list(head);
                return EXIT_SUCCESS;
            break;
        }
    }
}

/** creates new nodes in a linked list
 * @param n number to pass into list
 */
struct node_t *create_node(double n)
{
    struct node_t *node = (struct node_t*)malloc(sizeof(struct node_t));
    node->x = n;
    node->next = NULL;
    return node;
}

/** prints single node in a linked list
 * @param node the array to print
 */
void print_node(struct node_t *node)
{
    printf("%lf ",node->x);
}

/** prints list of linked list nodes
 * @param head starts printing from head node
 */
void print_list(struct node_t *head)
{
    if(head == NULL)
    printf("Empty List\n");
               
    if(head != NULL)           
    {         
        struct node_t *curr = head;
        while(curr != NULL)
        {
            print_node(curr);
            curr = curr->next;
        }
    printf("\n");
    }
}

/** addes a node to the head of a linked list and moves the head over one.
 * @param node the node value to add
 * @param head the prevoius head node to overwrite
 */
struct node_t *insert_head(struct node_t *head, struct node_t *node)
{
    node->next = head;
    head = node;
    return head;
}

/** addes a node to the tail of a linked list
 * @param node the node value to add
 * @param head the head node to start from
 */
struct node_t *insert_tail(struct node_t *head, struct node_t *node)
{
    if(head == NULL)
        return insert_head(head, node);

    if(head != NULL)
    {
    struct node_t *curr = head;
    while(curr->next != NULL)
    {
        curr = curr->next;
    }

    curr->next = node;

    }
    return head;
}

/** addes a node to the middle of a linked list.
 * @param node the node value to add
 * @param head the head node to start from
 * @param pos position of the node to add
 */
struct node_t *insert_middle(struct node_t *head, struct node_t *node,int pos)
{
    if(head == NULL || pos == 0)
        return(insert_head(head,node));

    else if(pos >= count_nodes(head))
        return(insert_tail(head,node));

    else
    {
        struct node_t *curr = head;
        struct node_t *prev = NULL;
        int i = 0;

        while(curr != NULL)
        {

            if(i == pos)
            {
                prev->next = node;
                node->next = curr;
                return head;
            }

            prev = curr;
            curr = curr->next;
            i++;

        }
        return head;
    }
}

/** counts number of nodes in a linked list.
 * @param head the head node to start from
 */
int count_nodes(struct node_t *head)
{
    int count = 0;
    struct node_t *curr = head;

    while(curr != NULL)

    {

        count++;
        curr = curr->next;

    }
    return count;
}

/** finds a value in a linked list
 * @param n value to find
 * @param head the head node to start from
 */
struct node_t *find(struct node_t *head, double n)
{
    struct node_t *curr = head;

    while(curr != NULL)
    {
        if(isgreaterequal(curr->x,n) && islessequal(curr->x,n))
            return curr;

    curr = curr->next;

    }
    return NULL;
}

/** finds and deletes a value in a linked list
 * @param n value to find and delete
 * @param head the head node to start from
 */
struct node_t *delete(struct node_t *head, double n)
{

    struct node_t *foundNode = find(head,n);

    if(foundNode == NULL)
        return head;

    if(foundNode == head)

    {
        head = head->next;
        free(foundNode);
        return head;
    }

    struct node_t *curr = head;

    struct node_t *prev = head;

    while(curr != NULL)
    {

        if(curr == foundNode)
        {
            prev->next = curr->next;
            free(curr);
            return head;
        }

        prev = curr;

        curr = curr->next;
    }
    return head;
}

/** deletes list and frees heap memory
 * @param head the head node to start from
 */
void delete_list(struct node_t *head)
{
    struct node_t *curr;
    while(head != NULL)
    {
        curr = head;
        head = head->next;
        free(curr);
    }
}
