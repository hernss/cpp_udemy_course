#include <iostream>
#include <list>
#include <thread>
#include <string>
#include <mutex>
#include <Windows.h>
#include <future>

std::list<int> g_data;


std::list<int> data;
std::mutex g_mutex;

const int MAXSIZE = 50000;

class String {
public:
	String() {
		std::cout << "String()" << std::endl;
	}
	~String() {
		std::cout << "~String()" << std::endl;
	}
	String(const String&) {
		std::cout << "String(const String&)" << std::endl;
	}

	String & operator=(const String &) {
		std::cout << "operator=(const String&)" << std::endl;
		return *this;
	}
};





void Download(String &file) {
	//std::cout << "[DOWNLOADER] Started download file: " << file << std::endl;
	std::cout << "[DOWNLOADER] Started download" << std::endl;
	for (int i = 0; i < MAXSIZE; i++)
		g_data.push_back(i);

	std::cout << "[DOWNLOADER] Finished Download" << std::endl;
}


// Mutex example function
/*
void Download_1() {
	for (int i = 0; i < MAXSIZE; i++) {
		g_mutex.lock();
		data.push_back(i);
		g_mutex.unlock();
	}

}

void Download_2() {
	for (int i = 0; i < MAXSIZE; i++) {
		g_mutex.lock();
		data.push_back(i);
		g_mutex.unlock();
	}
}
*/


//Lock guard example
void Download_1() {

	std::cout << "Process id: " << std::this_thread::get_id() << std::endl;



	for (int i = 0; i < MAXSIZE; i++) {
		std::lock_guard<std::mutex> mtx(g_mutex);
		data.push_back(i);
		if (i == 500)
			break;		//No deadlock is produced
	}

}

void Download_2() {
	for (int i = 0; i < MAXSIZE; i++) {
		std::lock_guard<std::mutex> mtx(g_mutex);
		data.push_back(i);
	}
}

void Process() {
	using namespace std::chrono_literals;
	for (int i = 0; i < 10; i++) {
		std::this_thread::sleep_for(300ms); // std::chrono::seconds(100)
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

int Operation(int count) {
	using namespace std::chrono_literals;
	int sum{};
	for (int i = 0; i < count; i++) {
		std::this_thread::sleep_for(300ms); // std::chrono::seconds(100)
		std::cout << i << " ";
		sum += i;
	}
	std::cout << std::endl;
	return sum;
}

int Operation2(std::promise<int>& prom) {
	using namespace std::chrono_literals;
	int sum{};
	auto f = prom.get_future();
	try {
		std::cout << "[TASK] Waiting for data...\n";
		auto count = f.get();
		std::cout << "[TASK] Data received" << std::endl;
		for (int i = 0; i < count; i++) {
			std::this_thread::sleep_for(300ms); // std::chrono::seconds(100)
			std::cout << i << " ";
			sum += i;
		}
		std::cout << std::endl;
		return sum;
	}
	catch (std::exception& ex) {
		std::cout << "[TASK] Exception: " << ex.what() << std::endl;
		return -1;
	}
}

int main() {
	/*
	//std::string filename{ "cppcast.mp4" };
	String filename;
	std::cout << "[MAIN] User started an operation" << std::endl;

	// Download(); //Bloquea el hilo principal

	std::thread thDownloader(Download, std::ref(filename));

	std::cout << "[MAIN] User started another operation" << std::endl;


	//thDownloader.detach(); // Separa el hilo del programa principal. Libera los recursos cuando termina  la ejecucion, no se puede joinear por eso hay que preguntar joinable()

	if(thDownloader.joinable())
		thDownloader.join();
	*/
	/*
	//Mutex example
	std::thread thDownload_1(Download_1);
	std::thread thDownlaod_2(Download_2);

	auto id = thDownload_1.get_id();
	std::cout << "Thread id: " << id << std::endl;

	//ONLY FOR WINDOWS 10+
	HANDLE handle = thDownload_1.native_handle();

	SetThreadDescription(handle, L"MyThread");

	int cores = std::thread::hardware_concurrency();

	std::cout << "Number of cores: " << cores << std::endl;

	thDownload_1.join();
	thDownlaod_2.join();

	std::cout << "Global data count: " << data.size() << std::endl;

	*/
	/*
	std::thread thProcess(Process);

	thProcess.join();
*/
	/*
	std::future<void> result = std::async(Process); // void ahi va el return de la funcion que ejecuta el task
													// Por defecto los parametros se pasan por valor, si queres pasar por referencia hay que usar std::ref
													// 
	*/
	using namespace std::chrono_literals;


	/*
	std::future<int> result = std::async(std::launch::async, Operation, 10);			// Si launch policy es std::launch::deferred se ejecuta cuando se llama al result.get() de manera sincronica

	std::this_thread::sleep_for(1s);

	std::cout << "Main thread" << std::endl;

	//result.wait();	//wait() espera que se termina la ejecucion pero no devuelve nada. 

	auto timepoint = std::chrono::system_clock::now();
	timepoint += 1s;

	auto status = result.wait_until(timepoint);
	//auto status = result.wait_for(1s);
	switch (status) {
	case std::future_status::deferred:
		std::cout << "Task is synchronous" << std::endl;
		break;
	case std::future_status::ready:
		std::cout << "Task is ready" << std::endl;
		break;
	case std::future_status::timeout:
		std::cout << "Task is timeout" << std::endl;
		break;	
	
	}


	if (result.valid()) {
		
		auto sum = result.get();
		std::cout << "La suma es: " << sum << std::endl;
	}

	*/


	std::promise<int> data;

	std::future<int> result = std::async(std::launch::async, Operation2, std::ref(data));
	std::this_thread::sleep_for(1s);

	std::cout << "[MAIN] Main function running" << std::endl;

	try {
		throw std::runtime_error{ "Data not available" };
		
		data.set_value(10);

		if (result.valid()) {
			auto sum = result.get();
			std::cout << "[MAIN] La suma es: " << sum << std::endl;
		}
	}
	catch (std::exception& ex) {
		data.set_exception(std::make_exception_ptr(ex));
	}




	return 0;
}