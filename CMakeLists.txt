cmake_minimum_required(VERSION 3.17)
project(COMP_2012_PA2_2020Fall_)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(COMP_2012_PA2_2020Fall_
        account.cpp
        account.h
        expenses.cpp
        expenses.h
        income.cpp
        income.h
        ledger.cpp
        ledger.h
        main1.cpp
        main2.cpp
        main3.cpp
        transactions.cpp
        transactions.h)
