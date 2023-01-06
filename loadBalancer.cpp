#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include "webservers.cpp"

using namespace std;

/// @brief LoadBalancer manages flow of requests servers
class loadBalancer {
	public:
		/// @brief queue of type requests
		queue<requests> requestsQueue;

		/// @brief tracks the current clock cycle to output performance
		int currTime;

		/// @brief maximum num of clock cycles entered by user
		int maxTime;

		/// @brief vector of webservers names
		vector<webservers> serverVector;

		/// @brief construct loadBalancer given maximum number of clock cycles
		loadBalancer(int maxTime) : currTime(0), maxTime(maxTime) {};

	/// @brief sends request to the server
	void sendRequest() {
		// if webserver avaialable, send request
		// pop from queue
		// this->webServers.at(i).activeRequests < 1 && this->queue.size() > 0
		for (int i = 0; i < serverVector.size(); i++) {
			// server available
			if (serverVector.at(i).numActiveRequests == 0 && requestsQueue.size() > 0) {
				// get request and process it
				requests req = requestsQueue.front();
				requestsQueue.pop();
				serverVector.at(i).requestFinishTime = currTime + req.reqTime;
				serverVector.at(i).numActiveRequests = 1;
				serverVector.at(i).currentRequest = req;
			}
		}
	}
};