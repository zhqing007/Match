#pragma once
#include "DBManager.h"
#define NOTONLYONE 2

class DBObjcet
{
protected :
	virtual CString GetUpdateSQL() = 0;
	virtual CString GetAddNewSQL() = 0;
	virtual CString GetDeleteSQL() = 0;
	virtual CString GetCountSQL() = 0;
	virtual CString GetCountNoCuSQL() = 0;
	virtual CString GetIDSQL() = 0;

public:
	int Update(BOOL CheckNolyOne = TRUE);
	int AddNew(BOOL CheckNolyOne = TRUE);
	int Delete();
	int GetCount(BOOL);

	LONG ID;
};


class Organization : public DBObjcet
{
public:
	Organization(void);
	Organization(vector<_variant_t>*);
	Organization(_RecordsetPtr);
	~Organization(void);
	
	static vector<Organization> GetAll();
		
	CString Name;
	CString Name_en;
	CString Description;

protected :
	CString GetUpdateSQL();
	CString GetAddNewSQL();
	CString GetDeleteSQL();
	CString GetCountSQL();
	CString GetCountNoCuSQL();
	CString GetIDSQL();
};


class Athlete : public DBObjcet
{
public:
	Athlete(void);	
	~Athlete(void);
	vector<Athlete> Query();
		
	CString Name;
	CString Sex;
	CString Birth;
	CString Description;
	Organization Org;
	int Age;

private:
	Athlete(_RecordsetPtr);

protected :
	CString GetUpdateSQL();
	CString GetAddNewSQL();
	CString GetDeleteSQL();
	CString GetCountSQL();
	CString GetCountNoCuSQL();
	CString GetIDSQL();
};

class Meeting : public DBObjcet
{
public:
	Meeting(void);	
	~Meeting(void);
	static vector<Meeting> GetAll();
		
	CString Name;
	CString StartDate;
	CString Address;

private:
	Meeting(_RecordsetPtr);

protected :
	CString GetUpdateSQL();
	CString GetAddNewSQL();
	CString GetDeleteSQL();
	CString GetCountSQL();
	CString GetCountNoCuSQL();
	CString GetIDSQL();
};

class MatchType : public DBObjcet
{
public:
	MatchType(void);	
	~MatchType(void);
	static vector<MatchType> GetAll();
		
	CString Name;
	int Type;

private:
	MatchType(_RecordsetPtr);

protected :
	CString GetUpdateSQL();
	CString GetAddNewSQL();
	CString GetDeleteSQL();
	CString GetCountSQL();
	CString GetCountNoCuSQL();
	CString GetIDSQL();
};

class Match : public DBObjcet
{
public:
	Match(void);	
	~Match(void);
	vector<Match> Query();
		
	CString Name;
	CString StartDate;
	CString Address;
	CString Sex;
	int Minage;
	int Maxage;
	MatchType _matchType;
	Meeting _meeting;

private:
	Match(_RecordsetPtr);

protected :
	CString GetUpdateSQL();
	CString GetAddNewSQL();
	CString GetDeleteSQL();
	CString GetCountSQL();
	CString GetCountNoCuSQL();
	CString GetIDSQL();
};

class Troop : public DBObjcet
{
public:
	Troop(void);	
	~Troop(void);
	vector<Troop> Query();

	CString Name;
	Match _match;

private:
	Troop(_RecordsetPtr);

protected :
	CString GetUpdateSQL();
	CString GetAddNewSQL();
	CString GetDeleteSQL();
	CString GetCountSQL();
	CString GetCountNoCuSQL();
	CString GetIDSQL();
};