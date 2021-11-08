#include <bits/stdc++.h>

using namespace std;

void readFile(string filepath,vector<vector<string>> &inputData);

int main()
{
    string ic = "output.txt";
    vector<vector<string>> inputData;
    readFile(ic,inputData);

    string tii_path = "tii.txt";
    vector<vector<string>> tii;
    readFile(tii_path,tii);

    string lt = "literal.txt";
    vector<vector<string>> literal;
    readFile(lt,literal);
    // 0 -> index , 1 -> data , 2-. address

    string sy = "symbol.txt";
    vector<vector<string>> symbol;
    readFile(sy,symbol);
    // 0 -> index , 1 -> data , 2-. address

    cout << "Back patching : \n";
    // freopen ("target.txt","w",stdout);

    //Back Patching 

    int tii_ptr = 0 ;
    for(int i = 0 ; i < inputData.size(); i++)
    {
        if(tii[tii_ptr][2] == inputData[i][0] )
        {
            string s = tii[tii_ptr][1];
            string addr = "";
            if(s.find('=') != s.npos)
            {
                //Literal table 
                for(int lt_ptr = 0 ; lt_ptr < literal.size(); lt_ptr++)
                {
                    if(literal[lt_ptr][1] == s)
                    {
                        addr = literal[lt_ptr][2];
                        break;
                    }
                }

            }
            else
            {
                for(int sy_ptr = 0 ; sy_ptr < symbol.size(); sy_ptr++)
                {
                    if(symbol[sy_ptr][1] == s)
                    {
                        addr = symbol[sy_ptr][2];
                        break;
                    }
                }

            }
                inputData[i].push_back(addr);
                tii_ptr++;
        }

        for(int j = 0 ; j < inputData[i].size(); j++)
        {
            cout << inputData[i][j] << " ";
        }

        cout <<"\n";

    }
       

        cout << "\n";
    
    fclose(stdout);
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

    in.close();
}
