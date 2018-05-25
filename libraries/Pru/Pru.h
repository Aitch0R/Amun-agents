
class Pru{
public:
Test* t;
Pru(int u,Test* foo){
t=foo;}

void foos(){
	t->foo();
}
};
