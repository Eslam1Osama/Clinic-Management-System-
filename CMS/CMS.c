/********************************************************************/
/************** NAME : Eslam Osama Saad     *************************/
/************** DATE : 28 / 04 / 2023       *************************/
/************** VERSION : 1.0 			    *************************/
/************** SWC : console application 	*************************/
/********************************************************************/

#include<stdio.h>//for input output processes and getchar()
#include<stdbool.h>// to use bool
#include<stdlib.h>//for dynamic memory allocation
#include<string.h>//to use strcpy() & strcmp() & strlen() functions

#include"LIB.h"
#include"utility_control.h"

#include"CMS.h"

/********************************************************************/
/**********    FUNCTIONS    **********/

void create_clinic_sched(clinic *ptr_c)
{
   ptr_c->head = NULL;
   ptr_c->tail = NULL;
   ptr_c->node_nums = 0;
}

/********************************************************************/

bool clinic_sched_empty(clinic *ptr_c)
{
    return (!(ptr_c->head));
}

/********************************************************************/

void clear_clinic_sched(clinic *ptr_c)
{
    if(clinic_sched_empty(ptr_c) == 1)
        return;

    patient_node *temp = ptr_c->head;
    while(temp != NULL)
    {
        temp = temp->next;
        free(temp->prev);
        temp->prev = NULL;
    }

    ptr_c->node_nums = 0;
    ptr_c->head = NULL;
    ptr_c->tail = NULL;
}

/********************************************************************/

bool clinic_sched_full(clinic *ptr_c)
{
    if(ptr_c->node_nums == MAX_NUM_NODES_CLINIC)
        return CLINIC_IS_FULL;

    return CLINIC_IS_NOT_FULL;
}

/********************************************************************/

CLINIC_DATA_COND search_patient_with_code(clinic *ptr_c  , u8 patient_code[4])
{
    if(clinic_sched_empty(ptr_c) == 1)
       return EMPTY_CLINIC_SCHED;

    patient_node *temp = ptr_c->head;
    while(temp != NULL)
    {
        if( strcmp(temp->data.patient_code , patient_code) == 0 )
            return PATIENT_NODE_EXSISTED;
        temp = temp->next;
    }

    return PATIENT_NODE_NOT_EXSISTED;
}

/********************************************************************/

CLINIC_DATA_COND patient_code(clinic *ptr_c , patient_node *ptr , USAGE_COND usage)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_patient_code = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter code: ");
    gets(local_patient_code);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_patient_code);

    if(x != 3)
    {
        free(local_patient_code);
        local_patient_code = NULL;
        return WRONG_CODE;
    }
    else
    {
        for(u16 i = 0 ; i < x ; i++)
        {
            if( (local_patient_code[i] < '0') || (local_patient_code[i] > '9') )
            {
                free(local_patient_code);
                local_patient_code = NULL;
                return WRONG_CODE;
            }
        }
    }

    if(search_patient_with_code(ptr_c , local_patient_code) == PATIENT_NODE_EXSISTED)
    {
        if(usage == ADDING_NEW_PATIENT)
        {
            free(local_patient_code);
            local_patient_code = NULL;
            return WRONG_CODE;
        }
        else if( (usage == GETTING_CODE_TO_MODIFY) || (usage == GETTING_CODE_TO_DELETE) )
        {
            strcpy(ptr->data.patient_code , local_patient_code);
            free(local_patient_code);
            local_patient_code = NULL;
            return PATIENT_NODE_EXSISTED;
        }
    }

    if(usage == ADDING_NEW_PATIENT)
    {
        strcpy(ptr->data.patient_code , local_patient_code);
        free(local_patient_code);
        local_patient_code = NULL;
        return OK;
    }
    else if( (usage == GETTING_CODE_TO_MODIFY) || (usage == GETTING_CODE_TO_DELETE) )
    {
        free(local_patient_code);
        local_patient_code = NULL;
        return PATIENT_NODE_NOT_EXSISTED;
    }
}

/*****************************************************************/

CLINIC_DATA_COND patient_name(patient_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_patient_name = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter name: ");
    gets(local_patient_name);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_patient_name);
    if( (x < 17) || (x > 35))
    {
        free(local_patient_name);
        local_patient_name = NULL;
        return WRONG_NAME;
    }
    else
    {
        for(u16 i = 0 ; i < x ; i++)
        {
            if( !( ( (local_patient_name[i] >= 'a') && (local_patient_name[i] <= 'z') ) || ( (local_patient_name[i] >= 'A') && (local_patient_name[i] <= 'Z') ) || (local_patient_name[i] == 32) ) )
            {
                free(local_patient_name);
                local_patient_name = NULL;
                return WRONG_NAME;
            }
        }
    }

    strcpy(ptr->data.name , local_patient_name);
    free(local_patient_name);
    local_patient_name = NULL;
    return OK;
}

/********************************************************************/

CLINIC_DATA_COND patient_gender(patient_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_patient_gender = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter gender ('m' male or 'f' female): ");
    gets(local_patient_gender);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_patient_gender);

    if(x != 1)
    {
        free(local_patient_gender);
        local_patient_gender = NULL;
        return WRONG_GENDER;
    }
    else if( !( (local_patient_gender[0] == 'm') || (local_patient_gender[0] == 'f') ) )
    {
        free(local_patient_gender);
        local_patient_gender = NULL;
        return WRONG_GENDER;
    }

    ptr->data.gender = local_patient_gender[0];
    free(local_patient_gender);
    local_patient_gender = NULL;
    return OK;
}

/********************************************************************/

CLINIC_DATA_COND patient_age(patient_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_patient_age = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter your age : ");
    gets(local_patient_age);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_patient_age);

    //important to prevent user from press enter at the start of getting input
    if(x == 0)
    {
        free(local_patient_age);
        local_patient_age = NULL;
        return WRONG_AGE;
    }
    //65535 is max size of u16
    else if( !( (atoi(local_patient_age) >= 1) && (atoi(local_patient_age) <= 65535) ) )
    {
        free(local_patient_age);
        local_patient_age = NULL;
        return WRONG_AGE;
    }

    ptr->data.age = atoi(local_patient_age);
    free(local_patient_age);
    local_patient_age = NULL;
    return OK;
}

/********************************************************************/

CLINIC_DATA_COND patient_phon_num(patient_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_patient_phon_num = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter your phone number : ");
    gets(local_patient_phon_num);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_patient_phon_num);

    if(x != 11)
    {
        free(local_patient_phon_num);
        local_patient_phon_num = NULL;
        return WRONG_PHON_NUM;
    }
    else
    {
        for(u16 i = 0 ; i < x ; i++)
        {
            if( !( (local_patient_phon_num[i] >= '0') && (local_patient_phon_num[i] <= '9') ) )
            {
                free(local_patient_phon_num);
                local_patient_phon_num = NULL;
                return WRONG_PHON_NUM;
            }
        }
    }

    strcpy(ptr->data.phone_num , local_patient_phon_num);
    free(local_patient_phon_num);
    local_patient_phon_num = NULL;
    return OK;
}

/********************************************************************/

//Getting address from patient :
//=============================
//1- governments
CLINIC_DATA_COND patient_addre_gover(patient_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_patient_addre_gover = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please choose from the above government list using it's number (your government) : ");
    gets(local_patient_addre_gover);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_patient_addre_gover);

    //important to prevent user from press enter at the start of getting input
    if(x == 0)
    {
        free(local_patient_addre_gover);
        local_patient_addre_gover = NULL;
        return WRONG_GOVER_NUM;
    }

    // in the choice list there are only 27 choices (governments in egypt)
    else if( !( (atoi(local_patient_addre_gover) >= 1) && (atoi(local_patient_addre_gover) <= 27) ) )
    {
        free(local_patient_addre_gover);
        local_patient_addre_gover = NULL;
        return WRONG_GOVER_NUM;
    }

    ptr->data.pat_addre.gover = atoi(local_patient_addre_gover);
    free(local_patient_addre_gover);
    local_patient_addre_gover = NULL;
    return OK;
}

/********************************************************************/

//2- district
CLINIC_DATA_COND patient_addre_distr(patient_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_patient_addre_distr = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter which district in the government chosen : ");
    gets(local_patient_addre_distr);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_patient_addre_distr);

    if( (x < 8) || (x > 35) )
    {
        free(local_patient_addre_distr);
        local_patient_addre_distr = NULL;
        return WRONG_DISTR_FORMAT;
    }
    else
    {
        for(u16 i = 0 ; i < x ; i++)
        {
            if( !( ( (local_patient_addre_distr[i] >= 'a') && (local_patient_addre_distr[i] <= 'z') ) || ( (local_patient_addre_distr[i] >= 'A') && (local_patient_addre_distr[i] <= 'Z') ) || (local_patient_addre_distr[i] == 32) ) )
            {
                free(local_patient_addre_distr);
                local_patient_addre_distr = NULL;
                return WRONG_DISTR_FORMAT;
            }
        }
    }

    strcpy(ptr->data.pat_addre.distr , local_patient_addre_distr);
    free(local_patient_addre_distr);
    local_patient_addre_distr = NULL;
    return OK;
}

/********************************************************************/

//2- street
CLINIC_DATA_COND patient_addre_stre(patient_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_patient_addre_stre = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter which street in the district entered : ");
    gets(local_patient_addre_stre);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_patient_addre_stre);

    if( (x < 8) || (x > 35) )
    {
        free(local_patient_addre_stre);
        local_patient_addre_stre = NULL;
        return WRONG_STRE_FORMAT;
    }
    else if( !( (local_patient_addre_stre[x-1] == 't') && (local_patient_addre_stre[x-2] == 's') && (local_patient_addre_stre[x-3] == '.') ) )
    {
        free(local_patient_addre_stre);
        local_patient_addre_stre = NULL;
        return WRONG_STRE_FORMAT;
    }
    else
    {
        for(u16 i = 0 ; i < (x-3) ; i++)
        {
            if( !( ( (local_patient_addre_stre[i] >= 'a') && (local_patient_addre_stre[i] <= 'z') ) || ( (local_patient_addre_stre[i] >= 'A') && (local_patient_addre_stre[i] <= 'Z') ) || (local_patient_addre_stre[i] == 32) ) )
            {
                free(local_patient_addre_stre);
                local_patient_addre_stre = NULL;
                return WRONG_STRE_FORMAT;
            }
        }
    }

    strcpy(ptr->data.pat_addre.street , local_patient_addre_stre);
    free(local_patient_addre_stre);
    local_patient_addre_stre = NULL;
    return OK;
}

/********************************************************************/

CLINIC_DATA_COND patient_addre_home_num(patient_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_patient_addre_home_num = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter your home number : ");
    gets(local_patient_addre_home_num);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_patient_addre_home_num);

    //important to prevent user from press enter at the start of getting input
    if(x == 0)
    {
        free(local_patient_addre_home_num);
        local_patient_addre_home_num = NULL;
        return WRONG_HOME_NUM_FORMAT;
    }
    //65535 is max size of u16
    else if( !( (atoi(local_patient_addre_home_num) >= 1) && (atoi(local_patient_addre_home_num) <= 65535) ) )
    {
        free(local_patient_addre_home_num);
        local_patient_addre_home_num = NULL;
        return WRONG_HOME_NUM_FORMAT;
    }

    ptr->data.pat_addre.home_no = atoi(local_patient_addre_home_num);
    free(local_patient_addre_home_num);
    local_patient_addre_home_num = NULL;
    return OK;
}

/********************************************************************/

CLINIC_DATA_COND patient_choose_dr(patient_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_patient_choose_dr = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please choose from the above dr's list using it's number : ");
    gets(local_patient_choose_dr);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_patient_choose_dr);

    //important to prevent user from press enter at the start of getting input
    if(x == 0)
    {
        free(local_patient_choose_dr);
        local_patient_choose_dr = NULL;
        return WRONG_DR_NUM;
    }
    //4 is choices in the list of doctors works in clinic
    else if( !( (atoi(local_patient_choose_dr) >= 1) && (atoi(local_patient_choose_dr) <= 4) ) )
    {
        free(local_patient_choose_dr);
        local_patient_choose_dr = NULL;
        return WRONG_DR_NUM;
    }

    ptr->data.doctor = atoi(local_patient_choose_dr);
    free(local_patient_choose_dr);
    local_patient_choose_dr = NULL;
    return OK;
}

/********************************************************************/

