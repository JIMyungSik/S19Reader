#pragma once

class CConversion
{
public:
	CConversion(void);
	~CConversion(void);
	//@{
	//#############################################################################
	CString ByteArray2Str(BYTE* byInput, int iInputLen);
	/**< BYTE���� ���ڿ��� ��ȯ
	@param\n
	byInput : BYTE ������\n
	iInputLen : ������ ����
	@return\n
	CString
	*/
	//#############################################################################
	void ConvertHexToBinSub(char* nums, unsigned int u, CString* BinCode);
	/**< HEX���� 2������ ��ȯ
	@param\n
	nums : HEX ������\n
	u : ������ ����\n
	BinCode : ��ȯ��2����
	@return\n
	none
	*/
	//#############################################################################
	void str2ByteArry(CString strInput, BYTE* byOutput, int iLength);
	/**< ���ڿ��� BYTE������ ��ȯ
	@param\n
	strInput : �Է¹��ڿ�\n
	byOutPut : ��ȯ�� BYTE ����\n
	iLength : ��ȯ�� ������ ����
	@return\n
	none
	*/
	//#############################################################################
	void HEXTOASC(LPBYTE Source, LPBYTE Dest, int length);
	/**< HEX���� �ƽ�Ű�� ��ȯ
	@param\n
	Source : HEX ������\n
	Dest : ��ȯ�� �ƽ�Ű ����\n
	length : HEX ������ ����
	@return\n
	none
	*/
	//#############################################################################
	void STRTOHEX(char Source[], char Dest[], int length);
	void ASCTOHEX(LPBYTE Source, LPBYTE Dest, int length);
	/**< �ƽ�Ű���� HEX�� ��ȯ
	@param\n
	Source : �ƽ�Ű ������\n
	Dest : ��ȯ�� HEX ����\n
	length : ����
	@return\n
	none
	*/
	//#############################################################################
	int StrhextoInt(char src);
	//#############################################################################
	unsigned short byteSwap(unsigned short n);
	//#############################################################################
	void HangulToHex(char* strHangul, char* Dest);
	//#############################################################################
	unsigned char HexToByte(char hex);
	//#############################################################################
	unsigned int hextoDec(CString strHex);
	/**< HEX���� 10������ ��ȯ
	@param\n
	strHex : HEX ������
	@return\n
	10���� ��
	*/
	//#############################################################################
	int StrToIntConv(CString hv);
//@}
	void Mag_DecodeData(BSTR strTrack1Data, BSTR strTrack2Data, BSTR strTrack3Data, char* card_no, char* valid_thru);
	void SpaceHangul(char* strHangul, char* spaceHangul);
	void SpaceCardNo(char* strCardNo, char* spaceCardNo);

	char hex4b2str4b(BYTE hexdata);
	int HexVal_To_StrHex(char *strdata, BYTE *hexdata, int hexlength);
};
