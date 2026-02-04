#include <thread>
#include <iostream>
#include <mutex> 
#include <future>

int fun(int i) {
    std::cout << "Fun" << i << std::endl;
    return i;
}

void fun2(void) {
    std::cout << "Fun2" << std::endl;
}

class MyFun {
public:
    void operator()(void);
};

void MyFun::operator()(void) {
    std::cout << "MyFun" << std::endl;
}


class Counter {
    int val = 0;
    std::mutex m;
public:
    int get(void) const {return val;}
    void incr(void);
};

void Counter::incr(void) {
    //m.lock(); //problem, jak bedziemy rzucac wyjatek, albo return, bo unlock sie nie wywola
    std::scoped_lock lock(m);
    ++val;
    //m.unlock();
}

int main(void) {
    MyFun f;
    int w;
    Counter c;
 
    std::future<int> result = std::async(std::launch::async, fun, 5);
    std::cout << "Future " << result.get() << std::endl;


    std::thread t1(fun, 1);
    std::thread t2(fun2);
    std::thread t3(f);
    std::thread t4([]()->void {std::cout << "Lambda" << std::endl;});
    std::thread t5([](int a)->void {std::cout << "Lambda" << a << std::endl;}, 1);
    std::thread t6([&w](int a)->void {w = a + 5; std::cout << "w= " << w << std::endl;}, 2);
    std::thread t7([&c](int N) {while(N) {c.incr(); N--;}}, 10000);
    std::thread t8([&c](int N) {while(N) {c.incr(); N--;}}, 1000);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    std::cout << c.get() << std::endl;
    return 0;
}
