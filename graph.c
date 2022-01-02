#include <stdio.h>
#include <stdlib.h>

typedef struct edge{
    int weight;
    struct node* dest;
    struct edge *next_edge;
}edge;

typedef struct node{
    int id;
    struct node *next;
    edge *edges;
}node;

typedef struct queue{
    int prio;
    node *info;
    struct queue *next;
}priorityQueue;

typedef struct list{
    int id;
    int weight;
    struct list *next;
}list;

int contains(list * l,int id){
    list *tmp=l;
    while(tmp!=NULL){
        if(tmp->id==id){
            return 1;
        }
        tmp=tmp->next;
    }
    return 0;
}
list *add_list(list *l,int id,int weight){
    if(l==NULL){
        l=(list*)malloc(sizeof(list));
        l->id=id;
        l->weight=weight;
        return l;
    }
    list *tmp=l;
    while(tmp->next!=NULL){
        tmp=tmp->next;
    }
    list *li=(list*)malloc(sizeof(list));
    li->id=id;
    li->weight=weight;
    tmp->next=li;
}
void free_li(list *l){
        list *tmp=l;
    while(l!=NULL){
        tmp=l->next;
        free(l);
        l=tmp;
    }
}

int isNotEmpty(priorityQueue *queue){
    if(queue==NULL){
        return 0;
    }
    else{
        return 1;
    }
}
int *pop(priorityQueue *queue){
    int *arr={queue->id,queue->weight};
    if(queue->next==NULL)
    {
        queue=NULL;
    }
    else{
     queue=queue->next;   
    }
    tmp->next=NULL;
    return tmp;
}
priorityQueue *add_prio(priorityQueue *queue,node *info,int prio){
    if(queue==NULL){
        queue=(priorityQueue*)malloc(sizeof(queue));
        queue->info=info;
        queue->prio=prio;
        queue->next=NULL;
        return queue;
    }
    else if(queue->prio>prio){
        priorityQueue *q =(priorityQueue*)malloc(sizeof(priorityQueue));
        q->info=info;
        q->next=queue;
        return q;
    }
    else{
        priorityQueue *tmp=queue;
        while(tmp->next!=NULL && tmp->next->prio<prio){
            tmp=tmp->next;
        }
        if(tmp->next==NULL){
            priorityQueue *q = (priorityQueue*)malloc(sizeof(priorityQueue));
            q->next=NULL;
            q->prio=prio;
            q->info=info;
            return queue;
        }
        else{
            priorityQueue *q = (priorityQueue*)malloc(sizeof(priorityQueue));
            q->next=tmp->next;
            q->info=info;
            q->prio=prio;
            tmp->next=q;
            return queue;
        }
    }
}
void free_prio(priorityQueue *prio){
    priorityQueue *tmp=prio;
    while(prio!=NULL){
        tmp=prio->next;
        free(prio);
        prio=tmp;
    }
}

node* allocate_graph(int num)
{
    // allocates the node list
    node *head = (node*)malloc(sizeof(num));
    if(head==NULL)
    {
        exit(1);
    }
    node *tmp =head;
    for(int i=0;i<num-1;i++){
        tmp->id=i;
        tmp->edges=NULL;
        node *n = (node*)malloc(sizeof(num));
        if(n==NULL){
            exit(1);
        }
        tmp->next=n;
        tmp=tmp->next;
    }
    tmp->id=num-1;
    tmp->edges=NULL;
    tmp->next=NULL;
    return head;
}

//returns the num node
node* get(node *head,int num){
    node *tmp =head;
    int i=0;
    while(i<num && tmp->next!=NULL)
    {
        i++;
        tmp=tmp->next;
    }
    if(i<num)
    {
        return NULL;
    }
    return tmp;
}

node* get_id(node *head,int num){
    node *tmp =head;
    int i=0;
    while(tmp!=NULL)
    {
        if(tmp->id==num){
            return tmp;
        }
        tmp=tmp->next;
    }
    return tmp;
}
//free  the memory of the edges
void free_edges(node *head){
    edge *e=head->edges;
    edge *tmp=e;
    while(tmp!=NULL){
        e=tmp;
        tmp=tmp->next_edge;
        free(e);
    }
}

void free_list(node *head){
    node *tmp=head;
    while(tmp!=NULL){
        head=tmp;
        free_edges(head);
        tmp=tmp->next;
        free(head);
    }
}

