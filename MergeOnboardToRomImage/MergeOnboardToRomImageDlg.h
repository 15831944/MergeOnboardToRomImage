
// MergeOnboardToRomImageDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

//DEBUG���Կ�
#define DEBUG_PORT    1

//��֤ʲô��־λ    VERIFY_NAME->0   VERIFY_ADDRESS->1
#define VERIFY_NAME         0
#define VERIFY_ADDRESS      1

//�ѻ���֤��ά����������
#define ROW			    100   //����
#define COL				20    //����

//��ȡ����־λ�󣬿�ʼ�������ݻ�������С
#define LENTH_TITLE        512

//����ַƫ��ֵ
#define DDROFFSET_UNCOMMENT   12
#define DDROFFSET_COMMENT     (DDROFFSET_UNCOMMENT+1)

//��������������
#define  PROGRESSPOS_START   0
#define  PROGRESSPOS_DEAL    20
#define  PROGRESSPOS_END     200

typedef struct  
{
	char szNameFile[MAX_PATH];        //�ļ���
	long lSizeFile;                   //�����ļ���ʵ�ʴ�С
	char szAddr[MAX_PATH];            //û�д���ĵ�ַ�ַ���
	long Address;                     //RomImage�е�ƫ�Ƶ�ַ
	bool bAddrError;                  //��ַ��������   false-û������  true-������(��ַΪ��) 
}NAME_ADD,*P_NAME_ADD;

typedef struct  
{
	NAME_ADD name_add[9];
}INFO_NAME_ADD,*P_INFO_NAME_ADD;

// CMergeOnboardToRomImageDlg �Ի���
class CMergeOnboardToRomImageDlg : public CDialogEx
{
// ����
public:
	CMergeOnboardToRomImageDlg(CWnd* pParent = NULL);	// ��׼���캯��

	int GetMergeFileSize( P_INFO_NAME_ADD infoNameAdd );   //��ȡ�ļ���С��infoNameAdd�ṹ����
	int GetInfromatinFromRomImageFile(char *Path, P_INFO_NAME_ADD infoNameAdd);  // ��RomImage�ļ��л�ȡ��Ҫ�ϲ��ļ������ֺ͵�ַ��Ϣ
	int VerifyFlagFromArray( char v_pVerifyFlag[COL][ROW], char v_pGetDateBuf[LENTH_TITLE], int iFlag );
	int ConvertAddrAndSequence( P_INFO_NAME_ADD infoNameAdd );    //����ַ�ַ���ת����Long���ͣ���ͨ��˳��ַ����
	int VerifyAddrError( P_INFO_NAME_ADD infoNameAdd );           //��֤��ַ�ַ����Ƿ�������
	int SequenceInfoNameAddStruct( P_INFO_NAME_ADD infoNameAdd ); //���յ�ַ��С�������������infoNameAdd�ṹ�壬Ϊ����RomImage�ϲ���׼��
	void LongArraySequence( long *v_LongArray, long Len );        //�����������������
	bool VerifyRomImageSize( P_INFO_NAME_ADD infoNameAdd );       //ͨ����ַ���ж������ǲ��ǳ���RomImage��������С������������ʾ��APP�˳�
	int MergeImageFile( P_INFO_NAME_ADD infoNameAdd );            //ͨ��infoNameAdd�ṹ����Ϣ�ϲ�Romimage�ļ�
	long GetMergeFileData( byte *FileData, int Index, P_INFO_NAME_ADD infoNameAdd );         //��ȡ�ϲ����ļ�����
	void SetProgressPos( long lPos );                             //���ý�����λ��
	int  iLenOnboardPath;
	char szPath[MAX_PATH];           //���ѡ���Ŀ¼·��
	INFO_NAME_ADD infoNameAdd;     //�ϲ�RomImage�ļ������ļ���Ϣ
	int  iSumFile;                   //��Ҫ�ϲ����ļ�����
	int  nIndex;                     //ѡ��оƬ������
	CProgressCtrl *m_Pro;            //�������ؼ�

// �Ի�������
	enum { IDD = IDD_MERGEONBOARDTOROMIMAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
