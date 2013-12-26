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
	int Update();
	int AddNew();
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