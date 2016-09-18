/*

=======================================================
 >>> SAMPLE DATA <<< 
 
16										
PhamQuoc Trong 102140225 1 28/08/1995 14TCLC2 PGD 1.5
NguyenThiLam Oanh 102160215 0 06/08/1995 14TCLC2 GD 1.3
NguyenQuang Huy 103150225 1 13/12/1994 13VCL NV 0.9
HoangVan Phung 13213215 1 12/01/1996 14SA PGD 0.9
TruongQuy Thang 102140225 1 28/08/1993 14TCLC2 TT 1.5
PhamHong Dan 102140215 0 06/08/1995 14TCLC2 PP 1.3
DoPhuc Hoa 103150212 1 13/12/1996 13VCL QL 0.9
HoVanAnh Quoc 13213215 1 12/01/1996 14SA QL 0.9
LuongThanh Phuc 122140225 1 28/08/1995 14TCLC2 PGD 1.5
LeQuang Khang 102140215 0 06/08/1992 14TCLC2 GD 1.3
NguyenThanh Hai 103150225 1 13/12/1996 13VCL TP 0.9
HoangThiThuy Dung 13213215 1 12/01/1900 14SA QL 0.9
LeQuoc Huy 102140225 1 28/08/1995 14TCLC2 TP 1.5
LeXuan Hoang 102140215 0 06/08/1995 14TCLC2 GD 1.3
HoangThuy Linh 103123425 1 13/12/1992 13VCL NV 0.9
Cristiano Ronaldo 13213215 1 12/01/1900 14SA PP 0.9
========================================================

Format:
- Ten: Ho va ten lot viet lien, in hoa chu cai dau. Ten in hoa chu cai dau 
- Ma Nhan Vien: Day gom 9 so, bat dau bang so 1
- Gioi Tinh: 1: Nam, 0: Nu
- Ngay thang nam sinh: dd/mm/yyyy (1 chu so thi them so 0 dau)
- Don Vi: Chuoi ky tu
- Chuc Vu: 
	
	+ CTHDQT	: Chu Tich Hoi Dong Quan Tri
	+ TGD		: Tong Giam Doc
	+ PTGD		: Pho Tong Giam Doc
	
	
	+ GD		: Giam Doc		: rank 7
	+ PGD		: Pho Giam Doc	: rank 6
	+ TP		: Truong Phong	: rank 5
	+ PP		: Pho Phong		: rank 4
	+ TT		: To Truong		: rank 3
	+ TP		: To Pho			: rank 2
	+ NV		: Nhan Vien		: rank 1

- Phu cap: 
	Phu Cap = 40% Luong neu Giam Doc hoac Pho Giam Doc
	Phu Cap = 25% Luong neu Truong Phong hoac Pho Phong
	Phu Cap = 0 cho cac doi tuong con lai


*/

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <string.h>

#define MAX 30
#define LCB 850000

struct date {
	char raw[MAX];
	int Ngay, Thang, Nam;
	void get_date() {
		Ngay = (raw[0]-48)*10 + (raw[1]-48);
		Thang = (raw[3]-48)*10 + (raw[4]-48);
		Nam = (raw[6]-48)*1000 + (raw[7]-48)*100 + (raw[8]-48)*10 + (raw[9]-48);
	}
};

struct NhanVien {
	long int Ma_NhanVien;
	char Ho[20];
	char Ten[20];
	date NgaySinh;
	int Tuoi;
	int GioiTinh;
	char DonVi[100];
	char ChucVu[100];
	float HeSoLuong;
	float Luong;
	float PhuCap;
	float ThucLinh;
	int Bac_ChucVu;
	
