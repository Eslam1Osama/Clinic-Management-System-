#include<stdio.h>//for input output processes and getchar()
#include<stdbool.h>// to use bool
#include<stdlib.h>//for dynamic memory allocation
#include<string.h>//to use strcpy() & strcmp() & strlen() functions

#include"LIB.h"
#include"utility_control.h"

#include"CMS.h"
int main()
{
    clinic clin;

    create_clinic_sched(&clin);

    entry_window(&clin);

    return 0;
}
