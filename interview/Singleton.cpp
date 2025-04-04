#include <iostream>

class EagerSingleton {
   public:
    static EagerSingleton& getInstance() { return instance_; }
    void work() { std::cout << "EagerSingleton is working ..." << std::endl; }
    EagerSingleton(const EagerSingleton&) = delete;             // 拷贝构造
    EagerSingleton& operator=(const EagerSingleton&) = delete;  // 拷贝赋值
   private:
    EagerSingleton() {
        std::cout << "creating a EagerSingleton. " << std::endl;
    }
    ~EagerSingleton() {
        std::cout << "Destroying a EagerSingleton." << std::endl;
    }
    static EagerSingleton instance_;
};

EagerSingleton EagerSingleton::instance_;

class LazySingleton {
   public:
    static LazySingleton& getInstance() {
        static LazySingleton instance_;
        return instance_;
    }
    void work() {
        std::cout << "LazySingleton is working ..." << std::endl;
    }
    LazySingleton(const LazySingleton&) = delete;
    LazySingleton& operator=(const LazySingleton&) = delete;
   private:
    LazySingleton() {
        std::cout << "creating a LazySingleton. " << std::endl;
    }
    ~LazySingleton() {
        std::cout << "Destroying a LazySingleton. " << std::endl;
    }
};

int main() {
    LazySingleton& lazy = LazySingleton::getInstance();
}