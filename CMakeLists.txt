cmake_minimum_required(VERSION 3.26)
project(P6)

set(CMAKE_CXX_STANDARD 17)

add_executable(P6 main.cpp
        PaMedicamento.cpp
        PaMedicamento.h
        MediExpress.cpp
        MediExpress.h
        Laboratorio.cpp
        Laboratorio.h
        Farmacia.cpp
        Farmacia.h
        Stock.cpp
        Stock.h
        ThashMedicam.cpp
        ThashMedicam.h
        MallaRegular.cpp
        MallaRegular.h
        Usuario.cpp
        Usuario.h
        UTM.cpp
        UTM.h)
