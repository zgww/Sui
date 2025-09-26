
package Orc


struct ScopeData {
    void *data
    void *onExitScope
}

// typedef struct ScopeData ScopeData

// ScopeData mkScopeData(void *data, void (*onExitScope)(void *scopeData)){
ScopeData mkScopeData(void *data, void* onExitScope){
    ScopeData ret;
    ret.data = data
    ret.onExitScope = onExitScope  
    return ret
}