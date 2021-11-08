#include <bits/stdc++.h>

using namespace std;

struct table{
    vector<string> data;
    vector<int> address;
    int ptr;
}typedef table;

void readFile(string filepath,vector<vector<string>> &inputData);

void storetable(table Table,string file_name);

int update_literal(table &lit_table,int ptr,int start);

void printliteral(table lit_table,int start,int end)
{
    for(int i = start; i < end ; i++)
    {
        cout  << lit_table.address[i] <<" )\t\t\t" <<lit_table.data[i] ;
        if(i != end-1)
            cout <<"\n";
    }
}

int update_literal(table &lit_table,int ptr,int start)
{
    for (int i = start; i < lit_table.data.size(); i++)
    {
        lit_table.address[i] = ptr++;
    }

    printliteral(lit_table,start,lit_table.data.size());

    if(lit_table.data.size()-1 - start > 0)
        return ptr;
    else
        return ptr;
}

int main()
{

    string filepath = "input.txt";
    vector<vector<string>> inputData;
    readFile(filepath,inputData);

    //loc_ptr
    int start_ptr = inputData[0].size() == 1 ? 0 : stoi(inputData[0][1]) ;
    cout<<start_ptr;
    //START -> 00
    map<string,pair<string,string>> instr = { { "STOP" ,{"IS","00"} } , { "ADD" ,{"IS","1"} } , { "SUB" ,{"IS","2"} } , { "MULT" ,{"IS","3"} } , { "MOVER" ,{"IS","4"} } , { "MOVEM" ,{"IS","5"} } , { "COMP" ,{"IS","6"} } , { "BC" ,{"IS","7"} } , { "DIV" ,{"IS","8"} } , { "READ" ,{"IS","9"} } , { "PRINT" ,{"IS","10"} } ,  { "DC" ,{"DL","1"} }, { "DS" ,{"DL","2"} } ,{ "START" ,{"AD","1"} },{ "END" ,{"AD","2"} } , { "ORIGIN" ,{"AD","3"} } , { "EQU" ,{"AD","4"} } ,{ "LTORG" ,{"AD","5"} } };
    // Remaining LTORG , ORIGIN , EQU , DS , STOP

    //OPTAB

    map<string,char> reg = {{"AREG",'1'},{"BREG",'2'},{"CREG",'3'},{"DREG",'4'}};
    map<string,char> branch = {{"LT",'1'},{"LE",'2'},{"EQ",'3'} , {"GT",'4'} , {"GE",'5'} , {"ANY",'6'}};

    table literal,symbol,tii;
    literal.ptr = 0 ; symbol.ptr = 0 ; tii.ptr = 0 ;

    int pool_ptr = 1 ;
    vector<int> pool_tab;
    pool_tab.push_back(pool_ptr);

    bool error_found = false ;
    freopen ("output.txt","w",stdout);

    // vector<vector<

    for(int i = 0 ; i < inputData.size(); i++)
    {
        for(int j = 0 ; j < inputData[i].size(); j++)
        {
            string s = inputData[i][j];

            if(instr.find(s) != instr.end())
            {
                if(instr[s].first != "AD")
                {
                    cout<<start_ptr<<" )\t"<<"( "<<instr[s].second<<" ) ";
                    start_ptr++;
                }
                else
                {

                    if(s != "START")
                        start_ptr++;

                }

                //Processing For SPECIAL Instruction
                if(s == "BC")
                {
                    string condition = inputData[i][++j];
                    cout<<"( "<<branch[condition]<<" ) ";
                }
                if(s == "ORIGIN")
                {
                    string addr = inputData[i][++j];
                    if((addr.find_first_not_of( "0123456789" ) == addr.npos))
                    {
                        start_ptr = stoi(s);
                    }
                    else
                    {
                        int split = addr.find('+');
                        string start = addr.substr(0,split) ,value = addr.substr(split+1);
                        auto it = find(symbol.data.begin(),symbol.data.end(),start);
                        int new_address = symbol.address[it - symbol.data.begin()] + stoi(value);
                        start_ptr = new_address;
                    }
                }
                if(s == "LTORG")
                {
                    // start_ptr++;
                    start_ptr = update_literal(literal,start_ptr-1,pool_ptr-1);
                    pool_ptr = literal.address.size()+1;
                    pool_tab.push_back(pool_ptr);
                }
                if(s == "EQU")
                {
                        string label = inputData[i][j-1], value = inputData[i][++j];
                        auto it = find(symbol.data.begin(),symbol.data.end(),value);
                        symbol.address[it - symbol.data.begin()] = symbol.address[find(symbol.data.begin(),symbol.data.end(),label)- symbol.data.begin()];
                }
                if(s == "DS")
                {
                    int size = stoi(inputData[i][j+1]);
                    start_ptr += size-1;
                }

            }
            else if(reg.find(s) != reg.end())
            {
                cout<<"( " <<reg[s]<<" ) ";
            }
            //Checking if string is a constant
            else if((s.find_first_not_of( "0123456789" ) == s.npos))
            {
                //Only checks for positive integers.
                cout<<"( C , "<<s<<" ) ";
            }
            //Check if literal
            else if(s.find('=') != s.npos)
            {
                tii.data.push_back(s);
                tii.address.push_back(start_ptr-1);
                tii.ptr++;

                int ind = -1;
                for(int i = pool_ptr-1 ; i < literal.data.size(); i++)
                {
                    if(literal.data[i] == s)
                    {
                        ind = i ;
                        break;
                    }
                }

                //  When literal is found
                if(ind != -1)
                {
                    // int ind = find(literal.data.begin(),literal.data.end(),s) - literal.data.begin();
                    // cout << " ( L , "<< literal.address[ind] <<" ) ";
                }
                else
                {
                    literal.data.push_back(s);
                    literal.address.push_back(++(literal.ptr));
                }

            }
            else
            {

                //Symbol is at front and address is used
                if(j == 0)
                {
                    auto it = find(symbol.data.begin(),symbol.data.end(),s);
                    if(it == symbol.data.end())
                    {
                        symbol.data.push_back(s);
                        symbol.address.push_back(start_ptr);
                        symbol.ptr++;
                    }
                    else
                        symbol.address[it - symbol.data.begin()] = start_ptr;
                }
                else
                {

                    tii.data.push_back(s);
                    tii.address.push_back(start_ptr-1);
                    tii.ptr++;

                    auto it = find(symbol.data.begin(),symbol.data.end(),s);
                    if(it == symbol.data.end())
                    {
                        symbol.data.push_back(s);
                        symbol.address.push_back(++(symbol.ptr));
                    }

                }
            }
        }
        cout<<"\n";
    }

    if(!error_found)
    {
        start_ptr = update_literal(literal,start_ptr,pool_ptr);


        storetable(literal,"literal.txt");
        storetable(symbol,"symbol.txt");
        storetable(tii,"tii.txt");

        freopen("pool.txt","w",stdout);
        cout << "Pool tab : ";

        for(int i : pool_tab)
        {
            cout << i << " ";
        }
    }
    return 0;

}

void readFile(string filepath,vector<vector<string>> &inputData)
{
    ifstream in(filepath);
    string line;

    while(getline(in,line))
    {
        string temp;
        vector<string> instr;
        stringstream ss(line);
        while (ss >> temp)
        {
            if(temp == ",")continue;
            instr.push_back(temp);
        }
        inputData.push_back(instr);
        // in>>inputData[num++];
    }

    in.close();

}

void storetable(table Table,string file_name)
{
    freopen (&file_name[0],"w",stdout);
    for(int i = 0 ; i < Table.data.size(); i++)
    {
        cout << i+1 << "\t" << Table.data[i] <<"\t" << Table.address[i]<< "\n";
    }
}

