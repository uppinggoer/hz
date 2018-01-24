int func1() {
    int i=1;
    int j=2;
    return i+j+func3()+func2();
}
int func2() {
    int i=2;
    int j=2;
    return i+j;
}
int func3() {
    int i=3;
    int j=2;
    return i+j;
}

int main(int argc, char const *argv[])
{
    func1();
    func2();
    return 0;
}