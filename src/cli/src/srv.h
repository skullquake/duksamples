#include<mongoosecpp/Server.h>
#include<mongoosecpp/WebController.h>
using namespace std;
using namespace Mongoose;
class MyController:public WebController{
	public: 
		MyController(){
		}
		~MyController(){
		}
		void setup();
		void xas(Request &request, StreamResponse &response);
	private:
	protected:
};
void srvstart();
void srvstop();
