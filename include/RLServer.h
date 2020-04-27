#ifndef RLSERVER_H
#define RLSERVER_H
#include <boost/asio.hpp>

class RLServer
{
public:
    using socket_ptr = boost::shared_ptr<boost::asio::ip::tcp::socket>;
    RLServer();
    virtual ~RLServer();
    void run();
private:
    boost::asio::io_service m_service;
    boost::asio::ip::tcp::endpoint m_end_point{boost::asio::ip::tcp::v4(), 12345};
    boost::asio::ip::tcp::acceptor m_acc{m_service, m_end_point};

private:
    void client_session(socket_ptr sock);
};

#endif // RLSERVER_H
