#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "sstream"

void mealy_output(std::string s, int initial_state, std::vector<std::vector<std::pair<int, std::string>>> &graph)
{
    // for (int i = 0; i < graph.size(); i++)
    // {
    //     std::cout << i << "-> ";
    //     for (int j = 0; j < graph[i].size(); j++)
    //         std::cout << "{ " << graph[i][j].first << ", " << graph[i][j].second << "} ";
    //     std::cout << std::endl;
    // }
    std::string output;
    bool inturupted = false;
    std::cout << "Transition states : ";
    for (int i = 0; i < (int)s.size(); i++)
    {
        int col = s[i] - '0';
        output += graph[initial_state][col].second;
        std::cout << initial_state << " -> ";
        int next_state = graph[initial_state][col].first;
        if (next_state == -1)
        {
            inturupted = true;
            break;
        }
        initial_state = next_state;
    }
    if (!inturupted)
        std::cout << initial_state;
    std::cout << "\nMelay Output : " << output;
    std::cout << std::endl;
}

void fileInput(int &initial_state, std::vector<std::vector<std::pair<int, std::string>>> &graph)
{
    std::fstream myFile;
    myFile.open("mealy.txt");
    try
    {
        if (!myFile.is_open())
            throw "Unable to open input file\n";
        std::string line;
        int line_num = 0;
        while (std::getline(myFile, line))
        {
            if (line_num == 0)
            {
                std::stringstream ss(line);
                ss >> initial_state;
                line_num++;
            }
            else
            {
                std::string word;
                std::stringstream ss(line);
                std::vector<int> temp_num;
                std::vector<std::string> temp_str;
                int col = 0;
                std::pair<int, std::string> p;
                while (ss >> word)
                {
                    if (col & 1)
                    {
                        temp_str.push_back(word);
                    }
                    else
                    {
                        temp_num.push_back(std::stoi(word));
                    }
                    col++;
                }
                std::vector<std::pair<int, std::string>> temp_pair;
                for (int i = 0; i < (int)temp_num.size(); i++)
                {
                    temp_pair.push_back({temp_num[i], temp_str[i]});
                }
                graph.push_back(temp_pair);
            }
        }
    }
    catch (const char *error)
    {
        std::cerr << error;
        exit(0);
    }
}

int32_t main(int argc, char **argv)
{
    int initial_state;
    // {next_state, output}
    std::vector<std::vector<std::pair<int, std::string>>> graph;
    fileInput(initial_state, graph);
    std::cout << "Enter the input string : ";
    std::string s;
    std::cin >> s;
    mealy_output(s, initial_state, graph);
    return 0;
}