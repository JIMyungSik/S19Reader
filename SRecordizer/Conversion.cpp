#include "StdAfx.h"
#include "Conversion.h"
#include <math.h>

CConversion::CConversion(void)
{
}

CConversion::~CConversion(void)
{
}

CString CConversion::ByteArray2Str(BYTE* byInput, int iInputLen)
{
	CString strTemp, strOutput; 

	strOutput = "" ;
	for (int i=0 ; i<iInputLen ; i++)
	{
		strTemp.Format("%02X", *(byInput+i));
		strOutput += strTemp;
	}

	strOutput += "\0";

	return strOutput;
}

void CConversion::ConvertHexToBinSub(char* nums, unsigned int u, CString* BinCode)
{
	unsigned num;
	char buf[5]="";
	*BinCode="";
	int i;


	for ( ; u ; nums++,u--)
	{
		if((*nums>='0')&&(*nums<='9'))
		{
			num = *nums - '0';
		}
		else if((*nums>='a')&&(*nums<='f'))
		{
			num = *nums - 'a' + 10;
		}
		else if((*nums>='A')&&(*nums<='F'))
		{
			num = *nums - 'A' + 10;
		}
		else
		{
			return;
		}

		for(i=0; i<4; i++)
		{ 
			buf[i] = (num&1) +'0'; 
			num = num>>1;
		}

		//순서 변환 
		for(i=3; i>=0; i--)
		{
			*BinCode+=buf[i];
		}
	}
}

void CConversion::str2ByteArry(CString strInput, BYTE* byOutput, int iLength)
{
	int iInputLen = strInput.GetLength()/2;
	char *ptr;

	memset(byOutput, 0, iLength) ;
	for (int i=0 ; i<iInputLen ; i++)
	{
		*(byOutput+i) = (BYTE)strtoul(strInput.Mid(i*2, 2), &ptr, 16);
	}
}

void CConversion::HEXTOASC(LPBYTE Source, LPBYTE Dest, int length)
{
	int i,j;

	for(i=0, j=0; i<length; i++, j=i*2)
	{
		Dest[j]   = Source[i] >> 4; Dest[j+1] = Source[i] & 0x0f;
		if(Dest[j  ] >= 0 && Dest[j  ] <= 9) Dest[j  ] += 0x30; else Dest[j  ] += 0x37;
		if(Dest[j+1] >= 0 && Dest[j+1] <= 9) Dest[j+1] += 0x30; else Dest[j+1] += 0x37;
	}
}

void CConversion::ASCTOHEX(LPBYTE Source, LPBYTE Dest, int length)
{
	int i;

	for(i=0; i<length; i++)
		Dest[i] = StrhextoInt(Source[i*2]) * 16 + StrhextoInt(Source[i*2+1]);
}

void CConversion::STRTOHEX(char Source[], char Dest[], int length)
{
	char str_hex[10];

	memset(Dest, 0x00, sizeof(Dest));

	for (int i = 0; i < length; i++){
		memset(str_hex, 0x00, sizeof(str_hex));
		sprintf_s(str_hex, "%02X", Source[i]);
		StrCat(Dest, str_hex);
	}

}

int CConversion::StrhextoInt(char src)
{
	int temp_val;

	if(src == (char)'\0') return 0;

	temp_val = src;
	if     (temp_val >= 0x30 && temp_val <= 0x39) temp_val -= 0x30;
	else if(temp_val >= 0x41 && temp_val <= 0x46) temp_val += 10 - 0x41;
	else if(temp_val >= 0x61 && temp_val <= 0x66) temp_val += 10 - 0x61;

	return temp_val;
}

unsigned short CConversion::byteSwap(unsigned short n) 
{
	return ((n >> 8) | (n << 8));
}

void CConversion::HangulToHex(char* strHangul, char* Dest)
{
	unsigned short char16;
	int len = (int)strlen(strHangul) / 2;
	char str_tmp[512];
	char str_hex[512];

	memset(str_tmp, 0x00, sizeof(str_tmp));
	memset(str_hex, 0x00, sizeof(str_hex));

	for (int i = 0; i < len; i++) {
		char16 = *((unsigned short *)strHangul + i);
		sprintf_s(str_tmp, "%04X", byteSwap(char16));
		strcat_s(str_hex, str_tmp);
	}

	StrCpy(Dest, str_hex);
	//str2ByteArry(str_hex, Dest, strlen(strHangul)*2);
}


