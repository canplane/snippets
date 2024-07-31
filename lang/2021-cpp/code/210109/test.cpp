#include <iostream>

class Marine {
    static int total_marine_num;
    
    public:
        Marine();
        ~Marine() { total_marine_num--; print(); }
        
        void print() {
            std::cout << total_marine_num << std::endl;
        }
};
int Marine::total_marine_num = 0;
Marine::Marine() {
	total_marine_num++;
}

int main() {
    Marine marine;
    marine.print();
    return 0;
}
