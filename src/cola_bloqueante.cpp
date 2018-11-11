#include "cola_bloqueante.h"

ColaBloqueante::ColaBloqueante(const unsigned int max_size) : 
max_size(max_size) {}
        
void ColaBloqueante::push(const std::string& val) {
    std::unique_lock<std::mutex> lock(mutex);

    if (q.empty()) {
        is_not_empty.notify_all();
    }

	while (q.size() >= this->max_size) {
	   //cola llena se bloquea
		is_not_full.wait(lock);
	}

    q.push(val);
} 

std::string ColaBloqueante::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    while (q.empty()) {
        std::cout << " cola vacia, el pull se bloquea\n";
        is_not_empty.wait(lock);
    }

    const std::string val = q.front();
    q.pop();

    is_not_full.notify_all();

    return val;
}