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

namespace CVWay {
class CVCount {
public:
  CVCount(int _range) : range(_range) {}

  void printEvenAtomic() {
    for (int i = 0; i < range; i += 2) {
      std::unique_lock<std::mutex> lock(m_lock);
      cv.wait(lock, [&]() { return !(current & 1); });
      std::cout << "CVCount_Even: " << current << std::endl;
      current++;
      cv.notify_all();
    }
  }

  void printOddAtomic() {
    for (int i = 0; i < range; i += 2) {
      std::unique_lock<std::mutex> lock(m_lock);
      cv.wait(lock, [&]() { return (current & 1); });
      std::cout << "CVCount_Odd: " << current << std::endl;
      current++;
      cv.notify_all();
    }
  }

private:
  int current = 0;
  std::condition_variable cv;
  std::mutex m_lock;
  int range;
};

void test_cv(int range) {
	CVCount cv_count = CVCount(50);
	auto t1 = std::thread(&CVCount::printEvenAtomic, &cv_count);
	auto t2 = std::thread(&CVCount::printOddAtomic, &cv_count);
	t1.join();
	t2.join();
}
} // namespace CVWay

int main() {
//   AtomicWay::testAtomic(50);
  CVWay::test_cv(50);
  return 0;
}