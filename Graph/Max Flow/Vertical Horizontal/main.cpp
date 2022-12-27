#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include<ctime>
#include <limits>
#include <queue>
#include <set>

using namespace std;
#define INFINITY numeric_limits<int>::max()

int ans = 0;

class Node {
public:

    Node(int value, int number, const long *coordinates, bool isVertical);

    Node(int value, int number);

    bool visited = false;
    unordered_map<Node *, int> adjs;
    int value;
    int number;
    long x1{}, x2{}, y1{}, y2{};
    bool vertical{};
    Node *parent = nullptr;
    string name = "";
};

struct edge {
    int weight;
    int num;
    Node *n1;
    Node *n2;
};

void update_path(const Node *firstNode, Node *destination, pair<Node *const, int> &child);

void test();

static vector<Node *> allNodes;
static vector<Node *> verticalNodes;
static vector<Node *> horizontalNodes;
vector<Node *> MST;
unordered_set<int> allValues;
unordered_map<int, Node *> numToNode;
vector<edge> edges;
int mst_size = 0;
int vertexes = 0;
int max_flow = 0;

Node::Node(int value, int number, const long coordinates[4], bool isVertical) {
    this->value = value;
    this->number = number;
    allNodes.push_back(this);
    if (isVertical)
        verticalNodes.push_back(this);
    else
        horizontalNodes.push_back(this);
    numToNode[value] = this;
    x1 = coordinates[0];
    y1 = coordinates[1];
    x2 = coordinates[2];
    y2 = coordinates[3];
    vertical = isVertical;
}

Node::Node(int value, int number) {
    this->value = value;
    this->number = number;
    allNodes.push_back(this);
}


bool bfs(vector<Node *> nodes, Node *firstNode, Node *destination) {
    for (auto &node: nodes)
        node->visited = false;
    queue<Node *> bfsQueue;
    bfsQueue.push(firstNode);
    firstNode->visited = true;
    while (!bfsQueue.empty()) {
        Node *front = bfsQueue.front();
        bfsQueue.pop();
        for (auto &child: front->adjs) {
            if (!child.first->visited) {
                child.first->parent = front;
                child.first->visited = true;
                bfsQueue.push(child.first);
                if (child.first == destination) {
                    update_path(firstNode, destination, child);
                    return true;
                }
            }
        }
    }
    return false;
}

void update_path(const Node *firstNode, Node *destination, pair<Node *const, int> &child) {
    Node *k = child.first;
    Node *parent;
    vector<int> dists;
    vector<Node *> path;
    while (k != firstNode) {
        dists.push_back(k->parent->adjs[k]);
        path.push_back(k);
        k = k->parent;
    }
    int min = *min_element(dists.begin(), dists.end());
    k = destination;
    while (k != firstNode) {
        parent = k->parent;
        int node_size = parent->adjs[k];
        int new_size = node_size - min;

        if (k->adjs.find(parent) == k->adjs.end())
            k->adjs[parent] = min;
        else
            k->adjs[parent] += min;
        if (new_size == 0)
            (k->parent->adjs).erase(k);
        else
            parent->adjs[k] = new_size;
        k = parent;
    }
    max_flow += min;
}


int main() {
    int numOfNodes;
    cin >> numOfNodes;
    for (int i = 0; i < numOfNodes; ++i) {
        long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1 > x2)
            swap(x1,x2);
        if(y1>y2)
            swap(y1,y2);
        bool isVertical = x1 == x2;
        long nums[] = {x1, y1, x2, y2};
        new Node(0, i + 1, nums, isVertical);
    }
    for (auto &node1: horizontalNodes) {
        for (auto &node2: verticalNodes) {
            if (node2->x1 >= node1->x1 &&
                node2->x1 <= node1->x2 &&
                node1->y1 >= node2->y1 &&
                node1->y1 <= node2->y2) {
                node1->adjs[node2] = 1;
                node2->adjs[node1] = -1;
            }
        }
    }
    Node *s = new Node(0, 0);
    Node *t = new Node(0, 1);
    for (auto &node: horizontalNodes) {
        s->adjs[node] = 1;
    }
    for (auto &node: verticalNodes) {
        node->adjs.clear();
        node->adjs[t] = 1;
    }
    while (bfs(allNodes, s, t));
    cout << allNodes.size() - max_flow + ans - 2;
    return 0;
}

