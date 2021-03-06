// ������ ������� ���������

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <TCHAR.h>
#pragma warning( disable : 4996)
 
static int count;
static long long size;
 
void dfs() {
    // �������� ������� ������ � ����� � ������� �����
    // 1) ����� . � .. ����������
    // 2) ���� �����, �� ������� � ��� � �������� dfs
    // 3) ���� ����, �� ��������� ��� � ������ count � size
    // 4) ������� � ������������ �����
 
    HANDLE hFind;                   	// ����� ������
    WIN32_FIND_DATA res;            	// ��������� ������
 
    hFind = FindFirstFile(L"*", &res);   // ����� ������ ����
 
    do {
		if ((res.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 &&  
			_tcscmp (res.cFileName, TEXT("..")) &&
			_tcscmp (res.cFileName, TEXT("."))) { // ���� ��� ��������	
				SetCurrentDirectory(res.cFileName);
				dfs();
				SetCurrentDirectory(TEXT(".."));
        }
        else {// ��� ����
			if (_tcscmp (res.cFileName, TEXT("..")) && _tcscmp (res.cFileName, TEXT(".")))
				count++; // ��������� ����� �� ���������??
		_tprintf(TEXT("file #%d is <%s>\n"), count, res.cFileName);
		long long filesize;
		filesize = res.nFileSizeHigh;
		filesize = filesize << 32;
		filesize = filesize + res.nFileSizeLow;
		size += filesize;
		size+=res.nFileSizeLow;
        }
    } while (FindNextFile(hFind, &res) != 0);
    FindClose(hFind);
}
 
int main(int argc, wchar_t* argv[]) {
    wchar_t s[512];               	// ������� �����
    GetCurrentDirectory(512, s);  	// �������� ������� �����
    wprintf(L"Starting in: %s\n", s);
 
    count = 0;                  	// �������� ������� ������
    size = 0;                   	// �������� ��������� ������ ������
    dfs();                      	// ��������� ����� � ������� �� ������� �����
 
    printf("File count = %d, size = %lld\n", count, size);
    return 0;
}
 
