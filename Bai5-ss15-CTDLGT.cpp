#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
    bool* recursionStack;
} Graph;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));
    graph->recursionStack = (bool*)malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
        graph->recursionStack[i] = false;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

bool dfsCycleCheck(Graph* graph, int vertex) {
    graph->visited[vertex] = true;
    graph->recursionStack[vertex] = true;

    Node* temp = graph->adjLists[vertex];
    while (temp != NULL) {
        int adjVertex = temp->vertex;

        if (!graph->visited[adjVertex]) {
            if (dfsCycleCheck(graph, adjVertex)) {
                return true;
            }
        } else if (graph->recursionStack[adjVertex]) {
            return true;
        }

        temp = temp->next;
    }

    graph->recursionStack[vertex] = false;
    return false;
}

bool hasCycle(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            if (dfsCycleCheck(graph, i)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int vertices, edges;
    printf("Nhap so dinh: ");
    scanf("%d", &vertices);

    printf("Nhap so canh: ");
    scanf("%d", &edges);

    Graph* graph = createGraph(vertices);

    printf("Nhap danh sach canh (u v):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    if (hasCycle(graph)) {
        printf("\n Do thi co chu trinh\n");
    } else {
        printf("\n Do thi khong co chu trinh\n");
    }

    return 0;
}

