#pragma once

class CConversion
{
public:
	CConversion(void);
	~CConversion(void);
	//@{
	//#############################################################################
	CString ByteArray2Str(BYTE* byInput, int iInputLen);
	/**< BYTE형을 문자열로 변환
	@param\n
	byInput : BYTE 데이터\n
	iInputLen : 데이터 길이
	@return\n
	CString
	*/
	//#############################################################################
	void ConvertHexToBinSub(char* nums, unsigned int u, CString* BinCode);
	/**< HEX값을 2진수로 변환
	@param\n
	nums : HEX 데이터\n
	u : 데이터 길이\n
	BinCode : 변환될2진수
	@return\n
	none
	*/
	//#############################################################################
	void str2ByteArry(CString strInput, BYTE* byOutput, int iLength);
	/**< 문자열을 BYTE형으로 변환
	@param\n
	strInput : 입력문자열\n
	byOutPut : 변환될 BYTE 변수\n
	iLength : 변환될 데이터 길이
	@return\n
	none
	*/
	//#############################################################################
	void HEXTOASC(LPBYTE Source, LPBYTE Dest, int length);
	/**< HEX값을 아스키로 변환
	@param\n
	Source : HEX 데이터\n
	Dest : 변환될 아스키 변수\n
	length : HEX 데이터 길이
	@return\n
	none
	*/
	//#############################################################################
	void STRTOHEX(char Source[], char Dest[], int length);
	void ASCTOHEX(LPBYTE Source, LPBYTE Dest, int length);
	/**< 아스키값을 HEX로 변환
	@param\n
	Source : 아스키 데이터\n
	Dest : 변환될 HEX 변수\n
	length : 길이
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
	/**< HEX값을 10진수로 변환
	@param\n
	strHex : HEX 데이터
	@return\n
	10진수 값
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
