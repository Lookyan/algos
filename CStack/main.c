#include <stdio.h>
#include <stdlib.h>
#define buffer_size 100

struct node
{
    char data;
    struct node *next;
};

void show(struct node *head)
{
    printf("Stack: \t");
    if(head==NULL)printf("empty\t");
    else{
    while(head != NULL){
        printf("%c",head->data);
        head = head->next;
    }
    printf("\t");
    }
}

void push (struct node **head, char val)
{
    printf("PUSH\t %c\n",val);
    struct node *temp = malloc(sizeof(struct node));
    temp->data = val;
    temp->next = *head;
    *head = temp;
}

char pop (struct node **head)
{
    char temp = (char)255;
    if(head == NULL) return temp;
    temp = (*head)->data;
    *head = (*head)->next;
    return temp;
}

int main(int argc, char *argv[])
{
    char *buffer = (char*)calloc(buffer_size, sizeof(char));
    FILE *to_read;
    to_read = fopen(argv[1],"r");
    int size = 0;
    while((buffer[size] = fgetc(to_read)) != EOF){
        size++;
    }
    fclose(to_read);
    buffer[size]='\0';
    printf("---------------------------------------------------------------\n");
    printf("Here the string:\t%s\n\n", buffer);
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
    struct node *head = NULL;
    int counter = 0;
    for(counter = 0; counter < size; ++counter)
    {
        printf("%d.%c\t",counter+1,buffer[counter]);
        show(head);
        switch(buffer[counter])
        {
        case '{':
            push(&head,buffer[counter]);
            break;
        case '}':
            if(head == NULL || head->data != '{')
            {
                printf("it's wrong\n");
                counter = size;
                break;
            }
            if(head->data == '{') printf("POP\t %c\n",pop(&head));
            break;
        case '[':
            push(&head,buffer[counter]);
            break;
        case ']':
            if(head == NULL || head->data != '[')
            {
                printf("it's wrong\n");
                counter = size;
                break;
            }
            if(head->data == '[') printf("POP\t %c\n",pop(&head));
            break;
        case '(':
            push(&head,buffer[counter]);
            break;
        case ')':
            if(head == NULL || head->data != '(')
            {
                printf("it's wrong\n");
                counter = size;
                break;
            }
            if(head->data == '(') printf("POP\t %c\n",pop(&head));
            break;
        default:
            printf("skipping...\n");
            break;
        }
    }
    if(counter == size && head == NULL) printf("------------------------------OKAY-----------------------------\n");
    else printf("----------------------------MISTAKE----------------------------\n");
    free(buffer);
    return 0;
}
