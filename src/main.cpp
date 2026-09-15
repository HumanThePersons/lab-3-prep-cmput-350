#include "UniquePtr.h"
#include <iostream>
#include <cassert>

// For testing access to member
struct testClass {
        int id() const { return 0; }
    };

int main() {
    // Default-constructor - UniquePtr is empty
    UniquePtr<int> empty;
    assert(!empty.operator bool());

    // Construct from a raw pointer
    UniquePtr<int> ptest1(new int(5));
    assert(*ptest1 == 5);

    UniquePtr<testClass> ptest2(new testClass());
    assert(ptest2->id() == 0);

    // Move construction empties the ptest1 and moves value to ptest2
    UniquePtr<int> ptest3(std::move(ptest1));
    assert(!ptest1.operator bool());
    assert(*ptest3 == 5);

    // Move assignment replaces and frees ptest4's old value
    UniquePtr<int> ptest4(new int(10));
    ptest4 = std::move(ptest3);
    assert(*ptest4 == 5);
    assert(!ptest3.operator bool());

    // Testing release() gets rid of ownership without destroying it
    int* raw = ptest4.release();
    assert(!ptest4.operator bool());
    assert(*raw == 5);
    delete raw;  // deleting test ptr

    // reset() replaces and destroys the old one
    UniquePtr<int> ptest5(new int(6));
    ptest5.reset(new int(7));
    assert(*ptest5 == 7);

    // testing swap()
    UniquePtr<int> ptest6(new int(10));
    UniquePtr<int> ptest7(new int(20));
    ptest6.swap(ptest7);
    assert(*ptest6 == 20);
    assert(*ptest7 == 10); 

    // test makeUnique
    auto ptest8 = makeUnique<int>(5);
    assert(*ptest8 == 5);

    std::cout << "End tests";

    return 0;
}
