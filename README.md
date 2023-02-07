# Store Database 

This program is designed to receive, create, and generate reports for a store. The program receives and displays customer details and their debts, processes the data, checks its integrity, and adds it to the customer's details in the DB. 

The program receives data from a CSV file and from the user. There are two variations of the program:

1. Local program
2. Server and client program

## Local Program 
To compile the files locally, run `make local` 
To run the program locally, run `make run_local` 

The program receives a file in the command line to read the data from it (by default `./DB.csv`).
The program prints the results of the requests to `stdout` and runs until it is closed. 

## Network Program
To start the server, run `make server`. 
To run the server, run `make run_server` with arguments `<ip> <port> <file.csv>` 

To start the client, run `make client`. 
To run the client, run `make run_client` with arguments `<ip> <port>` 

The client can send up to five requests to the server, each request is sent separately and a separate thread is opened for it.
The server maintains the order and sends a signal to execute according to the order of the requests.
The server returns the answers to the client's requests and they are printed at the client's place.
After sending the response to the client, the client software closes, and the server software runs until it closes. 

The local program and the network use the same files except for the specific executable files.

## User Manual
- `Set` adds debt lines for new or existing users.
- `Select` displays customers according to the query parameters.
- `Print` prints all existing customers.

**Required customer data:**
- First name
- Second Name
- Id
- Phone
- Date
- Department

Note: Dept can be negative (debt increases) or positive (debt decreases).
You can get customer details according to each parameter and according to the comparison `>`, `<`, `=`, `!=`.
