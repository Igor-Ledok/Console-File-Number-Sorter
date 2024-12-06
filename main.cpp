#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

bool isNumber(const std::string& str) {
    for (char ch : str) {
        if (!std::isdigit(ch) && ch != '-' && ch != '+') {
            return false;
        }
    }
    return !str.empty();
}

std::vector<int> extractNumbers(const std::string& input) {
    std::vector<int> numbers;
    std::istringstream iss(input);
    std::string word;

    while (iss >> word) {
        if (isNumber(word)) {
            numbers.push_back(std::stoi(word));
        }
    }

    return numbers;
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        }
        else {
            temp.push_back(arr[j++]);
        }
    }

    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); ++k) {
        arr[left + k] = temp[k];
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    std::string filePath;
    std::cout << "Enter the file path: ";
    std::getline(std::cin, filePath);

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filePath << std::endl;
        return 1;
    }

    std::vector<int> allNumbers;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<int> lineNumbers = extractNumbers(line);
        allNumbers.insert(allNumbers.end(), lineNumbers.begin(), lineNumbers.end());
    }

    file.close();

    if (allNumbers.empty()) {
        std::cout << "No numbers found in the file." << std::endl;
        return 0;
    }

    mergeSort(allNumbers, 0, allNumbers.size() - 1);

    std::cout << "Sorted numbers:" << std::endl;
    for (int num : allNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
