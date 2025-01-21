#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Aaron Rothman  creategraph.cpp
// Note: This program uses string parsing functions from C++11.
// Input assumptions: Constraints are input in the form w1 <= n1 - n2 <= w2, n1 - n2 <= w1, w1 <= n1 <= w2, n1 <= w1, w1 <= n1,
// or w1 <= n1 - n2 and are each on separate lines.
// Input error checking missing: Currently do not check if multiple of the same directional edges are created (with same or different weights)
// Whitespace removal loop influenced by: https://stackoverflow.com/questions/14233065/remove-whitespace-in-stdstring
// For simplicity, integer weights are assumed.
// Node names cannot begin with a digit.
// 10/26/17: Simplified output to be easier to read by FloydWarshall.cpp.

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
      int weight;
      Edge();
      Edge(Node begin1, Node end1, int weight1);
      ~Edge();
};
Edge::Edge()
{
}
Edge::Edge(Node begin1, Node end1, int weight1)
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
string removeWhitespace(string s);
void parseNodes(string s, Graph& graph);
void operator<<(ostream& cout, const Graph& graph);
int main()
{
   Graph graph;
   string line;
   string delimiter1 = "<=";
   string delimiter2 = "-";

   //beginning of time
   Node n0 = Node("0");
   graph.insertNode(n0);
   int j = 1;
   while (getline(cin, line))
   {
      if (line.find_first_of("0123456789") == 0 && line.find(delimiter2) > 0 && line.find(delimiter2) < line.length() && line.find_last_of("0123456789") == line.length()-1)
      {
         //Input of the form w1 <= n1 - n2 <= w2
         size_t delpos;

         delpos = line.find(delimiter1);
         string line1 = line.substr(0, delpos);
         string line2 = line.substr(delpos + 2);
         delpos = line2.find(delimiter2);
         string line21 = line2.substr(0, delpos);
         string line22 = line2.substr(delpos + 1);
         delpos = line22.find(delimiter1);
         string line221 = line22.substr(0, delpos);
         string line222 = line22.substr(delpos + 2);
         
         //Remove whitespace from strings
         string line1w = removeWhitespace(line1);
         string line21w = removeWhitespace(line21);
         string line221w = removeWhitespace(line221);
         string line222w = removeWhitespace(line222);

         //Search for nodes already present and add if not there
         parseNodes(line21w, graph);
         parseNodes(line221w, graph);
         
         //Insert edges
         for (int i = 0; i < graph.nodes.size(); i++)
            for (int j = 0; j < graph.nodes.size(); j++)
            {
               if (graph.nodes[i].name.compare(line21w)==0 && graph.nodes[j].name.compare(line221w)==0)
               {
                  Edge edge1 = Edge(graph.nodes[i], graph.nodes[j], stoi(line222w));
                  Edge edge2 = Edge(graph.nodes[j], graph.nodes[i], -1 * stoi(line1w));
                  graph.insertEdge(edge1);
                  graph.insertEdge(edge2);
               }
            }
      }
      else 
      {
         if (line.find_first_of("0123456789") == 0 && line.find(delimiter2) > 0 && line.find(delimiter2) < line.length())
         {
            //Input of the form w1 <= n1 - n2
            size_t delpos;
            
            delpos = line.find(delimiter1);
            string line1 = line.substr(0, delpos);
            string line2 = line.substr(delpos + 2);
            delpos = line2.find(delimiter2);
            string line21 = line2.substr(0, delpos);
            string line22 = line2.substr(delpos + 1);

            //Remove whitespace from strings
            string line1w = removeWhitespace(line1);
            string line21w = removeWhitespace(line21);
            string line22w = removeWhitespace(line22);

            //Search for nodes already present and add if not
            parseNodes(line21w, graph);
            parseNodes(line22w, graph);
            
            //Insert edge
            //Insert edge
            for (int i = 0; i < graph.nodes.size(); i++)
               for (int j = 0; j < graph.nodes.size(); j++)
               {
                  if (graph.nodes[i].name.compare(line21w) == 0 && graph.nodes[j].name.compare(line22w) == 0)
                  {
                     Edge edge1 = Edge(graph.nodes[j], graph.nodes[i], -1*stoi(line1w));
                     graph.insertEdge(edge1);
                  }
               }
         }
         else
         {
            if (line.find(delimiter2) > 0 && line.find(delimiter2)<line.length())
            {
               //Input of the form n1 - n2 <= w1
               size_t delpos;

               delpos = line.find(delimiter2);
               string line1 = line.substr(0, delpos);
               string line2 = line.substr(delpos + 1);
               delpos = line2.find(delimiter1);
               string line21 = line2.substr(0, delpos);
               string line22 = line2.substr(delpos + 2);

               //Remove whitespace from strings
               string line1w = removeWhitespace(line1);
               string line21w = removeWhitespace(line21);
               string line22w = removeWhitespace(line22);

               //Search for nodes already present and add if not there
               parseNodes(line1w, graph);
               parseNodes(line21w, graph);

               //Insert edge
               for (int i = 0; i < graph.nodes.size(); i++)
                  for (int j = 0; j < graph.nodes.size(); j++)
                  {
                     if (graph.nodes[i].name.compare(line1w)==0 && graph.nodes[j].name.compare(line21w)==0)
                     {
                        Edge edge1 = Edge(graph.nodes[i], graph.nodes[j], stoi(line22w));
                        graph.insertEdge(edge1);
                     }
                  }
            }
            else
            {
               if (line.find_first_of("0123456789") == 0 && (line.find_last_of("0123456789")==line.length()-1))
               {
                  //input of the form w1 <= n1 <= w2
                  size_t delpos;

                  delpos = line.find(delimiter1);
                  string line1 = line.substr(0, delpos);
                  string line2 = line.substr(delpos + 2);
                  delpos = line2.find(delimiter1);
                  string line21 = line2.substr(0, delpos);
                  string line22 = line2.substr(delpos+2);

                  //Remove whitespace from strings
                  string line1w = removeWhitespace(line1);
                  string line21w = removeWhitespace(line21);
                  string line22w = removeWhitespace(line22);

                  //Search for nodes already present and add if not
                  parseNodes(line21w, graph);
                  
                  //Insert edges
                  for (int i = 0; i < graph.nodes.size(); i++)
                     if (graph.nodes[i].name.compare(line21w) == 0)
                     {
                        Edge edge1 = Edge(graph.nodes[0], graph.nodes[i], stoi(line22w));
                        Edge edge2 = Edge(graph.nodes[i], graph.nodes[0], -1 * stoi(line1w));
                        graph.insertEdge(edge1);
                        graph.insertEdge(edge2);
                     }
               }
               else
               {
                  if (line.find_last_of("0123456789") == line.length()-1)
                  {
                     //Input of the form n1 <= w1
                     size_t delpos;

                     delpos = line.find(delimiter1);
                     string line1 = line.substr(0, delpos);
                     string line2 = line.substr(delpos + 2);

                     //Remove whitespace
                     string line1w = removeWhitespace(line1);
                     string line2w = removeWhitespace(line2);

                     //Search for nodes already present  and add if not
                     parseNodes(line1w, graph);

                     //Insert edge
                     for (int i = 0; i < graph.nodes.size(); i++)
                        if (graph.nodes[i].name.compare(line1w) == 0)
                        {
                           Edge edge1 = Edge(graph.nodes[0], graph.nodes[i], stoi(line2w));
                           graph.insertEdge(edge1);
                        }
                  }
                  else
                  {
                     if(line.find_first_of("0123456789") == 0)
                     {
                        //Input of the form w1 <= n1
                        size_t delpos;

                        delpos = line.find(delimiter1);
                        string line1 = line.substr(0, delpos);
                        string line2 = line.substr(delpos + 2);

                        //Remove whitespace
                        string line1w = removeWhitespace(line1);
                        string line2w = removeWhitespace(line2);

                        //Search for nodes already present  and add if not
                        parseNodes(line2w, graph);

                        //Insert edge
                        for (int i = 0; i < graph.nodes.size(); i++)
                           if (graph.nodes[i].name.compare(line2w) == 0)
                           {
                              Edge edge1 = Edge(graph.nodes[0], graph.nodes[i], -1 * stoi(line1w));
                              graph.insertEdge(edge1);
                           }
                     }
                     else
                     {
                        cout << "Input type not known.";
                        break;
                     }
                  }
               }
            }
         }
      }
   }
   cout << graph;
   return 0;
}
string removeWhitespace(string s)
{
   for (size_t i = 0; i < s.length(); i++)
      if (s[i] == ' ')
      {
         s.erase(i, 1);
         i--;
      }
   return s;
}
void parseNodes(string s, Graph& graph)
{
   bool there = false;
   for (int i = 0; i < graph.nodes.size(); i++)
      if (graph.nodes[i].name.compare(s)==0)
      {
         there = true;
         break;
      }
   if (!there)
   {
      Node node = Node(s);
      graph.insertNode(node);
   }
}
void operator<<(ostream& out, const Graph& graph)
{
   out <<graph.nodes.size()<<endl;
   out <<graph.edges.size()<<endl;
   for (int i = 0; i < graph.nodes.size(); i++)
   {
      out << graph.nodes[i].name;
      if(i!=graph.nodes.size()-1)
         out<<"|";
   }
   out << endl;
   for (int i = 0; i < graph.edges.size(); i++)
      out << graph.edges[i].begin.name << "|" << graph.edges[i].end.name << "|" << graph.edges[i].weight << endl;
}