#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>
#include <cstdlib>
#include <string>
#include "parser.hpp"

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
    //        string host("de.wikipedia.org");
    //        string parameter("/wiki/Katzen");

    string host("www.youtube.com");
    string parameter("/get_video_info?video_id=gPEu2fhNONM");
    //    string parameter("/watch?v=hS5CfP8n_js&feature=youtu.be");

    ssl::context ctx(ssl::context::sslv23);
    //    ctx.set_default_verify_paths();
    ctx.load_verify_file("/usr/local/etc/openssl/certs/cert.pem");
    // Open a socket and connect it to the remote host. // https://de.wikipedia.org/wiki/Hauskatze  //gPEu2fhNONM
    // https://www.youtube.com/watch?v=hS5CfP8n_js&feature=youtu.be  http://www.dailymotion.com/video/x28eaj_whitney-houston-i-will-always-love_music
    boost::asio::io_service io_service;
    ssl_socket sock(io_service, ctx);
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(host, "https");

    boost::asio::connect(sock.lowest_layer(), resolver.resolve(query));
    sock.lowest_layer().set_option(tcp::no_delay(true));

    // Perform SSL handshake and verify the remote host's
    // certificate.
    //    sock.set_verify_mode(ssl::verify_none);
    sock.set_verify_mode(ssl::verify_peer);
    sock.set_verify_callback(ssl::rfc2818_verification(host));
    sock.handshake(ssl_socket::client);



    //    tcp::iostream stream;
    //    stream.expires_from_now(boost::posix_time::seconds(60));
    //    stream.connect(host, "http");

    boost::asio::streambuf request;
    ostream stream(&request);
    stream << "GET " << parameter << " HTTP/1.0\r\n";
    stream << "Host:" << host << "\r\n";
    stream << "Accept: */*\r\n";
    stream << "Connection: close\r\n\r\n";

    //        stream.flush();
    //        cout << stream.rdbuf();

    // only for testing you know!
    //    size_t t;
    //    const char* header=boost::asio::buffer_cast<const char*>(request.data());
    //    cout << header << "this is header-dop" << endl;
    // testing end

    try{
        boost::asio::write(sock, request);
        stream.clear();
        size_t t=sizeof(request);
        request.consume(t);
    }catch(runtime_error e)
    {
        cout << "shit happens man" << endl;
        cout << e.what() << endl;

    }

    boost::asio::streambuf response;
    try{
        //Point to start next time && and done//
        boost::asio::read_until(sock, response, "\r\n");
        //boost::asio::read(sock, response);

    }catch(runtime_error e)
    {
        cout << e.what() << endl;

    }

    // check out
    const char* input = boost::asio::buffer_cast<const char*>(response.data());
    string a = parser::getContent();


    cout << "yes man !!" << endl;
    return 0;

}

