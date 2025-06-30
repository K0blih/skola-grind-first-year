/**
 * @file main.cpp
 * @brief Program for merging multiple sorted lists from text files into a single sorted output file.
 *
 * This program reads a number of lists from text files located in a specified folder.
 * The lists are merged into one sorted list, which is saved to an output file.
 * Input is taken from `input.txt` via redirected stdin or entered manually via stdin.
 * @details
 * Sources:
 * - https://en.wikipedia.org/wiki/Merge_algorithm
 * - https://www.doxygen.nl/manual/docblocks.html
 * - https://en.cppreference.com/w/cpp/algorithm/merge
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

 /**
  * @brief Extracts integer lists from text files in the specified folder.
  *
  * Each file is expected to be named as `0.txt`, `1.txt`, ..., `k-1.txt`.
  * The contents of these files are saved in the provided vector of vectors.
  *
  * @param folder Path to the folder containing the input text files.
  * @param inputLists Vector to store the extracted integer lists.
  * @param k Number of input files/lists to read.
  */
void extractLists(std::string& folder, std::vector<std::vector<int>>& inputLists, int k);

/**
 * @brief Merges multiple sorted integer lists into one sorted output list.
 *
 * Implements a k-way merge algorithm that compares the current smallest elements
 * across all lists and appends the minimum to the output list.
 *
 * @param inputLists Vector of sorted integer lists to be merged.
 * @param outputList Vector where the merged sorted list will be stored.
 * @param k Number of input lists.
 */
void mergeLists(std::vector<std::vector<int>>& inputLists,
                std::vector<int>& outputList, int k);

/**
 * @brief Writes the merged sorted list to an output text file.
 *
 * Each number is written on a separate line, except the last number which is written without a trailing newline.
 *
 * @param outputFile Path to the output file.
 * @param outputList Vector containing the merged sorted integers.
 */
void createOutput(std::string& outputFile, std::vector<int>& outputList);

int main() 
{
    // variables for input
	int k;
	std::string folder;
	std::string outputFile;

    // take input from input.txt
    FILE* file;
    if (freopen_s(&file, "input.txt", "r", stdin) != 0) {
        std::cerr << "Failed to open input.txt for reading." << std::endl;
        return 1;
    }

    // k input
    std::cin >> k;

    // folder input
    std::cin.ignore();
    std::getline(std::cin, folder);
    folder = folder + "/";

    // output file
    std::getline(std::cin, outputFile);
    outputFile = outputFile + ".txt";

    //init input lists and output list
    std::vector<std::vector<int>> inputLists(k);
    std::vector<int> outputList;

    // extract lists from input files
    extractLists(folder, inputLists, k);
    // merge lists
    mergeLists(inputLists, outputList, k);
    // create output.txt file
    createOutput(outputFile, outputList);



    // test for comparison
    /*std::vector<int> merged(inputLists[0].size() + inputLists[1].size());

    std::merge(inputLists[0].begin(), inputLists[0].end(), inputLists[1].begin(),
        inputLists[1].end(), merged.begin());

    for (int i = 0; i < merged.size(); i++) {
        std::cout << merged[i] << " ";
    }*/

	return 0;
}

void extractLists(std::string& folder, std::vector<std::vector<int>>& inputLists, int k)
{
    // extract lists
    for (int i = 0; i < k; ++i) {
        std::string filename = folder + std::to_string(i) + ".txt";

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            continue;
        }

        int number;
        while (file >> number) {
            inputLists[i].push_back(number);
        }

        file.close();
    }
}

void mergeLists(std::vector<std::vector<int>>& inputLists, 
                std::vector<int>& outputList, int k)
{
    // indices and loop condition
    std::vector<int> indices(k, 0);
    bool hasElements = true;

    // k-way merge algorithm
    while (hasElements) {
        hasElements = false;
        int minValue = -1;
        int minIndex = -1;

        for (int i = 0; i < k; ++i) {
            if (indices[i] >= inputLists[i].size()) {
                continue;
            }

            hasElements = true;

            if (minIndex == -1 || inputLists[i][indices[i]] < inputLists[minIndex][indices[minIndex]]) {
                minIndex = i;
                minValue = inputLists[i][indices[i]];
            }
        }

        if (minIndex != -1) {
            outputList.push_back(minValue);
            indices[minIndex]++;
        }
    }
}

void createOutput(std::string& outputFile, std::vector<int>& outputList)
{
    // output
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open output file: " + outputFile);
    }

    for (int i = 0; i < outputList.size(); ++i) {
        if (i < outputList.size() - 1) {
            outFile << outputList[i] << "\n";
        }
        else {
            outFile << outputList[i];
        }
    }
}