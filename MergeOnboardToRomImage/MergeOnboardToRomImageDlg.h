
// MergeOnboardToRomImageDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

//DEBUG调试口
#define DEBUG_PORT    1

//验证什么标志位    VERIFY_NAME->0   VERIFY_ADDRESS->1
#define VERIFY_NAME         0
#define VERIFY_ADDRESS      1

//堆积验证二维数组行列数
#define ROW			    100   //列数
#define COL				20    //行数

//读取到标志位后，开始缓存数据缓冲区大小
#define LENTH_TITLE        512

//各地址偏移值
#define DDROFFSET_UNCOMMENT   12
#define DDROFFSET_COMMENT     (DDROFFSET_UNCOMMENT+1)

//进度条步进长度
#define  PROGRESSPOS_START   0
#define  PROGRESSPOS_DEAL    20
#define  PROGRESSPOS_END     200

typedef struct  
{
	char szNameFile[MAX_PATH];        //文件名
	long lSizeFile;                   //各个文件的实际大小
	char szAddr[MAX_PATH];            //没有处理的地址字符串
	long Address;                     //RomImage中的偏移地址
	bool bAddrError;                  //地址有问题吗？   false-没有问题  true-有问题(地址为空) 
}NAME_ADD,*P_NAME_ADD;

typedef struct  
{
	NAME_ADD name_add[9];
}INFO_NAME_ADD,*P_INFO_NAME_ADD;

// CMergeOnboardToRomImageDlg 对话框
class CMergeOnboardToRomImageDlg : public CDialogEx
{
// 构造
public:
	CMergeOnboardToRomImageDlg(CWnd* pParent = NULL);	// 标准构造函数

	int GetMergeFileSize( P_INFO_NAME_ADD infoNameAdd );   //读取文件大小到infoNameAdd结构体中
	int GetInfromatinFromRomImageFile(char *Path, P_INFO_NAME_ADD infoNameAdd);  // 从RomImage文件中获取到要合并文件的名字和地址信息
	int VerifyFlagFromArray( char v_pVerifyFlag[COL][ROW], char v_pGetDateBuf[LENTH_TITLE], int iFlag );
	int ConvertAddrAndSequence( P_INFO_NAME_ADD infoNameAdd );    //将地址字符串转化成Long类型，并通过顺地址排序
	int VerifyAddrError( P_INFO_NAME_ADD infoNameAdd );           //验证地址字符串是否有问题
	int SequenceInfoNameAddStruct( P_INFO_NAME_ADD infoNameAdd ); //按照地址从小到达的重新排序infoNameAdd结构体，为后面RomImage合并做准备
	void LongArraySequence( long *v_LongArray, long Len );        //对整型数组进行排序
	bool VerifyRomImageSize( P_INFO_NAME_ADD infoNameAdd );       //通过地址上判断数据是不是超过RomImage缓存器大小，大于跳出提示，APP退出
	int MergeImageFile( P_INFO_NAME_ADD infoNameAdd );            //通过infoNameAdd结构体信息合并Romimage文件
	long GetMergeFileData( byte *FileData, int Index, P_INFO_NAME_ADD infoNameAdd );         //读取合并子文件内容
	void SetProgressPos( long lPos );                             //设置进度条位置
	int  iLenOnboardPath;
	char szPath[MAX_PATH];           //存放选择的目录路径
	INFO_NAME_ADD infoNameAdd;     //合并RomImage文件的子文件信息
	int  iSumFile;                   //需要合并的文件个数
	int  nIndex;                     //选择芯片的类型
	CProgressCtrl *m_Pro;            //进度条控件

// 对话框数据
	enum { IDD = IDD_MERGEONBOARDTOROMIMAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	CComboBox m_RomSizeCombo;
};
