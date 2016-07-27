
#include "PR01_101044025.h"


/* bu fonksiyon stdin'i bosaltir */
/* getchar ve gets fonksiyonlarini duzgun kullanabilmek icin;
 * hemen oncesinde stdin'i bosaltmak gerekir */
void flushStdin()
{
	int ch;
	do
	{
		ch = fgetc(stdin);
	} while (ch != EOF && ch != '\n');
	clearerr(stdin);
}


/* bu fonksiyon enter basilana kadar bekler */
void mypause()
{
	/* stdin'i bosalt */
	flushStdin();

	printf("Devam etmek icin Enter'a basiniz");
	fflush(stdout);
	getchar();
}


/* iki bigInt turunden nesnenin esit olup olmadigini kontrol eder
 * esitse TRUE, degilse FALSE doner */
int isEqualBigInts(bigInt *bi1, bigInt *bi2)
{
	if(bi1->lspart == bi2->lspart && bi1->mspart == bi2->mspart)
	{
		return TRUE;
	}

	return FALSE;
}


/* string olarak verilen sayiyi, bigInt yapisina donusturur */
void stringToBigInt(char *str, bigInt *bi)
{
	unsigned int i, j, len;
	char strMsHalf[16], strLsHalf[16];

	memset( strMsHalf, 0, sizeof(strMsHalf));
	memset( strLsHalf, 0, sizeof(strLsHalf));

	len = strlen(str);

/* string olarak verilen sayinin son 8 karakterini strLsHalf'a yazacagiz,
bastaki karakterden sondan 8.karaktere olan kismini da strMsHalf'a yazacagiz */
	for(i=0; i < len-8; ++i)
	{
		strMsHalf[i]=str[i];
	}

	for(i=0, j=len-8; j<len; ++i, ++j)
	{
		strLsHalf[i]=str[j];
	}


	bi -> lspart = atoi(strLsHalf);
	bi -> mspart = atoi(strMsHalf);
}


/* bigInt yapisini string'e donusturur */
char *bigIntToString(bigInt *bi)
{
	char *str;

	str = (char*)malloc(32);

	sprintf(str, "%d%8d", bi->mspart, bi->lspart);

	return str;
}


/* belirli bir dosyadan satir satir okuma yapar 
 * (newline karakter gorene kadar okur) */
int readLine(FILE *f, char *buf, unsigned int bufSize)
{
	char c;
	unsigned int i;

	memset(buf, 0, bufSize);
	
	for(i=0; i<bufSize; i++)
	{
		c=fgetc(f);

		if(!feof(f))
		{
			if(c == '\r')
			{
				buf[i]=0;
			}
			else if(c == '\n')
			{
				buf[i]=0;

				return i+1;
			}
			else
			{
				buf[i]=c;
			}
		}
		else
		{
			return -1;
		}
	}

	return -1;
}


/* StudentsNames.csv dosyasindan okunan bir satiri bolumlere ayirir */
void parseStudentName(studentsNames *stdPtr, char *buffer, unsigned int bufLen)
{
	char stdId[16], bday[8], bmonth[8], byear[8];
	unsigned int i, j;


	/* ogrenci nosunu al */
	memset(stdId, 0, sizeof(stdId));

	for(i=0; i<bufLen; i++)
	{
		if(buffer[i] == ';')
		{
			stdId[i]=0;

			stringToBigInt(stdId, &(stdPtr->id));
			break;
		}
		stdId[i]=buffer[i];
	}

	/* ogrenci adini oku */
	for(i++, j=0; i<bufLen; i++, j++)
	{
		if(buffer[i] == ';')
		{
			stdPtr->name[j]=0;
			break;
		}
		stdPtr->name[j]=buffer[i];
	}

	/* ogrenci soyadini oku */
	for(i++, j=0; i<bufLen; i++, j++)
	{
		if(buffer[i] == ';')
		{
			stdPtr -> surname[j]=0;
			break;
		}
		stdPtr->surname[j]=buffer[i];
	}

	/* ogrenci dogum tarihini oku - gun */
	memset(bday, 0, sizeof(bday));

	for(i++, j=0; i<bufLen; i++, j++)
	{
		if(buffer[i] == '.')
		{
			bday[j]=0;

			stdPtr->bday_day=atoi(bday);
			break;
		}
		bday[j]=buffer[i];
	}

	/* ogrenci dogum tarihini oku - ay */
	memset(bmonth, 0, sizeof(bmonth));

	for(i++, j=0; i<bufLen; i++, j++)
	{
		if(buffer[i] == '.')
		{
			bmonth[j]=0;

			stdPtr->bday_month=atoi(bmonth);
			break;
		}

		bmonth[j]=buffer[i];
	}

	/* ogrenci dogum tarihini oku - yil */
	memset(byear, 0, sizeof(byear));

	for(i++, j=0; i<bufLen; i++ ,j++)
	{
		if(buffer[i] == ';')
		{
			byear[j]=0;

			stdPtr->bday_year=atoi(byear);
			break;
		}
		byear[j]=buffer[i];
	}


	/* score type'i oku */
	i++;

	if(buffer[i] == 'Q')
	{
		stdPtr->scoreType=SCORE_TYPE_QUANTATIVE;
	}
	else
	{
		stdPtr->scoreType=SCORE_TYPE_VERBAL;
	}

}


/* StudentsAdress.csv dosyasindan okunan bir satiri bolumlere ayirir */
void parseStudentAddress(studentsAddressInfo *stdAddrPtr, char *buffer, unsigned int bufLen)
{
	char stdId[16], tel[16];
	unsigned int i, j;


	/* ogrenci nosunu al */
	memset(stdId, 0, sizeof(stdId));

	for (i=0; i<bufLen; i++)
	{
		if(buffer[i] == ';')
		{
			stdId[i]=0;

			stringToBigInt(stdId, &(stdAddrPtr->id));
			break;
		}

		stdId[i]=buffer[i];
	}


	/* ogrenci telefon nosunu al */
	memset(tel, 0, sizeof(tel));

	for (i++, j=0; i<bufLen; i++, j++)
	{
		if (buffer[i] == ';')
		{
			tel[j]=0;

			stringToBigInt(tel, &(stdAddrPtr->phone));
			break;
		}
		tel[j]=buffer[i];
	}


	/* ogrenci mail adresini oku */
	for (i++, j=0; i<bufLen; i++, j++)
	{
		if (buffer[i] == ';')
		{
			stdAddrPtr->email[j]=0;
			break;
		}
		stdAddrPtr->email[j]=buffer[i];
	}


	/* ogrenci ev adresini oku */
	for (i++, j=0; i<bufLen; i++, j++)
	{
		if (buffer[i] == ';')
		{
			stdAddrPtr->address[j]=0;
			break;
		}
		stdAddrPtr->address[j]=buffer[i];
	}
}

/* Departments.csv dosyasindan okunan bir satiri bolumlere ayirir */
void parseDepartment(departments *depPtr, char *buffer, unsigned int bufLen)
{
	char uniId[8], depId[8], quota[8];
	unsigned int i, j;


	/* university */
	for(i=0; i<bufLen; i++)
	{
		if(buffer[i] == ';')
		{
			depPtr->university[i]=0;
			break;
		}
		depPtr->university[i]=buffer[i];
	}


	/* UniId */
	memset(uniId, 0, sizeof(uniId));

	for(i++, j=0; i<bufLen; i++, j++)
	{
		if(buffer[i] == ';')
		{
			uniId[j]=0;

			depPtr->uniId=atoi(uniId);
			break;
		}
		uniId[j]=buffer[i];
	}


	/* department */
	for(i++, j=0; i<bufLen; i++, j++)
	{
		if(buffer[i] == ';')
		{
			depPtr->department[j]=0;
			break;
		}
		depPtr->department[j]=buffer[i];
	}



	/* DepId */
	memset(depId, 0, sizeof(depId));

	for(i++, j=0; i<bufLen; i++, j++)
	{
		if(buffer[i] == ';')
		{
			depId[j]=0;

			depPtr->depId=atoi(depId);
			break;
		}

		depId[j]=buffer[i];
	}


	/* score type */
	i++;

	if(buffer[i] == 'Q')
	{
		depPtr->scoreType=SCORE_TYPE_QUANTATIVE;
	}
	else
	{
		depPtr->scoreType=SCORE_TYPE_VERBAL;
	}

	i++;


	/* quota */
	memset(quota, 0, sizeof(quota));

	for(i++, j=0; i<bufLen; i++, j++)
	{
		if(buffer[i] == ';')
		{
			quota[j]=0;

			depPtr->quota=atoi(quota);
			break;
		}
		quota[j]=buffer[i];
	}
}


/* Preferences.csv dosyasindan okunan bir satiri bolumlere ayirir */
void parsePreference(preferences *prefPtr, char *buffer, unsigned int bufLen)
{
	char stdId[16], uniId[8], depId[8];
	unsigned int i, j, k;


	/* ogrenci nosunu al */
	memset(stdId, 0, sizeof(stdId));

	for(i=0; i<bufLen; i++)
	{
		if(buffer[i] == ';')
		{
			stdId[i]=0;

			stringToBigInt(stdId, &(prefPtr->studentId));
			break;
		}
		stdId[i]=buffer[i];
	}

	for(k=0; k<8; k++)
	{

		/* UniId */
		memset(uniId, 0, sizeof(uniId));

		for(i++, j=0; i<bufLen; i++, j++)
		{
			if(buffer[i] == ';')
			{
				uniId[j]=0;

				prefPtr->uniIds[k]=atoi(uniId);
				break;
			}
			uniId[j]=buffer[i];
		}


		/* DepId */
		memset(depId, 0, sizeof(depId));

		for(i++, j=0; i<bufLen; i++, j++)
		{
			if(buffer[i] == ';')
			{
				depId[j]=0;

				prefPtr->depIds[k]=atoi(depId);
				break;
			}
			depId[j]=buffer[i];
		}
	}
}


/* Scores.csv dosyasindan okunan bir satiri parse eder */
void parseScore(scores *scrPtr, char *buffer, unsigned int bufLen)
{
	char stdId[16], qscore[32], vscore[32];
	unsigned int i, j;


	/* ogrenci nosunu al */
	memset(stdId, 0, sizeof(stdId));

	for(i=0; i<bufLen; i++)
	{
		if(buffer[i] == ';')
		{
			stdId[i]=0;

			stringToBigInt(stdId, &(scrPtr->studentId));
			break;
		}
		stdId[i]=buffer[i];
	}

	/* quantative score */
	memset(qscore, 0, sizeof(qscore));

	for(i++, j=0; i<bufLen; i++, j++)				
	{
		if(buffer[i] == ';')
		{
			qscore[j]=0;

			scrPtr->quantativeScore=atof(qscore);
			break;
		}
		qscore[j]=buffer[i];
	}

	/* verbal score */
	memset(vscore, 0, sizeof(vscore));

	for(i++, j=0; i<bufLen; i++, j++)
	{
		if(buffer[i] == ';')
		{
			vscore[j]=0;

			scrPtr->verbalScore=atof(vscore);
			break;
		}
		vscore[j]=buffer[i];
	}
}


/* StudentsNames.csv, StudentsAddressInfo.csv, Deparments.csv, 
 * Preferences.csv, Scores.csv dosyalarini okur
 * bolumlere ayirir ve gerekli yapilari linked list seklinde olusturur */
