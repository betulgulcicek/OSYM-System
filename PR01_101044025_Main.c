
#include "PR01_101044025.h"


void universityMenu()
{
	int	choice = 0;

	do
	{
		system( "cls" );

		printf( "\nOgrenci Yerlestirme Programi\n" );
		printf( "------------------\n\n" );

		printf("\nUniversite Islemleri:\n"
			"\t1. Yeni universite ekleme\n"
			"\t2. Universite kaydi silme\n"
			"\t0. Exit\n"
			"Seciminizi giriniz : ");
		scanf("%d" , &choice);


		switch (choice)
		{
			case 1:
				insertNewUniversity();
				break;

			case 2:
			deleteUniversity();
				break;

			case 0:	
				break;

			default:	
				break;
		}


	} while (choice != 0);

}


void departmentMenu()
{
	int	choice = 0;

	do
	{
		system("cls");

		printf("\nOgrenci Yerlestirme Programi\n");
		printf("------------------\n\n");

		printf("\nDepartman Islemleri:\n"
			"\t1. Yeni departman ekleme\n"
			"\t2. Departman kaydi silme\n"
			"\t0. Exit\n"
			"Seciminizi giriniz : ");
		scanf("%d", &choice);


		switch (choice)
		{
			case 1:
				insertNewDepartment();
				break;

			case 2:
				deleteDepartment();
				break;

			case 0:	
				break;

			default:	
				break;
		}


	}while(choice != 0);
}


void informationMenu()
{
	int	choice = 0;

	do
	{
		system("cls");

		printf("\nOgrenci Yerlestirme Programi\n");
		printf("------------------\n\n");

		printf("\nBilgi Goruntuleme:\n"
			"\t1. Ogrenci ad soyad girerek puan goruntuleme\n"
			"\t2. Ogrenci ad soyad girerek yerlestirildigi bolumu goruntuleme\n"
			"\t3. TCKN girerek puan goruntuleme\n"
			"\t4. TCKN girerek yerlestirildigi bolumu goruntuleme\n"
			"\t5. Butun universiteleri ve toplam kotalarini goruntuleme\n"
			"\t6. Bir universitenin bolumlerini goruntuleme\n"
			"\t7. Bir bolumun yerlestirme istatistiklerini goruntuleme\n"
			"\t8. Bir universitenin yerlestirme istatistiklerini goruntuleme\n"
			"\t9. Sinav istatistiklerini goruntuleme\n"
			"\t0. Exit\n"
			"Seciminizi giriniz : ");
		scanf("%d", &choice);


		switch (choice)
		{
			case 1:
				displayScoreByName();
				break;

			case 2:
				displayPlacementByName();
				break;

			case 3:
				displayScoreById();
				break;

			case 4:
				displayPlacementById();
				break;

			case 5:
				displayAllUnis();
				break;

			case 6:
				displayDepartmentsOfUni();
				break;

			case 7:
				displayPlacementStatsOfDep();
				break;

			case 8:
				displayPlacementStatsOfUni();
				break;

			case 9:
				displayExamStats();
				break;

			case 0:	
				break;

			default:	
				break;
		}

	}while(choice != 0);
}



int main()
{
	studentsNames		*pStudentNameList = NULL , *pStd , *pStdNext;
	studentsAddressInfo	*pAddressInfoList = NULL , *pAddr , *pAddrNext;
	departments			*pDepartmentsList = NULL , *pDep , *pDepNext;
	preferences			*pPreferencesList = NULL , *pPref , *pPrefNext;
	scores				*pScoresList = NULL , *pScr , *pScrNext;
	int	choice = 0;


	/* csv dosyalarini oku */
	readCsvFiles( &pStudentNameList , &pAddressInfoList , &pDepartmentsList , &pPreferencesList , &pScoresList );


	/* binary database dosyalarini olustur */
	createBinaryDbFiles( pStudentNameList , pAddressInfoList , pDepartmentsList , pPreferencesList , pScoresList );


	/* bu listelerle isimiz kalmadi. hafizayi bosalt */

	pStd = pStudentNameList;
	while(pStd != NULL)
	{
		pStdNext = pStd -> next;
		free(pStd);
		pStd = pStdNext;
	}

	pAddr = pAddressInfoList;
	while(pAddr != NULL)
	{
		pAddrNext = pAddr -> next;
		free(pAddr);
		pAddr = pAddrNext;
	}

	pDep = pDepartmentsList;
	while(pDep != NULL)
	{
		pDepNext = pDep -> next;
		free(pDep);
		pDep = pDepNext;
	}

	pPref = pPreferencesList;
	while(pPref != NULL)
	{
		pPrefNext = pPref -> next;
		free(pPref);
		pPref = pPrefNext;
	}

	pScr = pScoresList;
	while(pScr != NULL )
	{
		pScrNext = pScr -> next;
		free(pScr);
		pScr = pScrNext;
	}



	/* ana menu */
	do
	{
		system("cls");

		printf("\nOgrenci Yerlestirme Programi\n");
		printf("------------------\n\n");

		printf("\nAna Menu:\n"
			"\t1. Universite islemleri\n"
			"\t2. Departman islemleri\n"
			"\t3. Ogrenci yerlestirmeyi gerceklestirme\n"
			"\t4. Bilgi goruntuleme\n"
			"\t0. Exit\n"
			"Seciminizi giriniz : ");
		scanf("%d", &choice);


		switch(choice)
		{
			case 1:
				universityMenu();
				break;

			case 2:
				departmentMenu();
				break;

			case 3:
				/* yerlestirmeyi gerceklestir */
				doPlacement();
				break;

			case 4:
				informationMenu();
				break;

			case 0:	
				break;

			default:	
				break;
		}
	}while(choice != 0);


	return 0;
}
