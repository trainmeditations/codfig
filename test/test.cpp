/*
 * Copyright © Shaun Bouckaert 2012
 *
 * This file is part of Codfig.
 *
 *  Codfig is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Codfig is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Codfig.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * Test Suite for Codfig Configuration Library
 */

//MS Visual C++ Memory Leak Detection Code
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
//END MS Visual C++ Memory Leak Detection Code

#include <iostream>
#include <string>
#include <cstdlib>
#include "codfig.h"
#include "tests.h"
#include "buildopts.h"

using std::cout;
using std::endl;
using std::string;

using codfig::Config;

#if Test_INI
#include "codfigio_ini.h"
using codfig::ConfigIOini;
#endif

enum Fixture { fullConfig };

enum Test { values, structure, exceptions, iniIn, iniOut };

Config getFixture(Fixture);

bool runTests(Test, bool = false);


int main(int argc, char * argv []) {
    //MS Visual C++ Memory Leak Detection - Uncomment the lines to use
    #ifdef _MSC_VER
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif
    //END MS Visual C++ Memory Leak Detection Code

    //int * blah = new int(0x12345678);
    string colourArg;
    bool colours = false;
    if (argc > 1)
        colourArg = string(argv[1]);
    if (colourArg == "colours")
        colours = true;
    cout << "Begining Tests" << endl;
        runTests(values, colours);
        runTests(structure, colours);
        runTests(exceptions, colours);
#if Test_INI
        runTests(iniIn, colours);
        runTests(iniOut, colours);
#endif

        cout << endl << "Completed Test Suite." << endl << endl;

        return 0;
}

