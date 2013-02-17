#include <iostream>
#include "RBST.hpp"
using namespace std;
int main() {
	
	RBST *s = new RBST();
	char c;
	Key k;
	do {
		cout<<"a - add\nf - find\nd - del\np - print\nq - quit\n";
		cin>>c;
		if (!(c!='a' || c!='f' || c!='d' || c!='q'))
			continue;
		if(c!='p' && c!='q'){
			cout<<"Value:\n";
		    cin>>k;
		}
		if(c=='a') {
			
			s->add(k);
		} else if(c == 'f') {
			
			if((s->find(k)))
				cout<<"Found!\n";
			else
				cout<<"Nod found!\n";
			
		} else if(c == 'd') {
			s->del(k);
		} else if (c=='p') {
			s->dump();
		}
			}while(c!='q');
	cout<<"That's all, folks!\n";
	return 0;
}
