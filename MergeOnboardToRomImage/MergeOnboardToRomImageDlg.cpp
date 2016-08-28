
// MergeOnboardToRomImageDlg.cpp : 实现文件
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

//导入验证堆积二维数组内容(没注释)
char FileNameFlag1[COL][ROW] = {
									"ExecuteFile=\"u-boot.spi-boot\"",     //u-boot.spi-boot—>0
									"File=\"uuImage.lzo\"",                //uuImage.lzo—>1
									"File=\"root.squashfs.lzo\"",          //root.squashfs.lzo—>2
									"File=\"rw.jffs2\"",                   //rw.jffs2—>3
									"File=\"rw2.jffs2\"",                  //rw2.jffs2—>4
									"File=\"rw3.jffs2\""                   //rw3.jffs2—>5
                                  };
//导入验证堆积二维数组内容(有注释)
char FileNameFlag2[COL][ROW] = {
									";ExecuteFile=\"u-boot.spi-boot\"",     //u-boot.spi-boot—>10
									";File=\"uuImage.lzo\"",                //uuImage.lzo—>11
									";File=\"root.squashfs.lzo\"",          //root.squashfs.lzo—>12
									";File=\"rw.jffs2\"",                   //rw.jffs2—>13
									";File=\"rw2.jffs2\"",                  //rw2.jffs2—>14
									";File=\"rw3.jffs2\""                   //rw3.jffs2—>5
								 };
//导入验证堆积二维数组内容(没注释)
char FileNameFlag3[COL][ROW] = {
									"File=\"u-boot.spi-boot\"",             //u-boot.spi-boot—>0
									"File=\"uuImage.lzo\"",                 //uuImage.lzo—>1
									"File=\"root.squashfs.lzo\"",           //root.squashfs.lzo—>2
									"File=\"rw.jffs2\"",                    //rw.jffs2—>3
									"File=\"rw2.jffs2\"",                   //rw2.jffs2—>4
									"File=\"rw3.jffs2\""                    //rw3.jffs2—>5
								};
//导入验证堆积二维数组内容(有注释)
char FileNameFlag4[COL][ROW] = {
									";File=\"u-boot.spi-boot\"",            //u-boot.spi-boot—>10
									";File=\"uuImage.lzo\"",                //uuImage.lzo—>11
									";File=\"root.squashfs.lzo\"",          //root.squashfs.lzo—>12
									";File=\"rw.jffs2\"",                   //rw.jffs2—>13
									";File=\"rw2.jffs2\"",                 //rw2.jffs2—>14
									";File=\"rw3.jffs2\""                   //rw3.jffs2—>5
								};
//导入验证堆积二维数组内容(要和上面的文件名对应)
char FileName[COL][ROW] =     {
									"u-boot.spi-boot",                      //u-boot.spi-boot—>0
									"uuImage.lzo",                          //uuImage.lzo—>1
									"root.squashfs.lzo",                    //root.squashfs.lzo—>2
									"rw.jffs2",                             //rw.jffs2—>3
									"rw2.jffs2",                            //rw2.jffs2—>4
									"rw3.jffs2"                             //rw3.jffs2—>5
								};

char AddFlag[COL][ROW]   =   {
								    "DDROFFSET=0x",
								    ";DDROFFSET=0x"
							   };

char *MergeRes_name = "ResultFile.bin";

long SizeRomImageContain[10] = {
									0x01000000,                   //对应下拉菜单的第一个芯片 MX25L12835 容量，对应下标 m_RomSizeCombo.InsertString(0,_T("MX25L12835"));
									0x02000000,                   //对应下拉菜单的第一个芯片 MX25L25635 容量，对应下标 m_RomSizeCombo.InsertString(1,_T("MX25L25635"));
									0x04000000,                   //对应下拉菜单的第一个芯片 MX25L51235 容量，对应下标 m_RomSizeCombo.InsertString(2,_T("MX66L51235"));
							    };

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMergeOnboardToRomImageDlg 对话框


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


// CMergeOnboardToRomImageDlg 消息处理程序

BOOL CMergeOnboardToRomImageDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	//RomSize下拉菜单初始化
	m_RomSizeCombo.InsertString(0,_T("MX25L12835"));
	m_RomSizeCombo.InsertString(1,_T("MX25L25635"));
	m_RomSizeCombo.InsertString(2,_T("MX66L51235"));

	iLenOnboardPath = 0;   iSumFile = 0;
	memset( szPath, 0x00, MAX_PATH );
	memset( &infoNameAdd, '\0', sizeof(infoNameAdd) );
	m_Pro=(CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);

	//如果堆积行号COL小于类型数fn_INVALID就异常，提示退出
	if ( COL < fn_INVALID )
	{
		AfxMessageBox(_T("COL < fn_INVALID error!"));
		exit(0);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMergeOnboardToRomImageDlg::OnPaint()
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
	//错误信息文件头先加好
	sprintf( szErrorPrompt+iAddrSet, "缺少以下文件:\n", strlen("缺少以下文件:\n") );
	iAddrSet += strlen("缺少以下文件:\n");
	for ( int iCnt=0; iCnt<iSumFile; iCnt++ )
	{
		memset( pFile, '\0', sizeof(pFile) );   lSizeFile = 0;
		sprintf( pFile, "%s", szPath );
		sprintf( pFile+iLenOnboardPath, "\\" );
		sprintf( pFile+iLenOnboardPath+1, "%s", FileName[iCnt] );
		//循环读取文件
		fp = fopen( pFile, "rb" );
		if( fp == NULL ) 
		{
			iRes = 1;
			sprintf( szErrorPrompt+iAddrSet, FileName[iCnt], strlen(FileName[iCnt]) );
			iAddrSet += strlen(FileName[iCnt]);
			sprintf( szErrorPrompt+iAddrSet, ";\n", strlen(";\n") );
			iAddrSet += strlen(";\n");
			continue;     //打不开文件，继续下一个文件读写
		}
		while( cGetChar = getc( fp ) != EOF )
		{
			lSizeFile++ ;
		}
		//读取完文件，存储文件大小
		infoNameAdd->name_add[iCnt].lSizeFile = lSizeFile;
		fclose( fp );
		fp = NULL;
	}
	//缺什么文件就提示出来
	if( 1==iRes )
	{
		AfxMessageBox(_T(szErrorPrompt));
	}
	return iRes;
}


void CMergeOnboardToRomImageDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码 
	CString str;
	memset(szPath, '\0', sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "请选择Onboard文件目录：";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框
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
	//每次点击转化按钮都清除计算值，避免堆积
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
		;//Alian:待后续还有其他需要合并的文件时扩展
	}
	//设置进度条长度、每一步长度
	m_Pro->SetRange( PROGRESSPOS_START, PROGRESSPOS_END );
	m_Pro->SetPos( PROGRESSPOS_START );
	//m_Pro->SetStep(1);
	// TODO: 在此添加控件通知处理程序代码
	// 先找有没有RomCode.inf文件
	char Path_RomCodeInf[MAX_PATH] = {0};
	memset( Path_RomCodeInf, '\0', sizeof(Path_RomCodeInf) );
	sprintf( Path_RomCodeInf, "%s", szPath );
	sprintf( Path_RomCodeInf+iLenOnboardPath, "\\" );
	sprintf( Path_RomCodeInf+iLenOnboardPath+1, "%s", RomCodeinf_name );
	if ( 0 == access(Path_RomCodeInf,0) )
	{
		//先读取各文件实际大小到infoNameAdd结构体中
		GetMergeFileSize( &infoNameAdd );
		m_Pro->SetPos( PROGRESSPOS_DEAL/2 );
		//从AdjData.inf文件中获取到要合并的文件信息(地址和名字)
		GetInfromatinFromRomImageFile( Path_RomCodeInf, &infoNameAdd );
		//先验证地址有没有，没有就提示错误
		VerifyAddrError( &infoNameAdd );
		//重新按照地址从小到大顺序排序
		ConvertAddrAndSequence( &infoNameAdd );
		//通过地址上判断数据是不是超过RomImage缓存器大小，大于跳出提示，APP退出
		if (!VerifyRomImageSize( &infoNameAdd ))
		{
			return;
		}
		m_Pro->SetPos( PROGRESSPOS_DEAL );
		//合并RomImage文件
		MergeImageFile( &infoNameAdd );
		m_Pro->SetPos( PROGRESSPOS_END );
		//合并完成提示
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
	int  iFileNameType1 = -1;     //获取到文件名没注释标志位
	int  iFileNameType2 = -1;     //获取到文件名有注释标志位
	int  iFileNameType3 = -1;     //获取到文件名没注释标志位
	int  iFileNameType4 = -1;     //获取到文件名有注释标志位
	int  iAddrGetType1 = -1;      //获取到偏移地址没注释标志位
	int  iAddrGetType2 = -1;      //获取到偏移地址有注释标志位
	int  iAddrGetType = -1;
	int  iSaveIndex = -1;
	int  iCommented = -1;         //未注释为0，注释为1

	fp = fopen( Path, "a+" );
	if( fp == NULL )    //RomCode.inf 文件打开失败
	{
		AfxMessageBox(_T("Open RomCode.inf file fail!"));
		return 0;
	}
	else       //RomCode.inf 文件打开成功
	{
		//读到文件结束符(到达EOF就结束)
		while( !feof(fp) )
		{
			//从文件中读一行字符串
			fgets( pGetDateBuf, LENTH_TITLE, fp );

			//处理文件名(注释、不带注释)
			iFileNameType1 = VerifyFlagFromArray( FileNameFlag1, pGetDateBuf, VERIFY_NAME );
			iFileNameType2 = VerifyFlagFromArray( FileNameFlag2, pGetDateBuf, VERIFY_NAME );
			iFileNameType3 = VerifyFlagFromArray( FileNameFlag3, pGetDateBuf, VERIFY_NAME );
			iFileNameType4 = VerifyFlagFromArray( FileNameFlag4, pGetDateBuf, VERIFY_NAME );
			//遍历每一行开始缓存数据
			/* 一组匹配(FileNameFlag1匹配FileNameFlag2)的判断放在一起 */
			if ( -1!=iFileNameType1 )
			{
				iSaveIndex = iFileNameType1;    iCommented = 0;
				{ 
				  iAddrGetType = -1; iAddrGetType1 = -1;         //每一次获取到文件名时都要先清除地址标志位
				  memset( pInfoNameAdd->name_add[iFileNameType1].szNameFile, '\0', MAX_PATH );   //清除文件名
				  memset( pInfoNameAdd->name_add[iFileNameType1].szAddr, '\0', MAX_PATH );       //清除地址
				  pInfoNameAdd->name_add[iFileNameType1].Address = 0;   //转化后的地址也清0(主要是考虑不关掉APP后怕有数据残留)
				}
				memcpy( pInfoNameAdd->name_add[iFileNameType1].szNameFile, FileName[iFileNameType1], strlen(FileName[iFileNameType1]) );
			}
			if ( -1==iFileNameType1 && -1!=iFileNameType2  )
			{
				iSaveIndex = iFileNameType2;    iCommented = 1;
				{ 
					iAddrGetType = -1; iAddrGetType1 = -1;          //每一次获取到文件名时都要先清除地址标志位
					memset( pInfoNameAdd->name_add[iFileNameType2].szNameFile, '\0', MAX_PATH );   //清除文件名
					memset( pInfoNameAdd->name_add[iFileNameType2].szAddr, '\0', MAX_PATH );       //清除地址
					pInfoNameAdd->name_add[iFileNameType2].Address = 0;   //转化后的地址也清0(主要是考虑不关掉APP后怕有数据残留)
				}
				memcpy( pInfoNameAdd->name_add[iFileNameType2].szNameFile, FileName[iFileNameType2], strlen(FileName[iFileNameType2]) );
			}
			/* 一组匹配(FileNameFlag3匹配FileNameFlag4)的判断放在一起 */
			if ( -1!=iFileNameType3 )
			{
				iSaveIndex = iFileNameType3;    iCommented = 0;
				{ 
					iAddrGetType = -1; iAddrGetType1 = -1;         //每一次获取到文件名时都要先清除地址标志位
					memset( pInfoNameAdd->name_add[iFileNameType3].szNameFile, '\0', MAX_PATH );   //清除文件名
					memset( pInfoNameAdd->name_add[iFileNameType3].szAddr, '\0', MAX_PATH );       //清除地址
					pInfoNameAdd->name_add[iFileNameType1].Address = 0;   //转化后的地址也清0(主要是考虑不关掉APP后怕有数据残留)
				}
				memcpy( pInfoNameAdd->name_add[iFileNameType3].szNameFile, FileName[iFileNameType3], strlen(FileName[iFileNameType3]) );
			}
			if ( -1==iFileNameType3 && -1!=iFileNameType4  )
			{
				iSaveIndex = iFileNameType4;    iCommented = 1;
				{ 
					iAddrGetType = -1; iAddrGetType1 = -1;          //每一次获取到文件名时都要先清除地址标志位
					memset( pInfoNameAdd->name_add[iFileNameType4].szNameFile, '\0', MAX_PATH );   //清除文件名
					memset( pInfoNameAdd->name_add[iFileNameType4].szAddr, '\0', MAX_PATH );       //清除地址
					pInfoNameAdd->name_add[iFileNameType4].Address = 0;   //转化后的地址也清0(主要是考虑不关掉APP后怕有数据残留)
				}
				memcpy( pInfoNameAdd->name_add[iFileNameType4].szNameFile, FileName[iFileNameType4], strlen(FileName[iFileNameType4]) );
			}
			/* 一组匹配(FileNameFlagX匹配FileNameFlagX)的判断放在一起,添加时和FileNameFlagX标志符数组同步添加 */
			//Alian：Add new Flag(这个希望做成函数，后续代码添加都在函数里面)

			//处理偏移地址(注释、不带注释)
			iAddrGetType = VerifyFlagFromArray( AddFlag, pGetDateBuf, VERIFY_ADDRESS );
			
			if ( -1!=iSaveIndex )			//得有获取到文件名才能开始取地址
			{
				//如果获取到没有注释的地址偏移数据
				if ( 0==iAddrGetType )
				{
					iAddrGetType1 = 0;
					if ( 0 == iCommented )
					{
						memcpy( pInfoNameAdd->name_add[iSaveIndex].szAddr, pGetDateBuf+DDROFFSET_UNCOMMENT, strlen(pGetDateBuf)-DDROFFSET_UNCOMMENT );
					}
				}
				//在没获取到没有注释的地址偏移数据时，获取到有注释地址偏移数据
				if ( 0!=iAddrGetType1&&1==iAddrGetType )
				{
					iAddrGetType1 = 1;
					if ( 1 == iCommented )
					{
						memcpy( pInfoNameAdd->name_add[iSaveIndex].szAddr, pGetDateBuf+DDROFFSET_COMMENT, strlen(pGetDateBuf)-DDROFFSET_COMMENT );
					}
				}
			}
			//每一次使用完缓存区，需要重新清除缓存留待下次使用
			memset( pGetDateBuf, '\0', sizeof(pGetDateBuf) );
		}
		fclose( fp );
		fp = NULL;
		return 1;
	}
}

