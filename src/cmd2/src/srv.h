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
		void setup();
		void xas(Request &request, StreamResponse &response);
	private:
	protected:
};
void srvstart();
void srvstop();