unsigned char CConversion::HexToByte(char hex)
{
	switch(hex)
	{
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'A': case 'a': return 10;
		case 'B': case 'b': return 11;
		case 'C': case 'c': return 12;
		case 'D': case 'd': return 13;
		case 'E': case 'e': return 14;
		case 'F': case 'f': return 15;
	}
	return 32;
}

unsigned int CConversion::hextoDec(CString strHex)
{

	unsigned char bin[8] = {0,};
	unsigned int m_nDEC = 0;

	int nLen = strHex.GetLength();
	if (nLen > 8)
		return -1;

	for (int i=0 ; i<nLen ; i++) {
		bin[i] = HexToByte(strHex[(nLen-1) - i]);
		if(bin[i] >= 0 && bin[i] <= 15) {    // 0 ~ A ~ F
			m_nDEC += bin[i] << (4*i);     // 10진수 출력
		}
		else if (bin[i] == 32) {
			return -1;
		}
	}
	return m_nDEC;
}

int CConversion::StrToIntConv(CString hv)
{
	int dest = 0;
	char chv[2];
	sprintf_s(chv,hv);

	dest = (char)((chv[0] <= '9') ? chv[0] - '0' : (chv[0] <= 'Z') ? chv[0] - 'A' + 10 : chv[0] - 'a' + 10);
	return dest;
}


void CConversion::SpaceHangul(char* strHangul, char* spaceHangul)
{
	int len = 0;
	CString str_name = "";
	str_name.Format("%s", strHangul);

	memset(spaceHangul, 0x00, sizeof(spaceHangul));

	//성명이 한글일 경우 한칸씩 띄우기 (홍길동 => 홍 길 동)
	if (IsDBCSLeadByte(str_name.GetAt(0))){
		//한글일경우
		len = str_name.GetLength();
		for (int j = 0; j < len; j += 2){
			StrCat(spaceHangul, str_name.Mid(j, 2));
			StrCat(spaceHangul, " ");
		}
	}
	else{
		// 영어일경우
		StrCpy(spaceHangul, strHangul);
	}
}

void CConversion::SpaceCardNo(char* strCardNo, char* spaceCardNo)
{
	CString str_card_no = "";
	str_card_no.Format("%s", strCardNo);

	memset(spaceCardNo, 0x00, sizeof(spaceCardNo));
	StrCat(spaceCardNo, str_card_no.Left(4));
	StrCat(spaceCardNo, " ");
	StrCat(spaceCardNo, str_card_no.Mid(4, 4));
	StrCat(spaceCardNo, " ");
	StrCat(spaceCardNo, str_card_no.Mid(8, 4));
	StrCat(spaceCardNo, " ");
	StrCat(spaceCardNo, str_card_no.Mid(12, 4));
}

char CConversion::hex4b2str4b(BYTE hexdata)
{
	switch (hexdata)
	{
	case  0:    return '0';
	case  1:    return '1';
	case  2:    return '2';
	case  3:    return '3';
	case  4:    return '4';
	case  5:    return '5';
	case  6:    return '6';
	case  7:    return '7';
	case  8:    return '8';
	case  9:    return '9';
	case 10:    return 'A';
	case 11:    return 'B';
	case 12:    return 'C';
	case 13:    return 'D';
	case 14:    return 'E';
	case 15:    return 'F';
	default:    return 0;
	}
}

int CConversion::HexVal_To_StrHex(char *strdata, BYTE *hexdata, int hexlength)
{
	int i;

	for (i = 0; i < hexlength; i++)
	{
		char highchar, lowchar;

		highchar = hex4b2str4b((char)((BYTE)*(hexdata + i) >> 4));
		lowchar = hex4b2str4b((char)((BYTE)*(hexdata + i) & 0x0F));
		*(strdata + i * 2) = highchar;
		*(strdata + i * 2 + 1) = lowchar;
	}

	return hexlength * 2;
}