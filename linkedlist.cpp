#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct Mahasiswa{
	char nim[15];
	char nama[30];
	float ipk;
};

struct Elemen{
	Mahasiswa mhs;
	Elemen *next;
};

struct List{
	Elemen *first;
	Elemen *last;
};

void addFirst(char nim[], char nama[], float ipk, List *L);
void addAfter(Elemen *prev, char nim[], char nama[], float ipk, List *L);
void addLast(char nim[], char nama[], float ipk, List *L);

void deleteFirst(List *L);
void deleteAfter(Elemen *prev, List *L);
void deleteLast(List *L);

void showData(List *L);

Elemen *searchData(char nim[], List *L);
Mahasiswa inputMahasiswa();
char *searchNim();

int main(){
	char option;
	
	List L;
	L.first = NULL;
	
	Mahasiswa data;
	Elemen *prev;
	
	int menu = 0;
	int pos = 0;
	
	do{
		system("cls");
		printf("+++ LINKED LIST +++\n");
		printf("1. Input Data (Depan)\n");
		printf("2. Input Data (Setelah)\n");
		printf("3. Input Data (Akhir)\n");
		printf("4. Hapus Data (Depan)\n");
		printf("5. Hapus Data (Setelah)\n");
		printf("6. Hapus Data (Akhir)\n");
		printf("7. Tampilkan Data\n");
		printf("8. Search Data\n");
		printf("9. Exit\n");
		printf("github.com/znladnsyh\n");
		
		printf("Pilih Menu : ");
		scanf("%d", &menu);
//				fflush(stdin)
		
		switch(menu){
			case 1:
				data = inputMahasiswa();
				addFirst(data.nim, data.nama, data.ipk, &L);
				break;
				
			case 2:
				prev = searchData(searchNim(), &L);
				if(prev != NULL){
					data = inputMahasiswa();
					addAfter(prev, data.nim, data.nama, data.ipk, &L);
				}
				break;
				
			case 3:
				data = inputMahasiswa();
				addLast(data.nim, data.nama, data.ipk, &L);
				break;
				
			case 4:
				deleteFirst(&L);
				break;
				
			case 5:
				prev = searchData(searchNim(), &L);
				if(prev != NULL){
					deleteAfter(prev, &L);
				}
				break;
				
			case 6:
				deleteLast(&L);
				break;
				
			case 7:
				showData(&L);
				break;
				
			case 8:
				searchData(searchNim(), &L);
				break;
				
			case 9:
				printf("Keluar Program!!");
				break;	
				
			default:
				printf("Invalid Input!!");
				break;	
		}
		printf("\n");
		
	   printf("Press any key to continue...\n");
	   getch();
	
	}while(menu!=9);
	
	return 0;
}

void addFirst(char nim[], char nama[], float ipk, List *L){
	Elemen *baru = new Elemen;
	
	strcpy(baru->mhs.nim, nim);
	strcpy(baru->mhs.nama, nama);
	baru->mhs.ipk = ipk;
	
	if(L->first == NULL){
		L->first = baru;
		baru->next = NULL;
		L->last = baru;
	}else{
		baru->next = L->first;
		L->first = baru;
	}
	
	
	baru = NULL;
	printf("\nBerhasil ditambahkan!");
}

void addAfter(Elemen *prev, char nim[], char nama[], float ipk, List *L){
	Elemen *baru = (Elemen*) malloc (sizeof(Elemen));
	
	strcpy(baru->mhs.nim, nim);
	strcpy(baru->mhs.nama, nama);
	baru->mhs.ipk = ipk;
	
	baru->next = prev->next;
	prev->next = baru;
	
	if(baru->next == NULL){
		L->last = baru;
	}
	
	baru = NULL;
	printf("\nBerhasil ditambahkan!");
}

void addLast(char nim[], char nama[], float ipk, List *L){
	Elemen *baru = (Elemen*) malloc (sizeof(Elemen));
	
	strcpy(baru->mhs.nim, nim);
	strcpy(baru->mhs.nama, nama);
	baru->mhs.ipk = ipk;
	
	if(L->first == NULL){
		L->first = baru;
		L->last = baru;
		baru->next = NULL;
	}else{
		L->last->next = baru;
		L->last = baru;
		baru->next = NULL;
	}
	
	baru = NULL;
	printf("\nBerhasil ditambahkan!");
}

void deleteFirst(List *L){
	Elemen *data = L->first;
	L->first = data->next;

	free(data);
	
	printf("\nBerhasil dihapus!");
}

void deleteAfter(Elemen *prev, List *L){
	Elemen *data = prev->next;
	prev->next = data->next;
	
	if(prev->next == NULL){
		L->last = prev;
	}
	
	free(data);
	
	printf("\nBerhasil dihapus!");
}

void deleteLast(List *L){
	Elemen *data = NULL;
	Elemen *prev = NULL;
	Elemen *pNow = L->first;
	
	while(pNow != NULL){
		prev = data;
		data = pNow;
		pNow = pNow->next;
	}
	
	if(prev == NULL){
		L->first = NULL;
		L->last = NULL;
	}else{
		prev->next = NULL;
		L->last = prev;	
	}
	
	free(data);
	
	printf("\nBerhasil dihapus!");
}

void showData(List *L){
	Elemen *pnow = L->first;
	if(pnow == NULL){
		printf("\nAnda belum menambahkan data!\n");
	}else{
		printf("\nIsi Data");
		int no = 0;
		while(pnow != NULL){
			no++;
	    	printf("\n\nMahasiswa ke-%d", no);
	    	printf("\nNIM : %s", pnow->mhs.nim);
	    	printf("\nNama : %s", pnow->mhs.nama);
	    	printf("\nIpk : %.2f", pnow->mhs.ipk);
			pnow = pnow->next;
		}
	}
}

Elemen *searchData(char nim[], List *L){
	int no = 0;
	Elemen *pnow = L->first;
	Elemen *result = NULL;
	if(pnow == NULL){
		printf("\nAnda belum menambahkan data!\n");
	}else{
		while(pnow != NULL){
			no++;
			if(strcmp(pnow->mhs.nim,nim) == 0){
				result = pnow;
				pnow = NULL;
			}else{
				pnow = pnow->next;
			}
		}
	}
	
	if(result == NULL){
		printf("Data tidak ditemukan!");
	}else{
		printf("Data ditemukan pada posisi ke-%d!",no);
	}
	
	return result;
}

Mahasiswa inputMahasiswa(){
	Mahasiswa data;
	
	printf("\nNIM : ");
	scanf("%s",&data.nim);
	
	printf("Nama : ");
	scanf("%s",&data.nama);
	
	printf("Ipk : ");
	scanf("%f",&data.ipk);
	
	return data;
}

char *searchNim(){
	Mahasiswa data;
	printf("\nCari data (NIM) : ");
	scanf("%s",&data.nim);
	return data.nim;
}