CLINIC_DATA_COND patient_working_day(DAY *ptr_working_day , DAY Dr_avail_day[3] , USAGE_COND use)
{
    bool flag = 0;
    u16  x = 150;// it's going to be erased after function return
    u8 *local_patient_working_day = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please choose from the above working day/period list using it's number : ");
    gets(local_patient_working_day);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_patient_working_day);

    //important to prevent user from press enter at the start of getting input
    if(x == 0)
    {
        free(local_patient_working_day);
        local_patient_working_day = NULL;
        return WRONG_DAY_NUM;
    }
    //12 is choices in the list of available days/periods for each doctor in clinic
    else if( !( (atoi(local_patient_working_day) >= 1) && (atoi(local_patient_working_day) <= 12) ) )
    {
        free(local_patient_working_day);
        local_patient_working_day = NULL;
        return WRONG_DAY_NUM;
    }
    if(use == ADDING_NEW_PATIENT)
    {
        for(u16 i = 0 ; i < 4 ; i++)
        {
            if(Dr_avail_day[i] == 0)
                continue;
            else if(atoi(local_patient_working_day) != Dr_avail_day[i])
                flag = 1;
            else if(atoi(local_patient_working_day) == Dr_avail_day[i])
            {
                flag = 0;
                break;
            }
        }
    }


    if(flag == 0)
    {
        *ptr_working_day = atoi(local_patient_working_day);
        free(local_patient_working_day);
        local_patient_working_day = NULL;
        return OK;
    }
    else if(flag == 1)
    {
        free(local_patient_working_day);
        local_patient_working_day = NULL;
        return WRONG_DAY_NUM;
    }

}

/********************************************************************/

CLINIC_DATA_COND patient_appoi_num(patient_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_patient_appoi_num = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please choose from the above appointment list using it's number : ");
    gets(local_patient_appoi_num);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_patient_appoi_num);

    //important to prevent user from press enter at the start of getting input
    if(x == 0)
    {
        free(local_patient_appoi_num);
        local_patient_appoi_num = NULL;
        return WRONG_APPOI_NUM;
    }
    //12 is choices in the list of appointments for each period in clinic
    else if( !( (atoi(local_patient_appoi_num) >= 1) && (atoi(local_patient_appoi_num) <= 12) ) )
    {
        free(local_patient_appoi_num);
        local_patient_appoi_num = NULL;
        return WRONG_APPOI_NUM;
    }

    if( (ptr->data.working_day == sat_per2) || (ptr->data.working_day == sun_per2) || (ptr->data.working_day == mon_per2) || (ptr->data.working_day == tues_per2) || (ptr->data.working_day == wens_per2) || (ptr->data.working_day == thur_per2) )
        ptr->data.appoi = atoi(local_patient_appoi_num) + 12;
    else
        ptr->data.appoi = atoi(local_patient_appoi_num);
    free(local_patient_appoi_num);
    local_patient_appoi_num = NULL;
    return OK;
}

/********************************************************************/

CLINIC_DATA_COND patient_choose_prob(patient_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_patient_choose_prob = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please choose from the above possible problem list using it's number : ");
    gets(local_patient_choose_prob);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_patient_choose_prob);

    //important to prevent user from press enter at the start of getting input
    if(x == 0)
    {
        free(local_patient_choose_prob);
        local_patient_choose_prob = NULL;
        return WRONG_PROB_NUM;
    }
    //6 is choices in the list of possible problems which patient is suffer from
    else if( !( (atoi(local_patient_choose_prob) >= 1) && (atoi(local_patient_choose_prob) <= 6) ) )
    {
        free(local_patient_choose_prob);
        local_patient_choose_prob = NULL;
        return WRONG_PROB_NUM;
    }

    ptr->data.illness = atoi(local_patient_choose_prob);
    free(local_patient_choose_prob);
    local_patient_choose_prob = NULL;
    return OK;
}

/********************************************************************/

/*
using the following function we can check if the chosen appointment is available or not
based on appointments picked by another patients in clinic schedule list
*/
CLINIC_DATA_COND check_appoi_avail(clinic *ptr_c , patient_node *ptr)
{
    if(clinic_sched_empty(ptr_c) == 1)
        return EMPTY_SCHE_CLINIC;

    patient_node *temp = ptr_c->head;
    while(temp != NULL)
    {
        if( (temp->data.appoi == ptr->data.appoi) && (temp->data.working_day == ptr->data.working_day) )
            return NON_AVAIL_APPOI;
        temp = temp->next;
    }
    return OK;
}

/********************************************************************/

/*
using the following function we can check if the chosen doctor is available or not using
number of appointments per week for doctor or if doctor available in the chose day using
number of appointments per day for doctor based on appointments picked by another patients
in clinic schedule list
*/
CLINIC_DATA_COND check_sched_dr(clinic *ptr_c , DR doctor , DAY day , USAGE_COND usage)
{
    u16 count = 0;

    if(clinic_sched_empty(ptr_c) == 1)
        return EMPTY_SCHE_CLINIC;

    patient_node *temp = ptr_c->head;
    while(temp != NULL)
    {
        if(temp->data.doctor == doctor)
        {
            if(usage == CHECK_DR_DAY)
            {
                if(temp->data.working_day == day)
                    count++;
            }
            else if(usage == CHECK_DR_WEEK)
                count++;
        }
        temp = temp->next;
    }

    if( (usage == CHECK_DR_DAY) && (count == MAX_NUM_APPOI_DR_PER_DAY) )
        return DR_DAY_SCHED_FULL;

    else if( (usage == CHECK_DR_DAY) && (count == 0) )
        return DR_DAY_SCHED_EMPTY;

    else if( (usage == CHECK_DR_WEEK) && (count == MAX_NUM_APPOI_DR_PER_WEEK) )
        return DR_WEEK_SCHED_FULL;

    else if( (usage == CHECK_DR_WEEK) && (count == 0) )
        return DR_WEEK_SCHED_EMPTY;

    return OK;
}

/********************************************************************/

CLINIC_DATA_COND getting_username(u8 mem_username[15] , USAGE_COND use)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_username = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter UserName : ");
    gets(local_username);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_username);

    if(x == 0)
    {
        free(local_username);
        local_username = NULL;
        return WRONG_USERNAME;
    }
    if(use == ADMIN)
    {
        if(strcmp(local_username , admin_username) != 0)
        {
            free(local_username);
            local_username = NULL;
            return WRONG_USERNAME;
        }
    }
    if(use == DOCTOR)
    {
        if( (strcmp(local_username , DR_EO_username) != 0) && (strcmp(local_username , DR_SM_username) != 0) && (strcmp(local_username , DR_NM_username) != 0) && (strcmp(local_username , DR_MS_username) != 0) )
        {
            delete_exact_lines(2);
            free(local_username);
            local_username = NULL;
            return WRONG_USERNAME;
        }
    }

    strcpy(mem_username , local_username);
    free(local_username);
    local_username = NULL;
    return OK;
}

/********************************************************************/

CLINIC_DATA_COND getting_passw(u8 mem_passw[10] , u8 *ptr_username ,USAGE_COND use)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_passw = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter Password : ");
    gets(local_passw);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_passw);

    if(x == 0)
    {
        free(local_passw);
        local_passw = NULL;
        return WRONG_PASSW;
    }
    if(use == ADMIN)
    {
        if(strcmp(local_passw , admin_password) != 0)
        {
            free(local_passw);
            local_passw = NULL;
            return WRONG_PASSW;
        }
    }
    if(use == DOCTOR)
    {
        if( ( (strcmp(local_passw , DR_EO_password) != 0) && (strcmp(ptr_username , DR_EO_username) != 0) ) && ( (strcmp(local_passw , DR_NM_password) != 0) && (strcmp(ptr_username , DR_NM_username) != 0) )\
               && ( (strcmp(local_passw , DR_MS_password) != 0) && (strcmp(ptr_username , DR_MS_username) != 0) ) && ( (strcmp(local_passw , DR_SM_password) != 0) && (strcmp(ptr_username , DR_SM_username) != 0) ) )
        {
            free(local_passw);
            local_passw = NULL;
            return WRONG_PASSW;
        }
    }

    strcpy(mem_passw , local_passw);
    free(local_passw);
    local_passw = NULL;
    return OK;
}

/********************************************************************/

void show_drs_name(void)
{
    printf("(1) Dr.Shon Murphy\n");
    printf("(2) Dr.Neil Millendes\n");
    printf("(3) Dr.Eslam Osama\n");
    printf("(4) Dr.Mohamed Saleh\n");
}

/********************************************************************/

void getting_dr_name(patient_node *ptr)
{
    switch(ptr->data.doctor)
    {
        case dr_shon_murphy:    printf("Doctor's name : Dr.Shon Murphy\n");     break;
        case dr_neil_millendes: printf("Doctor's name : Dr.Neil Millendes\n");  break;
        case dr_eslam_osama:    printf("Doctor's name : Eslam Osama\n");        break;
        case dr_mohamed_saleh:  printf("Doctor's name : Mohamed Saleh\n");      break;
    }
}

/********************************************************************/

void print_working_day_period(DAY day)
{
   switch(day)
   {
     case sat_per1:     printf("(num_1) Saturday - Period 1\n");        break;
     case sat_per2:     printf("(num_2) Saturday - Period 2\n");        break;
     case sun_per1:     printf("(num_3) Sunday - Period 1\n");          break;
     case sun_per2:     printf("(num_4) Sunday - Period 2\n");          break;
     case mon_per1:     printf("(num_5) Monday - Period 1\n");          break;
     case mon_per2:     printf("(num_6) Monday - Period 2\n");          break;
     case tues_per1:    printf("(num_7) Tuesday - Period 1\n");         break;
     case tues_per2:    printf("(num_8) Tuesday - Period 2\n");         break;
     case wens_per1:    printf("(num_9) Wednesday - Period 1\n");       break;
     case wens_per2:    printf("(num_10) Wednesday - Period 2\n");      break;
     case thur_per1:    printf("(num_11) Thursday - Period 1\n");       break;
     case thur_per2:    printf("(num_12) Thursday - Period 2\n");       break;
   }
}

/********************************************************************/

void show_working_days_period_list(DR doctor , DAY day_avail_list[3] , USAGE_COND use)
{
    u16 x = 0;
    for(u16 i = 0 ; i < 12 ; i++)
    {
        if(clinic_schedule[i].doctor == doctor)
        {
            print_working_day_period(clinic_schedule[i].day);
            if(use == ADDING_NEW_PATIENT)
            {
                day_avail_list[x] = clinic_schedule[i].day;
                x++;
            }
        }
    }
}

/********************************************************************/

void getting_patient_per(patient_node *ptr)
{
    switch(ptr->data.working_day)
    {
     case sat_per1:     printf("Day of reservation : Saturday - Period 1\n");       break;
     case sat_per2:     printf("Day of reservation : Saturday - Period 2\n");       break;
     case sun_per1:     printf("Day of reservation : Sunday - Period 1\n");         break;
     case sun_per2:     printf("Day of reservation : Sunday - Period 2\n");         break;
     case mon_per1:     printf("Day of reservation : Monday - Period 1\n");         break;
     case mon_per2:     printf("Day of reservation : Monday - Period 2\n");         break;
     case tues_per1:    printf("Day of reservation : Tuesday - Period 1\n");        break;
     case tues_per2:    printf("Day of reservation : Tuesday - Period 2\n");        break;
     case wens_per1:    printf("Day of reservation : Wednesday - Period 1\n");      break;
     case wens_per2:    printf("Day of reservation : Wednesday - Period 2\n");      break;
     case thur_per1:    printf("Day of reservation : Thursday - Period 1\n");       break;
     case thur_per2:    printf("Day of reservation : Thursday - Period 2\n");       break;
    }
}

/********************************************************************/

void show_appointment_list(patient_node *ptr)
{
    if( (ptr->data.working_day == sat_per1) || (ptr->data.working_day == sun_per1) || (ptr->data.working_day == mon_per1) || (ptr->data.working_day == tues_per1) || (ptr->data.working_day == wens_per1) || (ptr->data.working_day == thur_per1) )
    {
        printf("1-  from 02:00 pm to 02:20 pm\n");
        printf("2-  from 02:20 pm to 02:40 pm\n");
        printf("3-  from 02:40 pm to 03:00 pm\n");
        printf("4-  from 03:00 pm to 03:20 pm\n");
        printf("5-  from 03:20 pm to 03:40 pm\n");
        printf("6-  from 03:40 pm to 04:00 pm\n");
        printf("7-  from 04:00 pm to 04:20 pm\n");
        printf("8-  from 04:20 pm to 04:40 pm\n");
        printf("9-  from 04:40 pm to 05:00 pm\n");
        printf("10- from 05:00 pm to 05:20 pm\n");
        printf("11- from 05:20 pm to 05:40 pm\n");
        printf("12- from 05:40 pm to 06:00 pm\n");
    }
    else if( (ptr->data.working_day == sat_per2) || (ptr->data.working_day == sun_per2) || (ptr->data.working_day == mon_per2) || (ptr->data.working_day == tues_per2) || (ptr->data.working_day == wens_per2) || (ptr->data.working_day == thur_per2) )
    {
        printf("1-  from 06:00 pm to 06:20 pm\n");
        printf("2-  from 06:20 pm to 06:40 pm\n");
        printf("3-  from 06:40 pm to 07:00 pm\n");
        printf("4-  from 07:00 pm to 07:20 pm\n");
        printf("5-  from 07:20 pm to 07:40 pm\n");
        printf("6-  from 07:40 pm to 08:00 pm\n");
        printf("7-  from 08:00 pm to 08:20 pm\n");
        printf("8-  from 08:20 pm to 08:40 pm\n");
        printf("9-  from 08:40 pm to 09:00 pm\n");
        printf("10- from 09:00 pm to 09:20 pm\n");
        printf("11- from 09:20 pm to 09:40 pm\n");
        printf("12- from 09:40 pm to 10:00 pm\n");
    }
}

