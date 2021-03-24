#include "stdafx.h"
#include <stdlib.h>
#include <string.h>

int id = 10000000;

typedef struct{
	char accountType[30];
	//IBANа се състои от 22 слимвола и нула за край
	char IBAN[23];
	long double moneyAmount;
}AccountInfo;


class ClientBank {
private:
	char firstName[21];
	char lastName[21];
	int clientID;
	int numberOfAccounts;
	AccountInfo accountsInfo[6];
public:
	ClientBank(void);
	ClientBank(char *pfirstName, char *plastName, ClientBank &client);
	ClientBank(ClientBank &clientCopy);
	int addAccount();
	int removeAccount();
	AccountInfo* find(char *pIBAN);
	int addMoney(long double amount);
	int withdrawMoney(long double amount);
	long double sumMoney();
	void printData();
	int clientinfo();
	int returnID();
	int retrunNumAccounts();
};
ClientBank::ClientBank(void){
	firstName[0] = '\0';
	lastName[0] = '\0';
	clientID = 0;
	numberOfAccounts = 0;
	for (int i = 0; i < 6; i++){
		accountsInfo[i].accountType[0] = '\0';
		accountsInfo[i].IBAN[0] = '\0';
		accountsInfo[i].moneyAmount = 0;
	}
}
ClientBank::ClientBank(char *pfirstName, char *plastName, ClientBank &client){
	int i;
	for (i = 0; pfirstName[i] != '\0'; i++){
		client.firstName[i] = pfirstName[i];
	}client.firstName[i] = '\0';
	for (i = 0; plastName[i] != '\0'; i++){
		client.lastName[i] = plastName[i];
	}client.lastName[i] = '\0';
	client.clientID = id;
}
ClientBank::ClientBank(ClientBank &clientCopy){
	strcpy(firstName, clientCopy.firstName);
	strcpy(lastName, clientCopy.lastName);
	clientID = clientCopy.clientID;
	numberOfAccounts = clientCopy.numberOfAccounts;
	for (int i = 0; i < 6; i++){
		accountsInfo[i] = clientCopy.accountsInfo[i];
	}
}

