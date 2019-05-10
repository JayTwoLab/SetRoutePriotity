#ifndef _ROUTE_IP_ENUM_H
#define _ROUTE_IP_ENUM_H

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

#endif