void readCsvFiles(studentsNames **pStNames, studentsAddressInfo **pStAddr, 
				  departments **pDeps, preferences **pPref, scores **pScr)
{
	char buffer[2048];
	studentsNames *stdName, *lastStdName;
	studentsAddressInfo	*stdAddr, *lastStdAddr;
	departments	*dep, *lastDep;
	preferences	*pref, *lastPref;
	scores *scr, *lastScr;
	FILE *fStudentsName, *fStudentsAddressInfo, 
		 *fDepartments, *fPreferences, *fScores;
	int	length;


/* StudentsNames.csv, StudentsAddressInfo.csv, Deparments.csv, 
 * Preferences.csv, Scores.csv  dosyalarini oku
 * linked list structures olustur */

	fStudentsName = fopen("StudentsNames.csv", "r");

	/* ilk satiri oku ve gec */
	readLine(fStudentsName, buffer, sizeof(buffer));

	while((length=readLine(fStudentsName, buffer, sizeof(buffer))) != -1)
	{
		if(length <= 1)	/* dosyada fazladan bir newline olabiliyor */
		{
			continue;
		}

		stdName = (studentsNames*)malloc(sizeof(studentsNames));
		memset(stdName, 0, sizeof(studentsNames));

		parseStudentName(stdName, buffer, length);


		/* linked liste ekle */
		if(*pStNames == NULL)
		{
			*pStNames=stdName;
			lastStdName=stdName;
		}
		else
		{
			lastStdName->next=stdName;
			lastStdName=stdName;
			lastStdName->next=NULL;
		}


	}

	fclose(fStudentsName);


	fStudentsAddressInfo = fopen("StudentsAddressInfo.csv", "r");

	/* ilk satiri oku ve gec */					
	readLine(fStudentsAddressInfo, buffer, sizeof(buffer));
	
	while((length=readLine(fStudentsAddressInfo, buffer, sizeof(buffer))) != -1)
	{
		if(length <= 1)	/* fazladan bir newline olabiliyor */
		{
			continue;
		}

		stdAddr = (studentsAddressInfo*)malloc(sizeof(studentsAddressInfo));
		memset(stdAddr, 0, sizeof(studentsAddressInfo));


		parseStudentAddress(stdAddr, buffer, length);


		/* linked liste ekle */
		if(*pStAddr == NULL)
		{
			*pStAddr=stdAddr;
			lastStdAddr=stdAddr;
		}
		else
		{
			lastStdAddr->next=stdAddr;
			lastStdAddr=stdAddr;
			lastStdAddr->next=NULL;
		}

	}

	fclose(fStudentsAddressInfo);


	fDepartments = fopen("Departments.csv", "r");

	/* ilk satiri oku ve gec */
	readLine(fDepartments, buffer, sizeof(buffer));

	while((length=readLine(fDepartments, buffer, sizeof(buffer))) != -1)
	{
		if(length <= 1)	/* fazladan bir newline olabiliyor */
		{
			continue;
		}

		dep = (departments*)malloc(sizeof(departments));
		memset(dep, 0, sizeof(departments));


		parseDepartment(dep, buffer, length);

		/* linked liste ekle */
		if(*pDeps == NULL)
		{
			*pDeps=dep;
			lastDep=dep;
		}
		else
		{
			lastDep->next=dep;
			lastDep=dep;
			lastDep->next=NULL;
		}

	}

	fclose(fDepartments);


	fPreferences = fopen("Preferences.csv", "r");

	/* ilk satiri oku ve gec */
	readLine(fPreferences, buffer, sizeof(buffer));

	while((length=readLine(fPreferences, buffer, sizeof(buffer))) != -1)
	{
		if(length <= 1)	/* fazladan bir newline olabiliyor */
		{
			continue;
		}

		pref = (preferences*)malloc(sizeof(preferences));
		memset(pref, 0, sizeof(preferences));

		/* uni id ve dep id '0' olabildiginden dolayi, 
		 * uniIds ve depIds arraylarini -1 ile initialize ediyoruz */
		memset(pref->uniIds, -1, sizeof(pref->uniIds));
		memset(pref->depIds, -1, sizeof(pref->depIds));


		parsePreference(pref, buffer, length);

		/* linked liste ekle */
		if(*pPref == NULL)
		{
			*pPref=pref;
			lastPref=pref;
		}
		else
		{
			lastPref->next=pref;
			lastPref=pref;
			lastPref->next=NULL;
		}

	}

	fclose(fPreferences);


	fScores = fopen("Scores.csv", "r");

	/* ilk satiri oku ve gec */
	readLine(fScores, buffer, sizeof(buffer));

	while((length=readLine(fScores, buffer, sizeof(buffer))) != -1)
	{
		if(length <= 1)	/* fazladan bir newline olabiliyor */
		{
			continue;
		}

		scr = (scores*)malloc(sizeof(scores));
		memset(scr, 0, sizeof(scores));


		parseScore(scr, buffer, length);

		/* linked liste ekle */
		if(*pScr == NULL)
		{
			*pScr=scr;
			lastScr=scr;
		}
		else
		{
			lastScr->next=scr;
			lastScr=scr;
			lastScr->next=NULL;
		}
	}

	fclose(fScores);
}


/* binary database dosyalarini YOKSA olusturur */
void createBinaryDbFiles(studentsNames *pStNames, studentsAddressInfo *pStAddr, 
						 departments *pDeps, preferences *pPref, scores *pScr)
{
	departments	*pDepartment;
	studentsNames *pStudentName;
	studentsAddressInfo	*pAddressInfo;
	preferences	*pPreference;
	scores *pScore;
	departmentsDb *depsDbFirst=NULL, *depsDbLast=NULL, *depsDb;
	universitiesDb *unisDbFirst=NULL, *unisDbLast=NULL, *unisDb;
	depOfUniDb *depOfUniDbFirst=NULL, *depOfUniDbLast=NULL, *pDepOfUniDb ;
	studentsInfoDb *stinfoDbFirst=NULL, *stinfoDbLast=NULL, *stinfoDb;
	studentsPreferenceDb *stprefDbFirst=NULL, *stprefDbLast=NULL ,*stprefDb;
	unsigned int depsKeyId, unisKeyId, depOfUniKeyId, stdInfoKeyId, stdPrefKeyID;
	int	found=FALSE;


/* Binary database dosyalari var mi diye kontrol et */
	FILE *fDepartmentsDb =  fopen("departments.bin", "r");
	FILE *fUniversitiesDb =  fopen("universities.bin", "r");
	FILE *fDepofunisDb =  fopen("depofunis.bin", "r");
	FILE *fStudentsinfoDb =  fopen("studentsinfo.bin", "r");
	FILE *fStudentsprefDb =  fopen("studentspreference.bin", "r");

	if(fDepartmentsDb != NULL && fUniversitiesDb != NULL && fDepofunisDb != NULL 
		&& fStudentsinfoDb != NULL && fStudentsprefDb != NULL)
	{
		/* binary database dosyalari zaten var */

		fclose(fDepartmentsDb);
		fclose(fUniversitiesDb);
		fclose(fDepofunisDb);
		fclose(fStudentsinfoDb);
		fclose(fStudentsprefDb);
	}



/* dosyalar daha onceden olusturulmamis */
/* departments.bin, universities.bin, depofunis.bin (universitelerin departmanlari) 
 * binary db dosyalarini "write binary" modunda olustur */

	fDepartmentsDb = fopen("departments.bin", "wb");
	fUniversitiesDb = fopen("universities.bin", "wb");
	fDepofunisDb = fopen("depofunis.bin", "wb");

	depsKeyId=0;
	unisKeyId=0;
	depOfUniKeyId=0;

	pDepartment=pDeps;

	while(pDepartment != NULL)
	{
		/* her bir departments nesnesi icin;
		 * birer departmentsDb, universitiesDb, DepOfUni olustur
		 * keyId'leri ver
		 * dosyalara yaz
		 * keyId'leri increment et */


		/* bu department database listesinde var mi diye bak */
		depsDb=depsDbFirst;
		found=FALSE;
		while(depsDb != NULL)
		{
			if(pDepartment->depId == depsDb->depId)
			{
				found=TRUE;
				break;
			}

			depsDb=depsDb->next;
		}

		/* database listesinde yoksa ekle */
		if(found == FALSE)
		{
			depsDb = (departmentsDb*)malloc(sizeof(departmentsDb));
			memset(depsDb, 0, sizeof(departmentsDb));

			depsDb->keyId=depsKeyId;
			depsDb->depId=pDepartment->depId;
			depsDb->scoreType=pDepartment->scoreType;
			strcpy(depsDb->depName, pDepartment->department);

			/* database listesine ekle */
			if(depsDbFirst == NULL)
			{
				depsDbFirst=depsDb;
				depsDbLast=depsDb;
			}
			else
			{
				depsDbLast->next=depsDb;
				depsDbLast=depsDb;
			}

			depsKeyId++;
		}


		/* bu university database listesinde var mi diye bak */
		unisDb=unisDbFirst;
		found=FALSE;
		while(unisDb != NULL)
		{
			if(pDepartment->uniId == unisDb->uniId)
			{
				found=TRUE;
				break;
			}

			unisDb=unisDb->next;
		}

		/* univesity database listesinde yoksa ekle */
		if(found == FALSE)
		{
			unisDb = (universitiesDb*)malloc(sizeof(universitiesDb));
			memset(unisDb, 0, sizeof(universitiesDb));

			unisDb->keyId=unisKeyId;
			unisDb->uniId= pDepartment->uniId;
			strcpy(unisDb->uniName, pDepartment->university);

			/* database listesine ekle */
			if(unisDbFirst == NULL)
			{
				unisDbFirst=unisDb;
				unisDbLast=unisDb;
			}
			else
			{
				unisDbLast->next=unisDb;
				unisDbLast=unisDb;
			}
			unisKeyId++;
		}


		/* bu dep of uni database listesinde var mi diye bak */
		pDepOfUniDb=depOfUniDbFirst;
		found=FALSE;
		while(pDepOfUniDb != NULL)
		{
			if ((pDepartment->uniId == pDepOfUniDb->uniId) && (pDepartment->depId == pDepOfUniDb->depId))
			{
				found=TRUE;
				break;
			}
			pDepOfUniDb=pDepOfUniDb->next;
		}

		/* dep of uni database listesinde yoksa ekle */
		if(found == FALSE)
		{
			pDepOfUniDb = (depOfUniDb*)malloc(sizeof(depOfUniDb));
			memset(pDepOfUniDb, 0, sizeof(depOfUniDb));

			pDepOfUniDb->keyId=depOfUniKeyId;
			pDepOfUniDb->uniId=pDepartment->uniId;
			pDepOfUniDb->depId=pDepartment->depId;
			pDepOfUniDb->quota=pDepartment->quota;
			pDepOfUniDb->scoreType=pDepartment->scoreType;
			pDepOfUniDb->placedCount=0;

			/* database listesine ekle */
			if(depOfUniDbFirst == NULL)
			{
				depOfUniDbFirst=pDepOfUniDb;
				depOfUniDbLast=pDepOfUniDb;
			}
			else
			{
				depOfUniDbLast->next=pDepOfUniDb;
				depOfUniDbLast=pDepOfUniDb;
			}
			depOfUniKeyId++;
		}

		pDepartment=pDepartment->next;
	}


	/* binary db dosyalarini yaz */
	depsDb=depsDbFirst;
	while(depsDb != NULL)
	{
		fwrite(depsDb, sizeof(departmentsDb), 1, fDepartmentsDb);

		depsDb=depsDb->next;
	}

	/* hafizayi temizle */
	freeDepartmentsDb(&depsDbFirst);

	unisDb=unisDbFirst;
	while(unisDb!= NULL)
	{
		fwrite(unisDb, sizeof(universitiesDb), 1, fUniversitiesDb);

		unisDb=unisDb->next;
	}

	/* hafizayi temizle */
	freeUniversitiesDb(&unisDbFirst);


	pDepOfUniDb=depOfUniDbFirst;
	while(pDepOfUniDb != NULL)
	{
		fwrite(pDepOfUniDb, sizeof(depOfUniDb), 1, fDepofunisDb);

		pDepOfUniDb=pDepOfUniDb->next;
	}

	/* hafizayi temizle */
	freeDepOfUniDb(&depOfUniDbFirst);


	fclose(fDepartmentsDb);
	fclose(fUniversitiesDb);
	fclose(fDepofunisDb);


	/* studentsinfo.bin, studentspreference.bin binary db dosyalarini 
	 * "write binary" modunda olustur */

	fStudentsinfoDb = fopen("studentsinfo.bin", "wb");
	fStudentsprefDb = fopen("studentspreference.bin", "wb");

	stdInfoKeyId=0;
	stdPrefKeyID=0;

	pStudentName=pStNames;
	while(pStudentName != NULL)
	{
		
		/* StudensNames ve StudentsAddressInfo listelerini dolas */
		/* Bilgileri studentsInfoDb yapisina koy ve 
		 * studentsinfo.bin dosyasina yaz */

		/* bu ogrencinin adres kaydini bul */
		pAddressInfo=pStAddr;
		while(pAddressInfo != NULL)
		{
			if(isEqualBigInts(&(pStudentName->id), &(pAddressInfo->id)))
			{
				/* ogrencinin adresini bulduk */
				break;
			}

			pAddressInfo=pAddressInfo->next;
		}

		stinfoDb = (studentsInfoDb*)malloc(sizeof(studentsInfoDb));
		memset(stinfoDb, 0, sizeof(studentsInfoDb));

/* StudentNames ve studentsAddressInfo listelerinden bu ogrenciye ait bilgileri al */
		stinfoDb->studentId.lspart = pStudentName->id.lspart;
		stinfoDb->studentId.mspart = pStudentName->id.mspart;
		stinfoDb->phone.lspart = pAddressInfo->phone.lspart;
		stinfoDb->phone.mspart = pAddressInfo->phone.mspart;
		strcpy(stinfoDb->name, pStudentName->name);
		strcpy(stinfoDb->surname, pStudentName->surname);
		strcpy(stinfoDb->email, pAddressInfo->email);
		strcpy(stinfoDb->address, pAddressInfo->address);

		stinfoDb->keyId=stdInfoKeyId;

		/* listeye ekle */
		if(stinfoDbFirst == NULL)
		{
			stinfoDbFirst=stinfoDb;
			stinfoDbLast=stinfoDb;
		}
		else
		{
			stinfoDbLast->next=stinfoDb;
			stinfoDbLast=stinfoDb;
		}

		stdInfoKeyId++;

		pStudentName=pStudentName->next;
	}

	pScore=pScr;
	while(pScore != NULL)
	{
		/* scores ve preferences listelerini dolas */
		/* Bilgileri studentsPreferenceDb yapisina koy ve 
		 * studentspreference.bin dosyasina yaz */

		/* bu ogrencinin preference kaydini bul */
		pPreference=pPref;
		while(pPreference != NULL)
		{
			if(isEqualBigInts(&(pScore->studentId), &(pPreference->studentId)))
			{
				/* ogrencinin tercihini bulduk */
				break;
			}

			pPreference=pPreference->next;
		}

		/* bu ogrencinin StudentNames kaydini bul */
		pStudentName=pStNames;
		while(pStudentName != NULL)
		{
			if (isEqualBigInts(&(pScore->studentId), &(pStudentName->id)))
			{
				/* ogrencinin adini bulduk */
				break;
			}

			pStudentName=pStudentName->next;
		}


		stprefDb = (studentsPreferenceDb*)malloc(sizeof(studentsPreferenceDb));
		memset(stprefDb, 0, sizeof(studentsPreferenceDb));

		/* uni id ve dep id '0' olabildiginden dolayi, uniIds ve depIds 
		 * arraylarine -1 initialize ediyoruz */
		memset(stprefDb->uniIds, -1, sizeof(stprefDb->uniIds));
		memset(stprefDb->depIds, -1, sizeof(stprefDb->depIds));
		stprefDb->placedUniId = -1;
		stprefDb->placedDepId = -1;


		/* scores, preferences ve student names listelerinden gerekli bilgileri kopyala */
		stprefDb->studentId.lspart = pScore->studentId.lspart;
		stprefDb->studentId.mspart = pScore->studentId.mspart;
		stprefDb->quantativeScore = pScore->quantativeScore;
		stprefDb->verbalScore = pScore->verbalScore;
		stprefDb->bday_day = pStudentName->bday_day;
		stprefDb->bday_month = pStudentName->bday_month;
		stprefDb->bday_year = pStudentName->bday_year;
		stprefDb->scoreType = pStudentName->scoreType;


		memcpy(stprefDb->uniIds, pPreference->uniIds, sizeof(stprefDb->uniIds));
		memcpy(stprefDb->depIds, pPreference->depIds, sizeof(stprefDb->depIds));

		stprefDb->keyId=stdPrefKeyID;

		/* listeye ekle */
		if(stprefDbFirst == NULL)
		{
			stprefDbFirst=stprefDb;
			stprefDbLast=stprefDb;
		}
		else
		{
			stprefDbLast->next=stprefDb;
			stprefDbLast=stprefDb;
		}

		stdPrefKeyID++;

		pScore = pScore->next;
	}


	/* binary db dosyalarini yaz */
	stinfoDb=stinfoDbFirst;
	while(stinfoDb != NULL)
	{
		fwrite(stinfoDb, sizeof(studentsInfoDb), 1, fStudentsinfoDb);

		stinfoDb=stinfoDb->next;
	}

	/* hafizayi bosalt */
	freeStudentsInfoDb(&stinfoDbFirst);

	stprefDb = stprefDbFirst;
	while(stprefDb!= NULL)
	{
		fwrite(stprefDb, sizeof(studentsPreferenceDb), 1, fStudentsprefDb);

		stprefDb=stprefDb->next;
	}

	/* hafizayi bosalt */
	freeStudentsPreferenceDb(&stprefDbFirst);


	fclose(fStudentsinfoDb);
	fclose(fStudentsprefDb);
}


