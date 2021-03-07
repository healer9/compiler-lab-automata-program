#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void dfa_check(string input, int initial_state, vector<int> &final_states, vector<vector<int>> &dfa_graph)
{
    bool accepted = false;
    for (int i = 0; i < (int)input.size(); i++)
    {
        string input_val;
        input_val += input[i];
        int column = stoi(input_val);
        int next_state = dfa_graph[initial_state][column];
        if (next_state == -1)
        {
            cout << "\nString not accepted\n";
            return;
        }
        initial_state = next_state;
        input_val.clear();
    }

    for (int i : final_states)
    {
        if (i == initial_state)
        {
            accepted = !accepted;
            break;
        }
    }

    cout << input;
    accepted ? cout << " is Accepted\n" : cout << " is Discarded\n";
}

int main()
{
    string line;
    string fileName;
    cout << "Enter the file name to open it: ";
    cin >> fileName;
    ifstream myFile(fileName);
    int lineNo = 0;

    int initial_state;
    vector<int> final_states;

    vector<vector<int>> dfa_graph;

    if (myFile.is_open())
    {
        vector<int> temp;
        while (getline(myFile, line))
        {
            if (lineNo == 0)
            {
                initial_state = stoi(line);
                lineNo++;
                line.clear();
            }
            else if (lineNo == 1)
            {
                string num;
                for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] == ' ')
                    {
                        continue;
                    }
                    else if (line[i] == ',')
                    {
                        int final_state = stoi(num);
                        final_states.push_back(final_state);
                        num.clear();
                    }
                    else
                    {
                        num += line[i];
                    }
                }
                int left_state = stoi(num);
                final_states.push_back(left_state);
                lineNo++;
                line.clear();
            }
            else
            {
                string num;
                for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] == ' ')
                    {
                        int state = stoi(num);
                        temp.push_back(state);
                        num.clear();
                        continue;
                    }
                    else
                    {
                        num += line[i];
                    }
                }
                int digit = stoi(num);
                temp.push_back(digit);
                dfa_graph.push_back(temp);
                temp.clear();
                line.clear();
            }
        }
    }
    else
    {
        cout << "Not able to open file : " << fileName << endl;
        myFile.close();
    }
    myFile.close();

    while (1)
    {
        string input;
        cout << "\nEnter the input string: ";
        cin >> input;

        if (input[0] == '-')
        {
            cout << "\nProgram is terminated\n";
            break;
        }

        dfa_check(input, initial_state, final_states, dfa_graph);
        input.clear();
    }

    return 0;
}