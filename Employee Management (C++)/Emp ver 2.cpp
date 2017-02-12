#include <iostream>
#include <conio.h>
#include <cstring>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <Windows.h>
using namespace std;

#define MAX 100
#define BasicSalary 850000

time_t now = time(0);
tm *ltm = localtime(&now);
int CurrentYear = (1900 + ltm -> tm_year);


void showCur(bool CursorVisibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void clrscr() {
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0, 0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void gotoXY(int column, int line) {
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

enum {
   KEY_ESC     = 27,
   KEY_ENTER   = 13,
   ARROW_UP    = 256 + 72,
   ARROW_DOWN  = 256 + 80,
   ARROW_LEFT  = 256 + 75,
   ARROW_RIGHT = 256 + 77
};

static int Get_KeyCode() {
  int ch = getch();
  if ( ch == 0 || ch == 224 ) ch = 256 + getch();
  return ch;
}

struct Date {
	string Raw;
	int Day, Month, Year;
	void Get_Date() {
	   Day = 0; Month = 0; Year = 0;
      int i = 0;
      while (Raw[i] != '/' && i < Raw.size()) Day = Day*10 + (Raw[i] - 48), i++; i++;
      while (Raw[i] != '/' && i < Raw.size()) Month = Month*10 + (Raw[i] - 48), i++; i++;
      while (i < Raw.size()) Year = Year*10 + (Raw[i] - 48), i++;
	}
};

struct EMPLOYEE {
	long int EmployeeCode;
	string LastName;  // Ho
	string FirstName; // Ten
	Date DayOfBirth;
	int Age;
	int Sex;
	string Department;    // Don vi
	string Position; // Chuc vu
	float SalaryCoenfficient; // He so luong
	float Salary;    // Luong
	float Allowance; // Phu cap
	float NetSalary; // Thuc linh 
	
	void Update() {
		
		Age = CurrentYear - DayOfBirth.Year;
      
		Salary = SalaryCoenfficient * BasicSalary;
		
		if (Position == "GD" || Position == "PGD") Allowance = Salary * 0.4;
		else if (Position == "TP" || Position == "PP") Allowance = Salary * 0.25;
		else Allowance = 0.0;
		
		NetSalary = Salary + Allowance;
	}
	
	
	void Print_DetailInformation() {
		
		gotoXY(33, 11); cout << "> Ho va ten       :  " << LastName << " " << FirstName << endl;
		gotoXY(33, 12); cout << "> Ma so           :  " << EmployeeCode << endl;
		gotoXY(33, 13); cout << "> Gioi Tinh       :  "; cout << ((Sex == 1) ? "Nam\n" : "Nu\n");
		gotoXY(33, 14); cout << "> Ngay sinh       :  " << DayOfBirth.Raw << endl;
		gotoXY(33, 15); cout << "> Tuoi            :  " << Age << endl;
		gotoXY(33, 16); cout << "> Chuc vu         :  ";
		
		if (Position == "GD") cout << "Giam Doc";
		if (Position =="PGD") cout << "Pho Giam Doc";
		if (Position == "TP") cout << "Truong Phong";
		if (Position == "PP") cout << "Pho Phong";
		if (Position == "TT") cout << "To Truong";
		if (Position =="TPH") cout << "To Pho";
		if (Position == "NV") cout << "Nhan Vien";
		cout << endl;
		
	   gotoXY(33, 17); cout << "> Don vi cong tac :  " << Department << endl;
		gotoXY(33, 18); cout << setprecision(3) << "> He so luong     :  " << SalaryCoenfficient << endl;
		//cout << setprecision(10);
		gotoXY(33, 19); cout << setprecision(10) << "> Luong           :  " << Salary << endl;
		gotoXY(33, 20); cout << setprecision(10) << "> Phu cap         :  " << Allowance << endl;
		gotoXY(33, 21); cout << setprecision(10) << "> Thuc Linh       :  " << NetSalary << endl;
		getch();
		
	}
	
};

struct MenuFrame {
   int posX, posY;
   int numberOfCol, numberOfRow, numberOfComp;
   
   string Title;
   string Components[100];
   
   void Set(int x, int y, int k, string s, string comp[]) {
      posX = x; posY = y;
      numberOfComp = k;
      Title = s;
      numberOfCol = 0;
      for (int i = 1; i <= k; i++) {
         Components[i] = comp[i];
         numberOfCol = max(numberOfCol, (int) Components[i].size());
      }
      
      numberOfCol = min(60, numberOfCol + 4);
      numberOfRow = k + 6;
   }
   
   void Highlight(int Comp) {
      TextColor(240);
      gotoXY(posX + 1, posY + 3 + Comp);
      cout << " ";
      cout << Components[Comp];
      gotoXY(posX + 2 + Components[Comp].size(), posY + 3 + Comp);
      for (int i = 1; i <= numberOfCol - 3 - Components[Comp].size(); i++) cout << " ";
   }
   
   void UnHighlight(int Comp) {
      TextColor(15);
      gotoXY(posX + 1, posY + 3 + Comp);
      cout << " ";
      cout << Components[Comp];
      gotoXY(posX + 2 + Components[Comp].size(), posY + 3 + Comp);
      for (int i = 1; i <= numberOfCol - 3 - Components[Comp].size(); i++) cout << " ";
   }
   
   void Print() {
      int len = Title.size();
      int rem = (numberOfCol - 2 - len) / 2;
      
      gotoXY(posX, posY);
      for (int i = 1; i <= numberOfRow; i++) {
         for (int j = 1; j <= numberOfCol; j++) {
            if (i == 1 && j == 1) cout << (char) 201;
            else if (i == 1 && j == numberOfCol) cout << (char) 187;
            else if (i == numberOfRow && j == 1) cout << (char) 200;
            else if (i == numberOfRow && j == numberOfCol) cout << (char) 188;
            else if (i == 3 && j == 1) cout << (char) 204;
            else if (i == 3 && j == numberOfCol) cout << (char) 185;
            else if (i == 1 || i == numberOfRow || i == 3) cout << (char) 205;
            else if (j == 1 || j == numberOfCol) cout << (char) 186;
            else cout << " ";
         }
         gotoXY(posX, posY + i);
      }
      
      gotoXY(posX + rem + 1, posY + 1);
      cout << Title;;
      
      int j = 0;
      for (int i = 4; i <= numberOfRow - 1; i++) {
         gotoXY(posX + 2, posY + i);
         cout << Components[++j];
      }
   }
   
   int Move(int cur) {
      int ch;
      if (cur != -1) Highlight(cur);
      
      while (true) {
         ch = Get_KeyCode();
         if (ch == ARROW_UP) {
            if (cur == -1) {
               cur = numberOfComp;
               Highlight(cur);
            }
            else {
               if (cur != 1) {
                  UnHighlight(cur);
                  Highlight(--cur);
               }            
            }
         }
         else if (ch == ARROW_DOWN) {
            if (cur == -1) {
               cur = 1;
               Highlight(cur);
            }
            else {
               if (cur != numberOfComp) {
                  UnHighlight(cur);
                  Highlight(++cur);
               }            
            }
         }
         else if (ch == ARROW_RIGHT || ch == KEY_ENTER) {
            if (cur != -1) {
               UnHighlight(cur);
               return cur;
            }
         }
         else if (ch == ARROW_LEFT || ch == KEY_ESC) {
            UnHighlight(cur);
            return 0;
         }
      }
   }
};

struct ListFrame {
   int posX, posY;
   int numberOfCol;
   int numberOfRow;
   int numberOfRec;
   int numberOfComp;
   string Title;
   int sizeOfComponents[100];
   string Components[100];
   int Mark[1000];
   
   void Set(int x, int y, int n, int k, string s, string comp[], int sz[]) {
      posX = x;
      posY = y;
      numberOfRec = n;
      numberOfComp = k;
      Title = s;
      numberOfCol = numberOfComp + 1;
      for (int i = 1; i <= k; i++) {
         Components[i] = comp[i];
         sizeOfComponents[i] = sz[i];
         numberOfCol += sizeOfComponents[i];
      }
      numberOfRow = numberOfRec + 6;
      
      for (int i = 1; i <= numberOfRow; i++) Mark[i] = 0;
      Mark[1] = 1;
      int Next = 1;
      int j = 1;
      for (int i = 1; i <= numberOfCol; i++) {
         if (i == Next) {
            Mark[i] = 1;
            Next += (sizeOfComponents[j++] + 1);
         }
         else Mark[i] = 0;
      }
   }
   
   void Print() {
      
      gotoXY(posX, posY);
      
      for (int i = 1; i <= numberOfRow; i++) {
         for (int j = 1; j <= numberOfCol; j++) {
            if (i == 1 && j == 1) cout << (char) 201;
            else if (i == 1 && j == numberOfCol) cout << (char) 187;
            else if ((i == 3 || i == 5) && j == 1) cout << (char) 204;
            else if ((i == 3 || i == 5) && j == numberOfCol) cout << (char) 185;
            else if (i == numberOfRow && j == 1) cout << (char) 200;
            else if (i == numberOfRow && j == numberOfCol) cout << (char) 188;
            else if (i == 3 && Mark[j] == 1) cout << (char) 203;
            else if (i == 5 && Mark[j] == 1) cout << (char) 206;
            else if (i > 3 && i < numberOfRow && Mark[j] == 1) cout << (char) 186;
            else if (i == numberOfRow && Mark[j]) cout << (char) 202;
            else if (i == 1 || i == 3 || i == 5 || i == numberOfRow) cout << (char) 205;
            else if (j == 1 || j == numberOfCol) cout << (char) 186;
            else cout << " ";
         }
         gotoXY(posX, posY + i);
      }
      
      int len = Title.size();
      int rem = (numberOfCol - 2 - len) / 2;
      gotoXY(posX + rem + 1, posY + 1);
      cout << Title << endl;           
      
      gotoXY(posX, posY + 3);
      int j = 1;
      for (int i = 1; i <= numberOfCol; i++) {
         gotoXY(posX + i, posY + 3);
         if (Mark[i]) {
            int tmp = (sizeOfComponents[j] - Components[j].size())/2;
            for (int k = 1; k <= tmp; k++) cout << " ";
            cout << Components[j++];
            if (j == numberOfComp + 1) break;
         }
      }
   }
   
   void PrintRecord(EMPLOYEE Emp[], int n) {
      for (int k = 1; k <= n; k++) {
         int j = 1;
         for (int i = 1; i <= numberOfCol; i++) {
            if (Mark[i]) {
               gotoXY(posX + i, posY + 4 + k);
               cout << " ";
               if (j == 1) cout << k;
               if (j == 2) cout << Emp[k].EmployeeCode;
               if (j == 3) cout << Emp[k].LastName;
               if (j == 4) cout << Emp[k].FirstName;
               if (j == 5) cout << Emp[k].DayOfBirth.Raw;
               if (j == 6) cout << ((Emp[k].Sex == 1) ? "Nam" : "Nu");
               if (j == 7) cout << Emp[k].Department;
               if (j == 8) cout << Emp[k].Position;
               j++;
            }
         }
      }
   }
   
   void Highlight(EMPLOYEE e, int pos) {
      TextColor(240);
      gotoXY(posX, posY + 4 + pos);
      for (int i = 1; i <= numberOfCol; i++) {
         if (Mark[i]) {
            if (i == 1 || i == numberOfCol) {
               TextColor(15);
               cout << (char) 186;
               TextColor(240);
            }
            else cout << (char) 186;
         }
         else cout << " ";
      }
      int j = 1;
      for (int i = 1; i <= numberOfCol; i++) {
         gotoXY(posX + i, posY + 4 + pos);
         if (Mark[i]) {
            if (j != 9) cout << " ";
            if (j == 1) cout << pos;
            if (j == 2) cout << e.EmployeeCode;
            if (j == 3) cout << e.LastName;
            if (j == 4) cout << e.FirstName;
            if (j == 5) cout << e.DayOfBirth.Raw;
            if (j == 6) cout << ((e.Sex == 1) ? "Nam" : "Nu");
            if (j == 7) cout << e.Department;
            if (j == 8) cout << e.Position;
            j++;
         }
      }
   }
   
   void UnHighlight(EMPLOYEE e, int pos) {
      TextColor(15);
      gotoXY(posX, posY + 4 + pos);
      for (int i = 1; i <= numberOfCol; i++) {
         if (Mark[i]) cout << (char) 186;
         else cout << " ";
      }
      int j = 1;
      for (int i = 1; i <= numberOfCol; i++) {
         gotoXY(posX + i, posY + 4 + pos);
         if (Mark[i]) {
            if (j != 9) cout << " ";
            if (j == 1) cout << pos;
            if (j == 2) cout << e.EmployeeCode;
            if (j == 3) cout << e.LastName;
            if (j == 4) cout << e.FirstName;
            if (j == 5) cout << e.DayOfBirth.Raw;
            if (j == 6) cout << ((e.Sex == 1) ? "Nam" : "Nu");
            if (j == 7) cout << e.Department;
            if (j == 8) cout << e.Position;
            j++;
         }
      }
   }
   
   
   int Move(EMPLOYEE e[], int cur) {
      int ch;
      if (cur != -1) Highlight(e[cur], cur);
      if (numberOfRec == 0) return 0;
      
      while (true) {
         ch = Get_KeyCode();
         if (ch == ARROW_UP) {
            if (cur == -1) {
               cur = numberOfRec;
               Highlight(e[cur], cur);
            }
            else {
               if (cur != 1) {
                  UnHighlight(e[cur], cur); cur--;
                  Highlight(e[cur], cur);
               }            
            }
         }
         else if (ch == ARROW_DOWN) {
            if (cur == -1) {
               cur = 1;
               Highlight(e[cur], cur);
            }
            else {
               if (cur != numberOfRec) {
                  UnHighlight(e[cur], cur); cur++;
                  Highlight(e[cur], cur);
               }            
            }
         }
         else if (ch == ARROW_RIGHT || ch == KEY_ENTER) {
            if (cur != -1) {
               //UnHighlight(e[cur], cur);
               return cur;
            }
         }
         else if (ch == ARROW_LEFT || ch == KEY_ESC) {
            if (cur != -1) UnHighlight(e[cur], cur);
            return 0;
         }
      }
   }
   
};

int Number;
int SortType = 0;
EMPLOYEE Employees[MAX];

void Init_Frame();
void Read_Data();
void Update_Data();
void MainMenu();
void Print_EmployeeList(EMPLOYEE e[], int n);
void Print_Notification(int posX, int posY, string Title);
void Add_Employee();
void FindMenu();
void SortMenu();
void DeleteMenu();
void Insert_Employee();
void Print_DepartmentList();

MenuFrame MainMenu_Frame;
MenuFrame FindMenu_Frame;
MenuFrame SortMenu_Frame;
MenuFrame DeleteMenu_Frame;
MenuFrame EmployeeDetail_Frame;

int main() {
   
   TextColor(15);
   Read_Data();
   Init_Frame();
   MainMenu();
   
   TextColor(15);
   gotoXY(1, MainMenu_Frame.posY + 16);
   return 0;
}

void Read_Data() {
   
   ifstream MyFile;
   MyFile.open("data.txt");
   
   if (!MyFile) {
		cout << "Khong the mo file!" << endl;
		exit(0);
	}
   Number = 0;
	while (!MyFile.eof()) {
      Number++;
      MyFile >> Employees[Number].LastName 
             >> Employees[Number].FirstName
	          >> Employees[Number].EmployeeCode
	          >> Employees[Number].Sex
	          >> Employees[Number].DayOfBirth.Raw
	          >> Employees[Number].Department
	          >> Employees[Number].Position
	          >> Employees[Number].SalaryCoenfficient;
      MyFile.ignore();
      Employees[Number].DayOfBirth.Get_Date();
	   Employees[Number].Update();
	   if (MyFile.eof()) {
	      Number--;
	      break;
      }
	}
	MyFile.close();
	
}

void Update_Data() {
   
   ofstream MyFile;
   MyFile.open("data.txt");
   
   for (int i = 1; i <= Number; i++) {
      MyFile << Employees[i].LastName << " "
             << Employees[i].FirstName << " "
             << Employees[i].EmployeeCode << " "
	          << Employees[i].Sex << " "
	          << Employees[i].DayOfBirth.Raw << " "
	          << Employees[i].Department << " "
	          << Employees[i].Position << " "
	          << Employees[i].SalaryCoenfficient << " "
	          << endl;
   }
   MyFile.close();
   
}

EMPLOYEE Enter_Information() {
   
   EMPLOYEE Emp;
   cout << endl << endl << endl;
 Retype_LastName:
   cout << ">> Ho va ten lot: ";
	cin >> Emp.LastName;
   cin.clear(); cin.ignore(); fflush(stdin);
	for (int i = 0; i < Emp.LastName.size(); i++) {
	   if (Emp.LastName[i] < 65 || (Emp.LastName[i] > 90 && Emp.LastName[i] < 97) || Emp.LastName[i] > 122
         || (Emp.LastName[0] < 65 || Emp.LastName[0] > 90)) {
	      cout << "Yeu cau nhap dung ho va ten lot! (viet lien, in hoa chu cai dau)\n";
	      goto Retype_LastName;
      }
   }
	
	
 Retype_FirstName:
   cout << ">> Ten: ";
   cin >> Emp.FirstName;
   cin.clear(); cin.ignore(); fflush(stdin);
	for (int i = 0; i < Emp.FirstName.size(); i++) {
	   if (Emp.FirstName[i] < 65 || (Emp.FirstName[i] > 90 && Emp.FirstName[i] < 97) || Emp.FirstName[i] > 122
         || (Emp.FirstName[0] < 65 || Emp.FirstName[0] > 90)) {
	      cout << "Yeu cau nhap dung ten nhan vien! (viet hoa chu cai dau)\n";
	      goto Retype_FirstName;
      }
   }


 Retype_Code:
   cout << ">> Ma so: ";	
   cin >> Emp.EmployeeCode;
   cin.clear(); cin.ignore(); fflush(stdin);
	if (Emp.EmployeeCode <= 0) {
	   cout << "Yeu cau nhap dung Ma Nhan Vien!\n";
	   goto Retype_Code;
   }
	
	
 Retype_Sex:
   cout << ">> Gioi tinh (1: Nam, 0: Nu): ";
	cin >> Emp.Sex;
   cin.clear(); cin.ignore(); fflush(stdin);
	if (Emp.Sex != 0 && Emp.Sex != 1) {
	   cout << "Yeu cau nhap dung Gioi tinh (0 hoac 1)!\n";
	   goto Retype_Sex;
   }
	
	
 Retype_Day:
	cout << ">> Ngay thang nam sinh (dd/mm/yyyy): ";
	cin >> Emp.DayOfBirth.Raw;
   cin.clear(); cin.ignore(); fflush(stdin);
	Emp.DayOfBirth.Get_Date();
	int cnt = 0;
   for (int i = 0; i < Emp.DayOfBirth.Raw.size(); i++) {
	   if (Emp.DayOfBirth.Raw[i] == '/') cnt++;
   }
   
   if (cnt != 2) {
      cout << "Yeu cau nhap dung theo dinh dang (dd/mm/yyyy)! ";
      goto Retype_Day;
   }
	if ((Emp.DayOfBirth.Day < 1 || Emp.DayOfBirth.Day > 31) || (Emp.DayOfBirth.Month < 1 || Emp.DayOfBirth.Month > 12)
       || (Emp.DayOfBirth.Year < 1900 || Emp.DayOfBirth.Year > CurrentYear)) {
	   cout << "Yeu cau nhap dung ngay thang nam sinh!\n";
	   goto Retype_Day;
   }
	
	
 Retype_Department:
	cout << ">> Don vi: ";
	cin >> Emp.Department;
   cin.clear(); cin.ignore(); fflush(stdin);
	for (int i = 0; i < Emp.Department.size(); i++) {
	   if (Emp.Department[i] < 48 || (Emp.Department[i] > 57 && Emp.Department[i] < 65)
	      || (Emp.Department[i] > 90 && Emp.Department[i] < 97) || Emp.Department[i] > 122) {
	         cout << "Yeu cau nhap dung ten Don Vi! \n";
	         goto Retype_Department;
      }
   }
	
 Retype_Position:
	cout << ">> Chuc vu: ";
	cin >> Emp.Position;
   cin.clear(); cin.ignore(); fflush(stdin);
	
   int ok = 0;
	if (Emp.Position == "GD") ok = 1;
	if (Emp.Position =="PGD") ok = 1;
	if (Emp.Position == "TP") ok = 1;
	if (Emp.Position == "PP") ok = 1;
	if (Emp.Position == "TT") ok = 1;
	if (Emp.Position == "TPH") ok = 1;
	if (Emp.Position == "NV") ok = 1;
   if (!ok) {
      cout << "Khong co chuc vu nay! Yeu cau nhap dung ten Chuc Vu!\n";
      goto Retype_Position;
   }
   
   
 Retype_SalaryCoenfficient:
	cout << ">> He so luong: ";
	cin >> Emp.SalaryCoenfficient;
   cin.clear(); cin.ignore(); fflush(stdin);
	if (Emp.SalaryCoenfficient < 0.0) {
	   cout << "Yeu cau nhap dung He So Luong!\n";
      goto Retype_SalaryCoenfficient;
   }
	Emp.Update();
	
	return Emp;
}

void Init_Frame() {
   
   string tmp[100];
   
   // Main menu:
   tmp[1] = "1. IN DANH SACH NHAN VIEN";
   tmp[2] = "2. THEM NHAN VIEN";
   tmp[3] = "3. TIM KIEM NHAN VIEN";
   tmp[4] = "4. SAP XEP NHAN VIEN";
   tmp[5] = "5. CHEN NHAN VIEN";
   tmp[6] = "6. XOA NHAN VIEN";
   tmp[7] = "7. IN DANH SACH CAC DON VI";
   tmp[8] = "8. THOAT CHUONG TRINH";
   MainMenu_Frame.Set(10, 3, 8, "MAIN MENU", tmp);
   
   // Find Menu
   tmp[1] = "1. TIM KIEM THEO TEN";
   tmp[2] = "2. TIM KIEM THEO MA SO";
   tmp[3] = "3. TIM KIEM THEO DON VI";
   tmp[4] = "4. TIM KIEM THEO CHUC VU";
   tmp[5] = "5. TRO LAI";
   FindMenu_Frame.Set(MainMenu_Frame.posX + MainMenu_Frame.numberOfCol + 2, 
                      MainMenu_Frame.posY + 5, 5, "FIND MENU", tmp);
   
   // Sort Menu
   tmp[1] = "1. SAP XEP THEO TEN";
   tmp[2] = "2. SAP XEP THEO MA SO";
   tmp[3] = "3. SAP XEP THEO CHUC VU";
   tmp[4] = "4. SAP XEP THEO DON VI";
   tmp[5] = "5. TRO LAI";
   SortMenu_Frame.Set(MainMenu_Frame.posX + MainMenu_Frame.numberOfCol + 2, 
                      MainMenu_Frame.posY + 6, 5, "SORT MENU", tmp);
   
   // Delete Menu
   tmp[1] = "1. XOA THEO TEN";
   tmp[2] = "2. XOA THEO MA SO";
   tmp[3] = "3. XOA THEO STT";
   tmp[4] = "4. XOA NV TREN 50 TUOI";
   tmp[5] = "5. TRO LAI";
   DeleteMenu_Frame.Set(MainMenu_Frame.posX + MainMenu_Frame.numberOfCol + 2, 
                        MainMenu_Frame.posY + 8, 5, "DELETE MENU", tmp);
   
   
//   Employee_List.Set(5, 3, Number, 8, "DANH SACH NHAN VIEN");
//   Employee_List.Components[1] = "STT";
//   Employee_List.Components[2] = "MA NHAN VIEN";
//   Employee_List.Components[3] = "HO VA TEN LOT";
//   Employee_List.Components[4] = "TEN";
//   Employee_List.Components[5] = "NGAY SINH";
//   Employee_List.Components[6] = "GIOI TINH";
//   Employee_List.Components[7] = "DON VI";
//   Employee_List.Components[8] = "CHUC VU";
//   
//   Employee_List.sizeOfComponents[1] = 5;
//   Employee_List.sizeOfComponents[2] = 14;
//   Employee_List.sizeOfComponents[3] = 17;
//   Employee_List.sizeOfComponents[4] = 9;
//   Employee_List.sizeOfComponents[5] = 12;
//   Employee_List.sizeOfComponents[6] = 12;
//   Employee_List.sizeOfComponents[7] = 10;
//   Employee_List.sizeOfComponents[8] = 9;
//   
//   EmployeeDetail_Frame.Set(30, 7, 45, 14, 0, "DETAIL INFORMATION");
   
}

void Print_Notification(int posX, int posY, string Title) {
   MenuFrame Notification;
   string tmp[10];
   Notification.Set(posX, posY, 0, Title, tmp);
   Notification.numberOfCol = 30;
   Notification.numberOfRow = 5;
   Notification.Print();
   gotoXY(posX + 3, posY + 3);
}

void Print_EmployeeList(EMPLOYEE e[], int n) {
   
   ListFrame Employee_List;
   MenuFrame EmployeeDetail_Frame;
   string tmp[100];
   tmp[1] = "STT";
   tmp[2] = "MA NHAN VIEN";
   tmp[3] = "HO VA TEN LOT";
   tmp[4] = "TEN";
   tmp[5] = "NGAY SINH";
   tmp[6] = "GIOI TINH";
   tmp[7] = "DON VI";
   tmp[8] = "CHUC VU";
   
   int sz[100];
   sz[1] = 5;
   sz[2] = 14;
   sz[3] = 19;
   sz[4] = 9;
   sz[5] = 12;
   sz[6] = 11;
   sz[7] = 10;
   sz[8] = 9;
   Employee_List.Set(5, 3, n, 8, "DANH SACH NHAN VIEN", tmp, sz);
   EmployeeDetail_Frame.Set(30, 7, 0, "DETAIL INFORMATION", tmp);
   EmployeeDetail_Frame.numberOfCol = 45;
   EmployeeDetail_Frame.numberOfRow = 17;
   
   int cur = -1;
   while (true) {
      clrscr();
      Employee_List.Print();
      Employee_List.PrintRecord(e, n);
      
      TextColor(15);
      gotoXY(Employee_List.posX, Employee_List.posY + Employee_List.numberOfRec + 7);
      cout << "Danh sach nay co " << n << " nguoi!";
      gotoXY(Employee_List.posX, Employee_List.posY + Employee_List.numberOfRec + 8);
      cout << "Nhan 'Enter' de xem thong tin chi tiet, 'ESC' de tro ve!";
      
      int sw = Employee_List.Move(e, cur);
      if (sw != 0 && sw != -1) {
         TextColor(15);
         EmployeeDetail_Frame.Print();
         e[sw].Print_DetailInformation();
         cur = sw;
      }
      else break;
   }
}

void MainMenu() {
   
   int cur = -1;
   while (true) {
      clrscr();
      TextColor(15);
      MainMenu_Frame.Print();
      if (cur != -1) MainMenu_Frame.Highlight(cur);
      showCur(false);
      int ch;
      while (true) {
         ch = Get_KeyCode();
         if (ch == ARROW_UP) {
            if (cur == -1) {
               cur = MainMenu_Frame.numberOfComp;
               MainMenu_Frame.Highlight(cur);
            }
            else {
               if (cur != 1) {
                  MainMenu_Frame.UnHighlight(cur);
                  MainMenu_Frame.Highlight(--cur);
               }            
            }
         }
         else if (ch == ARROW_DOWN) {
            if (cur == -1) {
               cur = 1;
               MainMenu_Frame.Highlight(cur);
            }
            else {
               if (cur != MainMenu_Frame.numberOfComp) {
                  MainMenu_Frame.UnHighlight(cur);
                  MainMenu_Frame.Highlight(++cur);
               }            
            }
         }
         else if (ch == ARROW_RIGHT || ch == KEY_ENTER) {
            if (cur != -1) {
               
               switch (cur) {
                  case 1: {
                     MainMenu_Frame.UnHighlight(cur);
                     Print_EmployeeList(Employees, Number);
                     break;
                  }
                  case 2: {
                     MainMenu_Frame.UnHighlight(cur);
                     Add_Employee();
                     break;
                  }
                  case 3: {
                     MainMenu_Frame.UnHighlight(cur);
                     FindMenu();
                     break;
                  }
                  case 4: {
                     SortMenu();
                     break;
                  }
                  case 5: {
                     MainMenu_Frame.UnHighlight(cur);
                     Insert_Employee();
                     break;
                  }
                  case 6: {
                     DeleteMenu();
                     break;
                  }
                  case 7: {
                     MainMenu_Frame.UnHighlight(cur);
                     Print_DepartmentList();
                     break;
                  }
                  case 8: {
                     return;
                  }
               }
               break;
            }
         }
      }
   }
   
}

void Add_Employee() {
   
   TextColor(15);
   clrscr();
   while (true) {
      Number++;
      Employees[Number] = Enter_Information();
      Update_Data();
      int check = 0;
      char ch;
      cout << endl << "Da nhap xong!" << endl;
      cout << "Ban co muon nhap them khong? (Y/N): ";
      showCur(true);
      cin >> ch;
      cin.clear(); cin.ignore(); fflush(stdin);
      showCur(false);
      if (ch == 'y' || ch == 'Y') continue;
      else return;
   }
   
}

void Find_Employee(int Type) {
   
   TextColor(15);
   
   EMPLOYEE Found[100];
   long int Code;
   string Name;
   string Department;
   string Position;
   
   cout << endl << endl << endl;
   showCur(true);
   if (Type == 1) {
      Print_Notification(28, 9, "NHAP TEN CAN TIM");
      cin >> Name;
      cin.clear(); cin.ignore(); fflush(stdin);
   }
   else if (Type == 2) {
      Print_Notification(28, 9, "NHAP MA CAN TIM");
      cin >> Code;
      cin.clear(); cin.ignore(); fflush(stdin);
   }
   else if (Type == 3) {
      Print_Notification(28, 9, "NHAP DON VI CAN TIM");
      cin >> Department;
      cin.clear(); cin.ignore(); fflush(stdin);
   }
   else if (Type == 4) {
      Print_Notification(28, 9, "NHAP CHUC VU CAN TIM");
      cin >> Position;
      cin.clear(); cin.ignore(); fflush(stdin);
   }
   showCur(false);
   
   int n = 0;
   for (int i = 1; i <= Number; i++) {
      if (Type == 1) {
         if (Employees[i].FirstName == Name) {
            n++;
            Found[n] = Employees[i];
         }
      }
      else if (Type == 2) {
         if (Employees[i].EmployeeCode == Code) {
            n++;
            Found[n] = Employees[i];
         }
      }
      else if (Type == 3) {
         if (Employees[i].Department == Department) {
            n++;
            Found[n] = Employees[i];
         }
      }
      else if (Type == 4) {
         if (Employees[i].Position == Position) {
            n++;
            Found[n] = Employees[i];
         }
      }
   }
   if (n == 0) {
      Print_Notification(28, 9, "THONG BAO");
      cout << "Khong tim thay!";
   }
   else Print_EmployeeList(Found, n);
   
}

void FindMenu() {
   
   TextColor(15);
   FindMenu_Frame.Print();
   
   int cur = -1;
   while (true) {
      int sw = FindMenu_Frame.Move(cur);
      if (sw == 5) return;
      if (sw != -1 && sw != 0) {
         Find_Employee(sw);
         getch();
      }
      return;
   }
   
}

void Sort_Employees(int Type) {
   
   SortType = Type;
   for (int i = 1; i <= Number; i++) {
      for (int j = i + 1; j <= Number; j++) {
         if (Type == 1) {
            if (Employees[i].FirstName == Employees[j].FirstName) {
               if (Employees[i].LastName > Employees[j].LastName) {
                  swap(Employees[i], Employees[j]);
               }
            }
            else if (Employees[i].FirstName > Employees[j].FirstName) {
               swap(Employees[i], Employees[j]);
            }
         }
         else if (Type == 2) {
            if (Employees[i].EmployeeCode > Employees[j].EmployeeCode) {
               swap(Employees[i], Employees[j]);
            }
         }
         else if (Type == 3) {
            if (Employees[i].Position > Employees[j].Position) {
               swap(Employees[i], Employees[j]);
            }
         }
         else if (Type == 4) {
            if (Employees[i].Department > Employees[j].Department) {
               swap(Employees[i], Employees[j]);
            }
         }
      }
   }
   Update_Data();
   
   Print_Notification(28, 9, "THONG BAO");
   cout << "Da sap xep xong!";  
}

void SortMenu() {
   
   TextColor(15);
   SortMenu_Frame.Print();
   int cur = -1;
   while (true) {
      int sw = SortMenu_Frame.Move(cur);
      if (sw == 5) return;
      else if (sw != -1 && sw != 0) {
         Sort_Employees(sw);
         getch();
      }
      return;
   }
   
}

void Insert_Employee() {
   
   clrscr();
   TextColor(15);
   
  Continue:
   EMPLOYEE Emp = Enter_Information();
   if (SortType == 0) {
      Number++;
      Employees[Number] = Emp;
      for (int i = 1; i <= Number; i++) {
         for (int j = 1; j <= Number; j++) {
            if (Employees[i].FirstName < Employees[j].FirstName) {
               swap(Employees[i], Employees[j]);
            }
         }
      }
   }
   else {
      int i = Number;
      if (SortType == 1) {
         while (Emp.FirstName < Employees[i].FirstName && i > 0) {
            Employees[i+1] = Employees[i];
            i--;
         }
      }
      else if (SortType == 2) {
         while (Emp.EmployeeCode < Employees[i].EmployeeCode && i > 0) {
            Employees[i+1] = Employees[i];
            i--;
         }
      }
      else if (SortType == 3) {
         while (Emp.Position < Employees[i].Position && i > 0) {
            Employees[i+1] = Employees[i];
            i--;
         }
      }
      else if (SortType == 4) {
         while (Emp.Department < Employees[i].Department && i > 0) {
            Employees[i+1] = Employees[i];
            i--;
         }
      }
      
      Employees[i+1] = Emp;
      Number++;
   }
   Update_Data();
   
   cout << "\n\nDa chen xong! Ban co muon chen them nhan vien khong? (Y/N): ";
   int ch; cin >> ch;
   cin.clear(); cin.ignore(); fflush(stdin);
   if (ch == 'y' || ch == 'Y') goto Continue;
   
}

void Delete_Employee(int Type) {
   
   string Name;
   long int Code;
   int num;
   
   showCur(true);
   if (Type == 1) {
      Print_Notification(28, 9, "NHAP TEN CAN XOA");
      cin >> Name;
      cin.clear(); cin.ignore(); fflush(stdin);
   }
   if (Type == 2) {
      Print_Notification(28, 9, "NHAP MA SO CAN XOA");
      cin >> Code;
      cin.clear(); cin.ignore(); fflush(stdin);
   }
   if (Type == 3) {
      Print_Notification(28, 9, "NHAP SO THU TU CAN XOA");
      cin >> num;
      cin.clear(); cin.ignore(); fflush(stdin);
   }
   showCur(false);
   
   int Mark[100];
   for (int i = 1; i <= Number; i++) {
      Mark[i] = 0;
      if (Type == 1) {
         if (Employees[i].FirstName == Name) Mark[i] = 1;
      }
      else if (Type == 2) {
         if (Employees[i].EmployeeCode == Code) Mark[i] = 1;
      }
      else if (Type == 3) {
         if (i == num) Mark[i] = 1;
      }
      else if (Type == 4) {
         if (Employees[i].Age > 50) Mark[i] = 1;
      }
   }
   
   int cnt = 0;
   for (int i = 1; i <= Number; i++) {
      if (Mark[i] == 0) {
         cnt++;
         Employees[cnt] = Employees[i];
      }
   }
   
   if (Number - cnt == 0 && Type != 4) {
      Print_Notification(28, 9, "THONG BAO");
      cout << "Khong tim thay!";
      return;
   }
   else {
      Print_Notification(28, 9, "THONG BAO");
      cout << "Da xoa xong!";
   }
   
   Number = cnt;
   Update_Data();
}

void DeleteMenu() {
   
   TextColor(15);
   DeleteMenu_Frame.Print();
   int cur = -1;
   
   while (true) {
      int sw = DeleteMenu_Frame.Move(cur);
      if (sw == 5) return;
      else if (sw != -1 && sw != 0) {
         Delete_Employee(sw);
         getch();
      }
      return;
   }
   
}

void Print_DepartmentList() {
   
   struct DEPARTMENT {
      string Name;
      int numberOfMale;
      int numberOfFemale;
      float sumOfNetSalary;
   };
   DEPARTMENT Departments[100];
   
   int nDe = 0;
   
   for (int i = 1; i <= Number; i++) {
      int found = 0;
      for (int j = 1; j <= nDe; j++) {
         if (Employees[i].Department == Departments[j].Name) {
            if (Employees[i].Sex == 1) Departments[j].numberOfMale++;
            else if (Employees[i].Sex == 0) Departments[j].numberOfFemale++;
            Departments[j].sumOfNetSalary += Employees[i].NetSalary;
            found = 1;
            break;
         }
      }
      if (!found) {
         nDe++;
         Departments[nDe].Name = Employees[i].Department;
         Departments[nDe].numberOfMale = (Employees[i].Sex == 1);
         Departments[nDe].numberOfFemale = (Employees[i].Sex == 0);
         Departments[nDe].sumOfNetSalary = Employees[i].NetSalary;
      }
   }
   
   TextColor(15);
   clrscr();
   ListFrame Department_List;
   
   string tmp[100];
   tmp[1] = "STT";
   tmp[2] = "TEN DON VI";
   tmp[3] = "SO NV NAM";
   tmp[4] = "SO NV NU";
   tmp[5] = "TONG THUC LINH";
   
   int sz[100];
   sz[1] = 5;
   sz[2] = 15;
   sz[3] = 11;
   sz[4] = 10;
   sz[5] = 17;
   
   Department_List.Set(5, 3, nDe, 5, "DANH SACH CAC DON VI", tmp, sz);
   Department_List.Print();
   
   for (int k = 1; k <= nDe; k++) {
      int j = 1;
      for (int i = 1; i <= Department_List.numberOfCol; i++) {
         if (Department_List.Mark[i]) {
            gotoXY(Department_List.posX + i, Department_List.posY + 4 + k);
            cout << " ";
            if (j == 1) cout << k;
            if (j == 2) cout << Departments[k].Name;
            if (j == 3) cout << "    " << Departments[k].numberOfMale;
            if (j == 4) cout << "   " << Departments[k].numberOfFemale;
            if (j == 5) cout << setprecision(10) << Departments[k].sumOfNetSalary;
            j++;
         }
      }
   }
   
   TextColor(15);
   gotoXY(Department_List.posX, Department_List.posY + Department_List.numberOfRec + 7);
   cout << "Nhan mot phim bat ky de tro ve!";
   
   getch();
   
}






