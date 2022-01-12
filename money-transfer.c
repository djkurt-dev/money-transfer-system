
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>

void menu();
void main();
int sendmoney();
char loggedEmail[30];

typedef struct transaction{
	char code[12];
	double amount;
	char sender[100];
	char sender_phone[12];
	char receiver[100];	
	char receiver_phone[11];		
}transaction;

struct teller{
	char email[50];
	char password[12];
}login,check,signup;

int generateCode(){
	int code,lower=1000000,upper=9999999;
	srand(time(NULL));
	code = (rand()%(upper-lower+1))+lower;
	return code;
}

void delay(int a){
	int add,time,i;
	
	time = a*100000000;
	for(i=0;i<time;i++){
		add*=i;
		add++;
		add++;
	}
}

void fordelay(){
	int i;
	printf("\n\n\n\t\t\t\t\t\t\t");
	for(i=0;i<3;i++){
		printf("* ");	
		delay(1);
	}
	system("cls");
}

int sendmoney(){
	fordelay();
	printf("\n\n\t| ================================================= SEND MONEY ================================================= |\n\n");
	transaction tr;
	char ch, converted[10], trans_code[10]="KMTS",fileName[15]="unclaimed.txt";
	int code;
	double charge, total;
	
	FILE *fp;
	fp = fopen("unclaimed.txt","a");
	if(!fp){
		printf("\n Unable to open : %s.", fileName);
		return -1;
	}
	
	printf("\n\t\tSENDER (name in ALL CAPS): ");
	ch = getchar();
	gets(tr.sender);
	printf("\n\t\tSENDER (phone): ");
	gets(tr.sender_phone);	
	printf("\n\t\tRECEIVER (name in ALL CAPS): ");
	gets(tr.receiver);
	printf("\n\t\tRECEIVER (phone): ");
	gets(tr.receiver_phone);
	
	amt:
	printf("\n\t\tAMOUNT: ");
	scanf("%lf",&tr.amount);
	
	if(tr.amount <= 50){
		charge = 5.0;
	}
	else if(tr.amount > 50 && tr.amount <= 100){
		charge = 10.0;
	} 
	else if(tr.amount > 100 && tr.amount <= 400){
		charge = 15.0;
	} 
	else if(tr.amount > 400 && tr.amount <= 800){
		charge = 20.0;
	} 
	else if(tr.amount > 800 && tr.amount <= 1500){
		charge = 25.0;
	}
	else if(tr.amount > 1500 && tr.amount <= 2500){
		charge = 30.0;
	}
	else if(tr.amount > 2500 && tr.amount <= 3500){
		charge = 35.0;
	}
	else if(tr.amount > 3500 && tr.amount <= 5000){
		charge = 40.0;
	}
	else if(tr.amount > 5000 && tr.amount <= 10000){
		charge = 60.0;
	} 
	else if(tr.amount > 10000 && tr.amount <= 15000){
		charge = 80.0;
	}
	else if(tr.amount > 15000 && tr.amount <= 20000){
		charge = 100.0;
	}
	else{
		printf("\n\t\t!!!!!!!!!! Send money cannot exceed P20,000 !!!!!!!!!!");
		printf("\n\t\tPlease enter amount again");
		goto amt;
	}
	
	total = tr.amount + charge;
	
	//reference code
	code = generateCode();
	sprintf(converted,"%d",code);
	strcat(trans_code,converted);
	strcpy(tr.code,trans_code);
	
	
	
	fprintf(fp,"%s\t%.2lf\t\t%s\t%s\t%s\t%s\n",tr.code,tr.amount,tr.sender,tr.sender_phone,tr.receiver,tr.receiver_phone);
	printf("\n\n\t| ***************************************** MONEY SENT SUCCESSFULLY ****************************************** |\n");
	printf("\n\t\t\t\tREFERENCE CODE: %37s\n\t\t\t\tSENDER\n\t\t\t\t\t%45s\n\t\t\t\t\t%45s\n\t\t\t\tRECEIVER\n\t\t\t\t\t%45s\n\t\t\t\t\t%45s\n\t\t\t\tAmount: Php%42.2lf\n\t\t\t\tService Fee: Php%37.2lf\n\t\t\t\tTOTAL => Php%41.2lf",tr.code,tr.sender,tr.sender_phone,tr.receiver,tr.receiver_phone,tr.amount,charge,total);

	fclose(fp);
	menu();
}

