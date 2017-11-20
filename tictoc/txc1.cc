//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

// txc1.cc
// ned 파일의 실질적인 움직임을 정의
#include <string.h>
#include <omnetpp.h>
/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
// cSimpleModule에 정의되어있는(OMNeT++에 정의) 모듈 Txc1의 동작을 정의한다.
class Txc1 : public cSimpleModule
{
  protected:
    // The following redefined virtual function holds the algorithm.
    // initialize와 handleMessage가 모듈 동작의 대부분이다.
    virtual void initialize();
    // msg를 받아 처리한다.
    virtual void handleMessage(cMessage *msg);
};
// The module class needs to be registered with OMNeT++
// 모듈 등록
Define_Module(Txc1);
// Functions definition
void Txc1::initialize()
{
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be `tic'.
    // Am I Tic or Toc?
    // getName()은 모듈의 이름을 가져온다. -> tic에서 시작.
    if (strcmp("tic", getName()) == 0)
    {
        // create and send first message on gate "out". "tictocMsg" is an
        // arbitrary string which will be the name of the message object.
        // "tictocMsg"라는 메세지를 만들어서 msg에 저장.
        cMessage *msg = new cMessage("tictocMsg");
        // send(msg, gateName, gateIndex), return 값은 딜레이되서 나온 결과값(ned에 정의)
        send(msg, "out");
    }
}
void Txc1::handleMessage(cMessage *msg)
{
    // The handleMessage() method is called whenever a message arrives
    // at the module. Here, we just send it to the other module, through
    // gate `out'. Because both `tic' and `toc' does the same, the message
    // will bounce between the two.
    send(msg, "out");
}

