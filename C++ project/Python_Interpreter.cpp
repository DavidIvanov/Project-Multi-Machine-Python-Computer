#include <stdio.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <iostream>
#include <string>

//this only for mac because Python.h is a framework
#define PY_SSIZE_T_CLEAN
#include <Python/Python.h>

using namespace std;

//whole code might only work on mac

static void run_python(char* script_name, char* func_name, char* arguments[], int num_arguments){
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i = 0;

    Py_Initialize();
    pName = PyString_FromString(script_name);
    
    pModule = PyImport_Import(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, func_name);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(num_arguments);
            for (i = 0; i < num_arguments; ++i) {
                pValue = PyLong_FromLong(atoi(arguments[i]));
                if (!pValue) {
                    Py_DecRef(pArgs);
                    Py_DecRef(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DecRef(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                Py_DecRef(pValue);
            }
            else {
                Py_DecRef(pFunc);
                Py_DecRef(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", func_name);
        }
        Py_DecRef(pFunc);
        Py_DecRef(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", script_name);
        
    }
    Py_Finalize();
    

}


int main(){
    
}