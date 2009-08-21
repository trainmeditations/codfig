/*
 * Test Driver for Codfig Configuration Library
 */

#include <iostream>
#include "codfig.h"

using std::cout;
using std::endl;

using codfig::Config;
using codfig::ApplicationID;

int main(int argc, char * argv []) {
	//Test Object Creation
	Config testConfig(ApplicationID("Test App", "0.0.0", "Shaun Bouckaert"));

	//Test copying and assignment
	//Unit Testing
	//Test Object Distruction
	return 0;
}
