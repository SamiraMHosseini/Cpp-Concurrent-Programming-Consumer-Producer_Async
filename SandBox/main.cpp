struct SharedResource
{
	SharedResource() :
		mtx(), condVar(), flag(false), counter(0xA)
	{

	}
	std::mutex mtx;
	std::condition_variable condVar;
	bool flag;
	unsigned int counter;
};
class Consumer : public BannerBase
{

public:
	Consumer() = delete;
	Consumer(const Consumer&) = default;
	Consumer& operator=(const Consumer&) = default;
	~Consumer() = default;
	Consumer(const char* const name) :
		BannerBase(name), name(name)
	{

	}
	void operator ()(SharedResource& sharedResource) //Functor 
	{
		START_BANNER;
		Debug::SetCurrentName(name);
		while (true)
		{
			std::unique_lock<std::mutex> lock(sharedResource.mtx);
			//The predicate version (2) returns pred(), 
			//regardless of whether the timeout was triggered (although it can only be false if triggered).
			if (sharedResource.condVar.wait_for(lock, 2s,

				[&]()->bool {  return sharedResource.flag; }))

				//The following line of code is executed only if the function pred() returns a boolean value of true 
				//regardless of whether the timeout was triggered. However, it can only be false if timeout is triggered
			{

				Debug::out("I have received 0x%X from the Producer \n", sharedResource.counter);
				sharedResource.counter = (sharedResource.counter * 2) + 1;
				sharedResource.flag = false;
				Debug::out("I am  sending 0x%X to the Producer \n", sharedResource.counter);

			}
			else

			{
				//Once notified or once rel_time has passed, 
				//the function unblocksand calls lck.lock(), leaving lck in the same state as when the function was called.
				Debug::out("I am waiting for the Producer...\n");

			}


		}

	}

private:

	const char* const name;
};

class Producer : public BannerBase
{
public:

	Producer() = delete;
	Producer(const Producer&) = default;
	Producer& operator=(const Producer&) = default;
	~Producer() = default;
	Producer(const char* const name) :
		BannerBase(name), name(name)

	{

	}
	void operator() (SharedResource& sharedResource) // Function object
	{
		START_BANNER;
		Debug::SetCurrentName(name);
		Initiate(sharedResource);
		while (true)
		{

			std::unique_lock<std::mutex> lock(sharedResource.mtx);
			if (sharedResource.condVar.wait_for(lock, 2s,
				[&]()->bool
				{
					return !(sharedResource.flag);
				}

			))
				//The following line of code is executed only if the function pred() returns a boolean value of true 
				//regardless of whether the timeout was triggered. However, it can only be false if timeout is triggered
			{

				Debug::out("I have received 0x%X from the Consumer\n", sharedResource.counter);
				sharedResource.counter = (sharedResource.counter / 2) + 1;
				sharedResource.flag = true;
				Debug::out("I am sending 0x%X to the Consumer\n", sharedResource.counter);
			}
			else
			{
				//Once notified or once rel_time has passed, 
				//the function unblocksand calls lck.lock(), leaving lck in the same state as when the function was called.
				//lock.lock(); This line will cause run-time error! we can't lock a simple type lock that's already locked! 
				Debug::out("I am waiting for the Consumer...\n");

			}

		}

	}
	void Initiate(SharedResource& sharedResource)
	{
		std::unique_lock<std::mutex> lock(sharedResource.mtx);
		Debug::out("I am sending 0x%X to the Consumer\n", sharedResource.counter);
		sharedResource.flag = true;
	}
private:
	const char* const name;
};

int main()
{
	START_BANNER_MAIN("main");
	SharedResource sharedResource;
	Consumer consumer("Consumer");
	Producer producer("Producer");
	std::future<void> taskA = std::async(std::launch::async, consumer, std::ref(sharedResource));
	std::future<void> taskB = std::async(std::launch::async, producer, std::ref(sharedResource));

}