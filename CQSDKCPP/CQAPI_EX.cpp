#include "CQAPI_EX.h"

#include "CQAPI.h"
#include "Unpack.h"
#include "CQEVE_GroupMsg.h"
#include "CQEVE_PrivateMsg.h"
#include "CQTools.h"

using namespace CQ;
using namespace std;
int lasterr;

CQ::StrangerInfo::StrangerInfo(const char* msg)
{
	if (msg[0] == '\0')
	{
		QQID = 0; sex = 255; age = -1; nick = "";
	}
	else
	{
		Unpack p(base64_decode(msg));
		QQID = p.getLong();
		nick = p.getstring();
		sex = p.getInt();
		age = p.getInt();
	}
}

string CQ::StrangerInfo::tostring() const
{
	return string("{")
		+ "QQ:" + to_string(QQID)
		+ " ,�ǳ�:" + nick
		+ " ,�Ա�:" + (sex == 255 ? "δ֪" : sex == 1 ? "��" : "Ů")
		+ " ,����:" + to_string(age)
		+ "}"
		;
}

void CQ::GroupMemberInfo::Void()
{
	Group = 0;
	QQID = 0;
	Nick = "";
	GroupNick = "";
	Gender = 0;
	Age = 0;
	Region = "";
	AddGroupTime = 0;
	LastMsgTime = 0;
	LevelName = "";
	permissions = 0;
	NaughtyRecord = 0;
	Title = "";
	ExpireTime = 0;
	canEditGroupNick = 0;
}

void CQ::GroupMemberInfo::setdata(Unpack& u)
{
	Group = u.getLong();
	QQID = u.getLong();
	Nick = u.getstring();
	GroupNick = u.getstring();
	Gender = u.getInt();
	Age = u.getInt();
	Region = u.getstring();
	AddGroupTime = u.getInt();
	LastMsgTime = u.getInt();
	LevelName = u.getstring();
	permissions = u.getInt();
	NaughtyRecord = u.getInt() == 1;
	Title = u.getstring();
	ExpireTime = u.getInt();
	canEditGroupNick = u.getInt() == 1;
}

CQ::GroupMemberInfo::GroupMemberInfo(Unpack & msg) { setdata(msg); }

CQ::GroupMemberInfo::GroupMemberInfo(const char* msg)
{
	if (msg[0] == '0')
	{
		Void();
	}
	else
	{
		Unpack u(base64_decode(msg));
		setdata(u);
		//setdata(Unpack(base64_decode(msg)));
	}
}

CQ::GroupMemberInfo::GroupMemberInfo(vector<unsigned char> data)
{
	if (data.size() <= 0)
	{
		Void();
	}
	else
	{
		Unpack u(data);
		setdata(u);
		//setdata(Unpack(base64_decode(msg)));
	}
}

string CQ::GroupMemberInfo::tostring() const
{
	string s = "{";
	s += "Ⱥ��:"; s += to_string(Group);
	s += " ,QQ��:"; s += to_string(QQID);
	s += " ,�ǳ�:"; s += Nick;
	s += " ,��Ƭ:"; s += GroupNick;
	s += " ,�Ա�:"; s += (Gender == 255 ? "δ֪" : Gender == 1 ? "��" : "Ů");
	s += " ,����:"; s += to_string(Age);
	s += " ,����:"; s += Region;
	s += " ,��Ⱥʱ��:"; s += to_string(AddGroupTime);
	s += " ,�����:"; s += to_string(LastMsgTime);
	s += " ,�ȼ�_����:"; s += LevelName;
	s += " ,����Ȩ��:"; s += (permissions == 3 ? "Ⱥ��" : permissions == 2 ? "����Ա" : "ȺԱ"); s += "("; s += to_string(permissions); s += ")";
	s += " ,������¼��Ա:"; s += to_string(NaughtyRecord);
	s += " ,ר��ͷ��:"; s += Title;
	s += " ,ר��ͷ�ι���ʱ��:"; s += to_string(ExpireTime);
	s += " ,�����޸���Ƭ:"; s += to_string(canEditGroupNick);
	s += "}"; return s;
}

//����������־
int CQ::addLog(int Priorty, const char* Type, const char* Content) { return lasterr = CQ_addLog(getAuthCode(), Priorty, Type, Content); }

