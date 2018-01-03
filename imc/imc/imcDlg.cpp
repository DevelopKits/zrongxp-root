
// imcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "imc.h"
#include "ims.h"
#include "imcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CimcDlg �Ի���



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


// CimcDlg ��Ϣ�������

BOOL CimcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);
	m_proc.SetRange(0, 100);
	m_width.SetWindowText(L"2048");
#ifdef _DEBUG
	m_folder.SetWindowTextW(L"C:\\Program Files (x86)\\IQIYI Video\\LStyle\\6.0.46.4598\\QYAppPlugin\\qixiu\\skin\\emoticon");
#endif
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CimcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		// �ļ��Ѿ�ת������
		CString str;
		m_folder.GetWindowText(str);
		//MessageBox(L"�ļ�ת�����ˣ�\n" + str + L"\\convert_out.png", 0, 0);
	}
}

void CimcDlg::func(TaskInfo *pm)
{
	// �ļ�Ŀ¼
	CString str;
	m_folder.GetWindowText(str);
	if (str.IsEmpty())
	{
		return;
	}
	if(pm->error.IsEmpty())
		MessageBox(L"�ļ�����\n" + str + L"\\convert_out.png");
	else
		MessageBox(L"�ļ�����ʧ��\n" + pm->error);
	m_start.EnableWindow(TRUE);
}

void CimcDlg::OnBnClickedButton1()
{
	// �ļ�Ŀ¼
	CString str;
	m_folder.GetWindowText(str);
	if (str.IsEmpty())
	{
		return;
	}
	m_start.EnableWindow(FALSE);
	// ͼƬ������
	CString strWidth;
	m_width.GetWindowText(strWidth);
	// ���õ�ǰ����
	m_proc.SetPos(0);
	// �����̲߳�ִ��
	taskparam *param = new taskparam;
	param->filepath = str;
	param->uithread = ::GetCurrentThreadId();
	param->width = _wtoi(strWidth);
	CThread *Thread = new CThread;
	Thread->CreateThread();
	PostPaskAsync(Thread->GetThreadId(), task, (DWORD)param, std::bind(&CimcDlg::func, this, std::placeholders::_1), ::GetCurrentThreadId(), L"");
}
