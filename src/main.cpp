#include <string>
#include <chrono>
#include <iostream>
#include <list>
#include <vector>

class TimeMeasurement
{
	std::string name;
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	
public:
	TimeMeasurement(std::string _name) : name(_name) {
		start = std::chrono::high_resolution_clock::now();
	}
	
	~TimeMeasurement() {
		std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		std::cout << name << ": " << duration.count() << " sec" << std::endl;
	}
};

int main()
{
	{
        std::vector<int> container = {};
        TimeMeasurement t("Element addition (Vector)");
        for (int i = 0; i < 100000; i++) {
            container.insert(container.begin(), 123456);
        }
    }
    {
        std::list<int> container = {};
        TimeMeasurement t("Element addition (List)");
        for (int i = 0; i < 100000; i++) {
            container.insert(container.begin(), 123456);
        }
    }

    {
        std::vector<int> container(100000, 1);
        long sum = 0;
        TimeMeasurement t("Cache friendliness (Vector)");
        for (int element : container) {
            sum += element;
        }
    }
    {
        std::list<int> container(100000, 1);
        long sum = 0;
        TimeMeasurement t("Cache friendliness (List)");
        for (int element : container) {
            sum += element;
        }
    }

	return 0;
}