void claim(){
	fordelay();
	printf("\n\n\t| ================================================= CLAIM MONEY ================================================= |\n\n");

	transaction cl;
	FILE *fp,*fp2,*temp;
	char cont,line[500],*token,ch,code[15],temp_line[500];
	int found=0;
	
	enter_ref:
	printf("\n\t\tEnter Reference Code: ");	
	scanf("%s",code);
	
	fp = fopen("unclaimed.txt","r");
	fp2 = fopen("claimed.txt","a");
	
	while (fgets(line, sizeof(line), fp)) {
		token = strtok(line,"\t");		
		if(strcmp(token,code) == 0){		
			found=1;	
			strcpy(cl.code,code);
			printf("\n\t\tRECEIVER (name in ALL CAPS): ");
			ch = getchar();
			gets(cl.receiver);
			printf("\n\t\tRECEIVER (phone): ");
			gets(cl.receiver_phone);
			printf("\n\t\tSENDER (name in ALL CAPS): ");	
			gets(cl.sender);
			printf("\n\t\tSENDER (phone): ");
			gets(cl.sender_phone);
			printf("\n\t\tAMOUNT: ");
			scanf("%lf",&cl.amount);
			fprintf(fp2,"%s\t%.2lf\t\t%s\t%s\t%s\t%s\n",cl.code,cl.amount,cl.sender,cl.sender_phone,cl.receiver,cl.receiver_phone);
			fclose(fp);
			fclose(fp2);
		}
	}
	
	if(!found){
		printf("\n\t\t\t\t!!!!!!!!!!!! TRANSACTION NOT FOUND !!!!!!!!!!!!");		
		to_continue:
		printf("\n\t\t\t\tDo you want to enter again? [y/n] : ");		
		ch=getchar();
		cont=getchar();
		if(cont == 'Y' || cont == 'y'){
			goto enter_ref;
		} 
		if(cont == 'N' || cont == 'n'){
			system("cls");
			menu();
		} 
		else{
			printf("\n\t\t\t\t!!!!!!!!!!!! INVALID SELECTION !!!!!!!!!!!!");
			goto to_continue;
		}
	}	
	
	temp = fopen("temp.txt","w");
	fp = fopen("unclaimed.txt","r");
	while(fgets(line, sizeof(line), fp)){
		strcpy(temp_line,line);
		token = strtok(line,"\t");
		if(strcmp(token,code) != 0){
			fprintf(temp,"%s",temp_line);
		}
	}	
	fclose(temp);
	fclose(fp);	
	
	//modifying the unclaimed records
	temp = fopen("temp.txt","r");
	fp = fopen("unclaimed.txt","w");
	while(fgets(line, sizeof(line), temp)){
		fprintf(fp,"%s",line);
	}		
	fclose(temp);
	fclose(fp);
	remove("temp.txt");
	
	fordelay();
	printf("\n\n\t| ***************************************** MONEY CLAIMED SUCCESSFULLY ****************************************** |\n");
	printf("\n\t\t\t\tREFERENCE CODE: %37s\n\t\t\t\tAmount: %45.2lf\n\t\t\t\tCLAIMED BY:\n\t\t\t\t\t%45s\n\t\t\t\t\t%45s\n",cl.code,cl.amount,cl.receiver,cl.receiver_phone);
	menu();
}

