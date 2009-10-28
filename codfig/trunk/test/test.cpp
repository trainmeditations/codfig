/*
 * Test Driver for Codfig Configuration Library
 */

/*#define _CRTDBG_MAP_ALLOC
 *#include <stdlib.h>
 *#include <crtdbg.h>*/

#include <iostream>
#include <string>
#include "codfig.h"

using std::cout;
using std::endl;

using codfig::Config;
using codfig::ApplicationID;

enum Fixture { fullConfig };
enum Test { basic };

Config getFixture(Fixture);

bool runTest(Test);

int main(int argc, char * argv []) {
    cout << "Begining Tests" << endl;
	//Test Object Creation
	Config testConfig = getFixture(fullConfig);
	cout << "Have Fixture" << endl;
	Config otherConfig(testConfig);
	cout << testConfig("accounts.isp.smtp.ip").getValue<string>()<<":"<<testConfig("accounts.isp.smtp.port").getValue<int>()<<endl;
	otherConfig("accounts.isp.smtp.ip").setValue<string>(string("127.0.0.2"));
	otherConfig("accounts.isp.smtp.port").setValue<int>(23);
	cout << otherConfig("accounts.isp.smtp.ip").getValue<string>()<<":"<<otherConfig("accounts.isp.smtp.port").getValue<int>()<<endl;
	return 0;
}

Config getFixture(Fixture fixture) {
    Config testConfig(ApplicationID("Test App", "0.0.0", "Shaun Bouckaert"));
    cout << "Creating fixture \"";
    switch(fixture){
    case fullConfig:
        cout << "fullConfig\"" << endl;
       	testConfig.addSection("accounts");
        testConfig["accounts"].addSection("isp");
        testConfig["accounts.isp"].addSection("smtp");
        testConfig("accounts.isp.smtp.ip").setValue<string>(string("127.0.0.1"));
        testConfig("accounts.isp.smtp.port").setValue<int>(80);
        testConfig.addProfile("Test Profile");
        break;
    }
    cout << "Returning Fixture" << endl;
    return testConfig;
}