/* Yerlestirme sonuclarinin raporlarini csv dosyalari olarak olusturur */
void createCsvReports()
{
/*
- Departmanlari ve bu departmanlara yerlesen ogrencileri listeleyen bir 
	csv dosyasi olustur
- Ogrencileri ve yerlestikleri departmanlari listeleyen bir csv dosyasi olustur
- Universiteleri ve bu universitelere yerlesen ogrencileri listeleyen bir 
	csv dosyasi olustur
- Butun universitelerin her bolumunun maksimum ve minimum yerlestirme puanlarini 
	listeleyen bir csv dosyasi olustur
*/
	studentsInfoDb *stInfoList, *stInfo;
	studentsPreferenceDb *stPrefList, *stPref;
	universitiesDb *uniList, *uni;
	departmentsDb *depList, *dep;
	depOfUniDb *depOfUniList, *depOfUni;
	FILE *fDepsAndStudents, *fStudents, *fUnisAndStudents, *fUnisAndDeps;
	float maxScore, minScore, score;


	/* database dosyalarini oku ve listeleri olustur */
	readStudentsInfoDb(&stInfoList);
	readStudentsPreferenceDb(&stPrefList);
	readUniversitiesDb(&uniList);
	readDepartmentsDb(&depList);
	readDepOfUniDb(&depOfUniList);

	/* artik elimizde butun bilgiler var */

	/* Departmanlari ve bu departmanlara yerlesen ogrencileri listeleyen bir 
	 * csv dosyasi olustur */
	/* University;UniID;Department;DepID;Stu1 ID;Stu1 Name;Stu2 ID;Stu2 Name;...*/

	fDepsAndStudents = fopen("DepartmentsAndStudents.csv", "w");

	/* baslik'lari yaz */
	fprintf(fDepsAndStudents, 
			"Department;DepID;Stu1 ID;Stu1 Name;Stu2 ID;Stu2 Name;\n");


	/* dep of uni listesini dolas */
	dep=depList;

	while(dep != NULL)
	{
		/* department bilgilerini yaz */
		fprintf(fDepsAndStudents, "%s;%d;", dep->depName, dep->depId);

		/* bu bolume yerlesen ogrencileri bul */
		stPref=stPrefList;

		while(stPref != NULL)
		{
			if( stPref->placedDepId == dep->depId)
			{
				/* ogrenci bilgilerine ulas */
				stInfo = searchStudentInfoById(stInfoList, &(stPref->studentId));

				/* csv dosyasina ekle */

				fprintf(fDepsAndStudents, "%s;%s %s;", 
		   bigIntToString(&(stInfo->studentId)), stInfo->name, stInfo->surname);
			}

			stPref=stPref->next;
		}

		fprintf(fDepsAndStudents, "\n");

		dep=dep->next;
	}

	fclose(fDepsAndStudents);



	/* Ogrencileri ve yerlestikleri departmanlari listeleyen bir 
	 * csv dosyasi olustur */

	fStudents = fopen("StudentsAndDepartments.csv", "w");

	/* baslik'lari yaz */
	fprintf(fStudents, "ID;Name;Surname;University;UniID;Department;DepID;\n");


	/* student preferences listesini dolas */
	stPref=stPrefList;

	while(stPref != NULL)
	{
		/* ogrenci bilgilerine ulas */
		stInfo = searchStudentInfoById(stInfoList, &(stPref->studentId));

		/* dosyaya yaz */
		fprintf(fStudents, "%s;%s;%s;", bigIntToString(&(stInfo->studentId)), 
										stInfo->name, stInfo->surname);


		/* universite ve department bilgilerine ulas */
		uni = searchUniversityById(uniList, stPref->placedUniId);
		dep = searchDepartmentById(depList, stPref->placedDepId);

		if(uni != NULL && dep != NULL)
		{
			fprintf(fStudents, "%s;%d;%s;%d;\n", 
					uni->uniName, uni->uniId, dep->depName, dep->depId);
		}
		else
		{
			fprintf(fStudents, "\n");
		}

		stPref=stPref->next;
	}

	fclose(fStudents);


	/* Universiteleri ve bu universitelere yerlesen ogrencileri listeleyen bir 
	 * csv dosyasi olustur */

	fUnisAndStudents = fopen("UniversitiesAndStudents.csv", "w");

	/* baslik'lari yaz */
	fprintf(fUnisAndStudents, 
			"University;UniID;Stu1 Name;Score1;Stu2 Name;Score2;\n");


	/* universty listesini dolas */
	uni=uniList;

	while(uni != NULL)
	{
		/* universite bilgilerini yaz */
		fprintf(fUnisAndStudents, "%s;%d;", uni->uniName, uni->uniId);


		/* bu universiteye yerlesen ogrencileri bul */
		stPref=stPrefList;

		while(stPref != NULL)
		{
			if(stPref->placedUniId == uni->uniId)
			{
				/* ogrenci bilgilerine ulas */
				stInfo = searchStudentInfoById(stInfoList, &(stPref->studentId));

				if(stPref->scoreType == SCORE_TYPE_QUANTATIVE)
				{
					score=stPref->quantativeScore;
				}
				else
				{
					score=stPref->verbalScore;
				}

				/* csv dosyasina ekle */
				fprintf(fUnisAndStudents, "%s %s;%.3f;", 
						stInfo->name, stInfo->surname, score);
			}

			stPref=stPref->next;
		}
		fprintf(fUnisAndStudents, "\n");

		uni=uni->next;
	}

	fclose(fUnisAndStudents);



	/* Butun universitelerin her bolumunun maksimum ve minimum 
	 * yerlestirme puanlarini listeleyen bir csv dosyasi olustur */

	fUnisAndDeps = fopen("UniversitiesAndDepartments.csv", "w");

	/* baslik'lari yaz */
	fprintf(fUnisAndDeps ,"Universty;UniID;Department;DepID;Max Score;Min Score;\n");


	/* dep of uni listesini dolas */

	depOfUni=depOfUniList;

	while(depOfUni != NULL)
	{
		/* uni ve dep bilgilerine ulas */
		uni = searchUniversityById(uniList, depOfUni->uniId);
		dep = searchDepartmentById(depList, depOfUni->depId);

		fprintf(fUnisAndDeps, "%s;%d;%s;%d;", 
				uni->uniName, uni->uniId, dep->depName, dep->depId);


		/* bu bolume yerlesen max ve min puanlari bul */

		maxScore=0.0;
		minScore=1001.0;

		/* student preferences listesini dolas */
		stPref=stPrefList;

		while(stPref != NULL)
		{
			/* ogrenci bu bolume yerlesmisse */
			if((stPref->placedUniId == uni->uniId) && 
			   (stPref->placedDepId == dep->depId))
			{
				
				if(depOfUni->scoreType == SCORE_TYPE_QUANTATIVE)
				{
					if(stPref->quantativeScore > maxScore)
						maxScore=stPref->quantativeScore;

					if(stPref->quantativeScore < minScore)
						minScore=stPref->quantativeScore;
				}
				else
				{
					if(stPref->verbalScore > maxScore)
						maxScore=stPref->verbalScore;

					if(stPref->verbalScore < minScore)
						minScore=stPref->verbalScore;
				}
			}

			stPref=stPref->next;
		}


		/* max ve min score'lar bulundu. yazdir */

		fprintf(fUnisAndDeps, "%.3f;%.3f;\n", maxScore, minScore);


		depOfUni=depOfUni->next;
	}

	fclose(fUnisAndDeps);


	/* hafizayi temizle */
	freeStudentsInfoDb(&stInfoList);
	freeStudentsPreferenceDb(&stPrefList);
	freeUniversitiesDb(&uniList);
	freeDepartmentsDb(&depList);
	freeDepOfUniDb(&depOfUniList);
}


