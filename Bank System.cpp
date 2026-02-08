#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

const string ClientsFileName = "ClientsData.txt";

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};


vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable
    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
    sWord = S1.substr(0, pos); // store the word
    if (sWord != "")
    {
    vString.push_back(sWord);
    }
    S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
    vString.push_back(S1); // it adds last word of the string.
    }
    return vString;
}

sClient ConvertLineToData(string clientRecord, string seperator = "#//#"){

    sClient Client;

    vector<string> vClientData;
    vClientData = SplitString(clientRecord, seperator);
    
    if (vClientData.size() < 5)
        return Client;

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;
}

vector <sClient> LoadCleintsDataFromFile(){
    vector <sClient> vClients;
    fstream MyFile;
    
    MyFile.open(ClientsFileName, ios::in);

    if(MyFile.is_open()){
        string Line;
        sClient Client;
        while (getline(MyFile, Line)){
            Client = ConvertLineToData(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }

    return vClients;
}

//? ==========================================  Show  =====================================================

void PrintClientRecord(sClient Client){
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector <sClient> vClientsData){
    cout << "\n\t\t\t\t\tClient List (" << vClientsData.size() << ") Client(s).";
    cout <<
    "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
    "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClientsData)
    {
    PrintClientRecord(Client);
    cout << endl;
    }
    cout <<
    "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

//? ==========================================  Add  =====================================================

bool AccountNumberExist(string AccountNumber, vector <sClient> ClientsData){
    for(int i = 0; i < ClientsData.size(); i++){
        if (AccountNumber == ClientsData[i].AccountNumber){
            return false;
        }
    }
    
    return true;
}

sClient ReadClientData(vector <sClient>& ClientsData){
    
    sClient Client1;
    
    cout << "Enter Account Number: ";
    cin >> Client1.AccountNumber;
    
    while(!AccountNumberExist(Client1.AccountNumber, ClientsData)){
        cout << "Sorry, this Account Number is Exist, Please enter another Account Number\n\n";
        cout << "Enter Account Number: ";
        cin >> Client1.AccountNumber;
    }   
    cout << "Enter Pincode: ";
    cin >> Client1.PinCode;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, Client1.Name);
    cout << "Enter Phone: ";
    cin >> Client1.Phone;
    cout << "Enter Account Balance: ";
    cin >> Client1.AccountBalance;
    cout << "\nClient Added succesfully\n";
    
    return Client1;
}

string ConvertDataToLineRecord(sClient Client1, string separator){
    
    string stClientRecord = "";
    stClientRecord += Client1.AccountNumber + separator;
    stClientRecord += Client1.PinCode + separator;
    stClientRecord += Client1.Name + separator;
    stClientRecord += Client1.Phone + separator;
    stClientRecord += to_string(Client1.AccountBalance);
    
    return stClientRecord;
}

void AddClientToFile(string ClientData){
    fstream clientsData;
    
    clientsData.open("ClientsData.txt", ios::out | ios::app);
    
    if(clientsData.is_open()){
        clientsData << ClientData << endl;

        clientsData.close();
    }
}

void AddNewClient(sClient Client){
    
    string lineRecord =  ConvertDataToLineRecord(Client, "#//#");
    AddClientToFile(lineRecord);
    
    cout << "Client Added succesfully\n";
}

//? ===========================================  Delete  ====================================================

string ConvertRecordToLine(sClient Client, string Seperator ="#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}

bool FindClientByAccountNumber(string& AccountNumber, vector<sClient>& vClients, sClient& Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber,vector <sClient>& vClients)
{
    for (sClient& C : vClients)
    {
    if (C.AccountNumber == AccountNumber)
    {
    C.MarkForDelete = true;
    return true;
    }
    }
    return false;
}

void SaveCleintsDataToFile(string FileName, vector<sClient>& vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine;
    if (MyFile.is_open())
    {
    for (sClient C : vClients)
    {
    if (C.MarkForDelete == false)
    {
    //we only write records that are not marked for delete.
    DataLine = ConvertRecordToLine(C);
    MyFile << DataLine << endl;
    }
    }
    MyFile.close();
    }
}

bool DeleteClientByAccountNumber(string AccountName, vector<sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountName, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountName,
            vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
    cout << "\nClient with Account Number (" << AccountName<< ") is Not Found!";
    }

return false;

}

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

//? ===========================================  Update Client  ====================================================

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

//? ===========================================  Find Client  ====================================================

sClient ClientExist(vector <sClient> vClientsData, string AccountNumber){

    for(sClient client: vClientsData){
        if(client.AccountNumber == AccountNumber)
            return client;
        }
        
    return sClient{};
}

void PrintClient(sClient Client)
{
    cout << "\n\nThe following is "<< Client.Name << " Info:\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}

//? ========================================================== Bank Options ==========================================================

void ListClients(vector<sClient>& vClients){
    PrintAllClientsData(vClients);
} 

void AddNewClientM(vector<sClient>& vClients){
    sClient Client = ReadClientData(vClients);
    vClients.push_back(Client);
    SaveCleintsDataToFile(ClientsFileName, vClients);
} 

void DeleteClient(vector<sClient>& vClients){
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
} 

void UpdateClient(vector<sClient>& vClients){
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
} 

void FindClient(vector<sClient>& vClients){
    string accountNumber;

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    sClient client = ClientExist(vClients, accountNumber);

    if (client.AccountNumber == "")
        cout << "Client not found\n";
    else
        PrintClient(client);

} 

//? ==================================================================================================================================
enum enMainMenueOptions {eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5,  eTransactionMenu = 6, eExit = 7};
enum enTransactionsMenueOptions {eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenu = 4};
void ClearScreen() {system("cls");}

//! =======================================================  Transactions  ===========================================================

void AddMoneyToClient(vector<sClient>& vClients, string AccountNumber, int money){
   
    sClient Client;
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
            for (sClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C.AccountBalance += money;
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nDeposit done Successfully.";
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }    
}

void WithdrawMoney(vector<sClient>& vClients, string AccountNumber, int money){
   
    sClient Client;
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
            for (sClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C.AccountBalance -= money;
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nWithdrawal done Successfully.";
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }    
}

void Deposit(vector<sClient>& vClients){

    string AccountNumber = ReadClientAccountNumber();
    
    while(AccountNumberExist(AccountNumber, vClients)){
        cout << "Sorry, Account Number Doesn't Exist \n";
        AccountNumber = ReadClientAccountNumber();
        AccountNumberExist(AccountNumber, vClients);
    }

    int depositeAmount;
    cout << "Please enter deposite amount: ";
    cin >> depositeAmount;

    AddMoneyToClient(vClients, AccountNumber, depositeAmount);
}

void Withdraw(vector<sClient>& vClients){

    string AccountNumber = ReadClientAccountNumber();
    
    while(AccountNumberExist(AccountNumber, vClients)){
        cout << "Sorry, Account Number Doesn't Exist \n";
        AccountNumber = ReadClientAccountNumber();
        AccountNumberExist(AccountNumber, vClients);
    }

    int WithdrawalAmount;
    cout << "Please enter Withdrawal amount: ";
    cin >> WithdrawalAmount;

    
    while(WithdrawalAmount > ClientExist(vClients, AccountNumber).AccountBalance){
    cout << "Amount exceeds balance! Max: " << ClientExist(vClients, AccountNumber).AccountBalance << endl;
    cout << "Enter amount: ";
    cin >> WithdrawalAmount;
    }

    WithdrawMoney(vClients, AccountNumber, WithdrawalAmount);
}

void PrintClientsBalances(const vector<sClient>& vClients)
{
    cout << "\n\t\tClients Balances List\n";
    cout << "------------------------------------------------------------\n";
    cout << "| " << left << setw(15) << "Account Number"
         << "| " << left << setw(30) << "Client Name"
         << "| " << left << setw(12) << "Balance" << endl;
    cout << "------------------------------------------------------------\n";

    for (const sClient& C : vClients)
    {
        cout << "| " << left << setw(15) << C.AccountNumber
             << "| " << left << setw(30) << C.Name
             << "| " << left << setw(12) << C.AccountBalance << endl;
    }

    cout << "------------------------------------------------------------\n";
}

long long CalculateTotalBalances(const vector<sClient>& vClients)
{
    long long TotalBalances = 0;

    for (const sClient& C : vClients)
    {
        TotalBalances += C.AccountBalance;
    }

    return TotalBalances;
}

void ShowTotalBalances(const vector<sClient>& vClients)
{
    ClearScreen();

    PrintClientsBalances(vClients);

    double Total = CalculateTotalBalances(vClients);

    cout << "\n\t\tTotal Balances = " << Total << endl;
}


void DisplayTransactionsMenu(){

    ClearScreen();
    cout << "------------------------------- EMA Bank  -------------------------------\n";
    cout << "=========================================================================\n";
    cout << "                         Transactions Menu Screen                        \n";
    cout << "=========================================================================\n";
    cout << "[1] Deposit.\n";
    cout << "[2] Withdraw.\n";
    cout << "[3] Total Balances.\n";
    cout << "[4] Main Menu.\n";
    cout << "=========================================================================\n";
    
}

short TakeChoiceFromUser(){
    
    DisplayTransactionsMenu();
    
    short choice;

    cout << "Choose what do you want to do? [1 to 6]: ";
    cin >> choice;

    return choice;
}



//! =======================================================  Main Menu  ==============================================================

short MainMenu(){
    ClearScreen();
    
    short int UserChoice;

    cout << "-------------------------  Welcome to EMA Bank  -------------------------\n";
    cout << "=========================================================================\n";
    cout << "                             Main Menu Screen                            \n";
    cout << "=========================================================================\n";
    cout << "[1] Show Clients List.\n";
    cout << "[2] Add New Client.\n";
    cout << "[3] Delete Client.\n";
    cout << "[4] Update Client Info.\n";
    cout << "[5] Find Client.\n";
    cout << "[6] Transactions.\n";
    cout << "[7] Exit.\n";
    cout << "=========================================================================\n";
    
    cout << "Choose what do you want to do? [1 to 7]: ";
    cin >> UserChoice;
    return UserChoice;
}

void TransactionMenue(vector<sClient>& vClients);

void PerformMainMenue(vector<sClient>& vClients)
{
    short UserChoice;

    UserChoice = MainMenu();

    switch (UserChoice)
    {
    case enMainMenueOptions::eListClients:
        ListClients(vClients);
        break;

    case enMainMenueOptions::eAddNewClient:
        AddNewClientM(vClients);
        break;

    case enMainMenueOptions::eDeleteClient:
        DeleteClient(vClients);
        break;

    case enMainMenueOptions::eUpdateClient:
        UpdateClient(vClients);
        break;

    case enMainMenueOptions::eFindClient:
        FindClient(vClients);
        break;

    case enMainMenueOptions::eTransactionMenu:
        TransactionMenue(vClients);
        break;
    case enMainMenueOptions::eExit:
        cout << "\nThank you for using EMA Bank\n";
        break;

    default:
        cout << "Invalid choice!\n";
        break;
    }
}

void TransactionMenue(vector<sClient>& vClients)
{
    short UserChoice;

    UserChoice = TakeChoiceFromUser();

    switch (UserChoice)
    {
    case enTransactionsMenueOptions::eDeposit:
        Deposit(vClients);
        break;

    case enTransactionsMenueOptions::eWithdraw:
        Withdraw(vClients);
        break;

    case enTransactionsMenueOptions::eTotalBalances:
    ShowTotalBalances(vClients);    
    break;

    case enTransactionsMenueOptions::eMainMenu:
        PerformMainMenue(vClients);
        break;

    default:
        cout << "Invalid choice!\n";
        break;
    }
}

void Start(vector<sClient>& vClients){

    char AnotherOperation;
    do
    {
        ClearScreen();
        PerformMainMenue(vClients);
        
        cout << "\nDo you want to make another operation? (y/n): ";
        cin >> AnotherOperation;
        
    } while (AnotherOperation == 'y' || AnotherOperation == 'Y');
    
    ClearScreen();
    cout << "\nThank you for using EMA Bank\n";
}



int main()
{
    vector<sClient> vClients = LoadCleintsDataFromFile();
    Start(vClients);
    
    system("pause>0");
    system("pause"); 
    return 0;
}