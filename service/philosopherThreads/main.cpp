#include<memory>
#include<thread>
#include<string>
#include<string_view>
#include<print>
#include<mutex>
#include<condition_variable>

class Fork {
    private:
        bool busy;
        std::mutex mutex;
        std::condition_variable taken;
        std::string_view name;
    public:
        void pickUp(std::string_view name) {
            {
                std::unique_lock lock(mutex);
                std::println("{} is waiting for fork", name);
                taken.wait(lock, [&] {return !busy;});
                busy = true;
                this->name = name;
            }
        }
        void putDown() {
            busy = false;
            taken.notify_one();
        }

        bool Busy () const {
            return busy;
        }
};

class Philosopher {
    private:
        std::shared_ptr<Fork> leftFork;
        std::shared_ptr<Fork> rightFork;
        std::string name;
    public:
        void eat() {
            while(true) {
                leftFork->pickUp(name);
                if (rightFork->Busy()) {
                    std::println("{} putting left fork down", name);
                    leftFork->putDown();
                    continue;
                }
                std::println("{} picking right fork", name);
                rightFork->pickUp(name);
                std::println("{} started eating", name);
                std::this_thread::sleep_for(std::chrono::seconds(2));
                std::println("{} done eating", name);
                std::println("{} putting left fork down", name);
                leftFork->putDown();
                std::println("{} putting right fork down", name);
                rightFork->putDown();

            }
        }
        std::shared_ptr<Fork> &LeftFork() {
            return leftFork;
        }
        std::shared_ptr<Fork> &RightFork() {
            return rightFork;
        }
        Philosopher(std::string name):name(name) {

        }
};

int main() {
    std::shared_ptr<Fork> fork1 = std::make_shared<Fork>();
    std::shared_ptr<Fork> fork2 = std::make_shared<Fork>();
    std::shared_ptr<Fork> fork3 = std::make_shared<Fork>();
    std::shared_ptr<Fork> fork4 = std::make_shared<Fork>();
    std::shared_ptr<Fork> fork5 = std::make_shared<Fork>();
    Philosopher shrek("Shrek");
    Philosopher donkey("Donkey");
    Philosopher fiona("Fiona");
    Philosopher harold("King Harold");
    Philosopher lillian("Queen Lillian");

    shrek.LeftFork() = fork1;
    shrek.RightFork() = fork2;

    donkey.LeftFork() = fork2;
    donkey.RightFork() = fork3;

    fiona.LeftFork() = fork3;
    fiona.RightFork() = fork4;

    harold.LeftFork() = fork4;
    harold.RightFork() = fork5;

    lillian.LeftFork() = fork5;
    lillian.RightFork() = fork1;

    // shrek.eat();
    std::thread threadShrek([&](){
        shrek.eat();
    });

    std::thread threadDonkey([&]() {
        donkey.eat();
    });

    std::thread threadFiona([&]() {
        fiona.eat();
    });

    std::thread threadHarold([&]() {
        harold.eat();
    });

    std::thread threadLillian([&]() {
        lillian.eat();
    });

    threadShrek.join();

    threadDonkey.join();

    threadFiona.join();

    threadHarold.join();

    threadLillian.join();

    return 0;
}