	void CapNhat() {
		Tuoi = 2016 - NgaySinh.Nam;
		
		if (strcmp(ChucVu, "GD") == 0) Bac_ChucVu = 7;
		if (strcmp(ChucVu, "PGD")== 0) Bac_ChucVu = 6;
		if (strcmp(ChucVu, "TP") == 0) Bac_ChucVu = 5;
		if (strcmp(ChucVu, "PP") == 0) Bac_ChucVu = 4;
		if (strcmp(ChucVu, "TT") == 0) Bac_ChucVu = 3;
		if (strcmp(ChucVu, "TP") == 0) Bac_ChucVu = 2;
		if (strcmp(ChucVu, "NV") == 0) Bac_ChucVu = 1;
		
		Luong = HeSoLuong * LCB;
		
		if (strcmp(ChucVu, "GD") == 0 || strcmp(ChucVu, "PGD") == 0) PhuCap = Luong * 0.4;
		else if (strcmp(ChucVu, "TP") == 0 || strcmp(ChucVu, "PP") == 0) PhuCap = Luong * 0.25;
		else PhuCap = 0.0;
		
		ThucLinh = Luong + PhuCap;
	}
	
	void In_ThongTin(int stt) {
		printf("  %-3d %-12d %-21s %-8s %-13s", stt, Ma_NhanVien, Ho, Ten, NgaySinh.raw);
		printf(GioiTinh == 1 ? "Nam    " : "Nu     ");
		printf("%-10s %-10s\n", DonVi, ChucVu);
	}
	
	void In_ThongTin_ChiTiet(int stt) {
		
		system("cls");
		printf("\n\n >>> THONG TIN NHAN VIEN CHI TIET <<< \n\n");
		printf("Ho va ten		: %s%s\n", Ho, Ten);
		printf("Ma so			: %ld\n", Ma_NhanVien);
		printf("Gioi Tinh		: "); printf(GioiTinh == 1 ? "Nam\n" : "Nu\n");
		printf("Ngay sinh		: %s\n", NgaySinh.raw);
		printf("Tuoi			: %d\n", Tuoi);
		printf("Chuc vu			: %s\n", ChucVu);
		printf("Don vi cong tac		: %s\n", DonVi);
		printf("He so luong		: %f\n", HeSoLuong);
		printf("Luong			: %.0f\n", Luong);
		printf("Phu cap			: %.0f\n", PhuCap);
		printf("Thuc Linh		: %.0f\n", ThucLinh);
		
	}
};

int num, Kieu_SapXep = 0;
NhanVien NV[MAX];

void Menu();
void Doc_DuLieu();
void Tao_DanhSach();
void CapNhat_DuLieu();
void In_DanhSach();
void Nhap_ThongTinNhanVien(NhanVien &nv);
void Them_NhanVien();
bool Trung_Ten(char *Ten1, char *Ten2);
void TimKiem_NhanVien();
void SapXep(int c);
void SapXep_DanhSach();
void Them_NhanVien_DaSapXep();
void Xoa_NhanVien();
void Xoa_NhanVien_Tren50t();
void In_DanhSach_DonVi();

int main() {
	
	Doc_DuLieu();
	Menu();
	
	return 0;
}

void Menu() {
	
	do {
		system("cls");
		printf(" >>> QUAN LY NHAN VIEN <<< \n\n");
		
		printf(" ---> Tao danh sach Nhan Vien (1)\n");
		printf(" ---> In danh sach Nhan Vien  (2)\n");
		printf(" ---> Them Nhan Vien          (3)\n");
		printf(" ---> Tim kiem                (4)\n");
		printf(" ---> Sap xep danh sach       (5)\n");
		printf(" ---> Chen Nhan Vien          (6)\n");
		printf(" ---> Xoa Nhan Vien           (7)\n");
		printf(" ---> Xoa nhan vien > 50t     (8)\n");
		printf(" ---> In danh sach cac don vi (9)\n");
		printf(" ---> Thoat chuong trinh      (10)\n\n");
		int sw;
	luachon:
		printf("\nNhap lua chon: ");
		fflush(stdin); scanf("%d", &sw);
		
		switch(sw) {
			case 1: Tao_DanhSach(); break;
			case 2: In_DanhSach(); break;
			case 3: Them_NhanVien(); break;
			case 4: TimKiem_NhanVien(); break;
			case 5: SapXep_DanhSach(); break;
			case 6: Them_NhanVien_DaSapXep(); break;
			case 7: Xoa_NhanVien(); break;
			case 8: Xoa_NhanVien_Tren50t(); break;
			case 9: In_DanhSach_DonVi(); break;
			case 10: return;
			default: goto luachon;
		}
		
	} while (true);
}

