#include <iostream>
#include <memory>
#include <stack>

class MinStack {
public:
    MinStack() {}
    
    void push(int val) {
        _normal_stack.push(val);
        if(_min_stack.empty() || val <= _min_stack.top()) 
            _min_stack.push(val);
    }
    
    void pop() {
        int result = _normal_stack.top();
        _normal_stack.pop();
        if(result == _min_stack.top())
            _min_stack.pop();
    }
    
    int top() {
        return _normal_stack.top();
    }
    
    int getMin() {
        return _min_stack.top();
    }
private:
    std::stack<int> _normal_stack, _min_stack;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */