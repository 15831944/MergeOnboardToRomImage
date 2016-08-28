
// MergeOnboardToRomImageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MergeOnboardToRomImage.h"
#include "MergeOnboardToRomImageDlg.h"
#include "afxdialogex.h"
#include <io.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char *ubootinf_name   = "uboot.inf";
char *uboot_name      = "u-boot.spi-boot";
char *RomCodeinf_name = "RomCode.inf";
char *uuImage_name    = "uuImage.lzo";
char *root_name       = "root.squashfs.lzo";
char *rw_name         = "rw.jffs2";
char *AdjDatainf_name = "AdjData.inf";
char *rw2_name        = "rw2.jffs2";

enum{
	fn_uboot = 0,
	fn_uuImage,
	fn_rootsquashfs,
	fn_rw,
	fn_rw2,
	fn_rw3,
	fn_INVALID
}eFN_TYPE;

enum{
	ad_enable = 0,
	ad_disable,
	ad_INVALID
}eAD_TYPE;

//������֤�ѻ���ά��������(ûע��)
char FileNameFlag1[COL][ROW] = {
									"ExecuteFile=\"u-boot.spi-boot\"",     //u-boot.spi-boot��>0
									"File=\"uuImage.lzo\"",                //uuImage.lzo��>1
									"File=\"root.squashfs.lzo\"",          //root.squashfs.lzo��>2
									"File=\"rw.jffs2\"",                   //rw.jffs2��>3
									"File=\"rw2.jffs2\"",                  //rw2.jffs2��>4
									"File=\"rw3.jffs2\""                   //rw3.jffs2��>5
                                  };
//������֤�ѻ���ά��������(��ע��)
char FileNameFlag2[COL][ROW] = {
									";ExecuteFile=\"u-boot.spi-boot\"",     //u-boot.spi-boot��>10
									";File=\"uuImage.lzo\"",                //uuImage.lzo��>11
									";File=\"root.squashfs.lzo\"",          //root.squashfs.lzo��>12
									";File=\"rw.jffs2\"",                   //rw.jffs2��>13
									";File=\"rw2.jffs2\"",                  //rw2.jffs2��>14
									";File=\"rw3.jffs2\""                   //rw3.jffs2��>5
								 };
//������֤�ѻ���ά��������(ûע��)
char FileNameFlag3[COL][ROW] = {
									"File=\"u-boot.spi-boot\"",             //u-boot.spi-boot��>0
									"File=\"uuImage.lzo\"",                 //uuImage.lzo��>1
									"File=\"root.squashfs.lzo\"",           //root.squashfs.lzo��>2
									"File=\"rw.jffs2\"",                    //rw.jffs2��>3
									"File=\"rw2.jffs2\"",                   //rw2.jffs2��>4
									"File=\"rw3.jffs2\""                    //rw3.jffs2��>5
								};
//������֤�ѻ���ά��������(��ע��)
char FileNameFlag4[COL][ROW] = {
									";File=\"u-boot.spi-boot\"",            //u-boot.spi-boot��>10
									";File=\"uuImage.lzo\"",                //uuImage.lzo��>11
									";File=\"root.squashfs.lzo\"",          //root.squashfs.lzo��>12
									";File=\"rw.jffs2\"",                   //rw.jffs2��>13
									";File=\"rw2.jffs2\"",                 //rw2.jffs2��>14
									";File=\"rw3.jffs2\""                   //rw3.jffs2��>5
								};
//������֤�ѻ���ά��������(Ҫ��������ļ�����Ӧ)
char FileName[COL][ROW] =     {
									"u-boot.spi-boot",                      //u-boot.spi-boot��>0
									"uuImage.lzo",                          //uuImage.lzo��>1
									"root.squashfs.lzo",                    //root.squashfs.lzo��>2
									"rw.jffs2",                             //rw.jffs2��>3
									"rw2.jffs2",                            //rw2.jffs2��>4
									"rw3.jffs2"                             //rw3.jffs2��>5
								};

char AddFlag[COL][ROW]   =   {
								    "DDROFFSET=0x",
								    ";DDROFFSET=0x"
							   };

char *MergeRes_name = "ResultFile.bin";

