#include <iostream>

using namespace std;


// this is our class graph
class Graph
{ 
public:
    // this will store the nodes in the adjacency list
    struct node 
    {
        int val = 0;
        node *next = nullptr;
	    //bool visited;
    };

    // this will store the head of all the list for the nodes
    int numVertices; 
    node *graphArray = NULL;
    // constructor
    Graph(int n)
    { 
        this->numVertices = n;
        graphArray = new node[numVertices];
        // initially all the list are null
        for (int i = 0; i < numVertices; i++)
        {
			graphArray[i].next = nullptr;
            graphArray[i].val = i;
        } 
    }

    // utility function for adding the edge
    void addEdge(int origin, int dest)
    {
        node* insertNode = new node;
        insertNode->val = dest;
        insertNode->next = NULL;
        node location = graphArray[origin];
        while(location.next)
        {
            location = location.next;
        }
        location.next = insertNode;
    }

    // this will remove the edge
    void removeEdge(int origin, int dest)
    {   
        node* ptr = graphArray[origin];
		node nextNode;
		while(ptr->next)
        {
            if(ptr->next->val == dest)
            {
				nextNode = *ptr->next;
				delete ptr->next;
				ptr->next = nextNode.next;
				return;
            }
            ptr = ptr->next;
        }
        // uh oh not goods
		return;
		/* if(graphArray[origin]->val = dest)
        {
            graphArray[origin] = graphArray[origin]->next;
            return;
        }
        struct node *ptr = graphArray[origin];
        struct node *prev = ptr;
        while (ptr->val != dest)
        {
            prev = ptr;
            ptr = ptr->next;
        }
        prev->next = ptr->next;
        delete ptr; */
    }

    // this will check about edge existence or not
    bool hasEdge(int origin, int dest)
    {
        node* ptr = graphArray[origin];
        while(ptr->next)
        {
            if(ptr->next->val == dest)
            {
                return true;
            }
        }
        return false;
        /* struct node *ptr = graphArray[origin];
        while (ptr != NULL && ptr->val != dest)
        {
            ptr = ptr->next;
        }
        return ptr != NULL; */
    }
    // this will return the list as it contain the outedges
    void outEdges(int origin)
    {
        node* ptr = graphArray[origin];
        while(ptr->next)
        {
            ptr = ptr->next;
            cout << ptr->val << " ";
        }
        cout << endl;
    }
    // here we will check for every other vertex if it is connected with the given vertex with the help of hasEdge() function
    // TODO: fix inEdges
    node *inEdges(int dest)
    {
        for(int i = 0; i < numVertices; i++)
        {
            if(hasEdge(i, dest))
            {
                cout << i << " ";
            }
        }
        cout << endl;
        /* node *head = NULL;
        node *ptr = NULL;
        for (int j = 0; j < numVertices; j++)
        {
            if (hasEdge(j, i))
            {
                if (head == NULL)
                {
                    head = new node;
                    head->val = j;
                    head->next = NULL;
                    ptr = head;
                }
                else
                {
                    ptr->next = new node;
                    ptr = ptr->next;
                    ptr->val = j;
                    ptr->next = NULL;
                }
            }
        }
        return head; */
    }
    // this function will print the graph
    void printGraph()
    {
        node* ptr;
        for (int i = 0; i < numVertices; i++)
        {
            ptr = graphArray[i];
            cout << ptr->val << " -> ";
            while(ptr)
            {
                ptr = ptr->next;
                cout << ptr->val << " -> ";
            }
            cout << endl;
        }
    }
    
    void DFSVisited(node startNode, bool visited[]){
		/*
        //Mark node as visited
        startNode.visited = true;

        */
	}

    void depthFirstSearch(node startNode){
		/*
        //Make a list of indices and mark them all as not visited
        bool *visited = new bool[numVertices];
        for(unsigned i = 0; i < numVertices; i++){
            visited[i] = false
		}
        //recursive function going through indices
        DFSVisited(startNode, visited)
        */
	}

    // this is our destructor which will delete all the memory
    // TODO: first destructor
    ~Graph()
    {
        /* node *ptr;
        // this loop will first delete the every element of the list
        for (int i = 0; i < numVertices; i++)
        {
            ptr = graphArray[i];
            while (ptr->next != NULL)
            {
                struct node *lptr = ptr;
                ptr = ptr->next;
                delete lptr;
            }
        } */
        // now delete the list itself
        delete[] graphArray;
    }
};

/* int main()
{
    Graph *graph = new Graph(5);
    graph->addEdge(0, 1);
    graph->addEdge(0, 4);
    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(1, 4);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);
    graph->addEdge(4, 2);
    graph->printGraph();
    cout << "graph after removing the edge (1,3)";
    graph->removeEdge(1, 3);
    graph->printGraph();
    cout << " the list of elements having 0 as outedge";
    struct node *ptr = graph->outEdges(0);
    while (ptr != NULL)
    {
        cout << " " << ptr->val;
        ptr = ptr->next;
    }
    cout << "\numVertices";
    cout << "the list of elements having 3 as indedge ";
    struct node *lptr = NULL;
    ptr = graph->inEdges(3);
    while (ptr != NULL)
    {
        cout << " " << ptr->val;
        lptr = ptr;
        ptr = ptr->next;
        delete lptr;
    }
    cout << "\numVertices";
} */