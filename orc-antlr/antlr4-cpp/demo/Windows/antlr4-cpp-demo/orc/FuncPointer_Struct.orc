package Project_Mod;


struct Father {
    void (*hi)();
}

struct User {
    Father *p;
    Father p2;
}
void main(){
    Father f;
    f.hi()
}