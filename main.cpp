#include <iostream>
#include <thread>
#include <sstream>
#include <atomic>

#define MAXNUM 1000
//const int MAXNUM = 10;
// std::atomic<int> num(0);

std::string thrid_tostring(std::thread::id thrid ){
    std::stringstream ss;
    ss << thrid;
    return ss.str();
}
struct Atomizer {

    Atomizer(const int& num): count(num) {}

    std::atomic<int> count;

    Atomizer operator++(int) { return Atomizer(count.fetch_add(1)); }
    Atomizer operator--(int) { return Atomizer(count.fetch_sub(1)); }
    Atomizer operator+=(const int& num) { return Atomizer(count.fetch_add(num)); }
    Atomizer operator-=(const int& num) { return Atomizer(count.fetch_sub(num)); }

    void store(const int& num) { return count.store(num); }
    Atomizer load() { return Atomizer(count.load()); }

    std::atomic<int> release() { return count.load(); };
};

Atomizer num(0);

void fincr(){
    std::cout << "#id = " + thrid_tostring(std::this_thread::get_id()) + "\n";
    while(1){
        //while(num < MAXNUM){
        //std::this_thread::sleep_for(1000ms);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if(num.release().load() < MAXNUM){ //CAN THIS COMPARISON BE ATOMIC?
            std::cout << "Number of clients increased from " << num.release().load() << " to " << num.release().load()+2 << "\n"; //THIS HAS TO BE LOCKED TO BE THREAD-SAFE
            num += 2;
        }
    }
}
void fdecr(){
    std::cout << "#id = " + thrid_tostring(std::this_thread::get_id()) + "\n";
    while(1){
        //while(num > 0){
        //std::this_thread::sleep_for(2000ms);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        if(num.release().load() > 0){    //CAN THIS COMPARISON BE ATOMIC?
            std::cout << "Number of clients decreased from " << num.release().load() << " to " << num.release().load()-1 << "\n"; //THIS HAS TO BE LOCKED TO BE THREAD-SAFE
            num--;
        }
    }
}

int main(){

    std::cout << "is std::atomic<int> lock free? - " << std::boolalpha << std::atomic<int>::is_always_lock_free << std::endl;
    std::atomic<int> a(0);
    std::cout << "is num variable lock free? - " << std::boolalpha << a.is_lock_free() << std::endl;

    std::thread t1(fincr);
    std::thread t2(fdecr);
    t2.join();
    t1.join();
}