int view_all(){
	printf("\n\t\t\t\t#################### FETCHING DATA ####################");
	fordelay();
	
	FILE *clmd,*uclmd;
	int count=0;
	char line[500];
	
	clmd = fopen("claimed.txt","r");
	uclmd = fopen("unclaimed.txt","r");
	system("cls");
	
	printf("\n\n\t| ================================================= CLAIMED ================================================= |\n\n");
	if(!clmd){
		printf("\n Unable to open : claimed.txt.");
		return -1;
	}	
	printf("\n\t\t-------------------------------------------------------------------------------------------\n");
	printf("\t\tRef. Code\tAmount\t\tSender\t\tPhone\t\tReceiver\tPhone");
	printf("\n\t\t-------------------------------------------------------------------------------------------\n");
	while (fgets(line, sizeof(line), clmd)) {
		count++;
		printf("\t\t%s", line); 	
	}
	if(!count){
		printf("\t\t\t\t\t\tNO CLAIMED TRANSACTIONS\n");
	}
	printf("\t\t-------------------------------------------------------------------------------------------\n");
	
	printf("\n\n\t| =============================================== UNCLAIMED ================================================= |\n\n");
	if(!uclmd){
		printf("\n Unable to open : unclaimed.txt.");
		return -1;
	}
	count=0;
	printf("\n\t\t-------------------------------------------------------------------------------------------\n");
	printf("\t\tRef. Code\tAmount\t\tSender\t\tPhone\t\tReceiver\tPhone");
	printf("\n\t\t-------------------------------------------------------------------------------------------\n");
	while (fgets(line, sizeof(line), uclmd)) {
		count++;
		printf("\t\t%s", line); 
	}	
	if(!count){
		printf("\t\t\t\t\t\tNO UNCLAIMED TRANSACTIONS\n");
	}
	printf("\t\t-------------------------------------------------------------------------------------------\n");
	
	fclose(clmd);
	fclose(uclmd);
	menu();
}

int view_claimed(){
	printf("\n\t\t\t\t#################### FETCHING DATA ####################");
	fordelay();
	printf("\n\n\t| ================================================= CLAIMED ================================================= |\n\n");
	FILE *fp;
	char fileName[20] = "claimed.txt",line[500];;
	int count=0;
	
	fp = fopen("claimed.txt","r");
	if(!fp){
		printf("\n Unable to open : %s ", fileName);
		return -1;
	}
	
	printf("\n\t\t-------------------------------------------------------------------------------------------\n");
	printf("\t\tRef. Code\tAmount\t\tSender\t\tPhone\t\tReceiver\tPhone");
	printf("\n\t\t-------------------------------------------------------------------------------------------\n");
	while (fgets(line, sizeof(line), fp)) {
		count++;
		printf("\t\t%s", line); 	
	}
	if(!count){
		printf("\t\t\t\t\t\tNO CLAIMED TRANSACTIONS\n");
	}
	printf("\t\t-------------------------------------------------------------------------------------------\n");
	fclose(fp);
	
	printf("\n\n\t| ================================================= CLAIMED ================================================= |\n\n");
	menu();
}

int view_unclaimed(){
	printf("\n\t\t\t\t#################### FETCHING DATA ####################");
	fordelay();
	printf("\n\n\t| =============================================== UNCLAIMED =============================================== |\n\n");
	
	FILE *fp;
	char fileName[20] = "unclaimed.txt",line[500];
	int count=0;
	
	fp = fopen("unclaimed.txt","r");
	if(!fp){
		printf("\n Unable to open : %s ", fileName);
		return -1;
	} 
	printf("\n\t\t-------------------------------------------------------------------------------------------\n");
	printf("\t\tRef. Code\tAmount\t\tSender\t\tPhone\t\tReceiver\tPhone");
	printf("\n\t\t-------------------------------------------------------------------------------------------\n");
	while (fgets(line, sizeof(line), fp)) {
		count++;
		printf("\t\t%s", line); 
	}
	if(!count){
		printf("\t\t\t\t\t\tNO UNCLAIMED TRANSACTIONS\n");
	}
	printf("\t\t-------------------------------------------------------------------------------------------\n");
	fclose(fp);
	
	printf("\n\n\t| =============================================== UNCLAIMED =============================================== |\n\n");
	menu();
}

void _login(int *log){
	system("cls");
	fordelay();
	printf("\n\n\t| ================================================= LOGIN ================================================= |\n\n");
	
	FILE *accounts;
	accounts = fopen("accounts.txt","r");
	
	char ch;	
	
	printf("\t\t\t\tEmail: ");
	ch=getchar();
	gets(login.email);
	printf("\t\t\t\tPassword: ");
	gets(login.password);
	
	while(fscanf(accounts,"%s\t%s",&check.email,&check.password) != EOF){
		if((strcmp(check.email,login.email)==0) && (strcmp(check.password,login.password)==0)){
			system("cls");
			printf("\n\t\t\t\t#################### LOGIN SUCCESSFUL ####################");
			fordelay();
			*log = 1;
		}
	}
	
	strcpy(loggedEmail,login.email);
	fclose(accounts);
}

