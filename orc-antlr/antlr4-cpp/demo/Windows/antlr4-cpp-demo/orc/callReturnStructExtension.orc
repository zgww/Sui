package Test

import * from "./Struct.orc"

struct Vec3 {
    Main main
    float x
}
Vec3 mkVec3(){
    Vec3 v
    return v
}
extension Vec3 {
    Vec3 print(){
        return mkVec3()
    }
    Vec3 gogo(){
        return mkVec3()
    }

}
void printMyName(){
    mkVec3().print().gogo()
}

