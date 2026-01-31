#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const int maxSize = 100;  
enum TrangThai { CHOPHEDUYET, DADUYET, HUY, HOANTHANH };

//Cau truc du lieu don hang
struct DonHang {
    string maDonHang;
    string ngayTao;
    double tongTien;
    string tenKhachHang;
    TrangThai trangThai;
};

//Cau truc node
struct Node {
    DonHang data;
    Node* next;
};

//Cau truc Queu
struct Queue {
    Node* front; 
    Node* back; 
    int count;   
};
//Hàm hiển thị thông tin đơn hàng
string trangThaiToString(TrangThai tt) {
    switch(tt) {
        case CHOPHEDUYET: return "Cho phe duyet";
        case DADUYET: return "Da duyet";
        case HUY: return "Huy";
        case HOANTHANH: return "Hoan thanh";
        default: return "Khong xac dinh";
    }
}
//1)
//Khoi tao Queue
void initQueue (Queue& q){
    q.front = q.back = NULL;
    q.count = 0;
}
//Kiem tra Queue co rong khong
bool isEmpty (const Queue& q){
    return q.front == NULL;
}

// Tao don hang(Them vao cuoi Queue)
void enQueue(Queue& q) {
    DonHang dh;
    cout << "\n--- NHAP THONG TIN DON HANG ---\n";
    cout << "Nhap ma don hang: "; cin >> dh.maDonHang;
    cin.ignore();
    cout << "Nhap ngay tao (VD: 01/01/2026): "; getline(cin, dh.ngayTao);
    cout << "Nhap ten khach hang: "; getline(cin, dh.tenKhachHang);
    cout << "Nhap tong tien: "; cin >> dh.tongTien;
    dh.trangThai = CHOPHEDUYET;

    Node* newNode = new Node;
    newNode->data = dh;
    newNode->next = NULL;
    if (isEmpty(q)) {
        q.front = q.back = newNode;
    }
    else {
        q.back->next = newNode;
        q.back = newNode;
    }
    q.count++;
    cout << "Them don hang thanh cong!\n";
}

//Tim kiem theo id
Node* searchById(Queue &s, string id){
    Node *t = s.front;
    while(t!=NULL) {
        if(t->data.maDonHang==id){
            break;
        }
        t = t->next;
    }
    return t;
}
//Xoa don hang
bool removeDonHang(Queue &q, Node *x) {
    //Danh sach rong
    if (q.front == NULL || x == NULL) return false;
    //Xoa node dau
    if (x == q.front) {
        q.front = q.front->next;
       //Danh sach chi co 1 don hang
        if (q.front == NULL) q.back = NULL; 
        delete x;
        q.count--;
        return true;
    }
    //Tim don hang truoc don hang x
     Node* s = q.front;
    while (s != NULL && s->next != x) s = s->next;
    if (s == NULL) return false;
    else {//Xoa node giua hoac cuoi
        s->next = x->next;
        if (x == q.back) q.back = s;
        delete x;
        q.count--;
        return true;
    }
}

//Ham hien thi 1 don hang
void hienThiDonHang(const DonHang& dh) {
    cout << "| " << left << setw(12) << dh.maDonHang;
    cout << "| " << left << setw(12) << dh.ngayTao;     
    cout << "| " << left << setw(20) << dh.tenKhachHang;
    cout << "| " << left << setw(12) << dh.tongTien;
    cout << "| " << left << setw(14) << trangThaiToString(dh.trangThai) << " |" << endl; 
}
void khungChuongTrinh(){
    cout <<"| "<<left<<setw(12)<<"Ma don hang";
    cout <<"| "<<left<<setw(12)<<"Ngay tao";
    cout <<"| "<<left<<setw(20)<<"Ten khach hang";
    cout <<"| "<<left<<setw(12)<<"Tong tien";
    cout <<"| "<<left<<setw(14)<<"Trang thai"<<" |"<<endl;
}
//Xem don hang
void showQueue (const Queue& q){
    if (isEmpty(q)){
        cout<<"Hien tai khong co don hang nao trong danh sach!"<<endl;
    }
    cout << "==========================================================================================\n";
    cout<<"                                 DANH SACH TAT CA DON HANG\n";
    cout <<"| "<<left<<setw(5)<<"STT";
    khungChuongTrinh();
    cout << "==========================================================================================\n";
    Node* current = q.front;
    int stt = 1;
    while (current != NULL){
        cout <<"| "<<left<<setw(5)<<stt++;
        hienThiDonHang(current->data);
        current = current->next;
    }	 
    cout << "==========================================================================================\n";
    cout<<"Tong so co "<<q.count<<" don hang\n";
}