int ClientBank::addAccount(){
	//Съзадавам променливата index за да следя текущия акаунт на клиента
	//Променливата country е за въвеждане на държавата
	//tempClientID е за да използвам ID на клиента за създаване на IBAN
	//tempAccount е за да въведе потребителя желания от него акаунт и 
	//също за един от символите на Айбана
	//flag ми служи като булева променлива
	//и променлива за записване на парите
	int index, country, tempClientID = clientID, tempAccount, flag = 1;
	long double money;
	if (accountsInfo[4].accountType[0]){
		return 0; //Не може повече акаунти
	}
	//Увеличавам индекса докато не открия свободно място
	//за нов акаунт
	for (index = 0; accountsInfo[index].accountType[0]; index++);
repeat:
	fflush(stdin);
	printf("\n1. Current Account\n2. Savings Account\n3. Recurring Deposit Account\n4. Fixed Deposit Accoun\n5. Checking account");
	printf("\nEnter the number of the account type you want to add : ");
	scanf("%d", &tempAccount);
	switch (tempAccount)
	{
	case 1:
		strcpy(accountsInfo[index].accountType, "Current\0");
		break;
	case 2:
		strcpy(accountsInfo[index].accountType, "Savings\0");
		break;
	case 3:
		strcpy(accountsInfo[index].accountType, "RecurringDeposit\0");
		break;
	case 4:
		strcpy(accountsInfo[index].accountType, "FixedDeposit\0");
		break;
	case 5:
		strcpy(accountsInfo[index].accountType, "Checking\0");
		break;
	default:
		//Продължи записването докато потребителя не въведе правилна стойност
		goto repeat;
	}
	//Правим проверка дали потребителя вече има такъв акаунт
	for (int i = 0; i < index; i++){
		flag = strcmp(accountsInfo[index].accountType, accountsInfo[i].accountType);
		if (!flag){ printf("\nYou can't have two accounts of the same type!"); goto repeat; }
	}
	do{
		printf("\nHow much money would you like to deposit : ");
		scanf("%Lf", &money);
	} while (money < 0);
	accountsInfo[index].moneyAmount += money;
repeat1:

	printf("\nAlbania 1\nAndorra 2\nAustria 3\nAzerbaijan 4\nBahrain 5\nBelarus 6\nBelgium 7\nBosnia and Herzegovina 8\nBrazil 9\nBulgaria 10\n");
	printf("\nThe last step is to enter the number of the country you're from : ");
	scanf("%d", &country);
	switch (country){
	case 1:
		accountsInfo[index].IBAN[0] = 'A';
		accountsInfo[index].IBAN[1] = 'L';
		break;
	case 2:
		accountsInfo[index].IBAN[0] = 'A';
		accountsInfo[index].IBAN[1] = 'D';
		break;
	case 3:
		accountsInfo[index].IBAN[0] = 'A';
		accountsInfo[index].IBAN[1] = 'T';
		break;
	case 4:
		accountsInfo[index].IBAN[0] = 'A';
		accountsInfo[index].IBAN[1] = 'Z';
		break;
	case 5:
		accountsInfo[index].IBAN[0] = 'B';
		accountsInfo[index].IBAN[1] = 'H';
		break;
	case 6:
		accountsInfo[index].IBAN[0] = 'B';
		accountsInfo[index].IBAN[1] = 'Y';
		break;
	case 7:
		accountsInfo[index].IBAN[0] = 'B';
		accountsInfo[index].IBAN[1] = 'E';
		break;
	case 8:
		accountsInfo[index].IBAN[0] = 'B';
		accountsInfo[index].IBAN[1] = 'A';
		break;
	case 9:
		accountsInfo[index].IBAN[0] = 'B';
		accountsInfo[index].IBAN[1] = 'R';
		break;
	case 10:
		accountsInfo[index].IBAN[0] = 'B';
		accountsInfo[index].IBAN[1] = 'G';
		break;
	default:
		goto repeat1;
	}
	//Следващите 11 числа ги поставям статични, защото те
	//указват банка, клон и т.н.
	//Тези числа са примерен IBAN
	strcpy(&accountsInfo[index].IBAN[2], "80BNBG96611");
	//Следващия символ е номера на типа акаунт за да сме сигурни, че
	//айбана няма да се повтаря за други акаунти
	accountsInfo[index].IBAN[13] = tempAccount + 48;
	//Следващите 8 числа взимаме от клиентския номер
	//и накрая слагам нула за край на стринга
	for (int i = 21; i > 13; i--){
		accountsInfo[index].IBAN[i] = ((tempClientID % 10) + 48);
		tempClientID /= 10;
	}accountsInfo[index].IBAN[22] = 0;
	printf("\nIBAN : %s", accountsInfo[index].IBAN);
	numberOfAccounts++;
	return 1;
}
int ClientBank::removeAccount(){
	char tempIBAN[100];
	AccountInfo *paccountsInfo;
	do{
		fflush(stdin);
		printf("\nEnter IBAN of the account you want to remove : ");
		gets(tempIBAN);
		if (strlen(tempIBAN) < 22) {
			printf("\nIBAN too short");
		}
		else if (strlen(tempIBAN) > 22) {
			printf("\nIBAN too long");
		}
		else {
			paccountsInfo = find(tempIBAN);
			if (paccountsInfo){
				break;
			}
			else return 0;
		}
	} while (1);
	//Ако парите в акаунта са мнус трябва да бъдат издължени
	//преди да се закрие акаунта
	if (paccountsInfo->moneyAmount < -0.01) return -1;
	//Акаунта трябва да е празен преди да се закрие
	else if (paccountsInfo->moneyAmount > 0.01) return 1;
	else {
		//Когато премахваме акаунта преместваме всички след него
		//с енда позиция 
		for (int i = 0; i < 5; i++){
			*(paccountsInfo + i) = *(paccountsInfo + (i + 1));
		}
		(paccountsInfo + 5)->accountType[0] = '\0';
		(paccountsInfo + 5)->IBAN[0] = '\0';
		numberOfAccounts--;
		return 2;
	}
}
AccountInfo* ClientBank::find(char *pIBAN){
	int i, flag = 1;
	//Сравнявам Айбаните до намиране на правилния
	//Ако не го откривам връщам NULL
	for (i = 0; i < 5; i++){
		flag = strcmp(accountsInfo[i].IBAN, pIBAN);
		if (!flag) return &accountsInfo[i];
	}return NULL;
}
int ClientBank::addMoney(long double amount){
	char tempIBAN[100];
	int numAttempts = 0;
	//Проверка ако сумата е отрицателно число или 0
	if (amount <= 0) return 0;
repeat:
	numAttempts++;
	fflush(stdin);
	//Ако надвишиш опитите се връщаш обратно в менюто
	if (numAttempts > 5){ fflush(stdin); printf("\nSorry couldn't find it\n"); getchar(); return -1; }
	do{
		printf("\nEnter IBAN : ");
		gets(tempIBAN);
	} while (!tempIBAN[0]);
	if (!find(tempIBAN)){ fflush(stdin); printf("\nInvalid IBAN\n"); getchar(); goto repeat; }
	//Ако всичко е точно добавяме парите в акаунта и връщаме 1
	find(tempIBAN)->moneyAmount += amount;
	return 1;
}
//Следващия метод е почти същия като затода за добавяне на пари
int ClientBank::withdrawMoney(long double amount){
	char tempIBAN[100];
	int numAttempts = 0;
	if (amount <= 0) return 0;
repeat:
	numAttempts++;
	fflush(stdin);
	if (numAttempts > 5){ fflush(stdin); printf("\nSorry couldn't find it\n"); getchar(); return -1; }
	do{
		printf("\nEnter IBAN : ");
		gets(tempIBAN);
	} while (!tempIBAN[0]);
	if (!find(tempIBAN)){ fflush(stdin); printf("\nInvalid IBAN\n"); getchar(); goto repeat; }
	//Ако парите в сметката са по-малко от парите които изтегляме се връща -2
	if (find(tempIBAN)->moneyAmount < amount) return -2;
	find(tempIBAN)->moneyAmount -= amount;
	return 1;
}
long double ClientBank::sumMoney(){
	//Променлива са сумата
	long double sum = 0;
	int i = 0;
	//Ако клиента няма акаунти метода връща 0
	if (!accountsInfo[0].accountType[0]) return 0;
	//Добавяме сумата от всеки акаунт в променливата sum и връщаме резултата
	while (accountsInfo[i].accountType[0]){ sum += accountsInfo[i].moneyAmount; i++; }
	return sum;
}
void ClientBank::printData(){
	//Ако клиента не е създаден няма как да отпечата инфо
	if (!clientID){ fflush(stdin); printf("\nClient does not exist!"); getchar(); return; }
	printf("\nFirst name : %s", firstName);
	printf("\nLast name : %s", lastName);
	if (!accountsInfo[0].accountType[0]){ printf("\nClient doesn't hava an account!"); return; }
	for (int i = 0; accountsInfo[i].accountType[0]; i++){
		printf("\nAccount type : %s", accountsInfo[i].accountType);
		printf("\nIBAN : %s", accountsInfo[i].IBAN);
		printf("\nBalance : %.2Lf", accountsInfo[i].moneyAmount);
	}
}
//Този метод е за да взема само IDто
int ClientBank::returnID(){
	return clientID;
}
//Този метод е за да изпиша лист от всички потребители
int ClientBank::clientinfo(){
	if (!firstName[0]) return 0;
	printf("\n%s %s\nClient ID : %d\n", firstName, lastName, clientID);
	return 1;
}
//Този метод връща броя на акаунтите
int ClientBank::retrunNumAccounts(){
	return numberOfAccounts;
}





