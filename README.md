# Concurrent rogramming in C++ using std::condition_variable
The following piece of code utilizes concurrent programming in C++ using std::condition_variable to create a producer and consumer. 
The producer initially sends a value to the consumer and then waits for the modified value from the consumer. 
Meanwhile, the consumer receives the value, modifies it, and sends it back to the producer, thus establishing an infinite loop. 
The aim is to produce sequential consistency.
# What is sequential consistency? 
Sequential consistency is a property of concurrent programs that guarantees that the program's execution appears to be sequentially consistent from the perspective of an external observer, despite being executed concurrently. This means that the execution of a program should be equivalent to some sequential execution of the program in which the operations of all threads are interleaved in a consistent and coherent manner.

C++ supports concurrent programming with features like threads, mutexes, condition variables, and atomic variables. These features allow developers to write programs that can execute multiple tasks concurrently. However, when multiple threads access shared data, it is essential to ensure that the accesses are synchronized in a way that ensures sequential consistency.

In C++, sequential consistency can be achieved through the use of atomic variables and memory barriers. Atomic variables provide a way to ensure that a variable is modified atomically, and memory barriers provide a way to enforce an order of operations between threads.

In summary, C++ concurrent programming refers to the ability to execute multiple tasks concurrently, while sequential consistency is a property that guarantees that the program's execution appears to be sequentially consistent from the perspective of an external observer, despite being executed concurrently.
 