void Doc_DuLieu() {
	FILE *f = fopen("data.txt", "rt");
	fscanf(f, "%d", &num);
	for (int i = 0; i < num; i++) {
		fscanf(f, "%s%s%ld%d%s%s%s%f", 
		&NV[i].Ho, &NV[i].Ten, &NV[i].Ma_NhanVien, &NV[i].GioiTinh, 
		&NV[i].NgaySinh.raw, &NV[i].DonVi, &NV[i].ChucVu, &NV[i].HeSoLuong);
		NV[i].NgaySinh.get_date();
		NV[i].CapNhat();
	}
	fclose(f);
}

void CapNhat_DuLieu() {
	FILE *f = fopen("data.txt", "wt");
	fprintf(f, "%d\n", num);
	for (int i = 0; i < num; i++) {
		fprintf(f, "%d %s %s %ld %d %s %s %s %f\n", i+1, NV[i].Ho, NV[i].Ten, NV[i].Ma_NhanVien, NV[i].GioiTinh,
		NV[i].NgaySinh.raw, NV[i].DonVi, NV[i].ChucVu, NV[i].HeSoLuong);
	}
	fclose(f);
}

void Nhap_ThongTinNhanVien(NhanVien &nv) {
	
	printf("Nhap ho va ten lot (neu co): ");
	fflush(stdin); gets(nv.Ho);
	printf("Nhap ten nhan vien: ");
	fflush(stdin); gets(nv.Ten);
	
	printf("Nhap ma nhan vien: ");
	fflush(stdin); scanf("%d", &nv.Ma_NhanVien);
	
	printf("Nhap gioi tinh nhan vien (1: Nam, 0: Nu) ");
	fflush(stdin); scanf("%d", &nv.GioiTinh);
	
	printf("Nhap ngay thang nam sinh (dd/mm/yyyy): ");
	fflush(stdin); gets(nv.NgaySinh.raw);
	nv.NgaySinh.get_date();
	
	printf("Nhap don vi cua nhan vien: ");
	fflush(stdin); gets(nv.DonVi);
	
	printf("Nhap chuc vu cua nhan vien: ");
	fflush(stdin); gets(nv.ChucVu);
	
	printf("Nhap he so luong cua nhan vien: ");
	fflush(stdin); scanf("%f", &nv.HeSoLuong);
	
	nv.CapNhat();
}

void Tao_DanhSach() {
	
	system("cls");
	printf("\n\n\t >>> Tao moi danh sach cac nhan vien <<<\n\n");
	printf("Nhap so nhan vien: ");
	scanf("%d", &num);
	printf("Nhap danh sach cac nhan vien: \n");
	for (int i = 0; i < num; i++) {
		printf("\nNhap du lieu nhan vien thu %d: \n\n", i+1);
		fflush(stdin); 
		Nhap_ThongTinNhanVien(NV[i]);
	}
	CapNhat_DuLieu();
	
}

void In_KhungDanhSach() {
	
	printf("  STT |MA NV      |HO VA TEN LOT        |TEN     |NGAY SINH    |GT   |DON VI    |CHUC VU   \n");
	printf("     --------------------------------------------------------------------------\n");
		
}

void In_DanhSach() {
	
	do {
	nhap:
		system("cls");
		printf("\n\n\t >>> Danh sach cac nhan vien <<<\n\n");
		In_KhungDanhSach();
		for (int i = 0; i < num; i++) {
			NV[i].In_ThongTin(i+1);
		}
		printf("     --------------------------------------------------------------------------\n\n");
		
		printf("\n\nNhap STT cua Nhan Vien de xem chi tiet, nhap 0 de tro ve Menu ...");
		int sw;
		fflush(stdin); scanf("%d", &sw);
		if (sw > num || sw < 0) goto nhap;
		if (sw) {
			NV[sw-1].In_ThongTin_ChiTiet(sw);
			printf("\n\nAn phim bat ky de tro lai danh sach...");
			fflush(stdin); getch();
		}
		else break;
	} while (true);
	
}

