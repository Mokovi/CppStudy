#include <iostream>
/*
    C++的并行与并发
一、基础概念
    并发（Concurrency）
        指的是程序中多个任务可以在逻辑上同时启动、交替执行。并发的关键在于任务之间“互相切换”，并不要求同时在多个 CPU 上真正“同时”运行。常见应用场景包括 I/O 密集型程序、事件驱动系统等。
    并行（Parallelism）
        指的是在多核或多处理器系统上，同时运行多个任务，实现真正的同时执行。并行通常用于计算密集型任务，通过分解问题，将工作分配给多个线程或进程同时计算，从而提高性能。
    同步（Synchronous）
        调用者在发起任务后必须等待任务完成后才能继续执行后续代码。这种模式下，任务执行是阻塞的，直到结果返回。
    异步（Asynchronous）
        调用者在发起任务后不需要等待任务完成，可以立即继续执行其它操作。任务在后台执行，完成后会以某种方式通知调用者（例如通过回调函数、future/promise 等机制）
*/

/*
二、线程（Thread）
        std::thread 用于创建一个执行的线程实例，所以它是一切并发编程的基础，使用时需要包含 <thread> 头文件，
它提供了很多基本的线程操作，例如 get_id() 来获取所创建线程的线程 ID，使用 join() 来等待一个线程结束
    1. std::thread::join()
        作用：
            调用 join() 会使调用该函数的线程（通常是主线程）阻塞，直到目标线程执行结束。也就是说，它等待被 join 的线程完成，然后继续后续代码执行。
        使用场景：
            当你需要保证所有工作线程在主线程退出之前都完成工作，或需要同步结果时，应该使用 join()。
        特点：
            一旦线程被 join，该 std::thread 对象变为不可 join（non-joinable）。
            如果未调用 join 或 detach，程序析构线程对象时会抛出异常（通常为 std::terminate()）。

    2. std::thread::detach()
        作用：
            调用 detach() 会将线程与其 std::thread 对象分离，使线程在后台独立执行。分离后，线程不再受当前线程对象的控制，而是成为一个“守护线程”，它在结束时会自动释放资源。
        使用场景：
            当你不需要等待线程完成，或者线程执行与主线程的后续操作无关时，可以使用 detach()。例如，后台日志写入、定时任务等。
        特点：
            一旦线程被 detach，线程对象不再与线程相关联（称为非 joinable）。
            分离后的线程与主线程独立执行，主线程不能再同步或获取其返回值。
            使用 detach 后，必须确保线程的生命周期内所使用的所有资源仍然有效，否则可能会出现访问已销毁对象的风险。
*/
#include <thread>
void task(){
    std::cout << "hello world." << std::endl;
}
void testThread(){
    std::thread t(task);
    t.join();
}

/*
三、互斥量
    std::mutex 是 C++11 中最基本的互斥量类其，所有相关的函数都放在 <mutex> 头文件中，可以通过构造 std::mutex 对象创建互斥量，
而通过其成员函数 lock() 可以进行上锁，unlock() 可以进行解锁。但是在实际编写代码的过程中，最好不去直接调用成员函数，因为调用成员
函数就需要在每个临界区的出口处调用 unlock()，当然，还包括异常。
    而 C++11 为互斥量提供了一个 RAII 机制的模板类 std::lock_guard、std::unique_lock
    1.std::lock_guard 
        描述
            是一个简单的、轻量级的互斥量管理器。它在构造时自动锁定给定的互斥量，并在析构时自动释放锁，从而确保在作用域结束时锁一定被释放。
        使用场景：
            当你只需要在某个代码块内加锁，并且不需要在该块内有解锁或重新加锁的需求时，std::lock_guard 是最佳选择。由于其简单性，通常没有额外的性能开销。
    2.std::unique_lock
        基本特性：
            std::unique_lock 提供了比 std::lock_guard 更高的灵活性，除了在构造时自动加锁和析构时自动解锁之外，它还支持：
                延迟加锁：可以在构造时不立即加锁，而后通过调用 lock() 手动加锁。
                提前解锁：允许在作用域内调用 unlock() 释放锁，然后可以在需要时再次调用 lock()。
                条件变量配合：在等待条件变量时通常需要传入 std::unique_lock，因为条件变量会在等待时自动释放锁，再在唤醒后重新加锁。
                可移动性：std::unique_lock 支持移动构造和移动赋值，这使得你可以将锁的所有权转移到其他对象中。
*/
#include <mutex>
int num1 = 0;
int num2 = 0;
std::mutex mtx;

