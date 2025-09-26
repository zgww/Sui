package Project_Mod;


int say(){
    return 10;
}
class Father {
    void lala(){
    }
}
class User extends Father{

    void print(){

    }
}
static void st(){

}
extension User {
    void calc(){

    }
}
User@ useRef(User@ u){
    return u;
}
void main(){
    User@ a = null;
    User@ b = a;
    User *c = null;
    b = c;
    useRef(b);
}