void Them_NhanVien() {
	
	num++;
	system("cls");
	printf("\n\n >>> Them nhan vien vao danh sach <<< \n\n");
	Nhap_ThongTinNhanVien(NV[num-1]);
	CapNhat_DuLieu();
	
}

bool Trung_Ten(char *Ten1, char *Ten2) {
	
	if (strlen(Ten1) != strlen(Ten2)) return false;
	for (int i = 0; i < strlen(Ten1); i++) {
		char x = Ten1[i], y = Ten2[i];
		if (x < 91) x += 32;
		if (y < 91) y += 32;
		if (x != y) return false;
	}
	return true;
	
}

void TimKiem(int c) {
	
	int dem = 0;
	long int Ms_TimKiem = -1;
	char *Ten_TimKiem;
	
	if (c == 1) {
		printf("\nNhap ten can tim: ");
		fflush(stdin); gets(Ten_TimKiem);
	}
	else {
		printf("\nNhap ma so cam tim: ");
		fflush(stdin); scanf("%ld", &Ms_TimKiem);
	}
	
	printf("\n");

DanhSach:
	system("cls");
	printf("\n\n\n");
	In_KhungDanhSach();
	for (int i = 0; i < num; i++) {
		if (c == 1) {
			if (Trung_Ten(NV[i].Ten, Ten_TimKiem)) {
				NV[i].In_ThongTin(i+1);
				dem++;
			}
		}
		else {
			if (NV[i].Ma_NhanVien == Ms_TimKiem) {
				NV[i].In_ThongTin(i+1);
				dem++;
			}
		}
	}
	if (dem == 0) {
		printf("\nKhong tim thay nhan vien ");
		printf(c == 1 ? "co ten nay!\n" : "co ma so nay!\n");
	}
	else {
		printf("\nTim thay %d nhan vien ", dem);
		printf(c == 1 ? "co ten \"%s\" trong danh sach!\n", Ten_TimKiem :"co ma so %ld trong danh sach!\n", Ms_TimKiem);
		
		printf("\n\nNhap STT cua Nhan Vien de xem chi tiet, nhap 0 de tro ve Menu ... ");
		int sw;
		fflush(stdin); scanf("%d", &sw);
		
		while (sw != 0 && (!Trung_Ten(NV[sw-1].Ten, Ten_TimKiem) && NV[sw-1].Ma_NhanVien != Ms_TimKiem)) {
			printf("\nSTT nay khong co trong danh sach, vui long nhap lai! ");
			printf("\n\nNhap STT cua Nhan Vien de xem chi tiet, nhap 0 de tro ve Menu ... ");
			fflush(stdin); scanf("%d", &sw);
		}
		
		if (sw != 0) {
			NV[sw-1].In_ThongTin_ChiTiet(sw);
			printf("\n\nAn phim bat ky de tro lai danh sach...");
			fflush(stdin); getch();
			goto DanhSach;
		}
	}
	
}

void TimKiem_NhanVien() {
	
	int sw;
	do {
		system("cls");
		printf("\n\n >>> Tim kiem nhan vien <<< \n\n");
		printf("Chon kieu tim kiem: \n");
		printf("1. Tim theo ten\n");
		printf("2. Tim theo ma so\n");
		printf("3. Tro lai\n\n");
	luachon:
		printf("Nhap lua chon: ");
		fflush(stdin); scanf("%d", &sw);
		switch (sw) {
			case 1: TimKiem(1); break;
			case 2: TimKiem(2); break;
			case 3: return;
			default: goto luachon;
		}
	} while (true);
	
}

