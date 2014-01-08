#include "StdAfx.h"
#include "DBObject.h"

int DBObjcet::AddNew(BOOL CheckNolyOne){
	if(CheckNolyOne)
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

int DBObjcet::Update(BOOL CheckNolyOne){
	if(CheckNolyOne)
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
	this->ID = reSet->GetCollect("id");
	_variant_t var = reSet->GetCollect("athlete.name");
	this->Name = (LPWSTR)(_bstr_t)(var.vt <= VT_NULL ? _T("") : var);
	var = reSet->GetCollect("sex");
	this->Sex = (LPWSTR)(_bstr_t)(var.vt <= VT_NULL ? _T("") : var);
	var = reSet->GetCollect("birth");
	this->Birth = (LPWSTR)(_bstr_t)(var.vt <= VT_NULL ? _T("") : var);
	var = reSet->GetCollect("athlete.description");
	this->Description = (LPWSTR)(_bstr_t)(var.vt <= VT_NULL ? _T("") : var);
	this->Org.ID = reSet->GetCollect("org_id");
	var = reSet->GetCollect("org.name");
	this->Org.Name = (LPWSTR)(_bstr_t)(var.vt <= VT_NULL ? _T("") : var);
	var = reSet->GetCollect("name_en");
	this->Org.Name_en = (LPWSTR)(_bstr_t)(var.vt <= VT_NULL ? _T("") : var);
	var = reSet->GetCollect("org.description");
	this->Org.Description = (LPWSTR)(_bstr_t)(var.vt <= VT_NULL ? _T("") : var);
}

Athlete::~Athlete(void)
{
}

CString Athlete::GetAddNewSQL(){
	CString sql;
	sql.Format(_T("insert into athlete (org_id, name, sex, birth, description)\
				  values (%ld, '%s','%s', #%s#, '%s')"),
				  Org.ID >= 0 ? Org.ID : -1, Name, Sex, Birth, Description);
	return sql;
}

CString Athlete::GetDeleteSQL(){
	CString sql;
	sql.Format(_T("delete from athlete where id=%ld"), ID);
	return sql;
}

CString Athlete::GetUpdateSQL(){
	CString sql;
	sql.Format(_T("update athlete set org_id=%ld,name='%s',sex='%s',birth=#%s#,description='%s' where id=%ld"),
		Org.ID, Name, Sex, Birth, Description, ID);
	return sql;
}

CString Athlete::GetCountSQL(){
	CString sql;
	sql.Format(_T("select count(*) as cou from athlete where name='%s' and org_id=%ld"), Name, Org.ID);
	return sql;
}

CString Athlete::GetCountNoCuSQL(){
	CString sql;
	sql.Format(_T("select count(*) as cou from athlete where name='%s' \
				  and org_id=%ld and id<>%d"), Name, Org.ID, ID);
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
					 athlete.org_id,org.name,org.name_en,org.description \
					 from athlete left join org on athlete.org_id=org.id where 1=1 ");
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

//Meeting
Meeting::Meeting(void)
{
}

Meeting::Meeting(_RecordsetPtr reSet){
	this->ID = reSet->GetCollect("id");
	this->Name = (LPWSTR)(_bstr_t)(reSet->GetCollect("name"));
	this->StartDate = (LPWSTR)(_bstr_t)(reSet->GetCollect("startdate"));
	_variant_t var = reSet->GetCollect("address");
	this->Address = (LPWSTR)(_bstr_t)(var.vt <= VT_NULL ? _T("") : var);
}

Meeting::~Meeting(void)
{
}

CString Meeting::GetAddNewSQL(){
	CString sql;
	sql.Format(_T("insert into sports_meeting (name,startdate,address)\
				  values ('%s',#%s#,'%s')"),
				  Name, StartDate, Address);
	return sql;
}

CString Meeting::GetDeleteSQL(){
	CString sql;
	sql.Format(_T("delete from sports_meeting where id=%ld"), ID);
	return sql;
}

CString Meeting::GetUpdateSQL(){
	CString sql;
	sql.Format(_T("update sports_meeting set name='%s',startdate=#%s#,address='%s' where id=%ld"),
		Name, StartDate, Address, ID);
	return sql;
}

CString Meeting::GetCountSQL(){
	CString sql;
	sql.Format(_T("select count(*) as cou from sports_meeting where name='%s'"), Name);
	return sql;
}

CString Meeting::GetCountNoCuSQL(){
	CString sql;
	sql.Format(_T("select count(*) as cou from sports_meeting where name='%s' and id<>%d"), Name, ID);
	return sql;
}

CString Meeting::GetIDSQL(){
	CString sql;
	sql.Format(_T("select id  from sports_meeting where name='%s'"), Name);
	return sql;
}

vector<Meeting> Meeting::GetAll(){
	vector<Meeting> v_meeting;
	_RecordsetPtr reSet = DBManager::QueryForRecordset(_T("select * from sports_meeting"));
	if(reSet->GetRecordCount() == 0) return v_meeting;
	reSet->MoveFirst();
	while(!reSet->adoEOF){
		v_meeting.push_back(Meeting(reSet));
		reSet->MoveNext();
	}
	reSet->Close();
	return v_meeting;
}

//Match
Match::Match(void)
{
}

Match::Match(_RecordsetPtr reSet){
	this->ID = reSet->GetCollect("id");
	this->Name = (LPWSTR)(_bstr_t)(reSet->GetCollect("name"));
	this->StartDate = (LPWSTR)(_bstr_t)(reSet->GetCollect("startdate"));
	_variant_t var = reSet->GetCollect("address");
	this->Address = (LPWSTR)(_bstr_t)(var.vt <= VT_NULL ? _T("") : var);
	var = reSet->GetCollect("sex");
	this->Sex = (LPWSTR)(_bstr_t)(var.vt <= VT_NULL ? _T("") : var);
	this->Minage = reSet->GetCollect("minage");
	this->Maxage = reSet->GetCollect("maxage");
	this->_matchType.ID = reSet->GetCollect("matchtype");
	this->_meeting.ID = reSet->GetCollect("meeting_id");
}

Match::~Match(void)
{
}

CString Match::GetAddNewSQL(){
	CString sql;
	sql.Format(_T("insert into _match (name,startdate,address,sex,minage,maxage,matchtype,meeting_id)\
				  values ('%s',#%s#,'%s','%s',%d,%d,%d,%d)"),
				  Name, StartDate, Address, Sex, Minage, Maxage, _matchType.ID, _meeting.ID);
	return sql;
}

CString Match::GetDeleteSQL(){
	CString sql;
	sql.Format(_T("delete from _match where id=%ld"), ID);
	return sql;
}

CString Match::GetUpdateSQL(){
	CString sql;
	sql.Format(_T("update _match set name='%s',startdate=#%s#,address='%s',sex='%s'\
				  ,minage=%d,maxage=%d,matchtype=%d,meeting_id=%d where id=%ld"),
		Name, StartDate, Address, Sex, Minage, Maxage, _matchType.ID, _meeting.ID, ID);
	return sql;
}

CString Match::GetCountSQL(){
	CString sql;
	sql.Format(_T("select count(*) as cou from _match where name='%s'"), Name);
	return sql;
}

CString Match::GetCountNoCuSQL(){
	CString sql;
	sql.Format(_T("select count(*) as cou from _match where name='%s' and id<>%d"), Name, ID);
	return sql;
}

CString Match::GetIDSQL(){
	CString sql;
	sql.Format(_T("select id  from _match where name='%s'"), Name);
	return sql;
}

vector<Match> Match::Query(){
	vector<Match> v_match;
	CString sql;
	sql.Format(_T("select * from _match where meeting_id=%d"), this->_meeting.ID);
	_RecordsetPtr reSet = DBManager::QueryForRecordset(sql);
	if(reSet->GetRecordCount() == 0) return v_match;
	reSet->MoveFirst();
	while(!reSet->adoEOF){
		v_match.push_back(Match(reSet));
		reSet->MoveNext();
	}
	reSet->Close();
	return v_match;
}


//MatchType
MatchType::MatchType(void)
{
}

MatchType::MatchType(_RecordsetPtr reSet){
	this->ID = reSet->GetCollect("id");
	this->Name = (LPWSTR)(_bstr_t)(reSet->GetCollect("name"));
	this->Type = reSet->GetCollect("type");
}

MatchType::~MatchType(void)
{
}

CString MatchType::GetAddNewSQL(){
	CString sql;
	sql.Format(_T("insert into match_type (name,type) values ('%s',%d)"),
				  Name, Type);
	return sql;
}

CString MatchType::GetDeleteSQL(){
	CString sql;
	sql.Format(_T("delete from match_type where id=%ld"), ID);
	return sql;
}

CString MatchType::GetUpdateSQL(){
	CString sql;
	sql.Format(_T("update match_type set name='%s',type=%d where id=%ld"),
		Name, Type, ID);
	return sql;
}

CString MatchType::GetCountSQL(){
	CString sql;
	sql.Format(_T("select count(*) as cou from match_type where name='%s'"), Name);
	return sql;
}

CString MatchType::GetCountNoCuSQL(){
	CString sql;
	sql.Format(_T("select count(*) as cou from match_type where name='%s' and id<>%d"), Name, ID);
	return sql;
}

CString MatchType::GetIDSQL(){
	CString sql;
	sql.Format(_T("select id  from match_type where name='%s'"), Name);
	return sql;
}

vector<MatchType> MatchType::GetAll(){
	vector<MatchType> v_matchType;
	_RecordsetPtr reSet = DBManager::QueryForRecordset(_T("select * from match_type"));
	if(reSet->GetRecordCount() == 0) return v_matchType;
	reSet->MoveFirst();
	while(!reSet->adoEOF){
		v_matchType.push_back(MatchType(reSet));
		reSet->MoveNext();
	}
	reSet->Close();
	return v_matchType;
}