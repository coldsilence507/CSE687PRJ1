// Query.cpp : Defines the entry point for the console application.
//
#include "Query.h"
#include "../Payload/Payload.h"
using namespace NoSqlDb;
using namespace Payload;

//----< test stub >--------------------------------------------------

#ifdef TEST_QUERY

int main()
{

	NoSqlDb::DbCore<std::string> db;
	db.ReadFromXml("../src/test.xml");
	Query::Query<std::string> q1(db);
	q1.show();
	q1.selectByName("Jim");
	q1.show();

	Query::Query<std::string> q2(db);
	q2.selectByDescrip("TA");
	q2.unionQuery(q1);
	q2.show();


	DateTime t1(DateTime::makeTime(2018, 1, 20));
	std::cout << std::endl << (std::string)t1 << std::endl;
	Query::Query<std::string> q3(db);
	q3.show();

	/*
	DbCore<std::string> db;
	db.ReadFromXml("../src/test.xml");
	//db.delRecord("Fawcett");
	showDb(db);
	DbElement<std::string> demoElem;

	demoElem.name("Jim");
	demoElem.descrip("Instructor for CSE687");
	DateTime t2(DateTime::makeTime(2018, 1, 19));
	demoElem.dateTime(t2);
	demoElem.payLoad("The good news is ...");

	db.addRecord("Fawcett", demoElem);
	showDb(db);

	Query::Query<std::string> q1(db);
	q1.selectByName("Jim");
	q1.show();

	Query::Query<std::string> q2(db);
	q2.selectByDescrip("TA");
	q2.unionQuery(q1);
	q2.show();

	DateTime t1(DateTime::makeTime(2018, 1, 18));
	DateTime t3(DateTime::makeTime(2018, 1, 20));
	//std::cout << std::endl << (std::string)t1<< std::endl;
	Query::Query<std::string> q3(db);

	q3.selectByTime(t1, t3);

	q3.show();

	Query::Condition<std::string> c1;
	c1.name("Ammar").descrip("TA").begintime(t1);

	q3.select(c1);
	q3.show();
	db.delChild("Salman", "Sun");
	q3.show();
	showDb(db);
	putLine();
	*/
	DbCore<Payload::File> db1;
	DbElement<Payload::File> demoElem1;

	DateTime t2(DateTime::makeTime(2018, 1, 19));
	demoElem1.name("Jim");
	demoElem1.descrip("Instructor for CSE687");
	demoElem1.dateTime(t2);
	Payload::File p1;
	p1.path("12345");
	p1.addCategory("test");
	p1.addCategory("test1");
	demoElem1.payLoad(p1);
	db1.addRecord("Fawcett", demoElem1);
	db1.showDb();
	Query::Query<Payload::File> q4(db1);
	q4.selectByPayload(p1);

	db1.WriteToXml("../src/test1.xml");
	db1.ReadFromXml("../src/test1.xml");
	db1.showDb();
	

    return 0;
}

#endif