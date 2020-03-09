#include <time.h>
#include <iostream>
#include <string>
#include "Session.h"

using namespace std;

namespace Mongoose
{
	Session::Session()
	:ctx(NULL)
	{
		//std::cout<<"Session()"<<std::endl;
		ping();
	}
	Session::~Session()
	{
		//std::cout<<"~Session()"<<std::endl;
	}

	void Session::ping()
	{
		mutex.lock();
		date = time(NULL);
		mutex.unlock();
	}

	void Session::setValue(string key, string value)
	{
		mutex.lock();
		values[key] = value;
		mutex.unlock();
	}

	void Session::unsetValue(string key)
	{
		mutex.lock();
		values.erase(key);
		mutex.unlock();
	}

	bool Session::hasValue(string key)
	{
		return values.find(key) != values.end();
	}

	string Session::get(string key, string fallback)
	{
		mutex.lock();
		if (hasValue(key)) {
			string value = values[key];
			mutex.unlock();

			return value;
		} else {
			mutex.unlock();
			return fallback;
		}
	}
	map<string,string> Session::getValues(){
		return this->values;
	}


	int Session::getAge()
	{
		return time(NULL)-date;
	}
	duk_context* Session::getCtx()
	{
		return this->ctx;
	}
	void Session::setCtx(duk_context* c)
	{
		this->ctx=c;
	}
}
