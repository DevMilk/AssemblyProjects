#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "image_processing.cpp"
using namespace std;

void SteganografiBul(int n, int resimadres_org, int resimadres_ste, int steganografi_adres);

int main(void) {
	int M, N, Q, i, j;
	bool type;
	int efile;
	char org_resim[100], ste_resim[100], steganografi[100];
	do {
		printf("Orijinal resmin yolunu (path) giriniz:\n-> ");
		scanf("%s", &org_resim);
		system("CLS");
		efile = readImageHeader(org_resim, N, M, Q, type);
	} while (efile > 1);
	int** resim_org = resimOku(org_resim);

	do {
		printf("Steganografik resmin yolunu (path) giriniz:\n-> ");
		scanf("%s", &ste_resim);
		system("CLS");
		efile = readImageHeader(ste_resim, N, M, Q, type);
	} while (efile > 1);
	int** resim_ste = resimOku(ste_resim);

	printf("Orjinal Resim Yolu: \t\t\t%s\n", org_resim);
	printf("SteganografiK Resim Yolu: \t\t%s\n", ste_resim);

	short *resimdizi_org, *resimdizi_ste;
	resimdizi_org = (short*) malloc(N*M * sizeof(short));
	resimdizi_ste = (short*) malloc(N*M * sizeof(short));

	for (i = 0; i < N; i++) 
		for (j = 0; j < M; j++) {
			resimdizi_org[i*N + j] = (short) resim_org[i][j];
			resimdizi_ste[i*N + j] = (short) resim_ste[i][j];
		}

	int resimadres_org = (int) resimdizi_org;
	int resimadres_ste = (int) resimdizi_ste;
	int steganografi_adres = (int) steganografi;

	SteganografiBul(N*M, resimadres_org, resimadres_ste, steganografi_adres);

	printf("\nResim icerisinde gizlenmis kod: \t%s\n", steganografi);
	system("PAUSE");
	return 0;
}

void SteganografiBul(int n, int resim_org, int resim_ste, int steganografi_adres) {
	__asm {

		//KODUNUZU BURAYA YAZINIZ, ASAGIDAKI 2 SATIRI SILMELISINIZ
		//Eðer ascii normalinen küçükse 256? ile topla orijinalinden farkýný bul
		//Eðer ascii mormalinden büyükse direk farkýný bul
		/*ALGORÝTMA ÞÖYLE OLACAK:
		 SHORT 2 BYTE -> 16 BÝT-> AX -> WORD
				
		*/
		XOR ESI,ESI //karþýlaþtýrma orijinal adresi
		XOR EDI,EDI //atýlacak dizinin adresi
		XOR ECX,ECX //karþýlaþtýrma sahte adres
		MOV EDI, steganografi_adres

		/*MOV ESI, resim_org
		MOV ECX, resim_ste*/

		Satir:
			XOR EAX,EAX

			MOV EAX, resim_org
			ADD EAX,ECX
			MOV AX, WORD PTR [EAX] //120 100 AX'DEN BX'Ý ÇIKAR ONU DA 255DEN ÇIKAR

			MOV EBX, resim_ste
			ADD EBX, ECX
			MOV BX,  WORD PTR [EBX]

 			CMP AX,BX
			
			JZ NOTHING
			JB FARK //Orijinal'den büyükse direk farkýný bul
					//Orijinalden küçükse 255 ile toplayýp farkýný bul
				SUB AL,BL
				MOV BX, 256
				XOR AH,AH
				SUB BX,AX
				MOV [EDI],BL
				INC EDI
				JMP NOTHING


			FARK: //al<bl
				SUB BL,AL
				MOV  [EDI], BL
				INC EDI
			NOTHING:
				INC ECX
				INC ECX
				INC ESI
				CMP ESI,n
				JNE Satir


		//YAZDIR
					MOV[EDI], '-'
		INC EDI
					MOV[EDI], '1'
		INC EDI
					MOV[EDI], '7'
		INC EDI
					MOV[EDI], '0'
		INC EDI
					MOV[EDI], '1'
		INC EDI
					MOV[EDI], '1'
		INC EDI
					MOV[EDI], '0'
		INC EDI
					MOV[EDI], '4'
		INC EDI
					MOV[EDI], '4'
		INC EDI
					MOV[EDI],'\0'
	}
}
