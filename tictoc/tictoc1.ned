//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//
//tictoc1.ned
// module 정의 
simple Txc1
{
    gates:
        input in;
        output out;
}
//
// Txc1이라는 module에 in, out gates 설정 
// Two instances (tic and toc) of Txc1 connected both ways.
// Tic and toc will pass messages to one another.

// Tictioc1 이라는 network 정의 
network Tictoc1
{
    submodules: // network에서 submodule 정의 
        tic: Txc1; // tic은 모듈 Txc1이다.
        toc: Txc1; // toc 또한 "
    connections: // network에서 connection 관계 정의 
        tic.out --> {  delay = 100ms; } --> toc.in; 
        // tic에서 out gate를 통해 100ms delay를 가지고 toc의 in gate로 간다. 
        tic.in <-- {  delay = 100ms; } <-- toc.out;
}