//С помоща на този клас ще заделям динамично памет за клиентите
class Bank{
private:
	ClientBank *Table;
	int TableEnd;
public:
	Bank(int *numClients);
	~Bank();
	void Append(int *count);
	void Delete();
	void newAccount();
	void deleteAccount();
	void clientDetails();
	int findByID(ClientBank *clients);
	void viewList();
	void atmMenu();
};
Bank::Bank(int *numClients){
	//Създавам масива с още един елемент за край
	Table = new ClientBank[*numClients + 1];
	TableEnd = *numClients;
}
Bank::~Bank(){
	delete[]Table;
}
void Bank::Append(int *count){
	ClientBank *tempTable;
	char firstName[100], lastName[100];
	firstName[0] = 0;
	lastName[0] = 0;
	if (*count == TableEnd){
		tempTable = new ClientBank[(TableEnd * 2) + 1];
		for (int i = 0; i < TableEnd; i++){
			tempTable[i] = ClientBank(Table[i]);
		}
		TableEnd *= 2;
		delete[]Table;
		Table = tempTable;
	}
	do{
		fflush(stdin);
		system("cls");
		printf("Enter first name : ");
		gets(firstName);
	} while (!firstName[0] || strlen(firstName) > 20);
	do{
		fflush(stdin);
		system("cls");
		printf("Enter last name : ");
		gets(lastName);
	} while (!lastName[0] || strlen(lastName) > 20);
	id++;
	ClientBank(firstName, lastName, Table[*count]);
	fflush(stdin);
	printf("\nClient %s %s was successfully created!", firstName, lastName);
	printf("\nID : %d", id);
	getchar();
}
void Bank::Delete(void){
	int index = (int)findByID(Table);
	if (index == -1) return;
	//Проверявам дали клиента има незакрити акаунти
	if (Table[index].retrunNumAccounts()) { fflush(stdin); printf("\nFirst you must close all of your bank accounts!"); getchar(); return; }
	for (int i = index; i < TableEnd; i++){
		Table[i] = ClientBank(Table[i + 1]);
	}
	fflush(stdin);
	printf("\nClient was successfully removed!");
	getchar();
}
void Bank::newAccount(){
	int index = (int)findByID(Table);
	if (index == -1) return;
	if (Table[index].addAccount()){ fflush(stdin); printf("\nNew account successfully added!"); getchar(); return; }
	printf("\nCan't add more accounts!");
	system("pause");
}
void Bank::deleteAccount(){
	int index = (int)findByID(Table);
	if (index == -1) return;
	int returned = Table[index].removeAccount();
	if (returned == 0) { fflush(stdin); printf("\nWrong IBAN!"); getchar(); }
	else if (returned == -1) { fflush(stdin); printf("\nCan't remove account!\nYou owe the bank money!"); getchar(); }
	else if (returned == 1)  { fflush(stdin); printf("\nCan't remove account!\nAccount not empty!"); getchar(); }
	else { fflush(stdin); printf("\nAccount successfully removed!"); getchar(); }
}
void Bank::clientDetails(){
	int index = (int)findByID(Table);
	if (index == -1) return;
	Table[index].printData();
	fflush(stdin);
	printf("\nSum of all accounts : %.2Lf", Table[index].sumMoney());
	getchar();
}
//Правя този метод за откриване на индекса на клиент
int Bank::findByID(ClientBank *clients){
	int i, ID, flag = 1;
	do{
		system("cls");
		printf("Enter client ID : ");
		scanf("%d", &ID);
		//Проверявам дали idто е валидно т.е. дали се състой от 8 цифри
		if (ID >= 10000000 && ID <= 99999999) flag = 0;
		else{
			printf("\nInvalid ID!\nThe client ID must contain 8 numbers!\n");
			system("pause");
		}
	} while (flag);
	//Правя цикъл за намиране на клиента
	for (i = 0; i < 20; i++){
		//продължавам търсенето до намиране на правилния клиент
		if (clients[i].returnID() == ID) return i;
	}
	if (i == 20){
		//Използвам fflush(stdin) да изчистя стека и така да използвам getchar().
		//Така давам възможност да се прочете съобщението
		printf("\nID not found!\n");
		system("pause");
		return -1;
	}
	return -1;
}
void Bank::viewList(){
	for (int i = 0; Table[i].clientinfo(); i++);
	system("pause");
}
void Bank::atmMenu() {
	char buf[20];
	long double money;
	int choice, index = findByID(Table), returned;
	if (index == -1) return;
here:
	system("cls");
	printf("\n\n\t\t==========Welcome to ATM Feature==========\n\n");
	printf("\n\t\t----Please choose one of the options below----\n");
	printf("\n\t\t< 1 >  Check Balance\n");
	printf("\n\t\t< 2 >  Deposit\n");
	printf("\n\t\t< 3 >  Withdraw\n");
	printf("\n\t\t< 4 >  Exit\n\n");
	scanf("%d", &choice);
	fflush(stdin);
	switch (choice)
	{
	case 1:
		Table[index].printData();
		getchar();
		goto here;
		break;
	case 2:
		printf("\nHow much would you like to deposit : ");
		scanf("%Lf", &money);
		returned = Table[index].addMoney(money);
		if (returned == 0){ printf("\nCan't enter a negative amount!\n"); system("pause"); break; }
		else if (returned == 1){ printf("\nThe deposit has been successfully made!\n"); system("pause"); }
		break;
	case 3:
		printf("\nHow much would you like to withdraw : ");
		scanf("%Lf", &money);
		returned = Table[index].withdrawMoney(money);
		if (returned == 0){ printf("\nCan't enter a negative amount!\n"); system("pause"); break; }
		else if (returned == -2){ printf("\nInsufficient funds!\n"); system("pause"); }
		else if (returned == 1){ printf("\nYou have successfully withdrawn %.2Lf from account!\n", money); system("pause"); }
		break;
	case 4:
		printf("\nAre you shure you want to exit?\nType yes to exit\n");
		//Използвам масива buf за да питам потребителя дали иска да остане в това меню
		gets(buf);
		if (!strcmp("yes\0", buf)) return;
		break;
	default:
		break;
	}
	goto here;
}

