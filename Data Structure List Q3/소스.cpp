#include <iostream>
using namespace std;

class Polynomial {
private:
	double coeff; // 계수
	int degree;   // 차수
public:
	Polynomial(double coeff = 0.0, int degree = 0) {
		this->coeff = coeff;
		this->degree = degree;
	}
	double getCoeff()
	{
		return coeff;
	}
	int getDegree()
	{
		return degree;
	}
	double setcoeff(double a)
	{
		this->coeff = a;
		return coeff;
	}
	// 필요하면 아래에 관련 멤버 함수 작성 가능
};

class Node {
private:
	Polynomial p;
	Node* Link = nullptr;
public:
	Node(Polynomial poly = 0)
		:p(poly)
	{

	}
	Node* getlink()
	{
		return this->Link;
	}
	void setlink(Node* next)
	{
		this->Link = next;
	}
	Polynomial getData()
	{
		return this->p;
	}
	void setData(Polynomial poly)
	{
		p = poly;
	}
	double getCoeff()
	{
		double a = p.getCoeff();
		return a;
	}
	int getDegree()
	{
		return p.getDegree();
	}
};

class Linkedlist {
private:
	Node head;
	int cnt;
	Node* getHead()
	{
		return head.getlink();
	}
	Node* getNode(int pos)
	{
		Node* p = &head;
		for (int i = -1; i < pos; i++)
		{
			if (p == nullptr)break;
			p = p->getlink();
		}
		return p;
	}
public:
	Linkedlist() {
		this->cnt = 0;
	}
	bool empty()
	{
		return this->getHead() == nullptr;
	}
	int size()
	{
		return this->cnt;
	}
	void insert(int pos, Polynomial poly)
	{
		Node* prev = this->getNode(pos - 1);
		if (prev != nullptr)
		{
			Node* p = new Node(poly);
			p->setlink(prev->getlink());
			prev->setlink(p);
			this->cnt++;
		}
	}
	void remove(int pos)
	{
		Node* prev = this->getNode(pos - 1);
		if (prev != NULL)
		{
			Node* removed = prev->getlink();
			prev->setlink(removed->getlink());
			delete removed;
			this->cnt--;
		}
	}
	void display()
	{
		int cnt;
		Node* p = getHead();

		cout << fixed;
		cout.precision(1);
		cout << "f(x) = " << p->getCoeff();
		cout << " x^" << p->getDegree();

		for (Node* p = getNode(1); p != nullptr; p = p->getlink())
		{
			cout << fixed;
			cout.precision(1);
			cout << " + " << p->getCoeff();
			cout << " x^" << p->getDegree();
		}

		cout << endl;
	}
	void replace(int pos, Polynomial poly) {
		if (this->empty() || !(pos >= 0 && pos < size()))
			throw "error: List is empty or out of range";
		Node* node = getNode(pos);
		node->setData(poly);
	}
	void sorted_insert(Polynomial poly)
	{
		if (this->empty() == true)
		{
			insert(0, poly);
		}
		else {
			if (getNode(this->size() - 1)->getDegree() >= poly.getDegree())
			{
				if (this->getNode(this->size() - 1)->getDegree() == poly.getDegree())
				{
					double coeff = this->getNode(this->size() - 1)->getCoeff() + poly.getCoeff();
					Polynomial p(coeff, poly.getDegree());
					this->replace(size() - 1, p);
				}
				else {
					insert(this->size(), poly);
				}
			}
			else {
				int size = this->size();
				for (int i = 0; i < size; i++)
				{
					if (getNode(i)->getDegree() == poly.getDegree())
					{
						double coeff = (this->getNode(i)->getCoeff() + poly.getCoeff());
						Polynomial p(coeff, poly.getDegree());
						replace(i, p);
						break;
					}
					else if (getNode(i)->getDegree() < poly.getDegree())
					{
						insert(i, poly);
						break;
					}
				}
			}
		}
	}
	bool zero()
	{		
		for (Node* p = getHead(); p != nullptr; p = p->getlink())
		{
			if (p->getCoeff() == 0)
			{
				continue;
			}
			else {
				return true;
			}
		}
		return false;
	}
};


int main()
{
	int n;
	cin >> n;

	Linkedlist list1;
	Linkedlist list2;
	Linkedlist Biglist;
	for (int i = 0; i < n; i++)
	{
		double coeff;
		int degree;
		cin >> coeff >> degree;

		Polynomial p(coeff, degree);
		list1.sorted_insert(p);
		Biglist.sorted_insert(p);
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		double coeff;
		int degree;
		cin >> coeff >> degree;

		Polynomial k(coeff, degree);
		list2.sorted_insert(k);
		Biglist.sorted_insert(k);
	}
	list1.display();
	list2.display();
	if (Biglist.zero() == false)
	{
		cout << "f(x) = 0" << endl;
	}
	else {
		Biglist.display();
	}


	return 0;
}