//Hàm thay đổi trạng thái đơn hàng
void thayDoiTrangThai(Queue &dh) {
    if (isEmpty(dh)) {
        cout << "Danh sach rong!\n";
        return;
    }
    string ma;
    cout << "Nhap ma don hang can xu ly: "; cin >> ma;
    Node* p = searchById(dh, ma); 
    if (p == NULL) {
        cout << "Khong tim thay don hang co ma: " << ma << endl;
    } 
    else {
        cout << "Trang thai hien tai: " << trangThaiToString(p->data.trangThai) << endl;
        cout << "Chon trang thai moi (1: Da duyet, 2: Huy, 3: Hoan thanh): ";
        int chon; cin >> chon;
        bool hopLe = true;
        switch (chon) {
            case 1: p->data.trangThai = DADUYET; break;
            case 2: p->data.trangThai = HUY; break;
            case 3: p->data.trangThai = HOANTHANH; break;
            default: 
                cout << "Lua chon khong hop le, giu nguyen trang thai.\n"; 
                hopLe = false;
        }
        if(hopLe) cout << "=> Cap nhat trang thai thanh cong!\n";
    }
}

//Thong ke don hang
void thongKeDonHang(Queue q) {
    if (isEmpty(q)) {
        cout << " Chua co du lieu de thong ke don hang!\n";
        return;
    }
    int tongDH = 0;
    double tongGiaTri = 0;
    int theoTrangThai[4] = {0};

    Node* p = q.front;
    while (p != nullptr) {
        tongDH++;
        tongGiaTri += p->data.tongTien;
        theoTrangThai[p->data.trangThai]++;
        p = p->next;
    }

    cout << "\n=== Thong ke don hang ===\n";
    cout << " Tong so don hang: " << tongDH << endl;
    cout << " Tong gia tri: " << (long long)tongGiaTri << endl;
    cout << " Theo trang thai:\n";
    cout << " Cho phe duyet: " << theoTrangThai[CHOPHEDUYET] << endl;
    cout << " Da duyet: " << theoTrangThai[DADUYET] << endl;
    cout << " Huy: " << theoTrangThai[HUY] << endl;
    cout << " Hoan thanh: " << theoTrangThai[HOANTHANH] << endl;
}

//Tim ds don hang theo ngay tao
void searchByDay(Queue q) {
    string ngay;
    cout << "Nhap ngay can tim: ";
    getline(cin, ngay);
    
    Node* p = q.front;
    bool co = false;
    cout << "\nKet qua tim kiem ngay " << ngay << ":\n";
    khungChuongTrinh();
    cout << "==========================================================================================\n";
    while (p != NULL) {
        if (p->data.ngayTao == ngay) {
            hienThiDonHang(p->data);
            co = true;
        }
        p = p->next;
    }
    cout << "==========================================================================================\n";
    if (!co) cout << "Khong tim thay don hang!\n";
}
//Xem danh sach don hang theo trang thai don hang
void xemDanhSachDonHangTheoTrangThai(Queue q) {
    if (q.front == NULL) {
        cout << "Danh sach don hang rong!\n";
        return;
    }
    int tt;
    cout << "Nhap trang thai can xem:\n";
    cout << "0. Cho phe duyet\n";
    cout << "1. Da duyet\n";
    cout << "2. Huy\n";
    cout << "3. Hoan thanh\n";
    cout << "Chon: ";
    cin >> tt;
    if (tt < 0 || tt > 3) {
        cout << "Lua chon khong hop le!\n";
        return;
    }
    Node* p = q.front;
    bool timThay = false;
    cout << "==========================================================================================\n";
    cout << "                    DANH SACH DON HANG LOC THEO TRANG THAI ===\n";
    cout << "==========================================================================================\n";
 	khungChuongTrinh();
    cout << "==========================================================================================\n";
    while (p != NULL) {
        if (p->data.trangThai == (TrangThai)tt) {
           hienThiDonHang(p->data);
            timThay = true;
        }
        p = p->next;
    }
    cout << "==========================================================================================\n";
    if (!timThay) {
        cout << "Khong co don hang nao o trang thai nay!\n";
    }
}

int main() {
    Queue q;
    initQueue(q);
    
    int choice;
    do {
        cout << "\n================ MENU QUAN LY DON HANG ================\n";
        cout << "1. Tao don hang moi\n";
        cout << "2. Xem danh sach tat ca don hang\n";
        cout << "3. Xu ly don hang (Thay doi trang thai)\n";
        cout << "4. Xoa don hang (Theo Ma ID)\n";
        cout << "5. Thong ke don hang\n";
        cout << "6. Tim don hang theo Ngay\n";
        cout << "7. Xem danh sach theo Trang thai\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "=======================================================\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            enQueue(q);
            break;
        case 2:
            showQueue(q);
            break;
        case 3:
            thayDoiTrangThai(q);
            break;
        case 4: {
            string idXoa;
            cout << "Nhap ma don hang can xoa: ";
            cin >> idXoa;
            Node* nodeXoa = searchById(q, idXoa);
            if (nodeXoa != NULL) {
                removeDonHang(q, nodeXoa);
                cout << "=> Da xoa don hang " << idXoa << " thanh cong!\n";
            }
            else {
                cout << "=> Khong tim thay ma don hang!\n";
            }
            break;
        }
        case 5:
            thongKeDonHang(q);
            break;
        case 6:
            cin.ignore();
            searchByDay(q);
            break;
        case 7:
            xemDanhSachDonHangTheoTrangThai(q);
            break;
        case 0:
            cout << "Thoat chuong trinh thanh cong\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);

    return 0;
}
