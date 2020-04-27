#include "RLServer.h"
#include "Board.h"
#include "RLMsg.h"
#include <boost/thread.hpp>
#include <iostream>
#include <string>

using namespace boost::asio;

RLServer::RLServer() {

}

RLServer::~RLServer() {
    //dtor
}

void RLServer::run() {
    while (true) {
        socket_ptr sock(new ip::tcp::socket(m_service));
        m_acc.accept(*sock);
        boost::thread(boost::bind(&RLServer::client_session, this, sock));
    }
}

void RLServer::client_session(socket_ptr sock) {
    Board board;
    RLMsg msg_processor;

    while (true) {
        boost::asio::streambuf buf;
        try {
            read_until(*sock, buf, "\n");
        } catch (boost::system::system_error& e) {
            std::cout << e.what() << std::endl;
            break;
        }
        std::istream in(&buf);
        std::string str;
        std::getline(in, str);
        auto request = msg_processor.parseRequest(str);
        auto response = msg_processor.generateResponse(request, board);
        try {
            sock->write_some(buffer(response));
        } catch (boost::system::system_error& e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }
    sock->close();
}
