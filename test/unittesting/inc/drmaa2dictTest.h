/*
 * Copyright (C) 1994-2017 Altair Engineering, Inc.
 * For more information, contact Altair at www.altair.com.
 *
 * This file is part of the PBS Professional ("PBS Pro") software.
 *
 * Open Source License Information:
 *
 * PBS Pro is free software. You can redistribute it and/or modify it under the
 * terms of the GNU Affero General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * PBS Pro is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Commercial License Information:
 *
 * The PBS Pro software is licensed under the terms of the GNU Affero General
 * Public License agreement ("AGPL"), except where a separate commercial license
 * agreement for PBS Pro version 14 or later has been executed in writing with Altair.
 *
 * Altair’s dual-license business model allows companies, individuals, and
 * organizations to create proprietary derivative works of PBS Pro and distribute
 * them - whether embedded or bundled with other software - under a commercial
 * license agreement.
 *
 * Use of Altair’s trademarks, including but not limited to "PBS™",
 * "PBS Professional®", and "PBS Pro™" and Altair’s logos is subject to Altair's
 * trademark licensing policies.
 *
 */

#ifndef TEST_UNITTESTING_SRC_DRMAA2DICTTEST_H_
#define TEST_UNITTESTING_SRC_DRMAA2DICTTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>

#include "../../../api/c-binding/drmaa2.h"

namespace drmaa2 {

class drmaa2_dict_Test: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE (drmaa2_dict_Test);
	CPPUNIT_TEST (testDictCreate);
	CPPUNIT_TEST (testDictFree);
	CPPUNIT_TEST (testDictDel);
	CPPUNIT_TEST (testDictSetGet);
	CPPUNIT_TEST (testFreeNullDict);
	CPPUNIT_TEST (testDictGetList);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
public:
	void testDictCreate();
	void testDictFree();
	void testDictDel();
	void testDictSetGet();
	void testFreeNullDict();
	void testDictGetList();
public:
	drmaa2_dict_Test();
	virtual ~drmaa2_dict_Test();
private:
	drmaa2_dict d;
};

} /* namespace drmaa2 */

#endif /* TEST_UNITTESTING_SRC_DRMAA2DICTTEST_H_ */