void taskPlus(){
    for(int i = 0; i < 100000; i++){
        num1++;
    }
}
void taskMinus(){
    for(int i = 0; i < 100000; i++){
        num1--;
    }
}
void taskPlus2(){
    std::lock_guard<std::mutex> lock(mtx);
    for(int i = 0; i < 100000; i++){
        num2++;
    }
}
void taskMinus2(){
    std::lock_guard<std::mutex> lock(mtx);
    for(int i = 0; i < 100000; i++){
        num2--;
    }
}
void testMutex(){
    std::thread t1(taskPlus), t2(taskMinus);
    t1.join();
    t2.join();
    std::cout << "num1 = " << num1 << std::endl; //结果不确定，因为++，--均原子性操作，需要用锁

    std::thread t3(taskPlus2), t4(taskMinus2);
    t3.join();
    t4.join();
    std::cout << "num2 = " << num2 << std::endl;
}
/*
四、条件变量
    1. 概念
        条件变量 std::condition_variable 是为了解决死锁而生，当互斥操作不够用而引入的。比如，线程可能需要等待某个条件为真才能继续执行。而一个忙等待循环中可能
    会导致所有其他线程都无法进入临界区使得条件为真时，就会发生死锁。
    2. 核心成员函数
            函数	                    说明
        wait(lock)	            释放锁并阻塞线程，直到被唤醒。需配合循环检查条件。
        wait(lock, predicate)	自动检查谓词（条件），避免虚假唤醒。等价于 while (!pred) wait(lock)。
        notify_one()	        唤醒一个等待的线程（若有多个线程等待，随机选择一个）。
        notify_all()	        唤醒所有等待的线程。
    3. 使用步骤
        a.定义条件变量与互斥量
                #include <mutex>
                #include <condition_variable>

                std::mutex mtx;
                std::condition_variable cv;
                bool ready = false; // 共享条件

        b.等待条件的线程
                void waiting_thread() {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, []{ return ready; }); // 等待条件为 true
                    // 条件满足后，继续执行任务...
                }
        c.修改条件并通知的线程
                void notifying_thread() {
                    {
                        std::lock_guard<std::mutex> lock(mtx);
                        ready = true; // 修改条件
                    }
                    cv.notify_one(); // 发送通知
                }
    4. 关键机制与注意事项
        a. 虚假唤醒（Spurious Wakeup）
            现象：线程可能在没有收到 notify 的情况下被唤醒。
            解决方案：始终在 wait 中使用 谓词（Predicate） 循环检查条件。
                cv.wait(lock, []{ return ready; }); // 自动处理虚假唤醒
        b. 锁与条件变量的关系
            必须持有锁：在检查或修改条件时，必须通过互斥量保护共享数据。
            wait 的锁释放：调用 wait 时，线程会释放锁并进入阻塞状态；被唤醒后重新获取锁。
        c. 通知时是否需要持有锁？
            建议持有锁：在修改条件时持有锁，确保修改和通知的原子性，避免竞态条件。
    5.注意事项
        a. 使用 wait_for 或 wait_until 设置等待超时时间
                std::unique_lock<std::mutex> lock(mtx);
                if (cv.wait_for(lock, std::chrono::seconds(1), []{ return ready; })) {
                    // 条件在 1 秒内满足
                } else {
                    // 超时处理
                }
        b. 结合 std::atomic
                std::atomic<bool> ready(false);

                void waiter() {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [&]{ return ready.load(); }); // 原子读取
                }
*/
//生产者-消费者模型
#include <queue>
#include <condition_variable>

std::mutex mtx_pc;
std::condition_variable cv_producer, cv_consumer;
std::queue<int> data_queue;
const int MAX_SIZE = 10;

void producer(int id){
    for (int i = 0; i < 200; i++){
        std::unique_lock<std::mutex> ulock(mtx_pc);
        cv_producer.wait(ulock,[](){return data_queue.size() < MAX_SIZE;});//数据队列未满时，执行
        data_queue.push(i);
        std::cout << "Producer " << id << " produced " << i << std::endl;
        ulock.unlock();//主动解锁
        cv_consumer.notify_one(); // 通知消费者
    }
}

