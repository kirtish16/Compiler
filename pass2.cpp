#include <bits/stdc++.h>

using namespace std;

void readFile(string filepath,vector<vector<string>> &inputData);


int main()
{
    string ic = "output.txt";
    vector<vector<string>> inputData;
    readFile(ic,inputData);

    string lt = "literal.txt";
    vector<vector<string>> literal;
    readFile(lt,literal);
    // 0 -> index , 1 -> data , 2-. address

    string sy = "symbol.txt";
    vector<vector<string>> symbol;
    readFile(sy,symbol);
    // 0 -> index , 1 -> data , 2-. address

    freopen ("target.txt","w",stdout);
    for(int i = 0 ; i < inputData.size(); i++)
    {

        if(inputData[i][1] == "IS")
        {
            cout << inputData[i][0] <<") " ;
            int j = 2 ;
            while(j < inputData[i].size())
            {
                if(inputData[i][j] == "S")
                {

                    int syind =  stoi(inputData[i][++j]) ;
                    cout << symbol[syind-1][2] << " ";

                }
                else if(inputData[i][j] == "L")
                {
                    int ltind =  stoi(inputData[i][++j]) ;
                    cout << literal[ltind-1][2] << " ";
                }
                else if(inputData[i][j] == "CC"){
                    j++;
                    continue;

                }
                else
                    cout << inputData[i][j] << " " ;
                j++;
            }

        }
        else if(inputData[i][1] == "DL" && inputData[i][2] == "1")
        {
            cout << inputData[i][0] <<") " <<inputData[i][4] ;
        }
        else if(inputData[i][1].find('=') != inputData[i][1].npos)
        {
            cout << inputData[i][0] << ") " << inputData[i][1];
        }

        cout << "\n";
    }
    // IS , DL 1 , Literal
    return 0 ;
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
            if(temp == "(")continue;
            if(temp == ")")continue;
            instr.push_back(temp);
        }
        inputData.push_back(instr);
    }

}
