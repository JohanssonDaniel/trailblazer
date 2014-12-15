// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <set>
#include <vector>
#include "pqueue.h"
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
void breadthFirstSearchHelper(BasicGraph& graph, vector<Vertex*> path, Vertex* start, Vertex* end){

}
vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    /*graph.resetData();

    path.push_back(start);
    while(!path.empty()){
        for(Vertex *vertex : path){
            vertex->visited = true;
            for(Edge* edge : graph.getEdgeSet(vertex)){
                if(!(edge->visited)){
                    if(!(edge->finish->visited)){
                        edge->visited = true;
                        edge->finish->visited = true;
                        path.push_back(edge->finish);
                    }else{

                    }
                }
            }
        }
    }*/
    vector<Vertex*> path;
    return path;
}
vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    graph.resetData();
    vector<Vertex*> path;
    start->cost = 0;
    PriorityQueue<Vertex*> pq;
    start->setColor(YELLOW);
    pq.enqueue(start,start->cost);
    while(!(pq.isEmpty())){
        int size = pq.size() - 1;
        PriorityQueue<Vertex*> tempPq;

        cout << "Highest cost: " << pq.peek()->toString() << endl;
        for(int i = 0; i < size; ++i){
            Vertex* tempV = pq.dequeue();
            tempPq.enqueue(tempV,tempV->cost);
        }
        Vertex* v = pq.dequeue();
        v->setColor(GREEN);
        cout << "v: " << v->toString() << "pq-size: " << tempPq.size() << endl;
        if(v == end){
            pq.clear();
        }else{
            for(Edge* edge : graph.getEdgeSet(v)){
                if(!(edge->finish->visited)){
                    edge->finish->setColor(YELLOW);
                    int cost = (v->cost + edge->cost);
                    edge->cost;
                    if(cost < edge->finish->cost || edge->finish->cost == 0.0){
                        edge->finish->cost = cost;
                        edge->finish->previous = v;
                        tempPq.enqueue(edge->finish,cost);
                    }
                }
            }
        }
        int tempSize = tempPq.size();
        for(int i = 0; i < tempSize; ++i){
            Vertex* tempV = tempPq.dequeue();
            pq.enqueue(tempV,tempV->cost);
        }
    }

    Vertex* tempV = end;
    while(tempV != start){
        path.emplace(path.begin(),tempV);
        tempV = tempV->previous;
    }
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
