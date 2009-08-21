/*
 * Test Driver for Codfig Configuration Library
 */

#include <iostream>
#include <string>
#include "codfig.h"

using std::cout;
using std::endl;

using codfig::Config;
using codfig::ApplicationID;

Config * fixture() {
	Config * testConfig = new Config(ApplicationID("Test App", "0.0.0", "Shaun Bouckaert"));

	(*testConfig).addSection("accounts");
	(*testConfig)["accounts"].addSection("isp");
	(*testConfig)["accounts.isp"].addSection("smtp");
	(*testConfig)("accounts.isp.smtp.ip").setValue<string>("127.0.0.1");
	(*testConfig)("accounts.isp.smtp.port").setValue(80);

	(*testConfig).selectProfile((*testConfig).addProfile("alternate isp"));
	(*testConfig).addSection("accounts");
	(*testConfig)["accounts"].addSection("isp");
	(*testConfig)["accounts.isp"].addSection("smtp");
	(*testConfig)("accounts.isp.smtp.ip").setValue<string>("127.0.0.2");
	(*testConfig)("accounts.isp.smtp.port").setValue(81);

	return testConfig;
}

int main(int argc, char * argv []) {
	Config * testConfig = fixture();
        cout << (*testConfig)("accounts.isp.smtp.ip").getValue<string>() << endl;
        delete testConfig;
	return 0;
}
