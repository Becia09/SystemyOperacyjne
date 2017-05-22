//gcc lab0.c -g
//valgrind ./a.out -g
#include <stdlib.h>
#include <stdio.h>
#include <utmpx.h>
#include <unistd.h> 
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>

int main(int argc, char **argv)
{
	int ret, flagId=0, flagGr=0;

	struct utmpx *a = getutxent();
	struct passwd *pwd;
	gid_t * idGrupy;
	struct group *grupa;

	while((ret = getopt(argc, argv, "ig::")) != -1)
	{
		switch (ret)
		{
			case 'i': flagId = 1; break;
			case 'g': flagGr = 1; break;
			default: printf ("nieprawidlowe przelaczniki"); return (0);
		}
	}

	while(a)
	{
		if (a->ut_type==7)
		{
         pwd = getpwnam(a->ut_user);
         if (flagId) printf("%d ", pwd->pw_uid);
         printf("%s ", a->ut_user);
			if (flagGr)
			{
            int il_grup=0;
				getgrouplist(a->ut_user, pwd->pw_gid, idGrupy, &il_grup);
         	idGrupy = malloc (sizeof(gid_t)*il_grup);
				getgrouplist(a->ut_user, pwd->pw_gid, idGrupy, &il_grup); //funkcja uzupelnia przedostatni parametr

				printf("[");
				for (int i=0; i<il_grup; i++)
				{
					grupa = getgrgid(idGrupy[i]);
					printf ("%s ", grupa->gr_name);
				}
				free(idGrupy);
				printf("]");
			}
			printf("\n");
		}
	a = getutxent();
	}

	return(0);
}
