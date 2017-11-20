//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

// Txc4.ned
simple Txc4
{
    parameters:
        // whether the module should send out a message on initialization
        // 이렇게 함으로서 초기에 누구를 먼저 보낼 지 정할 수 있다.
        bool sendMsgOnInit = default(false); // sendMsgOnInit을 false로 지정.
        int limit = default(2);   // another parameter with a default value
        @display("i=block/routing");
    gates:
        input in;
        output out;
}
network Tictoc4
{
    submodules:
        tic: Txc4 {
            parameters:
                // tic의 sendMsgOnInit을 true로 지정함으로서 순서를 지정하는 효과.
                sendMsgOnInit = true;
                @display("i=,cyan");
        }
        toc: Txc4 {
            parameters:
                sendMsgOnInit = false;
                @display("i=,gold");
        }
    connections:
        tic.out --> {  delay = 100ms; } --> toc.in;
        tic.in <-- {  delay = 100ms; } <-- toc.out;
}
