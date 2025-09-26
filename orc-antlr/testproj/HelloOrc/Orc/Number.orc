package OrcLang


import * from "./String.orc"

//受urgc管理的列表

class Number {
    String@ toString(){
        return str("")
    }
    long long toLongLong(){
        return 0
    }
    int toInt(){
        return 0
    }
    double toDouble(){
        return 0
    }
}
class Integer extends Number {
    int value = 0
    String@ toString(){
        return str("").addi(self.value)
    }
    int toLongLong(){
        return self.value
    }
    int toInt(){
        return self.value
    }
    double toDouble(){
        return self.value
    }
}
class Boolean extends Number {
    bool value = false;
    String@ toString(){
        return str("").add(self.value?"true":"false")
    }
    long long toLongLong(){
        return self.value
    }
    int toInt(){
        return self.value
    }
    double toDouble(){
        return self.value
    }
}
class Float extends Number {
    float value = 0
    String@ toString(){
        return str("").addf(self.value)
    }
    long long toLongLong(){
        return self.value
    }
    int toInt(){
        return self.value
    }
    double toDouble(){
        return self.value
    }
}
class Double extends Number {
    double value = 0;
    String@ toString(){
        return str("").addf(self.value)
    }
    long long toLongLong(){
        return self.value
    }
    int toInt(){
        return self.value
    }
    double toDouble(){
        return self.value
    }
}

Integer@ mkInteger(int v){
    Integer@ o = new Integer();
    o.value = v
    return o
}
Boolean@ mkBoolean(bool v){
    Boolean@ o = new Boolean();
    o.value = v
    return o
}
Double@ mkDouble(double v){
    Double@ o = new Double();
    o.value = v
    return o
}
Float@ mkFloat(float val){
    Float@ v = new Float()
    v.value = val
    return v
}