/* Yerlestirme sonuclarinin raporlarini HTML dosyalari olarak olusturur */
void createHtmlOutputs()
{
	FILE					*fPlacementHtml, *fStudentsHtml;
	studentsInfoDb			*stInfoList, *stInfo;
	studentsPreferenceDb	*stPrefList, *stPref;
	universitiesDb			*uniList, *uni;
	departmentsDb			*depList, *dep;
	char					*str, *formatStr, buffer[4096];


/* students info, students preferences, universities ve departments 
 * listelerini oku */
	readStudentsInfoDb(&stInfoList);
	readStudentsPreferenceDb(&stPrefList);
	readUniversitiesDb(&uniList);
	readDepartmentsDb(&depList);


	/* Placement.html olustur */
	fPlacementHtml = fopen("Placement.html", "w");


	/* Placement.html dosyasinin head kismi */
	str = "<html>\n<head>\n<title>Placements</title>\n</head>\n<body bgcolor=\"#F0F0F0\">\n";

	/* head kismini yaz */
	fwrite(str, strlen(str), 1, fPlacementHtml);

	/* tabloyu ac */
	str = "<table border=\"1\">\n"
		"<tr>\n"
		  "<td bgcolor=\"#cc8888\"><b>TCKN</b></td>\n"
		  "<td bgcolor=\"#cc8888\"><b>Ogrenci Adi Soyadi</b></td>\n"
		  "<td bgcolor=\"#cc8888\"><b>Sayisal Puani</b></td>\n"
		  "<td bgcolor=\"#cc8888\"><b>Sozel Puani</b></td>\n"
		  "<td bgcolor=\"#cc8888\"><b>Universite</b></td>\n"
		  "<td bgcolor=\"#cc8888\"><b>Bolum</b></td>\n"
		  "<td bgcolor=\"#cc8888\"><b>Puanlama Turu</b></td>\n"
		"</tr>\n";

	fwrite(str, strlen(str), 1, fPlacementHtml);


	/* tablonun satirlarini olustur */
	formatStr = "<tr>"
			/* tckn */
		    "<td bgcolor=\"#cc8888\"><a href=\"Students.html#%s\">%s</a></td>"		
		    "<td bgcolor=\"#cc8888\">%s %s</td>"	/* ad soyad */
		    "<td bgcolor=\"#cc8888\">%.3f</td>"		/* sayisal puan */
		    "<td bgcolor=\"#cc8888\">%.3f</td>"		/* sozel puan */
		    "<td bgcolor=\"#cc8888\">%s</td>"		/* uni */
		    "<td bgcolor=\"#cc8888\">%s</td>"		/* dep */
		    "<td bgcolor=\"#cc8888\">%s</td>"		/* score type */
		    "</tr>\n";


	/* student info listesini dolas */

	stInfo=stInfoList;

	while(stInfo != NULL)
	{
		/* ogrencinin diger bilgilerini bul */
		stPref = searchStudentPrefById(stPrefList , &(stInfo -> studentId));
		uni = searchUniversityById(uniList, stPref -> placedUniId);
		dep = searchDepartmentById(depList, stPref -> placedDepId);


		memset(buffer, 0, sizeof(buffer));

		if(stPref -> scoreType == SCORE_TYPE_QUANTATIVE)
		{
			str = "SAYISAL";
		}
		else
		{
			str = "SOZEL";
		}


		/* Ogrenci Adi Soyadi - Sayisal Puani - Sozel Puani - Universite - Bolum */
		if(stPref -> placedUniId == -1 || stPref -> placedDepId == -1 )
		{
			/* ogrenci yerlesememisse uni ve dep name yerine - koy */
			sprintf(buffer, formatStr, bigIntToString(&(stInfo -> studentId)), 
			bigIntToString(&(stInfo -> studentId)), stInfo -> name, 
			stInfo -> surname, stPref -> quantativeScore, 
			stPref -> verbalScore, "-" , "-" ,str);
		}
		else
		{
			sprintf(buffer, formatStr, bigIntToString(&(stInfo -> studentId)), 
			bigIntToString(&(stInfo -> studentId)), stInfo -> name, 
			stInfo -> surname, stPref -> quantativeScore, stPref -> verbalScore,
			uni -> uniName, dep -> depName, str);
		}

		/* satiri yaz */
		fwrite(buffer, strlen(buffer), 1, fPlacementHtml);

		stInfo = stInfo -> next;
	}


	/* tabloyu kapat */
	str = "</tr>\n</table>";
	fwrite(str, strlen(str), 1, fPlacementHtml);

	/* html'yi kapat */
	str = "</body></html>";
	fwrite(str, strlen(str), 1, fPlacementHtml);

	fclose(fPlacementHtml);


	/* Student.html yarat */
	fStudentsHtml = fopen("Students.html", "w");


	/* Placement.html dosyasinin head kismi */
	str = "<html>\n<head>\n<title>Students</title>\n</head>\n<body bgcolor=\"#F0F0F0\">\n";

	/* head kismini yaz */
	fwrite(str, strlen(str), 1, fStudentsHtml);

	/* tabloyu ac */
	str = "<table border=\"1\">\n"
		"<tr>\n"
		  "<td bgcolor=\"#cc8888\"><b>TCKN</b></td>\n"
		  "<td bgcolor=\"#cc8888\"><b>Ogrenci Adi Soyadi</b></td>\n"
		  "<td bgcolor=\"#cc8888\"><b>Telefon</b></td>\n"
		  "<td bgcolor=\"#cc8888\"><b>Email</b></td>\n"
		  "<td bgcolor=\"#cc8888\"><b>Adres</b></td>\n"
		"</tr>\n";

	fwrite(str, strlen(str), 1, fStudentsHtml);


	/* tablonun satirlarini olustur */
	formatStr = "<tr>"
		    "<td bgcolor=\"#cc8888\"><a name=\"%s\">%s</a></td>"	/* tckn */
		    "<td bgcolor=\"#cc8888\">%s %s</td>"	/* ad soyad */
		    "<td bgcolor=\"#cc8888\">%s</td>"		/* telefon */
		    "<td bgcolor=\"#cc8888\">%s</td>"		/* email */
		    "<td bgcolor=\"#cc8888\">%s</td>"		/* adres */
		    "</tr>\n";


	/* student info listesini dolas */

	stInfo = stInfoList;

	while(stInfo != NULL)
	{

		memset(buffer, 0, sizeof(buffer));

		/* ogrenci bilgilerini satir satir yaz */
		sprintf(buffer, formatStr, bigIntToString(&(stInfo -> studentId)), 
				bigIntToString(&(stInfo -> studentId)), stInfo -> name, 
				stInfo -> surname, bigIntToString(&(stInfo -> phone)), 
				stInfo -> email, stInfo -> address);

		fwrite(buffer, strlen(buffer), 1, fStudentsHtml);

		stInfo = stInfo -> next;
	}


	/* tabloyu kapat */
	str = "</tr>\n</table>";
	fwrite(str, strlen(str), 1, fStudentsHtml);

	/* html'yi kapat */
	str = "</body></html>";
	fwrite(str, strlen(str), 1, fStudentsHtml);

	fclose(fPlacementHtml);


	/* hafizayi temizle */
	freeStudentsInfoDb(&stInfoList);
	freeStudentsPreferenceDb(&stPrefList);
	freeUniversitiesDb(&uniList);
	freeDepartmentsDb(&depList);
}


/* Yerlestirme islemini yapar */
void doPlacement()
{

	studentsPreferenceDb	*stPrefFirst=NULL, *stPref, *stPrefPrev;
	depOfUniDb				*depOfUniFirst=NULL, *depOfUni;
	FILE					*fStPref, *fDepOfUnis;
	int						swapped;
	char					c;


	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n");
	printf("Yerlestirme:\n\n");

	printf("Yerlestirme yapiliyor...\n");

	/* binary database dosyasinda students listesini oku
	 * ogrencileri quantative puanlarina gore sirala
	 * en yuksek puanli ogrenciden baslayarak quantative puanli ogrencileri yerlestirmeyi yap
	 * yerlestirilmeyen ogrencileri verbal puana gore sirala
	 * bunlarin da yerlestirmesini yap */

	/* ogrenci tercih listesini oku */
	readStudentsPreferenceDb(&stPrefFirst);


	/* departments of unis listesini oku */
	readDepOfUniDb(&depOfUniFirst);


	/* yerlestirmeden once placed count lari sifirla */
	depOfUni = depOfUniFirst;
	while(depOfUni != NULL)
	{
		depOfUni -> placedCount = 0;

		depOfUni = depOfUni -> next;
	}





	/* ogrenci tercih listesini quantative score a gore sirala */
	sortStudentListByScoreType(&stPrefFirst, SCORE_TYPE_QUANTATIVE);


	/* quntative puana gore yerlestirmeyi yap */
	placeStudents(stPrefFirst, depOfUniFirst, SCORE_TYPE_QUANTATIVE);


	/* ogrenci tercih listesini verbal score a gore sirala */
	sortStudentListByScoreType(&stPrefFirst, SCORE_TYPE_VERBAL);


	/* verbal puana gore yerlestirmeyi yap */
	placeStudents(stPrefFirst, depOfUniFirst, SCORE_TYPE_VERBAL);


	/* yerlestirme sonucunu database dosyalarina yaz */

	/* ogrenci listesini dosyaya yazmadan once keyId ye gore sirala */
	do
	{
		swapped = FALSE;

		stPref = stPrefFirst;
		while(stPref -> next != NULL)
		{
			if(stPref -> keyId > stPref -> next -> keyId)
			{
				if(stPref == stPrefFirst)
				{
					stPrefFirst = stPref -> next;
					stPref -> next = stPref -> next -> next;
					stPrefFirst -> next = stPref;

					stPrefPrev = stPrefFirst;
				}
				else
				{
					stPrefPrev -> next = stPref -> next;
					stPref -> next = stPref -> next -> next;
					stPrefPrev -> next -> next = stPref;

					stPrefPrev = stPrefPrev -> next;
				}
				swapped = TRUE;
			}
			else
			{
				stPrefPrev = stPref;
				stPref = stPref -> next;
			}
		}
	} while(swapped == TRUE);

	/* keyID ye gore siralanmis student preference listesini dosyaya yaz */
	fStPref = fopen("studentspreference.bin", "wb");

	stPref = stPrefFirst;
	while(stPref!= NULL)
	{
		fwrite(stPref, sizeof(studentsPreferenceDb), 1, fStPref);

		stPref = stPref -> next;
	}

	fclose(fStPref);


#ifdef	_DEBUG_MODE_

	printf("Yerlestirme sonuclari:\n");
	stPref = stPrefFirst;
	while(stPref != NULL)
	{
		printf("\tTCKN: %s, uni: %d, dep: %d\n", 
				bigIntToString(&(stPref -> studentId)), 
				stPref -> placedUniId, stPref -> placedDepId);
		stPref = stPref -> next;
	}

#endif


	/* depofunis listesini dosyaya yaz. siralamayi degistirmedigimiz icin;
	 * tekrar keyId ye gore siralamaya gerek yok */
	fDepOfUnis = fopen("depofunis.bin", "wb");

	depOfUni = depOfUniFirst;
	while(depOfUni!= NULL)
	{
		fwrite(depOfUni, sizeof(depOfUniDb ), 1, fDepOfUnis);

		depOfUni = depOfUni -> next;
	}

	fclose(fDepOfUnis);


#ifdef	_DEBUG_MODE_

	printf("Universiteler ve bolumleri:\n");
	depOfUni = depOfUniFirst;
	while(depOfUni != NULL)
	{
		printf("\tuni: %d, bolum: %d, kota: %d, yerlestirilmis: %d\n", 
				depOfUni -> uniId, depOfUni -> depId, depOfUni -> quota, 
				depOfUni -> placedCount);
		depOfUni = depOfUni -> next;
	}

#endif


	/* yerlestirme bittikten sonra csv raporlarini ve html dosyalarini olustur */
	printf("CSV raporlari olusturuluyor...\n");
	createCsvReports();
	printf("HTML raporlari olusturuluyor...\n");
	createHtmlOutputs();

	fflush(stdin);
	printf("Yerlestirme tamamlandi.\n");



	/* hafizayi temizle */
	freeStudentsPreferenceDb(&stPrefFirst);
	freeDepOfUniDb(&depOfUniFirst);

	mypause();
}


