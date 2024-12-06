
// MFCStartDlg.h : header file
//

#pragma once
constexpr int X_SIGN_SIZE = 10;
constexpr int TEXT_POSITION = 15;
constexpr int BASE_CIRCLE_SIZE = 10;
constexpr int CIRCLE_SIZE_DELTA = 30;
constexpr int CIRCLE_COLOR_MAX = 200;

// CMFCStartDlg dialog
class CMFCStartDlg : public CDialogEx
{
private:
	CImage m_image;
	int m_nImageWidth;
	int m_nImageHeight;
	int m_nImageStart;
	int m_radius;
	unsigned char m_color;
// Construction
public:
	CMFCStartDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSTART_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDraw();

	void drawCircle(unsigned char* fm, int i, int j, int nRadius, unsigned char  color);
	void findCircleCenter(int& centerX, int& centerY);
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
	afx_msg void OnBnClickedButtonAction();
	afx_msg void OnBnClickedButtonOpen();

};
