
#include <iostream>
#include <memory>
#include <cstdlib>
#include "restbed"
#include "spdlog/spdlog.h"
#include "json/json.h"

using namespace std;
using namespace restbed;
using namespace Json;
namespace spd = spdlog;

void get_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    int content_length = request->get_header( "Content-Length", 0 );
    std::string host = request->get_header("Host", "");
    spdlog::get("console")->info("Request from {0}", host);

    session->fetch( content_length, [ ]( const shared_ptr< Session > session, const Bytes & body )
    {
        Json::Value root;
        root["response"] = "Hello World!!!";
        Json::StreamWriterBuilder wbuilder;
        std::string document = Json::writeString(wbuilder, root);
        const multimap<string, string> headers{
            {"Content-Type", "application/json"},
            {"Content-Length", std::to_string(document.length())}};
        session->close(OK, document, headers);

    } );
}

int main( const int, const char** )
{
    // Console logger with color
    auto console = spd::stdout_color_mt("console");
    console->info("Creating rest endpoint /resource...");
    auto resource = make_shared<Resource>( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler );

    auto settings = make_shared< Settings >( );
    console->info("Listening on port 8080.");
    settings->set_port( 8080 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}