// 传入堆积验证数组，判断这条字符串是什么类型(本函数验证文件名)
int CMergeOnboardToRomImageDlg::VerifyFlagFromArray( char v_pVerifyFlag[COL][ROW], char v_pGetDateBuf[LENTH_TITLE], int iFlag  )
{
	int iRes = -1;
	int iCnt = 0;
	if ( VERIFY_NAME == iFlag )
	{
		//和堆积二维数组内容进行判断
		for( iCnt=0; iCnt<iSumFile; iCnt++ )
		{
			//想要判断长度是否一样，不一样直接就不做比较判断
			if( strlen(v_pVerifyFlag[iCnt])==(strlen(v_pGetDateBuf)-1) )
			{
				//按照堆积数组进行验证，异常判断调用者自己处理
				//因为是对windows的txt文件进行读取，每一行都隐藏换行符，比较的时候要去掉,所以strlen(v_pGetDateBuf)-1
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
		//和堆积二维数组内容进行判断
		for( iCnt=0; iCnt<iSumFile; iCnt++ )
		{
			//因为地址只取前面10位标识位进行比较，所以不用做长度判断
			//按照堆积数组进行验证，异常判断调用者自己处理
			//因为是对windows的txt文件进行读取，每一行都隐藏换行符，比较的时候要去掉,同时地址只比较前面的标志位，所以strlen(v_pVerifyFlag[iCnt])-1
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
	//字符串转化为X进制  nptr要转化的字符串例如"0XDEADbeEDA", endptr-endptr是一个传出参数，函数返回时指向后面未被识别的第一个字符,
	//base-代表要转化的进制值,需要注意的是它是"0300"->0x300<16进制>或者300<10进制>这样转化的
	//long int strtol(const char *nptr,char **endptr,int base);
	for ( iCnt=0; iCnt<iSumFile; iCnt++ )
	{
		infoNameAdd->name_add[iCnt].Address = strtol( infoNameAdd->name_add[iCnt].szAddr, &p, 16 );
	}
	//按照地址从大到小顺序排序，重新整理infoNameAdd管理结构体，为后面RomImage合并做准备
	SequenceInfoNameAddStruct( infoNameAdd );

	return iRes;
}


int CMergeOnboardToRomImageDlg::VerifyAddrError( P_INFO_NAME_ADD infoNameAdd )
{
	int iRes = -1;
	bool bHaveError = false;    //是否地址有误标志位
	// 只验证地址是否为NULL，名字不用要
	for ( int iCnt=0; iCnt<iSumFile; iCnt++ )
	{
		if( 0==strlen( infoNameAdd->name_add[iCnt].szAddr ) )
		{
			infoNameAdd->name_add[iCnt].bAddrError = true;
			bHaveError = true;   //只要地址有一个错误，标志位都被激发，需要提示用户后APP退出
		}
		else
		{
			infoNameAdd->name_add[iCnt].bAddrError = false;
		}
		iRes = 0;
	}
	//有地址错误才要提示，没有错误就不要做了
	if ( bHaveError )
	{
		char szErrorPrompt[200] = {0};
		int  iAddrSet = 0;
		//错误信息文件头先加好
		sprintf( szErrorPrompt+iAddrSet, RomCodeinf_name, strlen(RomCodeinf_name) );
		iAddrSet += strlen(RomCodeinf_name);
		sprintf( szErrorPrompt+iAddrSet, "配置文件:\n", strlen("配置文件:\n") );
		iAddrSet += strlen("配置文件:\n");
		//如果那个地址没有直接提示，APP退出
		for ( int iCnt=0; iCnt<iSumFile; iCnt++ )
		{
			//循环加入个设置有问题的项目
			if( infoNameAdd->name_add[iCnt].bAddrError )
			{
				sprintf( szErrorPrompt+iAddrSet, infoNameAdd->name_add[iCnt].szNameFile, strlen(infoNameAdd->name_add[iCnt].szNameFile) );
				iAddrSet += strlen(infoNameAdd->name_add[iCnt].szNameFile);
				sprintf( szErrorPrompt+iAddrSet, "设置有问题;\n", strlen("设置有问题;\n") );
				iAddrSet += strlen("设置有问题;\n");
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

	//先把整形地址数组循环存入数组中，待排序使用
	for ( iCnt=0; iCnt<iSumFile; iCnt++ )
	{
		AddrArray[iCnt] = infoNameAdd->name_add[iCnt].Address;
	}
	//传去排序函数进行排序
	LongArraySequence( AddrArray, iCnt );
	//先循环判断需不需要重新排序，不需要就直接跳过后面步骤，省时间
	for ( iCnt=0; iCnt<iSumFile; iCnt++ )
	{
		if ( AddrArray[iCnt] != infoNameAdd->name_add[iCnt].Address )
		{
			bNeedCopy = true;     //任何一个地址需要排序，就激发标志位
		}
		iRes = 0;
	}

	//需要重新排序才做拷贝，否则就是浪费时间
	if ( bNeedCopy )
	{
		INFO_NAME_ADD TempINA;
		//按照地址从小到大的顺序重新排序inforNameAdd结构体
		memset( &TempINA, '\0', sizeof(INFO_NAME_ADD) );
		memcpy( &TempINA, infoNameAdd, sizeof(INFO_NAME_ADD) );
		for ( iCnt=0; iCnt<fn_INVALID; iCnt++ )
		{
			for ( iFind=0; iFind<fn_INVALID; iFind++ )
			{
				if ( AddrArray[iCnt] == TempINA.name_add[iFind].Address )
				{
					break;    //找到对应地址的新下表，留给后面拷贝使用
				}
			}
			//找到对应下标进行拷贝
			memcpy( &(infoNameAdd->name_add[iCnt]), &(TempINA.name_add[iFind]), sizeof( NAME_ADD ) );
		}
		iRes = 1;
	}
	return iRes;
}

//中间取值法
void CMergeOnboardToRomImageDlg::LongArraySequence( long *v_LongArray, long Len ) 
{ 
	long iCnt1,iCnt2,iSpace,iRes; 
	iCnt1 = iCnt2 = iRes = 0;
	iSpace = Len/2;          //间距值
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
		iSpace/=2;           //缩小间距值
	} 
}

//从RomCode.inf文件读取到的infoNameAdd信息，来判断下拉菜单中所选的芯片是否容量够
//错误提示 情况1.下拉菜单芯片选错   情况2.最大值地址加上文件大小已经超出芯片容器大小
bool CMergeOnboardToRomImageDlg::VerifyRomImageSize( P_INFO_NAME_ADD infoNameAdd )
{
	//添加下拉菜单，同时添加验证容器大小代码  小洲
	int FileSize;
	CString str;

	FileSize = (infoNameAdd->name_add[iSumFile-1].Address + infoNameAdd->name_add[iSumFile-1].lSizeFile)/1024/1024;
	//FileSize = 200;
	str.Format(_T("当前文件大小为%dM,超过芯片容量！请重新选择！"),FileSize);
	
	//检查是否超出下一个地址范围
	for (int i=0; i<iSumFile-1; i++)
	{
		int fileAddress = infoNameAdd->name_add[i].Address;
		int fileISize = infoNameAdd->name_add[i].lSizeFile;
		int fileNextAddress = infoNameAdd->name_add[i+1].Address;

		if (fileAddress + fileISize > fileNextAddress)
		{
			CString strFileName;
			strFileName.Format(_T("%s偏移地址错误，请查验后再合并！"),infoNameAdd->name_add[i].szNameFile);
			AfxMessageBox(strFileName);
			return FALSE;
		}
	}
	
	//验证是否超出芯片大小
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
	//AfxMessageBox(_T("提示信息，如果需要的话"));
}

//合并RomImage文件
int CMergeOnboardToRomImageDlg::MergeImageFile( P_INFO_NAME_ADD infoNameAdd )
{
	//合并bin文件过程，通过infoNameAdd将各文件数据循环写入ResultFile.bin文件，位置就放在对应文件夹底下
	FILE *fp_merge= NULL;
	char pBin[MAX_PATH] = {0};
	byte *pMergeData = NULL;
	long lCnt = 0, lPos = 0;
	int  iWriteLen = 0;
	long l0XFF_Len = 0;
	//生成并打开合并完的文件
	memset( pBin, '\0', sizeof(pBin) );
	sprintf( pBin, "%s", szPath );
	sprintf( pBin+iLenOnboardPath, "\\" );
	sprintf( pBin+iLenOnboardPath+1, "%s", MergeRes_name );
	fp_merge = fopen( pBin, "wb" );
	if( fp_merge == NULL ) 
	{
		AfxMessageBox(_T("无法创建或打开ResultFile.bin文件"));
		return -1;
	}
	//循环提取各文件
	for ( int iCnt=0; iCnt<iSumFile; iCnt++ )
	{
		//按照infoNameAdd对应的长度申请暂用空间
		pMergeData = (byte *)malloc( infoNameAdd->name_add[iCnt].lSizeFile*sizeof(char) );
		memset( pMergeData, '\0', infoNameAdd->name_add[iCnt].lSizeFile*sizeof(char) );
		//提取对应文件名数据
		GetMergeFileData( pMergeData, iCnt, infoNameAdd );

		//1.写入ResultFile.bin文件
		while ( lCnt<infoNameAdd->name_add[iCnt].lSizeFile )
		{
			iWriteLen = fwrite( pMergeData+lCnt, 1, 1, fp_merge );
			if ( 1==iWriteLen )
			{
				lCnt += 1;
				SetProgressPos( lPos++ );
			}
		}
		//用完缓冲地址，直接释放地址
		free( pMergeData ); pMergeData = NULL; lCnt = 0;

		//2.到下一个文件偏移地址之前填充0xFF数据
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
		//用完缓冲地址，直接释放地址
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
	//循环读取文件
	fp = fopen( pFile, "rb" );
	if( fp == NULL ) 
	{
		//需要做提醒处理
		lRes = -1;
	}
	//按照实际内容直接提取文件数据
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
		//进度条先定位
		m_Pro->SetPos( PROGRESSPOS_DEAL+(rank*10) );
		rank++;
		if ( PROGRESSPOS_END-PROGRESSPOS_DEAL < rank*10 )
		{
			rank = 1;
		}
	}
}