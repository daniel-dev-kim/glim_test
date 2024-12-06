
// MFCStartDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCStart.h"
#include "MFCStartDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CMFCStartDlg dialog



CMFCStartDlg::CMFCStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSTART_DIALOG, pParent)
	, m_x1(0)
	, m_y1(0)
	, m_x2(0)
	, m_y2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, m_x1);
	DDX_Text(pDX, IDC_EDIT_Y1, m_y1);
	DDX_Text(pDX, IDC_EDIT_X2, m_x2);
	DDX_Text(pDX, IDC_EDIT_Y2, m_y2);
}

BEGIN_MESSAGE_MAP(CMFCStartDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CMFCStartDlg::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_ACTION, &CMFCStartDlg::OnBnClickedButtonAction)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMFCStartDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CMFCStartDlg message handlers

BOOL CMFCStartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CreateDirectory(_T("image"), NULL);
	CRect rect;
	GetClientRect(&rect);

	m_nImageWidth = static_cast<int>(rect.Width() * 0.6);
	m_nImageHeight = static_cast<int>(rect.Height() * 0.8);
	m_nImageStart = static_cast<int>(rect.Height() * 0.1);

	m_radius = rand() % 30 + 10;
	m_color = rand() % 200;


	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCStartDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCStartDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCStartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCStartDlg::OnBnClickedButtonDraw()
{
	UpdateData(TRUE);
	m_image.Create(m_nImageWidth, -m_nImageHeight, 8);

	static RGBQUAD rgb[256];
	for (int i = 0; i < 256; i++)
	{
		rgb[i].rgbBlue = rgb[i].rgbGreen = rgb[i].rgbRed = i;
	}
	m_image.SetColorTable(0, 256, rgb);

	int pitch = m_image.GetPitch();

	unsigned char* fm = reinterpret_cast<unsigned char*>(m_image.GetBits());
	memset(fm, 0xFF, abs(pitch) * m_nImageHeight);

	m_radius = rand() % CIRCLE_SIZE_DELTA + BASE_CIRCLE_SIZE;
	m_color = rand() % CIRCLE_COLOR_MAX;

	drawCircle(fm, m_x1, m_y1, m_radius, m_color);

	CClientDC dc(this);
	m_image.Draw(dc, m_nImageStart, m_nImageStart);

	m_image.Destroy();
}

void CMFCStartDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, unsigned char color)
{

    int nCenterX = x + nRadius;
    int nCenterY = y + nRadius;
    int nPitch = m_image.GetPitch();

    int nWidth = nRadius * 2;
    int nHeight = nRadius * 2;

    for (int i = y; i < y + nHeight; i++) {
        for (int j = x; j < x + nWidth; j++) {
            int dx = j - nCenterX;
            int dy = i - nCenterY;
            if (dx * dx + dy * dy <= nRadius * nRadius) {
                fm[i * nPitch + j] = color;
            }
        }
    }
}


void CMFCStartDlg::OnBnClickedButtonAction()
{
	UpdateData(TRUE);
	int startX = m_x1;
	int startY = m_y1;

	int numOfPic = 32;
	int deltaX = (m_x2 - m_x1) / numOfPic;
	int deltaY = (m_y2 - m_y1) / numOfPic;

	static RGBQUAD rgb[256];
	for (int i = 0; i < 256; i++)
	{
		rgb[i].rgbBlue = rgb[i].rgbGreen = rgb[i].rgbRed = i;
	}


	for (int step = 0; step <= numOfPic; step++) {
		m_image.Create(m_nImageWidth, -m_nImageHeight, 8);
		m_image.SetColorTable(0, 256, rgb);

		int pitch = m_image.GetPitch();
		unsigned char* fm = reinterpret_cast<unsigned char*>(m_image.GetBits());
		memset(fm, 0xFF, abs(pitch) * m_nImageHeight);

		int currentX = startX + deltaX * step;
		int currentY = startY + deltaY * step;
		drawCircle(fm, currentX, currentY, m_radius, m_color);

		CString fileName;
		fileName.Format(_T(".\\image\\frame_%03d.bmp"), step);
		m_image.Save(fileName, Gdiplus::ImageFormatBMP);

		CClientDC dc(this);
		m_image.Draw(dc, m_nImageStart, m_nImageStart);

		m_image.Destroy();

		Sleep(50);
	}
}



void CMFCStartDlg::OnBnClickedButtonOpen()
{
	CFileDialog fileDlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST,
		_T("Image Files (*.bmp;*.jpg;*.jpeg)|*.bmp;*.jpg;*.jpeg|All Files (*.*)|*.*||"));
	CString filePath;
	if (fileDlg.DoModal() == IDOK) filePath = fileDlg.GetPathName();
	else return;

	m_image.Load(filePath);

	int centerX = 0, centerY = 0;
	findCircleCenter(centerX, centerY);

	CClientDC dc(this);
	m_image.Draw(dc, m_nImageStart, m_nImageStart);

	int adjustedCenterX = m_nImageStart + centerX;
	int adjustedCenterY = m_nImageStart + centerY;
	dc.MoveTo(adjustedCenterX - X_SIGN_SIZE, adjustedCenterY - X_SIGN_SIZE);
	dc.LineTo(adjustedCenterX + X_SIGN_SIZE, adjustedCenterY + X_SIGN_SIZE);
	dc.MoveTo(adjustedCenterX - X_SIGN_SIZE, adjustedCenterY + X_SIGN_SIZE);
	dc.LineTo(adjustedCenterX + X_SIGN_SIZE, adjustedCenterY - X_SIGN_SIZE);

	CString coordText;
	coordText.Format(_T("(%d, %d)"), centerX, centerY);
	dc.TextOutW(adjustedCenterX + TEXT_POSITION, adjustedCenterY + TEXT_POSITION, coordText);

	m_image.Destroy();
}

void CMFCStartDlg::findCircleCenter(int& centerX, int& centerY)
{
	if (m_image.IsNull()) {
		return;
	}

	const int width = m_image.GetWidth();
	const int height = m_image.GetHeight();
	const int pitch = m_image.GetPitch();

	unsigned char* fm = reinterpret_cast<unsigned char*>(m_image.GetBits());
	unsigned int totalX = 0, totalY = 0, count = 0;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int offset = y * pitch + x;
			if (fm[offset] != 255) { // If the pixel is not 0xFF, it's a part of circle
				totalX += x;
				totalY += y;
				count++;
			}
		}
	}

	if (count == 0) {
		return;
	}

	centerX = totalX / count;
	centerY = totalY / count;
}

