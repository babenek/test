//
// Created by user on 17.02.19.
//


#include <iostream>

class V
{
public:
	const int id;
	const unsigned edges;
	V **v;

	V(const int id_, const unsigned edges_)
		: id(id_), edges(edges_), v(nullptr)
	{
		v = new V *[edges];
	}

	~V()
	{
		delete[] v;
	}
};

void solve(V *v)
{
	V *n = v;
	while (true)
	{
		std::cout << "id:" << n->id << " ";
		if (nullptr != n->v and 0 != n->edges)
		{
			n = n->v[0];
		}
		else
			break;
	}
}

int main(int argc, char *argv[])
{
	V v0(0, 1);
	V v1(1, 1);
	V v2(2, 1);
	V v3(3, 1);
	V v4(4, 1);
	V v5(5, 1);
	V v6(6, 1);
	V v7(7, 1);
	V v8(8, 1);
	V v9(9, 0);

	v0.v[0] = &v1;
	v1.v[0] = &v2;
	v2.v[0] = &v3;
	v3.v[0] = &v4;
	v4.v[0] = &v5;
	v5.v[0] = &v6;
	v6.v[0] = &v7;
	v7.v[0] = &v8;
	v8.v[0] = &v9;

	solve(&v0);

	return 0;
}