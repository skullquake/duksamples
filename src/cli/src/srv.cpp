#include"mongoose-cpp/Server.h"
#include"mongoose-cpp/WebController.h"
using namespace std;
using namespace Mongoose;
class MyController:public WebController{
	public: 
		MyController(){
		}
		~MyController(){
		}
		void setup(){
			addRoute("GET","/xas",MyController,xas);
		}
		void xas(Request &request, StreamResponse &response){
			response.setHeader("Content-type","text/plain");
			response<<"hi";
		}
	private:
	protected:
};
MyController myController;
Server server(8080);
void srvstart(){
	std::cout<<"Starting server"<<std::endl;
	server.registerController(&myController);
	server.setOption("enable_directory_listing","yes");
	server.setOption("document_root","./pub");
	server.start(); 
}

void srvstop(){
	std::cout<<"Stopping server"<<std::endl;
	server.stop(); 
}