//���ͺ�����Ϣ
int CQ::sendPrivateMsg(long long QQ, const char* msg) { return  CQ_sendPrivateMsg(getAuthCode(), QQ, msg); }

//���ͺ�����Ϣ
int CQ::sendPrivateMsg(long long QQ, std::string & msg) { return sendPrivateMsg(QQ, msg.c_str()); }

//���ͺ�����Ϣ
//int CQ::sendPrivateMsg(EVEPrivateMsg eve, std::string msg) { return sendPrivateMsg(eve.fromQQ, msg.c_str()); }

//����Ⱥ��Ϣ
int CQ::sendGroupMsg(long long GroupID, const char* msg) { return  CQ_sendGroupMsg(getAuthCode(), GroupID, msg); }

//����Ⱥ��Ϣ
int CQ::sendGroupMsg(long long GroupID, std::string & msg) { return sendGroupMsg(GroupID, msg.c_str()); }

int CQ::sendDiscussMsg(long long DiscussID, const char* msg) { return   CQ_sendDiscussMsg(getAuthCode(), DiscussID, msg); }

//������������Ϣ
int CQ::sendDiscussMsg(long long DiscussID, std::string & msg) { return sendDiscussMsg(DiscussID, msg.c_str()); }

//������
int CQ::sendLike(long long QQID, int times) { return lasterr = CQ_sendLikeV2(getAuthCode(), QQID, times); }

//ȡCookies (���ã��˽ӿ���Ҫ�ϸ���Ȩ)
const char* CQ::getCookies() { return  CQ_getCookies(getAuthCode()); }

//��������
const char* CQ::getRecord(const char* file, const char* outformat) { return CQ_getRecord(getAuthCode(), file, outformat); }

//��������
std::string CQ::getRecord(std::string & file, std::string outformat) { return getRecord(file.c_str(), outformat.c_str()); }

//ȡCsrfToken (���ã��˽ӿ���Ҫ�ϸ���Ȩ)
int CQ::getCsrfToken() { return  CQ_getCsrfToken(getAuthCode()); }

//ȡӦ��Ŀ¼
const char* CQ::getAppDirectory() { return  CQ_getAppDirectory(getAuthCode()); }

//ȡ��¼QQ
long long CQ::getLoginQQ() { return  CQ_getLoginQQ(getAuthCode()); }

//ȡ��¼�ǳ�
const char* CQ::getLoginNick() { return  CQ_getLoginNick(getAuthCode()); }

//��ȺԱ�Ƴ�
int CQ::setGroupKick(long long GroupID, long long QQID, CQBOOL refuseForever) { return lasterr = CQ_setGroupKick(getAuthCode(), GroupID, QQID, refuseForever); }

//��ȺԱ����
int CQ::setGroupBan(long long GroupID, long long QQID, long long banTime) { return lasterr = CQ_setGroupBan(getAuthCode(), GroupID, QQID, banTime); }

//��Ⱥ����Ա
int CQ::setGroupAdmin(long long GroupID, long long QQID, CQBOOL isAdmin) { return lasterr = CQ_setGroupAdmin(getAuthCode(), GroupID, QQID, isAdmin); }

//��Ⱥ��Աר��ͷ��
int CQ::setGroupSpecialTitle(long long GroupID, long long QQID, const char* Title, long long ExpireTime) { return lasterr = CQ_setGroupSpecialTitle(getAuthCode(), GroupID, QQID, Title, ExpireTime); }

//��Ⱥ��Աר��ͷ��
int CQ::setGroupSpecialTitle(long long GroupID, long long QQID, std::string & Title, long long ExpireTime) { return setGroupSpecialTitle(GroupID, QQID, Title.c_str(), ExpireTime); }

//��ȫȺ����
int CQ::setGroupWholeBan(long long GroupID, CQBOOL isBan) { return lasterr = CQ_setGroupWholeBan(getAuthCode(), GroupID, isBan); }

//��AnonymousȺԱ����
int CQ::setGroupAnonymousBan(long long GroupID, const char* Anonymous, long long banTime) { return lasterr = CQ_setGroupAnonymousBan(getAuthCode(), GroupID, Anonymous, banTime); }

//��ȺAnonymous����
int CQ::setGroupAnonymous(long long GroupID, CQBOOL enableAnonymous) { return lasterr = CQ_setGroupAnonymous(getAuthCode(), GroupID, enableAnonymous); }