/********************************************************************/

void show_appointment_patient(patient_node *ptr)
{
    switch(ptr->data.appoi)
    {
        case from_2_to_2_20:    printf("appointment info: from 02:00 pm to 02:20 pm\n");  break;
        case from_2_20_to_2_40: printf("appointment info: from 02:20 pm to 02:40 pm\n");  break;
        case from_2_40_to_3:    printf("appointment info: from 02:40 pm to 03:00 pm\n");  break;
        case from_3_to_3_20:    printf("appointment info: from 03:00 pm to 03:20 pm\n");  break;
        case from_3_20_to_3_40: printf("appointment info: from 03:20 pm to 03:40 pm\n");  break;
        case from_3_40_to_4:    printf("appointment info: from 03:40 pm to 04:00 pm\n");  break;
        case from_4_to_4_20:    printf("appointment info: from 04:00 pm to 04:20 pm\n");  break;
        case from_4_20_to_4_40: printf("appointment info: from 04:20 pm to 04:40 pm\n");  break;
        case from_4_40_to_5:    printf("appointment info: from 04:40 pm to 05:00 pm\n");  break;
        case from_5_to_5_20:    printf("appointment info: from 05:00 pm to 05:20 pm\n");  break;
        case from_5_20_to_5_40: printf("appointment info: from 05:20 pm to 05:40 pm\n");  break;
        case from_5_40_to_6:    printf("appointment info: from 05:40 pm to 06:00 pm\n");  break;
        case from_6_to_6_20:    printf("appointment info: from 06:00 pm to 06:20 pm\n");  break;
        case from_6_20_to_6_40: printf("appointment info: from 06:20 pm to 06:40 pm\n");  break;
        case from_6_40_to_7:    printf("appointment info: from 06:40 pm to 07:00 pm\n");  break;
        case from_7_to_7_20:    printf("appointment info: from 07:00 pm to 07:20 pm\n");  break;
        case from_7_20_to_7_40: printf("appointment info: from 07:20 pm to 07:40 pm\n");  break;
        case from_7_40_to_8:    printf("appointment info: from 07:40 pm to 08:00 pm\n");  break;
        case from_8_to_8_20:    printf("appointment info: from 08:00 pm to 08:20 pm\n");  break;
        case from_8_20_to_8_40: printf("appointment info: from 08:20 pm to 08:40 pm\n");  break;
        case from_8_40_to_9:    printf("appointment info: from 08:40 pm to 09:00 pm\n");  break;
        case from_9_to_9_20:    printf("appointment info: from 09:00 pm to 09:20 pm\n");  break;
        case from_9_20_to_9_40: printf("appointment info: from 09:20 pm to 09:40 pm\n");  break;
        case from_9_40_to_10:   printf("appointment info: from 09:40 pm to 10:00 pm\n");  break;
    }
}

/********************************************************************/

void print_list_gover(void)
{
    printf("(1) Alexandria\n");
    printf("(2) Aswan\n");
    printf("(3) Asyut\n");
    printf("(4) Beheira\n");
    printf("(5) BeniSuef\n");
    printf("(6) Cairo\n");
    printf("(7) Dakahlia\n");
    printf("(8) Damietta\n");
    printf("(9) Faiyum\n");
    printf("(10) Gharbia\n");
    printf("(11) Giza\n");
    printf("(12) Ismailia\n");
    printf("(13) Kafr El-Sheikh\n");
    printf("(14) Luxor\n");
    printf("(15) Matruh\n");
    printf("(16) Minya\n");
    printf("(17) Monufia\n");
    printf("(18) New Valley\n");
    printf("(19) North Sinai\n");
    printf("(20) Port Said\n");
    printf("(21) Qalyubia\n");
    printf("(22) Qena\n");
    printf("(23) Red Sea\n");
    printf("(24) Sharqia\n");
    printf("(25) Sohag\n");
    printf("(26) South Sinai\n");
    printf("(27) Suez\n");
}

/********************************************************************/

void show_gover_patient(patient_node *ptr)
{
   switch(ptr->data.pat_addre.gover)
   {
       case Alexandria:     printf("Alexandria    ");             break;
       case Aswan:          printf("Aswan         ");             break;
       case Asyut:          printf("Asyut         ");             break;
       case Beheira:        printf("Beheira       ");             break;
       case BeniSuef:       printf("Beni-Suef     ");             break;
       case Cairo:          printf("Cairo         ");             break;
       case Dakahlia:       printf("Dakahlia      ");             break;
       case Damietta:       printf("Damietta      ");             break;
       case Faiyum:         printf("Faiyum        ");             break;
       case Gharbia:        printf("Gharbia       ");             break;
       case Giza:           printf("Giza          ");             break;
       case Ismailia:       printf("Ismailia      ");             break;
       case KafrEl_Sheikh:  printf("Kafr El-Sheikh");             break;
       case Luxor:          printf("Luxor         ");             break;
       case Matruh:         printf("Matruh        ");             break;
       case Minya:          printf("Minya         ");             break;
       case Monufia:        printf("Monufia       ");             break;
       case NewValley:      printf("New Valley    ");             break;
       case NorthSinai:     printf("North Sinai   ");             break;
       case PortSaid:       printf("Port Said     ");             break;
       case Qalyubia:       printf("Qalyubia      ");             break;
       case Qena:           printf("Qena          ");             break;
       case RedSea:         printf("Red Sea       ");             break;
       case Sharqia:        printf("Sharqia       ");             break;
       case Sohag:          printf("Sohag         ");             break;
       case SouthSinai:     printf("South Sinai   ");             break;
       case Suez:           printf("Suez          ");             break;
   }
}

/********************************************************************/

void print_dise(void)
{
    printf("(1) stomach aches\n");
    printf("(2) diarrhea\n");
    printf("(3) colds and flu\n");
    printf("(4) allergies\n");
    printf("(5) celiac disease\n");
    printf("(6) other\n");
}

/********************************************************************/

void show_problem_patient(patient_node *ptr)
{
    switch(ptr->data.illness)
    {
        case stomach_aches:     printf("stomach aches");    break;
        case diarrhea:          printf("diarrhea");         break;
        case colds_and_flu:     printf("colds and flu");    break;
        case allergies:         printf("allergies");        break;
        case celiac_disease:    printf("celiac disease");   break;
        case other:             printf("other");            break;
    }
}

/********************************************************************/

