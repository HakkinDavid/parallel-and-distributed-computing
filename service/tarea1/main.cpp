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

class GlobalSum {
    private:
        bool busy;
        std::shared_ptr<RandomNumberSum> maxSum;
        std::mutex mutex;
        std::condition_variable processing;
    public:
        void request() {
            {
                std::unique_lock lock(mutex);
                processing.wait(lock, [&] {return !busy;});
                busy = true;
            }
        }
        bool update(std::shared_ptr<RandomNumberSum> &localSum) {
            if (maxSum == nullptr || maxSum->Sum() < localSum->Sum()) {
                maxSum = localSum;
                std::println("{} is currently the greatest sum so far.", maxSum->Name());
                return true;
            }
            return false;
        }
        void release() {
            busy = false;
            processing.notify_one();
        }

        bool Busy () const {
            return busy;
        }
        std::shared_ptr<RandomNumberSum> &MaxSum() {
            return maxSum;
        }

        GlobalSum() {
           maxSum = nullptr;
        }
};

int main() {
    GlobalSum globalSum;
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
        std::make_shared<RandomNumberSum>(100, 1, 1000, "Thread 1's sum0")
    };

    std::thread thread1([&]() {
        randomSums.at(0)->executeRandomSum();
        std::println("Thread 1 finalized with result {}.", randomSums[0]->getHumanReadableSum());
        globalSum.request();
        globalSum.update(randomSums.at(0));
        globalSum.release();
    });

    std::thread thread2([&]() {
        randomSums.at(1)->executeRandomSum();
        std::println("Thread 2 finalized with result {}.", randomSums[1]->getHumanReadableSum());
        globalSum.request();
        globalSum.update(randomSums.at(1));
        globalSum.release();
    });

    std::thread thread3([&]() {
        randomSums.at(2)->executeRandomSum();
        std::println("Thread 3 finalized with result {}.", randomSums[2]->getHumanReadableSum());
        globalSum.request();
        globalSum.update(randomSums.at(2));
        globalSum.release();
    });

    std::thread thread4([&]() {
        randomSums.at(3)->executeRandomSum();
        std::println("Thread 4 finalized with result {}.", randomSums[3]->getHumanReadableSum());
        globalSum.request();
        globalSum.update(randomSums.at(3));
        globalSum.release();
    });

    std::thread thread5([&]() {
        randomSums.at(4)->executeRandomSum();
        std::println("Thread 5 finalized with result {}.", randomSums[4]->getHumanReadableSum());
        globalSum.request();
        globalSum.update(randomSums.at(4));
        globalSum.release();
    });

    std::thread thread6([&]() {
        randomSums.at(5)->executeRandomSum();
        std::println("Thread 6 finalized with result {}.", randomSums[5]->getHumanReadableSum());
        globalSum.request();
        globalSum.update(randomSums.at(5));
        globalSum.release();
    });

    std::thread thread7([&]() {
        randomSums.at(6)->executeRandomSum();
        std::println("Thread 7 finalized with result {}.", randomSums[6]->getHumanReadableSum());
        globalSum.request();
        globalSum.update(randomSums.at(6));
        globalSum.release();
    });

    std::thread thread8([&]() {
        randomSums.at(7)->executeRandomSum();
        std::println("Thread 8 finalized with result {}.", randomSums[7]->getHumanReadableSum());
        globalSum.request();
        globalSum.update(randomSums.at(7));
        globalSum.release();
    });

    std::thread thread9([&]() {
        randomSums.at(8)->executeRandomSum();
        std::println("Thread 9 finalized with result {}.", randomSums[8]->getHumanReadableSum());
        globalSum.request();
        globalSum.update(randomSums.at(8));
        globalSum.release();
    });

    std::thread thread10([&]() {
        randomSums.at(9)->executeRandomSum();
        std::println("Thread 10 finalized with result {}.", randomSums[9]->getHumanReadableSum());
        globalSum.request();
        globalSum.update(randomSums.at(9));
        globalSum.release();
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

    std::println("\nGreatest sum of all was {} with value {}.", globalSum.MaxSum()->Name(), globalSum.MaxSum()->Sum());
    
    return 0;
}