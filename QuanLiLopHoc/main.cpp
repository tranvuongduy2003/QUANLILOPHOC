#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct NodeSinhVien
{
	string id = "";
	string name = "";
	float gpa{};
	NodeSinhVien* next = NULL;
};
typedef struct NodeSinhVien NSINHVIEN;

struct ListSinhVien
{
	NSINHVIEN *head;
	NSINHVIEN *tail;
};
typedef struct ListSinhVien LSINHVIEN;


NSINHVIEN* CreateNode(string, string, float);
void CreateList(LSINHVIEN&);
bool Compare(NSINHVIEN*, NSINHVIEN*);
NSINHVIEN* Search(LSINHVIEN, NSINHVIEN*);
int DeleteHead(LSINHVIEN&);
int DeleteByID(LSINHVIEN&, string);
LSINHVIEN GPAMoreThanAverage(LSINHVIEN);
int Rank(float);
void QuickSort(LSINHVIEN&);
void PrintList(LSINHVIEN, int);
void InsertHead(LSINHVIEN&, NSINHVIEN*);
void InsertTail(LSINHVIEN&, NSINHVIEN*);
void Insert(LSINHVIEN&, int, NSINHVIEN*);
void OrderedInsert(LSINHVIEN&, NSINHVIEN*);


int main()
{
	string m;
	string id;
	string name;
	float gpa;
	NSINHVIEN *p{}, *t{};
	LSINHVIEN danhSachSinhVien, danhSachSinhVienTrenTB;

	CreateList(danhSachSinhVien);
	do {
		getline(cin, id);
		getline(cin, name);
		if (name == "")
			break;
		cin >> gpa;
		cin.ignore();

		p = CreateNode(id, name, gpa);
		InsertHead(danhSachSinhVien, p);
	} while (1);

	cout << "Danh sach sinh vien:\n";
	PrintList(danhSachSinhVien, 0);

	cout << "Nhap thong tin sinh vien can tim:\n";
	getline(cin, id);
	getline(cin, name);
	cin >> gpa;
	cin.ignore();
	t = CreateNode(id, name, gpa);

	p = Search(danhSachSinhVien, t);
	if (p != NULL)
		cout << "Tim thay!" << endl;
	else
		cout << "Khong tim thay!" << endl;

	cout << "Nhap ma so sinh vien can xoa: ";
	getline(cin, m);
	DeleteByID(danhSachSinhVien, m);
	cout << "Danh sach sau khi xoa:\n";
	PrintList(danhSachSinhVien, 0);

	CreateList(danhSachSinhVienTrenTB);
	danhSachSinhVienTrenTB = GPAMoreThanAverage(danhSachSinhVien);
	cout << "Danh sach sinh vien co diem trung binh lon hon hoac bang 5:\n";
	PrintList(danhSachSinhVienTrenTB, 0);

	cout << "Danh sach hoc sinh co xep loai:\n";
	PrintList(danhSachSinhVien, 1);


	QuickSort(danhSachSinhVien);
	cout << "Danh sach sinh vien sau khi sap xep:\n";
	PrintList(danhSachSinhVien, 0);

	
	OrderedInsert(danhSachSinhVien, t);
	cout << "Danh sach sinh vien sau khi chen:\n";
	PrintList(danhSachSinhVien, 0);

	return 0;
}

