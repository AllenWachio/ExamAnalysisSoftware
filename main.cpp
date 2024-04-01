#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

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
            variance += pow(mark - average, 2);
        }
        variance /= marks.size();
        return sqrt(variance);
    }
};

// Class to handle grade calculations
class GradeCalculator {
public:
    // Grade
    static char calculateGrade(int mark) {
        if (mark >= 90) {
            return 'A';
        } else if (mark >= 80) {
            return 'B';
        } else if (mark >= 70) {
            return 'C';
        } else if (mark >= 60) {
            return 'D';
        } else if (mark >= 50) {
            return 'E';
        } else {
            return 'F';
        }
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

// Function to compare total marks for ranking
bool compareTotalMarks(const vector<string>& student1, const vector<string>& student2) {
    int totalMarks1 = stoi(student1[student1.size() - 2]); // Total marks is the second last element
    int totalMarks2 = stoi(student2[student2.size() - 2]);
    return totalMarks1 > totalMarks2;
}

int main() {
    vector<vector<string>> studentData = FileHandler::readFromFile("input.txt");
    vector<string> outputLines;
    vector<vector<string>> rankData = studentData; // Copy student data for ranking

    for (vector<string>& record : studentData) {
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

        // Calculate grades for each subject
        vector<char> grades;
        for (int mark : marks) {
            grades.push_back(GradeCalculator::calculateGrade(mark));
        }

        outputLines.push_back("Student: " + name);
        outputLines.emplace_back("Marks:");
        for (size_t i = 0; i < marks.size(); ++i) {
            outputLines.push_back("Subject " + to_string(i + 1) + ": " + to_string(marks[i]) + " (Grade: " + grades[i] + ")");
        }
        outputLines.push_back("Total Marks: " + to_string(totalMarks));
        outputLines.push_back("Average Marks: " + to_string(average));
        outputLines.push_back("Standard Deviation: " + to_string(stdDev));
        outputLines.emplace_back("");
    }

    // Sort students based on total marks
    sort(rankData.begin(), rankData.end(), compareTotalMarks);

    // Write ranked results to output file
    vector<string> rankOutputLines;
    rankOutputLines.emplace_back("Ranking of Students (Best to Worst):");
    int rank = 1;
    for (const vector<string>& record : rankData) {
        rankOutputLines.push_back(to_string(rank++) + ". " + record[0] + " - Total Marks: " + to_string(totalMarks));
    }

    FileHandler::writeToFile("output.txt", outputLines);
    FileHandler::writeToFile("ranking.txt", rankOutputLines);
    cout << "Analysis completed. Results saved to output.txt and ranking.txt." << endl;
    return 0;
}