//��Ⱥ��Ա��Ƭ
int CQ::setGroupCard(long long GroupID, long long QQID, const char* newGroupNick) { return lasterr = CQ_setGroupCard(getAuthCode(), GroupID, QQID, newGroupNick); }

//��Ⱥ��Ա��Ƭ
int CQ::setGroupCard(long long GroupID, long long QQID, std::string newGroupNick) { return setGroupCard(GroupID, QQID, newGroupNick.c_str()); }

//��Ⱥ�˳�
int CQ::setGroupLeave(long long GroupID, CQBOOL isDismiss) { return lasterr = CQ_setGroupLeave(getAuthCode(), GroupID, isDismiss); }

//���������˳�
int CQ::setDiscussLeave(long long DiscussID) { return lasterr = CQ_setDiscussLeave(getAuthCode(), DiscussID); }

//�ú�����������
int CQ::setFriendAddRequest(const char* RequestToken, int ReturnType, const char* Remarks) { return lasterr = CQ_setFriendAddRequest(getAuthCode(), RequestToken, ReturnType, Remarks); }

//��Ⱥ��������
int CQ::setGroupAddRequest(const char* RequestToken, int RequestType, int ReturnType, const char* Reason) { return lasterr = CQ_setGroupAddRequestV2(getAuthCode(), RequestToken, RequestType, ReturnType, Reason); }

//������������ʾ
int CQ::setFatal(const char* ErrorMsg) { return lasterr = CQ_setFatal(getAuthCode(), ErrorMsg); }

//ȡȺ��Ա��Ϣ (֧�ֻ���)
GroupMemberInfo CQ::getGroupMemberInfo(long long GroupID, long long QQID, CQBOOL disableCache) { return GroupMemberInfo(CQ_getGroupMemberInfoV2(getAuthCode(), GroupID, QQID, disableCache)); }

//ȡİ������Ϣ (֧�ֻ���)
StrangerInfo CQ::getStrangerInfo(long long QQID, CQBOOL disableCache) { return StrangerInfo(CQ_getStrangerInfo(getAuthCode(), QQID, disableCache)); }

//ȡȺ��Ա�б�
std::vector<GroupMemberInfo> CQ::getGroupMemberList(long long GroupID) {
	const char* data = CQ_getGroupMemberList(getAuthCode(), GroupID);
	vector<GroupMemberInfo> infovector;
	if (data[0] == '\0')return infovector;

	Unpack u(base64_decode(data));
	auto i = u.getInt();
	while (--i && u.len()>0)
	{
		infovector.push_back(GroupMemberInfo(u.getchars()));
		//infovector.emplace_back(GroupMemberInfo(u.getUnpack()));
	}

	return infovector;
}

//ȡȺ�б�
std::map<long long, std::string> CQ::getGroupList() {
	string source(CQ_getGroupList(getAuthCode()));// ��ȡԭʼ����
	string data(base64_decode(source)); // ����
	Unpack pack(data);// ת��ΪUnpack

	int len = pack.getInt();//��ȡ��Ⱥ��
	std::map<long long, std::string> ret;
	while (pack.len() > 0) {//�������ʣ������,�ͼ�����ȡ
		auto tep = pack.getUnpack();//��ȡ��һ��Ⱥ
		long long ID = tep.getLong();//��ȡGroupID
		string name = tep.getstring();//��ȡȺ����
		ret[ID] = name;//д��map
	}
	return ret;
}

int CQ::deleteMsg(long long MsgId)
{
	return lasterr = CQ_deleteMsg(getAuthCode(), MsgId);
}

