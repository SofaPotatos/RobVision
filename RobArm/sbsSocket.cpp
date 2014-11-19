#include "sbsSocket.h"

/*******************************************************************************
* Constructor & Destructor
********************************************************************************/

sbsSocket::sbsSocket()
{
	try
	{
		socket.reset(new tcp::socket(ioservice));
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

sbsSocket::~sbsSocket()
{
}

/*******************************************************************************
* Private Method
********************************************************************************/

bool sbsSocket::connect()
{
	boost::asio::ip::tcp::endpoint remoteEndpoint(boost::asio::ip::address::from_string(m_deviceIP), m_devicePort);
	try
	{
		socket->connect(remoteEndpoint);
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return socket->is_open();
}

void sbsSocket::disconnect()
{
	socket->close();
}

string sbsSocket::getMessage()
{
	char msg[1024];
	boost::system::error_code error;
	size_t len = socket->read_some(boost::asio::buffer(msg), error);

	if (error == boost::asio::error::eof)
	{
		std::cout << "The connection is closed" << std::endl;
	}
    else if (error)
        throw boost::system::system_error(error); // Some other error.

	return msg;
}

bool sbsSocket::sendMessage(string msg)
{
	boost::system::error_code error;
	size_t len = socket->write_some(boost::asio::buffer(msg), error);

	if (error)
	{
        throw boost::system::system_error(error);
		return false;
	}
	else
		return true;

}

/*******************************************************************************
* Public Method
********************************************************************************/

string sbsSocket::getOneMessage(boost::shared_ptr<string> str)
{
	string temp;
	if(connect())
		if(sendMessage(*str))
		{
		    temp = getMessage();
		    disconnect();
		    return temp;
		}
    cout << "Error" << endl;
    return NULL;
}

void sbsSocket::sendOneMessage(boost::shared_ptr<string> str)
{
	if(connect())
	{
		sendMessage(*str);
		disconnect();
	}
}

