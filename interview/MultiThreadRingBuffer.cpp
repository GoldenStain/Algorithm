#include <cassert>
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <cstdlib>

// 原代码中的 ConcurrenceQueue 定义在此处
template<typename DATATYPE, typename SEQUENCE = std::deque<DATATYPE>>
class ConcurrenceQueue {
public:
    ConcurrenceQueue() = default;
    
    ConcurrenceQueue(const ConcurrenceQueue & other) {
        std::lock_guard<std::mutex> lg(other.m_mutex);
        m_data = other.m_data;
    }
    ConcurrenceQueue(ConcurrenceQueue &&) = delete;
    ConcurrenceQueue & operator= (const ConcurrenceQueue &) = delete;
    ~ConcurrenceQueue() = default;
    bool empty() const {
        std::lock_guard<std::mutex> lg(m_mutex);
        return m_data.empty();
    }
    
    void push(const DATATYPE & data) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_data.push(data);
        m_cond.notify_one();
    }
    
    void push(DATATYPE && data) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_data.push(std::move(data));
        m_cond.notify_one();
    }
    
    std::shared_ptr<DATATYPE> tryPop() {  // 非阻塞
        std::lock_guard<std::mutex> lg(m_mutex);
        if (m_data.empty()) return {};
        auto res = std::make_shared<DATATYPE>(m_data.front());
        m_data.pop();
        return res;
    }
    
    std::shared_ptr<DATATYPE> pop() {  // 阻塞
        std::unique_lock<std::mutex> lg(m_mutex);
        m_cond.wait(lg, [this] { return !m_data.empty(); });
        auto res = std::make_shared<DATATYPE>(std::move(m_data.front()));
        m_data.pop();
        return res;
    }
    
private:
    std::queue<DATATYPE, SEQUENCE> m_data;
    mutable std::mutex m_mutex;
    std::condition_variable m_cond;
};


// 测试工具函数：打印带时间戳的消息
void log(const std::string& msg) {
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::cout << std::ctime(&t) << " | " << msg << std::endl;
}

// 测试场景1：单线程基础功能
void test_single_thread() {
    log("[Test1] 开始单线程基础测试");
    ConcurrenceQueue<int> q;
    
    // 验证空队列行为
    assert(q.empty());
    assert(q.tryPop() == nullptr);
    
    // 推送数据
    q.push(1);
    q.push(2);
    q.push(3);
    
    // 验证非阻塞弹出
    assert(*q.tryPop() == 1);
    assert(*q.tryPop() == 2);
    
    // 验证阻塞弹出
    assert(*q.pop() == 3);
    assert(q.empty());
    
    log("[Test1] 通过 ✓");
}

// 测试场景2：多线程生产消费
void test_multi_thread() {
    log("[Test2] 开始多线程生产消费测试");
    ConcurrenceQueue<int> q;
    std::atomic<int> counter{0};
    const int TOTAL = 1000;
    const int NUM_PRODUCERS = 2;
    const int NUM_CONSUMERS = 3;
    std::atomic<bool> stop_consumers{false};

    // 生产者线程
    auto producer = [&] {
        for (int i = 0; i < TOTAL; ++i) {
            q.push(i);
            counter.fetch_add(1, std::memory_order_relaxed);
        }
    };

    // 消费者线程（使用 tryPop + 轮询）
    auto consumer = [&] {
        while (!stop_consumers.load()) {
            auto val = q.tryPop(); // 非阻塞弹出
            if (val) {
                counter.fetch_sub(1, std::memory_order_relaxed);
            } else {
                // 短暂休眠避免CPU空转
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    };

    // 启动生产者和消费者
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;
    for (int i = 0; i < NUM_PRODUCERS; ++i) producers.emplace_back(producer);
    for (int i = 0; i < NUM_CONSUMERS; ++i) consumers.emplace_back(consumer);

    // 等待生产者完成
    for (auto& t : producers) t.join();

    // 等待队列清空
    while (!q.empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // 通知消费者停止
    stop_consumers.store(true);

    // 等待消费者完成
    for (auto& t : consumers) t.join();

    // 最终验证
    assert(q.empty());
    assert(counter.load() == 0);
    log("[Test2] 通过 ✓");
}


int main() {
    // 禁用cout同步提升打印性能
    std::ios::sync_with_stdio(false);
    
    test_single_thread();
    test_multi_thread();
    
    log("所有测试通过！");
    return 0;
}