/* studentdsinfo.bin db dosyasindan ogrenci bilgilerini okur */
void readStudentsInfoDb(studentsInfoDb **pStdList)
{
	FILE			*fStInfo;
	studentsInfoDb	*stInfoFirst=NULL, *stInfoLast, *stInfo;
	int				ret;


	fStInfo = fopen("studentsinfo.bin" , "rb");

	/* dosyayi oku ve listeyi olustur */

	while(feof(fStInfo) == 0 && ferror(fStInfo) == 0)
	{
		stInfo = (studentsInfoDb*)malloc(sizeof(studentsInfoDb));
		memset(stInfo, 0, sizeof(studentsInfoDb));

		ret = fread(stInfo, sizeof(studentsInfoDb), 1, fStInfo);

		if(ret != 1)
		{
			free(stInfo);
			continue;
		}

		stInfo -> next = NULL;

		/* listeye ekle */
		if(stInfoFirst == NULL)
		{
			stInfoFirst = stInfo;
			stInfoLast = stInfo;
		}
		else
		{
			stInfoLast -> next = stInfo;
			stInfoLast = stInfo;
		}
	}

	fclose(fStInfo);


	/* olusturdugumuz listeyi fonksiyonun parametresine ata */
	*pStdList = stInfoFirst;
}


/* studentspreference.bin dosyasinden tercih bilgilerini okur */
void readStudentsPreferenceDb(studentsPreferenceDb **pStdPrefList)
{
	FILE					*fStPref;
	studentsPreferenceDb	*stPrefFirst=NULL, *stPrefLast, *stPref;
	int						ret;


	fStPref = fopen("studentspreference.bin", "rb");

	/* dosyayi oku ve listeyi olustur */

	while(feof(fStPref) == 0 && ferror(fStPref) == 0)
	{
		stPref = (studentsPreferenceDb*)malloc(sizeof(studentsPreferenceDb));
		memset(stPref, 0, sizeof(studentsPreferenceDb));

		ret = fread(stPref, sizeof(studentsPreferenceDb), 1, fStPref);

		if(ret != 1)
		{
			free(stPref);
			continue;
		}

		stPref -> next = NULL;

		/* listeye ekle */
		if(stPrefFirst == NULL)
		{
			stPrefFirst = stPref;
			stPrefLast = stPref;
		}
		else
		{
			stPrefLast -> next = stPref;
			stPrefLast = stPref;
		}
	}

	fclose(fStPref);


	/* olusturdugumuz listeyi fonksiyonun parametresine ata */
	*pStdPrefList = stPrefFirst;
}


/* depofunis.db dosyasindan universitelerin bolumleri bilgilerini okur */
void readDepOfUniDb(depOfUniDb **pDepOfUniList)
{
	FILE		*fDepOfUnis;
	depOfUniDb	*depOfUniFirst=NULL, *depOfUniLast, *depOfUni;
	int			ret;


	fDepOfUnis = fopen("depofunis.bin", "rb");

	/* dosyayi oku ve listeyi olustur */

	while(feof(fDepOfUnis) == 0 && ferror(fDepOfUnis) == 0 )
	{
		depOfUni = (depOfUniDb*)malloc(sizeof(depOfUniDb));
		memset(depOfUni, 0, sizeof(depOfUniDb));

		ret = fread(depOfUni, sizeof(depOfUniDb), 1, fDepOfUnis);

		if(ret != 1)
		{
			free(depOfUni);
			continue;
		}

		depOfUni -> next = NULL;

		/* listeye ekle */
		if(depOfUniFirst == NULL)
		{
			depOfUniFirst = depOfUni;
			depOfUniLast = depOfUni;
		}
		else
		{
			depOfUniLast -> next = depOfUni;
			depOfUniLast = depOfUni;
		}
	}

	fclose(fDepOfUnis);


	/* olusturdugumuz listeyi fonksiyonun parametresine ata */
	*pDepOfUniList = depOfUniFirst;
}


/* universities.bin dosyasindan universite bilgilerini okur */
void readUniversitiesDb(universitiesDb **pUniList)
{
	FILE			*fUnis;
	universitiesDb	*uniFirst=NULL, *uniLast, *uni;
	int				ret;


	fUnis = fopen("universities.bin", "rb");

	/* dosyayi oku ve listeyi olustur */

	while(feof(fUnis) == 0 && ferror(fUnis) == 0)
	{
		uni = (universitiesDb*)malloc(sizeof(universitiesDb));
		memset(uni, 0, sizeof(universitiesDb));

		ret = fread(uni, sizeof(universitiesDb), 1, fUnis);

		if(ret != 1)
		{
			free(uni);
			continue;
		}


		uni -> next = NULL;

		/* listeye ekle */
		if(uniFirst == NULL)
		{
			uniFirst = uni;
			uniLast = uni;
		}
		else
		{
			uniLast -> next = uni;
			uniLast = uni;
		}

	}

	fclose(fUnis);

	/* olusturdugumuz listeyi fonksiyonun parametresine ata */
	*pUniList = uniFirst;
}



/* departments.bin dosyasindan bolumlerin bilgilerini okur */
void readDepartmentsDb(departmentsDb **pDepList)
{
	FILE			*fDeps;
	departmentsDb	*depFirst=NULL, *depLast, *dep;
	int				ret;


	fDeps = fopen("departments.bin", "rb");

	/* dosyayi oku ve listeyi olustur */

	while(feof(fDeps) == 0 && ferror(fDeps) == 0)
	{
		dep = (departmentsDb*)malloc(sizeof(departmentsDb));
		memset(dep, 0, sizeof(departmentsDb));

		ret = fread(dep, sizeof(departmentsDb), 1, fDeps);

		if(ret != 1)
		{
			free(dep);
			continue;
		}

		dep -> next = NULL;

		/* listeye uniFirst */
		if(depFirst == NULL)
		{
			depFirst = dep;
			depLast = dep;
		}
		else
		{
			depLast -> next = dep;
			depLast = dep;
		}
	}

	fclose(fDeps);

	/* olusturdugumuz listeyi fonksiyonun parametresine ata */
	*pDepList = depFirst;
}


/* ogrenci tercih listesini, ogrencilerin sayisal ya da sozel puanlarina gore
 * buyukten kucuge siralar */
void sortStudentListByScoreType(studentsPreferenceDb **pStdList, scoreType scrType)
{
	studentsPreferenceDb	*stPref, *stPrefPrev;
	float					score1, score2;
	int						swapped;


	/* ogrenci tercih listesini score type a gore buyukten kucuge dogru sirala
     * bubble sort algoritmasi */
	do
	{
		swapped = FALSE;

		stPref = *pStdList;
		while(stPref -> next != NULL)
		{
			/* score tipine gore ilgili puani al */
			if(scrType == SCORE_TYPE_QUANTATIVE)
			{
				score1 = stPref -> quantativeScore;
				score2 = stPref -> next -> quantativeScore;
			}
			else if(scrType == SCORE_TYPE_VERBAL)
			{
				score1 = stPref -> verbalScore;
				score2 = stPref -> next -> verbalScore;
			}


			/* birinci puan ikinci puandan kucukse yer degistir */
			if(score1 < score2)
			{
				if(stPref == *pStdList)
				{
					*pStdList = stPref -> next;
					stPref -> next = stPref -> next -> next;
					(*pStdList) -> next = stPref;

					stPrefPrev = *pStdList;
				}
				else
				{
					stPrefPrev -> next = stPref -> next;
					stPref -> next = stPref -> next -> next;
					stPrefPrev -> next -> next = stPref;

					stPrefPrev = stPrefPrev -> next;
				}

				swapped = TRUE;
			}
			else if(score1 == score2)
			{
				/* puanlar esitse, yasi buyuk olani arkaya at */
				/* dogum yili kucukse, ya da dogum yili esitken ay kucukse, 
				 * ya da yil ve ay esitken gun kucukse, bu adamin yasi buyuktur */
				if ( (stPref -> bday_year < stPref -> next -> bday_year) ||
				     ((stPref -> bday_year == stPref -> next -> bday_year) && 
					  (stPref -> bday_month < stPref -> next -> bday_month)) ||
				     ((stPref -> bday_year == stPref -> next -> bday_year) && 
        			  (stPref -> bday_month == stPref -> next -> bday_month) && 
					  (stPref -> bday_day < stPref -> next -> bday_day)) )
				{
					if(stPref == *pStdList)
					{
						*pStdList = stPref -> next;
						stPref -> next = stPref -> next -> next;
						(*pStdList) -> next = stPref;

						stPrefPrev = *pStdList;
					}
					else
					{
						stPrefPrev -> next = stPref -> next;
						stPref -> next = stPref -> next -> next;
						stPrefPrev -> next -> next = stPref;

						stPrefPrev = stPrefPrev -> next;
					}

					swapped = TRUE;
				}
				else
				{
		  /* yasi kucukse ya da dogum tarihleri esitse degistirmeye gerek yok */
					stPrefPrev = stPref;
					stPref = stPref -> next;
				}

			}
			else
			{
				stPrefPrev = stPref;
				stPref = stPref -> next;
			}
		}
	}while(swapped == TRUE);
}


/* sayisal ya da sozel puanlara gore ogrenci yerlesimini yapar */
void placeStudents(studentsPreferenceDb *pStdList, depOfUniDb *pDepList, scoreType scrType)
{
	studentsPreferenceDb	*stPref;
	depOfUniDb				*depOfUni;
	int						pref;


	/* score type a gore yerlestirmeyi yap */

	stPref = pStdList;
	while(stPref != NULL)
	{
		if(stPref -> scoreType == scrType)
		{
			/* sirayla butun tercihleri dolas */
			for(pref=0; pref<8; pref++)
			{
				/* istedigi departmani bul */
				depOfUni = pDepList;
				while(depOfUni != NULL)
				{
					if( (stPref -> uniIds[ pref ] == depOfUni -> uniId) &&
					    (stPref -> depIds[ pref ] == depOfUni -> depId) &&
					    ((depOfUni -> scoreType == scrType) ||
		 /* quantative ogrenciler sadece son tercihlerini verbal yapabilirler */
					    (stPref -> scoreType == SCORE_TYPE_QUANTATIVE) &&
						(pref == 7 ) && ( depOfUni -> scoreType == SCORE_TYPE_VERBAL)) )
					{
						/* ogrencinin istedigi bolumu bulduk. kotayi kontrol et */
						if(depOfUni -> placedCount < depOfUni -> quota)
						{
							/* bu bolumde yer var. yerlestir */
							stPref -> placedUniId = depOfUni -> uniId;
							stPref -> placedDepId = depOfUni -> depId;

							/* bu bolumun placed count'unu artir */
							depOfUni -> placedCount++;
						}
						else
						{
							/* bu bolumde yer yok. yerlestirilemedi */
						}
						break;
					}
					depOfUni = depOfUni -> next;
				}

				if (depOfUni == NULL)
				{
					/* ogrencinin tercih ettigi bolum yok */
				}


				/* ogrenci bu tercihine yerlestirilmisse sonraki ogrenciye gec */
				if(stPref -> placedUniId != -1 && stPref -> placedDepId != -1)
				{
					break;
				}			
			}
		}

		stPref = stPref -> next;
	}
}


/* universities listesinden belirli bir id ye sahip olan universiteyi arar */
universitiesDb *searchUniversityById(universitiesDb *pUniList, unsigned int uniId)
{
	universitiesDb *uni;

	if(uniId == -1)	/* ogrenci herhangi bir universiteye yerlesememis */
		return NULL;

	uni = pUniList;

	while(uni != NULL)
	{
		if(uni -> uniId == uniId)
		{
			return uni;
		}

		uni = uni -> next;
	}


	/* verilen id'li bir uni bulunamadi */

	return NULL;
}


/* departments listesinden belirli bir id ye sahip olan department i arar */
departmentsDb *searchDepartmentById(departmentsDb *pDepList, unsigned int depId)
{
	departmentsDb *dep;

	if(depId == -1)	/* ogrenci herhangi bir bolume yerlesememis */
		return NULL;

	dep = pDepList;

	while(dep != NULL)
	{
		if(dep -> depId == depId)
		{
			return dep;
		}

		dep = dep -> next;
	}


	/* verilen id'li bir department bulunamadi */

	return NULL;
}


