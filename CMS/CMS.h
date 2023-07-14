/********************************************************************/
/************** NAME : Eslam Osama Saad     *************************/
/************** DATE : 13 / 05 / 2023       *************************/
/************** VERSION : 1.0 			    *************************/
/************** SWC : console application 	*************************/
/********************************************************************/

#ifndef CMS_H_INCLUDED
#define CMS_H_INCLUDED

/********************************************************************/

//==================================

#define MAX_NUM_APPOI_DR_PER_DAY   12
#define MAX_NUM_APPOI_DR_PER_WEEK  36
#define MAX_NUM_NODES_CLINIC	   144
#define CLINIC_IS_FULL             1
#define CLINIC_IS_NOT_FULL         0

#define admin_username             "admin"
#define admin_password             "98071539"

#define DR_EO_username              "Eslam Osama"
#define DR_EO_password              "DOCEO2023"

#define DR_SM_username              "Shon Murphy"
#define DR_SM_password              "DOCSM2023"

#define DR_NM_username              "Neil Millendes"
#define DR_NM_password              "DOCNM2023"

#define DR_MS_username              "Mohamed Saleh"
#define DR_MS_password              "DOCMS2023"

//==================================

typedef enum{
	Alexandria = 1,
	Aswan,
	Asyut,
	Beheira,
	BeniSuef,
	Cairo,
	Dakahlia,
	Damietta,
	Faiyum,
	Gharbia,
	Giza,
	Ismailia,
	KafrEl_Sheikh,
	Luxor,
	Matruh,
	Minya,
	Monufia,
	NewValley,
	NorthSinai,
	PortSaid,
	Qalyubia,
	Qena,
	RedSea,
	Sharqia,
	Sohag,
	SouthSinai,
	Suez
}EGY_GOV;

typedef enum{
	sat_per1 = 1,
	sat_per2,
	sun_per1,
	sun_per2,
	mon_per1,
	mon_per2,
	tues_per1,
	tues_per2,
	wens_per1,
	wens_per2,
	thur_per1,
	thur_per2
}DAY;

typedef enum{
    from_2_to_2_20 = 1,
	from_2_20_to_2_40,
	from_2_40_to_3,
	from_3_to_3_20,
	from_3_20_to_3_40,
	from_3_40_to_4,
	from_4_to_4_20,
	from_4_20_to_4_40,
	from_4_40_to_5,
	from_5_to_5_20,
	from_5_20_to_5_40,
	from_5_40_to_6,
    from_6_to_6_20,
	from_6_20_to_6_40,
	from_6_40_to_7,
	from_7_to_7_20,
	from_7_20_to_7_40,
	from_7_40_to_8,
	from_8_to_8_20,
	from_8_20_to_8_40,
	from_8_40_to_9,
	from_9_to_9_20,
	from_9_20_to_9_40,
	from_9_40_to_10
}appointment;

typedef enum{
	dr_shon_murphy = 1,
	dr_neil_millendes,
	dr_eslam_osama,
	dr_mohamed_saleh
}DR;

typedef enum{
	stomach_aches = 1,
	diarrhea,
	colds_and_flu,
	allergies,
	celiac_disease,
	other
}problem;

typedef enum{
	HEAP_FULL,
	OK,
	EMPTY_CLINIC_SCHED,
	WRONG_CODE,
	WRONG_NAME,
	WRONG_GENDER,
	WRONG_AGE,
	WRONG_PHON_NUM,
	WRONG_GOVER_NUM,
	WRONG_DISTR_FORMAT,
	WRONG_STRE_FORMAT,
	WRONG_HOME_NUM_FORMAT,
	WRONG_DR_NUM,
	EMPTY_SCHE_CLINIC,
	FULL_SCHE_CLINIC,
	DR_WEEK_SCHED_FULL,
	DR_WEEK_SCHED_EMPTY,
	WRONG_DAY_NUM,
	DR_DAY_SCHED_FULL,
	DR_DAY_SCHED_EMPTY,
	WRONG_APPOI_NUM,
	NON_AVAIL_APPOI,
	WRONG_PROB_NUM,
	PATIENT_NODE_EXSISTED,
	PATIENT_NODE_NOT_EXSISTED,
	WRONG_USERNAME,
	WRONG_PASSW
}CLINIC_DATA_COND;


