#include "StdAfx.h"
#include "DBObject.h"

int DBObjcet::AddNew(){
	if(GetCount(FALSE) > 0) return NOTONLYONE;
	DBManager::Execute(this->GetAddNewSQL());
	_RecordsetPtr reSet = DBManager::QueryForRecordset(this->GetIDSQL());
	reSet->MoveFirst();
	ID = reSet->GetCollect("id");
	reSet->Close();
	return TRUE;
}

int DBObjcet::Delete(){
	return DBManager::Execute(this->GetDeleteSQL());
}

int DBObjcet::Update(){
	if(GetCount(TRUE) > 0) return NOTONLYONE;
	return DBManager::Execute(this->GetUpdateSQL());
}

int DBObjcet::GetCount(BOOL isNoCu){
	//FALSE 统计范围中包括当前记录， TRUE 不包括当前记录
	_RecordsetPtr reSet;
	if(isNoCu)
		reSet = DBManager::QueryForRecordset(this->GetCountNoCuSQL());
	else
		reSet = DBManager::QueryForRecordset(this->GetCountSQL());
	reSet->MoveFirst();
	int count = reSet->GetCollect("cou");
	reSet->Close();
	return count;
}

//Organization
Organization::Organization(void)
{
}

Organization::Organization(vector<_variant_t>* v_dat){
	this->ID = (LONG)((*v_dat)[0]);
	this->Name = (LPWSTR)(_bstr_t)((*v_dat)[1]);
	this->Name_en = (LPWSTR)(_bstr_t)((*v_dat)[2]);
	this->Description = (LPWSTR)(_bstr_t)((*v_dat)[3]);
}

Organization::Organization(_RecordsetPtr reSet){
	this->ID = reSet->GetCollect("id");
	this->Name = (LPWSTR)(_bstr_t)(reSet->GetCollect("name"));
	this->Name_en = (LPWSTR)(_bstr_t)(reSet->GetCollect("name_en"));
	this->Description = (LPWSTR)(_bstr_t)(reSet->GetCollect("description"));
}

Organization::~Organization(void)
{
}

CString Organization::GetAddNewSQL(){
	CString sql;
	sql.Format(_T("insert into org (name, name_en, description) values ('%s', '%s', '%s')"),
		Name, Name_en, Description);
	return sql;
}

CString Organization::GetDeleteSQL(){
	CString sql;
	sql.Format(_T("delete from org where id=%ld"), ID);
	return sql;
}

CString Organization::GetUpdateSQL(){
	CString sql;
	sql.Format(_T("update org set name='%s',name_en='%s',description='%s' where id=%ld"),
		Name, Name_en, Description, ID);
	return sql;
}

CString Organization::GetCountSQL(){
	CString sql;
	sql.Format(_T("select count(*) as cou from org where name='%s'"), Name);
	return sql;
}

CString Organization::GetCountNoCuSQL(){
	CString sql;
	sql.Format(_T("select count(*) as cou from org where name='%s' and id<>%d"), Name, ID);
	return sql;
}

CString Organization::GetIDSQL(){
	CString sql;
	sql.Format(_T("select id  from org where name='%s'"), Name);
	return sql;
}

vector<Organization> Organization::GetAll(){
	vector<Organization> v_org;
	_RecordsetPtr reSet = DBManager::QueryForRecordset(_T("select * from org"));
	reSet->MoveFirst();
	while(!reSet->adoEOF){
		v_org.push_back(Organization(reSet));
		reSet->MoveNext();
	}
	reSet->Close();
	return v_org;
}

//Athlete
Athlete::Athlete(void) : Age(-1)
{
}

Athlete::Athlete(_RecordsetPtr reSet){
	this->ID = reSet->GetCollect("athlete.id");
	this->Name = (LPWSTR)(_bstr_t)(reSet->GetCollect("athlete.name"));
	this->Sex = (LPWSTR)(_bstr_t)(reSet->GetCollect("sex"));
	this->Birth = (LPWSTR)(_bstr_t)(reSet->GetCollect("birth"));
	this->Description = (LPWSTR)(_bstr_t)(reSet->GetCollect("athlete.description"));

	this->Org.ID = reSet->GetCollect("org.id");
	this->Org.Name = reSet->GetCollect("org.name");
	this->Org.Name_en = reSet->GetCollect("name_en");
	this->Org.Description = reSet->GetCollect("org.description");
}

Athlete::~Athlete(void)
{
}

CString Athlete::GetAddNewSQL(){
	CString sql;
	sql.Format(_T("insert into athlete (org_id, name, sex, birth, description)\
				  values ('%ld', '%s','%s', '%s', '%s')"),
				  Org.ID, Name, Sex, Birth, Description);
	return sql;
}

CString Athlete::GetDeleteSQL(){
	CString sql;
	sql.Format(_T("delete from athlete where id=%ld"), ID);
	return sql;
}

CString Athlete::GetUpdateSQL(){
	CString sql;
	sql.Format(_T("update athlete set name='%s',name_en='%s',description='%s' where id=%ld"),
		Name, Name, Description, ID);
	return sql;
}

CString Athlete::GetCountSQL(){
	CString sql;
	sql.Format(_T("select count(*) as cou from athlete where name='%s'"), Name);
	return sql;
}

CString Athlete::GetCountNoCuSQL(){
	CString sql;
	sql.Format(_T("select count(*) as cou from athlete where name='%s' and id<>%d"), Name, ID);
	return sql;
}

CString Athlete::GetIDSQL(){
	CString sql;
	sql.Format(_T("select id  from athlete where name='%s'"), Name);
	return sql;
}

vector<Athlete> Athlete::Query(){
	vector<Athlete> v_ath;
	CString sql = _T("select athlete.id,athlete.name,athlete.sex,athlete.birth,athlete.description,\
					 org.id,org.name,org.name_en,org.description from athlete, org where athlete.org_id=org.id ");
	if(this->Name.Trim().GetLength() > 0){
		sql.Append(_T("and athlete.name like '%%"));
		sql.Append(this->Name.Trim());
		sql.Append(_T("%%' "));
	}
	if(this->Sex.GetLength() > 0){
		sql.Append(_T("and athlete.sex='"));
		sql.Append(this->Sex);
		sql.Append(_T("' "));
	}
	if(this->Org.ID >= 0){
		CString orgid;
		orgid.Format(_T("and athlete.org_id=%ld "), this->Org.ID);
		sql.Append(orgid);
	}
	if(this->Age > 0){
		CTime t_curr = CTime::GetCurrentTime();
		CTime str_MaxAge = CTime::GetCurrentTime() - CTimeSpan((Age + 1) * 365 - 1, 0, 0, 0);
		CTime str_MinAge = CTime::GetCurrentTime() - CTimeSpan(Age * 365, 0, 0, 0);
		CString orgid;
		orgid.Format(_T("and athlete.birth>=#%s# and athlete.birth<=#%s# "), 
			str_MaxAge.Format("%Y/%m/%d"), str_MinAge.Format("%Y/%m/%d"));
		sql.Append(orgid);
	}

	_RecordsetPtr reSet = DBManager::QueryForRecordset(sql);
	int a = reSet->RecordCount;
	if(reSet->RecordCount == 0) return v_ath;
	reSet->MoveFirst();
	while(!reSet->adoEOF){
		v_ath.push_back(Athlete(reSet));
		reSet->MoveNext();
	}
	reSet->Close();
	return v_ath;
}