// adds a node 
node *add(node *head){
        int i;
        scanf("%d",&i);
        node *added = (node*)malloc(sizeof(node));
        if(added==NULL)
        {
            exit(1);
        }
        added->edges=NULL;
        added->next=NULL;
        added->id=i;
        node *tmp=head;
        edge *e=NULL;
        while(scanf("%d",&i)){
            if(e==NULL){
                
                added->edges=(edge*)malloc(sizeof(edge));
                if(added->edges==NULL)
                {exit(1);}
                e=added->edges;
            }
            else{
                edge *tmp_edge = (edge*)malloc(sizeof(edge));
                if(tmp_edge==NULL)
                {exit(1);}
                e->next_edge=tmp_edge;
                e=tmp_edge;
            }
            e->dest = get(head,i);
            scanf("%d",&i);
            e->weight=i;
            e->next_edge=NULL;
        } 
        if(head->id==added->id)
        {
            added->next=head->next;
            free_edges(head);
            free(head);
            head=added;
            return head;
        }
        else {
        while(tmp->next!=NULL && tmp->next->id!=added->id){
            tmp=tmp->next;
        }
        if(tmp->next==NULL){
            tmp->next=added;
        }
        else{
                node *deleted = tmp->next;
                added->next=deleted->next;
                tmp->next=added;
                free_edges(deleted);
                free(deleted);
        }
        }
        return head;
}



node* load_graph(char *ch_copy,node *f){
    if(f!=NULL){
    free_list(f);
    }
    char numOfNodes[20];
    //gets how many nodes in the graph
    scanf("%s",numOfNodes);
    int num = atoi(numOfNodes);
    //initiates the graph
    node *head = allocate_graph(num);
    char ch;
    // takes the char
    scanf(" %c",&ch);
    // updates the info of the node
    while(ch=='n'){
        int i;
        // gets the node you want to work on
        scanf("%d",&i);
        node *tmp = get(head,i);
        edge *e = tmp->edges;
        while(scanf("%d",&i)){
            if(e==NULL){
                tmp->edges=(edge*)malloc(sizeof(edge));
                if(tmp->edges==NULL)
                {exit(1);}
                e=tmp->edges;
            }
            else{
                edge *tmp_edge = (edge*)malloc(sizeof(edge));
                if(tmp_edge==NULL)
                {exit(1);}
                e->next_edge=tmp_edge;
                e=tmp_edge;
            }
            e->dest = get(head,i);
            scanf("%d",&i);
            e->weight=i;
            e->next_edge=NULL;
        }
        scanf(" %c",&ch);
    }
    *ch_copy=ch;
    return head;
    
}

void print(node *head){
    while(head!=NULL){
        int id = head->id;
        printf("Node: %d\n  edges:\n    {",head->id);
        edge *e = head->edges;
        while(e!=NULL){
            printf("dest: %d, weight: %d",e->dest->id,e->weight);
            e=e->next_edge;
        }
        printf("}\n");
        head=head->next;
    }
}
void delete_edges(node *head, int id){
    node *tmp = head;
    while(tmp!=NULL){
        edge *e =tmp->edges;
        if(e!=NULL)
        {
            if(e!=NULL && e->dest->id ==id){
                tmp->edges=tmp->edges->next_edge;
                free(e);
            }
            else{
                while(e->next_edge!=NULL){
                    if(e->next_edge->dest->id==id)
                    {
                        edge *tmp_edge = e->next_edge;
                        e->next_edge=tmp_edge->next_edge;
                        free(tmp_edge);
                    }
                    e=e->next_edge;
                }
        }
        }
        tmp=tmp->next;
    }
}
node *delete(node *head ,int id){
    delete_edges(head,id);
    if(head->id==id){
        node *tmp=head->next;
        free(head);
        return tmp;
    }
    node *tmp=head;
    while(tmp->next!=NULL){
        if(tmp->next->id==id)
        {
            node *deleted = tmp->next;
            tmp->next=deleted->next;
            free_edges(deleted);
            free(deleted);
            return head;
        }
        tmp=tmp->next;
    }
    
}



int djikstra(node *head,int src,int dest){
  list *li=NULL;
  priorityQueue *queue=NULL;
  queue=add_prio(queue,get_id(head,src),0);
  while(isNotEmpty(queue)){
      int *arr = pop(queue);
      int weight=arr[1];
      int id =arr[0];
      node *n=get_id(head,id);
      if(!contains(li,id)){
          add_list(li,id,weight);
          if(id==dest){
              free_li(li);
              free_prio(queue);
              printf("%d",weight);
              return weight;
          }
          edge * e = n->edges;
          while(e!=NULL){
              weight=weight+e->weight;
              add_prio(queue,e->dest,weight);
              e=e->next_edge;
          }
      }
  }
  free_li(li);
  free_prio(queue);
  printf("-1");
  return -1;
  
    
    
}

int main()
{
    char ch;
    scanf(" %c",&ch);
    node *head=NULL;
    while(ch!= 'k'){
        // receiving a graph
        if(ch=='A'){
            head = load_graph(&ch,head);
        }
        if(ch=='B')
        {
            head=add(head);
        }
        if(ch=='D')
        {
            int id;
            scanf(" %d",&id);
            head=delete(head,id);
        }
        if(ch=='S')
        {
            int src,dest;
            scanf(" %d%d",&src,&dest);
            djikstra(head,src,dest);
        }
        scanf(" %c",&ch);
    }
}