long SizeRomImageContain[10] = {
									0x01000000,                   //��Ӧ�����˵��ĵ�һ��оƬ MX25L12835 ��������Ӧ�±� m_RomSizeCombo.InsertString(0,_T("MX25L12835"));
									0x02000000,                   //��Ӧ�����˵��ĵ�һ��оƬ MX25L25635 ��������Ӧ�±� m_RomSizeCombo.InsertString(1,_T("MX25L25635"));
									0x04000000,                   //��Ӧ�����˵��ĵ�һ��оƬ MX25L51235 ��������Ӧ�±� m_RomSizeCombo.InsertString(2,_T("MX66L51235"));
							    };

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMergeOnboardToRomImageDlg �Ի���


CMergeOnboardToRomImageDlg::CMergeOnboardToRomImageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMergeOnboardToRomImageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMergeOnboardToRomImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ROMSIZECOMBO, m_RomSizeCombo);
}

BEGIN_MESSAGE_MAP(CMergeOnboardToRomImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMergeOnboardToRomImageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CMergeOnboardToRomImageDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMergeOnboardToRomImageDlg ��Ϣ�������

BOOL CMergeOnboardToRomImageDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	//RomSize�����˵���ʼ��
	m_RomSizeCombo.InsertString(0,_T("MX25L12835"));
	m_RomSizeCombo.InsertString(1,_T("MX25L25635"));
	m_RomSizeCombo.InsertString(2,_T("MX66L51235"));

	iLenOnboardPath = 0;   iSumFile = 0;
	memset( szPath, 0x00, MAX_PATH );
	memset( &infoNameAdd, '\0', sizeof(infoNameAdd) );
	m_Pro=(CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);

	//����ѻ��к�COLС��������fn_INVALID���쳣����ʾ�˳�
	if ( COL < fn_INVALID )
	{
		AfxMessageBox(_T("COL < fn_INVALID error!"));
		exit(0);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMergeOnboardToRomImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMergeOnboardToRomImageDlg::OnPaint()
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
HCURSOR CMergeOnboardToRomImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CMergeOnboardToRomImageDlg::GetMergeFileSize( P_INFO_NAME_ADD infoNameAdd )
{
	int iRes = -1;
	char pFile[200] = {0};
	char pbuf[2048] = {0};
	char cGetChar;
	FILE *fp = NULL;
	long lSizeFile = 0;
	char szErrorPrompt[200] = {0};
	int  iAddrSet = 0;
	//������Ϣ�ļ�ͷ�ȼӺ�
	sprintf( szErrorPrompt+iAddrSet, "ȱ�������ļ�:\n", strlen("ȱ�������ļ�:\n") );
	iAddrSet += strlen("ȱ�������ļ�:\n");
	for ( int iCnt=0; iCnt<iSumFile; iCnt++ )
	{
		memset( pFile, '\0', sizeof(pFile) );   lSizeFile = 0;
		sprintf( pFile, "%s", szPath );
		sprintf( pFile+iLenOnboardPath, "\\" );
		sprintf( pFile+iLenOnboardPath+1, "%s", FileName[iCnt] );
		//ѭ����ȡ�ļ�
		fp = fopen( pFile, "rb" );
		if( fp == NULL ) 
		{
			iRes = 1;
			sprintf( szErrorPrompt+iAddrSet, FileName[iCnt], strlen(FileName[iCnt]) );
			iAddrSet += strlen(FileName[iCnt]);
			sprintf( szErrorPrompt+iAddrSet, ";\n", strlen(";\n") );
			iAddrSet += strlen(";\n");
			continue;     //�򲻿��ļ���������һ���ļ���д
		}
		while( cGetChar = getc( fp ) != EOF )
		{
			lSizeFile++ ;
		}
		//��ȡ���ļ����洢�ļ���С
		infoNameAdd->name_add[iCnt].lSizeFile = lSizeFile;
		fclose( fp );
		fp = NULL;
	}
	//ȱʲô�ļ�����ʾ����
	if( 1==iRes )
	{
		AfxMessageBox(_T(szErrorPrompt));
	}
	return iRes;
}


void CMergeOnboardToRomImageDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ���������� 
	CString str;
	memset(szPath, '\0', sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "��ѡ��Onboard�ļ�Ŀ¼��";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//����ѡ��Ŀ¼�Ի���
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if(lp && SHGetPathFromIDList(lp, szPath))
	{
		SetDlgItemText(IDC_EDIT1,szPath);
		iLenOnboardPath = strlen( szPath );
	}
	else
	{
		AfxMessageBox("Browse Dir Error!");
	}
}


void CMergeOnboardToRomImageDlg::OnBnClickedOk()
{
	//ÿ�ε��ת����ť���������ֵ������ѻ�
	nIndex = m_RomSizeCombo.GetCurSel();
	if( 0==nIndex|| 1==nIndex )
	{
		iSumFile = 5;
	}
	else if ( 2==nIndex )
	{
		iSumFile = 6;
	}
	else
	{
		;//Alian:����������������Ҫ�ϲ����ļ�ʱ��չ
	}
	//���ý��������ȡ�ÿһ������
	m_Pro->SetRange( PROGRESSPOS_START, PROGRESSPOS_END );
	m_Pro->SetPos( PROGRESSPOS_START );
	//m_Pro->SetStep(1);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ������û��RomCode.inf�ļ�
	char Path_RomCodeInf[MAX_PATH] = {0};
	memset( Path_RomCodeInf, '\0', sizeof(Path_RomCodeInf) );
	sprintf( Path_RomCodeInf, "%s", szPath );
	sprintf( Path_RomCodeInf+iLenOnboardPath, "\\" );
	sprintf( Path_RomCodeInf+iLenOnboardPath+1, "%s", RomCodeinf_name );
	if ( 0 == access(Path_RomCodeInf,0) )
	{
		//�ȶ�ȡ���ļ�ʵ�ʴ�С��infoNameAdd�ṹ����
		GetMergeFileSize( &infoNameAdd );
		m_Pro->SetPos( PROGRESSPOS_DEAL/2 );
		//��AdjData.inf�ļ��л�ȡ��Ҫ�ϲ����ļ���Ϣ(��ַ������)
		GetInfromatinFromRomImageFile( Path_RomCodeInf, &infoNameAdd );
		//����֤��ַ��û�У�û�о���ʾ����
		VerifyAddrError( &infoNameAdd );
		//���°��յ�ַ��С����˳������
		ConvertAddrAndSequence( &infoNameAdd );
		//ͨ����ַ���ж������ǲ��ǳ���RomImage��������С������������ʾ��APP�˳�
		if (!VerifyRomImageSize( &infoNameAdd ))
		{
			return;
		}
		m_Pro->SetPos( PROGRESSPOS_DEAL );
		//�ϲ�RomImage�ļ�
		MergeImageFile( &infoNameAdd );
		m_Pro->SetPos( PROGRESSPOS_END );
		//�ϲ������ʾ
		AfxMessageBox(_T("RomCode.inf merge success!"));
	}
	else
	{
		AfxMessageBox(_T("RomCode.inf file not found!"));
	}
}

int CMergeOnboardToRomImageDlg::GetInfromatinFromRomImageFile( char *Path, P_INFO_NAME_ADD pInfoNameAdd )
{
	FILE *fp = NULL;
	char pGetDateBuf[LENTH_TITLE+1] = {0};
	int  iFileNameType1 = -1;     //��ȡ���ļ���ûע�ͱ�־λ
	int  iFileNameType2 = -1;     //��ȡ���ļ�����ע�ͱ�־λ
	int  iFileNameType3 = -1;     //��ȡ���ļ���ûע�ͱ�־λ
	int  iFileNameType4 = -1;     //��ȡ���ļ�����ע�ͱ�־λ
	int  iAddrGetType1 = -1;      //��ȡ��ƫ�Ƶ�ַûע�ͱ�־λ
	int  iAddrGetType2 = -1;      //��ȡ��ƫ�Ƶ�ַ��ע�ͱ�־λ
	int  iAddrGetType = -1;
	int  iSaveIndex = -1;
	int  iCommented = -1;         //δע��Ϊ0��ע��Ϊ1

	fp = fopen( Path, "a+" );
	if( fp == NULL )    //RomCode.inf �ļ���ʧ��
	{
		AfxMessageBox(_T("Open RomCode.inf file fail!"));
		return 0;
	}
	else       //RomCode.inf �ļ��򿪳ɹ�
	{
		//�����ļ�������(����EOF�ͽ���)
		while( !feof(fp) )
		{
			//���ļ��ж�һ���ַ���
			fgets( pGetDateBuf, LENTH_TITLE, fp );

			//�����ļ���(ע�͡�����ע��)
			iFileNameType1 = VerifyFlagFromArray( FileNameFlag1, pGetDateBuf, VERIFY_NAME );
			iFileNameType2 = VerifyFlagFromArray( FileNameFlag2, pGetDateBuf, VERIFY_NAME );
			iFileNameType3 = VerifyFlagFromArray( FileNameFlag3, pGetDateBuf, VERIFY_NAME );
			iFileNameType4 = VerifyFlagFromArray( FileNameFlag4, pGetDateBuf, VERIFY_NAME );
			//����ÿһ�п�ʼ��������
			/* һ��ƥ��(FileNameFlag1ƥ��FileNameFlag2)���жϷ���һ�� */
			if ( -1!=iFileNameType1 )
			{
				iSaveIndex = iFileNameType1;    iCommented = 0;
				{ 
				  iAddrGetType = -1; iAddrGetType1 = -1;         //ÿһ�λ�ȡ���ļ���ʱ��Ҫ�������ַ��־λ
				  memset( pInfoNameAdd->name_add[iFileNameType1].szNameFile, '\0', MAX_PATH );   //����ļ���
				  memset( pInfoNameAdd->name_add[iFileNameType1].szAddr, '\0', MAX_PATH );       //�����ַ
				  pInfoNameAdd->name_add[iFileNameType1].Address = 0;   //ת����ĵ�ַҲ��0(��Ҫ�ǿ��ǲ��ص�APP���������ݲ���)
				}
				memcpy( pInfoNameAdd->name_add[iFileNameType1].szNameFile, FileName[iFileNameType1], strlen(FileName[iFileNameType1]) );
			}
			if ( -1==iFileNameType1 && -1!=iFileNameType2  )
			{
				iSaveIndex = iFileNameType2;    iCommented = 1;
				{ 
					iAddrGetType = -1; iAddrGetType1 = -1;          //ÿһ�λ�ȡ���ļ���ʱ��Ҫ�������ַ��־λ
					memset( pInfoNameAdd->name_add[iFileNameType2].szNameFile, '\0', MAX_PATH );   //����ļ���
					memset( pInfoNameAdd->name_add[iFileNameType2].szAddr, '\0', MAX_PATH );       //�����ַ
					pInfoNameAdd->name_add[iFileNameType2].Address = 0;   //ת����ĵ�ַҲ��0(��Ҫ�ǿ��ǲ��ص�APP���������ݲ���)
				}
				memcpy( pInfoNameAdd->name_add[iFileNameType2].szNameFile, FileName[iFileNameType2], strlen(FileName[iFileNameType2]) );
			}
			/* һ��ƥ��(FileNameFlag3ƥ��FileNameFlag4)���жϷ���һ�� */
			if ( -1!=iFileNameType3 )
			{
				iSaveIndex = iFileNameType3;    iCommented = 0;
				{ 
					iAddrGetType = -1; iAddrGetType1 = -1;         //ÿһ�λ�ȡ���ļ���ʱ��Ҫ�������ַ��־λ
					memset( pInfoNameAdd->name_add[iFileNameType3].szNameFile, '\0', MAX_PATH );   //����ļ���
					memset( pInfoNameAdd->name_add[iFileNameType3].szAddr, '\0', MAX_PATH );       //�����ַ
					pInfoNameAdd->name_add[iFileNameType1].Address = 0;   //ת����ĵ�ַҲ��0(��Ҫ�ǿ��ǲ��ص�APP���������ݲ���)
				}
				memcpy( pInfoNameAdd->name_add[iFileNameType3].szNameFile, FileName[iFileNameType3], strlen(FileName[iFileNameType3]) );
			}
			if ( -1==iFileNameType3 && -1!=iFileNameType4  )
			{
				iSaveIndex = iFileNameType4;    iCommented = 1;
				{ 
					iAddrGetType = -1; iAddrGetType1 = -1;          //ÿһ�λ�ȡ���ļ���ʱ��Ҫ�������ַ��־λ
					memset( pInfoNameAdd->name_add[iFileNameType4].szNameFile, '\0', MAX_PATH );   //����ļ���
					memset( pInfoNameAdd->name_add[iFileNameType4].szAddr, '\0', MAX_PATH );       //�����ַ
					pInfoNameAdd->name_add[iFileNameType4].Address = 0;   //ת����ĵ�ַҲ��0(��Ҫ�ǿ��ǲ��ص�APP���������ݲ���)
				}
				memcpy( pInfoNameAdd->name_add[iFileNameType4].szNameFile, FileName[iFileNameType4], strlen(FileName[iFileNameType4]) );
			}
			/* һ��ƥ��(FileNameFlagXƥ��FileNameFlagX)���жϷ���һ��,���ʱ��FileNameFlagX��־������ͬ����� */
			//Alian��Add new Flag(���ϣ�����ɺ���������������Ӷ��ں�������)

			//����ƫ�Ƶ�ַ(ע�͡�����ע��)
			iAddrGetType = VerifyFlagFromArray( AddFlag, pGetDateBuf, VERIFY_ADDRESS );
			
			if ( -1!=iSaveIndex )			//���л�ȡ���ļ������ܿ�ʼȡ��ַ
			{
				//�����ȡ��û��ע�͵ĵ�ַƫ������
				if ( 0==iAddrGetType )
				{
					iAddrGetType1 = 0;
					if ( 0 == iCommented )
					{
						memcpy( pInfoNameAdd->name_add[iSaveIndex].szAddr, pGetDateBuf+DDROFFSET_UNCOMMENT, strlen(pGetDateBuf)-DDROFFSET_UNCOMMENT );
					}
				}
				//��û��ȡ��û��ע�͵ĵ�ַƫ������ʱ����ȡ����ע�͵�ַƫ������
				if ( 0!=iAddrGetType1&&1==iAddrGetType )
				{
					iAddrGetType1 = 1;
					if ( 1 == iCommented )
					{
						memcpy( pInfoNameAdd->name_add[iSaveIndex].szAddr, pGetDateBuf+DDROFFSET_COMMENT, strlen(pGetDateBuf)-DDROFFSET_COMMENT );
					}
				}
			}
			//ÿһ��ʹ���껺��������Ҫ����������������´�ʹ��
			memset( pGetDateBuf, '\0', sizeof(pGetDateBuf) );
		}
		fclose( fp );
		fp = NULL;
		return 1;
	}
}

// ����ѻ���֤���飬�ж������ַ�����ʲô����(��������֤�ļ���)
int CMergeOnboardToRomImageDlg::VerifyFlagFromArray( char v_pVerifyFlag[COL][ROW], char v_pGetDateBuf[LENTH_TITLE], int iFlag  )
{
	int iRes = -1;
	int iCnt = 0;
	if ( VERIFY_NAME == iFlag )
	{
		//�Ͷѻ���ά�������ݽ����ж�
		for( iCnt=0; iCnt<iSumFile; iCnt++ )
		{
			//��Ҫ�жϳ����Ƿ�һ������һ��ֱ�ӾͲ����Ƚ��ж�
			if( strlen(v_pVerifyFlag[iCnt])==(strlen(v_pGetDateBuf)-1) )
			{
				//���նѻ����������֤���쳣�жϵ������Լ�����
				//��Ϊ�Ƕ�windows��txt�ļ����ж�ȡ��ÿһ�ж����ػ��з����Ƚϵ�ʱ��Ҫȥ��,����strlen(v_pGetDateBuf)-1
				if( 0==memcmp( v_pVerifyFlag[iCnt], v_pGetDateBuf, strlen(v_pGetDateBuf)-1 ) )
				{
					iRes = iCnt;
					break;
				}
			}
		}
	} 
	else if ( VERIFY_ADDRESS == iFlag )
	{
		//�Ͷѻ���ά�������ݽ����ж�
		for( iCnt=0; iCnt<iSumFile; iCnt++ )
		{
			//��Ϊ��ַֻȡǰ��10λ��ʶλ���бȽϣ����Բ����������ж�
			//���նѻ����������֤���쳣�жϵ������Լ�����
			//��Ϊ�Ƕ�windows��txt�ļ����ж�ȡ��ÿһ�ж����ػ��з����Ƚϵ�ʱ��Ҫȥ��,ͬʱ��ַֻ�Ƚ�ǰ��ı�־λ������strlen(v_pVerifyFlag[iCnt])-1
			if( 0==memcmp( v_pVerifyFlag[iCnt], v_pGetDateBuf, strlen(v_pVerifyFlag[iCnt])-1 ) )
			{
				iRes = iCnt;
				break;
			}
		}
	}
	return iRes;
}


int CMergeOnboardToRomImageDlg::ConvertAddrAndSequence( P_INFO_NAME_ADD infoNameAdd )
{
	int iRes = -1;
	int iCnt = 0;
	char *p;
	//�ַ���ת��ΪX����  nptrҪת�����ַ�������"0XDEADbeEDA", endptr-endptr��һ��������������������ʱָ�����δ��ʶ��ĵ�һ���ַ�,
	//base-����Ҫת���Ľ���ֵ,��Ҫע���������"0300"->0x300<16����>����300<10����>����ת����
	//long int strtol(const char *nptr,char **endptr,int base);
	for ( iCnt=0; iCnt<iSumFile; iCnt++ )
	{
		infoNameAdd->name_add[iCnt].Address = strtol( infoNameAdd->name_add[iCnt].szAddr, &p, 16 );
	}
	//���յ�ַ�Ӵ�С˳��������������infoNameAdd����ṹ�壬Ϊ����RomImage�ϲ���׼��
	SequenceInfoNameAddStruct( infoNameAdd );

	return iRes;
}


int CMergeOnboardToRomImageDlg::VerifyAddrError( P_INFO_NAME_ADD infoNameAdd )
{
	int iRes = -1;
	bool bHaveError = false;    //�Ƿ��ַ�����־λ
	// ֻ��֤��ַ�Ƿ�ΪNULL�����ֲ���Ҫ
	for ( int iCnt=0; iCnt<iSumFile; iCnt++ )
	{
		if( 0==strlen( infoNameAdd->name_add[iCnt].szAddr ) )
		{
			infoNameAdd->name_add[iCnt].bAddrError = true;
			bHaveError = true;   //ֻҪ��ַ��һ�����󣬱�־λ������������Ҫ��ʾ�û���APP�˳�
		}
		else
		{
			infoNameAdd->name_add[iCnt].bAddrError = false;
		}
		iRes = 0;
	}
	//�е�ַ�����Ҫ��ʾ��û�д���Ͳ�Ҫ����
	if ( bHaveError )
	{
		char szErrorPrompt[200] = {0};
		int  iAddrSet = 0;
		//������Ϣ�ļ�ͷ�ȼӺ�
		sprintf( szErrorPrompt+iAddrSet, RomCodeinf_name, strlen(RomCodeinf_name) );
		iAddrSet += strlen(RomCodeinf_name);
		sprintf( szErrorPrompt+iAddrSet, "�����ļ�:\n", strlen("�����ļ�:\n") );
		iAddrSet += strlen("�����ļ�:\n");
		//����Ǹ���ַû��ֱ����ʾ��APP�˳�
		for ( int iCnt=0; iCnt<iSumFile; iCnt++ )
		{
			//ѭ��������������������Ŀ
			if( infoNameAdd->name_add[iCnt].bAddrError )
			{
				sprintf( szErrorPrompt+iAddrSet, infoNameAdd->name_add[iCnt].szNameFile, strlen(infoNameAdd->name_add[iCnt].szNameFile) );
				iAddrSet += strlen(infoNameAdd->name_add[iCnt].szNameFile);
				sprintf( szErrorPrompt+iAddrSet, "����������;\n", strlen("����������;\n") );
				iAddrSet += strlen("����������;\n");
			}
		}
		AfxMessageBox(_T(szErrorPrompt));
		exit(0);
	}
	return iRes;
}

int CMergeOnboardToRomImageDlg::SequenceInfoNameAddStruct( P_INFO_NAME_ADD infoNameAdd )
{
	int iRes = -1;
	int iCnt = 0, iFind = 0;
	long AddrArray[fn_INVALID] = {0};
	bool bNeedCopy = false;

	//�Ȱ����ε�ַ����ѭ�����������У�������ʹ��
	for ( iCnt=0; iCnt<iSumFile; iCnt++ )
	{
		AddrArray[iCnt] = infoNameAdd->name_add[iCnt].Address;
	}
	//��ȥ��������������
	LongArraySequence( AddrArray, iCnt );
	//��ѭ���ж��費��Ҫ�������򣬲���Ҫ��ֱ���������沽�裬ʡʱ��
	for ( iCnt=0; iCnt<iSumFile; iCnt++ )
	{
		if ( AddrArray[iCnt] != infoNameAdd->name_add[iCnt].Address )
		{
			bNeedCopy = true;     //�κ�һ����ַ��Ҫ���򣬾ͼ�����־λ
		}
		iRes = 0;
	}

	//��Ҫ�������������������������˷�ʱ��
	if ( bNeedCopy )
	{
		INFO_NAME_ADD TempINA;
		//���յ�ַ��С�����˳����������inforNameAdd�ṹ��
		memset( &TempINA, '\0', sizeof(INFO_NAME_ADD) );
		memcpy( &TempINA, infoNameAdd, sizeof(INFO_NAME_ADD) );
		for ( iCnt=0; iCnt<fn_INVALID; iCnt++ )
		{
			for ( iFind=0; iFind<fn_INVALID; iFind++ )
			{
				if ( AddrArray[iCnt] == TempINA.name_add[iFind].Address )
				{
					break;    //�ҵ���Ӧ��ַ�����±��������濽��ʹ��
				}
			}
			//�ҵ���Ӧ�±���п���
			memcpy( &(infoNameAdd->name_add[iCnt]), &(TempINA.name_add[iFind]), sizeof( NAME_ADD ) );
		}
		iRes = 1;
	}
	return iRes;
}

//�м�ȡֵ��
void CMergeOnboardToRomImageDlg::LongArraySequence( long *v_LongArray, long Len ) 
{ 
	long iCnt1,iCnt2,iSpace,iRes; 
	iCnt1 = iCnt2 = iRes = 0;
	iSpace = Len/2;          //���ֵ
	while( iSpace>=1 ) 
	{ 
		for( iCnt1=iSpace; iCnt1<Len; iCnt1++ ) 
		{ 
			iRes = v_LongArray[iCnt1]; 
			iCnt2 = iCnt1 - iSpace; 
			while( iCnt2>=0 && iRes<v_LongArray[iCnt2] ) 
			{ 
				v_LongArray[iCnt2+iSpace] = v_LongArray[iCnt2]; 
				iCnt2 -= iSpace; 
			} 
			v_LongArray[iCnt2+iSpace] = iRes; 
		} 
		iSpace/=2;           //��С���ֵ
	} 
}

//��RomCode.inf�ļ���ȡ����infoNameAdd��Ϣ�����ж������˵�����ѡ��оƬ�Ƿ�������
//������ʾ ���1.�����˵�оƬѡ��   ���2.���ֵ��ַ�����ļ���С�Ѿ�����оƬ������С
bool CMergeOnboardToRomImageDlg::VerifyRomImageSize( P_INFO_NAME_ADD infoNameAdd )
{
	//��������˵���ͬʱ�����֤������С����  С��
	int FileSize;
	CString str;

	FileSize = (infoNameAdd->name_add[iSumFile-1].Address + infoNameAdd->name_add[iSumFile-1].lSizeFile)/1024/1024;
	//FileSize = 200;
	str.Format(_T("��ǰ�ļ���СΪ%dM,����оƬ������������ѡ��"),FileSize);
	
	//����Ƿ񳬳���һ����ַ��Χ
	for (int i=0; i<iSumFile-1; i++)
	{
		int fileAddress = infoNameAdd->name_add[i].Address;
		int fileISize = infoNameAdd->name_add[i].lSizeFile;
		int fileNextAddress = infoNameAdd->name_add[i+1].Address;

		if (fileAddress + fileISize > fileNextAddress)
		{
			CString strFileName;
			strFileName.Format(_T("%sƫ�Ƶ�ַ�����������ٺϲ���"),infoNameAdd->name_add[i].szNameFile);
			AfxMessageBox(strFileName);
			return FALSE;
		}
	}
	
	//��֤�Ƿ񳬳�оƬ��С
	if (nIndex == 0)
	{
		if (FileSize > 128)
		{			
			AfxMessageBox(str);
			return FALSE;
		}
		else
			return TRUE;
	}
	else if (nIndex == 1)
	{
		if (FileSize > 256)
		{
			AfxMessageBox(str);
			return FALSE;
		}
		else
			return TRUE;
	}
	else if (nIndex == 2)
	{
		if (FileSize > 512)
		{
			AfxMessageBox(str);
			return FALSE;
		}
		else
			return TRUE;
	}
	//AfxMessageBox(_T("��ʾ��Ϣ�������Ҫ�Ļ�"));
}

//�ϲ�RomImage�ļ�
int CMergeOnboardToRomImageDlg::MergeImageFile( P_INFO_NAME_ADD infoNameAdd )
{
	//�ϲ�bin�ļ����̣�ͨ��infoNameAdd�����ļ�����ѭ��д��ResultFile.bin�ļ���λ�þͷ��ڶ�Ӧ�ļ��е���
	FILE *fp_merge= NULL;
	char pBin[MAX_PATH] = {0};
	byte *pMergeData = NULL;
	long lCnt = 0, lPos = 0;
	int  iWriteLen = 0;
	long l0XFF_Len = 0;
	//���ɲ��򿪺ϲ�����ļ�
	memset( pBin, '\0', sizeof(pBin) );
	sprintf( pBin, "%s", szPath );
	sprintf( pBin+iLenOnboardPath, "\\" );
	sprintf( pBin+iLenOnboardPath+1, "%s", MergeRes_name );
	fp_merge = fopen( pBin, "wb" );
	if( fp_merge == NULL ) 
	{
		AfxMessageBox(_T("�޷��������ResultFile.bin�ļ�"));
		return -1;
	}
	//ѭ����ȡ���ļ�
	for ( int iCnt=0; iCnt<iSumFile; iCnt++ )
	{
		//����infoNameAdd��Ӧ�ĳ����������ÿռ�
		pMergeData = (byte *)malloc( infoNameAdd->name_add[iCnt].lSizeFile*sizeof(char) );
		memset( pMergeData, '\0', infoNameAdd->name_add[iCnt].lSizeFile*sizeof(char) );
		//��ȡ��Ӧ�ļ�������
		GetMergeFileData( pMergeData, iCnt, infoNameAdd );

		//1.д��ResultFile.bin�ļ�
		while ( lCnt<infoNameAdd->name_add[iCnt].lSizeFile )
		{
			iWriteLen = fwrite( pMergeData+lCnt, 1, 1, fp_merge );
			if ( 1==iWriteLen )
			{
				lCnt += 1;
				SetProgressPos( lPos++ );
			}
		}
		//���껺���ַ��ֱ���ͷŵ�ַ
		free( pMergeData ); pMergeData = NULL; lCnt = 0;

		//2.����һ���ļ�ƫ�Ƶ�ַ֮ǰ���0xFF����
		if ( (iSumFile-1)>iCnt )
		{
			l0XFF_Len = (infoNameAdd->name_add[iCnt+1].Address-infoNameAdd->name_add[iCnt].Address) - infoNameAdd->name_add[iCnt].lSizeFile;
		} 
		else
		{
			l0XFF_Len = (SizeRomImageContain[nIndex]-infoNameAdd->name_add[iCnt].Address) - infoNameAdd->name_add[iCnt].lSizeFile;
		}
		pMergeData = (byte *)malloc( l0XFF_Len* sizeof(char) );
		memset( pMergeData, 0xFF, l0XFF_Len );
		while ( lCnt<l0XFF_Len )
		{
			iWriteLen = fwrite( pMergeData+lCnt, 1, 1, fp_merge );
			if ( 1==iWriteLen )
			{
				lCnt += 1;
				SetProgressPos( lPos++ );
			}
		}
		//���껺���ַ��ֱ���ͷŵ�ַ
		free( pMergeData ); pMergeData = NULL; lCnt = 0;
	}
	fclose(fp_merge);
	fp_merge = NULL;
	return 0;
}


long CMergeOnboardToRomImageDlg::GetMergeFileData( byte *FileData, int Index, P_INFO_NAME_ADD infoNameAdd )
{
	long lRes = 0;
	FILE *fp= NULL;
	char pFile[MAX_PATH] = {0};
	memset( pFile, '\0', sizeof(pFile) );
	sprintf( pFile, "%s", szPath );
	sprintf( pFile+iLenOnboardPath, "\\" );
	sprintf( pFile+iLenOnboardPath+1, "%s", infoNameAdd->name_add[Index].szNameFile );
	//ѭ����ȡ�ļ�
	fp = fopen( pFile, "rb" );
	if( fp == NULL ) 
	{
		//��Ҫ�����Ѵ���
		lRes = -1;
	}
	//����ʵ������ֱ����ȡ�ļ�����
	char cGetChar;
	fread( FileData, infoNameAdd->name_add[Index].lSizeFile, 1, fp );
	fclose( fp );
	fp = NULL;
	return lRes;
}


void CMergeOnboardToRomImageDlg::SetProgressPos( long lPos )
{
	static int rank = 1;                                //   20    -      4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
	long lRankStep = (SizeRomImageContain[nIndex]*10)/(PROGRESSPOS_END-PROGRESSPOS_DEAL);
	if ( lPos > lRankStep*rank )
	{
		//�������ȶ�λ
		m_Pro->SetPos( PROGRESSPOS_DEAL+(rank*10) );
		rank++;
		if ( PROGRESSPOS_END-PROGRESSPOS_DEAL < rank*10 )
		{
			rank = 1;
		}
	}
}