bool runTests(Test test, bool colours){
    string testName;
    cout << endl << "Running test \"";
	ConfigEntry * testEntry = NULL;
    unsigned int failures = 0;
    string failText, successText, resetText;
    if (colours) {
        failText = "\033[22;31m";
        successText = "\033[22;32m";
        resetText = "\033[m";
    }
    switch(test){
        case values:
        {
            cout << (testName = "values") << "\"." << endl;
            //Test Object Creation
            Config testConfig = getFixture(fullConfig);

			testEntry = &(testConfig["accounts.isp.testValue"]);

            failures += boolTest("Earlier branch value",
                                 testConfig["accounts.isp.testValue"].value<int>() == 9999);

            //Compare string value
            failures += boolTest("Compare string value",
                                 testConfig["accounts.isp.smtp.ip"].value<string>() == "127.0.0.1");

            //Compare int value
            failures += boolTest("Compare int value",
                                 testConfig["accounts.isp.smtp.port"].value<int>() == 25);

            //Compare float value
            failures += boolTest("Compare float value",
                                 testConfig["accounts.isp.smtp.data"].value<float>() == 17.0F);

            //Compare bool value
            failures += boolTest("Compare bool value",
                                 testConfig["accounts.isp.smtp.default"].value<bool>() == false);
        }break;

        case structure:
        {
        cout << (testName = "structure") << "\"." << endl;
        Config testConfig = getFixture(fullConfig);

        failures += boolTest("Check number of root sections",
                             testConfig.getEntryNames().size() == 1);
        testEntry = &testConfig["accounts"];
        if (testEntry)
            failures += boolTest("Check number of sub-entries",
                                 testEntry->getEntryNames().size() == 2);
        testEntry = &(testConfig["accounts.isp.smtp"]);
        if (testEntry)
            failures += boolTest("Check number of sub-entries",
                                 testEntry->getEntryNames().size() == 4);
        }break;



        case exceptions:
        {
            cout << (testName = "exception") << "\"." << endl;
            Config testConfig = getFixture(fullConfig);
            const Config & cTestConfig(testConfig);

            failures += noExceptionTest
                        <codfig::ConfigEntry &(codfig::Config::*)(const std::string &)>
                        ("non-const Section/Value create check", "new.path", testConfig, &codfig::Config::operator[]);
            failures += exceptionTest
                        <codfig::bad_path, const codfig::ConfigEntry &(codfig::Config::*)(const std::string &) const>
                        ("Const section bad_path check", "bad.path", cTestConfig, &codfig::Config::operator[]);

            ConfigEntry & testEntry(testConfig["accounts.isp.smtp.data"]); //data value is type float
            failures += exceptionTestNoArg
                        <codfig::wrong_type, int &(codfig::ConfigEntry::*)()>
                        ("Check for exception on wrong type", testEntry, &codfig::ConfigEntry::value<int>);

            /*failures += exceptionTestNoArg
                        <codfig::not_a_section, ConfigSection &(codfig::ConfigEntry::*)()>
                        ("Check for exception on conversion to section of value", testEntry, &codfig::ConfigEntry::asSection);*/

        }break;

#if Test_INI

        case iniIn:
        {
            cout << (testName = "ini Input") << "\"." << endl;
            Config testIOConfig("Test App", "0.0.0", "Shaun Bouckaert");
            
            failures += boolTest("Check number of root sections",
                                 testIOConfig.getEntryNames().size() == 2);
            if (failures) break;
            /*failures += boolTest(("Check first root section name " + testIOConfig.getSectionNames()[0]).c_str(),
                                 testIOConfig.getSectionNames()[0] == "owner" || testIOConfig.getSectionNames()[0] == "database");
            failures += boolTest(("Check second root section name " + testIOConfig.getSectionNames()[1]).c_str(),
                                 testIOConfig.getSectionNames()[1] == "database" || testIOConfig.getSectionNames()[1] == "owner");
            failures += boolTest("Checknumber of first section subsections",
                                 testIOConfig["owner"].getSectionNames().size() == 1);
            failures += boolTest("Check first section's' first subsection name",
                                 testIOConfig["owner"].getSectionNames()[0] == "info");
            failures += boolTest("Check name value",
                                 testIOConfig("owner.info.name").value<string>() == "Mirititi");
            failures += boolTest("Check organiziation value",
                                 testIOConfig("owner.info.organization").value<string>() == "big lamer   ");
            failures += boolTest("Check server value",
                                 testIOConfig("database.server").value<string>() == "192.0.2.62     ");
            failures += boolTest("Check port value",
                                 testIOConfig("database.port").value<string>() == "143");
            failures += boolTest("Check file value",
                                 testIOConfig("database.file").value<string>() == "\"big lamer payroll.dat\"");
            failures += boolTest("Check file2 value",
                                 testIOConfig("database.file2").value<string>() == "");*/
        }break;

        case iniOut:
        {
            cout << (testName = "ini Output") << "\"." << endl;
            Config testConfig = getFixture(fullConfig);
            /*ConfigIOini("testout.ini").saveConfig(testConfig);*/
        }break;

#endif

        default:
        {
            cout << "!!!TEST NOT IMPLEMENTED!!!\"" << endl;
            return false;
        }
    }

    if (failures)
        cout << failText << failures << ((failures == 1)?" failure":" failures") << " during test \"" << testName << "\"." << resetText << endl;
    else
        cout << successText << "Completed test \"" << testName << "\" successfully." << resetText << endl;
    return !failures;
}

Config getFixture(Fixture fixture) {
    Config testConfig("Test App", "0.0.0", "Shaun Bouckaert");
    switch(fixture){
    case fullConfig:
        testConfig["accounts.isp"].value<string>() = "Test ISP";
        testConfig["accounts.isp.testValue"].value<int>() = 9999;
        testConfig["accounts.isp.smtp.ip"].value<string>() = "127.0.0.1";
        testConfig["accounts.isp.smtp.port"].value<int>() = 25;
        testConfig["accounts.isp.smtp.data"].value<float>() = 17.0F;
        testConfig["accounts.isp.smtp.default"].value<bool>() = false;
        testConfig["accounts.isp2.number"].value<string>() = "073344556677";
        testConfig.addProfile("Test Profile");
        break;
    }
    return testConfig;
}
