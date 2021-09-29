#include <bits/stdc++.h>

using namespace std;


struct table{
    vector<string> data;
    vector<int> address;
    int ptr;
}typedef table;

void readFile(string filepath,vector<vector<string>> &inputData);
void storetable(table Table,string file_name);

int main()
{

    string filepath = "input.txt";
    vector<vector<string>> inputData;
    readFile(filepath,inputData);

    int start_ptr = stoi(inputData[0][1]) ;     
    cout<<start_ptr;

    // vector<pair<string,pair<string,string>>> instr = { { "MOVER" ,{"IS","4"} },{ "ADD" ,{"IS","3"} },{ "DC" ,{"DL","1"} },{ "START" ,{"AD","1"} },{ "END" ,{"AD","2"} } };//,"ADD","MOVER"};
    map<string,pair<string,string>> instr = { { "MOVER" ,{"IS","4"} },{ "ADD" ,{"IS","3"} },{ "DC" ,{"DL","1"} },{ "START" ,{"AD","1"} },{ "END" ,{"AD","2"} } };//,"ADD","MOVER"};
    map<string,char> reg = {{"AREG",'1'},{"BREG",'2'},{"CREG",'3'},{"DREG",'4'}};
    // cout<<" "<<reg["AREG"];
    // vector<pair<string,int>> literal;
    // vector<pair<string,int>> symbol;
    table literal,symbol;
    literal.ptr = 0 ; symbol.ptr = 0 ;

    // int lit_ptr = 0 , sym_ptr = 0  ; 

    freopen ("output.txt","w",stdout);
    for(int i = 0 ; i < inputData.size(); i++)
    {
        for(int j = 0 ; j < inputData[i].size(); j++)
        {
            string s = inputData[i][j];

            if(instr.find(s) != instr.end())
            {
                if(instr[s].first != "AD")
                {
                    cout<<start_ptr<<") "<<"( "<<instr[s].first<<" , " <<instr[s].second<<" ) ";
                    start_ptr++;
                }
                else
                    cout<<"( "<<instr[s].first<<" , " <<instr[s].second<<" ) ";
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
                literal.data.push_back(s);
                literal.address.push_back(++(literal.ptr));
                cout << " ( L , "<< literal.ptr <<" ) ";   
            }
            else
            {
                //Symbol is at front and address is used 
                if(j == 0)
                {
                    auto it = find(symbol.data.begin(),symbol.data.end(),s);
                    symbol.address[it - symbol.data.begin()] = start_ptr;
                }
                else
                {
                    symbol.data.push_back(s);
                    symbol.address.push_back(++(symbol.ptr));
                    cout << " ( S , "<< symbol.ptr <<" ) ";   
                }
                // symbol.push_back({s,++sym_ptr});
                // cout << " ( S , "<< 1 <<" ) ";   
            }
            
            // cout<<s<<" | ";
        }
        cout<<"\n";
        // cout<<"\n --------------------------------------------- \n";
    }

    for (int i = 0; i < literal.data.size(); i++)
    {
        literal.address[i] = start_ptr++;
    }
    

    storetable(literal,"literal.txt");
    storetable(symbol,"symbol.txt");

    fclose(stdout);
    return 0;
}

void readFile(string filepath,vector<vector<string>> &inputData)
{
    ifstream in(filepath);
    int num = 0;
    string line;

    // ifstream file { "input.txt" };
    // vector<string> my_array;
    // string num { 0 };
    // while (file >> num)
    //     my_array.emplace_back(vector<num);

    // for(string s : my_array)
    //     cout<<s<<" ";

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

}

void storetable(table Table,string file_name)
{
    freopen (&file_name[0],"w",stdout);
    for(int i = 0 ; i < Table.data.size(); i++)
    {
        cout << i+1 << " " << Table.data[i] <<" " << Table.address[i]<< "\n";
    }
    fclose(stdout);
}

/*

START 200
MOVER AREG,A 
LOOP MOVER  CREG, B
    ADD CREG,='10'
END 

*/