#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>
#include <cstdlib>

using namespace std;
using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;


int main(int argc, char *argv[])
{

    //    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();

    //    return a.exec();
    // Create a context that uses the default paths for
    // finding CA certificates.
    ssl::context ctx(ssl::context::sslv23);
    //    ctx.set_default_verify_paths();
    ctx.load_verify_file("/usr/local/etc/openssl/certs/cert.pem");
    // Open a socket and connect it to the remote host. // https://de.wikipedia.org/wiki/Hauskatze
    boost::asio::io_service io_service;
    ssl_socket sock(io_service, ctx);
    tcp::resolver resolver(io_service);
    tcp::resolver::query query("www.google.de","https");
    boost::asio::connect(sock.lowest_layer(), resolver.resolve(query));
    sock.lowest_layer().set_option(tcp::no_delay(true));

    // Perform SSL handshake and verify the remote host's
    // certificate.
    //    sock.set_verify_mode(ssl::verify_none);
    sock.set_verify_mode(ssl::verify_peer);
    sock.set_verify_callback(ssl::rfc2818_verification("www.google.de"));
    sock.handshake(ssl_socket::client);
    tcp::resolver::iterator iterator = resolver.resolve(query);

    string parameter("/");

    tcp::iostream stream;
    stream.expires_from_now(boost::posix_time::seconds(60));
    stream.connect("www.google.de", "http");
    stream << "GET " << parameter << " HTTP/1.0\r\n";
    stream << "Host: www.google.de\r\n";
    stream << "Accept: */*\r\n";
    stream << "Connection: close\r\n\r\n";
    stream.flush();
    std::cout << stream.rdbuf();

    cout << "yes man !!" << endl;
    return 0;

}
