#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cassert>

class Dice {
    private:

    public:
        int flat;
        int* rolls;
        int roll_size;

        ~Dice() {
            delete this->rolls;
        }

        // constructors
        Dice() {
            this->flat = 0;
            this->roll_size = 1;
            this->rolls = new int[1] {1};
        };

        Dice(int faces) {
            this->flat = 0;
            this->roll_size = faces + 1;
            this->rolls = new int[roll_size];

            for (int i = 0; i < roll_size; i++) {
                this->rolls[i] = i > 0;
            }
        };

        Dice(int* rolls, int roll_size, int flat) {
            this->rolls = new int[roll_size];
            memcpy(this->rolls, rolls, roll_size * sizeof(int));

            this->roll_size = roll_size;
            this->flat = flat;
        }

        Dice(const Dice& dice) {
            this->rolls = new int[dice.roll_size];
            memcpy(this->rolls, dice.rolls, dice.roll_size * sizeof(int));
        
            this->roll_size = dice.roll_size;
            this->flat = dice.flat;
        }

        //functions
        float average() {
            int outcomes = 0;
            int sum_outcomes = 0;

            for (int i = 1; i < this->roll_size; i++) {
                outcomes += this->rolls[i];
                sum_outcomes += this->rolls[i] * i;
            }

            return (outcomes > 0 ? float(sum_outcomes)/outcomes : 0) + this->flat;
        };

        Dice crit() {
            return *this + Dice(this->rolls, this->roll_size, 0);
        }

        //operators
        Dice operator+(const Dice& other) {
            int roll_size = other.roll_size + this->roll_size - 1;
            int* rolls = (int*)calloc(roll_size, sizeof(int));


            for (int i = 0; i < this->roll_size; i++) {
                if (this->rolls[i] == 0) continue;

                for (int j = 0; j < other.roll_size; j++) {
                    if (other.rolls[j] == 0) continue;

                    rolls[i + j] += this->rolls[i] * other.rolls[j];
                }
            }

            Dice result = Dice(rolls, roll_size, this->flat + other.flat);
            free(rolls);
            return result;
        }

        Dice operator+(int other) {
            return Dice(this->rolls, this->roll_size, this->flat + other);
        }

        Dice operator*(int other) {
            assert(other >= 0);
            if (other == 0) {
                return Dice();
            }

            return *this + *this * (other - 1);
        }

        const Dice& operator=(const Dice& other) {
            return other;
        }

};


int main() {
    // test empty dice
    Dice empty = Dice();

    // assert(empty.average() == 0);
    
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
