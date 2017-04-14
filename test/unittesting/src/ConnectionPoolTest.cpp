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

#include <cppunit/extensions/AutoRegisterSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <ConnectionPool.h>
#include <ConnectionPoolTest.h>
#include <PBSProSystem.h>
#include "drmaa2.hpp"
#include <string>


using namespace drmaa2;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(ConnectionPoolTest);

void CheckForOpenConnection(const Connection& obj) {
	Connection *tmp = obj.clone();
	PBSConnection *_pbsCnHolder = static_cast<PBSConnection*>(tmp);
	CPPUNIT_ASSERT(_pbsCnHolder->getFd() > 0);
	delete tmp;
}

void TestMaxConnections() {
	Connection *pbtest = new PBSConnection(pbs_default(), 0, 0);
	ConnectionPool *tmp = ConnectionPool::getInstance();
	for(int i = 0; i < 20; i++) {
		const Connection &pbstmpFds = tmp->addConnection(*pbtest);
		if(i < 19) {
			CheckForOpenConnection(pbstmpFds);
			ConnectionPool::getInstance()->returnConnection(pbstmpFds);
		}
	}
	delete pbtest;
}

void TestGetConnections() {
	ConnectionPool *tmp = ConnectionPool::getInstance();
	for(int i = 0; i < 20; i++) {
		const Connection &pbstmpFds = tmp->getConnection();
		CheckForOpenConnection(pbstmpFds);
		if(i == 19) {
			tmp->reconnectConnection(pbstmpFds);
		}
	}
}

void ConnectionPoolTest::TestConnectionPool() {
	Connection *pbtest = new PBSConnection(pbs_default(), 0, 0);
	ConnectionPool *tmp = ConnectionPool::getInstance();
	const Connection &pbstmp = tmp->addConnection(*pbtest);
	delete pbtest;
	CheckForOpenConnection(pbstmp);
	ConnectionPool::getInstance()->returnConnection(pbstmp);
	TestMaxConnections();
	TestGetConnections();
	Connection *pbtstRel = new PBSConnection(pbs_default(), 0, 0);
	ConnectionPool::getInstance()->reconnectConnection(*pbtstRel);
	delete pbtstRel;
	ConnectionPool::getInstance()->clearConnectionPool();
        Connection *pbtestfin = new PBSConnection(pbs_default(), 0, 0);
        ConnectionPool *tmpfin = ConnectionPool::getInstance();
        const Connection &pbstmpFds = tmpfin->addConnection(*pbtestfin);
        DRMSystem *drms = Singleton<DRMSystem, PBSProSystem>::getInstance();
        drms->connect(*pbtestfin);
        Connection *tmpdelete = pbtestfin->clone();
        delete tmpdelete;
        QueueInfoList tst = drms->getAllQueues(*pbtestfin);
        cout<<tst.front().name;
        JobTemplate jt_;
        jt_.submitAsHold = false;
        jt_.minPhysMemory = 10;
        jt_.jobName.assign("TESTJOB");
        jt_.remoteCommand.assign("/bin/sleep");
        jt_.args.push_back("1000");
        jt_.queueName.assign("workq");
        jt_.minSlots = 1;
        jt_.priority = 0;
        jt_.accountingId.assign("DRMAA2JOB");
        jt_.email.push_back("user@drmaa2.com");
        jt_.emailOnStarted = 0;
        jt_.emailOnTerminated = 0;
        jt_.startTime = time(0);
        string s1, s2;
        s1.assign("TestVar");
        s2.assign("TestVal");
        jt_.jobEnvironment.insert(pair<string, string>(s1, s2));
        jt_.joinFiles = 1;
        //jt_.machineOS = LINUX;
        jt_.rerunnable = 0;
        s1.assign(DRMAA2_WALLCLOCK_TIME);
        s2.assign("01:00:00");
        jt_.resourceLimits.insert(pair<string, string>(s1, s2));
        Job* tmpjid = drms->runJob(*pbtestfin, jt_);
        sleep(2);
	JobInfo _jinfo = tmpjid->getJobInfo();
        tmpjid->suspend();
	string substate;
	tmpjid->getState(substate);
        sleep(10);
	tmpjid->resume();
        sleep(10);
	tmpjid->hold();
        sleep(10);
        tmpjid->release();
	sleep(10);
	tmpjid->terminate();
}