void consumer(int id){
    while (true) {
        std::unique_lock<std::mutex> lock(mtx_pc);
        cv_consumer.wait(lock, []{ return !data_queue.empty(); }); // 等待队列非空
        int data = data_queue.front();
        data_queue.pop();
        std::cout << "Consumer " << id << " consumed " << data << std::endl;
        lock.unlock();
        cv_producer.notify_one(); // 通知生产者
    }
}

void testProducerConsumer(){
    std::thread p1(producer, 1);
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);
    p1.join();
    c1.detach();
    c2.detach();
}
/*
五、期物 std::future
    1. 背景
        使用thread调用的线程函数返回值只能是void类型，在有future之前，若使用在多线程同步处理任务的流程是：创建一个线程 A，在线程 A 里启动任务 B，当准备完毕后发送一个事件，并将结果保存在全局变量中。
而主函数线程 A 里正在做其他的事情，当需要结果的时候，调用一个线程等待函数来获得执行的结果。而 std::future，它提供了一个访问异步操作结果的途径。
    2. 核心类
        a. std::future
            核心功能：
                std::future<T> 用于异步地获取某个任务的返回值或异常。它充当“期物”，代表未来某个时刻可用的值。
            主要成员函数：
                get()：阻塞当前线程，直到异步任务完成，然后返回任务结果；如果任务抛出异常，则 get() 会重新抛出异常。
                wait()、wait_for()、wait_until()：等待异步结果就绪，但不返回结果。可设置等待时长或截止时间。
                valid()：检查 future 是否关联了一个异步任务。
        b. std::async
            核心功能：
                std::async 用于启动异步任务，它自动决定是否以新的线程执行或延迟执行（取决于传入的执行策略），并返回一个与任务关联的 std::future<T> 对象。
            主要特点：
                自动管理线程：调用后返回 future，无需手动管理线程 join/detach（除非你需要额外控制）。
                执行策略：可以指定 std::launch::async（强制异步执行）或 std::launch::deferred（延迟执行，直到 future.get() 被调用）。
                异常传播：如果任务内部抛出异常，future.get() 会重新抛出该异常。
        c. std::promise
            核心功能：
                std::promise<T> 提供了一种写入（设置）异步任务结果的方式，与 std::future<T> 搭配使用。promise 是“生产者”，
            而 future 是“消费者”。promise 允许你在任意线程中将结果或异常传递给 future。
            主要成员函数：
                set_value(const T& value) / set_value_at_thread_exit(value)：设置任务成功完成后的返回值。
                set_exception(std::exception_ptr p)：设置任务在执行过程中遇到的异常。
                get_future()：获取与 promise 关联的 future，从而在其他线程中等待和获取结果。
        d. std::packaged_task
            核心功能：
                std::packaged_task<T(Args...)> 用于封装一个可调用对象（函数、lambda 或函数对象），使其能够异步执行，并生成一个 std::future<T> 来接收返回值。它本质上将任务与 future 绑定。
            主要成员函数：
                operator()：调用内部封装的可调用对象，执行任务，并将结果存储到关联的 future 中。
                get_future()：返回与该任务关联的 future 对象，供调用者获取任务结果或异常。
            使用场景：
                当你希望把一个现有的可调用对象封装成一个异步任务，并能通过 future 获取结果时，std::packaged_task 非常适用。
            你可以选择通过 std::thread 显式地启动任务，也可以用 std::async 来间接调用（不过后者一般直接用 std::async 更简单）。
    3. 注意事项
        a. get() 只能调用一次，否则抛出 std::future_error
        b. 使用promise获取的future，在使用get()时，是无法直接catch到线程内直接throw的异常的，需要通过promise转发
        c. std::promise 与 std::packaged_task 都无法复制，thread中使用时，需要通过std::move进行移动操作


*/
//1.future与async结合
#include <future>
#include <chrono>
int computeAnswer(int x){
    if (x == 0) throw std::runtime_error("division can not be zero!");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 100/x;
}
void testAsync(){
    // 使用 std::async 启动异步任务，并返回一个 future 对象
    std::future<int> fut = std::async(std::launch::async, computeAnswer, 0);
    std::cout << "wait for compute...." << std::endl;
    try{
        int answer = fut.get();//阻塞在此，且只能调用一次。
        std::cout << "Answer = " << answer << std::endl;
    }
    catch(std::runtime_error& e){
        std::cerr << "error : " << e.what() << std::endl;
    }
    catch(std::exception& e){
        std::cerr << "standard : " << e.what() << std::endl;
    }
    catch(...){
        std::cerr << "unexpected error!" << std::endl;
    }
}

