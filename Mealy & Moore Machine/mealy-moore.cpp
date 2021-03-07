#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "sstream"

void mealy_output(std::string s)
{
    int initial_state;
    // {next_state, output}
    std::vector<std::vector<std::pair<int, int>>> graph;
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
                int num;
                std::stringstream ss(line);
                std::vector<int> temp;
                std::vector<std::pair<int, int>> temp_pair;
                while (ss >> num)
                {
                    temp.push_back(num);
                }
                for (int i = 0; i < (int)temp.size(); i += 2)
                {
                    // {next_state, output}
                    temp_pair.push_back({temp[i], temp[i + 1]});
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

    // for (int i = 0; i < (int)graph.size(); i++)
    // {
    //     std::cout << "[ " << i << " ]->";
    //     for (int j = 0; j < (int)graph[i].size(); j++)
    //     {
    //         std::cout << "{ " << graph[i][j].first << ", " << graph[i][j].second << " } ";
    //     }
    //     std::cout << std::endl;
    // }

    std::string output;

    for (int i = 0; i < (int)s.size(); i++)
    {
        int col = s[i] - '0';
        output += std::to_string(graph[initial_state][col].second);
        std::cout << initial_state << " -> ";
        int next_state = graph[initial_state][col].first;
        initial_state = next_state;
    }
    std::cout << initial_state;
    std::cout << "\nMelay Output : " << output << std::endl;
}

void moore_output(std::string s, int initial_state, std::vector<std::vector<int>> &graph)
{
    std::string output;
    const int n = (int)s.size();
    for (int i = 0; i < n; i++)
    {
        int col = s[i] - 'a';
        output += std::to_string(graph[initial_state][2]);
        int next_state = graph[initial_state][col];
        // std::cout << initial_state << "-> ";
        initial_state = next_state;
    }
    // std::cout << initial_state << "-> ";
    output += std::to_string(graph[initial_state][2]);
    std::cout << "Moore Output : " << output << std::endl;
}

void fileInput(int &initial_state, std::vector<std::vector<int>> &graph)
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
                int num;
                std::stringstream ss(line);
                std::vector<int> temp;
                while (ss >> num)
                {
                    temp.push_back(num);
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
    fileInput(initial_state, graph);
    while (1)
    {
        std::cout << "1. Mealy Machine.\n2. Moore Machine.\n3. Exit.\nEnter your Choice: ";
        int ch;
        std::cin >> ch;
        if (ch == 3)
            break;
        std::cout << "Enter the input string : ";
        std::string s;
        std::cin >> s;
        switch (ch)
        {
        case 1:
            mealy_output(s);
            break;
        case 2:
            moore_output(s, initial_state, graph);
            break;
        }
    }
    return 0;
}