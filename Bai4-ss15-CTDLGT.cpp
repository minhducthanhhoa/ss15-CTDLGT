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
    bool* recStack;
} Graph;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));
    graph->recStack = (bool*)malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
        graph->recStack[i] = false;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

bool dfsCycle(Graph* graph, int vertex) {
    graph->visited[vertex] = true;
    graph->recStack[vertex] = true;

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;

        if (!graph->visited[adjVertex] && dfsCycle(graph, adjVertex)) {
            return true;
        }
        else if (graph->recStack[adjVertex]) {
            return true;
        }

        temp = temp->next;
    }

    graph->recStack[vertex] = false;
    return false;
}

bool hasCycle(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            if (dfsCycle(graph, i)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int V, E;
    printf("Nhap so dinh: ");
    scanf("%d", &V);
    printf("Nhap so canh: ");
    scanf("%d", &E);

    Graph* graph = createGraph(V);

    printf("Nhap danh sach cac canh (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    if (hasCycle(graph)) {
        printf("\nDo thi co chu trinh\n");
    } else {
        printf("\nDo thi khong co chu trinh\n");
    }

    return 0;
}

