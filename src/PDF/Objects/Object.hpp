#pragma once

#include <iostream>

#include "PDF/Writer.hpp"

using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Object
		{
		protected:
			/* @see http://stackoverflow.com/questions/9702053 */
			static int counter;

		public:
			static int objectCount()
			{
				return counter;
			}


			virtual void writePDFOutput(Writer &writer) = 0;
		};
	}
}
