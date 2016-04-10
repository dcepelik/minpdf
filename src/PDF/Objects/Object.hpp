#pragma once

#include <iostream>

using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Object
		{
			virtual void printInternal(ostream& out) const = 0;

			/* @see http://stackoverflow.com/questions/9702053 */
			static int counter;

		public:
			static int objectCount();

			void print(ostream& out) const;
		};
	}
}


ostream& operator<<(ostream &out, const PDF::Objects::Object &obj);
