#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} node;

typedef struct Graph {
  int vertices;
  int *visited;
  node **adjacencyLists;
} graph;

node *createNode(int value) {
  node *n = malloc(sizeof(node));
  n->data = value;
  n->next = NULL;
  return n;
}

graph *createGraph(int vertexCount) {
  graph *g = malloc(sizeof(graph));
  g->vertices = vertexCount;
  g->adjacencyLists = malloc(sizeof(node*) * vertexCount);
  g->visited = malloc(sizeof(int) * vertexCount);

  for(int i = 0; i < vertexCount; i++) {
    g->adjacencyLists[i] = NULL;
    g->visited[i] = 0;
  }

  return g;
}

void addEdge(graph *g, int src, int dest) {
  node *n = createNode(dest);
  n->next = g->adjacencyLists[src];
  g->adjacencyLists[src] = n;

  n = createNode(src);
  n->next = g->adjacencyLists[dest];
  g->adjacencyLists[dest] = n;
}

void insertEdges(graph *g, int edgeCount) {
  int src, dest;

  printf("Adaugă %d muchii (de la 0 la %d):\n", edgeCount, g->vertices - 1);

  for(int i = 0; i < edgeCount; i++) {
    scanf("%d%d", &src, &dest);
    if(src >= 0 && src < g->vertices && dest >= 0 && dest < g->vertices)
      addEdge(g, src, dest);
    else
      printf("Muchie invalidă. Reîncearcă.\n");
  }
}

int isEmpty(node *queue) {
  return queue == NULL;
}

void enqueue(node **queue, int value) {
  node *n = createNode(value);

  if(isEmpty(*queue)) {
    *queue = n;
  } else {
    node *temp = *queue;
    while(temp->next) temp = temp->next;
    temp->next = n;
  }
}

int dequeue(node **queue) {
  if(*queue == NULL) return -1;
  int value = (*queue)->data;
  node *temp = *queue;
  *queue = (*queue)->next;
  free(temp);
  return value;
}

void clearVisited(graph *g) {
  for(int i = 0; i < g->vertices; i++) {
    g->visited[i] = 0;
  }
}

void DFS(graph *g, int vertex) {
  g->visited[vertex] = 1;
  printf("%d ", vertex);

  node *temp = g->adjacencyLists[vertex];

  while(temp != NULL) {
    int neighbor = temp->data;

    if(g->visited[neighbor] == 0)
      DFS(g, neighbor);

    temp = temp->next;
  }
}

void BFS(graph *g, int start) {
  node *queue = NULL;

  g->visited[start] = 1;
  enqueue(&queue, start);

  while(!isEmpty(queue)) {
    int current = dequeue(&queue);
    printf("%d ", current);

    node *temp = g->adjacencyLists[current];

    while(temp != NULL) {
      int neighbor = temp->data;

      if(g->visited[neighbor] == 0) {
        g->visited[neighbor] = 1;
        enqueue(&queue, neighbor);
      }

      temp = temp->next;
    }
  }
}

int main() {
  int vertexCount;
  int edgeCount;
  int startVertex;

  printf("Câte noduri are graful? ");
  scanf("%d", &vertexCount);

  printf("Câte muchii are graful? ");
  scanf("%d", &edgeCount);

  graph *g = createGraph(vertexCount);

  insertEdges(g, edgeCount);

  printf("De unde începem DFS? ");
  scanf("%d", &startVertex);
  printf("Parcurgere DFS:\n");
  DFS(g, startVertex);

  clearVisited(g);

  printf("\nDe unde începem BFS? ");
  scanf("%d", &startVertex);
  printf("Parcurgere BFS:\n");
  BFS(g, startVertex);

  printf("\n");

  // Free memory
  for(int i = 0; i < g->vertices; i++) {
    node *temp = g->adjacencyLists[i];
    while(temp) {
      node *next = temp->next;
      free(temp);
      temp = next;
    }
  }

  free(g->adjacencyLists);
  free(g->visited);
  free(g);

  return 0;
}
