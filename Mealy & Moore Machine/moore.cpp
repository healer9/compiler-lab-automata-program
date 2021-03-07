#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "sstream"

void moore_output(std::string s, int initial_state, std::vector<std::vector<int>> &graph, std::vector<std::string> &output)
{
    bool interrupted = false;
    std::string output_str;
    const int n = (int)s.size();
    std::cout << "Transition states : ";
    for (int i = 0; i < n; i++)
    {
        int col = s[i] - '0';
        output_str += output[initial_state];
        int next_state = graph[initial_state][col];
        std::cout << initial_state << "-> ";
        if (next_state == -1)
        {
            interrupted = true;
            break;
        }
        initial_state = next_state;
    }
    if (!interrupted)
    {
        std::cout << initial_state;
        output_str += output[initial_state];
    }
    std::cout << "\nMoore Output : " << output_str << std::endl;
}

void fileInput(int &initial_state, std::vector<std::vector<int>> &graph, std::vector<std::string> &output)
{
    std::fstream myFile;
    myFile.open("moore.txt");
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
                std::vector<int> temp;
                int col = 0;
                while (ss >> word)
                {
                    if (col == 0)
                    {
                        col++;
                        output.push_back(word);
                    }
                    else
                        temp.push_back(stoi(word));
                }
                graph.push_back(temp);
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
    std::vector<std::vector<int>> graph;
    std::vector<std::string> output;
    fileInput(initial_state, graph, output);
    std::cout << "Enter the input string : ";
    std::string s;
    std::cin >> s;
    moore_output(s, initial_state, graph, output);
    return 0;
}