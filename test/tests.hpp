/*
 * Copyright © 2009-2010, 2018 Shaun Bouckaert
 *
 *  This file is part of Codfig.
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

#ifndef TESTS_HPP
#define TESTS_HPP

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

unsigned int boolTest(string, bool);

/*template <class E, class F, class A, class O>
int exceptionTest(const char *, A, const O &, F);//replace third arg with variable argument list

template <class E, class F, class A, class O>
int exceptionTest(const char * message, A argument, const O & object, F functionP){
	cout << "|-" << message << ": ";
	try {
			(object.*functionP)(argument);
			cout << "failure: no exception thrown!" << endl;
			return 1;
	} catch (const E & e) {
			cout << "success: exception thrown with message:" << endl << "\t\"" << e.what() << "\"" << endl;
			return 0;
	} catch (...) {
			cout << "failure: wrong exception thrown!" << endl;
			return 1;
	}
}*/


template <class E, class F, class A, class O>
unsigned int exceptionTest(const string message, A argument, O & object, F functionP) {
	cout << "|-" << message << ": ";
	try {
			(object.*functionP)(argument);
			cout << "failure: no exception thrown!" << endl;
			return 1;
	} catch (const E & e) {
			cout << "success: exception thrown with message:" << endl << "\t\"" << e.what() << "\"" << endl;
			return 0;
	} catch (...) {
			cout << "failure: wrong exception thrown!" << endl;
			return 1;
	}
}

template <class E, class F, class O>
unsigned int exceptionTestNoArg(const string message, O & object, F functionP) {
    cout << "|-" << message << ": ";
    try {
        (object.*functionP)();
        cout << "failure: no exception thrown!" << endl;
        return 1;
    } catch (const E &e) {
        cout << "success: exception thrown with message:" << endl << "\t\"" << e.what() << "\"" << endl;
        return 0;
    } catch (...) {
        cout << "failure: wrong exception thrown!" << endl;
        return 1;
    }
}

template <class F, class A, class O>
unsigned int noExceptionTest(const string message, A argument, O & object, F functionP) {
    cout << "|-" << message << ": ";
    try {
        (object.*functionP)(argument);
        cout << "success: no exception thrown!" << endl;
        return 0;
    } catch (...) {
        cout << "failure: unexpected exception thrown!" << endl;
        return 1;
    }
}

template <class D, class A>
int isDescendant(const string message, A &ancestor) {
    cout << "|-" << message << ": ";
    A *ancestorP = &ancestor;
    D *descendant = dynamic_cast<D *>(ancestorP);
    if (descendant != NULL) {
        cout << "success: object is a descendant" << endl;
        return 0;
    } else {
        cout << "failure: object is not a descendant" << endl;
        return 1;
    }
}
#endif
