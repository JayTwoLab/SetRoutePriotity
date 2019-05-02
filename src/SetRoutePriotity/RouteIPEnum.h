
#pragma once

class CIPEnum;
class CSetRoutePriotityDlg; 

class CRouteIPEnum : public CIPEnum
{
public:
	CRouteIPEnum(void);
	~CRouteIPEnum(void);

public:
	virtual BOOL EnumCallbackFunction(int nAdapter, const in_addr& address);

public:
	CSetRoutePriotityDlg* m_pSetRoutePriotityDlg; 

};


