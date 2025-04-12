#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} node;

typedef struct Graph {
  int vertexCount;
  int *visited;
  node **adjacencyList;
} graph;

typedef struct Stack {
  int top;
  int capacity;
  int *items;
} stack;

node *createNode(int value) {
  node *n = malloc(sizeof(node));
  n->data = value;
  n->next = NULL;
  return n;
}

graph *createGraph(int vertexCount) {
  graph *g = malloc(sizeof(graph));
  g->vertexCount = vertexCount;
  g->adjacencyList = malloc(sizeof(node*) * vertexCount);
  g->visited = malloc(sizeof(int) * vertexCount);

  for(int i = 0; i < vertexCount; i++) {
    g->adjacencyList[i] = NULL;
    g->visited[i] = 0;
  }

  return g;
}

void addEdge(graph *g, int src, int dest) {
  node *n = createNode(dest);
  n->next = g->adjacencyList[src];
  g->adjacencyList[src] = n;

  n = createNode(src);
  n->next = g->adjacencyList[dest];
  g->adjacencyList[dest] = n;
}

stack *createStack(int capacity) {
  stack *s = malloc(sizeof(stack));
  s->items = malloc(sizeof(int) * capacity);
  s->top = -1;
  s->capacity = capacity;
  return s;
}

void stackPush(stack *s, int value) {
  if(s->top < s->capacity - 1)
    s->items[++(s->top)] = value;
}

void DFS(graph *g, stack *s, int start) {
  g->visited[start] = 1;
  printf("%d ", start);
  stackPush(s, start);

  node *adj = g->adjacencyList[start];

  while(adj != NULL) {
    int neighbor = adj->data;

    if(g->visited[neighbor] == 0)
      DFS(g, s, neighbor);

    adj = adj->next;
  }
}

void insertEdges(graph *g, int edgeCount, int vertexCount) {
  int src, dest;

  printf("Adaugă %d muchii (de la 0 la %d):\n", edgeCount, vertexCount - 1);

  for(int i = 0; i < edgeCount; i++) {
    scanf("%d%d", &src, &dest);

    if(src >= 0 && src < vertexCount && dest >= 0 && dest < vertexCount)
      addEdge(g, src, dest);
    else
      printf("Noduri invalide. Reîncearcă.\n");
  }
}

void clearVisited(graph *g) {
  for(int i = 0; i < g->vertexCount; i++)
    g->visited[i] = 0;
}

void displayAllDFS(graph *g, stack *s) {
  for(int i = 0; i < g->vertexCount; i++) {
    clearVisited(g);
    s->top = -1;

    printf("\nDFS pornind de la nodul %d:\n", i);
    DFS(g, s, i);
    printf("\n");
  }
}

void freeGraph(graph *g) {
  for(int i = 0; i < g->vertexCount; i++) {
    node *cur = g->adjacencyList[i];
    while(cur) {
      node *next = cur->next;
      free(cur);
      cur = next;
    }
  }

  free(g->adjacencyList);
  free(g->visited);
  free(g);
}

void freeStack(stack *s) {
  free(s->items);
  free(s);
}

int main() {
  int vertexCount, edgeCount;

  printf("Câte noduri are graful? ");
  scanf("%d", &vertexCount);

  printf("Câte muchii are graful? ");
  scanf("%d", &edgeCount);

  graph *g = createGraph(vertexCount);
  stack *s = createStack(2 * vertexCount);

  insertEdges(g, edgeCount, vertexCount);
  displayAllDFS(g, s);

  freeGraph(g);
  freeStack(s);

  return 0;
}
