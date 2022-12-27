#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <limits>
#include <set>

using namespace std;
#define INFINITY numeric_limits<int>::max()

class Node {
public:
    Node(int value, int number);

    bool visited = false;
    unordered_map<Node *, int> adjs;
    int value;
    int number = 1;
    int size = 1;
    Node *last_update;
    Node *point = nullptr;
};

struct edge {
    int weight;
    int num;
    Node *n1;
    Node *n2;
    bool visited = false;
};

static vector<Node *> allNodes;
vector<Node *> MST;
unordered_set<int> allValues;
unordered_map<int, Node *> numToNode;
vector<edge> edges;
int mst_size = 0;
int vertexes = 0;

Node::Node(int value, int number) {
    this->value = value;
    this->number = number;
    allNodes.push_back(this);
    numToNode[value] = this;
    last_update = this;
    point = this;
}

class Compare {
public:
    bool operator()(Node *a, Node *b) {
        return a->value > b->value;
    }
};

void superHeavyEdges(int *road_bits);

void Prim(vector<Node *> &nodeCP) {
    auto cmp = [](Node *a, Node *b) { return a->value < b->value; };
    multiset<Node *, decltype(cmp)> sset(cmp);
    for (auto &node: nodeCP) {
        if (node->value == 0) {
            sset.insert(node);
            break;
        }
    }
    while (!sset.empty()) {
        auto it = sset.begin();
        Node *min = *it;
        sset.erase(it);


        if (!min->visited) {

            MST.push_back(min);
            min->visited = true;
            for (auto &adj: min->adjs) {
                if (adj.second < adj.first->value && !adj.first->visited) {
                    adj.first->value = adj.second;
                    adj.first->last_update = min;
                    sset.insert(adj.first);
                }
            }
        }
        if (sset.empty()) {
            for (auto &node: nodeCP) {
                if (!node->visited) {
                    node->value = 0;
                    sset.insert(node);
                    break;
                }
            }
        }

    }
}

const int MAX_N = 2000;

int sz[MAX_N];
int p[MAX_N];

Node *getpar(Node *v) {
    if (v == v->point)
        return v;
    Node *par = getpar(v->point);
    v->point = par;
    return par;
}

bool mrg(Node *u, Node *v) {
    u = getpar(u);
    v = getpar(v);
    if (u == v)
        return false;
    if (v->size > u->size)
        swap(u, v);
    u->size += v->size;
    v->point = u;
    return true;
}

int Kruskal(vector<edge> &edges) {
    auto cmp = [](edge a, edge b) { return a.weight < b.weight; };
    sort(edges.begin(), edges.end(), cmp);
    vector<edge> msts;
    int ans = 0;
    for (int i = 0; i < edges.size(); i++) {
        edge tt = edges[i];
        Node *n1 = tt.n1;
        Node *n2 = tt.n2;
        if (mrg(n1, n2)) {
            msts.push_back(tt);
            ans += tt.weight;
        }
    }
    return ans;
}


int main() {
    int sum_all = 0;
    int numOfNodes, numOfEdges;
    cin >> numOfNodes >> numOfEdges;
    int road_bits[numOfEdges];
    for (int i = 0; i < numOfNodes; ++i) {
        int num = i == 0 ? 0 : INFINITY;
        new Node(num, i + 1);
    }
    for (int i = 0; i < numOfEdges; ++i) {
        road_bits[i] = 1;
        int node1, node2, edgeWeight;
        cin >> node1 >> node2 >> edgeWeight;
        sum_all += edgeWeight;
        Node *x, *y;
        x = allNodes[node1 - 1];
        y = allNodes[node2 - 1];
        edges.push_back(edge{edgeWeight, i, x, y});
        x->adjs[y] = edgeWeight;
        y->adjs[x] = edgeWeight;
    }
    mst_size = Kruskal(edges);
    for (auto &i: allNodes) {
        i->visited = false;
        i->value = INFINITY;
        i->last_update = i;
        i->point = i;
        i->size = 1;
    }
    superHeavyEdges(road_bits);
    cout << sum_all - mst_size << endl;
    for (int i = 0; i < numOfEdges; i++)
        cout << road_bits[i];
    return 0;
}

void superHeavyEdges(int *road_bits) {
    for (auto &edge: edges) {
        int ww = edge.weight;
        int size = edge.weight;
        edge.n1->adjs[edge.n2] = 0;
        edge.n2->adjs[edge.n1] = 0;
        edge.n1->value = 0;
        edge.weight = 0;
        vector<struct edge> cc(edges);
        size += Kruskal(cc);
        for (auto &i: allNodes) {
            i->visited = false;
            i->value = INFINITY;
            i->last_update = i;
            i->point = i;
            i->size = 1;
        }
        edge.weight = ww;
        edge.n1->adjs[edge.n2] = edge.weight;
        edge.n2->adjs[edge.n1] = edge.weight;
        if (size != mst_size) {
            road_bits[edge.num] = 0;
        }
    }
}

