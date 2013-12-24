#include "StdAfx.h"
#include "DBManager.h"


DBManager::DBManager(void)
{
}

DBManager::~DBManager(void)
{
}

_ConnectionPtr DBManager::m_pConnection;

BOOL DBManager::Initialize(){
	 CoInitialize(NULL);
	 try{
		 m_pConnection.CreateInstance("ADODB.Connection");
		 m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=DrawLots.mdb",
			 "","",adModeUnknown);
	 }
	 catch(_com_error e){
		 MessageBox(NULL, e.Description(), _T("连接错误"), MB_OK);
		 return FALSE;
	 }
	 return TRUE;
}

void DBManager::Uninitialize(){
	m_pConnection->Close();
	CoUninitialize();
}

BOOL DBManager::Execute(CString SQL){
	try{
		m_pConnection->Execute((_bstr_t)SQL, NULL, adCmdText);
	}
	catch(_com_error e){
		MessageBox(NULL, e.Description(), _T("连接错误"), MB_OK);
		return FALSE;
	}
	return TRUE;
}

_RecordsetPtr DBManager::QueryForRecordset(CString SQL){
	_RecordsetPtr m_pRecordset;
	try{		
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->CursorLocation = adUseClient;
		m_pRecordset->Open((_bstr_t)SQL, (IDispatch*)m_pConnection,
			adOpenStatic, adLockBatchOptimistic, adCmdUnknown);
	}
	catch(_com_error e){
		MessageBox(NULL, e.Description(), _T("查询错误"), MB_OK);
		return FALSE;
	}
	return m_pRecordset;
}

vector<vector<_variant_t>> DBManager::Query(CString SQL, vector<CString> strName){
	_RecordsetPtr m_pRecordset = QueryForRecordset(SQL);
	vector<vector<_variant_t>> vRecord; //这是C++0x新标准，不是VS2010或者不支持新标准的， 
	//要写成vector< vector<_variant_t> >,因为>>会被认为是右移操作符 
	try{
		m_pRecordset->MoveFirst();
		while(!m_pRecordset->adoEOF)//遍历所有记录 
		{
			vector<_variant_t> vTheValue; //VARIANT数据类型的泛型 			
			for(vector<CString>::iterator na = strName.begin(); 
				na != strName.end(); ++na){
					vTheValue.push_back(m_pRecordset->GetCollect((LPCTSTR)(*na)));//得到字段的值,并添加到容器的最后
			}
			vRecord.push_back(vTheValue);
			m_pRecordset->MoveNext(); //移动到下一条记录
		}
	m_pRecordset->Close(); //关闭记录集
	}
	catch( _com_error e){
		MessageBox(NULL, e.Description(), _T("查询错误"), MB_OK);
	}
	return vRecord; 
}