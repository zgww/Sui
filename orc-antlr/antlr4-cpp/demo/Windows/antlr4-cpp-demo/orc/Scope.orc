package Test

class User {
    void * __exit__(){
    }
}

User@ div(){
    return new User()
}

void main(){
    div().{
        div().{
            div(o).{ }
            div().{ }
            div().{ }
            div().{ }
            div().{ }
            div().{ }
        }
        //统一的处理
        //clearUnusedNodes(o)
    }
}