/* studentsInfo listesinden belirli bir tckn ye sahip olan ogrenciyi arar */
studentsInfoDb *searchStudentInfoById(studentsInfoDb *pStInfoList, bigInt *id)
{
	studentsInfoDb *stInfo;

	stInfo = pStInfoList;

	while(stInfo != NULL)
	{
		if(isEqualBigInts(&(stInfo -> studentId), id))
		{
			return stInfo;
		}

		stInfo = stInfo -> next;
	}


	/* verilen id'li bir ogrenci bulunamadi */

	return NULL;
}


/* studentsPreferences listesinden belirli bir tckn ye sahip olan ogrenciyi arar */
studentsPreferenceDb *searchStudentPrefById(studentsPreferenceDb *pStPrefList, bigInt *id)
{
	studentsPreferenceDb *stPerf;

	stPerf = pStPrefList;

	while(stPerf != NULL)
	{
		if(isEqualBigInts(&(stPerf -> studentId), id))
		{
			return stPerf;
		}

		stPerf = stPerf -> next;
	}

	/* verilen id'li bir ogrenci bulunamadi */

	return NULL;
}



/* yeni bir univresite ekleme isini yapar
 * yeni eklenen universiteyi database dosyasina ekler */
void insertNewUniversity()
{
	char				uniName[128], c;
	int					i;
	universitiesDb		*newUni, *uniList, *uni;
	FILE				*fUni;


	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n");
	printf("Yeni universite ekleme:\n\n");

	flushStdin();
	printf("Universitenin adini giriniz: ");
	gets(uniName);


	/* yeni uni nesnesini yarat ve adini yaz */
	newUni = (universitiesDb*)malloc(sizeof(universitiesDb));
	memset(newUni, 0, sizeof(universitiesDb));

	strcpy(newUni -> uniName , uniName);


	/* universite listesini oku */
	readUniversitiesDb(&uniList);


	/* listedeki son uniId ve keyId leri bul, yeni universite kaydina 
	 * bu degerleri bir artirip id ver */

	uni = uniList;
	while(uni -> next != NULL)
	{
		uni = uni -> next;
	}

	newUni -> uniId = uni -> uniId + 1;
	newUni -> keyId = uni -> keyId + 1;


	/* yeni uni kaydini listeye ekle */
	uni -> next = newUni;

	/* yeni listeyi database dosyasina yaz */

	fUni = fopen("universities.bin", "wb");

	uni = uniList;
	while(uni != NULL)
	{
		fwrite(uni, sizeof(universitiesDb), 1, fUni);

		uni = uni -> next;
	}


	printf("Yeni universite kaydi eklendi.\n");


	fclose(fUni);


	/* hafizayi temizle */
	freeUniversitiesDb(&uniList);

	mypause();
}


/* univresite silme isini yapar
 * silinen universiteyi database dosyasindan cikarir */
void deleteUniversity()
{
	char				uniName[128], c;
	int					i;
	universitiesDb		*uniList=NULL, *uni, *uniPrev, *uni2;
	depOfUniDb			*depOfUniList, *depOfUni, *depOfUniPrev, *depOfUni2;
	FILE				*fUni, *fDepOfUni;


	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n");
	printf("Universite kaydi silme:\n\n");

	flushStdin();
	printf("Universitenin adini giriniz: ");
	gets(uniName);


	/* universite listesini oku */
	readUniversitiesDb(&uniList);

	/* liste icerisinde silinmek istenen universiteyi ara */
	uniPrev = uniList;
	uni = uniList;
	while(uni != NULL)
	{
		if(strcmp(uni -> uniName, uniName) == 0)
		{
			/* silecegimiz uni kaydini bulduk */
			break;
		}

		uniPrev = uni;
		uni = uni -> next;
	}

	if(uni == NULL)
	{
		printf("Kayitlarda bu isimli bir universite yok!\n");
	}
	else
	{
		/* bu uni'den sonraki uni'lerin keyId'lerini birer azalt */
		uni2 = uni -> next;
		while(uni2 != NULL)
		{
			uni2 -> keyId--;

			uni2 = uni2 -> next;
		}


		/* bu uni'yi listeden cikar */
		if(uni == uniList)
			uniList = uni -> next;
		else
			uniPrev -> next = uni -> next;


		/* yeni listeyi database dosyasina yaz */

		fUni = fopen("universities.bin", "wb");

		uni2 = uniList;
		while(uni2 != NULL)
		{
			fwrite(uni2, sizeof(universitiesDb), 1, fUni);

			uni2 = uni2 -> next;
		}

		fclose(fUni);


		/* bu universite kaydini dep of uni listesinden de sil */
		readDepOfUniDb(&depOfUniList);

		depOfUni = depOfUniList;
		depOfUniPrev = depOfUniList;
		while(depOfUni != NULL)
		{

			if(depOfUni -> uniId == uni -> uniId)
			{
				/* bu kayittan sonraki kayitlarin keyId'lerini birer azalt */

				depOfUni2 = depOfUni -> next;
				while(depOfUni2 != NULL)
				{
					depOfUni2 -> keyId--;

					depOfUni2 = depOfUni2 -> next;
				}


				/* kaydi listeden cikar */
				if (depOfUni == depOfUniList) /* listenin ilk elemaniysa */
				{
					depOfUniList = depOfUni -> next;
					depOfUniPrev = depOfUni -> next;
				}
				else
				{
					depOfUniPrev -> next = depOfUni -> next;
				}


				/* hafizayi bosalt */
				free(depOfUni);

				/* kaldigin yerden devam et */
				depOfUni = depOfUniPrev -> next;
			}
			else
			{
				depOfUniPrev = depOfUni;
				depOfUni = depOfUni -> next;
			}
		}

		/* yeni dep of uni listesini database dosyasina yaz */

		fDepOfUni = fopen("depofunis.bin", "wb");

		depOfUni = depOfUniList;
		while(depOfUni != NULL)
		{
			fwrite(depOfUni, sizeof(depOfUniDb), 1, fDepOfUni);

			depOfUni = depOfUni -> next;
		}

		fclose(fDepOfUni);


		/* hafizayi bosalt */
		free(uni);

		printf("Universite kaydi silindi.\n");
	}


	/* hafizayi temizle */
	freeUniversitiesDb(&uniList);
	freeDepOfUniDb(&depOfUniList);

	mypause();
}


/* yeni bir bolum ekleme isini yapar
 * yeni eklenen bolumu database dosyasina ekler */
void insertNewDepartment()
{
	char				depName[128], uniName[128], scr[4], choice[2], c;
	scoreType			scrType;
	int					quota, i;
	departmentsDb		*newDep, *depList, *dep;
	universitiesDb		*uniList=NULL, *uni, *uniPrev;
	depOfUniDb			*depOfUniList, *depOfUni, *newDepOfUni;
	FILE				*fDep , *fDepOfUni;

	
	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n");
	printf("Yeni departman ekleme:\n\n");


	flushStdin();
	printf("Departmanin adini giriniz: ");
	gets(depName);


	printf("Departman sayisal mi sozel mi? (Q/V):");
	scanf("%s", scr, 4);

	if(scr[0] == 'Q' || scr[0] == 'q')
	{
		scrType = SCORE_TYPE_QUANTATIVE;
	}
	else if(scr[0] == 'V' || scr[0] == 'v')
	{
		scrType = SCORE_TYPE_VERBAL;
	}


	/* yeni dep nesnesini yarat ve adini yaz */
	newDep = (departmentsDb*)malloc(sizeof(departmentsDb));
	memset(newDep, 0, sizeof(departmentsDb));

	strcpy(newDep -> depName , depName);

	newDep -> scoreType = scrType;


	/* departments listesini oku */
	readDepartmentsDb(&depList);


	/* listedeki son depId ve keyId leri bul, yeni department kaydina bu degerleri bir artirip id ver */

	dep = depList;
	while(dep -> next != NULL)
	{
		dep = dep -> next;
	}

	newDep -> depId = dep -> depId + 1;
	newDep -> keyId = dep -> keyId + 1;


	/* yeni uni kaydini listeye ekle */
	dep -> next = newDep;

	/* yeni listeyi database dosyasina yaz */

	fDep = fopen("departments.bin", "wb");

	dep = depList;
	while(dep != NULL)
	{
		fwrite(dep, sizeof(departmentsDb), 1, fDep);

		dep = dep -> next;
	}

	fclose(fDep);

	printf("Yeni departman eklendi.\n");


	do
	{
		system("cls");

		printf("\nOgrenci Yerlestirme Programi\n");
		printf("------------------\n\n");

		flushStdin();
		printf("\nBu departman icin bir universite girin: ");
		gets(uniName);


		/* universite listesini oku */
		readUniversitiesDb(&uniList);

		/* liste icerisinde eklenmek istenen universiteyi ara */
		uni = uniList;
		while(uni != NULL)
		{
			if(strcmp(uni -> uniName, uniName) == 0)
			{
				/* departmani ekleyecegimiz uni kaydini bulduk */
				break;
			}

			uniPrev = uni;
			uni = uni -> next;
		}

		if(uni == NULL)
		{
			printf("Kayitlarda bu isimli bir universite yok!\n");
		}
		else
		{
			printf("Kota bilgisini girin: ");
			scanf("%d", &quota);

			newDepOfUni = (depOfUniDb*)malloc(sizeof(depOfUniDb));
			memset(newDepOfUni, 0, sizeof(depOfUniDb));

			newDepOfUni -> depId = newDep -> depId;
			newDepOfUni -> uniId = uni -> uniId;
			newDepOfUni -> scoreType = newDep -> scoreType;
			newDepOfUni -> quota = quota;


			/* departmens of uni listesini oku */
			readDepOfUniDb(&depOfUniList);

			/* listedeki son elemani bul */
			depOfUni = depOfUniList;
			while(depOfUni -> next != NULL)
			{
				depOfUni = depOfUni -> next;
			}

			newDepOfUni -> keyId = depOfUni -> keyId + 1;

			/* listeye ekle */

			depOfUni -> next = newDepOfUni;


			/* dep of uni dosyasina yaz */

			fDepOfUni = fopen("depofunis.bin", "wb");


			depOfUni = depOfUniList;
			while(depOfUni != NULL)
			{
				fwrite(depOfUni, sizeof(depOfUniDb), 1, fDepOfUni);

				depOfUni = depOfUni -> next;
			}

			fclose(fDepOfUni);

			printf("Universite icin departman eklendi.\n");
		}


		memset(choice, 0, sizeof(choice));
		printf("Bu departman icin baska bir universite eklemek ister misiniz? E/H: ");
		scanf("%s", choice, 1);

	}while (choice[0] == 'E' || choice[0] == 'e');



	/* hafizayi temizle  */
	freeDepartmentsDb(&depList);
	freeUniversitiesDb(&uniList);
	freeDepOfUniDb(&depOfUniList);

	mypause();
}


/* bolum silme isini yapar
 * silinen bolumu database dosyasindan cikarir */