//Прототип на фукцията
int menu(int &count, Bank *bank);



int main()
{
	//В count записвам първоначалния брой на клиентите на банката
	//, а в index запазвам позицията на текущия клиент. Използвам
	//index само за инициализирането на първите клиенти
	int count, index = 0;
	do{
		printf("How many clients would you like to create : ");
		scanf("%d", &count);
	} while (count <= 0);
	Bank bank(&count);
	for (int i = 0; i < count; i++){
		bank.Append(&index);
		index++;
	}
	while (menu(count, &bank));
	system("cls");
	printf("\n\n\n\n\t\t\tThank you for using our services :)");
	fflush(stdin);
	getchar();
	return 0;
}




int menu(int &count, Bank *bank) {
	int choice;
	system("cls");
	system("color 7");
	printf("\n\n\t\t\t       BANKING MANAGEMENT SYSTEM");
	printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\t\t[1] Create a new client\n\t\t[2] Delete an existing client\n\t\t[3] Add a new account\n\t\t[4] Remove existing account\n\t\t[5] Check client's details\n\t\t[6] View client's list\n\t\t[7] ATM Feature\n\t\t[8] Exit\n\n\n\t\t Enter your choice:");
	scanf("%d", &choice);

	system("cls");
	switch (choice)
	{
	case 1:
		bank->Append(&count);
		count++;
		return 1;
	case 2:bank->Delete();
		count--;
		return 1;
	case 3:bank->newAccount();
		return 1;
	case 4:bank->deleteAccount();
		return 1;
	case 5:bank->clientDetails();
		return 1;
	case 6:bank->viewList();
		return 1;
	case 7:bank->atmMenu();
		return 1;
	case 8:
		return 0;
	default:
		return 1;
	}
	return 1;
}