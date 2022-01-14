// pherr.h: interface for the CBaseThread class.
//
//////////////////////////////////////////////////////////////////////
/*! \file pherr.h
*  \author skyvense
*  \date   2009-09-14
*  \brief PHDDNS �ͻ���ʵ��	
*/

#ifndef __PHERR__H__
#define __PHERR__H__



//! �ͻ���״̬
enum MessageCodes
{
	okConnected = 0,		//tcp�Ѿ������Ϸ�����
	okAuthpassed,			//��֤�Ѿ�ͨ��
	okDomainListed,			//�õ������б����Ѽ���DDNS�����ǵģ�
	okDomainsRegistered,	//����������ע�ᣬ���濪ʼ��ʱkeepalive udp
	okKeepAliveRecved,		//�յ�һ��
	okConnecting,			//�������ӷ�����
	okRetrievingMisc,		//no use
	okRedirecting,			//����ת����һ��������

	errorConnectFailed = 0x100,	//tcp����ʧ�ܣ�ͬʱҲ��ʾ��½ʧ��
	errorSocketInitialFailed,	//socket��ʼ������ ��ͬʱҲ��ʾ��½ʧ��
	errorAuthFailed,			//�û�����������������滹�и�������æ��Ҳ�������ʱ����ܷ���
	errorDomainListFailed,		//�г������б�������Ѽ���DDNS�����ǵģ���ͬʱҲ��ʾ��½ʧ��
	errorDomainRegisterFailed,	//ĳ������ע�����ͬʱҲ��ʾ��½ʧ��
	errorUpdateTimeout,			//no use
	errorKeepAliveError,		//no use
	errorRetrying,
	errorAuthBusy,				//������æ
	errorStatDetailInfoFailed,  //��ȡ�û���Ϣ������ϸ�����б�ʧ�ܣ�ͬʱҲ��ʾ��½ʧ��
	

	okNormal = 0x120,
	okNoData,					//keepalive����
	okServerER,					//keepalive����
	errorOccupyReconnect,		//�����������ӷ�����
};

#endif // __PHERR__H__