//2.future与promise结合,使用thread调用线程
void computeAnswer2(std::promise<int> pro, int x){
    try
    {
        if(x == 0) throw std::runtime_error("division can not be zero!");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        pro.set_value(100/x);
    }
    catch(...)
    {
        pro.set_exception(std::current_exception());//将异常打包回主线程处理
        //此时future是通过promise获取的，只能通过这种方式移动异常，直接throw,主线程无法catch
    }
}
void testPromise(){
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();//将promise与future绑定
    std::thread(computeAnswer2,std::move(prom),0).detach();//promise不能赋值，只能移动
    try{
        int answer = fut.get();//阻塞在此，且只能调用一次。
        std::cout << "Answer = " << answer << std::endl;
    }
    catch(std::runtime_error& e){
        std::cerr << "error : " << e.what() << std::endl;
    }
    catch(...){
        std::cerr << "unexpected error!" << std::endl;
    }
}
//3.future 与 std::packaged_task 结合
//直接借用computeAnswer函数
void testPackageTask(){
    std::packaged_task<int(int)> task(computeAnswer);
    std::future<int> fut = task.get_future();
    std::thread(std::move(task), 0).detach();//与std::promise相同，std::packaged_task也只能移动
    std::cout << "wait for compute...\n";
    try{
        int answer = fut.get();//阻塞在此，且只能调用一次。
        std::cout << "Answer = " << answer << std::endl;
    }
    catch(std::runtime_error& e){
        std::cerr << "error : " << e.what() << std::endl;
    }
    catch(...){
        std::cerr << "unexpected error!" << std::endl;
    }
}
//4.超时处理
void testOuttime(){
    std::packaged_task<int()> task([](){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 0;
    });
    std::future<int> fut = task.get_future();
    std::thread(std::move(task)).detach();
    auto status = fut.wait_for(std::chrono::seconds(2));
    if(status == std::future_status::ready){
        std::cout << "Answer = " << fut.get() << std::endl;
    }
    else if (status == std::future_status::timeout){
        std::cout << "Time out!\n";
    }
}
/*
六、内存顺序与原子操作
    1. 概念补充
        a. 内存模型：
                描述在多线程环境下，程序中不同线程如何对共享内存进行读写操作以及这些操作如何被观察到。它规定了哪些操作“发生前”（happens-before）关系，
            即一个操作的结果必须在另一个操作之前可见，从而保证程序正确性。
        b. 重排序：
                编译器和处理器为了提高性能可能会对指令进行重排序，但只要不破坏“可观察行为”，单线程程序就不会出现问题。而在多线程环境下，如果没有同步机制，
            不同线程看到的操作顺序可能会不一致，导致数据竞争。
        c. volatile
                volatile 告诉编译器某个变量的值可能在程序之外（如硬件或其他线程）的影响下发生变化，因此编译器不应对其进行优化（比如缓存变量值），每次访问
            该变量时都应重新从内存中读取。
        d. assert 宏
            a)assert 定义在头文件 <cassert>（在 C 中为 <assert.h>）用于在调试阶段检测程序中某个关键条件是否成立。如果条件为 false，assert 会打印错误信
            息（通常包括文件名、行号和条件表达式），然后调用 abort() 终止程序。
            b)在调试模式下（没有定义 NDEBUG 宏），assert 会进行检查。如果定义了 NDEBUG（通常在发布版本中定义），则 assert 会被编译器忽略，不产生任何代码，从而不会影响性能。
    2. 原子操作
        a. 概念
            原子性：一个操作不可被中断，要么完全执行，要么完全不执行。
            线程安全：多线程环境下对原子变量的操作无需额外锁机制。
        b. std::atomic
            a) 支持类型 int、bool、指针等，可以通过std::atomic<T>::is_lock_free 来检查该原子类型是否需支持原子操作。
            b) 常用成员函数
                load()：​以原子方式读取并返回当前值。
                store(value)：​以原子方式将指定值存储到原子对象中
                exchange(value)：​以原子方式将指定值存储到原子对象中，并返回之前的值
                compare_exchange_strong(expected, desired)：​以原子方式比较并交换值
                        std::atomic<int> atomicInt(50);
                        int expected = 50;
                        bool success = atomicInt.compare_exchange_strong(expected, 60);
                        // 如果 atomicInt 的值是 50，则被设置为 60，success 为 true
                        // 否则，expected 被更新为 atomicInt 的当前值，success 为 false
                fetch_add(value)：​以原子方式将指定值加到当前值，并返回之前的值
                fetch_sub(value)：​以原子方式从当前值减去指定值，并返回之前的值
                fetch_and(value)：​以原子方式对当前值与指定值进行按位与操作，并返回之前的值
                fetch_or(value)：​以原子方式对当前值与指定值进行按位或操作，并返回之前的值
                fetch_xor(value)：​以原子方式对当前值与指定值进行按位异或操作，并返回之前的值
                此外还重载了=，++，--等
    3. 内存顺序
            内存顺序	                        说明
            memory_order_relaxed	仅保证原子性，无顺序约束（性能最高，安全性最低）。
            memory_order_consume	依赖当前操作的后续操作需在该操作之后执行（已弃用，不推荐使用）。
            memory_order_acquire	当前操作后的读/写必须在该操作之后执行（用于“获取”操作）。
            memory_order_release	当前操作前的读/写必须在该操作之前执行（用于“释放”操作）。
            memory_order_acq_rel	同时具有 acquire 和 release 语义（用于“读-改-写”操作）。
            memory_order_seq_cst	顺序一致性（默认），全局操作顺序一致（性能最低，安全性最高）。
*/
#include <atomic>
#include <assert.h>
#include <vector>
//测试重排序
void testReorder(){
    const int MAX_SIZE = 10;
    int x[MAX_SIZE] = {0};
    volatile int flag[MAX_SIZE] = {0};
    std::vector<std::thread> tasks1, tasks2;

    for (int i = 0; i < MAX_SIZE; i++){
        tasks1.emplace_back(std::thread([&,i](){
            x[i] = 40;
            flag[i] = 1;
        }));
        tasks2.emplace_back(std::thread([&,i](){
            while(!flag[i]);
            assert(x[i] != 0);
        }));
    }
    for (auto& task : tasks1){
        task.join();
    }
    for (auto& task : tasks2){
        task.join();
    }
}
//1.relax顺序
void testRelaxed(){
    const int MAX_SIZE = 10000;
    std::vector<std::atomic<int>> x(MAX_SIZE);
    std::vector<std::atomic<int>> y(MAX_SIZE);
    std::vector<std::thread> tasks1, tasks2;

    for (int i = 0; i < MAX_SIZE; i++){
        tasks1.emplace_back(std::thread([&,i](){
            x[i].store(1,std::memory_order_relaxed);
            y[i].store(1,std::memory_order_relaxed);
        }));
        tasks2.emplace_back(std::thread([&,i](){
            if(y[i].load(std::memory_order_relaxed))
            {
                assert(x[i].load(std::memory_order_relaxed) == 1);
            }
        }));
    }
    for (auto& task : tasks1){
        task.join();
    }
    for (auto& task : tasks2){
        task.join();
    }
}

//2.使用acquire与release配合
void testAcuRel(){
    const int MAX_SIZE = 10;
    std::vector<std::atomic<int>> x(MAX_SIZE);
    std::vector<std::atomic<int>> y(MAX_SIZE);
    std::vector<std::thread> tasks1, tasks2;

    for (int i = 0; i < MAX_SIZE; i++){
        tasks1.emplace_back(std::thread([&,i](){ //i只能值捕获
            x[i].store(1,std::memory_order_relaxed);
            y[i].store(1,std::memory_order_release);
        }));
        tasks2.emplace_back(std::thread([&,i](){
            if(y[i].load(std::memory_order_acquire))
            {
                assert(x[i].load(std::memory_order_relaxed) == 1);
            }
        }));
    }
    for (auto& task : tasks1){
        task.join();
    }
    for (auto& task : tasks2){
        task.join();
    }
}


int main(){
    //testThread();
    //testMutex();
    //testProducerConsumer();
    //testAsync();
    //testPromise();
    //testPackageTask();
    //testOuttime();
    //testReorder();
    testRelaxed();
    //testAcuRel();
    return 0;
}

