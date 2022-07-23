#include <iostream>
#include <vector> 
#include <iostream>

void test(){
    printf("test\n");
}


auto f1 = [](int x, int y) { return x + y; };

int main(){

    std::vector<void (*)()> vec={test};
    vec[0]();

    std::cout<<"done\n";

}
