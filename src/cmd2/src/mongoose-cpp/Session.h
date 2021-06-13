#ifndef _MONGOOSE_SESSION_H
#define _MONGOOSE_SESSION_H

#include <map>
#include "Mutex.h"
#include"duktape/duktape.h"

using namespace std;

/**
 * A session contains the user specific values
 */ 
namespace Mongoose
{
	class Session
	{
		public:
			Session();
			~Session();

			/**
			 * Sets the value of a session variable
			 *
			 * @param string the name of the variable
			 * @param string the value of the variable
			 */
			void setValue(string key, string value);

			/**
			 * get all the values
			 */
			map<string,string> getValues();

			/**
			 * Unset a session varaible
			 *
			 * @param string the variable name
			 */
			void unsetValue(string key);

			/**
			 * Check if the given variable exists
			 *
			 * @param string the name of the variable
			 */
			bool hasValue(string key);

			/**
			 * Try to get the value for the given variable
			 *
			 * @pram string the name of the variable
			 * @param string the fallback value
			 *
			 * @return string the value of the variable if it exists, fallback else
			 */
			string get(string key, string fallback = "");

			/**
			 * Pings the session, this will update the creation date to now
			 * and "keeping it alive"
			 */
			void ping();

			/**
			 * Returns the session age, in seconds
			 *
			 * @return int the number of sessions since the last activity of the session
			 */
			int getAge();
			duk_context* getCtx();
			void setCtx(duk_context*);
			duk_context* ctx;
		protected:
			map<string, string> values;
			int date;
			Mutex mutex;
	};
}

#endif