void Hoan_Doi(NhanVien &nv1, NhanVien &nv2) {
	NhanVien nv3 = nv1;
	nv1 = nv2; 
	nv2 = nv3;
}

int str_cmp(char *s1, char *s2) {
	while(*s1 != NULL && *s1 == *s2){
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

void SapXep(int c) {
	
	Kieu_SapXep = c;
	
	for (int i = 0; i < num; i++) {
		for (int j = i+1; j < num; j++) {
			if (c == 1) {
				if (str_cmp(NV[i].Ten, NV[j].Ten) > 0) {
					Hoan_Doi(NV[i], NV[j]);
				}
			}
			else if (c == 2) {
				if (NV[i].Ma_NhanVien > NV[j].Ma_NhanVien) {
					Hoan_Doi(NV[i], NV[j]);
				}
			}
			else if (c == 3) {
				if (NV[i].Bac_ChucVu < NV[j].Bac_ChucVu) {
					Hoan_Doi(NV[i], NV[j]);
				}
			}
			else if (c == 4) {
				if (str_cmp(NV[i].DonVi, NV[j].DonVi) > 0) {
					Hoan_Doi(NV[i], NV[j]);
				}
			}
		}
	}
	
}

void SapXep_DanhSach() {
	
	system("cls");
	printf("\n\n >>> Sap xep danh sach nhan vien <<< \n\n");
	printf("Chon kieu sap xep: \n");
	printf("1. Sap xep theo ten\n");
	printf("2. Sap xep theo ma so\n");
	printf("3. Sap xep theo chuc vu\n");
	printf("4. Sap xep theo don vi\n");
	printf("5. Tro lai\n\n");
	
luachon:
	int sw;
	printf("Nhap lua chon: ");
	fflush(stdin); scanf("%d", &sw);
	switch (sw) {
		case 1: SapXep(1); break;
		case 2: SapXep(2); break;
		case 3: SapXep(3); break;
		case 4: SapXep(4); break;
		case 5: return;
		default: goto luachon;
	}
	printf("\nDa sap xep xong! Nhan phim bat ky de tro lai Menu ...");
	fflush(stdin); getch();
	
}

void Them_NhanVien_DaSapXep() {
	
	system("cls");
	printf("\n\n >>> Them nhan vien vao danh sach da sap xep <<< \n\n");
	NhanVien nv;
	Nhap_ThongTinNhanVien(nv);
	int idx = -1;
	
	for (int i = 0; i < num; i++) {
		if (Kieu_SapXep == 1) {
			if (str_cmp(NV[i].Ten, nv.Ten) > 0 && str_cmp(NV[i+1].Ten, nv.Ten) < 0) {
				idx = i;
				break;
			}
		}
		else if (Kieu_SapXep == 2) {
			if (nv.Ma_NhanVien > NV[i].Ma_NhanVien && nv.Ma_NhanVien < NV[i+1].Ma_NhanVien) {
				idx = i;
				break;
			}
		}
		else if (Kieu_SapXep == 3) {
			if (nv.Bac_ChucVu > NV[i].Bac_ChucVu && nv.Bac_ChucVu < NV[i+1].Bac_ChucVu) {
				idx = i;
				break;
			}
		}
		else if (Kieu_SapXep == 4) {
			if (str_cmp(NV[i].DonVi, nv.DonVi) > 0 && str_cmp(NV[i+1].DonVi, nv.DonVi) < 0) {
				idx = i;
				break;
			}
		}
	}
	
	num++;
	for (int i = num-1; i >= idx+2; i--) {
		NV[i] = NV[i-1];
	}
	
	NV[idx+1] = nv;
	CapNhat_DuLieu();
	printf("\nDa them xong! Nhan phim bat ky de tro lai Menu ...");
	fflush(stdin); getch();
	
}


void Xoa(int c) {
	
	int dem = 0, ok = 0;
	long int Ms_Xoa, Stt_Xoa;
	char Ten_Xoa[20];
	
	if (c == 1) {
		printf("\nNhap ten can xoa: ");
		fflush(stdin); gets(Ten_Xoa);
	}
	else if (c == 2) {
		printf("\nNhap ma so can xoa: ");
		fflush(stdin); scanf("%ld", &Ms_Xoa);
	}
	else {
		printf("\nNhap stt can xoa: ");
		fflush(stdin); scanf("%ld", &Stt_Xoa);
	}
	
	if (c == 1) {
		int KiemTra_Xoa[MAX];
		for (int i = 0; i < num; i++) {
			if (Trung_Ten(NV[i].Ten, Ten_Xoa)) {
				KiemTra_Xoa[i] = 1;
			}
			else KiemTra_Xoa[i] = 0;
		}
		
		int idx1 = 0, idx2 = 0;
		while (idx1 < num) {
			if (KiemTra_Xoa[idx1] == 0) {
				NV[idx2] = NV[idx1];
				idx2++;
			}
			idx1++;
		}
		num = idx2;
	}
	else {
		for (int i = 0; i < num; i++) {
			if (ok) {
				NV[i] = NV[i+1];
				continue;
			}
			if (c == 2 && NV[i].Ma_NhanVien == Ms_Xoa) {
				ok = 1;
				i--;
			}
			else if (c == 3 && i+1 == Stt_Xoa) {
				ok = 1;
				i--;
			}
		}
		num--;
	}
	CapNhat_DuLieu();
	
}

void Xoa_NhanVien() {
	
	system("cls");
	printf("\n\n >>> Xoa nhan vien <<< \n\n");
	printf("Xoa nhan vien bang: \n");
	printf("1. Ten\n");
	printf("2. Ma so\n");
	printf("3. STT\n");
	printf("4. Tro lai\n\n");
	
luachon:
	int sw;
	printf("Nhap lua chon: ");
	fflush(stdin); scanf("%d", &sw);
	switch (sw) {
		case 1: Xoa(1); break;
		case 2: Xoa(2); break;
		case 3: Xoa(3); break;
		case 4: return;
		default: goto luachon;
	}
	printf("\nDa xoa xong! Nhan phim bat ky de tro lai Menu ...");
	fflush(stdin); getch();
}

void Xoa_NhanVien_Tren50t() {
	
	system("cls");
	printf(" >>> Xoa nhan vien tren 50 tuoi <<< \n");
	
	int KiemTra_Xoa[MAX];
	for (int i = 0; i < num; i++) {
		if (NV[i].Tuoi >= 50) {
			KiemTra_Xoa[i] = 1;
		}
		else KiemTra_Xoa[i] = 0;
	}
	
	int idx1 = 0, idx2 = 0;
	while (idx1 < num) {
		if (KiemTra_Xoa[idx1] == 0) {
			NV[idx2] = NV[idx1];
			idx2++;
		}
		idx1++;
	}
	num = idx2;
	
	printf("\nDa xoa xong! Nhan phim bat ky de tro lai Menu ...");
	fflush(stdin); getch();
	CapNhat_DuLieu();
	
}


void In_DanhSach_DonVi() {
	
	system("cls");
	SapXep(4);
	int dem = 1;
	char *s1 = NV[0].DonVi;
		
	printf("\n\n\t >>> Danh sach cac don vi <<<\n\n");
	
	printf(" STT  |DON VI      |SO NV NAM  |SO NV NU  |TONG THUC LINH\n");
	printf("   ---------------------------------------------------\n");
	for (int i = 0; i < num; i++) {
		int nam = 0, nu = 0, sum = 0;
		while (strcmp(NV[i].DonVi, s1) == 0) {
			if (NV[i].GioiTinh == 1) nam++;
			else nu++;
			sum += NV[i].ThucLinh;
			i++;
			if (i > num) break;
		}
		printf("   %-3d %-15s %-12d %-8d %-8d\n", dem++, s1, nam, nu, sum);
		s1 = NV[i].DonVi;
	}
	printf("   ---------------------------------------------------\n");
	
	printf("\nNhan phim bat ky de tro lai Menu ...");
	fflush(stdin); getch();
}



