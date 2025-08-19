#include<memory>
#include<thread>
#include<string>
#include<iostream>
#include<mutex>
#include<condition_variable>
#include<random>
#include<vector>
#include<sstream>
#include<print>
#include <algorithm>

class RandomNumberSum {
    private:
        int minNumber;
        int maxNumber;
        int numberOfAddends;
        int sum;
        std::string name;
        std::vector<int> addends;
        std::mt19937 generator;
        std::uniform_int_distribution<int> distribution;
    public:
        RandomNumberSum(int numberOfAddends, int minNumber, int maxNumber, std::string name) : numberOfAddends(numberOfAddends), minNumber(minNumber), maxNumber(maxNumber), name(name) {
            generator = std::mt19937(std::chrono::high_resolution_clock::now().time_since_epoch().count());
            distribution = std::uniform_int_distribution<int>(minNumber, maxNumber);
        }
        void executeRandomSum() {
            addends.clear();
            sum = 0;
            addends.reserve(numberOfAddends);
            for(int i = 0; i < numberOfAddends; i++) {
                addends.push_back(distribution(generator));
                sum += addends.back();
            }
        }
        std::string getHumanReadableSum() {
            std::stringstream resultingSum;
            for (auto iterator = addends.cbegin(); iterator != addends.cend(); ++iterator) {
                resultingSum << *iterator << " + ";
            }
            std::string result = resultingSum.str();
            result.erase(result.length() - 2);
            result.append("= ");
            result.append(std::to_string(sum));
            return result;
        }
        std::string_view Name () {
            return name;
        }
        int Sum() const {
            return sum;
        }
        int MinNumber() const {
            return minNumber;
        }
        int MaxNumber() const {
            return maxNumber;
        }
        int NumberOfAddends() const {
            return numberOfAddends;
        }
        std::vector<int> Addends() {
            return addends;
        }
};

int main() {
    std::vector<std::shared_ptr<RandomNumberSum>> randomSums = {
        std::make_shared<RandomNumberSum>(100, 1, 1000, "Thread 1's sum"),
        std::make_shared<RandomNumberSum>(100, 1, 1000, "Thread 2's sum"),
        std::make_shared<RandomNumberSum>(100, 1, 1000, "Thread 3's sum"),
        std::make_shared<RandomNumberSum>(100, 1, 1000, "Thread 4's sum"),
        std::make_shared<RandomNumberSum>(100, 1, 1000, "Thread 5's sum"),
        std::make_shared<RandomNumberSum>(100, 1, 1000, "Thread 6's sum"),
        std::make_shared<RandomNumberSum>(100, 1, 1000, "Thread 7's sum"),
        std::make_shared<RandomNumberSum>(100, 1, 1000, "Thread 8's sum"),
        std::make_shared<RandomNumberSum>(100, 1, 1000, "Thread 9's sum"),
        std::make_shared<RandomNumberSum>(100, 1, 1000, "Thread 10's sum")
    };

    std::thread thread1([&]() {
        randomSums.at(0)->executeRandomSum();
        std::println("Thread 1 finalized as follows\n{}.\n", randomSums[0]->getHumanReadableSum());
    });

    std::thread thread2([&]() {
        randomSums.at(1)->executeRandomSum();
        std::println("Thread 2 finalized as follows\n{}.\n", randomSums[1]->getHumanReadableSum());
    });

    std::thread thread3([&]() {
        randomSums.at(2)->executeRandomSum();
        std::println("Thread 3 finalized as follows\n{}.\n", randomSums[2]->getHumanReadableSum());
    });

    std::thread thread4([&]() {
        randomSums.at(3)->executeRandomSum();
        std::println("Thread 4 finalized as follows\n{}.\n", randomSums[3]->getHumanReadableSum());
    });

    std::thread thread5([&]() {
        randomSums.at(4)->executeRandomSum();
        std::println("Thread 5 finalized as follows\n{}.\n", randomSums[4]->getHumanReadableSum());
    });

    std::thread thread6([&]() {
        randomSums.at(5)->executeRandomSum();
        std::println("Thread 6 finalized as follows\n{}.\n", randomSums[5]->getHumanReadableSum());
    });

    std::thread thread7([&]() {
        randomSums.at(6)->executeRandomSum();
        std::println("Thread 7 finalized as follows\n{}.\n", randomSums[6]->getHumanReadableSum());
    });

    std::thread thread8([&]() {
        randomSums.at(7)->executeRandomSum();
        std::println("Thread 8 finalized as follows\n{}.\n", randomSums[7]->getHumanReadableSum());
    });

    std::thread thread9([&]() {
        randomSums.at(8)->executeRandomSum();
        std::println("Thread 9 finalized as follows\n{}.\n", randomSums[8]->getHumanReadableSum());
    });

    std::thread thread10([&]() {
        randomSums.at(9)->executeRandomSum();
        std::println("Thread 10 finalized as follows\n{}.\n", randomSums[9]->getHumanReadableSum());
    });

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();
    thread8.join();
    thread9.join();
    thread10.join();

    std::sort(randomSums.begin(), randomSums.end(), [](std::shared_ptr<RandomNumberSum>& a, std::shared_ptr<RandomNumberSum>& b) {
        return a->Sum() < b->Sum();
    });

    std::println("\nGreatest sum of all was {} with value {}.", randomSums.back()->Name(), randomSums.back()->Sum());
    
    return 0;
}