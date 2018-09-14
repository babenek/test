#include <iostream>



typedef unsigned BitPos;
enum class FlagPos : BitPos{_0=0,_1=1,_2=2,_3=3,_4=4,_5=5,_6=6,_7=7};
enum class FlagState{N,O,I,};

class Flag
{
private:
FlagPos position;
FlagState state;
public:
Flag(const FlagPos x,const FlagState y):position{x},state{y}{}
Flag(const FlagPos x):position{x},state{FlagState::N}{}
void setState(const FlagState x){state=x;}
FlagState getState() const {return state;}
void set1(){state=FlagState::I;}
void set0(){state=FlagState::O;}
template <class T> void apply(T & i)
{
	const T mask=(static_cast<T>(1))<<(static_cast<BitPos>(position));
	switch(state)
	{
	case FlagState::O:
	{
		std::cout<<"-"<<~mask<<std::endl;
		i &= ~mask;
	}
	break;
	case FlagState::I:
	{
	
		std::cout<<"+"<<mask<<std::endl;
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



int main(int vc,char *vp[])
{
std::cout<<std::hex;


Flag f(FlagPos::_2);
if(f.getState() == FlagState::N)
std::cout<<"NUL";
else if(f.getState() == FlagState::I)
std::cout<<"ONE";
else if(f.getState() == FlagState::O)
std::cout<<"ZERO";
else
std::cout<<"????";

std::cout<<std::endl;


unsigned t=0x9;
try{
f.apply(t);
}catch(const std::exception & e){
std::cout<<e.what()<<std::endl;
}
std::cout<<t<<std::endl;
f.set1();
f.apply(t);
std::cout<<t<<std::endl;
f.set0();
f.apply(t);
std::cout<<t<<std::endl;













return 0;
}


