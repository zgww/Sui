package project;


#include "Main.h"

// 类似于typescript的导出
import * from 'Mod'


//Ori的行为与c一致
struct Ori{
    
};

//类全部继承Object
//Object提供虚函数，接口表, 反射的支持

class Model {
}

interface IRunnable {
}
interface IEmit extends IRunnable, IBoss {
}

class User extends Model {
    int age = 10
    char a = ''
    char *name = "";
    char * getName(){
        return name;
    }
}

extension User {
    int getAge(){
        return age;
    }
}


//扩展，是函数的简写法
extension float {
    float toFixed(){
        return (int)(this * 100) / 100.f ;
    }
}

//所有的功能都会加上package + '_' 前缀，然后生成
//c中的全局函数。
//会统一生成extern声明，所以顺序无关
//也支持static 函数，跟c一致
//除值传递和指针外，支持 urgc 引用。用'@'表示
//urgc引用会生成额外的引用和解引用代码
//urgc引用使用方式跟一级指针一致

/*编程的核心特性：

1. 内存管理
2. 模块隔离
3. 模块局部导入, 不引起全局冲突。
4. 静态派发
5. 动态派发 (单继承，多接口)。 接口采用胖指针传递
6. 反射
7. 闭包
8. 字典和数组字面量
9. 泛型, 纯用来代码提示即可。

*/



void whoami(User@ user){
    printf("user:%s\n", user->name);
}
void main(){
    float ratio = 10.f;
    ratio.toFixed();
    main_sayhi();
    sayok();
    
}