NSINHVIEN* CreateNode(string id, string name, float gpa)
{
	NSINHVIEN* p = new NSINHVIEN;
	p->id = id;
	p->name = name;
	p->gpa = gpa;
	p->next = NULL;
	return p;
}
void CreateList(LSINHVIEN& l)
{
	l.head = NULL;
	l.tail = NULL;
}
bool Compare(NSINHVIEN* p, NSINHVIEN* q)
{
	if (p->id != q->id)
		return false;
	if (p->name != q->name)
		return false;
	if (p->gpa != q->gpa)
		return false;
	return true;
}
NSINHVIEN* Search(LSINHVIEN l, NSINHVIEN* p)
{
	NSINHVIEN* q = l.head;
	while (q != NULL)
	{
		if (Compare(q, p))
			return q;
		q = q->next;
	}
	return NULL;
}
int DeleteHead(LSINHVIEN& l)
{
	NSINHVIEN* p;
	if (l.head != NULL)
	{
		p = l.head;
		l.head = p->next;
		delete p;
		return 1;
	}
	return 0;
}
int DeleteByID(LSINHVIEN& l, string x)
{
	NSINHVIEN *p, *q;
	if (l.head != NULL)
	{
		p = l.head;
		q = NULL;
		if (p->id == x)
		{
			DeleteHead(l);
			return 1;
		}
		while (p != NULL && p->id != x)
		{
			q = p;
			p = p->next;
		}
		if (p != NULL)
		{
			q->next = p->next;
			delete p;
			return 1;
		}
		else
			return 0;
	}
}
LSINHVIEN GPAMoreThanAverage(LSINHVIEN l)
{
	NSINHVIEN *p, *q;
	LSINHVIEN l1;
	CreateList(l1);
	p = l.head;
	while (p != NULL)
	{
		if (p->gpa >= 5)
		{
			q = CreateNode(p->id, p->name, p->gpa);
			InsertTail(l1, q);
		}
		p = p->next;
	}
	return l1;
}
int Rank(float gpa)
{
	if (gpa >= 9) //Xuat sac
		return 1;
	else if (gpa >= 8) //Gioi
		return 2;
	else if (gpa >= 7) //Kha
		return 3;
	else if (gpa >= 6.5) //Trung binh kha
		return 4;
	else if (gpa >= 5) //Trung binh
		return 5;
	else //Yeu
		return 6;
}
void QuickSort(LSINHVIEN& l)
{
	NSINHVIEN *p, *m;
	LSINHVIEN l1, l2;

	if (l.head == l.tail) return;

	CreateList(l1);
	CreateList(l2);

	m = l.head;
	l.head = m->next;

	while (l.head != NULL)
	{
		p = l.head;
		l.head = p->next;
		p->next = NULL;
		if (p->gpa <= m->gpa)
			InsertHead(l1, p);
		else
			InsertHead(l2, p);
	}

	QuickSort(l1);
	QuickSort(l2);

	if (l1.head != NULL)
	{
		l.head = l1.head;
		l1.tail->next = m;
	}
	else
		l.head = m;
	m->next = l2.head;
	if (l2.head != NULL)
		l.tail = l2.tail;
	else
		l.tail = m;
}
void PrintList(LSINHVIEN l, int option)
{
	NSINHVIEN* p = l.head;
	const char separator = ' ';
	const int nameWidth = 20;
	const int numWidth = 8;
	cout << left << setw(nameWidth) << setfill(separator) << "Ma so";
	cout << left << setw(nameWidth) << setfill(separator) << "Ho ten";
	cout << left << setw(numWidth) << setfill(separator) << "DTB";
	if (option == 1)
		cout << left << setw(nameWidth + 9) << setfill(separator) << "Xep loai";
	cout << endl;
	while (p != NULL)
	{
		cout << left << setw(nameWidth) << setfill(separator) << p->id;
		cout << left << setw(nameWidth) << setfill(separator) << p->name;
		cout << left << setw(numWidth) << setfill(separator) << p->gpa;
		if (option == 1)
		{
			string rankLabel = "";
			int rank = Rank(p->gpa);
			switch (rank)
			{
			case 1:
				rankLabel = "Xuat sac";
				break;
			case 2:
				rankLabel = "Gioi";
				break;
			case 3:
				rankLabel = "Kha";
				break;
			case 4:
				rankLabel = "Trung binh kha";
				break;
			case 5:
				rankLabel = "Trung binh";
				break;
			case 6:
				rankLabel = "Yeu";
				break;
			}
			cout << left << setw(nameWidth + 9) << setfill(separator) << rankLabel;
		}
		cout << endl;
		p = p->next;
	}
}
void InsertHead(LSINHVIEN& l, NSINHVIEN* p)
{
	if (l.head == NULL)
	{
		l.head = p;
		l.tail = l.head;
	}
	else
	{
		p->next = l.head;
		l.head = p;
	}
}
void InsertTail(LSINHVIEN& l, NSINHVIEN* p)
{
	if (l.head == NULL)
	{
		l.head = p;
		l.tail = l.head;
	}	
	else
	{
		p->next = NULL;
		l.tail->next = p;
		l.tail = p;
	}
}
void Insert(LSINHVIEN& l, int pos, NSINHVIEN* p)
{
	if (l.head == NULL)
		InsertHead(l, p);
	else
	{
		NSINHVIEN *q = l.head;
		for (int i = 0; i < pos - 1; i++)
			q = q->next;
		p->next = q->next;
		q->next = p;
	}
}
void OrderedInsert(LSINHVIEN& l, NSINHVIEN* p)
{
	if (l.head == NULL)
		InsertHead(l, p);
	else
	{
		NSINHVIEN *q, *t;
		q = l.head;
		t = NULL;
		while (q != NULL && q->gpa < p->gpa)
		{
			t = q;
			q = q->next;
		}
		p->next = t->next;
		t->next = p;
		if (q == NULL)
			l.tail = p;
	}
}