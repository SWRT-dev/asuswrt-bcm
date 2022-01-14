// phupdate.h: interface for the CBaseThread class.
//
//////////////////////////////////////////////////////////////////////
/*! \file phupdate.h
*  \author skyvense
*  \date   2009-09-14
*  \brief PHDDNS �ͻ���ʵ��	
*/

#ifndef _CUPDATECORE_H
#define _CUPDATECORE_H

#include "phglobal.h"

//! ������DDNS�ͻ���ʵ�ֻ���
/*!
*/
	

	//! �������ã����úò�������Ҫ��������˺��������������´���Ҫִ�б�������ʱ�䣨������
	int phddns_step(PHGlobal *phglobal);	

	//! ֹͣ������DDNS���£��������ò�����ɽ�����һ��
	void phddns_stop(PHGlobal *phglobal);

	//! ��ʼ��socket
	BOOL InitializeSockets(PHGlobal *phglobal);
	//! �ر�����socket
	BOOL DestroySockets(PHGlobal *phglobal);
	//! ��DDNS���������ӵ�TCP������
	int ExecuteUpdate(PHGlobal *phglobal);
	//! ����UDP�����ӡ�
	BOOL BeginKeepAlive(PHGlobal *phglobal);
	//! ����һ��UDP������
	BOOL SendKeepAlive(PHGlobal *phglobal, int opCode);
	//! ��������������
	int RecvKeepaliveResponse(PHGlobal *phglobal);

#endif