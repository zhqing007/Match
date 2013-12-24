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
		 MessageBox(NULL, e.Description(), _T("���Ӵ���"), MB_OK);
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
		MessageBox(NULL, e.Description(), _T("���Ӵ���"), MB_OK);
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
		MessageBox(NULL, e.Description(), _T("��ѯ����"), MB_OK);
		return FALSE;
	}
	return m_pRecordset;
}

vector<vector<_variant_t>> DBManager::Query(CString SQL, vector<CString> strName){
	_RecordsetPtr m_pRecordset = QueryForRecordset(SQL);
	vector<vector<_variant_t>> vRecord; //����C++0x�±�׼������VS2010���߲�֧���±�׼�ģ� 
	//Ҫд��vector< vector<_variant_t> >,��Ϊ>>�ᱻ��Ϊ�����Ʋ����� 
	try{
		m_pRecordset->MoveFirst();
		while(!m_pRecordset->adoEOF)//�������м�¼ 
		{
			vector<_variant_t> vTheValue; //VARIANT�������͵ķ��� 			
			for(vector<CString>::iterator na = strName.begin(); 
				na != strName.end(); ++na){
					vTheValue.push_back(m_pRecordset->GetCollect((LPCTSTR)(*na)));//�õ��ֶε�ֵ,����ӵ����������
			}
			vRecord.push_back(vTheValue);
			m_pRecordset->MoveNext(); //�ƶ�����һ����¼
		}
	m_pRecordset->Close(); //�رռ�¼��
	}
	catch( _com_error e){
		MessageBox(NULL, e.Description(), _T("��ѯ����"), MB_OK);
	}
	return vRecord; 
}