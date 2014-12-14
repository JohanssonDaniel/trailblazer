// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <set>
#include <vector>
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

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {

    vector<Vertex*> path;
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
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
