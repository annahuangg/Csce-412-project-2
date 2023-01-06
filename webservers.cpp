#include "requests.cpp"
#include <iostream>

/// @brief Webservers accepts requests and processes it
class webservers {
	public:
		/// @brief shows number of active requests a certain server has
		int numActiveRequests;

		/// @brief number of clock cycles taken to finish request
		int requestFinishTime;

		/// @brief tracks request currently being processed
		requests currentRequest;

		/// @brief servers empty upon initialization
		webservers() : numActiveRequests(0) {};

	/// @brief server receives request and outputs metrics
	/// @param name of the server
	/// @param tracks the current number of clock cycles
	/// @param maximum number of clock cycles
	void receiveRequest(int serverNum, int currTime, int maxTime) {
		// if server is busy and request is finish running, print stats
		if (currTime > requestFinishTime && numActiveRequests > 0 && requestFinishTime < maxTime) {
			cout << "Server " << serverNum << " finished at clock cycle " << requestFinishTime <<
			" from IP address " << currentRequest.ipIn << " to IP address "
			<< currentRequest.ipOut << endl;
			numActiveRequests -= 1;
			currentRequest = requests();
		}
	}
};