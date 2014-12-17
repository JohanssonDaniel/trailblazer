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
        if(v == end){               //Om vi nått slutet, töm kön för att stoppa while loopen
            emptyQueue(vQueue);
        }else{
            for(Edge *tempEdge: graph.getEdgeSet(v)){   //Loopa över alla närliggande bågar
                if(!(tempEdge->finish->visited)){       //Om vi inte redan varit vid noden i bågslutet
                    tempEdge->finish->visited = true;
                    tempEdge->finish->setColor(YELLOW);
                    tempEdge->finish->previous = v;     //Sätt previous till v för att kunna bygga upp path senare
                    vQueue.push(tempEdge->finish);
                }
            }
        }
        v->setColor(GREEN);
    }
    Vertex* tempV = end;
    while(tempV != start){                              //Går igenom alla previous och lägger in dem först i path
        path.emplace(path.begin(),tempV);
        tempV = tempV->previous;
    }
    path.emplace(path.begin(),tempV);
    return path;
}

void setToInfinity(BasicGraph& graph){
    for(Edge* edge : graph.getEdgeSet()){
        edge->finish->cost = POSITIVE_INFINITY;         //Sätter alla noders cost till inf
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
    pq.enqueue(start,start->cost);  //Lägger in start med 0 som kostnad
    while(!(pq.isEmpty())){
        Vertex* v = pq.dequeue();
        v->setColor(GREEN);
        v->visited = true;
        if(v == end){               //Om vi nått slutet töm kön för att avsluta while loopen
            pq.clear();
        }else{
            for(Edge* edge : graph.getEdgeSet(v)){
                if(!(edge->finish->visited)){   //Om vi inte redan varit i slutet av bågen
                    edge->finish->setColor(YELLOW);
                    double cost = (v->cost + edge->cost);   //Räkna ut kostnaden för noden med v:s kostnad + bågkostnaden
                    if(cost < edge->finish->cost){          //Om den nya konstaden är lägre
                        edge->finish->cost = cost;          //Uppdatera kostnaden
                        edge->finish->previous = v;         //Sätt previous för att kunna backtracka
                        if(checkInPriorityQueue(pq,edge->finish)){ //Finns den redan i kön
                            pq.changePriority(edge->finish,cost);   //Uppdatera kostnaden
                        }else{
                            pq.enqueue(edge->finish,cost);          //Annars lägg in den som nytt element i kön
                        }
                    }
                }
            }
        }
    }

    Vertex* tempV = end;
    while(tempV != start){
        path.emplace(path.begin(),tempV);  //Går igenom alla previous och lägger in dem först i path
        tempV = tempV->previous;
    }
    path.emplace(path.begin(),tempV);

    return path;
}
//Samma som dijsktras
vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    setToInfinity(graph);
    vector<Vertex*> path;
    start->cost = 0;
    start->visited = true;
    PriorityQueue<Vertex*> pq;
    start->setColor(YELLOW);
    pq.enqueue(start,start->heuristic(end)); //Förutom att kostnaden till slutet används
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
