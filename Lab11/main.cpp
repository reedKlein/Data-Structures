#include "graph.h"

using namespace std;

int main()  
{
    Graph userGraph(3);
    int userChoice = 0;
    do{
        cout << "*****************************************" << endl;
        cout << "Press 1 to add an edge to graph." << endl;
        cout << "Press 2 to remove an edge from graph." << endl;
        cout << "Press 3 to find an edge in the graph." << endl;
        cout << "Press 4 to find the out edges of a vertex." << endl;
        cout << "Press 5 to find the in edges of a vertex." << endl;
        cout << "Press 6 to exit." << endl;
        cout << "*****************************************" << endl;
        cin >> userChoice;
        cout << endl;
        
        // Edge
        if (userChoice == 1)
        {
            int val1;
            int val2;
            cout << "Enter the first value for the edge to add: " << endl;
            cin >> val1;
            cout << "Enter the second value for the edge to add: " << endl;
            cin >> val2;
            userGraph.addEdge(val1, val2);
            cout << "Graph state is now: " << endl;
            userGraph.printGraph();
            cout << endl;
        }

        // Remove
        else if (userChoice == 2)
        {
            int val1;
            int val2;
            cout << "Enter the first value for the edge to remove: " << endl;
            cin >> val1;
            cout << "Enter the second value for the edge to remove: " << endl;
            cin >> val2;
            userGraph.removeEdge(val1, val2);
            cout << "Graph state is now: " << endl;
            userGraph.printGraph();
            cout << endl;
        }
        else if (userChoice == 3)
        {
            int val1;
            int val2;
            cout << "Enter the first value for the edge to find: " << endl;
            cin >> val1;
            cout << "Enter the second value for the edge to find: " << endl;
            cin >> val2;
            if (userGraph.hasEdge(val1, val2))
            {
                cout << "Edge has been found in the graph." << endl;
            }
            else
            {
                cout << "Edge has not been found in the graph." << endl;
            }
        }
        else if (userChoice == 4)
        {
            int val1;
            cout << "Enter the value to find outedges for: " << endl;
            cin >> val1;
            cout << "The list of elements having " << val1 << " as outedge: ";
            userGraph.outEdges(val1);
            /* struct node *ptr = userGraph.outEdges(val1);
            while (ptr != NULL)
            {
                cout << " " << ptr->val;
                ptr = ptr->next;
            }*/
            cout << endl;
        }
        else if (userChoice == 5)  
        {
            int val1;
            cout << "Enter the value to find inedges for: " << endl;
            cin >> val1;
            cout << "the list of elements having " << val1 << " as inedge: ";
            userGraph.inEdges(val1);
            /* struct node *lptr = NULL;
            struct node* ptr = userGraph.inEdges(val1);
            while (lptr != NULL)
            {
                cout << " " << ptr->val;
                lptr = ptr;
                ptr = ptr->next;
                delete lptr;
            } */
            cout << endl;
        }
    }
    while(userChoice != 6);
    
    
    


}