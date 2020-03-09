#include<iostream>
#include"duk.h"
#include"srv.h"
int main(int argc,char** argv){
	std::cout<<"main()"<<std::endl;
	//_main(argc,argv);
	Duk d(argc,argv);
	return 0;
}
