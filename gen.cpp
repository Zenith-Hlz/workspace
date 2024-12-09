#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Structure for a data item
struct DataItem
{
    string key;
    int value;
};

// Function to read data from the file
vector<DataItem> readDataFromFile(const string &filename)
{
    vector<DataItem> data;

    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error: Cannot open file " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(infile, line))
    {
        size_t pos1 = line.find(' ');
        size_t pos2 = line.find(' ', pos1 + 1);
        if (pos1 != string::npos && pos2 != string::npos)
        {
            string key = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int value = stoi(line.substr(pos2 + 1));
            data.push_back({key, value});
        }
    }

    infile.close();
    return data;
}

// Function to generate uniform distribution test data
vector<string> generateUniformTestData(const vector<DataItem> &data, int insertOps, int queryOps, unordered_set<string> &insertedKeys)
{
    int dataSize = data.size();
    vector<string> output; // Vector to store generated input

    // Insert operations
    for (int i = 0; i < insertOps && i < dataSize; ++i)
    {
        int index = rand() % dataSize;
        while (insertedKeys.count(data[index].key))
        { // Avoid duplicate inserts
            index = rand() % dataSize;
        }
        insertedKeys.insert(data[index].key);
        output.push_back("0 " + data[index].key + " " + to_string(data[index].value));
    }

    // Query operations
    for (int i = 0; i < queryOps; ++i)
    {
        if (rand() % 2 == 0 && !insertedKeys.empty())
        { // Query inserted keys
            auto it = insertedKeys.begin();
            advance(it, rand() % insertedKeys.size());
            output.push_back("1 " + *it);
        }
        else
        { // Query random or non-inserted keys
            int index = rand() % dataSize;
            output.push_back("1 " + data[index].key);
        }
    }

    return output;
}

vector<string> generateRandomTestData(const vector<DataItem> &data, int insertOps, int queryOps, unordered_set<string> &insertedKeys)
{
    vector<string> output = generateUniformTestData(data, insertOps, queryOps, insertedKeys);

    random_shuffle(output.begin(), output.end());

    return output;
}

// Function to print test data
void printTestData(const vector<string> &testData)
{
    for (const auto &line : testData)
        cout << line << endl;
    cout << "2" << endl; // End of operations
}

// Main function to generate test data
void generateTestData(const vector<DataItem> &data, int insertCount, int queryCount, const string &distribution)
{
    unordered_set<string> insertedKeys;
    int insertOps = insertCount;
    int queryOps = queryCount;

    vector<string> testData;

    if (distribution == "uniform")
        testData = generateUniformTestData(data, insertOps, queryOps, insertedKeys);
    else if (distribution == "random")
        testData = generateRandomTestData(data, insertOps, queryOps, insertedKeys);
    else
    {
        cerr << "Error: Unknown distribution type " << distribution << endl;
        exit(1);
    }

    printTestData(testData);
}

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        cerr << "Usage: " << argv[0] << " <input_file> <insert_count> <query_count> <distribution> <output_file>" << endl;
        cerr << "Distribution types: uniform, random" << endl;
        return 1;
    }

    string inputFile = argv[1];
    int insertCount = stoi(argv[2]);
    int queryCount = stoi(argv[3]);
    string distribution = argv[4];
    string outputFile = argv[5];

    vector<DataItem> data = readDataFromFile(inputFile);

    // Redirect output to a file
    ofstream outfile(outputFile);
    if (!outfile)
    {
        cerr << "Error: Cannot open output file " << outputFile << endl;
        return 1;
    }

    // Redirect standard output to the file
    streambuf *coutbuf = cout.rdbuf();
    cout.rdbuf(outfile.rdbuf());

    generateTestData(data, insertCount, queryCount, distribution);

    // Restore standard output
    cout.rdbuf(coutbuf);

    cout << "Test data generated in " << outputFile << endl;

    return 0;
}
