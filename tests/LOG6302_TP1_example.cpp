

class Foo {

public:
    int x;

    int bar() {
        if (false)
            return 42;
	int k = baz();
        for (int i = 0; i < -1; i++)
	{
		if( i == 100)
			break;
	}

        return -1;
    }

    int baz(){
	    if(true)
	    {
		    for(int j = 0; j < 10; ++j)
			    ++x;
	    }
	    return x;
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

    return 0;
}
