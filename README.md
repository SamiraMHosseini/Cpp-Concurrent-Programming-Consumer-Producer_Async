# Concurrent rogramming in C++ using std::condition_variable
The following piece of code utilizes concurrent programming in C++ using std::condition_variable to create a producer and consumer. 
The producer initially sends a value to the consumer and then waits for the modified value from the consumer. 
Meanwhile, the consumer receives the value, modifies it, and sends it back to the producer, thus establishing an infinite loop. 
The aim is to produce sequential consistency.
# What is Async?
In C++ concurrent programming, "async" is a keyword used to initiate an asynchronous operation. An asynchronous operation is one that runs independently of the main program and allows the program to continue executing other tasks in the meantime, instead of waiting for the operation to complete before moving on to the next task.
 

