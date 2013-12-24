#pragma once
#include <vector>
#import "C:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF", "adoEOF") 
using namespace std;

class DBManager
{
public:
	DBManager(void);
	~DBManager(void);
	static BOOL Initialize();
	static void Uninitialize();
	static BOOL Execute(CString);
	static vector<vector<_variant_t>> Query(CString, vector<CString>);
	static _RecordsetPtr QueryForRecordset(CString);

private:
	static _ConnectionPtr m_pConnection;
};

