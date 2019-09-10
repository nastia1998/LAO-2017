#pragma once
#define ID_MAXSIZE		11			//������������ ���-�� �������� � ��������������
#define TI_MAXSIZE		4096		//������������ ���-�� ����� � ��������������
#define TI_INT_DEFAULT	0x00000000	//�������� �� ��������� ��� ���� integer
#define TI_STRDEFAULT	0x00		//�������� �� ��������� ��� ���� string
#define TI_NULLIDX		0xffffffff	//��� �������� ������� ���������������
#define TI_STR_MAXSIZE	225	

namespace IT
{
	enum IDDATATYPE { NUM = 1, STR = 2, OPR = 3 };
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, O = 5 };   //����������, �������, �������� �������, �������, ��������

	struct Entry						// ������ ������� ���������������
	{
		int			idxfirstLE;			//������ ������ ������ � ������� ������
		char		id[ID_MAXSIZE];		//�������������	(�������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE	iddatatype;			//��� ������
		IDTYPE		idtype;				//��� ��������������
		union
		{
			int vint;					//�������� integer
			struct {
				int len;						//����� string
				char str[TI_STR_MAXSIZE];		//������� string
			} vstr;								//�������� string
		} value;				//�������� ��������������
	};

	struct IdTable				//��������� ������� ���������������
	{
		int maxsize;			//������� ������� ��������������� < TI_MAXSIZE
		int size;				//������� ������ ������� ��������������� < maxsize
		Entry* table;			//������ ����� ������� ���������������
	};
	IdTable Create(				//������� ������� ���������������
		int size				//������� ������� ���������������
	);
	void Add(					//�������� ������ � ������� ���������������
		IdTable& idtable,		//��������� ������� ���������������
		Entry entry				//������ ������� ���������������
	);
	Entry GetEntry(				//�������� ������ ������� ���������������
		IdTable& idtable,		//��������� ������� ���������������
		int n					//����� ���������� ������
	);
	int IsId(					//�������: ����� ������(���� ����), TI_NULLIDX(���� ���)
		IdTable& idtable,		//��������� ������� ���������������
		char id[ID_MAXSIZE]		//�������������
	);
	void Delete(IdTable& idtable);
	int checkId(IdTable& idtable, char value[ID_MAXSIZE]);
	int IsDublId(IdTable& idtable, char id[ID_MAXSIZE]); //�������� �� ����������� ��

	int checkId(IdTable& idtable, int value);
};