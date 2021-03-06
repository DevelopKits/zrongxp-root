
// imc.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "imc.h"
#include "imcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CimcApp

BEGIN_MESSAGE_MAP(CimcApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CimcApp::CimcApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}


// 唯一的一个 CimcApp 对象

CimcApp theApp;

BOOL CimcApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	CimcDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



BOOL CimcApp::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_USER + 1000)
	{
		posinfo *info = (posinfo*)pMsg->wParam;
		CimcDlg *dlg = (CimcDlg*)m_pMainWnd;
		dlg->proc(info->info, info->pos, info->size);
		delete info;
	}
	else if (pMsg->message == WM_USER + 1001)
	{
		RunTask(pMsg->wParam);
	}
	return CWinApp::PreTranslateMessage(pMsg);
}

void CimcApp::RunTask(DWORD wParam)
{
	TaskInfo *taskinfo = (TaskInfo*)wParam;
	if (taskinfo)
	{
		taskinfo->task(taskinfo);
		// 返回到界面
		if (taskinfo->thread)
		{
			PostPaskAsync(taskinfo->thread, taskinfo->ret, 0, NULL, 0, L"");
		}
		delete taskinfo;
	}
}