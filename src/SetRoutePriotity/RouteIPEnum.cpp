
#include "StdAfx.h"

#include "RouteIPEnum.h"

CRouteIPEnum::CRouteIPEnum(void)
{
	m_pSetRoutePriotityDlg = NULL; 
}

CRouteIPEnum::~CRouteIPEnum(void)
{
}

BOOL CRouteIPEnum::EnumCallbackFunction(int nAdapter, const in_addr& address)
{
	if ( m_pSetRoutePriotityDlg == NULL )
		return TRUE; 

	// printf("%0d        %d.%d.%d.%d\n", nAdapter, address.S_un.S_un_b.s_b1, 
	//	address.S_un.S_un_b.s_b2, address.S_un.S_un_b.s_b3, address.S_un.S_un_b.s_b4);

	CString strIP;
	strIP.Format( 
		_T(" %d.%d.%d.%d"),  
		address.S_un.S_un_b.s_b1, 
		address.S_un.S_un_b.s_b2, 
		address.S_un.S_un_b.s_b3, 
		address.S_un.S_un_b.s_b4 );
	
	m_pSetRoutePriotityDlg->m_lbIP.AddString( strIP );  

	//in this case where we are just displaying the IP address 
	//always continue enumeration
	return TRUE;
}

