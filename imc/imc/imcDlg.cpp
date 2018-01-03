
// imcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "imc.h"
#include "ims.h"
#include "imcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CimcDlg 对话框



CimcDlg::CimcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CimcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_proc);
	DDX_Control(pDX, IDC_BUTTON1, m_start);
	DDX_Control(pDX, IDC_EDIT1, m_folder);
	DDX_Control(pDX, IDC_EDIT3, m_width);
}

BEGIN_MESSAGE_MAP(CimcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CimcDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CimcDlg 消息处理程序

BOOL CimcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);
	m_proc.SetRange(0, 100);
	m_width.SetWindowText(L"2048");
#ifdef _DEBUG
	m_folder.SetWindowTextW(L"C:\\Program Files (x86)\\IQIYI Video\\LStyle\\6.0.46.4598\\QYAppPlugin\\qixiu\\skin\\emoticon");
#endif
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CimcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CimcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CimcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CimcDlg::proc(imageinfo &info, int pos, int size)
{
	m_proc.SetPos(pos * 100 / size);
	if (pos == size)
	{
		m_start.EnableWindow(TRUE);
		// 文件已经转化好了
		CString str;
		m_folder.GetWindowText(str);
		//MessageBox(L"文件转化好了：\n" + str + L"\\convert_out.png", 0, 0);
	}
}

void CimcDlg::func(TaskInfo *pm)
{
	// 文件目录
	CString str;
	m_folder.GetWindowText(str);
	if (str.IsEmpty())
	{
		return;
	}
	if(pm->error.IsEmpty())
		MessageBox(L"文件生成\n" + str + L"\\convert_out.png");
	else
		MessageBox(L"文件生成失败\n" + pm->error);
	m_start.EnableWindow(TRUE);
}

void CimcDlg::OnBnClickedButton1()
{
	// 文件目录
	CString str;
	m_folder.GetWindowText(str);
	if (str.IsEmpty())
	{
		return;
	}
	m_start.EnableWindow(FALSE);
	// 图片宽度输出
	CString strWidth;
	m_width.GetWindowText(strWidth);
	// 设置当前进度
	m_proc.SetPos(0);
	// 启动线程并执行
	taskparam *param = new taskparam;
	param->filepath = str;
	param->uithread = ::GetCurrentThreadId();
	param->width = _wtoi(strWidth);
	CThread *Thread = new CThread;
	Thread->CreateThread();
	PostPaskAsync(Thread->GetThreadId(), task, (DWORD)param, std::bind(&CimcDlg::func, this, std::placeholders::_1), ::GetCurrentThreadId(), L"");
}