void _signup(int *sgd){
	fordelay();
	printf("\n\n\t| ================================================= SIGN UP ================================================= |\n\n");
	
	FILE *accounts;	
	char line[500],ch,*token;
	int exist=0;
	
	printf("\t\t\t\tPlease enter the required information \n");
	
	enter_acc:
	accounts = fopen("accounts.txt","a+");
	printf("\t\t\t\tEnter your e-mail: ");
	ch = getchar();
	gets(signup.email);	
	while (fgets(line, sizeof(line), accounts)) {
		token = strtok(line,"\t");	
		if(strcmp(token,signup.email) == 0){		
			printf("\n\t\t\t\t!!!!!!!!!! Account already existed !!!!!!!!!!\n");
			exist = 1;
		}
	}
	
	if(!exist){
		printf("\t\t\t\tEnter your password: ");
		gets(signup.password);	
		*sgd = 1;
	}
	
	fprintf(accounts,"%s\t%s\n",signup.email,signup.password);
	strcpy(loggedEmail,login.email);
	fclose(accounts);
}

void main_exit(){
	system("cls");
	fordelay();
	printf("\n\n\n\t| ================================= THANK YOU FOR USING MONEY TRANSFER SYSTEM ================================= |\n");
	printf("\t\t\t\t\t\t    [Developed by Kurt Timajo]");
	exit(0);
}

void edit_acc(char _current_email[30], char _new_email[30], char _new_password[30]){
	FILE *acc,*temp;
	char line[500],temp_line[50],*token;
	
	acc = fopen("accounts.txt","r");
	temp = fopen("temp.txt","a+");
	
	while(fgets(line, sizeof(line), acc)){
		strcpy(temp_line,line);
		token = strtok(line,"\t");
		if(strcmp(token,_current_email) != 0){
			fprintf(temp,"%s",temp_line);
		}
	}		
	fprintf(temp,"%s\t%s\n",_new_email,_new_password);
	fclose(acc);
	fclose(temp);
	
	acc = fopen("accounts.txt","w");
	temp = fopen("temp.txt","r");
	while(fgets(line, sizeof(line), temp)){
		fprintf(acc,"%s",line);
	}
	fordelay();
	printf("\n\t\t\t\t#################### ACCOUNT EDITED SUCCESSFULLY ####################");
	
	fclose(acc);
	fclose(temp);	
	remove("temp.txt");
	
	menu();
}

void delete_acc(char _email[30]){
	FILE *acc,*temp;
	char line[500],temp_line[50],*token;
	
	acc = fopen("accounts.txt","r");
	temp = fopen("temp.txt","a+");
	
	while(fgets(line, sizeof(line), acc)){
		strcpy(temp_line,line);
		token = strtok(line,"\t");
		if(strcmp(token,_email) != 0){
			fprintf(temp,"%s",temp_line);
		}
	}
	
	fclose(acc);
	fclose(temp);
	
	acc = fopen("accounts.txt","w");
	temp = fopen("temp.txt","r");
	while(fgets(line, sizeof(line), temp)){
		fprintf(acc,"%s",line);
	}
	fordelay();
	printf("\n\t\t\t#################### ACCOUNT DELETED SUCCESSFULLY ####################");
	fordelay();
	
	fclose(acc);
	fclose(temp);
	remove("temp.txt");
	main();
}

int emailExists(char _email[30]){
	FILE *acc;
	int exist=0;
	char *token,line[500];
	acc = fopen("accounts.txt","r");
	while(fgets(line, sizeof(line), acc)){
		token = strtok(line,"\t");
		if(strcmp(token,_email) == 0){
			exist = 1;
		}
	}
	fclose(acc);
	return exist;
}

