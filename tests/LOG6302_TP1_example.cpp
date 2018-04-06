
#if 0
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
#endif

int main(void) {
#if 0
Foo foo;

    if (foo.bar() == 17) {
        while (true) {
            if (foo.x == 42) {
                break;
            }
            continue;
        }
    }
#endif

    int k =5;
    if(k < 10)
    {
	    while(true)
	    {
		    if(k == 5) break;
		    continue;
	    }
    }
    return 0;
}
