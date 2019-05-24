//
// Created by user on 24.05.19.
//

#include <random>
#include <chrono>
#include <iostream>

typedef unsigned long long ULL;

const size_t XMAX = 0x100000;
const size_t STAT = 100;

const size_t YMAX = 0x100000;
const size_t ZMAX = 0x100000;

unsigned
hash(const ULL val)
{
	/*
	return val & 0xFFFFF;
	AVG=225.32 SIGM=1.16516
	*/
	/*
	return val % 0xffffd;
	 AVG=282.43 SIGM=1.59534
	 */
}

template<typename T>
std::pair<double, double>
zstat(T *ara, const unsigned size)
{
	double S = 0;
	for (unsigned n = 0; n < size; ++n)
	{
		S += ara[n];
	}
	S /= size;
	double Z = 0;
	for (unsigned n = 0; n < size; ++n)
	{
		const double t = ara[n] - S;
		Z += ((t * t) / size);
	}
	return std::make_pair(S, sqrt(Z));
}

class Node
{
public:
	int tc;
	ULL val;
	Node *next;
	Node() : tc(0), val(0), next(0) {}
};

class List
{
public:
	int tc;
	Node *nodes;
	unsigned inod;
	Node *dup;
	List() : tc(0), nodes(0), inod(0), dup(0)
	{
		nodes = new Node[YMAX];
		dup = new Node[ZMAX];
	}
	~List()
	{
		delete[]nodes;
		delete[]dup;
	}
	void
	init()
	{
		tc++;
		inod = 0;
	}
	void
	insert(const ULL val)
	{
		Node *n = &nodes[hash(val)];
		if (n->tc == tc)
		{
			while (n->val != val)
			{
				if (n->next)
				{
					n = n->next;
				}
				else
				{
					dup[inod].tc = tc;
					dup[inod].next = 0;
					dup[inod].val = val;
					n->next = &dup[inod];
					++inod;
					break;
				}
			}
		}
		else
		{
			n->tc = tc;
			n->next = 0;
			n->val = val;
		}
	}

	bool
	check(const ULL val)
	{
		Node *n = &nodes[hash(val)];
		while (n->tc == tc)
		{
			if (n->val == val)
			{
				return true;
			}

			if (n->next)
			{
				n = n->next;
			}
			else
			{
				return false;
			}
		}
		return false;
	}
	void
	remove(const ULL val)
	{
		Node *n = &nodes[hash(val)];
		Node *m = 0;
		while (n->tc == tc)
		{
			if (n->val == val)
			{
				if (m)
				{
					m->next = n->next;
					n->tc = -1;
				}
				else
				{
					if (n->next)
					{
						n->val = n->next->val;
						n->next = n->next->next;
					}
					else
					{
						n->tc = -1;
					}
				}
				return;
			}
			else
			{
				if (n->next)
				{
					m = n;
					n = n->next;
					continue;
				}
				else
				{
					return;
				}
			}
		}
	}

	void
	stat()
	{
		unsigned S = 0;
		for (unsigned n = 0; n < YMAX; ++n)
		{
			//std::cout << n<<":" <<nodes[n].tc<<"="<<nodes[n].val << std::endl;
			if (nodes[n].tc == tc)
				S++;
		}
		std::cout << "fill k=" << static_cast<double>(S) / YMAX << std::endl;
	}
};

int
main(void)
{
	ULL stat[STAT];
	std::mt19937_64 gen(0x0123456789ABCDEF);
	ULL *ara = new ULL[XMAX];

	{
		List tt;
		tt.init();
		for (auto n = 0; n < XMAX; ++n)
		{
			ULL t = gen();
			while (tt.check(t))
			{
				t = gen();
			}
			tt.insert(t);
			ara[n] = t;
		}
	}
	List ll;

	for (auto s = 0; s < 100; ++s)
	{
		const auto start = std::chrono::system_clock::now();
		ll.init();

		ll.stat();

		for (auto n = 0; n < XMAX; ++n)
		{
			ll.insert(ara[n]);
		}

		ll.stat();

		for (auto n = 0; n < XMAX; ++n)
		{
			if (not ll.check(ara[n]))
				return 1;
		}

		for (auto n = 0; n < XMAX; n += 2)
		{
			ll.remove(ara[n]);
		}

		ll.stat();

		for (auto n = 0; n < XMAX;)
		{
			if (ll.check(ara[n]))
				return 2;
			++n;
			if (not ll.check(ara[n]))
				return 3;
			++n;
		}

		const auto duration = std::chrono::system_clock::now() - start;
		stat[s] = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
		std::cout << s << " PASS " << stat[s] << " msec" << std::endl;
	}
	const auto zs = zstat(stat, STAT);
	std::cout << "AVG=" << zs.first << " SIGM=" << zs.second << std::endl;
	delete[]ara;
	return 0;
}

