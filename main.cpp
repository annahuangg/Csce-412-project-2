#include <string>
#include <queue>
#include "loadBalancer.cpp"

using namespace std;

/// @brief randomly generates true or false
/// @return true or false to determine whether to add new request to requestsQueue
bool getRandomBool() {
	return rand() % 2 == 0;
}

int main() {
	// ask for num of servers and num clock cycles
	int numServers;
	cout << "Please enter number of servers" << endl;
	cin >> numServers;
	int numClockCycles;
	cout << "Please enter number of clock cycles" << endl;
	cin >> numClockCycles;

	// create loadBalancer
	loadBalancer loadBalance = loadBalancer(numClockCycles);
	for (int i = 0; i < numServers; i++) {
		loadBalance.serverVector.push_back(webservers());
	}

	// place requests in queue
	for (int i = 0; i < 20 * numServers; i++) {
		loadBalance.requestsQueue.push(requests(2, 500));
	}

	// print queue size
	cout << "Starting queue size: " << loadBalance.requestsQueue.size() << endl;
	cout << "Range for task times: 2 - 500 clock cycles" << endl;

	// while there are still requests in the queue
	while (!loadBalance.requestsQueue.empty() && loadBalance.currTime <= numClockCycles) {
		loadBalance.currTime += 100;
		// load balancer sends request to server
		loadBalance.sendRequest();
		// server receives request if free
		for (int i = 0; i < loadBalance.serverVector.size(); i++) {
			loadBalance.serverVector.at(i).receiveRequest(i+1, loadBalance.currTime, loadBalance.maxTime);
		}

		for (int i = 0; i < 2; i++) {
			// randomly decide if new request should be added
			if (getRandomBool() && loadBalance.requestsQueue.size() < numServers * 20) {
				loadBalance.requestsQueue.push(requests(2, 500));
			}
		}
	}

	// print ending queue size
	cout << "Ending queue size: " << loadBalance.requestsQueue.size() << endl;

	cout << "finished" << endl;
}