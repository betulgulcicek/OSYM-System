
#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#if 0
#define	_DEBUG_MODE_
#endif


typedef enum scoreType_e
{
	SCORE_TYPE_QUANTATIVE,
	SCORE_TYPE_VERBAL
}scoreType;


typedef struct bigInt_s
{
	unsigned int mspart , lspart;	/* most significant part, least significant part */
}bigInt;


typedef struct studentsNames_s
{
	bigInt		id;
	char		name[64];
	char		surname[64];
	unsigned int	bday_year;
	unsigned int	bday_month;
	unsigned int	bday_day;
	scoreType	scoreType;
	struct studentsNames_s *next;	
}studentsNames;


typedef struct studentsAddressInfo_s
{
	bigInt		id;
	bigInt		phone;
	char		email[64];
	char		address[256];
	struct studentsAddressInfo_s *next;
}studentsAddressInfo;


typedef struct departments_s
{
	char		university[128];
	unsigned int	uniId;
	char		department[128];
	unsigned int	depId;
	scoreType	scoreType;
	unsigned int	quota;
	struct departments_s *next;
}departments;


typedef struct preferences_s
{
	bigInt		studentId;
	unsigned int	uniIds[8];
	unsigned int	depIds[8];
	struct preferences_s *next;
}preferences;


typedef struct scores_s
{
	bigInt		studentId;
	float		quantativeScore;
	float		verbalScore;
	struct scores_s	*next;
}scores;



/* Asagidaki structurelar binary db dosya kayitleri icin */
typedef struct departmentsDb_s
{
	unsigned int	keyId;
	unsigned int	depId;
	char		depName[128];
	scoreType	scoreType;
	struct departmentsDb_s *next;
}departmentsDb;


typedef struct universitiesDb_s
{
	unsigned int	keyId;
	unsigned int	uniId;
	char		uniName[128];
	struct universitiesDb_s	*next;
}universitiesDb;


typedef struct depOfUniDb_s
{
	unsigned int	keyId;
	unsigned int	uniId;
	unsigned int	depId;
	unsigned int	quota;
	unsigned int	placedCount;
	scoreType	scoreType;
	struct depOfUniDb_s *next;
}depOfUniDb;


typedef struct studentsInfoDb_s
{
	unsigned int	keyId;
	bigInt		studentId;
	char		name[64];
	char		surname[64];
	bigInt		phone;
	char		email[64];
	char		address[256];
	struct studentsInfoDb_s	*next;
}studentsInfoDb;


typedef struct studentsPreferenceDb_s
{
	unsigned int	keyId;
	bigInt		studentId;
	unsigned int	bday_year;
	unsigned int	bday_month;
	unsigned int	bday_day;
	float		quantativeScore;
	float		verbalScore;
	scoreType	scoreType;
	unsigned int	uniIds[8];
	unsigned int	depIds[8];
	unsigned int	placedUniId;
	unsigned int	placedDepId;
	struct studentsPreferenceDb_s *next;
}studentsPreferenceDb;


#define	FALSE 0
#define	TRUE 1

int isEqualBigInts(bigInt *bi1, bigInt *bi2);
void stringToBigInt(char *str, bigInt *bi);
char* bigIntToString(bigInt *bi);

void readCsvFiles(studentsNames **pStNames, studentsAddressInfo **pStAddr, 
		  departments **pDeps, preferences **pPref, scores **pScr);
void createBinaryDbFiles(studentsNames *pStNames, studentsAddressInfo *pStAddr, 
			 departments *pDeps, preferences *pPref, scores *pScr);
void doPlacement();
void createCsvReports();
void createHtmlOutputs();
void sortStudentListByScoreType(studentsPreferenceDb **pStdList, scoreType scrType);
void placeStudents(studentsPreferenceDb *pStdList, depOfUniDb *pDepList, 
		   scoreType scrType);

void insertNewUniversity();
void deleteUniversity();

void insertNewDepartment();
void deleteDepartment();

void displayScoreByName();
void displayPlacementByName();
void displayScoreById();
void displayPlacementById();
void displayAllUnis();
void displayDepartmentsOfUni();
void displayPlacementStatsOfDep();
void displayPlacementStatsOfUni();
void displayExamStats();

int readLine(FILE *f, char *buf, unsigned int bufSize);
void parseStudentName(studentsNames *stdPtr, char *buffer, unsigned int bufLen);
void parseStudentAddress(studentsAddressInfo *stdAddrPtr, char *buffer ,
			 unsigned int bufLen);
void parseDepartment(departments *depPtr, char *buffer, unsigned int bufLen);
void parsePreference(preferences *prefPtr ,char *buffer ,unsigned int bufLen);
void parseScore(scores *scrPtr, char *buffer, unsigned int bufLen);

void readStudentsInfoDb(studentsInfoDb **pStdList);
void readStudentsPreferenceDb(studentsPreferenceDb **pStdPrefList);
void readDepOfUniDb(depOfUniDb **pDepOfUniList);
void readUniversitiesDb(universitiesDb **pUniList);
void readDepartmentsDb(departmentsDb **pDepList);

universitiesDb *searchUniversityById(universitiesDb *pUniList, unsigned int uniId);
departmentsDb *searchDepartmentById(departmentsDb *pDepList, unsigned int depId);
studentsInfoDb *searchStudentInfoById(studentsInfoDb *pStInfoList, bigInt *id);
studentsPreferenceDb *searchStudentPrefById(studentsPreferenceDb *pStPrefList, bigInt *id);

/* hafizayi temizleme fonksiyonlari */
void freeStudentsInfoDb(studentsInfoDb **pStdList);
void freeStudentsPreferenceDb(studentsPreferenceDb **pStdPrefList);
void freeDepOfUniDb(depOfUniDb **pDepOfUniList);
void freeUniversitiesDb(universitiesDb **pUniList);
void freeDepartmentsDb(departmentsDb **pDepList);



#endif	/* _COMMON_H_ */
