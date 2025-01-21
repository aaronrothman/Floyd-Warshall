#include <iostream>
#include <vector>
#include <limits>
#include <string>
using namespace std;
//Aaron Rothman FloydWarshall.cpp
//Accepts output of creategraph.cpp
//Currently only accept integer weights, can change upon request.
//Have not yet tried using on an unsatisfiable constraint network.  Will be done soon.
//This was, admittedly, written quickly, so I have not yet added comments.  Though, I think the code is pretty self-explanitory
//when paired along with the comments in creategraph.cpp.

class Node {
   public:
      string name;
      Node();
      Node(string name1);
      ~Node();
};
Node::Node()
{
}
Node::Node(string name1)
{
   name = name1;
}
Node::~Node()
{
}
class Edge {
   public:
      Node begin;
      Node end;
      double weight;
      Edge();
      Edge(Node begin1, Node end1, double weight1);
      ~Edge();
};
Edge::Edge()
{
}
Edge::Edge(Node begin1, Node end1, double weight1)
{
   begin = begin1;
   end = end1;
   weight = weight1;
}
Edge::~Edge()
{
}
class Graph {
   public:
      vector<Node> nodes;
      vector<Edge> edges;
      Graph();
      ~Graph();
      void insertNode(Node node);
      void insertEdge(Edge edge);
};
Graph::Graph()
{
}
Graph::~Graph()
{
}
void Graph::insertNode(Node node)
{
   nodes.push_back(node);
}
void Graph::insertEdge(Edge edge)
{
   edges.push_back(edge);
}
string splitNodesString(string s,string delimiter, Graph& graph);
void parseNodes(string s, Graph& graph);
void splitEdgeString(string s, string delimiter,Graph& graph);
void parseEdges(string s1, string s2, string s3, Graph& graph);
int getNodeIndex(Node n, Graph graph);
int main()
{
   Graph graph;
   string numNodes1;
   getline(cin,numNodes1);
   int numNodes = stoi(numNodes1);
   string numEdges1;
   getline(cin,numEdges1);
   int numEdges = stoi(numEdges1);
   string lineOfNames;
   getline(cin,lineOfNames);
   
   string delimiter = "|";
   for(int i=0; i<numNodes; i++)
      lineOfNames = splitNodesString(lineOfNames,delimiter,graph);
   
   string edgeLine;
   for(int i=0; i<numEdges; i++)
   {
      getline(cin,edgeLine);
      splitEdgeString(edgeLine,delimiter,graph);
   }
   
   int MinPath[numNodes][numNodes];
   for(int i=0; i<numNodes; i++)
      for(int j=0; j<numNodes; j++)
         MinPath[i][j] = numeric_limits<int>::max()/2;
   for(int i = 0; i<numNodes; i++)
      for(int j = 0; j<numNodes; j++)
         if(i==j)
            MinPath[i][j]=0;
   for(int i =0; i<numEdges; i++)
      MinPath[getNodeIndex(graph.edges[i].begin,graph)][getNodeIndex(graph.edges[i].end,graph)]=graph.edges[i].weight;
   for(int k=0; k<numNodes; k++)
      for(int i=0; i<numNodes; i++)
         for(int j=0; j<numNodes; j++)
            if(MinPath[i][j]>MinPath[i][k]+MinPath[k][j])
               MinPath[i][j] = MinPath[i][k] + MinPath[k][j];
   //Begin output
   cout<<"The minimal network is:\n   ";
   size_t maxNodeNameLength = 0;
   for(int i=0; i<numNodes; i++)
      if(maxNodeNameLength<(graph.nodes[i].name+"|").length())
         maxNodeNameLength=(graph.nodes[i].name+"|").length();
   size_t maxIntervalTextLength = 0;
   for(int i=0; i<numNodes; i++)
      for(int j=0; j<numNodes; j++)
         if(maxIntervalTextLength<("["+to_string(-1*MinPath[j][i])+","+to_string(MinPath[i][j])+"]").length())
            maxIntervalTextLength=(" ["+to_string(-1*MinPath[j][i])+","+to_string(MinPath[i][j])+"] ").length();
   for(size_t i=0; i<maxNodeNameLength-3; i++)
      cout<<" ";
   for(int i = 0; i<numNodes; i++)
   {
      for(size_t j=graph.nodes[i].name.length(); j<maxIntervalTextLength; j++)
         cout<<" ";
      cout<<graph.nodes[i].name;
   }
   cout<<endl;
   for(size_t i=0; i<maxNodeNameLength+1; i++)
      cout<<" ";
   for(size_t i=0; i<maxIntervalTextLength*numNodes; i++)
      cout<<"-";
   cout<<endl;
   for(int i=0; i<numNodes; i++)
   {
      for(size_t n=graph.nodes[i].name.length(); n<maxNodeNameLength; n++)
         cout<<" ";
      cout<<graph.nodes[i].name + "|";
      for(int j=0; j<numNodes; j++)
      {
         if(i==j)
         {
            string s = " ["+to_string(MinPath[i][j])+"] ";
            for(size_t m=s.length(); m<maxIntervalTextLength; m++)
               cout<<" ";
            cout<<s;
         }
         else
         {
            string s = " ["+to_string(-1*MinPath[j][i])+","+to_string(MinPath[i][j])+"] ";
            for(size_t m=s.length(); m<maxIntervalTextLength; m++)
               cout<<" ";
            cout<<s;
         }
      }
      cout<<endl;
   }
   return 0;
}
int getNodeIndex(Node n, Graph graph)
{
   for(int i=0; i<graph.nodes.size(); i++)
      if(n.name.compare(graph.nodes[i].name)==0)
         return i;
}
string splitNodesString(string s,string delimiter,Graph& graph)
{
   size_t delpos;
   
   delpos = s.find(delimiter);
   string s1 = s.substr(0,delpos);
   string s2 = s.substr(delpos+1);
   
   parseNodes(s1,graph);
   
   return s2;
}
void splitEdgeString(string s, string delimiter,Graph& graph)
{
   size_t delpos;
   
   delpos = s.find(delimiter);
   string s1 = s.substr(0,delpos);
   string s2 = s.substr(delpos+1);
   
   delpos = s2.find(delimiter);
   string s21 = s2.substr(0,delpos);
   string s22 = s2.substr(delpos+1);
   parseEdges(s1,s21,s22,graph);
}
void parseNodes(string s, Graph& graph)
{
   Node node = Node(s);
   graph.insertNode(node);
}
void parseEdges(string s1,string s2,string s3,Graph& graph)
{
   Edge edge = Edge(s1,s2,stoi(s3));
   graph.insertEdge(edge);
}