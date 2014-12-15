// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <set>
#include <vector>
#include "pqueue.h"
#include <queue>
using namespace std;
void depthFirstSearchHelper(BasicGraph& graph, vector<Vertex*> &path, Vertex* start, Vertex* end,bool &finished){

    start->visited = true;
    start->setColor(GREEN);
    path.push_back(start);
    if (start == end){                              //om vi kommit till slutet
        finished = true;
    }else{
        auto edges = start->arcs;
        for(auto it = edges.begin(); !finished && it != edges.end(); ++it){  //För varje edge för den här punkten
            Arc* tempArc = *it;
            if(!(tempArc->visited) && !finished && !(tempArc->finish->getColor() == GREEN)){      //Om vi inte redan varit här och vi är inte klara
                graph.getInverseEdge(tempArc)->visited = true;
                depthFirstSearchHelper(graph,path,tempArc->finish,end,finished);
            }
        }
    }
    if(!finished){                                  //Markera som eleminerad väg
        path.pop_back();
        start->setColor(GRAY);
    }else{
        return;                                     //Retunera void för det rekursiva anropet
    }
}
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    bool finished = false;

    depthFirstSearchHelper(graph,path, start,end,finished);
    return path;
}
void emptyQueue(queue<Vertex*> &queue){
    while(!(queue.empty())){
        queue.pop();
    }
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    vector<Vertex*> path;
    queue<Vertex*> vQueue;
    start->visited = true;

    start->setColor(YELLOW);
    vQueue.push(start);

    while(!(vQueue.empty())){
        Vertex* v = vQueue.front();
        vQueue.pop();
        if(v == end){
            emptyQueue(vQueue);
        }else{
            for(Edge *tempEdge: graph.getEdgeSet(v)){
                if(!(tempEdge->finish->visited)){
                    tempEdge->finish->visited = true;
                    tempEdge->finish->setColor(YELLOW);
                    tempEdge->finish->previous = v;
                    vQueue.push(tempEdge->finish);
                }
            }
        }
        v->setColor(GREEN);
    }
    Vertex* tempV = end;
    while(tempV != start){
        path.emplace(path.begin(),tempV);
        tempV = tempV->previous;
    }
    path.emplace(path.begin(),tempV);
    return path;
}
class lessThanByCost{
public:
    bool operator()(Vertex* v1, Vertex* v2){
        return v1->cost > v2->cost;
    }
};
void setToInfinity(BasicGraph& graph){
    for(Edge* edge : graph.getEdgeSet()){
        edge->finish->cost = POSITIVE_INFINITY;
    }
}

bool checkInPriorityQueue(PriorityQueue<Vertex*> pq, Vertex* v){
    while(!(pq.isEmpty())){
        Vertex* v2 = pq.dequeue();
        if(v == v2) {
            return true;
        }
    }
    return false;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    setToInfinity(graph);
    vector<Vertex*> path;
    start->cost = 0;
    start->visited = true;
    PriorityQueue<Vertex*> pq;
    start->setColor(YELLOW);
    pq.enqueue(start,start->cost);
    while(!(pq.isEmpty())){
        Vertex* v = pq.dequeue();
        v->setColor(GREEN);
        v->visited = true;
        if(v == end){
            pq.clear();
        }else{
            for(Edge* edge : graph.getEdgeSet(v)){
                if(!(edge->finish->visited)){
                    edge->finish->setColor(YELLOW);
                    double cost = (v->cost + edge->cost);
                    if(cost < edge->finish->cost){
                        edge->finish->cost = cost;
                        edge->finish->previous = v;
                        if(checkInPriorityQueue(pq,edge->finish)){
                            pq.changePriority(edge->finish,cost);
                        }else{
                            pq.enqueue(edge->finish,cost);
                        }
                    }
                }
            }
        }
    }

    Vertex* tempV = end;
    while(tempV != start){
        path.emplace(path.begin(),tempV);
        tempV = tempV->previous;
    }
    path.emplace(path.begin(),tempV);

    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    setToInfinity(graph);
    vector<Vertex*> path;
    start->cost = 0;
    start->visited = true;
    PriorityQueue<Vertex*> pq;
    start->setColor(YELLOW);
    pq.enqueue(start,start->heuristic(end));
    while(!(pq.isEmpty())){
        Vertex* v = pq.dequeue();
        v->setColor(GREEN);
        v->visited = true;
        if(v == end){
            pq.clear();
        }else{
            for(Edge* edge : graph.getEdgeSet(v)){
                if(!(edge->finish->visited)){
                    edge->finish->setColor(YELLOW);
                    double cost = (v->cost + edge->cost);
                    if(cost < edge->finish->cost){
                        edge->finish->cost = cost;
                        edge->finish->previous = v;
                        double endCost = cost + edge->finish->heuristic(end);

                        if(checkInPriorityQueue(pq,edge->finish)){
                            pq.changePriority(edge->finish,endCost);
                        }else{
                            pq.enqueue(edge->finish,endCost);
                        }
                    }
                }
            }
        }
    }

    Vertex* tempV = end;
    while(tempV != start){
        path.emplace(path.begin(),tempV);
        tempV = tempV->previous;
    }
    path.emplace(path.begin(),tempV);

    return path;
}
