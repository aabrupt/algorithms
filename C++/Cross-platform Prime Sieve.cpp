# include <iostream>
# include <ctime>
# include <vector>
# include <chrono>
# include <future>

# define Debug 1
# if Debug
# define LOG(x) std::cout << x;
# else
# define LOG(x);
# endif

class SieveOfEratosthenes
{
private:
    int MaxNumber;
    bool Running = true;
    int CurrentIndex;

    std::vector<int> Primes;

    std::chrono::high_resolution_clock::time_point start, stop;
    double Speed;

    void Sieve()
    {
        for (int i = 0; i < this->MaxNumber; i++)
        {
            Primes.emplace_back(i);
        }

        Primes[1] = 0;

        for (int i = 0; i < Primes.size(); i++)
        {
            this->CurrentIndex = i;

            if (Primes[i] <= 0) continue;

            for (int j = Primes[i] * 2; j < Primes.size(); j += Primes[i])
            {
                Primes[j] = 0;
            }
        }

        Primes.erase(remove(Primes.begin(), Primes.end(), 0), Primes.end());

    }

    void setMaxNumber(const int MaxNumber) {
        if (MaxNumber < 0) {
            this->MaxNumber = MaxNumber * -1;
            return;
        }
        this->MaxNumber = MaxNumber;
    }

public:

    SieveOfEratosthenes(const int MaxNumber)
    {
        setMaxNumber(MaxNumber);

        this->Primes.reserve(MaxNumber);

        this->start = std::chrono::high_resolution_clock::now();

        Sieve();

        this->stop = std::chrono::high_resolution_clock::now();
        this->Speed = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()) / 1000;
    }

    ~SieveOfEratosthenes()
    {
        LOG("Prime Numbers Discovered:" << std::endl << std::endl);

        LOG(Primes.size());

        LOG(std::endl << std::endl << "Execution time: " << this->Speed << " s");
    }

    std::vector<int> getPrimes()
    {
        return Primes;
    }

    bool SearchPrime(int n)
    {
        for (int i = 0; i < Primes.size(); i++)
        {
            if (Primes[i] == n) return true;
        }
        return false;
    }

    double getSpeedSeconds()
    {
        return Speed;
    }

    double getSpeedMillis()
    {
        return Speed * 1000;
    }

    double getSpeedMinutes()
    {
        return static_cast<double>(std::chrono::duration_cast<std::chrono::minutes>(stop - start).count());
    }

    std::chrono::high_resolution_clock::time_point getStartTime()
    {
        return start;
    }

    std::chrono::high_resolution_clock::time_point getStopTime()
    {
        return stop;
    }
};
