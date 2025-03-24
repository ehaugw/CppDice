#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cassert>
#include "dice.cpp"


int main() {
    // test empty dice
    Dice empty = Dice();

    assert(empty.average() == 0);

    Dice e3 = empty;
    // e3 = empty;

    // test one regular dice
    Dice d6 = Dice(6);
    assert(d6.average() == 3.5);
    Dice d8 = Dice(8);
    assert(d8.average() == 4.5);

    // test add operator
    assert((Dice(6) + Dice(8)).average() == 8);
    assert((Dice(6) + Dice(6)).average() == 7);
    assert((d6 + empty).average() == (empty + empty + d6).average());
    assert((d8 + d6).average() == (d6 + d8).average());
    assert((Dice(6) + 1).average() == 4.5);
    assert((Dice(6) + (Dice(8) + 1)).average() == 9);

    // test multiply operator
    assert((d6*1).average() == d6.average() * 1);
    assert((d6*0).average() == 0);
    assert((d6*1).average() == d6.average());
    assert((d6*2).average() == d6.average() * 2);
    assert((d6*4).average() == d6.average() * 4);

    // test crit
    assert(Dice(6).crit().average() == 7);
    assert((Dice(6)+1).crit().average() == 8);

    std::cout << "End of tests\n";
}