void deleteDepartment()
{
	char				depName[128], c;
	int					i;
	departmentsDb		*depList=NULL, *dep, *depPrev, *dep2;
	depOfUniDb			*depOfUniList, *depOfUni, *depOfUniPrev, *depOfUni2;
	FILE				*fDep, *fDepOfUni;


	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n");
	printf("Departman kaydi silme:\n\n");

	flushStdin();
	printf("Departmanin adini giriniz: ");
	gets(depName);


	/* universite listesini oku */
	readDepartmentsDb(&depList);

	/* liste icerisinde silinmek istenen departmani ara */
	depPrev = depList;
	dep = depList;
	while(dep != NULL)
	{
		if(strcmp(dep -> depName , depName) == 0)
		{
			/* silecegimiz dep kaydini bulduk */
			break;
		}


		depPrev = dep;
		dep = dep -> next;
	}

	if(dep == NULL)
	{
		printf("Kayitlarda bu isimli bir departman yok!\n");
	}
	else
	{
		/* bu dep'den sonraki kayitlarin keyId'lerini birer azalt */

		dep2 = dep -> next;
		while(dep2 != NULL)
		{
			dep2 -> keyId--;

			dep2 = dep2 -> next;
		}


		/* bu uni'yi listeden cikar */
		if(dep == depList)
		{
			depList = dep -> next;
		}
		else
		{
			depPrev -> next = dep -> next;
		}

		/* yeni listeyi database dosyasina yaz */

		fDep = fopen("departments.bin", "wb");

		dep2 = depList;
		while(dep2 != NULL)
		{
			fwrite(dep2, sizeof(departmentsDb), 1, fDep);

			dep2 = dep2 -> next;
		}

		fclose(fDep);


		/* bu department kaydini dep of uni listesinden de sil */
		readDepOfUniDb(&depOfUniList);

		depOfUni = depOfUniList;
		depOfUniPrev = depOfUniList;
		while(depOfUni != NULL)
		{
			if(depOfUni -> depId == dep -> depId)
			{
				/* bu kayittan sonraki kayitlarin keyId'lerini birer azalt */

				depOfUni2 = depOfUni -> next;
				while(depOfUni2 != NULL)
				{
					depOfUni2 -> keyId--;

					depOfUni2 = depOfUni2 -> next;
				}


				/* kaydi listeden cikar */
				if(depOfUni == depOfUniList) /* listenin ilk elemaniysa */
				{
					depOfUniList = depOfUni -> next;
					depOfUniPrev = depOfUni -> next;
				}
				else
				{
					depOfUniPrev -> next = depOfUni -> next;
				}

				/* hafizayi bosalt */
				free(depOfUni);

				/* kaldigin yerden devam et */
				depOfUni = depOfUniPrev -> next;
			}
			else
			{
				depOfUniPrev = depOfUni;
				depOfUni = depOfUni -> next;
			}
		}


		/* yeni dep of uni listesini database dosyasina yaz */

		fDepOfUni = fopen("depofunis.bin", "wb");

		depOfUni = depOfUniList;
		while(depOfUni != NULL)
		{
			fwrite(depOfUni, sizeof(depOfUniDb), 1, fDepOfUni);

			depOfUni = depOfUni -> next;
		}

		fclose(fDepOfUni);


		/* hafizayi bosalt */
		free(dep);


		printf("Departman kaydi silindi.\n");
	}


	/* hafizayi temizle SERCAN */
	freeDepartmentsDb(&depList);
	freeDepOfUniDb(&depOfUniList);

	mypause();
}


/* Ogrenci ad soyad girerek puan goruntuleme */
void displayScoreByName()
{
	char					stName[128], stSurname[128];
	studentsInfoDb			*stInfoList, *stInfo;
	studentsPreferenceDb	*stPrefList, *stPref;


	memset(stName, 0, sizeof(stName));
	memset(stSurname, 0, sizeof(stSurname));

	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n");
	printf("Ogrenci bilgileri goruntuleme:\n\n");

	printf("Ogrencinin adini giriniz: ");
	scanf("%s", stName, 64);

	printf("Ogrencinin soyadini giriniz: ");
	scanf("%s", stSurname, 64);


	/* student info listesini oku */
	readStudentsInfoDb(&stInfoList);

	/* listeyi dolas */
	stInfo = stInfoList;

	while(stInfo != NULL)
	{

		if(strcmp(stInfo -> name, stName) == 0 &&
		   strcmp(stInfo -> surname, stSurname) == 0)
		{
			/* ogrenciyi bulduk */
			break;
		}
		stInfo = stInfo -> next;
	}


	if(stInfo == NULL)
	{
		printf("Bu isimle bir ogrenci kaydi bulunmamaktadir!\n");
	}
	else
	{
		/* student pref listesini oku */
		readStudentsPreferenceDb(&stPrefList);

		/* listeyi dolas */
		stPref = stPrefList;

		while(stPref != NULL)
		{
			if(isEqualBigInts(&(stPref -> studentId), &(stInfo -> studentId)))
			{
				break;
			}

			stPref = stPref -> next;
		}

		if(stPref -> scoreType == SCORE_TYPE_QUANTATIVE)
		{
			printf("Ogrencinin puan turu SAYISAL\n");
		}
		else
		{
			printf("Ogrencinin puan turu SOZEL\n");
		}

		printf("Sayisal puan: %.3f\n"
			   "Sozel puan: %.3f\n\n" , 
				stPref -> quantativeScore, stPref -> verbalScore);
	}


	/* hafizayi temizle */
	freeStudentsInfoDb(&stInfoList);
	freeStudentsPreferenceDb(&stPrefList);

	mypause();
}


/* Ogrenci ad soyad girerek yerlestirildigi bolumu goruntuleme */
void displayPlacementByName()
{
	char					stName[128], stSurname[128];
	studentsInfoDb			*stInfoList, *stInfo;
	studentsPreferenceDb	*stPrefList, *stPref;
	universitiesDb			*uniList, *uni;
	departmentsDb			*depList, *dep;


	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n");
	printf("Ogrenci bilgileri goruntuleme:\n\n");

	printf("Ogrencinin adini giriniz: ");
	scanf("%s", stName, 64);

	printf("Ogrencinin soyadini giriniz: ");
	scanf("%s", stSurname, 64);


	/* student info listesini oku */
	readStudentsInfoDb(&stInfoList);

	/* listeyi dolas */
	stInfo = stInfoList;

	while(stInfo != NULL)
	{

		if(strcmp(stInfo -> name, stName) == 0 &&
		     strcmp(stInfo -> surname, stSurname) == 0)
		{
			/* ogrenciyi bulduk */
			break;
		}
		stInfo = stInfo -> next;
	}


	if(stInfo == NULL)
	{
		printf("Bu isimle bir ogrenci kaydi bulunmamaktadir!\n");
	}
	else
	{
		/* student pref listesini oku */
		readStudentsPreferenceDb(&stPrefList);

		/* listeyi dolas */
		stPref = stPrefList;

		while(stPref != NULL)
		{
			if(isEqualBigInts(&(stPref -> studentId), &(stInfo -> studentId)))
			{
				break;
			}

			stPref = stPref -> next;
		}


		if(stPref -> placedDepId == -1 || stPref -> placedUniId == -1)
		{
			printf("Bu ogrenci herhangi bir bolume yerlesememistir.\n");
		}
		else
		{
			/* uni ve dep bilgilerini oku */
			readUniversitiesDb(&uniList);
			readDepartmentsDb(&depList);

			/* listeleri dolasarak ogrencinin yerlestigi uni ve dep bilgilerini bul */

			uni = uniList;
			while(uni != NULL)
			{
				if(uni -> uniId == stPref -> placedUniId)
				{
					printf("Universite: %s\n", uni -> uniName);
					break;
				}

				uni = uni -> next;
			}

			dep = depList;
			while(dep != NULL)
			{
				if(dep -> depId == stPref -> placedDepId)
				{
					printf("Bolum: %s\n", dep -> depName);
					break;
				}

				dep = dep -> next;
			}
		}
	}


	/* hafizayi temizle */
	freeStudentsInfoDb(&stInfoList);
	freeStudentsPreferenceDb(&stPrefList);
	freeUniversitiesDb(&uniList);
	freeDepartmentsDb(&depList);

	mypause();
}


/* TCKN girerek puan goruntuleme */
void displayScoreById()
{
	char					tckn[16];
	studentsInfoDb			*stInfoList , *stInfo;
	studentsPreferenceDb	*stPrefList , *stPref;
	bigInt					id;



	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n" );
	printf("Ogrenci bilgileri goruntuleme:\n\n");

	printf("Ogrencinin TCKN'sini giriniz: ");
	scanf("%s", tckn, 16);

	stringToBigInt(tckn, &id);


	/* student info listesini oku */
	readStudentsInfoDb(&stInfoList);

	/* listeyi dolas */
	stInfo = stInfoList;

	while(stInfo != NULL)
	{
		if(isEqualBigInts(&(stInfo -> studentId), &id))
		{
			/* ogrenciyi bulduk */
			break;
		}

		stInfo = stInfo -> next;
	}


	if(stInfo == NULL)
	{
		printf("Bu TCKN'li bir ogrenci kaydi bulunmamaktadir!\n");
	}
	else
	{
		printf("%s %s\n", stInfo -> name, stInfo -> surname);

		/* student pref listesini oku */
		readStudentsPreferenceDb(&stPrefList);

		/* listeyi dolas */
		stPref = stPrefList;

		while(stPref != NULL)
		{
			if(isEqualBigInts(&(stPref -> studentId), &(stInfo -> studentId)))
			{
				break;
			}

			stPref = stPref -> next;
		}

		if (stPref -> scoreType == SCORE_TYPE_QUANTATIVE)
		{
			printf("Ogrencinin puan turu SAYISAL\n");
		}
		else
		{
			printf("Ogrencinin puan turu SOZEL\n");
		}

		printf("Sayisal puan: %.3f\n"
			   "Sozel puan: %.3f\n\n", 
				stPref -> quantativeScore, stPref -> verbalScore );
	}


	/* hafizayi temizle */
	freeStudentsInfoDb(&stInfoList);
	freeStudentsPreferenceDb(&stPrefList);

	mypause();
}


/* TCKN girerek yerlestirildigi bolumu goruntuleme */
void displayPlacementById()
{
	char					tckn[16];
	studentsInfoDb			*stInfoList, *stInfo;
	studentsPreferenceDb	*stPrefList, *stPref;
	universitiesDb			*uniList, *uni;
	departmentsDb			*depList, *dep;
	bigInt					id;


	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n" );
	printf("Ogrenci bilgileri goruntuleme:\n\n");

	printf("Ogrencinin TCKN'sini giriniz: ");
	scanf("%s", tckn, 16);

	stringToBigInt(tckn, &id);


	/* student info listesini oku */
	readStudentsInfoDb(&stInfoList);

	/* listeyi dolas */
	stInfo = stInfoList;

	while(stInfo != NULL)
	{
		if(isEqualBigInts(&(stInfo -> studentId), &id))
		{
			/* ogrenciyi bulduk */
			break;
		}

		stInfo = stInfo -> next;
	}


	if(stInfo == NULL)
	{
		printf("Bu isimle bir ogrenci kaydi bulunmamaktadir!\n");
	}
	else
	{
		printf("%s %s\n", stInfo -> name, stInfo -> surname);

		/* student pref listesini oku */
		readStudentsPreferenceDb(&stPrefList);

		/* listeyi dolas */
		stPref = stPrefList;

		while(stPref != NULL)
		{
			if(isEqualBigInts(&(stPref -> studentId), &(stInfo -> studentId)))
			{
				break;
			}

			stPref = stPref -> next;
		}

		if(stPref -> placedDepId == -1 || stPref -> placedUniId == -1)
		{
			printf("Bu ogrenci herhangi bir bolume yerlesememistir.\n");
		}
		else
		{
			/* uni ve dep bilgilerini oku */
			readUniversitiesDb(&uniList);
			readDepartmentsDb(&depList);

			/* listeleri dolasarak ogrencinin yerlestigi uni ve dep bilgilerini bul */

			uni = uniList;
			while(uni != NULL)
			{
				if (uni -> uniId == stPref -> placedUniId)
				{
					printf("Universite: %s\n", uni -> uniName);
					break;
				}

				uni = uni -> next;
			}

			dep = depList;
			while(dep != NULL)
			{
				if(dep -> depId == stPref -> placedDepId)
				{
					printf("Bolum: %s\n", dep -> depName);
					break;
				}

				dep = dep -> next;
			}
		}
	}


	/* hafizayi temizle */
	freeStudentsInfoDb(&stInfoList);
	freeStudentsPreferenceDb(&stPrefList);
	freeUniversitiesDb(&uniList);
	freeDepartmentsDb(&depList);

	mypause();
}


/* Butun universiteleri ve toplam kotalarini goruntuleme */
void displayAllUnis()
{
	universitiesDb		*uniList, *uni;
	depOfUniDb			*depOfUniList, *depOfUni;
	int					totalQuota;


	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n");
	printf("Universiteler ve toplam kotalari:\n\n");


	/* universite ve dep of uni listelerini oku */
	readUniversitiesDb(&uniList);
	readDepOfUniDb(&depOfUniList);


	/* uni listesini dolas */
	uni = uniList;

	while(uni != NULL)
	{

		printf("%s: \tToplam kota: ", uni -> uniName);


		/* dep of uni listesini oku ve toplam kotayi hesapla */

		totalQuota = 0;
		depOfUni = depOfUniList;

		while(depOfUni != NULL)
		{

			if(depOfUni -> uniId == uni -> uniId)
			{
				totalQuota += depOfUni -> quota;
			}

			depOfUni = depOfUni -> next;
		}

		/* toplam kotayi yazdir */
		printf("%d\n", totalQuota);

		uni = uni -> next;
	}


	/* hafizayi temizle */
	freeUniversitiesDb(&uniList);
	freeDepOfUniDb(&depOfUniList);

	mypause();
}


