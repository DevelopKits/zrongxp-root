#pragma once

// 开始名字空间 xUICommon
#define WM_THREADINIT (WM_USER + 0x0100)
extern DWORD THREAD_UI;
extern DWORD THREAD_WORK;

// 线程类
class CThread
{
public:
	/** 构构函数
	*/
	CThread();

	/** 析构函数
	*/
	virtual ~CThread();
protected:
	// 线程句柄
	HANDLE m_hThread;

	// 线程ID
	DWORD m_nThreadID;

	// 现程退出代码
	DWORD m_dwCode;
	// 空闲次数计数器
	int _idle_count;
	// 线程的消息队列初始化完成的信号量
	HANDLE _hMessageInited;
public:
	DWORD m_uiThreadID;
	CString m_strFolder;
protected:
	/** 初始化
	*/
	virtual BOOL OnInit();

	/** 线程退出时
		@dwCode 退出状态码
	*/
	virtual DWORD OnThreadExit();

	/** 在运行时
	*/
	virtual void OnThreadRun();

	/** 在处理消息
	*/
	virtual void OnPreTranslateMessage(MSG* pMsg);
	// 线程空闲时
	virtual void OnIdle(int idlecount);
private:
	/** 线程入口
	*/
	friend UINT WINAPI xThreadEntry(void *pData);
public:
	/** 创建线程
	*/
	DWORD CreateThread(DWORD dwCreateFlags = 0, UINT nStackSize = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

	/** 挂起线程
	*/
	DWORD SuspendThread();

	/** 继续执行线程
	*/
	DWORD ResumeThread();

	/** 退出线程
		@bAsync 是否异步执行
		*/
	void ExitThread(DWORD dwCode, BOOL bAsync);

	/** 返回线程句柄
	*/
	HANDLE GetHandle();

	/** 返回线程ID
	*/
	DWORD GetThreadId();
	// 执行任务
	void RunTask(DWORD wParam);
};

// 任务信息
struct TaskInfo
{
	// 执行任务函数
	std::function<void(DWORD)> task;
	// 任务参数
	DWORD param;
	// 回调线程
	DWORD thread;
	// 回调函数
	std::function<void(DWORD)> ret;
};

// 执行异步任务
extern void PostPaskAsync(DWORD proc, std::function<void(DWORD)> task, DWORD param, std::function<void(DWORD)> ret, DWORD threadret);