typedef enum{
	CHECK_DR_DAY,
	CHECK_DR_WEEK,
	ADDING_NEW_PATIENT,
	GETTING_CODE_TO_MODIFY,
	GETTING_CODE_TO_DELETE,
	PRINT_ALL_DATA,
	PRINT_RES_DATA,
	PRINT_BIO_DATA,
	NORM_PRINT,
	WITH_ADD_PAT,
	WITH_MOD_PAT,
	FOR_PER1,
	FOR_PER2,
	ADMIN,
	DOCTOR
}USAGE_COND;

/********************************************************************/

/*THE FOLLOWING IS THE ACTUAL */
#define NUM_PER_WEEK    12  //number of periods per week (working days) = (num. of working days per week) * (num. of periods per day) = 6 * 2 = 12
typedef struct{
    DR doctor;
    DAY day;
}DR_INFO;

/********************************************************************/

static DR_INFO clinic_schedule[NUM_PER_WEEK] = { {dr_neil_millendes  , sat_per1}  ,
                                               {dr_shon_murphy     , sat_per2}  ,
                                               {dr_eslam_osama     , sun_per1}  ,
                                               {dr_shon_murphy     , sun_per2}  ,
                                               {dr_neil_millendes  , mon_per1}  ,
                                               {dr_mohamed_saleh   , mon_per2}  ,
                                               {dr_eslam_osama     , tues_per1} ,
                                               {dr_mohamed_saleh   , tues_per2} ,
                                               {dr_neil_millendes  , wens_per1} ,
                                               {dr_shon_murphy     , wens_per2} ,
                                               {dr_eslam_osama     , thur_per1} ,
                                               {dr_mohamed_saleh   , thur_per2} };


/********************************************************************/

typedef struct{
	EGY_GOV gover;
	u8 distr[36];
	u8 street[36];
	u16 home_no;
}address;

typedef struct{
    u8 patient_code[4];
	u8 name[36];
	u8 gender;
	address pat_addre;
	u16 age;
	s8 phone_num[12];
	DR doctor;
	DAY working_day;
    problem illness;
    appointment appoi;
}patient_data;

typedef struct node{
	patient_data data;
	struct node *next;
	struct node *prev;
}patient_node;

typedef struct{
	u8 node_nums;
	patient_node *head;
	patient_node *tail;
}clinic;

/********************************************************************/

typedef struct BST{
	patient_data data;
	struct BST *left;
	struct BST *right;
}tree_node;

typedef tree_node*  ptr_tree;

/********************************************************************/
/********************************************************************/
/**********    FUNCTIONS    **********/

void create_clinic_sched(clinic *ptr_c);

/********************************************************************/

bool clinic_sched_empty(clinic *ptr_c);

/********************************************************************/

void clear_clinic_sched(clinic *ptr_c);

/********************************************************************/

bool clinic_sched_full(clinic *ptr_c);

/********************************************************************/

CLINIC_DATA_COND search_patient_with_code(clinic *ptr_c  , u8 patient_code[4]);

/********************************************************************/

CLINIC_DATA_COND patient_code(clinic *ptr_c , patient_node *ptr , USAGE_COND usage);

/*****************************************************************/

CLINIC_DATA_COND patient_name(patient_node *ptr);

/********************************************************************/

CLINIC_DATA_COND patient_gender(patient_node *ptr);

/********************************************************************/

CLINIC_DATA_COND patient_age(patient_node *ptr);

/********************************************************************/

CLINIC_DATA_COND patient_phon_num(patient_node *ptr);

/********************************************************************/

//Getting address from patient :
//=============================
//1- governments
CLINIC_DATA_COND patient_addre_gover(patient_node *ptr);

/********************************************************************/

//2- district
CLINIC_DATA_COND patient_addre_distr(patient_node *ptr);

/********************************************************************/

//2- street
CLINIC_DATA_COND patient_addre_stre(patient_node *ptr);

/********************************************************************/

CLINIC_DATA_COND patient_addre_home_num(patient_node *ptr);

/********************************************************************/

CLINIC_DATA_COND patient_choose_dr(patient_node *ptr);

/********************************************************************/

CLINIC_DATA_COND patient_working_day(DAY *ptr_working_day , DAY Dr_avail_day[3] , USAGE_COND use);

/********************************************************************/

CLINIC_DATA_COND patient_appoi_num(patient_node *ptr);

/********************************************************************/

CLINIC_DATA_COND patient_choose_prob(patient_node *ptr);

/********************************************************************/

/*
using the following function we can check if the chosen appointment is available or not
based on appointments picked by another patients in clinic schedule list
*/
CLINIC_DATA_COND check_appoi_avail(clinic *ptr_c , patient_node *ptr);