void acc_settings(){
	fordelay();
	printf("\n\n\t| ============================================ ACCOUNT SETTINGS =========================================== |\n\n");
	int task;
	char ch,cur_email[30],new_email[30],new_password[15];
	
	choose_task:
	printf("\n\n\t\t\t\t1. EDIT ACCOUNT\n");
	printf("\n\t\t\t\t2. DELETE ACCOUNT\n");
	printf("\n\t\t\t\t0.  MENU\n\n\t\t\t\t>> ");
	scanf("%d",&task);
	
	if(task == 1){
		fordelay();
		enter_new:
		printf("\n\n\t\t\t#################### EDIT YOUR ACCOUNT ####################");
		
		printf("\n\n\t\t\t\tEnter your new email: ");
		ch = getchar();
		gets(new_email);
		printf("\n\t\t\t\tEnter your new password: ");
		gets(new_password);
		if(emailExists(new_email)){
			printf("\n\t\t\t\t!!!!!!!!!! Email is existing already. !!!!!!!!!!\n");
			fordelay();
			goto enter_new;
		}
		else{
			edit_acc(loggedEmail,new_email,new_password);
		}		
	}
	else if(task == 2){
		fordelay();
		printf("\n\n\t\t\t#################### DELETE YOUR ACCOUNT ####################");
		delete_acc(loggedEmail);
	}
	else if(task == 0){
		fordelay();
		menu();
	} 
	else{
		system("cls");
		printf("\t\t\t\t!!!!!!!!!!!! INVALID SELECTION !!!!!!!!!!!!");
		goto choose_task;
	}
	
}

int landing(){
	int task;
	printf("\n\t\t\t\t1. Login\n\n");
	printf("\t\t\t\t2. Sign Up\n\n");
	printf("\t\t\t\t0. Exit\n\n\t\t\t\t>> ");
	scanf("%d",&task);
	return task;
}

void menu(){
	int ch;
	choose_task:
	printf("\n\n\t\t\t\t\t*************** M E N U ***************\n");
	printf("\n\t\t\t\t\t1. SEND MONEY");
	printf("\n\t\t\t\t\t2. CLAIM MONEY");
	printf("\n\t\t\t\t\t3. VIEW ALL TRANSACTIONS");
	printf("\n\t\t\t\t\t4. VIEW CLAIMED");
	printf("\n\t\t\t\t\t5. VIEW UNCLAIMED");
	printf("\n\t\t\t\t\t6. ACCOUNT SETTINGS");
	printf("\n\t\t\t\t\t0. LOGOUT\n\n\t\t\t\t\t>> ");
	scanf("%d",&ch);
	switch(ch){
		case 1:
			sendmoney();
			break;
		case 2:
			claim();
			break;
		case 3:
			view_all();
			break;
		case 4:
			view_claimed();
			break;
		case 5:
			view_unclaimed();
			break;
		case 6:
			acc_settings();
			break;
		case 0:
			system("cls");
			printf("\n\t\t\t\t#################### LOGGING OUT ####################");
			fordelay();
			main();
			break;
		default:
			system("cls");
			printf("\t\t!!!!!!!!!!!! INVALID SELECTION !!!!!!!!!!!!");
			goto choose_task;
	}
}

void main(){
	int task,logged=0,signed_up=0;
	printf("\n\t| ================================== WELCOME TO MONEY TRANSFER SYSTEM ================================== |\n");
	
	entry:
	task = landing();	
	if(task == 1){
		_login(&logged);
		if(logged){
			system("cls");
			printf("\n\t| ================================== WELCOME TO MONEY TRANSFER SYSTEM ================================== |\n");
			menu();
		} else{
			system("cls");
			printf("\n\t\t#################### LOGIN FAILED ####################\n");
			printf("\t\tMake sure you entered the right email and password.\n");
			goto entry;
		}
	}
	else if(task==2){
		_signup(&signed_up);
		if(signed_up){
			fordelay();
			printf("\n\t| ================================== WELCOME TO MONEY TRANSFER SYSTEM ================================== |\n");
			menu();
		} else{
			system("cls");
			printf("\n\t\t#################### SIGNUP FAILED ####################\n");
			fordelay();
			goto entry;
		}
	}
	else if(task==0){
		main_exit();
	}
	else{
		system("cls");
		printf("\n\t!!!!!!!!!!!! INVALID SELECTION !!!!!!!!!!!!\n\n");
		goto entry;
	}
}