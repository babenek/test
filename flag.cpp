#include <iostream>


typedef unsigned BitPos;
enum class FlagPos : BitPos
{
	_0 = 0, _1 = 1, _2 = 2, _3 = 3, _4 = 4, _5 = 5, _6 = 6, _7 = 7
};


class Flag
{
public:

	enum class State
	{
		_, O, I,
	};

protected:
	State state;

public:

	Flag()
		: state(State::_)
	{
	}


	Flag(const bool x)
		: state(x ? State::I : State::O)
	{
	}


	virtual ~Flag()
	{
	}


	void set(const bool x)
	{
		state = x ? State::I : State::O;
	}

	bool get() const
	{
		if (Flag::State::I == state)
		{
			return true;
		}
		if (Flag::State::O != state)
		{
			throw std::domain_error("flag is not inited");
		}
		return false;
	}


};


class FlagBit : public Flag
{
protected:
	FlagPos position;
public:
	FlagBit(const FlagPos x, const bool y)
		: Flag(y), position(x)
	{
	}

	FlagBit(const FlagPos x)
		: Flag(), position(x)
	{
	}

	void setState(const Flag::State x)
	{
		state = x;
	}

	Flag::State getState() const
	{
		return state;
	}

	void set1()
	{
		state = Flag::State::I;
	}

	void set0()
	{
		state = Flag::State::O;
	}

	template<class T>
	void apply(T &i)
	{
		const T mask = (static_cast<T>(1)) << (static_cast<BitPos>(position));
		switch (state)
		{
			case Flag::State::O:
			{
				std::cout << "-" << ~mask << std::endl;
				i &= ~mask;
			}
				break;
			case Flag::State::I:
			{

				std::cout << "+" << mask << std::endl;
				i |= mask;
			}
				break;
			default:
			{
				throw std::domain_error("flag is not inited");
			}
				break;
		}
	}
};


int main(int vc, char *vp[])
{
	std::cout << std::hex;


	FlagBit f(FlagPos::_2);
	if (f.getState() == Flag::State::_)
		std::cout << "NUL";
	else if (f.getState() == Flag::State::I)
		std::cout << "ONE";
	else if (f.getState() == Flag::State::O)
		std::cout << "ZERO";
	else
		std::cout << "????";

	std::cout << std::endl;


	unsigned t = 0x9;
	try
	{
		f.apply(t);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << t << std::endl;
	f.set1();
	f.apply(t);
	std::cout << t << std::endl;
	f.set0();
	f.apply(t);
	std::cout << t << std::endl;


	return 0;
}


