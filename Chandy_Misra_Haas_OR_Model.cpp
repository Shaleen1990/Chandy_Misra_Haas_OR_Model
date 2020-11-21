#include <iostream>
#include <vector>
#include <stdio.h>
#include <conio.h>
using namespace std;
#define detected 1
#define notDetected 0


int DeadLockDetection_func(vector<std::vector<int>> &graph, int init, int dest); 	//Deadlock Detection Function
void getGraph(vector<vector<int>> mat);		//This Function will display the graph
int numOfProccesses;		//Variable : Number of proccesses in the system
bool deadLock = 0;	//Boolean Variable : 0 for false, 1 for true


void getGraph(vector<vector<int>> wait_graph)
{
	int n = wait_graph.at(0).size();
	int m = wait_graph.size();
	
	cout << "\t";
	for (int j = 0; j < m; j++) {
		cout << "S" << (j + 1) << "\t";
	}
	cout << endl;	

	for (int i = 0; i<m; i++)
	{
		cout << "S" << (i + 1) << "\t";
		for (int j = 0; j<n; j++)
		{
			cout << wait_graph.at(i).at(j) << "\t";
		}
		cout << "\n";
	}
}

int DeadLockDetection_func(vector<std::vector<int>> &graph, int init, int dest)
{
	int end = numOfProccesses;
	deadLock = notDetected;
	for (int col = 0; col < end; col++)
	{
		if (graph[dest][col] == 1)
		{
			if (init == col)
			{
				deadLock = detected;
				continue;
			}
			deadLock = DeadLockDetection_func(graph, init, col);
			//if single path found without any deadlock then there is no deadlock
			if (deadLock == notDetected) {
				return deadLock;
			}
		}
	}
	return deadLock;
}

int main() {
	int processIdForProbe;		//Proccess ID of the proccess initiating the probe
	
	cout << "Enter the number of processes ####The value should be greater than 1####" << endl;		//Enter the number of proccesses in the system
	cin >> numOfProccesses;
	
	if (numOfProccesses > 1) 
	{
		cout << "Enter the wait graph >> " << endl;		//Enter the wait-graph. (nxn) matrix.

		vector<vector<int>> wait_graph(numOfProccesses);		

		for (int from = 0; from < numOfProccesses; from++)		//Input the wait graph values
		{
			for (int to = 0; to < numOfProccesses; to++)
			{
				int temp;
				cin >> temp;
				wait_graph.at(from).push_back(temp);
			}
		}

		cout << endl;
		cout << "The wait for graph is >> " << endl << endl;

		getGraph(wait_graph);		//display wait for graph
		cout << endl;

		cout << "Enter the Proccess Number intiating the Probe ####The number should be between 1 and numOfProccesses####" << endl;	//Enter the proccess initiating the probe
		cin >> processIdForProbe;
		cout << endl;
		processIdForProbe--;

		
		cout << "Initiating Probe !!!" << endl << endl;	//Initializing the probe to detect deadlock
		cout << "DIRECTION" << "\t" << "PROBE" << endl;

		//Detecting deadlock
		// Loop through process which is waiting for the resource
		deadLock = detected;
		for (int col = 0; col < numOfProccesses; col++)
		{
			if (wait_graph.at(processIdForProbe).at(col) == 1)
			{
				if (DeadLockDetection_func(wait_graph, processIdForProbe, col) == notDetected){
					deadLock = notDetected;
					cout<<"Deadlock not detected ";
					break;
				}
			}
		}
	}
	else {
		cout << "No Proccess Found !!!. Dedlock can not be detected" << endl;
	}
	if (deadLock == detected){
		cout<<"DeadLock detected ";
	}
	getch();
	return 0;
}

