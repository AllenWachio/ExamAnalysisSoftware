#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

// Class to handle statistical calculations
class StatisticsCalculator {
public:
    // Average
    static double calculateAverage(const vector<int>& marks) {
        int sum = 0;
        for (int mark : marks) {
            sum += mark;
        }
        return static_cast<double>(sum) / marks.size();
    }

    // Standard deviation
    static double calculateStdDev(const vector<int>& marks, double average) {
        double variance = 0;
        for (int mark : marks) {
            variance += pow(mark - average, 2) /8;
        }
        variance /= marks.size();
        return sqrt(variance);
    }
};

// Class to handle file input/output operations
class FileHandler {
public:
    // Read data from file
    static vector<vector<string>> readFromFile(const string& filename) {
        vector<vector<string>> data;
        ifstream file(filename);
        if (!file) {
            cerr << "Error: Unable to open input file." << endl;
            return data;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> record;
            string item;
            while (ss >> item) {
                record.push_back(item);
            }
            data.push_back(record);
        }
        file.close();
        return data;
    }

    // Write data to file
    static void writeToFile(const string& filename, const vector<string>& lines) {
        ofstream file(filename);
        if (!file) {
            cerr << "Error: Unable to open output file." << endl;
            return;
        }

        for (const string& line : lines) {
            file << line << endl;
        }
        file.close();
    }
};

int main() {
    vector<vector<string>> studentData = FileHandler::readFromFile("input.txt");
    vector<string> outputLines;

    for (const vector<string>& record : studentData) {
        string name = record[0];
        vector<int> marks;
        for (size_t i = 1; i < record.size(); ++i) {
            marks.push_back(stoi(record[i]));
        }

        // Calculate total marks
        int totalMarks = 0;
        for (int mark : marks) {
            totalMarks += mark;
        }

        double average = StatisticsCalculator::calculateAverage(marks);

        double stdDev = StatisticsCalculator::calculateStdDev(marks, average);


        outputLines.push_back("Student: " + name);
        outputLines.push_back("Marks:");
        for (int mark : marks) {
            outputLines.push_back(to_string(mark));
        }
        outputLines.push_back("Total Marks: " + to_string(totalMarks));
        outputLines.push_back("Average Marks: " + to_string(average));
        outputLines.push_back("Standard Deviation: " + to_string(stdDev));
        outputLines.push_back("");
    }

    FileHandler::writeToFile("output.txt", outputLines);
    cout << "Analysis completed. Results saved to output.txt." << endl;
    return 0;
}