const char * CQ::getlasterrmsg()
{
	switch (lasterr)
	{
	case 0:    return "�����ɹ�";
	case -1:   return "������ʧ��";
	case -2:   return "δ�յ��������ظ�������δ���ͳɹ�";
	case -3:   return "��Ϣ������Ϊ��";
	case -4:   return "��Ϣ���������쳣";
	case -5:   return "��־����δ����";
	case -6:   return "��־���ȼ�����";
	case -7:   return "�������ʧ��";
	case -8:   return "��֧�ֶ�ϵͳ�ʺŲ���";
	case -9:   return "�ʺŲ��ڸ�Ⱥ�ڣ���Ϣ�޷�����";
	case -10:  return "���û�������/����Ⱥ��";
	case -11:  return "���ݴ����޷�������";
	case -12:  return "��֧�ֶ�Anonymous��Ա�������";
	case -13:  return "�޷�����Ҫ���Ե�Anonymous��Ա����";
	case -14:  return "����δ֪ԭ�򣬲���ʧ��";
	case -15:  return "Ⱥδ����Anonymous���Թ��ܣ���Anonymous�ʺű�����";
	case -16:  return "�ʺŲ���Ⱥ�ڻ���������޷��˳�/��ɢ��Ⱥ";
	case -17:  return "�ʺ�ΪȺ�����޷��˳���Ⱥ";
	case -18:  return "�ʺŷ�Ⱥ�����޷���ɢ��Ⱥ";
	case -19:  return "��ʱ��Ϣ��ʧЧ��δ����";
	case -20:  return "��������";
	case -21:  return "��ʱ��Ϣ��ʧЧ��δ����";
	case -22:  return "��ȡQQ��Ϣʧ��";
	case -23:  return "�Ҳ�����Ŀ��QQ�Ĺ�ϵ����Ϣ�޷�����";
	case -99:  return "�����õĹ����޷��ڴ˰汾��ʵ��";
	case -101: return "Ӧ�ù���";
	case -102: return "���ǺϷ���Ӧ��";
	case -103: return "���ǺϷ���Ӧ��";
	case -104: return "Ӧ�ò����ڹ�����Information����";
	case -105: return "�޷�����Ӧ����Ϣ";
	case -106: return "�ļ�����Ӧ��ID��ͬ";
	case -107: return "������Ϣ��������";
	case -108: return "AppInfo���ص�Api�汾��֧��ֱ�Ӽ��أ���֧��Api�汾Ϊ9(������)��Ӧ��ֱ�Ӽ���";
	case -109: return "AppInfo���ص�AppID����";
	case -110: return "ȱʧAppInfo���ص�AppID��Ӧ��[Appid].json�ļ�";
	case -111: return "[Appid].json�ļ��ڵ�AppID�����ļ�����ͬ";
	case -120: return "��Api��Ȩ���պ���(Initialize)";
	case -121: return "Api��Ȩ���պ���(Initialize)����ֵ��0";
	case -122: return "���Զ����޸Ŀ�Q�����ļ�����ȡ�����ز��رտ�Q";
	case -150: return "�޷�����Ӧ����Ϣ";
	case -151: return "Ӧ����ϢJson������ʧ�ܣ�����Json���Ƿ���ȷ";
	case -152: return "Api�汾���ɻ����";
	case -153: return "Ӧ����Ϣ��������ȱʧ";
	case -154: return "Appid���Ϸ�";
	case -160: return "�¼�����(Type)�����ȱʧ";
	case -161: return "�¼�����(Function)�����ȱʧ";
	case -162: return "Ӧ�����ȼ���Ϊ10000��20000��30000��40000�е�һ��";
	case -163: return "�¼�����(Api)��֧��Ӧ��Api�汾";
	case -164: return "Ӧ��Api�汾����8����ʹ�����°汾��ͣ�õ��¼�����(Type)��1(������Ϣ)��3(��ʱ��Ϣ)";
	case -165: return "�¼�����Ϊ2(Ⱥ��Ϣ)��4(��������Ϣ)��21(˽����Ϣ)����ȱ���������ʽ(regex)�ı���ʽ����(expression)";
	case -166: return "����Ϊ�յ��������ʽ(regex)��key";
	case -167: return "����Ϊ�յ��������ʽ(regex)�ı���ʽ����(expression)";
	case -168: return "Ӧ���¼�(event)id���������ڻ�Ϊ0";
	case -169: return "Ӧ���¼�(event)id�������ظ�";
	case -180: return "Ӧ��״̬(status)id���������ڻ�Ϊ0";
	case -181: return "Ӧ��״̬(status)period���������ڻ����ô���";
	case -182: return "Ӧ��״̬(status)id�������ظ�";
	case -201: return "�޷�����Ӧ�ã�������Ӧ���ļ�����";
	case -202: return "Api�汾���ɻ����";
	case -997: return "Ӧ��δ����";
	case -998: return "Ӧ�õ�����Auth����֮��� ��Q Api��";
	default:   return "δ֪����";
	}
}