/* Bir universitenin bolumlerini goruntuleme */
void displayDepartmentsOfUni()
{
	
	universitiesDb		*uniList, *uni;
	departmentsDb		*depList, *dep;
	depOfUniDb			*depOfUniList, *depOfUni;
	char				uniName[128], c;
	int					i, ch;


	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n");
	printf("Universite ve Bolumleri:\n\n");

	flushStdin();
	printf("Universitenin adini giriniz: ");
	gets(uniName);


	/* universite, department ve dep of uni listelerini oku */
	readUniversitiesDb(&uniList);
	readDepartmentsDb(&depList);
	readDepOfUniDb(&depOfUniList);


	/* uni listesini dolas */
	uni = uniList;

	while(uni != NULL)
	{
		if(strcmp(uni -> uniName, uniName) == 0)
		{
			/* uni kaydini bulduk */
			break;
		}

		uni = uni -> next;
	}


	if(uni == NULL)
	{
		printf("Bu isimle bir universite kaydi bulunmamaktadir!\n");
	}
	else
	{
		/* dep of uni listesini dolas */
		depOfUni = depOfUniList;

		while(depOfUni != NULL)
		{
			if(depOfUni -> uniId == uni -> uniId)
			{
				/* bu bolumun bilgilerini bul */
				dep = searchDepartmentById(depList, depOfUni -> depId);

				printf("Bolum: %s, Kota: %d\n", dep -> depName, depOfUni -> quota);
			}

			depOfUni = depOfUni -> next;
		}
	}


	/* hafizayi temizle */
	freeUniversitiesDb(&uniList);
	freeDepartmentsDb(&depList);
	freeDepOfUniDb(&depOfUniList);

	mypause();
}



/* Bir bolumun yerlestirme istatistiklerini goruntuleme */
void displayPlacementStatsOfDep()
{
	departmentsDb			*depList, *dep;
	depOfUniDb				*depOfUniList, *depOfUni;
	studentsPreferenceDb	*stPrefList, *stPref;
	char					depName[128], c;
	float					maxScore, minScore;
	int						totalPlaced, i;


	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n");
	printf("Bolum istatistikleri:\n\n");

	flushStdin();
	printf("Bolumun adini giriniz: ");
	gets(depName);


	/* department ve dep of uni listelerini oku */
	readDepartmentsDb(&depList);
	readDepOfUniDb(&depOfUniList);
	readStudentsPreferenceDb(&stPrefList);


	/* dep listesini dolas */
	dep = depList;

	while(dep != NULL)
	{
		if(strcmp(dep -> depName , depName) == 0)
		{
			/* dep kaydini bulduk */
			break;
		}

		dep = dep -> next;
	}


	if(depName == NULL)
	{
		printf("Bu isimle bir bolum kaydi bulunmamaktadir!\n");
	}
	else
	{
		maxScore = 0.0;
		minScore = 1001.0;

		
		/* student pref listi dolas, bu bolume yerlesen ogrencileri bul */

		stPref = stPrefList;

		while(stPref != NULL)
		{
			if(stPref -> placedDepId == dep -> depId)
			{

				if(dep -> scoreType == SCORE_TYPE_QUANTATIVE)
				{
					if(stPref -> quantativeScore > maxScore)
						maxScore = stPref -> quantativeScore;

					if(stPref -> quantativeScore < minScore)
						minScore = stPref -> quantativeScore;
				}
				else
				{
					if (stPref -> verbalScore > maxScore)
						maxScore = stPref -> verbalScore;

					if (stPref -> verbalScore < minScore)
						minScore = stPref -> verbalScore;
				}

			}

			stPref = stPref -> next;
		}


		/* dep of uni listesini dolas ve bu bolume yerlesen toplam ogrenci sayisini bul */

		totalPlaced = 0;
		depOfUni = depOfUniList;
		while(depOfUni != NULL)
		{

			if(depOfUni -> depId == dep -> depId)
			{
				totalPlaced += depOfUni -> placedCount;
			}

			depOfUni = depOfUni -> next;
		}


		/* istatistikleri yazdir */

		printf("Bu bolume yerlesen ogrenci sayisi: %d\n", totalPlaced);
		printf("Tavan puan: %.3f\n", maxScore);
		if(minScore == 1001.0)
			minScore = 0.0;
		printf("Taban puan: %.3f\n", minScore);


	}


	/* hafizayi temizle */
	freeDepartmentsDb(&depList);
	freeDepOfUniDb(&depOfUniList);
	freeStudentsPreferenceDb(&stPrefList);

	mypause();
}



/* Bir universitenin yerlestirme istatistiklerini goruntuleme */
void displayPlacementStatsOfUni()
{
	universitiesDb			*uniList, *uni;
	departmentsDb			*depList, *dep;
	depOfUniDb				*depOfUniList, *depOfUni;
	studentsPreferenceDb	*stPrefList, *stPref;
	char					uniName[128], c;
	float					maxScore, minScore;
	int						i;


	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n");
	printf("Universite istatistikleri:\n\n");

	flushStdin();
	printf("Universite adini giriniz: ");
	gets(uniName);



	/* universite, department ve dep of uni listelerini oku */
	readUniversitiesDb(&uniList);
	readDepartmentsDb(&depList);
	readDepOfUniDb(&depOfUniList);
	readStudentsPreferenceDb(&stPrefList);


	/* uni listesini dolas */
	uni = uniList;

	while(uni != NULL)
	{
		if(strcmp(uni -> uniName , uniName) == 0)
		{
			/* uni kaydini bulduk */
			break;
		}

		uni = uni -> next;
	}

	if(uni == NULL)
	{
		printf("Bu isimle bir universite kaydi bulunmamaktadir!\n");
	}
	else
	{
		/* bu universitede bulunan bolumler dolas */

		depOfUni = depOfUniList;
		while(depOfUni != NULL)
		{
			if(depOfUni -> uniId == uni -> uniId)
			{
				dep = searchDepartmentById(depList , depOfUni -> depId);

				/* bolum bilgilerini yazdir */
				printf("Bolum adi: %s\n", dep -> depName);

				if(dep -> scoreType == SCORE_TYPE_QUANTATIVE)
				{
					printf("\tSAYISAL\n");
				}
				else
				{
					printf("\tSOZEL\n");
				}

				printf("\tBolume yerlesen ogrenci sayisi: %d\n", 
													   depOfUni -> placedCount);

				/* ogrenci listesini dolas ve min max score hesapla */

				maxScore = 0.0;
				minScore = 1001.0;
				stPref = stPrefList;

				while(stPref != NULL)
				{
					if(stPref -> placedDepId == dep -> depId)
					{

						if(dep -> scoreType == SCORE_TYPE_QUANTATIVE)
						{
							if(stPref -> quantativeScore > maxScore)
								maxScore = stPref -> quantativeScore;

							if(stPref -> quantativeScore < minScore)
								minScore = stPref -> quantativeScore;
						}
						else
						{
							if(stPref -> verbalScore > maxScore)
								maxScore = stPref -> verbalScore;

							if(stPref -> verbalScore < minScore)
								minScore = stPref -> verbalScore;
						}
					}

					stPref = stPref -> next;
				}

				printf("\tTavan puan: %.3f\n", maxScore);
				if ( minScore == 1001.0 )
					minScore = 0.0;
				printf("\tTaban puan: %.3f\n", minScore);

			}

			depOfUni = depOfUni -> next;
		}
	}


	/* hafizayi temizle */
	freeUniversitiesDb(&uniList);
	freeDepartmentsDb(&depList);
	freeDepOfUniDb(&depOfUniList);
	freeStudentsPreferenceDb(&stPrefList);

	mypause();
}



/* Sinav istatistiklerini goruntuleme */
void displayExamStats()
{
/*Sinavda ogrenci sayısı, bir universiteye yerleştirilen ogrenci sayısı, 
 * ilk tercihinde yerleştirilen öğrenci sayısı, bosta kalan sayisi */

	
	depOfUniDb				*depOfUniList, *depOfUni;
	studentsPreferenceDb	*stPrefList, *stPref;
	studentsInfoDb			*stInfoList, *stInfo;
	int						totalEmptyQuota, totalStudent, totalPlaced, 
							totalNotPlaced, totalPlacedToFirstPref;


	system("cls");

	printf("\nOgrenci Yerlestirme Programi\n");
	printf("------------------\n\n");
	printf("Sinav istatistikleri:\n\n");


	/* sinava giren ogrenci sayisini hesapla */

	readStudentsInfoDb(&stInfoList);

	totalStudent = 0;
	stInfo = stInfoList;
	while(stInfo != NULL)
	{
		totalStudent++;

		stInfo = stInfo -> next;
	}

	printf("Sinava giren ogrenci sayisi: %d\n", totalStudent );



	/* herhangi bir bolume yerlesen ogrenci sayisini hesapla */

	readStudentsPreferenceDb(&stPrefList);

	totalPlaced = 0;
	totalNotPlaced = 0;
	totalPlacedToFirstPref = 0;
	stPref = stPrefList;
	while(stPref != NULL)
	{
		/* yerlesemeyenler */
		if(stPref -> placedDepId == -1 || stPref -> placedUniId == -1)
		{
			totalNotPlaced++;
		}
		else
		{
			totalPlaced++;

			/* ilk tercihine yerlesenler */
			if(stPref -> placedDepId == stPref -> depIds[0] || 
			   stPref -> placedUniId == stPref -> uniIds[0])
			{
				totalPlacedToFirstPref++;
			}
		}

		stPref = stPref -> next;
	}

	printf("Herhangi bir bolume yerlesebilenler: %d\n", totalPlaced);
	printf("Hic bir bolume yerlesemeyenler: %d\n", totalNotPlaced);
	printf("Ilk tercihine yerlesebilenler: %d\n", totalPlacedToFirstPref);


	/* bos kalan kotayi hesapla */

	readDepOfUniDb(&depOfUniList);

	totalEmptyQuota = 0;
	depOfUni = depOfUniList;
	while(depOfUni != NULL)
	{
		totalEmptyQuota += depOfUni -> quota - depOfUni -> placedCount;


		depOfUni = depOfUni -> next;
	}

	printf("Bos kalan toplam kota: %d\n", totalEmptyQuota);


	/* hafizayi temizle */
	freeStudentsInfoDb(&stInfoList);
	freeStudentsPreferenceDb(&stPrefList);
	freeDepOfUniDb(&depOfUniList);


	mypause();
}



/* studentsInfoDb listesini hafizadan temizler */
void freeStudentsInfoDb(studentsInfoDb **pStdList )
{
	studentsInfoDb *pStInfo, *pStInfoNext;

	pStInfo = *pStdList;
	while(pStInfo != NULL)
	{
		pStInfoNext = pStInfo -> next;
		free(pStInfo);

		pStInfo = pStInfoNext;
	}

	*pStdList = NULL;
}

/* studentsPreferenceDb listesini hafizadan temizler */
void freeStudentsPreferenceDb(studentsPreferenceDb **pStdPrefList)
{
	studentsPreferenceDb *pStPref, *pStPrefNext;

	pStPref = *pStdPrefList;
	while(pStPref != NULL)
	{
		pStPrefNext = pStPref -> next;
		free(pStPref);

		pStPref = pStPrefNext;
	}

	*pStdPrefList = NULL;
}



/* depOfUniDb listesini hafizadan temizler */
void freeDepOfUniDb(depOfUniDb **pDepOfUniList)
{
	depOfUniDb *pDep, *pDepNext;

	pDep = *pDepOfUniList;
	while(pDep != NULL)
	{
		pDepNext = pDep -> next;
		free(pDep);

		pDep = pDepNext;
	}


	*pDepOfUniList = NULL;
}



/* universitiesDb listesini hafizadan temizler */
void freeUniversitiesDb(universitiesDb **pUniList)
{
	universitiesDb *pUni, *pUniNext;

	pUni = *pUniList;
	while(pUni != NULL)
	{
		pUniNext = pUni -> next;
		free(pUni);

		pUni = pUniNext;
	}

	*pUniList = NULL;
}



/* departmentsDb listesini hafizadan temizler */
void freeDepartmentsDb(departmentsDb **pDepList)
{
	departmentsDb *pDep, *pDepNext;

	pDep = *pDepList;
	while(pDep != NULL)
	{
		pDepNext = pDep -> next;
		free( pDep );

		pDep = pDepNext;
	}

	*pDepList = NULL;
}