/*if it returns 0 then it means there is no change on reservation of patient and
if it returns 1 then it means change happened on patient's eservation*/
bool getting_data_res(clinic *ptr_c , patient_node *ptr , USAGE_COND use)
{
    u8 des = 'c';
    DAY Dr_avil_days[3] = {0 , 0 , 0};

    patient_node *ptr_copy = (patient_node *)malloc(sizeof(patient_node));

    if(ptr_copy == NULL)
    {
        printf("Heap is full (please try to free some of memory in heap first)...\n");
        getchar();
        system("cls");
        return 0;
    }

    /*this while(1) for doctor's name, working day/period, and appointment time*/
    while(1)
    {
        des = 'c';

        /*for getting name of doctor*/
        while(1)
        {
            des = 'c';
            show_drs_name();//4 lines on console

            CLINIC_DATA_COND check_patient_choose_dr = patient_choose_dr(ptr_copy);
            while(check_patient_choose_dr == WRONG_DR_NUM)
            {
                printf("WARNING!! you must choose a number from the above list, please try again...\n");

                getchar();
                delete_exact_lines(3);

                check_patient_choose_dr = patient_choose_dr(ptr_copy);
            }

            /*delete choice list and line of asking for dr name and exchange them with one line of the choosen dr name*/
            delete_exact_lines(5);
            getting_dr_name(ptr_copy);

            /*
            the following if is to make sure first we are using function to modify reservation data and for the choosen doctor name
            it's the same of name of doctor in the same old reservation data, so maybe it's about to choose the same reservation data
            */
            if( (use == WITH_MOD_PAT) && (ptr_copy->data.doctor == ptr->data.doctor) )
            {
                des = 'c';
                break;
            }
            else if(check_sched_dr(ptr_c , ptr_copy->data.doctor , ptr_copy->data.working_day , CHECK_DR_WEEK) == DR_WEEK_SCHED_FULL)
            {
                printf("Doctor has full weekly schedule, do you want to choose another doctor (y/n)? ");
                des_state check_decision = check_des(&des);
                while(check_decision == WRONG_DES_FORMAT)
                {
                    printf("WARNING!! wrong decision format (decision is either y or n)....\n");

                    getchar();
                    delete_exact_lines(3);

                    printf("Doctor has full weekly schedule, do you want to choose another doctor (y/n)? ");
                    check_decision = check_des(&des);
                }
                getchar();//to see if it's y or n
                if(des == 'y')
                {
                    /*
                    delete line of getchar(), ;ine of asking for des to get new doctor's name, and
                    line of showing choosen doctor
                    */
                    delete_exact_lines(3);
                    continue;
                }
                else if(des == 'n')
                {
                    if(use == WITH_ADD_PAT)
                    {
                        free(ptr);
                        ptr = NULL;
                    }
                    free(ptr_copy);
                    ptr_copy = NULL;
                    return 0;//means no change occurs on reservation data
                }
            }
            else
            {
                des = 'c';
                break;
            }
        }

        des = 'c';

        /*this while(1) is to get working day/period and appointment*/
        while(1)
        {
            /*this while(1) is to get working day/period*/
            while(1)
            {
                show_working_days_period_list(ptr_copy->data.doctor , Dr_avil_days , ADDING_NEW_PATIENT);

                CLINIC_DATA_COND check_patient_working_day = patient_working_day(&(ptr_copy->data.working_day) , Dr_avil_days , ADDING_NEW_PATIENT);
                while(check_patient_working_day == WRONG_DAY_NUM)
                {
                    printf("WARNING!! you must choose a number from the above list, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_patient_working_day = patient_working_day(&(ptr_copy->data.working_day) , Dr_avil_days , ADDING_NEW_PATIENT);
                }

                /*delete choice list and line of asking for day/period and exchange them with one line of the choosen day/period*/
                delete_exact_lines(4);
                getting_patient_per(ptr_copy);

                /*
                the following if is to make sure first we are using function to modify reservation data and for the choosen doctor name
                it's the same of name of doctor in the same old reservation data and the choosen day/period of reservation is the same of old
                old day/period of reservation, so maybe it's about to choose the same reservation data
                */
                if( (use == WITH_MOD_PAT) && (ptr_copy->data.doctor == ptr_copy->data.doctor) && (ptr_copy->data.working_day == ptr_copy->data.working_day) )
                {
                    des = 'c';
                    break;
                }
                else if(check_sched_dr(ptr_c , ptr_copy->data.doctor , ptr_copy->data.working_day , CHECK_DR_DAY) == DR_DAY_SCHED_FULL)
                {
                    printf("Doctor has full daily schedule, do you want to choose another day/period (y/n)? ");
                    des_state check_decision = check_des(&des);
                    while(check_decision == WRONG_DES_FORMAT)
                    {
                        printf("WARNING!! wrong decision format (decision is either y or n)....\n");

                        getchar();
                        delete_exact_lines(3);

                        printf("Doctor has full daily schedule, do you want to choose another day/period (y/n)? ");
                        check_decision = check_des(&des);
                    }
                    getchar();//to see if it's y or n
                    if(des == 'y')
                    {
                        delete_exact_lines(3);//delete line of getchar, line of asking for des, and line of choosen day/period
                        continue;//do continue to show again list of day/periods for choosen doctor
                    }
                    else if(des == 'n')
                        break;
                }
                else
                {
                    des = 'c';
                    break;
                }
            }

            if(des == 'n')
            {
                printf("do you want to choose another doctor (y/n)? ");
                des_state check_decision = check_des(&des);
                while(check_decision == WRONG_DES_FORMAT)
                {
                    printf("WARNING!! wrong decision format (decision is either y or n)....\n");

                    getchar();
                    delete_exact_lines(3);

                    printf("do you want to choose another doctor (y/n)? ");
                    check_decision = check_des(&des);
                }
                getchar();
                if(des == 'y')
                {
                    /*
                    delete 2 lines of getchar(), line of asking for des choosing another dr, line of asking for des choosing another day/period,
                    line of showing choosen doctor's name, and line of showing choosen day/period
                    */
                    delete_exact_lines(6);
                    break;
                }
                else if(des == 'n')
                {
                    if(use == WITH_ADD_PAT)
                    {
                        free(ptr);
                        ptr = NULL;
                    }
                    free(ptr_copy);
                    ptr_copy = NULL;
                    return 0;//means no change occurs on reservation data
                }
            }

            des = 'c';

            /*for getting appointment from user*/
            while(1)
            {
                show_appointment_list(ptr_copy);
                CLINIC_DATA_COND check_patient_appoi_num = patient_appoi_num(ptr_copy);
                while(check_patient_appoi_num == WRONG_APPOI_NUM)
                {
                    printf("WARNING!! you must choose a number from the above list, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_patient_appoi_num = patient_appoi_num(ptr_copy);
                }

                /*delete choice list and line of asking for appointment number and exchange them with one line of the choosen appointment time*/
                delete_exact_lines(13);
                show_appointment_patient(ptr_copy);

                /*
                the following if is to make sure first we are using function to modify reservation data and for the choosen doctor name
                it's the same of name of doctor in the same old reservation data and the choosen day/period of reservation is the same of old
                old day/period of reservation, the choosen new appointment is same as the old one  so we are now sure it's the same old reservation data
                */
                if( (use == WITH_MOD_PAT) && (ptr_copy->data.doctor == ptr_copy->data.doctor) && (ptr_copy->data.working_day == ptr_copy->data.working_day) && (ptr_copy->data.appoi == ptr_copy->data.appoi) )
                {
                    des = 'c';
                    break;
                }
                else if(check_appoi_avail(ptr_c , ptr_copy) == NON_AVAIL_APPOI)
                {
                    printf("the appointment is not available, do you want to choose another appointment (y/n)? ");
                    des_state check_decision = check_des(&des);
                    while(check_decision == WRONG_DES_FORMAT)
                    {
                        printf("WARNING!! wrong decision format (decision is either y or n)....\n");

                        getchar();
                        delete_exact_lines(3);

                        printf("the appointment is not available, do you want to choose another appointment (y/n)? ");
                        check_decision = check_des(&des);
                    }
                    getchar();//to see if it's y or n
                    if(des == 'y')
                    {
                        /*line of getchar , line of asking for des, and line of showing new appointment time*/
                        delete_exact_lines(3);
                        continue;
                    }
                    else if(des == 'n')
                        break;
                }
                else
                {
                    des = 'c';
                    break;
                }
            }
            if(des == 'c')
                break;
            else if(des == 'n')
            {
                printf("do you want to choose another day/period (y/n)? ");
                des_state check_decision = check_des(&des);
                while(check_decision == WRONG_DES_FORMAT)
                {
                    printf("WARNING!! wrong decision format (decision is either y or n)....\n");

                    getchar();
                    delete_exact_lines(3);

                    printf("do you want to choose another day (y/n)? ");
                    check_decision = check_des(&des);
                }
                getchar();
                if(des == 'y')
                {
                    /*
                    line of 2 getchar , line of asking for des about choose new appointment,
                    line of showing choosen new appointment time, line of asking for des about
                    choose new day/period, and line of showing choosen new period/day
                    */
                    delete_exact_lines(6);
                    continue;
                }
                else if(des == 'n')
                    break;
            }
        }

        if(des == 'c')
            break;
        else if(des == 'n')
        {
            printf("do you want to choose another doctor (y/n)? ");
            des_state check_decision = check_des(&des);
            while(check_decision == WRONG_DES_FORMAT)
            {
                printf("WARNING!! wrong decision format (decision is either y or n)....\n");

                getchar();
                delete_exact_lines(3);

                printf("do you want to choose another doctor (y/n)? ");
                check_decision = check_des(&des);
            }
            getchar();
            if(des == 'y')
            {
                /*
                line of 3 getchar , line of asking for des about choose new appointment, line of showing choosen
                new appointment time, line of asking for new period/day, line of showing choosen new period/day,
                line of asking for new doctor name, and line of showing choosen doctor name
                */
                delete_exact_lines(9);
                continue;
            }
            else if(des == 'n')
            {
                if(use == WITH_ADD_PAT)
                {
                    free(ptr);
                    ptr = NULL;
                }
                free(ptr_copy);
                ptr_copy = NULL;
                return 0;//means no change occurs on reservation data
            }
        }
    }
    ptr->data.doctor = ptr_copy->data.doctor;
    ptr->data.working_day = ptr_copy->data.working_day;
    ptr->data.appoi = ptr_copy->data.appoi;
    free(ptr_copy);
    ptr_copy = NULL;
    return 1;//means there is a successfull change occurs on reservation data
}

/********************************************************************/

CLINIC_DATA_COND add_patient(clinic *ptr_c)
{
    u8 des = 'c';

    while(1)
    {
        des = 'c';

        if(clinic_sched_full(ptr_c) == CLINIC_IS_FULL)
        {
            printf("Schedule of clinic is full for the current week (please try to make reservation next week)...\n");
            return CLINIC_IS_FULL;
        }

        patient_node *ptr = (patient_node *)malloc(sizeof(patient_node));

        if(ptr == NULL)
        {
            printf("Heap is full (please try to free some of memory in heap first)...\n");
            return HEAP_FULL;
        }

        //==========================================================================================
        printf("\t\t===============================\n");
        printf("\t\t**patient reservation section**\n");
        printf("\t\t===============================\n");
        printf("\t\t(1) Getting data of reservation\n");
        printf("\t\t===============================\n\n\n");

        bool stat_getting_data_res = getting_data_res(ptr_c , ptr , WITH_ADD_PAT);
        if(stat_getting_data_res == 0)
            return;

        //==========================================================================================

        /*for getting actual data of patient*/
        printf("\n\n\t\t===========================\n");
        printf("\t\t(2) Getting data of patient\n");
        printf("\t\t===========================\n\n\n");

        /*getting patient code*/
        CLINIC_DATA_COND check_patient_code = patient_code(ptr_c , ptr , ADDING_NEW_PATIENT);
        while(check_patient_code == WRONG_CODE)
        {
            printf("WARNING!! the code either not following format or it's already existed in reservation list, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_patient_code = patient_code(ptr_c , ptr , ADDING_NEW_PATIENT);
        }

        /*getting name*/
        CLINIC_DATA_COND check_patient_name = patient_name(ptr);
        while(check_patient_name == WRONG_NAME)
        {
            printf("WARNING!! wrong name format, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_patient_name = patient_name(ptr);
        }

        /*getting patient gender*/
        CLINIC_DATA_COND check_patient_gender = patient_gender(ptr);
        while(check_patient_gender == WRONG_GENDER)
        {
            printf("WARNING!! gender is either m or f, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_patient_gender = patient_gender(ptr);
        }

        /*getting patient age*/
        CLINIC_DATA_COND check_patient_age = patient_age(ptr);
        while(check_patient_age == WRONG_AGE)
        {
           printf("WARNING!! wrong age format, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_patient_age = patient_age(ptr);
        }

        /*getting patient phone number*/
        CLINIC_DATA_COND check_patient_phon_num = patient_phon_num(ptr);
        while(check_patient_phon_num == WRONG_PHON_NUM)
        {
            printf("WARNING!! wrong phone number format, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_patient_phon_num = patient_phon_num(ptr);
        }

        /*Getting Address of patient*/
        //1- governments
        print_list_gover();

        CLINIC_DATA_COND check_patient_addre_gover = patient_addre_gover(ptr);
        while(check_patient_addre_gover == WRONG_GOVER_NUM)
        {
            printf("WARNING!! please choose the number of your government from the above list of governments...\n");

            getchar();
            delete_exact_lines(3);

            check_patient_addre_gover = patient_addre_gover(ptr);
        }

        delete_exact_lines(28);
        printf("government name : ");
        show_gover_patient(ptr);
        printf("\n");

        //2- district
        CLINIC_DATA_COND check_patient_addre_distr = patient_addre_distr(ptr);
        while(check_patient_addre_distr == WRONG_DISTR_FORMAT)
        {
            printf("WARNING!! wrong district format, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_patient_addre_distr = patient_addre_distr(ptr);
        }

        //3- street name
        CLINIC_DATA_COND check_patient_addre_stre = patient_addre_stre(ptr);
        while(check_patient_addre_stre == WRONG_STRE_FORMAT)
        {
            printf("WARNING!! wrong street format (stre_name.st), please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_patient_addre_stre = patient_addre_stre(ptr);
        }

        //4- home number
        CLINIC_DATA_COND check_patient_addre_home_num = patient_addre_home_num(ptr);
        while(check_patient_addre_home_num == WRONG_HOME_NUM_FORMAT)
        {
            printf("WARNING!! home number must be integer value, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_patient_addre_home_num = patient_addre_home_num(ptr);
        }
        //================================================================================

        /*getting problem of patient*/
        print_dise();

        CLINIC_DATA_COND check_patient_choose_prob = patient_choose_prob(ptr);
        while(check_patient_choose_prob == WRONG_PROB_NUM)
        {
            printf("WARNING!! the entered in not included in the list of problems, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_patient_choose_prob = patient_choose_prob(ptr);
        }

        delete_exact_lines(7);
        printf("possible illness: ");
        show_problem_patient(ptr);
        printf("\n");


        /**************************************************************/
        ptr->next = NULL;
        ptr->prev = NULL;
        (ptr_c->node_nums)++;
        /**************************************************************/

        if(clinic_sched_empty(ptr_c) == 1)//1st node in reservation list
        {
            ptr_c->head = ptr;
            ptr_c->tail = ptr;
        }
        else//just append reservation list with the new node
        {
            ptr->prev = ptr_c->tail;
            ptr_c->tail->next = ptr;
            ptr_c->tail = ptr;
        }

        printf("\t\t============================================================================================================\n");
        printf("\t\tpatient with name (%s) and code (%s) successfully added in reservation list\n", ptr->data.name, ptr->data.patient_code);
        printf("\t\t============================================================================================================\n");

        printf("do you want to add new reservation again in clinic reservation list(y/n)?? ");
        des_state check_var_des =  check_des(&des);
        while(check_var_des == WRONG_DES_FORMAT)
        {
            printf("WARNING!! you must type either y or n, please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to add new reservation again in clinic reservation list(y/n)?? ");
            check_var_des =  check_des(&des);
        }

        getchar();
        if(des == 'y')
        {
            system("cls");
            continue;
        }
        else if(des == 'n')// return back general adding list
            break;
    }// end bracket of while(1) of the whole function
}// end bracket of the function itself

/********************************************************************/

void getting_dr(DR dr)
{
    u8 ch[2];
    switch(dr)
    {
        case dr_shon_murphy:    printf("Dr.Shon Murphy%-7s   " , ch);          break;
        case dr_neil_millendes: printf("Dr.Neil Millendes%-7s" , ch);          break;
        case dr_eslam_osama:    printf("Dr.Eslam Osama%-7s   " , ch);          break;
        case dr_mohamed_saleh:  printf("Dr.Mohamed Saleh%-7s " , ch);          break;
    }
}

/********************************************************************/

void print_res_day_head(DAY day)
{
    switch(day)
    {
        case sat_per1:     printf("  Saturday - Period 1 ");         break;
        case sat_per2:     printf("  Saturday - Period 2 ");         break;
        case sun_per1:     printf("  Sunday - Period 1   ");         break;
        case sun_per2:     printf("  Sunday - Period 2   ");         break;
        case mon_per1:     printf("  Monday - Period 1   ");         break;
        case mon_per2:     printf("  Monday - Period 2   ");         break;
        case tues_per1:    printf("  Tuesday - Period 1  ");         break;
        case tues_per2:    printf("  Tuesday - Period 2  ");         break;
        case wens_per1:    printf("  Wednesday - Period 1");         break;
        case wens_per2:    printf("  Wednesday - Period 2");         break;
        case thur_per1:    printf("  Thursday - Period 1 ");         break;
        case thur_per2:    printf("  Thursday - Period 2 ");         break;
    }
}

/********************************************************************/

void print_res_appoi(appointment appoi)
{
    switch(appoi)
    {
        case from_2_to_2_20:    printf("from 02:00 pm to 02:20 pm ");  break;
        case from_2_20_to_2_40: printf("from 02:20 pm to 02:40 pm ");  break;
        case from_2_40_to_3:    printf("from 02:40 pm to 03:00 pm ");  break;
        case from_3_to_3_20:    printf("from 03:00 pm to 03:20 pm ");  break;
        case from_3_20_to_3_40: printf("from 03:20 pm to 03:40 pm ");  break;
        case from_3_40_to_4:    printf("from 03:40 pm to 04:00 pm ");  break;
        case from_4_to_4_20:    printf("from 04:00 pm to 04:20 pm ");  break;
        case from_4_20_to_4_40: printf("from 04:20 pm to 04:40 pm ");  break;
        case from_4_40_to_5:    printf("from 04:40 pm to 05:00 pm ");  break;
        case from_5_to_5_20:    printf("from 05:00 pm to 05:20 pm ");  break;
        case from_5_20_to_5_40: printf("from 05:20 pm to 05:40 pm ");  break;
        case from_5_40_to_6:    printf("from 05:40 pm to 06:00 pm ");  break;
        case from_6_to_6_20:    printf("from 06:00 pm to 06:20 pm ");  break;
        case from_6_20_to_6_40: printf("from 06:20 pm to 06:40 pm ");  break;
        case from_6_40_to_7:    printf("from 06:40 pm to 07:00 pm ");  break;
        case from_7_to_7_20:    printf("from 07:00 pm to 07:20 pm ");  break;
        case from_7_20_to_7_40: printf("from 07:20 pm to 07:40 pm ");  break;
        case from_7_40_to_8:    printf("from 07:40 pm to 08:00 pm ");  break;
        case from_8_to_8_20:    printf("from 08:00 pm to 08:20 pm ");  break;
        case from_8_20_to_8_40: printf("from 08:20 pm to 08:40 pm ");  break;
        case from_8_40_to_9:    printf("from 08:40 pm to 09:00 pm ");  break;
        case from_9_to_9_20:    printf("from 09:00 pm to 09:20 pm ");  break;
        case from_9_20_to_9_40: printf("from 09:20 pm to 09:40 pm ");  break;
        case from_9_40_to_10:   printf("from 09:40 pm to 10:00 pm ");  break;
    }
}

/********************************************************************/

void print_pat_data(clinic *ptr_c , patient_node *temp ,USAGE_COND use)
{
    printf("====================================================================================================================================================\n\n");

    if( (use == PRINT_BIO_DATA) || (use == PRINT_ALL_DATA) )
    {
        printf("name\t\t\t\t   gender\tage\t\tphone number\t\tgovernment\t\tdistrict\t\t\t\tstreet\t\t\t\t\thome number\n");
        printf("%-35s" , temp->data.name);

        if(temp->data.gender == 'm')
            printf("male\t\t");
        else if(temp->data.gender == 'f')
            printf("female\t\t");

        printf("%d\t\t%-11s\t\t" , temp->data.age , temp->data.phone_num);
        show_gover_patient(temp);
        printf("\t\t%-35s\t%-35s\t%d\n" , temp->data.pat_addre.distr , temp->data.pat_addre.street , temp->data.pat_addre.home_no);
    }

    if( (use == PRINT_RES_DATA) || (use == PRINT_ALL_DATA) )
    {
        printf("\n\ndoctor's name : ");
        getting_dr(temp->data.doctor);
        printf("\nres_day/per :");
        print_res_day_head(temp->data.working_day);
        printf("\nappointment time : ");
        print_res_appoi(temp->data.appoi);
        printf("\n");
        printf("possible illness: ");
        show_problem_patient(temp);
        printf("\n");


    }

    printf("\n\n====================================================================================================================================================\n");

    return;
}

/********************************************************************/

bool mod_pat_bio_data(clinic *ptr_c ,  patient_node *ptr ,  patient_node *ptr1)
{
    u8 des = 'm';
    u16 choice;
    bool flag = 0;

    system("cls");
    while(1)
    {
        printf("\t\t==========================================\n");
        printf("\t\t**patient biography modification section**\n");
        printf("\t\t==========================================\n\n");

        printf("patient's biography data\n");
        printf("========================\n\n");
        print_pat_data(ptr_c , ptr1 , PRINT_BIO_DATA);

        printf("which of the following do you want to modify about patient biography info with code of (%s)? \n" , ptr1->data.patient_code);
        printf("=====================================================================================================\n\n");

        printf("(1) patient's name:\n");
        printf("(2) patient's gender:\n");
        printf("(3) patient's age:\n");
        printf("(4) patient's phone number:\n");
        printf("(5) patient's government:\n");
        printf("(6) patient's district:\n");
        printf("(7) patient's street name:\n");
        printf("(8) patient's home number:\n");
        printf("(9) patient's problem:\n");
        printf("(10) Exist:\n");

        printf("\n=====================================================================================================\n");

        choice_state check_var_choice = check_choice(&choice);
        while(check_var_choice == WRONG_CHOICE_FORMAT)
        {
            printf("WARNING!! choice is always a number, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_var_choice = check_choice(&choice);
        }

        switch(choice)
        {
        case 1:
            {
                CLINIC_DATA_COND check_patient_name = patient_name(ptr);
                while(check_patient_name == WRONG_NAME)
                {
                    printf("WARNING!! wrong name format, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_patient_name = patient_name(ptr);
                }
                strcpy(ptr1->data.name, ptr->data.name);
                printf("\t\t===========================================\n");
                printf("\t\tchanging patient's name successfully done!!\n");
                printf("\t\t===========================================\n");
                flag = 1;
                break;
            }

        case 2:
            {
                CLINIC_DATA_COND check_patient_gender = patient_gender(ptr);
                while(check_patient_gender == WRONG_GENDER)
                {
                    printf("WARNING!! gender is either m or f, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_patient_gender = patient_gender(ptr);
                }
                ptr1->data.gender = ptr->data.gender;
                printf("\t\t=============================================\n");
                printf("\t\tchanging patient's gender successfully done!!\n");
                printf("\t\t=============================================\n");
                flag = 1;
                break;
            }

        case 3:
            {
                CLINIC_DATA_COND check_patient_age = patient_age(ptr);
                while(check_patient_age == WRONG_AGE)
                {
                printf("WARNING!! wrong age format, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_patient_age = patient_age(ptr);
                }
                ptr1->data.age = ptr->data.age;
                printf("\t\t==========================================\n");
                printf("\t\tchanging patient's age successfully done!!\n");
                printf("\t\t==========================================\n");
                flag = 1;
                break;
            }

        case 4:
            {
                CLINIC_DATA_COND check_patient_phon_num = patient_phon_num(ptr);
                while(check_patient_phon_num == WRONG_PHON_NUM)
                {
                    printf("WARNING!! wrong phone number format, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_patient_phon_num = patient_phon_num(ptr);
                }
                strcpy(ptr1->data.phone_num , ptr->data.phone_num);
                printf("\t\t===================================================\n");
                printf("\t\tchanging patient's phone number successfully done!!\n");
                printf("\t\t===================================================\n");
                flag = 1;
                break;
            }

        case 5:
            {
                print_list_gover();

                CLINIC_DATA_COND check_patient_addre_gover = patient_addre_gover(ptr);
                while(check_patient_addre_gover == WRONG_GOVER_NUM)
                {
                    printf("WARNING!! please choose the number of your government from the above list of governments...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_patient_addre_gover = patient_addre_gover(ptr);
                }

                /*delete list of govers and also line of asking for choose from list,
                only show just which gover. patient is from*/
                delete_exact_lines(28);
                show_gover_patient(ptr);

                ptr1->data.pat_addre.gover = ptr->data.pat_addre.gover;
                printf("\t\t=================================================\n");
                printf("\t\tchanging patient's government successfully done!!\n");
                printf("\t\t=================================================\n");
                flag = 1;
                break;
            }

        case 6:
            {
                CLINIC_DATA_COND check_patient_addre_distr = patient_addre_distr(ptr);
                while(check_patient_addre_distr == WRONG_DISTR_FORMAT)
                {
                    printf("WARNING!! wrong district format, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_patient_addre_distr = patient_addre_distr(ptr);
                }
                strcpy(ptr1->data.pat_addre.distr , ptr->data.pat_addre.distr);
                printf("\t\t===============================================\n");
                printf("\t\tchanging patient's distruct successfully done!!\n");
                printf("\t\t===============================================\n");
                flag = 1;
                break;
            }

        case 7:
            {
                CLINIC_DATA_COND check_patient_addre_stre = patient_addre_stre(ptr);
                while(check_patient_addre_stre == WRONG_STRE_FORMAT)
                {
                    printf("WARNING!! wrong street format (stre_name.str), please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_patient_addre_stre = patient_addre_stre(ptr);
                }
                strcpy(ptr1->data.pat_addre.street , ptr->data.pat_addre.street);
                printf("\t\t==================================================\n");
                printf("\t\tchanging patient's street name successfully done!!\n");
                printf("\t\t==================================================\n");
                flag = 1;
                break;
            }

        case 8:
            {
                CLINIC_DATA_COND check_patient_addre_home_num = patient_addre_home_num(ptr);
                while(check_patient_addre_home_num == WRONG_HOME_NUM_FORMAT)
                {
                    printf("WARNING!! home number must be integer value, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_patient_addre_home_num = patient_addre_home_num(ptr);
                }
                ptr1->data.pat_addre.home_no = ptr->data.pat_addre.home_no;
                printf("\t\t==================================================\n");
                printf("\t\tchanging patient's home number successfully done!!\n");
                printf("\t\t==================================================\n");
                flag = 1;
                break;
            }

        case 9:
            {
                print_dise();

                CLINIC_DATA_COND check_patient_choose_prob = patient_choose_prob(ptr);
                while(check_patient_choose_prob == WRONG_PROB_NUM)
                {
                    printf("WARNING!! the entered in not included in the list of problems, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_patient_choose_prob = patient_choose_prob(ptr);
                }

                /*delete lines of problem list and line of asking for choice
                and only show which problem patient suffers from*/
                delete_exact_lines(7);
                printf("possible illness: ");
                show_problem_patient(ptr);
                printf("\n");

                ptr1->data.illness = ptr->data.illness;
                printf("\t\t=======================================================\n");
                printf("\t\tchanging patient's possible problem successfully done!!\n");
                printf("\t\t=======================================================\n");
                flag = 1;
                break;
            }

        case 10:
            des = 'e';
            break;

        default:
            printf("WARNING!! wrong choice not included in the list...\n");
            break;
        }

        if(des == 'e')
            return flag;

        printf("do you want to do another modification to biography of the same patient (y/n)? ");
        des_state check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to do another modification to biography of the same patient (y/n)? ");
            check_decision = check_des(&des);
        }
        getchar();
        if(des == 'y')
        {
            system("cls");
            continue;
        }
        if(des == 'n')
        {
            return flag;
        }
    }
}

/********************************************************************/

void modify_pat_data(clinic *ptr_c)
{
    u8 des = 'm';
    u16 choice;
    bool flag = 0 , key_same_pat = 0;
    patient_node *temp_p;

    if(clinic_sched_empty(ptr_c) == 1)
    {
        printf("reservation list of clinic is empty (no data to modify)...\n");
        return;
    }

    patient_node *ptr = (patient_node *)malloc(sizeof(patient_node));
    if(ptr == NULL)
    {
        printf("heap is full (please try to free some memory in heap first)...\n");
        return;
    }

    while(1)
    {
        flag = 0;
        des = 'm';

        printf("\t\t================================\n");
        printf("\t\t**patient modification section**\n");
        printf("\t\t================================\n\n");

        if(key_same_pat == 0)//in case loop again to modify another patient data
        {
            CLINIC_DATA_COND check_patient_code = patient_code(ptr_c , ptr , GETTING_CODE_TO_MODIFY);
            while(1)
            {
                if(check_patient_code == WRONG_CODE)
                {
                    printf("WARNING!! wrong patient code format, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_patient_code = patient_code(ptr_c , ptr , GETTING_CODE_TO_MODIFY);
                }
                else if(check_patient_code == PATIENT_NODE_NOT_EXSISTED)
                {
                    printf("WARNING!! patient code is not listed in reservation list, do you want to enter another patient code (y/n)? ");

                    des_state check_decision = check_des(&des);
                    while(check_decision == WRONG_DES_FORMAT)
                    {
                        printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        printf("WARNING!! patient code is not listed in reservation list, do you want to enter another patient code (y/n)? ");
                        check_decision = check_des(&des);
                    }
                    getchar();
                    if(des == 'y')
                    {
                        delete_exact_lines(3);
                        check_patient_code = patient_code(ptr_c , ptr , GETTING_CODE_TO_MODIFY);
                    }
                    else if(des == 'n')
                    {
                        free(ptr);
                        ptr = NULL;
                        system("cls");
                        return;
                    }
                }
                else if(check_patient_code == PATIENT_NODE_EXSISTED)
                    break;
            }

            temp_p = ptr_c->head;
            while(temp_p != NULL)
            {
                if(strcmp(temp_p->data.patient_code , ptr->data.patient_code) == 0)
                    break;
                temp_p = temp_p->next;
            }

            getchar();
            delete_exact_lines(2);
        }

        printf("patient's data\n");
        printf("===============\n\n");
        print_pat_data(ptr_c , temp_p , PRINT_ALL_DATA);

        printf("which of the following do you want to modify about the patient info with code of (%s)? \n" , ptr->data.patient_code);
        printf("============================================================================================\n\n");
        printf("(1) modify patient's reservation data: \n");
        printf("(2) modify patient's biography data: \n");
        printf("(3) Exist:\n");
        printf("\n============================================================================================\n");

        choice_state check_var_choice = check_choice(&choice);
        while(check_var_choice == WRONG_CHOICE_FORMAT)
        {
            printf("WARNING!! choice is always a number, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_var_choice = check_choice(&choice);
        }

        while(1)
        {
            if(choice == 1)//modify patient's reservation data
            {
                getchar();
                system("cls");

                printf("\t\t===============================\n");
                printf("\t\t**patient reservation section**\n");
                printf("\t\t===============================\n\n");
                printf("patient's reservation data\n");
                printf("==========================\n\n");
                print_pat_data(ptr_c , temp_p , PRINT_RES_DATA);

                if(clinic_sched_full(ptr_c) == 1)
                    printf("reservation list during week for all doctors is full, so it's pointless to modify to the same reservation data...\n");
                else
                {
                    bool stat_getting_data_res = getting_data_res(ptr_c , temp_p , WITH_MOD_PAT);
                    if(stat_getting_data_res == 1)
                    {
                        printf("\t\t=============================================\n");
                        printf("\t\tchanging reservation info successfully done!!\n");
                        printf("\t\t=============================================\n");
                        flag = 1;
                    }
                }

                printf("do you want to change any of biography data of the same patient (y/n)? ");
                des_state check_decision = check_des(&des);
                while(check_decision == WRONG_DES_FORMAT)
                {
                    printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    printf("do you want to change any of biography data of the same patient (y/n)? ");
                    check_decision = check_des(&des);
                }
                getchar();
                if(des == 'n')
                    break;
                else if(des == 'y')
                    choice = 2;
            }

            else if(choice == 2)
            {
                bool stat_mod_pat_bio_data = mod_pat_bio_data(ptr_c , ptr , temp_p);
                if(stat_mod_pat_bio_data == 1)
                    flag = 1;

                printf("do you want to change any of reservation data of the same patient (y/n)? ");
                des_state check_decision = check_des(&des);
                while(check_decision == WRONG_DES_FORMAT)
                {
                    printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    printf("do you want to change any of reservation data of the same patient (y/n)? ");
                    check_decision = check_des(&des);
                }
                if(des == 'n')
                {
                    getchar();
                    break;
                }
                else if(des == 'y')
                    choice = 1;
            }

            else if(choice == 3)
            {
                des = 'e';
                break;
            }

            else
            {
                printf("WARNING!! wrong choice not included in the list...\n");
                break;
            }
        }
        if(des == 'e')
        {
            getchar();
            free(ptr);
            ptr = NULL;
            system("cls");
            return;
        }
        else if(flag == 1)
        {
            printf("**patient's data after modification**\n");
            printf("=====================================\n\n");

            print_pat_data(ptr_c , temp_p , PRINT_ALL_DATA);
        }

        printf("do you want to do another modification to the same patient (y/n)? ");
        des_state check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to do another modification to the same patient (y/n)? ");
            check_decision = check_des(&des);
        }

        getchar();

        if(des == 'y')
        {
            system("cls");
            key_same_pat = 1;
            continue;
        }

        key_same_pat = 0;

        printf("do you want to do another modification to another patient (y/n)? ");
        check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to do another modification to another patient (y/n)? ");
            check_decision = check_des(&des);
        }

        getchar();
        if(des == 'y')
        {
            system("cls");
            continue;
        }
        else if(des == 'n')
        {
            free(ptr);
            ptr = NULL;
            return;
        }
    }
}

/********************************************************************/

void getting_dr_period(USAGE_COND use)
{
    for(u16 i = 0 ; i < 12 ; i++)
    {
        if(use == FOR_PER1)
        {
            if( (clinic_schedule[i].day == sat_per1) || (clinic_schedule[i].day == sun_per1) || (clinic_schedule[i].day == mon_per1) || (clinic_schedule[i].day == tues_per1) || (clinic_schedule[i].day == wens_per1) || (clinic_schedule[i].day == thur_per1) )
            {
                getting_dr(clinic_schedule[i].doctor);
            }
        }
        else if(use == FOR_PER2)
        {
            if( (clinic_schedule[i].day == sat_per2) || (clinic_schedule[i].day == sun_per2) || (clinic_schedule[i].day == mon_per2) || (clinic_schedule[i].day == tues_per2) || (clinic_schedule[i].day == wens_per2) || (clinic_schedule[i].day == thur_per2) )
            {
                getting_dr(clinic_schedule[i].doctor);
            }
        }
    }
    printf("\n\n");

}

/********************************************************************/

void print_DRs_schedule()
{
    u8 ch[2] = {0 , 0};

    printf("\t\t\t\t\t\t\t\t=======================\n");
    printf("\t\t\t\t\t\t\t\t**Clinic DRs Schedule**\n");
    printf("\t\t\t\t\t\t\t\t=======================\n\n");

    printf("\t\t\t\tSat.%-20ssun.%-20smon.%-20stues.%-19swed.%-20sthur.\n" , ch , ch , ch , ch , ch);
    printf("From 2:00 pm to 6:00 pm  :\t");
    getting_dr_period(FOR_PER1);
    printf("From 6:00 pm to 10:00 pm :\t");
    getting_dr_period(FOR_PER2);
}

/********************************************************************/

void print_pat_res(clinic *ptr_c)
{
    u8 des = 'm';
    patient_node *temp;

    patient_node *ptr = (patient_node *)malloc(sizeof(patient_node));
    if(ptr == NULL)
    {
        printf("heap is full (please try to free some memory in heap first)...\n");
        return;
    }

    if(clinic_sched_empty(ptr_c) == 1)
    {
        printf("reservation list of clinic is empty (no data to modify)...\n");
        return;
    }

    while(1)
    {
        printf("\t\t====================================\n");
        printf("\t\t**showing patient reservation data**\n");
        printf("\t\t====================================\n\n");
        CLINIC_DATA_COND check_patient_code = patient_code(ptr_c , ptr , GETTING_CODE_TO_MODIFY);
        while(1)
        {
            if(check_patient_code == WRONG_CODE)
            {
                printf("WARNING!! wrong patient code format, please try again...\n");

                getchar();
                delete_exact_lines(3);

                check_patient_code = patient_code(ptr_c , ptr , GETTING_CODE_TO_MODIFY);
            }
            else if(check_patient_code == PATIENT_NODE_NOT_EXSISTED)
            {
                printf("WARNING!! patient code is not listed in reservation list, do you want to enter another patient code (y/n)? ");

                des_state check_decision = check_des(&des);
                while(check_decision == WRONG_DES_FORMAT)
                {
                    printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    printf("WARNING!! patient code is not listed in reservation list, do you want to enter another patient code (y/n)? ");
                    check_decision = check_des(&des);
                }
                getchar();
                if(des == 'y')
                {
                    delete_exact_lines(3);
                    check_patient_code = patient_code(ptr_c , ptr , GETTING_CODE_TO_MODIFY);
                }
                else if(des == 'n')
                {
                    free(ptr);
                    ptr = NULL;
                    system("cls");
                    return;
                }
            }
            else if(check_patient_code == PATIENT_NODE_EXSISTED)
                break;
        }

        temp = ptr_c->head;
        while(temp != NULL)
        {
            if( strcmp(temp->data.patient_code , ptr->data.patient_code) == 0 )
                break;

            temp = temp->next;
        }
        delete_exact_lines(1);
        printf("\t\t====================================================\n");
        printf("\t\t**reservation data of patient with code of (%s)**\n" , temp->data.patient_code);
        printf("\t\t====================================================\n\n");
        printf("====================================================\n\n");

        printf("name\t\t\t\t   gender\tage\t\tphone number\t\tgovernment\t\tdistrict\t\t\t\tstreet\t\t\t\t\thome number\n");
        printf("%-35s" , temp->data.name);

        if(temp->data.gender == 'm')
            printf("male\t\t");
        else if(temp->data.gender == 'f')
            printf("female\t\t");

        printf("%d\t\t%-11s\t\t" , temp->data.age , temp->data.phone_num);
        show_gover_patient(temp);
        printf("\t\t%-35s\t%-35s\t%d\n" , temp->data.pat_addre.distr , temp->data.pat_addre.street , temp->data.pat_addre.home_no);

        printf("\n\ndoctor's name : ");
        getting_dr(temp->data.doctor);
        printf("\nres_day/per :");
        print_res_day_head(temp->data.working_day);
        printf("\nappointment time : ");
        print_res_appoi(temp->data.appoi);
        printf("\n");
        printf("possible illness: ");
        show_problem_patient(temp);
        printf("\n");

        printf("\n\n====================================================\n");

        printf("do you want to show data for another patient code (y/n)? ");
        des_state check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to show data for another patient code (y/n)? ");
            check_decision = check_des(&des);
        }
        getchar();

        if(des == 'y')
        {
            system("cls");
            continue;
        }
        else if(des == 'n')
        {
            free(ptr);
            ptr = NULL;
            return;
        }
    }
}

/********************************************************************/

void print_all_pat_data(clinic *ptr_c)
{
    if(clinic_sched_empty(ptr_c) == 1)
    {
        printf("reservation list of clinic is empty (doctor's schedule is empty)....\n");
        return;
    }

    patient_node *temp = ptr_c->head;
    printf("\t\t\t\t\t\t=================\n");
    printf("\t\t\t\t\t\t**Patients list**\n");
    printf("\t\t\t\t\t\t=================\n\n");

    printf("====================================================================================================================================================================================================================\n\n");

    while(temp != NULL)
    {
        printf("ID\tname\t\t\t\t   gender\tage\t\tphone number\t\tgovernment\t\tdistrict\t\t\t\tstreet\t\t\t\t\thome number\n");
        printf("%s\t%-35s" , temp->data.patient_code , temp->data.name);

        if(temp->data.gender == 'm')
            printf("male\t\t");
        else if(temp->data.gender == 'f')
            printf("female\t\t");

        printf("%d\t\t%-11s\t\t" , temp->data.age , temp->data.phone_num);
        show_gover_patient(temp);
        printf("\t\t%-35s\t%-35s\t%d\n" , temp->data.pat_addre.distr , temp->data.pat_addre.street , temp->data.pat_addre.home_no);

        printf("\n\ndoctor's name : ");
        getting_dr(temp->data.doctor);
        printf("\nres_day/per :");
        print_res_day_head(temp->data.working_day);
        printf("\nappointment time : ");
        print_res_appoi(temp->data.appoi);
        printf("\n");
        printf("possible illness: ");
        show_problem_patient(temp);
        printf("\n");

        printf("\n====================================================================================================================================================================================================================\n\n");
        temp = temp->next;
    }

    return;
}

/********************************************************************/

void delete_pat_res(clinic *ptr_c)
{
    u8 des = 'd';

    patient_node *ptr = (patient_node *)malloc(sizeof(patient_node));
    patient_node *temp_p = ptr_c->head;
    if(ptr == NULL)
    {
        printf("heap is full (please try to free some memory in heap first)...\n");
        return;
    }
    while(1)
    {
        printf("\t\t========================================\n");
        printf("\t\t**deleting patient reservation section**\n");
        printf("\t\t======================================\n\n");

        CLINIC_DATA_COND check_patient_code = patient_code(ptr_c , ptr , GETTING_CODE_TO_DELETE);
        while(1)
        {
            if(check_patient_code == WRONG_CODE)
            {
                printf("WARNING!! wrong patient code format, please try again...\n");

                getchar();
                delete_exact_lines(3);

                check_patient_code = patient_code(ptr_c , ptr , GETTING_CODE_TO_DELETE);
            }
            else if(check_patient_code == PATIENT_NODE_NOT_EXSISTED)
            {
                printf("WARNING!! patient code is not listed in reservation list, do you want to enter another patient code (y/n)? ");

                des_state check_decision = check_des(&des);
                while(check_decision == WRONG_DES_FORMAT)
                {
                    printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    printf("WARNING!! patient code is not listed in reservation list, do you want to enter another patient code (y/n)? ");
                    check_decision = check_des(&des);
                }
                getchar();
                if(des == 'y')
                {
                    delete_exact_lines(3);
                    check_patient_code = patient_code(ptr_c , ptr , GETTING_CODE_TO_DELETE);
                }
                else if(des == 'n')
                {
                    free(ptr);
                    ptr = NULL;
                    system("cls");
                    return;
                }
            }
            else if(check_patient_code == PATIENT_NODE_EXSISTED)
                break;
        }

        temp_p = ptr_c->head;
        while(temp_p != NULL)
        {
            if(strcmp(temp_p->data.patient_code , ptr->data.patient_code) == 0)
                break;
            temp_p = temp_p->next;
        }
        getchar();
        delete_exact_lines(2);

        /*delete node*/
        if( (temp_p->prev == NULL) && (temp_p->next == NULL) )//first and only node in DDL
        {
            ptr_c->head = ptr_c->tail = NULL;
        }
        else if(temp_p->prev == NULL)//first node in DLL
        {
            ptr_c->head = temp_p->next;
            temp_p->next->prev = NULL;
        }
        else if(temp_p->next == NULL)//last node in DLL
        {
            ptr_c->tail = temp_p->prev;
            temp_p->prev->next = NULL;
        }
        else//any node in between
        {
            temp_p->next->prev = temp_p->prev;
            temp_p->prev->next = temp_p->next;
        }

        ptr_c->node_nums--;
        free(temp_p);
        temp_p = NULL;

        printf("\t\t===========================================\n");
        printf("\t\tpatient with code (%s) successfully deleted\n" , ptr->data.patient_code);
        printf("\t\t===========================================\n");

        printf("do you want to delete another patient (y/n)? ");
        des_state check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to delete another patient (y/n)? ");
            check_decision = check_des(&des);
        }

        getchar();
        if(des == 'y')
        {
            system("cls");
            continue;
        }
        else if(des == 'n')
        {
            free(ptr);
            ptr = NULL;
            return;
        }
    }
}

/********************************************************************/
//======================================================================================================================================================
        /*************************   Doctor part   *************************/

void GoTo_doctor_section(clinic *ptr_c)
{
    u8 local_username[15];
    u8 local_password[10];
    DR local_doc;
    DAY local_working_day , local_dr_avail_day[3] = {0,0,0};

    u8 des = 'm';
    u16 choice;

    printf("\t\t==================\n");
    printf("\t\t**Doctor section**\n");
    printf("\t\t==================\n\n");

    CLINIC_DATA_COND check_doc_username = getting_username(local_username , DOCTOR);
    while(check_doc_username == WRONG_USERNAME)
    {
        printf("WARNING!! wrong doctor's username, please try again...\n");

        getchar();
        delete_exact_lines(3);

        check_doc_username = getting_username(local_username , DOCTOR);
    }

    CLINIC_DATA_COND check_doc_passw = getting_passw(local_password , local_username , DOCTOR);
    while(check_doc_passw == WRONG_PASSW)
    {
        printf("WARNING!! wrong doctor's password, please try again...\n");

        getchar();
        delete_exact_lines(3);

        check_doc_passw = getting_passw(local_password , local_username , DOCTOR);
    }

    getchar();
    delete_exact_lines(3);

    if(strcmp(local_username , DR_SM_username) == 0)       local_doc = dr_shon_murphy;
    else if(strcmp(local_username , DR_NM_username) == 0)  local_doc = dr_neil_millendes;
    else if(strcmp(local_username , DR_MS_username) == 0)  local_doc = dr_mohamed_saleh;
    else if(strcmp(local_username , DR_EO_username) == 0)  local_doc = dr_eslam_osama;


    while(1)
    {
        printf("=====================================================================================================\n");
        print_dr_wellcome_head(local_doc);
        printf("\n\n");
        printf("(1) showing doctor schedule for week\n");
        printf("(2) showing doctor week reservation \n");
        printf("(3) showing doctor day reservation\n");
        printf("(4) showing patient reservation data\n");
        printf("(5) Exist\n");

        printf("\n\n=====================================================================================================\n");

        choice_state check_var_choice = check_choice(&choice);
        while(check_var_choice == WRONG_CHOICE_FORMAT)
        {
            printf("WARNING!! choice is always a number, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_var_choice = check_choice(&choice);
        }

        getchar();
        if(choice != 5)
            system("cls");

        switch(choice)
        {
        case 1 :
            print_one_DR_schedule(local_doc);
            break;

        case 2:
            print_week_data(ptr_c , local_doc);
            break;

        case 3:
            printf("\t\t===========================\n");
            printf("\t\t**Doctor day reservations**\n");
            printf("\t\t===========================\n\n");
            show_working_days_period_list(local_doc , local_dr_avail_day , NORM_PRINT);

            CLINIC_DATA_COND check_patient_working_day = patient_working_day(&local_working_day , local_dr_avail_day , NORM_PRINT);
            while(check_patient_working_day == WRONG_DAY_NUM)
            {
                printf("WARNING!! you must choose a number from the above list, please try again...\n");

                getchar();
                delete_exact_lines(3);

                check_patient_working_day = patient_working_day(&local_working_day , local_dr_avail_day , NORM_PRINT);
            }

            /*delete choice list and line of asking for day/period and exchange them with one line of the choosen day/period*/
            delete_exact_lines(4);
            print_day_data(ptr_c , local_doc , local_working_day);
            break;

        case 4:
            print_pat_res(ptr_c);
            break;

        case 5:
            des = 't';// 't' stands for terminate
            break;

        default:
            printf("WARNING!! wrong choice....\n");
            break;
        }

        if(des == 't')
            return;
        else
        {
            printf("do you want to continue in doctor section (y/n)? ");
            des_state check_decision = check_des(&des);
            while(check_decision == WRONG_DES_FORMAT)
            {
                printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                getchar();
                delete_exact_lines(3);

                printf("do you want to continue in doctor section (y/n)? ");
                check_decision = check_des(&des);
            }

            getchar();
            if(des == 'y')
            {
                system("cls");
                printf("\t\t==================\n");
                printf("\t\t**Doctor section**\n");
                printf("\t\t==================\n\n");
                continue;
            }
            else if(des == 'n')
                return;
        }
    }
}

/********************************************************************/

void print_dr_wellcome_head(DR doctor)
{
    switch(doctor)
    {
        case dr_shon_murphy:
            printf("\t\t\t\t===========================\n");
            printf("\t\t\t\t**Wellcome Dr.Shon Murphy**\n");
            printf("\t\t\t\t===========================\n");
            break;
        case dr_neil_millendes:
            printf("\t\t\t\t==============================\n");
            printf("\t\t\t\t**Wellcome Dr.Neil Millendes**\n");
            printf("\t\t\t\t==============================\n");
            break;
        case dr_eslam_osama:
            printf("\t\t\t\t===========================\n");
            printf("\t\t\t\t**Wellcome Dr.Eslam Osama**\n");
            printf("\t\t\t\t===========================\n");
            break;
        case dr_mohamed_saleh:
            printf("\t\t\t\t=============================\n");
            printf("\t\t\t\t**Wellcome Dr.Mohamed Saleh**\n");
            printf("\t\t\t\t=============================\n");
            break;
    }
}

/********************************************************************/

void print_one_DR_schedule(DR doctor)
{
    if(doctor == dr_neil_millendes)
    {
        printf("\t\t=================================\n");
        printf("\t\tDR.Neil Millendes's week schedule\n");
        printf("\t\t=================================\n\n");
    }
    else if(doctor == dr_shon_murphy)
    {
        printf("\t\t==============================\n");
        printf("\t\tDR.Shon Murphy's week schedule\n");
        printf("\t\t==============================\n\n");
    }
    else if(doctor == dr_eslam_osama)
    {
        printf("\t\t==============================\n");
        printf("\t\tDR.Eslam Osama's week schedule\n");
        printf("\t\t==============================\n\n");
    }
    else if(doctor == dr_mohamed_saleh)
    {
        printf("\t\t================================\n");
        printf("\t\tDR.Mohamed Saleh's week schedule\n");
        printf("\t\t================================\n\n");
    }

    for(u16 i = 0 ; i < NUM_PER_WEEK ; i++)
    {
        if(doctor == clinic_schedule[i].doctor)
        {
           print_res_day_head(clinic_schedule[i].day);
           printf("\n");
        }
    }
}

/********************************************************************/

                    /**********DEALING WITH BINARY SEARCH TREE**********/

/********************************************************************/

void clear_BST(ptr_tree ptr)
{
    if(ptr)
    {
        clear_BST(ptr->left);
        clear_BST(ptr->right);

        free(ptr);
        ptr = NULL;
    }
}

/********************************************************************/

/*Binary Search Tree always follows rule of left < vertex < right*/
CLINIC_DATA_COND insert_node_BST(ptr_tree *ptr , patient_data pat)
{
    /*if tree is empty*/
    if(*ptr == NULL)
    {
        *ptr = (tree_node *)malloc(sizeof(tree_node));

        /*if memory was allocated then assign data*/
        if(*ptr != NULL)
        {
            /*copy all data of patient in BST node*/
            strcpy((*ptr)->data.patient_code , pat.patient_code);
            strcpy((*ptr)->data.name , pat.name);
            (*ptr)->data.gender = pat.gender;
            (*ptr)->data.age = pat.age;
            (*ptr)->data.pat_addre.gover = pat.pat_addre.gover;
            strcpy((*ptr)->data.pat_addre.distr , pat.pat_addre.distr);
            (*ptr)->data.pat_addre.home_no = pat.pat_addre.home_no;
            strcpy((*ptr)->data.pat_addre.street , pat.pat_addre.street);
            strcpy((*ptr)->data.phone_num , pat.phone_num);
            (*ptr)->data.doctor = pat.doctor;
            (*ptr)->data.working_day = pat.working_day;
            (*ptr)->data.illness = pat.illness;
            (*ptr)->data.appoi = pat.appoi;

            (*ptr)->left = NULL;
            (*ptr)->right = NULL;
        }
        else
            return HEAP_FULL;
    }
    else
    {/*tree is not empty*/
        /*appointment number of new node to be added is less than appointment number of current node (left < vertex)*/
        if(pat.appoi < (*ptr)->data.appoi)
            insert_node_BST(&( (*ptr)->left ) , pat);

        /*appointment number of new node to be added is greater than appointment number of current node (right > vertex)*/
        else if(pat.appoi > (*ptr)->data.appoi)
            insert_node_BST(&( (*ptr)->right ) , pat);
    }

    return OK;
}

/********************************************************************/
/*
WE ONLY HAVE 2 METHODS OF PRINTING DR DATA :
============================================
(1) printing just reservations of one period of working day
    related to dr schedule (inorder) ex) for period 1 starts
    from (02:00 -> 02:20) to (05:40 -> 06:00)

(2) printing reservations of the whole week which are 3 periods
    of each working day for all week
*/

/********************************************************************/

/*for method 1*/

void print_dr_day_head(DR doctor , DAY day)
{
    switch(doctor)
    {
        case dr_shon_murphy:    printf("\t\tDr.Shon Murphy's reservation list during");      print_res_day_head(day);  break;
        case dr_neil_millendes: printf("\t\tDr.Neil Millendes's reservation list during");   print_res_day_head(day);  break;
        case dr_eslam_osama:    printf("\t\tEslam Osama's reservation list during");         print_res_day_head(day);  break;
        case dr_mohamed_saleh:  printf("\t\tMohamed Saleh's reservation list during");       print_res_day_head(day);  break;
    }
}

/********************************************************************/

/*for method 2*/

void print_dr_week_head(DR doctor)
{
    switch(doctor)
    {
        case dr_shon_murphy:    printf("\t\t**Dr.Shon Murphy's ");      break;
        case dr_neil_millendes: printf("\t\t**Dr.Neil Millendes's ");   break;
        case dr_eslam_osama:    printf("\t\t**Eslam Osama's ");         break;
        case dr_mohamed_saleh:  printf("\t\t**Mohamed Saleh's ");       break;
    }
}

/********************************************************************/

/*for method 1*/

void print_day_data(clinic *ptr_c , DR doctor , DAY day)
{
    if(clinic_sched_empty(ptr_c) == 1)
    {
        printf("reservation list of clinic is empty (doctor's schedule is empty)....\n");
        return;
    }

    printf("\t\t==============================================================\n");
    print_dr_day_head(doctor , day);
    printf("\n\t\t==============================================================\n\n");

    if(check_sched_dr(ptr_c , doctor , day , CHECK_DR_DAY) == DR_DAY_SCHED_EMPTY)
    {
        printf("reservation list for day of doctor is empty (no data to show)....\n");
        return;
    }

    ptr_tree rootpt = NULL;

    patient_node *temp = ptr_c->head;
    while(temp != NULL)
    {
        if( (temp->data.doctor == doctor) && (temp->data.working_day == day) )
            insert_node_BST(&rootpt , temp->data);
        temp = temp->next;
    }

    printf("\t\t\t\tpatient code\n");

    print_BST_inorder(rootpt);

    clear_BST(rootpt);
}

/********************************************************************/

/*for method 2*/

void print_week_data(clinic *ptr_c , DR doctor)
{
    DAY local_day = 0;
    ptr_tree rootpt = NULL;

    if(clinic_sched_empty(ptr_c) == 1)
    {
        printf("reservation list of clinic is empty (doctor's schedule is empty)....\n");
        return;
    }

    printf("\t\t====================================================\n");
    print_dr_week_head(doctor);
    printf("reservation list during week**\n");
    printf("\t\t====================================================\n\n");

    if(check_sched_dr(ptr_c , doctor , local_day , CHECK_DR_WEEK) == DR_WEEK_SCHED_EMPTY)
    {
        printf("reservation list for week of doctor is empty (no data to show)....\n");
        return;
    }

    printf("\t\t\t\tpatient code\n");

    patient_node *temp = ptr_c->head;

    for(u16 i = 0 ; i < 12 ; i++)//12 is related to number of periods per week
    {
        if(clinic_schedule[i].doctor == doctor)
            local_day = clinic_schedule[i].day;
        else
            continue;

        print_res_day_head(local_day);
        printf(" :\n");

        if(check_sched_dr(ptr_c , doctor , local_day , CHECK_DR_DAY) == DR_DAY_SCHED_EMPTY)
        {
            printf("reservation list for day of doctor is empty (no data to show)....\n");
            printf("\n");
            temp = ptr_c->head;
            continue;
        }

        while(temp != NULL)
        {
            if( (temp->data.doctor == doctor) && (temp->data.working_day == local_day) )
                insert_node_BST(&rootpt , temp->data);
            temp = temp->next;
        }
        temp = ptr_c->head;
        print_BST_inorder(rootpt);
        clear_BST(rootpt);
        printf("\n");
    }
}

/********************************************************************/

void print_BST_inorder(ptr_tree ptr)//LVR
{
    if(ptr)
    {
        print_BST_inorder(ptr->left);

        print_res_appoi(ptr->data.appoi);
        printf(" \t     %s\n" , ptr->data.patient_code);

        print_BST_inorder(ptr->right);
    }
}
//======================================================================================================================================================
/********************************************************************/
//======================================================================================================================================================
        /*************************   patient part   *************************/

CLINIC_DATA_COND print_avail_week_data(clinic *ptr_c , DR doctor)
{
    DAY local_per_appoi[12];
    DAY local_day = 0;
    patient_node *temp = ptr_c->head;

    if(clinic_sched_full(ptr_c) == 1)
    {
        printf("reservation list of clinic is full (doctor's schedule is full)....\n");
        return FULL_SCHE_CLINIC;
    }

    printf("\t\t==========================================================\n");
    print_dr_week_head(doctor);
    printf("available appointments during week**\n");
    printf("\t\t==========================================================\n\n");

    if(check_sched_dr(ptr_c , doctor , local_day , CHECK_DR_WEEK) == DR_WEEK_SCHED_FULL)
    {
        printf("reservation list for week of doctor is full (no data to show)....\n");
        getchar();
        system("cls");
        return OK;
    }

    for(u16 i = 0 ; i < 12 ; i++)//12 is related to number of periods per week
    {
        if(clinic_schedule[i].doctor == doctor)
            local_day = clinic_schedule[i].day;
        else
            continue;

        if( (local_day == sat_per1) || (local_day == sun_per1) || (local_day == mon_per1) || (local_day == tues_per1) || (local_day == wens_per1) || (local_day == thur_per1) )
        {
            for(u16 p = 0 ; p < 12 ; p++)
                local_per_appoi[p] = p+1;
        }
        else if( (local_day == sat_per2) || (local_day == sun_per2) || (local_day == mon_per2) || (local_day == tues_per2) || (local_day == wens_per2) || (local_day == thur_per2) )
        {
            for(u16 p = 0 ; p < 12 ; p++)
                local_per_appoi[p] = p+13;
        }

        print_res_day_head(local_day);
        printf(" :\n");

        if(check_sched_dr(ptr_c , doctor , local_day , CHECK_DR_DAY) == DR_DAY_SCHED_FULL)
        {
            printf("reservation list for day of doctor is full (no data to show)....\n");
            printf("\n");
            temp = ptr_c->head;
            continue;
        }

        temp = ptr_c->head;
        while(temp != NULL)
        {
            if(local_day == temp->data.working_day)
            {
                for(u16 j = 0 ; j < 12 ; j++)//12 is related to number of appoint.s per week
                {
                    if(local_per_appoi[j] == temp->data.appoi)
                        local_per_appoi[j] = 0;
                }
            }
            temp = temp->next;
        }

        /*printing available appointments for working day*/
        for(u16 k = 0 ; k < 12 ; k++)
        {
                if(local_per_appoi[k] == 0)
                    continue;

                print_res_appoi(local_per_appoi[k]);
                printf("\n");
        }
        printf("\n");
    }
    return OK;
}

/********************************************************************/

void GoTo_patient_section(clinic *ptr_c)
{
    u8 des = 'm';
    u16 choice;

    while(1)
    {
        printf("\t\t=================\n");
        printf("\t\tpatient section**\n");
        printf("\t\t=================\n\n");

        printf("=====================================================================================================\n\n");

        printf("(1) showing doctors schedule for week\n");
        printf("(2) showing available appointment of doctor \n");
        printf("(3) Exist\n");

        printf("\n\n=====================================================================================================\n");

        choice_state check_var_choice = check_choice(&choice);
        while(check_var_choice == WRONG_CHOICE_FORMAT)
        {
            printf("WARNING!! choice is always a number, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_var_choice = check_choice(&choice);
        }

        getchar();
        if(choice != 3)
            system("cls");

        switch(choice)
        {
        case 1 :
            print_DRs_schedule();
            break;

        case 2:
            printf("\t\t\t\t\t======================================\n");
            printf("\t\t\t\t\t**available appointments during week**\n");
            printf("\t\t\t\t\t======================================\n\n");

            for(DR local_doc = dr_shon_murphy ; local_doc <= dr_mohamed_saleh ; local_doc++)
            {
                if(print_avail_week_data(ptr_c , local_doc) == FULL_SCHE_CLINIC)
                    break;
            }
            break;

        case 3:
            des = 't';// 't' stands for terminate
            break;

        default:
            printf("WARNING!! wrong choice....\n");
            break;
        }

        if(des == 't')
            return;
        else
        {
            printf("do you want to continue in patient section (y/n)? ");
            des_state check_decision = check_des(&des);
            while(check_decision == WRONG_DES_FORMAT)
            {
                printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                getchar();
                delete_exact_lines(3);

                printf("do you want to continue in patient section (y/n)? ");
                check_decision = check_des(&des);
            }

            getchar();
            if(des == 'y')
            {
                system("cls");
                continue;
            }
            else if(des == 'n')
                return;
        }
    }
}

//======================================================================================================================================================
/********************************************************************/
//======================================================================================================================================================
        /*************************   Administrator part   *************************/

void GoTo_admin_section(clinic *ptr_c)
{
    u8 local_username[6];
    u8 local_password[9];

    u8 des = 'm';
    u16 choice;

    printf("\t\t=======================\n");
    printf("\t\tadministrator section**\n");
    printf("\t\t=======================\n\n");

    CLINIC_DATA_COND check_admin_username = getting_username(local_username , ADMIN);
    while(check_admin_username == WRONG_USERNAME)
    {
        printf("WARNING!! wrong administrator username, please try again...\n");

        getchar();
        delete_exact_lines(3);

        check_admin_username = getting_username(local_username , ADMIN);
    }

    CLINIC_DATA_COND check_admin_passw = getting_passw(local_password , local_username , ADMIN);
    while(check_admin_passw == WRONG_PASSW)
    {
        printf("WARNING!! wrong administrator password, please try again...\n");

        getchar();
        delete_exact_lines(3);

        check_admin_passw = getting_passw(local_password , local_username , ADMIN);
    }

    getchar();
    delete_exact_lines(3);

    while(1)
    {

        printf("=====================================================================================================\n\n");

        printf("(1) showing doctors schedule for week\n");
        printf("(2) doing reservation for patient\n");
        printf("(3) modifying patient data\n");
        printf("(4) showing patient reservation data\n");
        printf("(5) showing patients record list\n");
        printf("(6) deleting patient reservation\n");
        printf("(7) Exist:\n");

        printf("\n\n=====================================================================================================\n");

        choice_state check_var_choice = check_choice(&choice);
        while(check_var_choice == WRONG_CHOICE_FORMAT)
        {
            printf("WARNING!! choice is always a number, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_var_choice = check_choice(&choice);
        }

        getchar();
        if(choice != 7)
            system("cls");

        switch(choice)
        {
        case 1 :
            print_DRs_schedule();
            break;

        case 2:
            add_patient(ptr_c);
            break;

        case 3:
            modify_pat_data(ptr_c);
            break;

        case 4:
            print_pat_res(ptr_c);
            break;

        case 5:
            print_all_pat_data(ptr_c);
            break;

        case 6:
            delete_pat_res(ptr_c);
            break;

        case 7:
            des = 't';// 't' stands for terminate
            break;

        default:
            printf("WARNING!! wrong choice....\n");
            break;
        }

        if(des == 't')
            return;
        else
        {
            printf("do you want to continue in administrator section (y/n)? ");
            des_state check_decision = check_des(&des);
            while(check_decision == WRONG_DES_FORMAT)
            {
                printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                getchar();
                delete_exact_lines(3);

                printf("do you want to continue in administrator section (y/n)? ");
                check_decision = check_des(&des);
            }

            getchar();
            if(des == 'y')
            {
                system("cls");
                printf("\t\t=======================\n");
                printf("\t\tadministrator section**\n");
                printf("\t\t=======================\n\n");
                continue;
            }
            else if(des == 'n')
                return;
        }
    }
}
//======================================================================================================================================================
/********************************************************************/

void entry_window(clinic *ptr_c)
{
    u8 des = 'm';
    u16 choice;
    bool flag = 0;

    while(1)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t===============================\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t**welcome to El-safwa clinic **\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t===============================\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t(1) you are doctor\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t(2) you are patient\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t(3) you are administrator\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t(4) Exit\n");
        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t===============================\n\n");

        printf("\t\t\t\t\t\t\t\t\t\t\t\t");
        choice_state check_var_choice = check_choice(&choice);
        while(check_var_choice == WRONG_CHOICE_FORMAT)
        {
            printf("\t\t\t\t\t\t\t\t\t\t\t\tWARNING!! choice is always a number, please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            check_var_choice = check_choice(&choice);
        }

        getchar();
        if(choice != 4)
            system("cls");

        switch(choice)
        {
        case 1 :
            GoTo_doctor_section(ptr_c);
            break;

        case 2:
            GoTo_patient_section(ptr_c);
            break;

        case 3:
            GoTo_admin_section(ptr_c);
            break;

        case 4:
            des = 't';// 't' stands for terminate
            break;

        default:
            printf("WARNING!! wrong choice....\n");
            flag = 1;
            break;
        }

        if(des == 't')
        {
            free(ptr_c);
            ptr_c = NULL;
            return;
        }

        else
        {
            if(flag == 1) printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            printf("do you want to return to clinic entry list (y/n)? ");
            des_state check_decision = check_des(&des);
            while(check_decision == WRONG_DES_FORMAT)
            {
                if(flag == 1) printf("\t\t\t\t\t\t\t\t\t\t\t\t");
                printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                getchar();
                delete_exact_lines(3);

                if(flag == 1) printf("\t\t\t\t\t\t\t\t\t\t\t\t");
                printf("do you want to return to clinic entry list (y/n)? ");
                check_decision = check_des(&des);
            }

            getchar();
            if(des == 'y')
            {
                system("cls");
                continue;
            }
            else if(des == 'n')
            {
                free(ptr_c);
                ptr_c = NULL;
                return;
            }
        }
    }
}

/********************************************************************/
