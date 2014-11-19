#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;
using boost::asio::ip::tcp;

/// sbsSocket Class
///
/// This class establish a network connection with the given
/// IP address and port number. It send message and receive message
/// accross the network.
class sbsSocket
{
    public:
		/// A public string variable.
		/// This variable holds the IP address of the server.
		string m_deviceIP;

		/// A public int variable.
		/// This variable holds the port number of service.
		int m_devicePort;

	public:
		/// A constructor.
		///
		/// This constructor a network socket.
		sbsSocket();

		/// A destructor.
		///
		/// This destructor free the resources that the object may have.
		~sbsSocket();

	private:
		/// A private object.
		/// This object is for I/O services.
		boost::asio::io_service ioservice;

		/// A shared pointer to an object.
		/// This shared pointer points to a socket object
		boost::shared_ptr<tcp::socket> socket;

    public:
        /// This member establish a connection to the server
        ///
        ///@return true if connected
        bool connect();

        /// This member close the connection with the server
        void disconnect();

        /// This member receive a message from the server
		///@return message receive from the server
        string getMessage();

        /// This member send a message to the server
		///
		///@param str: The message to be send over to the server
		///@return true if successfully sent
        bool sendMessage(string msg);

	public:
		/// This member establish a connection to the server and send a message
		/// over. It will return the message receive from the server.
		///
		///@param str: The message to be send over to the server
		///@return message receive from the server
		string getOneMessage(boost::shared_ptr<string> str);

		void sendOneMessage(boost::shared_ptr<string> str);

};