/********************************************************************/

/*
using the following function we can check if the chosen doctor is available or not using
number of appointments per week for doctor or if doctor available in the chose day using
number of appointments per day for doctor based on appointments picked by another patients
in clinic schedule list
*/
CLINIC_DATA_COND check_sched_dr(clinic *ptr_c , DR doctor , DAY day , USAGE_COND usage);

/********************************************************************/

CLINIC_DATA_COND getting_username(u8 mem_username[15] , USAGE_COND use);

/********************************************************************/

CLINIC_DATA_COND getting_passw(u8 mem_passw[10] , u8 *ptr_username ,USAGE_COND use);

/********************************************************************/

void show_drs_name(void);

/********************************************************************/

void getting_dr_name(patient_node *ptr);

/********************************************************************/

void print_working_day_period(DAY day);

/********************************************************************/

void show_working_days_period_list(DR doctor , DAY day_avail_list[3] , USAGE_COND use);

/********************************************************************/

void getting_patient_per(patient_node *ptr);

/********************************************************************/

void show_appointment_list(patient_node *ptr);

/********************************************************************/

void show_appointment_patient(patient_node *ptr);

/********************************************************************/

void print_list_gover(void);

/********************************************************************/

void show_gover_patient(patient_node *ptr);

/********************************************************************/

void print_dise(void);

/********************************************************************/

void show_problem_patient(patient_node *ptr);

/********************************************************************/

/*if it returns 0 then it means there is no change on reservation of patient and
if it returns 1 then it means change happened on patient's eservation*/
bool getting_data_res(clinic *ptr_c , patient_node *ptr , USAGE_COND use);

/********************************************************************/

CLINIC_DATA_COND add_patient(clinic *ptr_c);

/********************************************************************/

void getting_dr(DR dr);

/********************************************************************/

void print_res_day_head(DAY day);

/********************************************************************/

void print_res_appoi(appointment appoi);

/********************************************************************/

void print_pat_data(clinic *ptr_c , patient_node *temp ,USAGE_COND use);

/********************************************************************/

bool mod_pat_bio_data(clinic *ptr_c ,  patient_node *ptr ,  patient_node *ptr1);

/********************************************************************/

void modify_pat_data(clinic *ptr_c);

/********************************************************************/

void getting_dr_period(USAGE_COND use);

/********************************************************************/

void print_DRs_schedule(void);

/********************************************************************/

void print_pat_res(clinic *ptr_c);

/********************************************************************/

void print_all_pat_data(clinic *ptr_c);

/********************************************************************/

void delete_pat_res(clinic *ptr_c);

/********************************************************************/
//======================================================================================================================================================
        /*************************   Doctor part   *************************/

void GoTo_doctor_section(clinic *ptr_c);

/********************************************************************/

void print_dr_wellcome_head(DR doctor);

/********************************************************************/

void print_one_DR_schedule(DR doctor);

/********************************************************************/

                    /**********DEALING WITH BINARY SEARCH TREE**********/

/********************************************************************/

void clear_BST(ptr_tree ptr);

/********************************************************************/

/*Binary Search Tree always follows rule of left < vertex < right*/
CLINIC_DATA_COND insert_node_BST(ptr_tree *ptr , patient_data pat);

/********************************************************************/

/*for method 1*/

void print_dr_day_head(DR doctor , DAY day);

/********************************************************************/

/*for method 2*/

void print_dr_week_head(DR doctor);

/********************************************************************/

/*for method 1*/

void print_day_data(clinic *ptr_c , DR doctor , DAY day);

/********************************************************************/

/*for method 2*/

void print_week_data(clinic *ptr_c , DR doctor);

/********************************************************************/

void print_BST_inorder(ptr_tree ptr);//LVR

//======================================================================================================================================================
/********************************************************************/
//======================================================================================================================================================
        /*************************   patient part   *************************/

CLINIC_DATA_COND print_avail_week_data(clinic *ptr_c , DR doctor);

/********************************************************************/

void GoTo_patient_section(clinic *ptr_c);

//======================================================================================================================================================
/********************************************************************/
//======================================================================================================================================================
        /*************************   Administrator part   *************************/

void GoTo_admin_section(clinic *ptr_c);

//======================================================================================================================================================
/********************************************************************/

void entry_window(clinic *ptr_c);

/********************************************************************/

#endif // CMS_H_INCLUDED
