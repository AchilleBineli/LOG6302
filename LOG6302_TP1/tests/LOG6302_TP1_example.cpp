#include <iostream>
#include <string>
#include <vector>
class Foo {

public:
    int x;
    std::string name_;

    int bar() {
        if (false)
            return 42;
        for (int i = 0; i < -1; i++);
        return -1;
    }

    void setName(std::string name)
    {
	    name_ = name;
    }

    std::string getName()
    {
	    return name_;
    }
};

int main(void) {
    Foo foo;

    if (foo.bar() == 17) {
        while (true) {
            if (foo.x == 42) {
                break;
            }
            continue;
        }
    }
    std::string name = "LOG6302";
    foo.setName(name);
    
    return 0;
}
