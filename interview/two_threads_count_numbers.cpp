#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

namespace AtomicWay {
// 注意循环里面是i+=2，因为每个分别负责偶数奇数
void printEvenAtomic(int range, std::atomic<bool> &turn) {
  for (int i = 0; i < range; i += 2) {
    while (turn.load(std::memory_order_acquire)) {
    }
    std::cout << "Even thread: " << i << std::endl;
    turn.store(true, std::memory_order_release);
  }
}

void printOddAtomic(int range, std::atomic<bool> &turn) {
  for (int i = 1; i < range; i += 2) {
    while (!turn.load(std::memory_order_acquire)) {
    }
    std::cout << "Odd thread: " << i << std::endl;
    turn.store(false, std::memory_order_release);
  }
}

void testAtomic(int range) {
  std::atomic<bool> turn(false);
  // 这里要使用std::ref显式传递引用
  std::thread t1 = std::thread(&printEvenAtomic, range, std::ref(turn));
  std::thread t2 = std::thread(&printOddAtomic, range, std::ref(turn));
  t1.join();
  t2.join();
}
} // namespace AtomicWay

int main() {
  AtomicWay::testAtomic(50);
  return 0;
}