#include "stdafx.h"
#include "Thread.h"
#include "ims.h"

CThread::CThread()
{
	m_hThread = NULL;
	m_nThreadID = GetCurrentThreadId();
	m_dwCode = 0;
	_idle_count = 0;
	_hMessageInited = NULL;
}

CThread::~CThread()
{
}

UINT WINAPI xThreadEntry(void *pData)
{
	CThread *pThread = (CThread*)pData;

	// 指针检测
	if (pThread == NULL)
	{
		return 0xFFFFFFFF;
	}

	// 初始化
	PostThreadMessage(pThread->m_nThreadID, WM_THREADINIT, 0, 0);

	// 开始执行
	pThread->OnThreadRun();

	// 线程退出
	DWORD code = pThread->OnThreadExit();
	delete pThread;
	::_endthreadex(code);
	return 0x1111;
}

DWORD CThread::CreateThread(DWORD dwCreateFlags, UINT nStackSize, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{
	// 只能创建一次
	if (m_hThread != NULL)
	{
		return m_nThreadID;
	}

	// 创建一个新线程
	_hMessageInited = ::CreateEvent(0, FALSE, FALSE, 0);
	m_hThread = (HANDLE)_beginthreadex(lpSecurityAttrs, nStackSize, &xThreadEntry, this, dwCreateFlags, (UINT*) &m_nThreadID);
	// 等到vmpage主线程创建完毕
	::WaitForSingleObject(_hMessageInited, INFINITE);
	return m_nThreadID;
}

BOOL CThread::OnInit()
{
	return TRUE;
}

void CThread::OnThreadRun()
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));
	while(msg.message != WM_QUIT)
    {
		if(GetMessage(&msg, NULL, 0, 0))
		{
			if(msg.message == WM_THREADINIT)
			{
				::SetEvent(_hMessageInited);
				if (!OnInit())
				{
					return ;
				}
			}
			if (msg.message == WM_USER + 1001)
			{
				RunTask(msg.wParam);
				::PostThreadMessage(m_nThreadID, WM_QUIT, 0, 0);
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
        if(!::PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE))
        {
			if(_idle_count > 10000)
			{
				_idle_count = 10000;
			}
			else
			{
				_idle_count++;
			}
			OnIdle(_idle_count);
        }
    }
}

void CThread::RunTask(DWORD wParam)
{
	TaskInfo *taskinfo = (TaskInfo*)wParam;
	if(taskinfo)
	{
		taskinfo->task(taskinfo);
		// 返回到界面
		if(taskinfo->thread)
		{
			PostPaskAsync(taskinfo->thread, taskinfo->ret, 0, NULL, 0, taskinfo->error);
		}
		delete taskinfo;
	}
}

void CThread::OnIdle(int idlecount)
{
}

DWORD CThread::OnThreadExit()
{
	return 0x9991;
}

void CThread::ExitThread(DWORD dwCode, BOOL bAsync)
{
	::PostThreadMessage(m_nThreadID, WM_QUIT, 0, 0);
}

void CThread::OnPreTranslateMessage(MSG* pMsg)
{
}

DWORD CThread::ResumeThread()
{
	return ::ResumeThread(m_hThread);
}

DWORD CThread::SuspendThread()
{
	return ::SuspendThread(m_hThread);
}

HANDLE CThread::GetHandle()
{
	return m_hThread;
}

DWORD CThread::GetThreadId()
{
	return m_nThreadID;
}

void PostPaskAsync(DWORD proc, std::function<void(TaskInfo*)> task, DWORD param, std::function<void(TaskInfo*)> ret, DWORD threadret, LPCWSTR error)
{
	TaskInfo *taskinfo = new TaskInfo;
	taskinfo->task = task;
	taskinfo->param = param;
	taskinfo->ret = ret;
	taskinfo->thread = threadret;
	taskinfo->error = error;
	::PostThreadMessage(proc, WM_USER + 1001, (DWORD)taskinfo, 0);
}