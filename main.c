//export abc=/home/cipher/Desktop/pro/op/a.out
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int choice;
char fname[100],fname_dir[100]=".";
FILE *fp,*fo;
char str[100];
void Itoa(int value) {
    int radix=10;
	static char dig[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz";
    int n = 0, neg = 0;
    unsigned int v;
    char* p, *q;
    char c;
    v = value;
    do {
        str[n++] = dig[v%radix];
        v /= radix;
    } while (v);
    str[n] = '\0';
    for (p = str, q = p + n/2; p != q; ++p, --q)
        c = *p, *p = *q, *q = c;
}
void update_main(int ver_no)
{
	char fnames[100];
	char *date; 
	time_t timer; 
	timer=time(NULL); 
	date = asctime(localtime(&timer)); 
	strcpy(fnames,fname_dir);
	strcat(fnames,"main");
	fp=fopen(fnames,"a+");
	if(!fp) printf("Error While Opening File...\n");
	else {fprintf(fp,"%d %s",ver_no,date);fclose(fp);}
}
void update_main_new(int ver_no)
{
	int d;
	chdir(fname_dir);
	char line[5][100];
	fo=fopen("main","r+");
	fp=fopen("new","w");
	while(ver_no--) 
	{
		fscanf(fo,"%d %s %s %s %s %s",&d,line[0],line[1],line[2],line[3],line[4]);
		fprintf(fp,"%d %s %s %s %s %s\n",d,line[0],line[1],line[2],line[3],line[4]);
	}
	remove("main");
	rename("new","main");
	chdir("..");
}
void update_ver(int ver_no)
{
	char fnames[100];
	strcpy(fnames,fname_dir);
	strcat(fnames,"version");
	fp=fopen(fnames,"w");
	if(!fp) printf("Error While Opening File...\n");
	else {fprintf(fp,"%d",ver_no);fclose(fp);}
}
int query()
{
	char fnames[100];
	int ver_no;
	strcpy(fnames,fname_dir);
	strcat(fnames,"version");
	fp=fopen(fnames,"r");
	if(!fp) printf("Error While Opening File...\n");
	else {
		fscanf(fp,"%d",&ver_no);
		fclose(fp);
		}
	return ++ver_no;
}
void initialise()
{
	char fnames[100]="mkdir -p .";
	strcat(fnames,fname);
	system(fnames);
	strcpy(fnames,fname_dir);
	strcat(fnames,"main");
	fp=fopen(fnames,"a+");
	fclose(fp);
	strcpy(fnames,fname_dir);
	strcat(fnames,"version");
	fp=fopen(fnames,"a+");
	fprintf(fp,"0");
	fclose(fp);
	printf("Press Enter To continue...");
	getchar();
	getchar();
}
void new_ver()
{
	int ver_no;
	ver_no=query();
	char fnames[100],fname1[100],fname_dir1[100],diff[200]="diff ";
	strcpy(fnames,fname);
	strcpy(fname1,fname);
	strcat(fnames,"~ > ");
	strcat(fname1," ");
	strcat(fname1,fnames);
	strcat(diff,fname1);
	Itoa(ver_no);																//send converted value into char str[100]
	strcpy(fname_dir1,fname_dir);
	strcat(fname_dir1,str);
	strcat(diff,fname_dir1);
	system(diff);
	update_main(ver_no);
	update_ver(ver_no);
	printf("Version %d Created !!!\nPress Enter To continue...",ver_no);
	getchar();
	getchar();
}
void history()
{
	char fnames[100]="cat ";
	strcat(fnames,fname_dir);
	strcat(fnames,"main");
	system(fnames);
	printf("\n			Press Enter To continue...");
	getchar();
	getchar();
}
void restore_ver()
{
int ch,cur=query();
cur--;
history();
printf("Which Version you want?\n");
while(1){
scanf("%d",&ch);
if(ch>cur) {printf("You Can Only Enter choice Between 1-%d\n",cur);}
else{
	while(cur>ch){
		char fnames[50],pname[50],patch[50]="patch ";
		strcpy(pname,fname_dir);
		Itoa(cur);
		strcat(pname,str);
		strcpy(fnames,fname);
		strcat(fnames," ");
		strcat(patch,fnames);
		strcat(patch,pname);
		strcat(patch," > ");
		strcat(patch,fname_dir);
		strcat(patch,".log");
		//printf("%s    ---%s\n",patch,pname);
		system(patch);
		remove(pname);
		cur--;
	}
	update_ver(ch);
	update_main_new(ch);
	printf("Version %d Restored!!!\nPress Enter To continue...",ch);
	getchar();
	getchar();
	return;
	}
}
}
int main(int argc, char *argv[])
{
	char fnames[100];
	if(argc<2){printf("Error:please enter file name\n");return 0;}
	fp=fopen(argv[1],"r");if(!fp) {printf("ERROR: cannot access %s (No such file exists)\n",argv[1]);return 0;} else fclose(fp);
	strcpy(fname,argv[1]);
	strcat(fname_dir,argv[1]);
	strcat(fname_dir,"/");
	do
	{
	printf("Main Menu:\n"
			"1.Initialise\n"
			"2.Crete New Version\n"
			"3.Restore Version\n"
			"4.History\n"
			"5.Exit\n");
	printf("Enter Your Choice:\n");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:initialise();exit(0);break;
	case 2:strcpy(fnames,fname_dir);
	       strcat(fnames,"main");
		   if(!fopen(fnames,"r")) {printf("Error : Initialise %s First...\n",fname);return 0;} else fclose(fp);
		   new_ver();exit(0);break;
	case 3:strcpy(fnames,fname_dir);
	       strcat(fnames,"main");
		   if(!fopen(fnames,"r")) {printf("Error : Initialise %s First...\n",fname);return 0;} else fclose(fp);
		   restore_ver();exit(0);break;
	case 4:strcpy(fnames,fname_dir);
	       strcat(fnames,"main");
		   if(!fopen(fnames,"r")) {printf("Error : Initialise %s First...\n",fname);return 0;} else fclose(fp);
		   history();break;
	case 5:exit(0);break;
	default:printf("Wrong Choice...\n<press Enter to Continue>\n");
			getchar();getchar();getchar();
	}
	}while(1);
	return 0;
}